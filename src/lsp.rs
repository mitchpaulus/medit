//! LSP client. JSON-RPC 2.0 over stdio with a per-server reader thread
//! that forwards parsed messages onto the editor's unified event channel.
//! Hover, goto-definition, completion and diagnostics flow back through
//! `LspEvent`s emitted from `handle_message`, which the main loop calls
//! once per forwarded `Message`.
//!
//! Threading model:
//! - The spawned server reads from its stdin and writes to its stdout.
//! - One reader thread per server parses `Content-Length`-framed messages
//!   off the child's stdout and invokes the editor-supplied callback. The
//!   editor's callback funnels each message into its main event loop.
//! - The main thread owns the `LspClient` and the child stdin. Requests
//!   are non-blocking writes; responses come back via the callback and
//!   are resolved against an internal `pending` table that maps response
//!   ids to the request kind that originated them.
//! - The `initialize` handshake is the lone synchronous call: it happens
//!   inline in `spawn` before the reader thread is started, so there is
//!   no race between init-response delivery and the event-stream startup.

use std::collections::HashMap;
use std::io::{self, BufRead, BufReader, Read, Write};
use std::path::{Path, PathBuf};
use std::process::{Child, ChildStdin, ChildStdout, Command, Stdio};
use std::thread;

use serde_json::{Value, json};

/// A raw response or notification received from the LSP server. Emitted
/// by the reader thread; consumed by `LspClient::handle_message`.
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

/// Editor-facing event produced when the client correlates a server
/// message with a pending request (or processes a notification). The
/// main loop matches on these and updates UI/buffer state.
pub enum LspEvent {
    Hover {
        id: u64,
        result: Result<Option<String>, LspError>,
    },
    Definition {
        id: u64,
        result: Result<Option<DefinitionLocation>, LspError>,
    },
    /// Completion responses carry the raw `result` payload. Parsing into
    /// items is done by the completion module so it can read the exact
    /// fields it needs (textEdit, insertText, isIncomplete, ...).
    Completion {
        id: u64,
        result: Result<Value, LspError>,
    },
    DiagnosticsUpdated {
        uri: String,
    },
}

