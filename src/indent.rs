//! Smart indentation. Computes the indent prefix for a new line by
//! counting unbalanced opener brackets before the cursor position.
//!
//! Tree-sitter trees would in theory give us nicer answers (knowing strings
//! and comments so brackets inside them don't count), but the moment the
//! user has typed an opener without a closer the parse is an `(ERROR)` node
//! and the container queries don't match — which is exactly when smart
//! indent matters most. So we work at the byte level using a hardcoded
//! per-language bracket set; if we later want to mask out strings/comments
//! we can consult the tree opportunistically.
//!
//! Public surface:
//! - `Indenter::new()`: registers known languages.
//! - `Indenter::indent_for(lang_id, _tree, bytes, byte_pos)`: indent prefix.

use std::collections::HashMap;

/// Width of one indent level, in spaces.
pub const INDENT_WIDTH: usize = 4;

/// Per-language bracket sets. Multi-char openers/closers (like mshell's
/// `[|` / `|]`) are matched before the single-char ones so the longest
/// token wins.
struct LangBrackets {
    multi_open: &'static [&'static [u8]],
    multi_close: &'static [&'static [u8]],
    open: &'static [u8],
    close: &'static [u8],
}

pub struct Indenter {
    langs: HashMap<&'static str, LangBrackets>,
}

impl Indenter {
    pub fn new() -> Self {
        let mut langs = HashMap::new();
        langs.insert(
            "mshell",
            LangBrackets {
                multi_open: &[b"[|"],
                multi_close: &[b"|]"],
                open: b"[({",
                close: b"])}",
            },
        );
        Self { langs }
    }

    /// Indent level for a new line whose insertion point is at `byte_pos`:
    /// the count of unbalanced openers in `bytes[..byte_pos]`. Returns 0
    /// when no language is registered.
    pub fn level_for(&self, lang_id: &str, bytes: &[u8], byte_pos: usize) -> usize {
        let b = match self.langs.get(lang_id) {
            Some(b) => b,
            None => return 0,
        };
        let n = byte_pos.min(bytes.len());
        let mut depth: i32 = 0;
        let mut i = 0;
        'outer: while i < n {
            for tok in b.multi_open {
                if bytes[i..].starts_with(tok) && i + tok.len() <= n {
                    depth += 1;
                    i += tok.len();
                    continue 'outer;
                }
            }
            for tok in b.multi_close {
                if bytes[i..].starts_with(tok) && i + tok.len() <= n {
                    depth -= 1;
                    i += tok.len();
                    continue 'outer;
                }
            }
            let c = bytes[i];
            if b.open.contains(&c) {
                depth += 1;
            } else if b.close.contains(&c) {
                depth -= 1;
            }
            i += 1;
        }
        depth.max(0) as usize
    }

    /// Convenience wrapper returning the actual indent string (spaces).
    pub fn indent_for(&self, lang_id: &str, bytes: &[u8], byte_pos: usize) -> String {
        let level = self.level_for(lang_id, bytes, byte_pos);
        " ".repeat(level * INDENT_WIDTH)
    }
}

impl Default for Indenter {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn level_inside_list_is_one() {
        let i = Indenter::new();
        assert_eq!(i.level_for("mshell", b"[\n", 2), 1);
    }

    #[test]
    fn level_after_closed_list_is_zero() {
        let i = Indenter::new();
        assert_eq!(i.level_for("mshell", b"[\n1\n]\n", 6), 0);
    }

    #[test]
    fn level_nested_unclosed_lists() {
        let i = Indenter::new();
        assert_eq!(i.level_for("mshell", b"[\n[\n", 4), 2);
    }

    #[test]
    fn level_inside_quotation_two_char_token() {
        let i = Indenter::new();
        assert_eq!(i.level_for("mshell", b"[|\n", 3), 1);
    }

    #[test]
    fn level_quotation_close_dedents() {
        let i = Indenter::new();
        assert_eq!(i.level_for("mshell", b"[|\n1\n|]\n", 8), 0);
    }

    #[test]
    fn unknown_lang_returns_zero() {
        let i = Indenter::new();
        assert_eq!(i.level_for("go", b"[\n", 2), 0);
    }

    #[test]
    fn indent_for_returns_spaces() {
        let i = Indenter::new();
        assert_eq!(i.indent_for("mshell", b"[\n", 2), "    ");
    }
}
