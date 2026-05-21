//! Minimal LSP client. JSON-RPC 2.0 over stdio with a threaded reader and
//! blocking request/response. Goto-definition is the only feature wired up
//! for now; diagnostics, completion, etc. arrive later.
//!
//! Threading model:
//! - The spawned server reads from its stdin and writes to its stdout.
//! - We own one writer (the main thread writes requests/notifications via
//!   `ChildStdin`).
//! - A dedicated reader thread parses Content-Length-framed messages off
//!   the child's stdout and forwards each as a `Message` over an mpsc
//!   channel.
//! - The main thread drains the channel synchronously when it needs a
//!   response, discarding unrelated notifications in the meantime.

use std::collections::HashMap;
use std::io::{self, BufRead, BufReader, Read, Write};
use std::path::{Path, PathBuf};
use std::process::{Child, ChildStdin, ChildStdout, Command, Stdio};
use std::sync::mpsc;
use std::thread;
use std::time::{Duration, Instant};

use serde_json::{Value, json};

/// A response or notification received from the LSP server.
pub enum Message {
    Response {
        id: u64,
        result: Result<Value, LspError>,
    },
    Notification {
        method: String,
        params: Value,
    },
}

#[derive(Debug, Clone)]
pub struct LspError {
    pub code: i64,
    pub message: String,
}

pub struct LspClient {
    child: Child,
    stdin: ChildStdin,
    next_id: u64,
    rx: mpsc::Receiver<Message>,
    /// Latest published diagnostics per document URI. Replaced wholesale
    /// every time the server sends `textDocument/publishDiagnostics` for
    /// that URI (LSP semantics: an empty array clears).
    diagnostics: HashMap<String, Vec<Diagnostic>>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DiagnosticSeverity {
    Error,
    Warning,
    Information,
    Hint,
}

#[derive(Debug, Clone)]
pub struct Diagnostic {
    pub start_line: u32,
    pub start_character: u32,
    pub end_line: u32,
    pub end_character: u32,
    pub severity: DiagnosticSeverity,
    pub message: String,
    pub source: Option<String>,
}

/// Result of `textDocument/definition`. Always reduced to a single location
/// — if the server returned an array, we pick the first.
#[derive(Debug, Clone)]
pub struct DefinitionLocation {
    pub uri: String,
    pub line: u32,
    pub character: u32,
}

impl LspClient {
    /// Spawn `program` with `args` and complete the LSP
    /// `initialize`/`initialized` handshake. `root_uri` is the `file://`
    /// URI of the workspace root.
    pub fn spawn(program: &str, args: &[&str], root_uri: &str) -> io::Result<Self> {
        let mut child = Command::new(program)
            .args(args)
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .stderr(Stdio::null())
            .spawn()?;
        let stdin = child
            .stdin
            .take()
            .ok_or_else(|| io::Error::new(io::ErrorKind::Other, "no child stdin"))?;
        let stdout = child
            .stdout
            .take()
            .ok_or_else(|| io::Error::new(io::ErrorKind::Other, "no child stdout"))?;

        let (tx, rx) = mpsc::channel::<Message>();
        thread::spawn(move || reader_loop(stdout, tx));

        let mut client = LspClient {
            child,
            stdin,
            next_id: 1,
            rx,
            diagnostics: HashMap::new(),
        };

        let init_params = json!({
            "processId": std::process::id(),
            "rootUri": root_uri,
            "workspaceFolders": [{ "uri": root_uri, "name": "workspace" }],
            "capabilities": {
                "general": { "positionEncodings": ["utf-8"] },
                "textDocument": {
                    "definition": { "linkSupport": true },
                    "synchronization": { "didSave": false },
                    "publishDiagnostics": { "relatedInformation": false }
                }
            },
            "clientInfo": { "name": "medit", "version": "0.1.0" }
        });
        let id = client.request("initialize", init_params)?;
        // Wait for the initialize response; gopls can take a few seconds on
        // first run as it indexes the module.
        let _init_result = client.recv_response(id, Duration::from_secs(15))?;
        client.notify("initialized", json!({}))?;
        Ok(client)
    }

    fn request(&mut self, method: &str, params: Value) -> io::Result<u64> {
        let id = self.next_id;
        self.next_id += 1;
        let msg = json!({
            "jsonrpc": "2.0",
            "id": id,
            "method": method,
            "params": params,
        });
        write_message(&mut self.stdin, &msg)?;
        Ok(id)
    }

