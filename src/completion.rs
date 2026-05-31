//! Completion trigger detection. Decides — purely from buffer bytes and
//! the cursor position — whether the user has just typed something that
//! should fire a completion request, and where the replacement range
//! should start if so. No LSP, no UI; the editor's main loop calls
//! `detect` after each insert-mode keystroke and decides what to do
//! with the result.
//!
//! Trigger rules are hardcoded per language ([`triggers_for`]) for v1:
//! - **Python**: trigger character `.`; otherwise auto-trigger when the
//!   identifier prefix at the cursor first reaches two characters.
//! - **mshell**: trigger character `@` (variable completion). The `@`
//!   itself is part of the replacement range — the server returns
//!   items that include the `@` prefix.

/// Per-language rules for when to open the completion popup.
pub struct CompletionTriggers {
    /// Characters that immediately fire a completion request as
    /// `triggerKind = TriggerCharacter`. The server's own
    /// `completionProvider.triggerCharacters` is intentionally ignored
    /// — v1 hardcodes triggers per language for predictable UX.
    pub chars: &'static [TriggerChar],
    /// If `Some(n)`, also auto-trigger on the keystroke that *first*
    /// brings the identifier prefix at the cursor to exactly `n`
    /// characters. `None` disables prefix triggering.
    pub min_identifier_prefix: Option<u8>,
}

#[derive(Clone, Copy)]
pub struct TriggerChar {
    pub ch: char,
    /// `true` if the triggering character is part of the replacement
    /// range. mshell `@var` is this way: accepting an item replaces
    /// `@xy` with `@xyz`, keeping the `@`. Python `.` is the opposite —
    /// the `.` stays, only the suffix is replaced.
    pub anchor_includes_char: bool,
}

/// What `detect` decided about the buffer state at the cursor.
pub enum TriggerDecision {
    /// Nothing actionable: cursor isn't in an identifier, isn't right
    /// after a trigger character, or is partway through an existing
    /// identifier (extension, not a fresh start).
    None,
    /// Fire a completion request.
    Trigger {
        /// LSP `position` to send: the cursor byte offset.
        position: usize,
        /// Byte offset where the replacement range begins. The popup
        /// is anchored visually here; on accept, the bytes in
        /// `[anchor..position]` are replaced with the chosen item.
        anchor: usize,
        /// `Some(ch)` when triggered by a character (sent as
        /// `context.triggerCharacter`, drives `triggerKind = 2`).
        /// `None` for the identifier-prefix trigger (`triggerKind = 1`,
        /// Invoked).
        trigger_char: Option<char>,
    },
}

/// Hardcoded language rules for v1. Returns `None` for any language
/// that hasn't been wired up; the editor then suppresses completion
/// entirely for that buffer.
pub fn triggers_for(lang_id: &str) -> Option<CompletionTriggers> {
    match lang_id {
        "python" => Some(CompletionTriggers {
            chars: &[TriggerChar {
                ch: '.',
                anchor_includes_char: false,
            }],
            min_identifier_prefix: Some(2),
        }),
        "mshell" => Some(CompletionTriggers {
            chars: &[TriggerChar {
                ch: '@',
                anchor_includes_char: true,
            }],
            min_identifier_prefix: None,
        }),
        // Markdown/djot has no LSP; completions come from words already in
        // the buffer (see [`is_buffer_source`]). Auto-trigger once the word
        // prefix at the cursor first reaches three characters.
        "djot" => Some(CompletionTriggers {
            chars: &[],
            min_identifier_prefix: Some(3),
        }),
        _ => None,
    }
}

/// Languages whose completions are served from the buffer's own words
/// rather than an LSP server. The main loop fills the popup synchronously
/// via [`buffer_word_items`] instead of sending a request.
pub fn is_buffer_source(lang_id: &str) -> bool {
    matches!(lang_id, "djot")
}

/// Largest number of buffer words to offer at once. The popup only shows a
/// handful of rows; this just bounds the gather/sort work on large files.
const MAX_BUFFER_WORDS: usize = 200;