#[derive(Clone, Copy)]
enum PendingKind {
    Hover,
    Definition,
    Completion,
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

/// Result of `textDocument/definition`. Always reduced to a single
/// location — if the server returned an array, we pick the first.
#[derive(Debug, Clone)]
pub struct DefinitionLocation {
    pub uri: String,
    pub line: u32,
    pub character: u32,
}

/// Why a `textDocument/completion` request is being sent. Maps onto
/// the LSP `CompletionTriggerKind` enum (1/2/3).
#[derive(Debug, Clone, Copy)]
pub enum CompletionTrigger {
    /// Manually invoked (no trigger character). `triggerKind: 1`.
    Invoked,
    /// Triggered by typing one of the server-declared (or our
    /// language-specific) trigger characters. `triggerKind: 2`.
    Character(char),
    /// Re-requesting because the previous response for this session
    /// had `isIncomplete: true` and the user has typed more
    /// characters. `triggerKind: 3`.
    Incomplete,
}

pub struct LspClient {
    child: Child,
    stdin: ChildStdin,
    next_id: u64,
    /// Latest published diagnostics per document URI. Replaced wholesale
    /// every time the server sends `textDocument/publishDiagnostics` for
    /// that URI (LSP semantics: an empty array clears).
    diagnostics: HashMap<String, Vec<Diagnostic>>,
    /// Outstanding request ids → which kind of response we expect. Lets
    /// `handle_message` translate raw responses into typed `LspEvent`s.
    pending: HashMap<u64, PendingKind>,
    /// Trigger characters reported by the server in its `initialize`
    /// response under `capabilities.completionProvider.triggerCharacters`.
    completion_trigger_chars: Vec<char>,
}

impl LspClient {
    /// Spawn `program` with `args` and complete the LSP
    /// `initialize`/`initialized` handshake. The reader thread is started
    /// *after* the handshake so the init response can be consumed
    /// synchronously from the same buffered stdout reader the thread will
    /// then own.
    ///
    /// `on_message` is invoked from the reader thread for every parsed
    /// server message after init. The caller is expected to funnel those
    /// messages back to the main loop (e.g. via an mpsc) and call
    /// `handle_message` on this client to drive state updates.
    pub fn spawn<F>(
        program: &str,
        args: &[&str],
        root_uri: &str,
        on_message: F,
    ) -> io::Result<Self>
    where
        F: Fn(Message) + Send + 'static,
    {
        let mut child = Command::new(program)
            .args(args)
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .stderr(Stdio::null())
            .spawn()?;
        let mut stdin = child
            .stdin
            .take()
            .ok_or_else(|| io::Error::new(io::ErrorKind::Other, "no child stdin"))?;
        let stdout = child
            .stdout
            .take()
            .ok_or_else(|| io::Error::new(io::ErrorKind::Other, "no child stdout"))?;
        let mut reader = BufReader::new(stdout);

        let init_id: u64 = 1;
        let init_params = json!({
            "processId": std::process::id(),
            "rootUri": root_uri,
            "workspaceFolders": [{ "uri": root_uri, "name": "workspace" }],
            "capabilities": {
                "general": { "positionEncodings": ["utf-8"] },
                "textDocument": {
                    "definition": { "linkSupport": true },
                    "synchronization": { "didSave": false },
                    "publishDiagnostics": { "relatedInformation": false },
                    "completion": {
                        "completionItem": { "snippetSupport": false }
                    }
                }
            },
            "clientInfo": { "name": "medit", "version": "0.1.0" }
        });
        write_message(
            &mut stdin,
            &json!({
                "jsonrpc": "2.0",
                "id": init_id,
                "method": "initialize",
                "params": init_params,
            }),
        )?;
        // Drive the init response inline. Notifications received during
        // the handshake (rare; nothing has been opened yet) are discarded.
        // No timeout: a server that never responds to initialize is fatal
        // and the parent process will be killed on Drop anyway.
        let init_result = loop {
            match read_message(&mut reader)? {
                Some(Message::Response { id, result }) if id == init_id => match result {
                    Ok(v) => break v,
                    Err(e) => {
                        return Err(io::Error::new(
                            io::ErrorKind::Other,
                            format!("LSP init error: {}", e.message),
                        ));
                    }
                },
                Some(_) => continue,
                None => {
                    return Err(io::Error::new(
                        io::ErrorKind::BrokenPipe,
                        "LSP closed during init",
                    ));
                }
            }
        };
        let completion_trigger_chars = parse_completion_trigger_chars(&init_result);
        write_message(
            &mut stdin,
            &json!({
                "jsonrpc": "2.0",
                "method": "initialized",
                "params": {},
            }),
        )?;

        thread::spawn(move || reader_loop(reader, on_message));

        Ok(LspClient {
            child,
            stdin,
            next_id: init_id + 1,
            diagnostics: HashMap::new(),
            pending: HashMap::new(),
            completion_trigger_chars,
        })
    }

