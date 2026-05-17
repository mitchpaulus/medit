//! Walks `tests/golden/*.json` and runs each scenario against the medit core.
//! See `tests/golden/README.md` for the file format.

use std::path::Path;

use medit::buffer::Buffer;
use medit::core::{
    LspAction, Mode, ObjectKind, Registers, SearchState, Selection, Selections, collect_bytes,
    handle_ex, handle_insert, handle_normal, handle_search,
};
use medit::input::{Event, Parser};

#[test]
fn golden() {
    let dir = Path::new(env!("CARGO_MANIFEST_DIR")).join("tests/golden");
    let entries: Vec<_> = std::fs::read_dir(&dir)
        .expect("tests/golden dir")
        .filter_map(|e| e.ok())
        .map(|e| e.path())
        .filter(|p| p.extension().and_then(|s| s.to_str()) == Some("json"))
        .collect();
    let mut entries = entries;
    entries.sort();

    let mut failures = Vec::new();
    let mut passed = 0;
    for path in &entries {
        match run_test_file(path) {
            Ok(()) => passed += 1,
            Err(e) => failures.push(format!("--- FAIL: {}\n{}", path.display(), e)),
        }
    }
    if !failures.is_empty() {
        panic!(
            "\n{} of {} golden tests failed:\n\n{}\n",
            failures.len(),
            entries.len(),
            failures.join("\n\n")
        );
    }
    eprintln!("golden: {} passed", passed);
}

fn run_test_file(path: &Path) -> Result<(), String> {
    let raw = std::fs::read_to_string(path).map_err(|e| format!("read: {}", e))?;
    let v: serde_json::Value =
        serde_json::from_str(&raw).map_err(|e| format!("json parse: {}", e))?;

    let name = field_str(&v, "name")?;
    let initial = field_str(&v, "initial")?;
    let keys = field_str(&v, "keys")?;
    let expected = field_str(&v, "expected")?;
    let mode_str = optional_field_str(&v, "mode").unwrap_or_else(|| "normal".into());
    let expected_mode_str = optional_field_str(&v, "expected_mode");

    let (initial_bytes, initial_sel) = parse_text(&initial)
        .map_err(|e| format!("[{}] initial: {}", name, e))?;
    let mut buffer = Buffer::from_bytes(initial_bytes);
    let mut sels = Selections::new();
    *sels.primary_mut() = initial_sel;
    let mut mode = parse_mode(&mode_str)
        .map_err(|e| format!("[{}] {}", name, e))?;
    let mut registers = Registers::default();
    let mut ex_input = String::new();
    let mut ex_message = String::new();
    let mut pending_j = false;
    let mut pending_g = false;
    let mut pending_z = false;
    let mut pending_object: Option<ObjectKind> = None;
    let mut pending_lsp_action: Option<LspAction> = None;
    let mut top_line: usize = 0;
    let mut search_input = String::new();
    let mut search_state = SearchState::default();

    let mut parser = Parser::new();
    parser.feed(keys.as_bytes());
    loop {
        let event = match parser.next_event() {
            Some(e) => e,
            None => match parser.flush() {
                Some(e) => e,
                None => break,
            },
        };
        let Event::Key(k) = event;
        match mode {
            Mode::Normal => {
                let _quit = handle_normal(
                    &mut buffer,
                    &mut sels,
                    &mut mode,
                    &mut registers,
                    &mut pending_g,
                    &mut pending_z,
                    &mut pending_object,
                    &mut search_state,
                    &mut pending_lsp_action,
                    &mut top_line,
                    24,
                    k,
                );
                // LSP actions are not dispatched in tests (no server).
                pending_lsp_action = None;
            }
            Mode::Insert => {
                handle_insert(
                    &mut buffer,
                    &mut sels,
                    &mut mode,
                    &mut pending_j,
                    &mut registers,
                    k,
                );
            }
            Mode::Ex => {
                let _quit = handle_ex(
                    &buffer,
                    &mut mode,
                    &mut ex_input,
                    &mut ex_message,
                    None,
                    k,
                );
            }
            Mode::Search => {
                handle_search(
                    &buffer,
                    &mut sels,
                    &mut mode,
                    &mut search_input,
                    &mut search_state,
                    &mut ex_message,
                    k,
                );
            }
        }
    }

    let bytes = collect_bytes(&buffer);
    let actual = serialize_text(&bytes, sels.primary());
    if actual != expected {
        return Err(format!(
            "[{}] buffer mismatch:\n  expected: {:?}\n  actual:   {:?}",
            name, expected, actual
        ));
    }
    if let Some(em) = expected_mode_str {
        let expected_mode = parse_mode(&em)
            .map_err(|e| format!("[{}] expected_mode: {}", name, e))?;
        if mode != expected_mode {
            return Err(format!(
                "[{}] mode mismatch:\n  expected: {:?}\n  actual:   {:?}",
                name, expected_mode, mode
            ));
        }
    }
    Ok(())
}