/// Collect distinct words already present in `bytes` that begin with
/// `prefix` (case-insensitive) and are longer than it, as completion
/// items. Used for the buffer-word source (markdown). Words are runs of
/// identifier bytes; results are de-duplicated and sorted alphabetically.
pub fn buffer_word_items(bytes: &[u8], prefix: &str) -> Vec<CompletionItem> {
    if prefix.is_empty() {
        return Vec::new();
    }
    let prefix_lower = prefix.to_ascii_lowercase();
    let mut seen = std::collections::HashSet::new();
    let mut out: Vec<CompletionItem> = Vec::new();
    let mut i = 0;
    while i < bytes.len() {
        if !is_ident_byte(bytes[i]) {
            i += 1;
            continue;
        }
        let start = i;
        while i < bytes.len() && is_ident_byte(bytes[i]) {
            i += 1;
        }
        // A word worth offering is strictly longer than the prefix (so it
        // actually completes something) and shares the prefix. Skip
        // non-UTF-8 runs defensively, though identifier bytes are ASCII.
        let word = match std::str::from_utf8(&bytes[start..i]) {
            Ok(w) => w,
            Err(_) => continue,
        };
        if word.len() <= prefix.len() {
            continue;
        }
        if !word.to_ascii_lowercase().starts_with(&prefix_lower) {
            continue;
        }
        if !seen.insert(word.to_string()) {
            continue;
        }
        out.push(CompletionItem {
            label: word.to_string(),
            filter_text: word.to_string(),
            insert_text: word.to_string(),
            sort_text: word.to_string(),
            detail: None,
        });
    }
    out.sort_by(|a, b| a.sort_text.cmp(&b.sort_text).then(a.label.cmp(&b.label)));
    out.truncate(MAX_BUFFER_WORDS);
    out
}

/// Decide whether a completion should fire given the buffer bytes and
/// the cursor position. Pure: looks only at bytes and the rule table.
/// Caller is responsible for additional suppression (multi-cursor,
/// string/comment scope via tree-sitter, debounce).
pub fn detect(bytes: &[u8], cursor: usize, triggers: &CompletionTriggers) -> TriggerDecision {
    if cursor == 0 || cursor > bytes.len() {
        return TriggerDecision::None;
    }
    let last = bytes[cursor - 1];

    // Trigger characters take precedence — explicit user intent.
    for tc in triggers.chars {
        if tc.ch.is_ascii() && tc.ch as u8 == last {
            let anchor = if tc.anchor_includes_char {
                cursor - 1
            } else {
                cursor
            };
            return TriggerDecision::Trigger {
                position: cursor,
                anchor,
                trigger_char: Some(tc.ch),
            };
        }
    }

    // Identifier-prefix trigger fires at the exact moment N is reached,
    // not on subsequent keystrokes that *extend* an identifier past N.
    if let Some(n) = triggers.min_identifier_prefix {
        let n = n as usize;
        if n >= 1 && cursor >= n {
            let win_start = cursor - n;
            let all_ident = bytes[win_start..cursor].iter().all(|&b| is_ident_byte(b));
            // Boundary check: the byte just before the window must not
            // be an identifier byte. Otherwise the user is extending an
            // existing identifier and we'd re-fire on every keystroke.
            let boundary = win_start == 0 || !is_ident_byte(bytes[win_start - 1]);
            // First byte must be a valid identifier *start* — not a
            // digit (Python identifiers, like most languages, can't
            // begin with a digit).
            let starts_valid = !bytes[win_start].is_ascii_digit();
            if all_ident && boundary && starts_valid {
                return TriggerDecision::Trigger {
                    position: cursor,
                    anchor: win_start,
                    trigger_char: None,
                };
            }
        }
    }
    TriggerDecision::None
}

fn is_ident_byte(b: u8) -> bool {
    b == b'_' || b.is_ascii_alphanumeric()
}