    fn notify(&mut self, method: &str, params: Value) -> io::Result<()> {
        let msg = json!({
            "jsonrpc": "2.0",
            "method": method,
            "params": params,
        });
        write_message(&mut self.stdin, &msg)
    }

    /// Block until the response to `id` arrives, processing any unrelated
    /// notifications received along the way (so diagnostics published
    /// between requests aren't lost). Returns the inner result or an IO
    /// error if the server times out or disconnects.
    fn recv_response(&mut self, id: u64, timeout: Duration) -> io::Result<Value> {
        let deadline = Instant::now() + timeout;
        loop {
            let now = Instant::now();
            if now >= deadline {
                return Err(io::Error::new(io::ErrorKind::TimedOut, "LSP timeout"));
            }
            let remaining = deadline - now;
            match self.rx.recv_timeout(remaining) {
                Ok(Message::Response { id: rid, result }) if rid == id => {
                    return result.map_err(|e| {
                        io::Error::new(io::ErrorKind::Other, format!("LSP error: {}", e.message))
                    });
                }
                Ok(Message::Notification { method, params }) => {
                    self.handle_notification(&method, &params);
                }
                Ok(Message::Response { .. }) => continue,
                Err(mpsc::RecvTimeoutError::Timeout) => {
                    return Err(io::Error::new(io::ErrorKind::TimedOut, "LSP timeout"));
                }
                Err(mpsc::RecvTimeoutError::Disconnected) => {
                    return Err(io::Error::new(io::ErrorKind::BrokenPipe, "LSP disconnected"));
                }
            }
        }
    }

    /// Drain any pending notifications from the reader thread without
    /// blocking. Updates the diagnostics cache as `publishDiagnostics`
    /// notifications arrive. Stray responses (e.g. a stale definition
    /// result) are dropped on the floor.
    pub fn poll(&mut self) {
        while let Ok(msg) = self.rx.try_recv() {
            if let Message::Notification { method, params } = msg {
                self.handle_notification(&method, &params);
            }
        }
    }

    fn handle_notification(&mut self, method: &str, params: &Value) {
        if method == "textDocument/publishDiagnostics" {
            if let Some((uri, diags)) = parse_publish_diagnostics(params) {
                self.diagnostics.insert(uri, diags);
            }
        }
    }

    /// Latest diagnostics published for `uri`, sorted by start position.
    pub fn diagnostics_for(&self, uri: &str) -> &[Diagnostic] {
        self.diagnostics
            .get(uri)
            .map(|v| v.as_slice())
            .unwrap_or(&[])
    }

    /// Send `textDocument/didChange` with full-text sync. Simple and
    /// gopls-fast — re-runs the diagnostics pass against the new text.
    /// `version` should monotonically increase per URI.
    pub fn did_change(&mut self, uri: &str, version: u64, text: &str) -> io::Result<()> {
        self.notify(
            "textDocument/didChange",
            json!({
                "textDocument": { "uri": uri, "version": version },
                "contentChanges": [ { "text": text } ],
            }),
        )
    }

    pub fn did_open(&mut self, uri: &str, language_id: &str, text: &str) -> io::Result<()> {
        self.notify(
            "textDocument/didOpen",
            json!({
                "textDocument": {
                    "uri": uri,
                    "languageId": language_id,
                    "version": 1,
                    "text": text,
                }
            }),
        )
    }

    /// Send `textDocument/definition` and return the first location, if any.
    pub fn definition(
        &mut self,
        uri: &str,
        line: u32,
        character: u32,
    ) -> io::Result<Option<DefinitionLocation>> {
        let id = self.request(
            "textDocument/definition",
            json!({
                "textDocument": { "uri": uri },
                "position": { "line": line, "character": character },
            }),
        )?;
        let result = self.recv_response(id, Duration::from_secs(5))?;
        Ok(parse_definition_result(&result))
    }

    /// Send `textDocument/hover` and return the response text (joined
    /// across all `MarkedString` items if the server returns an array).
    /// Returns `Ok(None)` when the server reports no hover info at this
    /// position.
    pub fn hover(
        &mut self,
        uri: &str,
        line: u32,
        character: u32,
    ) -> io::Result<Option<String>> {
        let id = self.request(
            "textDocument/hover",
            json!({
                "textDocument": { "uri": uri },
                "position": { "line": line, "character": character },
            }),
        )?;
        let result = self.recv_response(id, Duration::from_secs(5))?;
        Ok(parse_hover_result(&result))
    }