    fn write_request(&mut self, method: &str, params: Value) -> io::Result<u64> {
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

    /// Process a server message forwarded from the reader thread. Returns
    /// zero or more editor-facing events: a matched response produces
    /// exactly one event, a `publishDiagnostics` notification produces one
    /// event after updating the internal diagnostics cache, and any other
    /// notification (or an unmatched response) is dropped.
    pub fn handle_message(&mut self, msg: Message) -> Vec<LspEvent> {
        let mut events = Vec::new();
        match msg {
            Message::Notification { method, params } => {
                if method == "textDocument/publishDiagnostics" {
                    if let Some((uri, diags)) = parse_publish_diagnostics(&params) {
                        self.diagnostics.insert(uri.clone(), diags);
                        events.push(LspEvent::DiagnosticsUpdated { uri });
                    }
                }
            }
            Message::Response { id, result } => {
                if let Some(kind) = self.pending.remove(&id) {
                    let ev = match kind {
                        PendingKind::Hover => LspEvent::Hover {
                            id,
                            result: result.map(|v| parse_hover_result(&v)),
                        },
                        PendingKind::Definition => LspEvent::Definition {
                            id,
                            result: result.map(|v| parse_definition_result(&v)),
                        },
                        PendingKind::Completion => LspEvent::Completion { id, result },
                    };
                    events.push(ev);
                }
            }
        }
        events
    }

    /// Latest diagnostics published for `uri`, sorted by start position.
    pub fn diagnostics_for(&self, uri: &str) -> &[Diagnostic] {
        self.diagnostics
            .get(uri)
            .map(|v| v.as_slice())
            .unwrap_or(&[])
    }

    /// Send `textDocument/didChange` with full-text sync. Simple and
    /// fast — re-runs the diagnostics pass against the new text.
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

    /// Fire `textDocument/definition`. Returns the request id; the
    /// response arrives later as `LspEvent::Definition` via
    /// `handle_message`.
    pub fn definition_async(
        &mut self,
        uri: &str,
        line: u32,
        character: u32,
    ) -> io::Result<u64> {
        let id = self.write_request(
            "textDocument/definition",
            json!({
                "textDocument": { "uri": uri },
                "position": { "line": line, "character": character },
            }),
        )?;
        self.pending.insert(id, PendingKind::Definition);
        Ok(id)
    }

    /// Fire `textDocument/hover`. Returns the request id; the response
    /// arrives later as `LspEvent::Hover` via `handle_message`.
    pub fn hover_async(&mut self, uri: &str, line: u32, character: u32) -> io::Result<u64> {
        let id = self.write_request(
            "textDocument/hover",
            json!({
                "textDocument": { "uri": uri },
                "position": { "line": line, "character": character },
            }),
        )?;
        self.pending.insert(id, PendingKind::Hover);
        Ok(id)
    }

    /// Fire `textDocument/completion`. The `trigger` argument is sent
    /// as the LSP `context` and chooses one of the three
    /// `CompletionTriggerKind` values.
    pub fn completion_async(
        &mut self,
        uri: &str,
        line: u32,
        character: u32,
        trigger: CompletionTrigger,
    ) -> io::Result<u64> {
        let context = match trigger {
            CompletionTrigger::Character(ch) => json!({
                "triggerKind": 2,
                "triggerCharacter": ch.to_string(),
            }),
            CompletionTrigger::Invoked => json!({ "triggerKind": 1 }),
            // TriggerForIncompleteCompletions: the previous result for
            // this session came back with `isIncomplete: true` and the
            // user has typed more characters since.
            CompletionTrigger::Incomplete => json!({ "triggerKind": 3 }),
        };
        let id = self.write_request(
            "textDocument/completion",
            json!({
                "textDocument": { "uri": uri },
                "position": { "line": line, "character": character },
                "context": context,
            }),
        )?;
        self.pending.insert(id, PendingKind::Completion);
        Ok(id)
    }

    /// True while at least one request is awaiting a response. Drives the
    /// status-line spinner.
    pub fn has_outstanding(&self) -> bool {
        !self.pending.is_empty()
    }

    pub fn completion_trigger_chars(&self) -> &[char] {
        &self.completion_trigger_chars
    }

    pub fn shutdown(&mut self) {
        let _ = self.write_request("shutdown", Value::Null);
        let _ = self.notify("exit", Value::Null);
        let _ = self.child.wait();
    }
}

impl Drop for LspClient {
    fn drop(&mut self) {
        // Best-effort shutdown so child doesn't outlive the editor.
        let _ = self.write_request("shutdown", Value::Null);
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

fn parse_completion_trigger_chars(init_response: &Value) -> Vec<char> {
    init_response
        .get("capabilities")
        .and_then(|c| c.get("completionProvider"))
        .and_then(|cp| cp.get("triggerCharacters"))
        .and_then(|tc| tc.as_array())
        .map(|arr| {
            arr.iter()
                .filter_map(|v| v.as_str())
                .filter_map(|s| s.chars().next())
                .collect()
        })
        .unwrap_or_default()
}

fn write_message(w: &mut ChildStdin, msg: &Value) -> io::Result<()> {
    let body = serde_json::to_vec(msg)
        .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
    write!(w, "Content-Length: {}\r\n\r\n", body.len())?;
    w.write_all(&body)?;
    w.flush()
}

fn reader_loop<F: Fn(Message)>(mut reader: BufReader<ChildStdout>, on_message: F) {
    loop {
        match read_message(&mut reader) {
            Ok(Some(msg)) => on_message(msg),
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

    #[test]
    fn parse_trigger_chars_basic() {
        let v = json!({
            "capabilities": {
                "completionProvider": {
                    "triggerCharacters": [".", ":"]
                }
            }
        });
        assert_eq!(parse_completion_trigger_chars(&v), vec!['.', ':']);
    }

    #[test]
    fn parse_trigger_chars_missing() {
        let v = json!({ "capabilities": {} });
        assert!(parse_completion_trigger_chars(&v).is_empty());
    }
}