fn field_str(v: &serde_json::Value, key: &str) -> Result<String, String> {
    v.get(key)
        .and_then(|x| x.as_str())
        .map(|s| s.to_string())
        .ok_or_else(|| format!("missing or non-string field: {}", key))
}

fn optional_field_str(v: &serde_json::Value, key: &str) -> Option<String> {
    v.get(key).and_then(|x| x.as_str()).map(|s| s.to_string())
}

fn parse_mode(s: &str) -> Result<Mode, String> {
    match s {
        "normal" => Ok(Mode::Normal),
        "insert" => Ok(Mode::Insert),
        "ex" => Ok(Mode::Ex),
        "search" => Ok(Mode::Search),
        _ => Err(format!("unknown mode: {:?}", s)),
    }
}

/// Walk back from `end` (an exclusive byte position) to the start of the last
/// character before it.
fn last_char_start_before(bytes: &[u8], end: usize) -> usize {
    if end == 0 {
        return 0;
    }
    let mut p = end - 1;
    while p > 0 {
        match bytes.get(p) {
            Some(&b) if b & 0xC0 == 0x80 => p -= 1,
            _ => break,
        }
    }
    p
}

/// Parse a buffer-with-markers string into (bytes, selection).
fn parse_text(text: &str) -> Result<(Vec<u8>, Selection), String> {
    let mut bytes = Vec::new();
    let mut first: Option<(char, usize)> = None;
    let mut second: Option<(char, usize)> = None;

    for c in text.chars() {
        if c == '<' || c == '>' {
            if first.is_none() {
                first = Some((c, bytes.len()));
            } else if second.is_none() {
                second = Some((c, bytes.len()));
            } else {
                return Err("more than two selection markers".into());
            }
        } else {
            let mut buf = [0u8; 4];
            let s = c.encode_utf8(&mut buf);
            bytes.extend_from_slice(s.as_bytes());
        }
    }

    let sel = match (first, second) {
        (None, _) => Selection::new(),
        (Some(_), None) => {
            return Err("only one selection marker found; need a matching pair".into());
        }
        (Some((c1, p1)), Some((c2, p2))) => {
            match (c1, c2) {
                ('<', '>') => {
                    let head = if p2 > p1 {
                        last_char_start_before(&bytes, p2)
                    } else {
                        p1
                    };
                    Selection {
                        anchor: p1,
                        head,
                        desired_col: 1,
                    }
                }
                ('>', '<') => {
                    let anchor = if p2 > p1 {
                        last_char_start_before(&bytes, p2)
                    } else {
                        p1
                    };
                    Selection {
                        anchor,
                        head: p1,
                        desired_col: 1,
                    }
                }
                _ => return Err(format!("mismatched markers '{}' ... '{}'", c1, c2)),
            }
        }
    };
    Ok((bytes, sel))
}

/// Serialize (bytes, selection) back to a buffer-with-markers string.
fn serialize_text(bytes: &[u8], sel: &Selection) -> String {
    if bytes.is_empty() {
        return String::new();
    }
    let min = sel.min();
    let max = sel.max();
    let last = medit::core::next_char_or_end(bytes, max);

    let head_is_right = sel.head >= sel.anchor;
    let (left, right) = if head_is_right { ("<", ">") } else { (">", "<") };

    let mut s = String::new();
    s.push_str(std::str::from_utf8(&bytes[..min]).unwrap_or("?"));
    s.push_str(left);
    s.push_str(std::str::from_utf8(&bytes[min..last]).unwrap_or("?"));
    s.push_str(right);
    s.push_str(std::str::from_utf8(&bytes[last..]).unwrap_or("?"));
    s
}