/// Start of the identifier-byte run ending at `cursor` — the word prefix
/// under the cursor. Returns `cursor` itself when the preceding byte isn't
/// an identifier byte (no word there). Used by the manual completion
/// trigger (Ctrl-n) to anchor the replacement range at any prefix length.
pub fn ident_prefix_start(bytes: &[u8], cursor: usize) -> usize {
    let mut a = cursor.min(bytes.len());
    while a > 0 && is_ident_byte(bytes[a - 1]) {
        a -= 1;
    }
    a
}

/// A single completion candidate parsed from a server response.
#[derive(Debug, Clone)]
pub struct CompletionItem {
    /// What the user sees in the popup.
    pub label: String,
    /// What the prefix filter matches against (`filterText` when the
    /// server provides one, falling back to `label`). Always already
    /// in original casing — the filter lowercases on the fly.
    pub filter_text: String,
    /// What gets inserted on accept. Honors `textEdit.newText` first,
    /// then `insertText`, then `label`. We initialize LSP with
    /// `snippetSupport: false`, so servers should return plain text;
    /// any stray `$N` markers a misbehaving server includes will land
    /// here verbatim.
    pub insert_text: String,
    /// Server-provided ordering hint (`sortText`); falls back to
    /// `label`. Comparison is byte-lex.
    pub sort_text: String,
    /// Optional secondary text shown alongside the label.
    pub detail: Option<String>,
}

/// Parsed completion response. `items` is already sorted by
/// `(sort_text, label)`; `is_incomplete` mirrors the server flag.
pub struct CompletionResponse {
    pub items: Vec<CompletionItem>,
    pub is_incomplete: bool,
}

/// Parse a `textDocument/completion` result. The LSP spec allows three
/// shapes: `null`, a bare `CompletionItem[]`, or a `CompletionList`
/// object with `isIncomplete` + `items`. We normalize all three into
/// `CompletionResponse`.
pub fn parse_response(v: &serde_json::Value) -> CompletionResponse {
    let (mut items, is_incomplete) = if let Some(arr) = v.as_array() {
        (arr.iter().filter_map(parse_item).collect::<Vec<_>>(), false)
    } else if let Some(obj) = v.as_object() {
        let is_incomplete = obj
            .get("isIncomplete")
            .and_then(|b| b.as_bool())
            .unwrap_or(false);
        let items: Vec<CompletionItem> = obj
            .get("items")
            .and_then(|i| i.as_array())
            .map(|arr| arr.iter().filter_map(parse_item).collect())
            .unwrap_or_default();
        (items, is_incomplete)
    } else {
        (Vec::new(), false)
    };
    items.sort_by(|a, b| a.sort_text.cmp(&b.sort_text).then(a.label.cmp(&b.label)));
    CompletionResponse {
        items,
        is_incomplete,
    }
}

fn parse_item(v: &serde_json::Value) -> Option<CompletionItem> {
    let label = v.get("label")?.as_str()?.to_string();
    let filter_text = v
        .get("filterText")
        .and_then(|s| s.as_str())
        .map(String::from)
        .unwrap_or_else(|| label.clone());
    let insert_text = v
        .get("textEdit")
        .and_then(|te| te.get("newText"))
        .and_then(|s| s.as_str())
        .or_else(|| v.get("insertText").and_then(|s| s.as_str()))
        .map(String::from)
        .unwrap_or_else(|| label.clone());
    let sort_text = v
        .get("sortText")
        .and_then(|s| s.as_str())
        .map(String::from)
        .unwrap_or_else(|| label.clone());
    let detail = v
        .get("detail")
        .and_then(|s| s.as_str())
        .map(String::from);
    Some(CompletionItem {
        label,
        filter_text,
        insert_text,
        sort_text,
        detail,
    })
}