    pub fn shutdown(&mut self) {
        let _ = self.request("shutdown", Value::Null);
        let _ = self.notify("exit", Value::Null);
        let _ = self.child.wait();
    }
}

impl Drop for LspClient {
    fn drop(&mut self) {
        // Best-effort shutdown so child doesn't outlive the editor.
        let _ = self.request("shutdown", Value::Null);
        let _ = self.notify("exit", Value::Null);
        let _ = self.child.kill();
        let _ = self.child.wait();
    }
}

fn parse_publish_diagnostics(params: &Value) -> Option<(String, Vec<Diagnostic>)> {
    let uri = params.get("uri")?.as_str()?.to_string();
    let arr = params.get("diagnostics")?.as_array()?;
    let mut out: Vec<Diagnostic> = arr.iter().filter_map(parse_diagnostic).collect();
    out.sort_by_key(|d| (d.start_line, d.start_character));
    Some((uri, out))
}

fn parse_diagnostic(v: &Value) -> Option<Diagnostic> {
    let range = v.get("range")?;
    let start = range.get("start")?;
    let end = range.get("end")?;
    let severity = match v.get("severity").and_then(|s| s.as_u64()) {
        Some(1) => DiagnosticSeverity::Error,
        Some(2) => DiagnosticSeverity::Warning,
        Some(3) => DiagnosticSeverity::Information,
        Some(4) => DiagnosticSeverity::Hint,
        // LSP says missing severity is client-defined; gopls always sets
        // it. Default to Error so anomalies stay visible.
        _ => DiagnosticSeverity::Error,
    };
    Some(Diagnostic {
        start_line: start.get("line")?.as_u64()? as u32,
        start_character: start.get("character")?.as_u64()? as u32,
        end_line: end.get("line")?.as_u64()? as u32,
        end_character: end.get("character")?.as_u64()? as u32,
        severity,
        message: v
            .get("message")
            .and_then(|m| m.as_str())
            .unwrap_or("")
            .to_string(),
        source: v
            .get("source")
            .and_then(|s| s.as_str())
            .map(String::from),
    })
}

/// LSP `Hover.contents` is the most overloaded field in the spec:
/// a plain string, a `{language, value}` object, a `MarkupContent` with
/// `{kind, value}`, or an array of any of the above. Flatten to a single
/// string, joining array items with a blank line.
fn parse_hover_result(v: &Value) -> Option<String> {
    if v.is_null() {
        return None;
    }
    let contents = v.get("contents")?;
    fn one(item: &Value) -> Option<String> {
        if let Some(s) = item.as_str() {
            return Some(s.to_string());
        }
        if let Some(obj) = item.as_object() {
            if let Some(s) = obj.get("value").and_then(|v| v.as_str()) {
                return Some(s.to_string());
            }
        }
        None
    }
    let text = if let Some(arr) = contents.as_array() {
        let parts: Vec<String> = arr.iter().filter_map(one).collect();
        if parts.is_empty() {
            return None;
        }
        parts.join("\n\n")
    } else {
        one(contents)?
    };
    let trimmed = text.trim();
    if trimmed.is_empty() {
        None
    } else {
        Some(trimmed.to_string())
    }
}

fn parse_definition_result(v: &Value) -> Option<DefinitionLocation> {
    let first = if v.is_array() {
        v.as_array()?.first().cloned()?
    } else if v.is_null() {
        return None;
    } else {
        v.clone()
    };
    // Either Location { uri, range } or LocationLink { targetUri, targetSelectionRange | targetRange }.
    let (uri, range) = if let Some(tu) = first.get("targetUri") {
        let r = first
            .get("targetSelectionRange")
            .or_else(|| first.get("targetRange"))?;
        (tu.as_str()?.to_string(), r.clone())
    } else {
        (
            first.get("uri")?.as_str()?.to_string(),
            first.get("range")?.clone(),
        )
    };
    let start = range.get("start")?;
    let line = start.get("line")?.as_u64()? as u32;
    let character = start.get("character")?.as_u64()? as u32;
    Some(DefinitionLocation {
        uri,
        line,
        character,
    })
}

fn write_message(w: &mut ChildStdin, msg: &Value) -> io::Result<()> {
    let body = serde_json::to_vec(msg)
        .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
    write!(w, "Content-Length: {}\r\n\r\n", body.len())?;
    w.write_all(&body)?;
    w.flush()
}

fn reader_loop(stdout: ChildStdout, tx: mpsc::Sender<Message>) {
    let mut reader = BufReader::new(stdout);
    loop {
        match read_message(&mut reader) {
            Ok(Some(msg)) => {
                if tx.send(msg).is_err() {
                    break;
                }
            }
            Ok(None) | Err(_) => break,
        }
    }
}

fn read_message(reader: &mut BufReader<ChildStdout>) -> io::Result<Option<Message>> {
    let mut content_length: Option<usize> = None;
    loop {
        let mut line = String::new();
        let n = reader.read_line(&mut line)?;
        if n == 0 {
            return Ok(None);
        }
        let trimmed = line.trim_end_matches(['\r', '\n']);
        if trimmed.is_empty() {
            break;
        }
        if let Some(v) = trimmed.strip_prefix("Content-Length: ") {
            content_length = v.parse().ok();
        }
    }
    let len = match content_length {
        Some(l) => l,
        None => return Err(io::Error::new(io::ErrorKind::InvalidData, "missing Content-Length")),
    };
    let mut body = vec![0u8; len];
    reader.read_exact(&mut body)?;
    let v: Value = serde_json::from_slice(&body)
        .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;

    let id = v.get("id").and_then(|i| i.as_u64());
    let method = v.get("method").and_then(|m| m.as_str()).map(String::from);

    match (id, method) {
        (Some(id), None) => {
            // Response
            if let Some(err) = v.get("error") {
                let code = err.get("code").and_then(|c| c.as_i64()).unwrap_or(-1);
                let message = err
                    .get("message")
                    .and_then(|m| m.as_str())
                    .unwrap_or("")
                    .to_string();
                Ok(Some(Message::Response {
                    id,
                    result: Err(LspError { code, message }),
                }))
            } else {
                let result = v.get("result").cloned().unwrap_or(Value::Null);
                Ok(Some(Message::Response {
                    id,
                    result: Ok(result),
                }))
            }
        }
        (_, Some(method)) => {
            // Notification (or server→client request, which we treat as
            // notification for now — we don't reply).
            let params = v.get("params").cloned().unwrap_or(Value::Null);
            Ok(Some(Message::Notification { method, params }))
        }
        _ => Ok(None),
    }
}

/// Convert an absolute path to a `file://` URI.
pub fn path_to_uri(path: &Path) -> io::Result<String> {
    let abs = path.canonicalize()?;
    let s = abs.to_string_lossy().into_owned();
    Ok(format!("file://{}", s))
}

/// Convert a `file://` URI to a `PathBuf`. Returns `None` if the URI
/// doesn't start with `file://`.
pub fn uri_to_path(uri: &str) -> Option<PathBuf> {
    uri.strip_prefix("file://").map(PathBuf::from)
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

    #[test]
    fn parse_hover_markup_content() {
        // What `ty server` returns.
        let v = json!({
            "contents": { "kind": "plaintext", "value": "def add(\n    a: int,\n    b: int\n) -> int" }
        });
        assert_eq!(
            parse_hover_result(&v).as_deref(),
            Some("def add(\n    a: int,\n    b: int\n) -> int")
        );
    }

    #[test]
    fn parse_hover_plain_string() {
        let v = json!({"contents": "hello"});
        assert_eq!(parse_hover_result(&v).as_deref(), Some("hello"));
    }

    #[test]
    fn parse_hover_marked_string_array() {
        let v = json!({
            "contents": [
                {"language": "go", "value": "func Add(a, b int) int"},
                "Adds two ints."
            ]
        });
        let s = parse_hover_result(&v).unwrap();
        assert!(s.contains("func Add"));
        assert!(s.contains("Adds two ints."));
    }

    #[test]
    fn parse_hover_null_or_empty() {
        assert_eq!(parse_hover_result(&json!(null)), None);
        assert_eq!(parse_hover_result(&json!({"contents": ""})), None);
        assert_eq!(parse_hover_result(&json!({})), None);
    }
}