/// Case-insensitive prefix filter. Returns the indices of `items`
/// whose `filter_text` starts with `prefix`, preserving the input
/// order (which `parse_response` already sorted).
pub fn filter_items(items: &[CompletionItem], prefix: &str) -> Vec<usize> {
    if prefix.is_empty() {
        return (0..items.len()).collect();
    }
    let pl = prefix.to_lowercase();
    items
        .iter()
        .enumerate()
        .filter_map(|(i, it)| {
            if it.filter_text.to_lowercase().starts_with(&pl) {
                Some(i)
            } else {
                None
            }
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    fn py() -> CompletionTriggers {
        triggers_for("python").unwrap()
    }
    fn msh() -> CompletionTriggers {
        triggers_for("mshell").unwrap()
    }

    fn parts(d: &TriggerDecision) -> Option<(usize, usize, Option<char>)> {
        match d {
            TriggerDecision::Trigger { position, anchor, trigger_char } => {
                Some((*position, *anchor, *trigger_char))
            }
            _ => None,
        }
    }

    #[test]
    fn python_dot_anchors_after_dot() {
        let d = detect(b"foo.", 4, &py());
        assert_eq!(parts(&d), Some((4, 4, Some('.'))));
    }

    #[test]
    fn python_prefix_fires_at_exactly_n_chars() {
        // 1 char: no trigger.
        assert!(matches!(detect(b"f", 1, &py()), TriggerDecision::None));
        // 2 chars: trigger with anchor at start of identifier.
        assert_eq!(parts(&detect(b"fo", 2, &py())), Some((2, 0, None)));
        // 3 chars: extending, no re-trigger.
        assert!(matches!(detect(b"foo", 3, &py()), TriggerDecision::None));
    }

    #[test]
    fn python_prefix_only_at_identifier_boundary() {
        // Cursor in the middle of a long identifier: window is "ng",
        // but the byte before is 'lo' → not a boundary, no trigger.
        let d = detect(b"longname", 5, &py());
        assert!(matches!(d, TriggerDecision::None));
    }

    #[test]
    fn python_prefix_does_not_fire_on_digit_start() {
        // "12" looks like two identifier bytes but tokens can't start
        // with a digit.
        let d = detect(b"12", 2, &py());
        assert!(matches!(d, TriggerDecision::None));
    }

    #[test]
    fn python_prefix_fires_after_non_identifier() {
        // After a space, the next two identifier chars trigger.
        let d = detect(b"a fo", 4, &py());
        assert_eq!(parts(&d), Some((4, 2, None)));
    }

    #[test]
    fn mshell_at_anchors_at_at_sign() {
        let d = detect(b"echo @", 6, &msh());
        // `@` is part of the replacement — anchor sits at it.
        assert_eq!(parts(&d), Some((6, 5, Some('@'))));
    }

    #[test]
    fn mshell_no_prefix_trigger() {
        // mshell only triggers on `@`, never on bare identifier
        // chars.
        assert!(matches!(detect(b"foo", 3, &msh()), TriggerDecision::None));
    }

    #[test]
    fn unknown_language_returns_none_from_triggers_for() {
        assert!(triggers_for("rust").is_none());
    }

    #[test]
    fn empty_bytes_yield_no_trigger() {
        assert!(matches!(detect(b"", 0, &py()), TriggerDecision::None));
    }

    #[test]
    fn parse_array_form_has_no_incomplete_flag() {
        let v = serde_json::json!([
            { "label": "alpha" },
            { "label": "beta" }
        ]);
        let r = parse_response(&v);
        assert_eq!(r.items.len(), 2);
        assert!(!r.is_incomplete);
    }

    #[test]
    fn parse_object_form_reads_is_incomplete() {
        let v = serde_json::json!({
            "isIncomplete": true,
            "items": [ { "label": "x" } ]
        });
        let r = parse_response(&v);
        assert_eq!(r.items.len(), 1);
        assert!(r.is_incomplete);
    }

    #[test]
    fn parse_uses_text_edit_new_text() {
        let v = serde_json::json!([{
            "label": "foo",
            "textEdit": {
                "range": { "start": { "line": 0, "character": 0 }, "end": { "line": 0, "character": 0 } },
                "newText": "foo_te"
            },
            "insertText": "foo_it"
        }]);
        let r = parse_response(&v);
        assert_eq!(r.items[0].insert_text, "foo_te");
    }

    #[test]
    fn parse_falls_back_to_insert_text_then_label() {
        let v = serde_json::json!([
            { "label": "a", "insertText": "a_it" },
            { "label": "b" }
        ]);
        let r = parse_response(&v);
        assert_eq!(r.items[0].insert_text, "a_it");
        assert_eq!(r.items[1].insert_text, "b");
    }

    #[test]
    fn parse_null_yields_empty() {
        let r = parse_response(&serde_json::Value::Null);
        assert!(r.items.is_empty());
        assert!(!r.is_incomplete);
    }

    #[test]
    fn parse_sorts_by_sort_text() {
        let v = serde_json::json!([
            { "label": "zeta", "sortText": "1" },
            { "label": "alpha", "sortText": "0" }
        ]);
        let r = parse_response(&v);
        assert_eq!(r.items[0].label, "alpha");
        assert_eq!(r.items[1].label, "zeta");
    }

    #[test]
    fn filter_case_insensitive_prefix_matches() {
        let items = vec![
            CompletionItem {
                label: "Foo".into(),
                filter_text: "Foo".into(),
                insert_text: "Foo".into(),
                sort_text: "Foo".into(),
                detail: None,
            },
            CompletionItem {
                label: "bar".into(),
                filter_text: "bar".into(),
                insert_text: "bar".into(),
                sort_text: "bar".into(),
                detail: None,
            },
        ];
        let idxs = filter_items(&items, "fo");
        assert_eq!(idxs, vec![0]);
        // Empty prefix returns everything.
        let idxs = filter_items(&items, "");
        assert_eq!(idxs, vec![0, 1]);
    }

    #[test]
    fn filter_uses_filter_text_over_label() {
        let items = vec![CompletionItem {
            label: "display only".into(),
            filter_text: "match_me".into(),
            insert_text: "x".into(),
            sort_text: "x".into(),
            detail: None,
        }];
        // Matches via filter_text, not label.
        assert_eq!(filter_items(&items, "match"), vec![0]);
        // Doesn't match the label.
        assert!(filter_items(&items, "display").is_empty());
    }

    #[test]
    fn djot_prefix_triggers_at_three_chars() {
        let dj = triggers_for("djot").unwrap();
        assert!(dj.chars.is_empty());
        // 2 chars: no trigger.
        assert!(matches!(detect(b"th", 2, &dj), TriggerDecision::None));
        // 3 chars: fires, anchored at the word start.
        assert_eq!(parts(&detect(b"the", 3, &dj)), Some((3, 0, None)));
        // 4 chars: extending an existing word, no re-trigger.
        assert!(matches!(detect(b"theo", 4, &dj), TriggerDecision::None));
    }

    #[test]
    fn djot_is_buffer_source() {
        assert!(is_buffer_source("djot"));
        assert!(!is_buffer_source("python"));
    }

    #[test]
    fn buffer_words_collects_longer_distinct_matches() {
        let text = b"completion completes complete\ncompletion again";
        let items = buffer_word_items(text, "com");
        let labels: Vec<&str> = items.iter().map(|i| i.label.as_str()).collect();
        // Distinct, sorted, each longer than the prefix; "completion"
        // appears twice but is de-duplicated.
        assert_eq!(labels, vec!["complete", "completes", "completion"]);
    }

    #[test]
    fn buffer_words_is_case_insensitive_but_keeps_original_case() {
        let items = buffer_word_items(b"Markdown markup", "mar");
        let labels: Vec<&str> = items.iter().map(|i| i.label.as_str()).collect();
        assert_eq!(labels, vec!["Markdown", "markup"]);
    }

    #[test]
    fn buffer_words_excludes_the_prefix_itself() {
        // A word equal to the prefix is no completion at all.
        let items = buffer_word_items(b"the the the", "the");
        assert!(items.is_empty());
    }
}
