//! Syntax highlighting via tree-sitter. Each supported language ships a
//! vendored grammar (under `grammars/<lang>/`) compiled by `build.rs`,
//! a `highlights.scm` query that maps tree nodes to capture names, and
//! a mapping from those capture names to ANSI fg colors via `theme.rs`.
//!
//! Public surface:
//! - `Highlighter`: holds all known languages' Parser + Query.
//! - `HighlightSpan`: a (byte range, scope) the renderer can consume.
//! - `Highlighter::language_for_path(path)`: pick a language by file
//!   extension. Returns `None` for unknown files (plain rendering).

use std::collections::HashMap;

use tree_sitter::{Language, Parser, Query, QueryCursor, StreamingIterator, Tree};

use crate::theme::{self, ScopeId};

/// A highlighted byte range. Spans are produced by the query engine,
/// sorted by `start`, and may overlap; `flatten_to_byte_scopes` resolves
/// overlaps into a dense per-byte array suitable for fast lookup at
/// render time.
#[derive(Debug, Clone, Copy)]
pub struct HighlightSpan {
    pub start: usize,
    pub end: usize,
    pub scope: ScopeId,
}

/// Flatten a list of (possibly overlapping) spans into a dense per-byte
/// scope array of length `len`. Later spans (deeper/more-specific
/// captures, since spans are sorted (start, Reverse(end))) overwrite
/// earlier ones — this approximates tree-sitter's "innermost wins" rule.
pub fn flatten_to_byte_scopes(spans: &[HighlightSpan], len: usize) -> Vec<ScopeId> {
    let mut out = vec![ScopeId::Default; len];
    for span in spans {
        let end = span.end.min(len);
        for cell in out.iter_mut().take(end).skip(span.start) {
            *cell = span.scope;
        }
    }
    out
}

/// Per-language data: the parser language and a compiled highlight query.
struct LangSupport {
    language: Language,
    query: Query,
    /// Capture index → scope. Index into `query.capture_names()`.
    capture_scopes: Vec<ScopeId>,
}

pub struct Highlighter {
    langs: HashMap<&'static str, LangSupport>,
}

impl Highlighter {
    pub fn new() -> Self {
        let mut h = Self {
            langs: HashMap::new(),
        };
        h.register("go", unsafe { tree_sitter_go() }, include_str!("../grammars/go/queries/highlights.scm"));
        h.register("mshell", unsafe { tree_sitter_mshell() }, include_str!("../grammars/mshell/queries/highlights.scm"));
        // Djot doubles as the markdown grammar for now — close enough that
        // reading other-people's markdown stays useful. Split if it starts
        // mis-parsing common constructs.
        h.register("djot", unsafe { tree_sitter_djot() }, include_str!("../grammars/djot/queries/highlights.scm"));
        h
    }

    fn register(&mut self, name: &'static str, language: Language, highlights: &str) {
        let query = match Query::new(&language, highlights) {
            Ok(q) => q,
            Err(e) => {
                eprintln!("highlight: failed to compile {} query: {}", name, e);
                return;
            }
        };
        let capture_scopes: Vec<ScopeId> = query
            .capture_names()
            .iter()
            .map(|n| theme::scope_for_capture(n))
            .collect();
        self.langs.insert(
            name,
            LangSupport {
                language,
                query,
                capture_scopes,
            },
        );
    }

    /// Map a file extension to a registered language id.
    pub fn language_for_path(path: &std::path::Path) -> Option<&'static str> {
        let ext = path.extension()?.to_str()?;
        Some(match ext {
            "go" => "go",
            "msh" | "mshell" => "mshell",
            "dj" | "djot" | "md" | "markdown" => "djot",
            _ => return None,
        })
    }

    /// Map a file's shebang line to a registered language id.
    /// Handles `#!/path/to/interp` and `#!/path/to/env [flags] interp`
    /// (where `env` skips `-flag` args and `VAR=VALUE` assignments).
    pub fn language_for_shebang(content: &[u8]) -> Option<&'static str> {
        let line = content.split(|&b| b == b'\n').next()?;
        let rest = line.strip_prefix(b"#!")?;
        let s = std::str::from_utf8(rest).ok()?;
        let mut parts = s.split_whitespace();
        let prog = parts.next()?;
        let basename = prog.rsplit('/').next().unwrap_or(prog);
        let interp = if basename == "env" {
            parts.find(|p| !p.starts_with('-') && !p.contains('='))?
        } else {
            basename
        };
        Some(match interp {
            "msh" | "mshell" => "mshell",
            _ => return None,
        })
    }

    /// Build a parser configured for `lang_id`. Returns `None` if the
    /// language isn't registered.
    pub fn parser_for(&self, lang_id: &str) -> Option<Parser> {
        let support = self.langs.get(lang_id)?;
        let mut parser = Parser::new();
        if parser.set_language(&support.language).is_err() {
            return None;
        }
        Some(parser)
    }

    /// Run the highlight query against `tree` over `bytes`, producing a
    /// sorted span list. Captures are resolved to scopes via the theme.
    pub fn highlight(&self, lang_id: &str, tree: &Tree, bytes: &[u8]) -> Vec<HighlightSpan> {
        let support = match self.langs.get(lang_id) {
            Some(s) => s,
            None => return Vec::new(),
        };
        let mut cursor = QueryCursor::new();
        let mut spans: Vec<HighlightSpan> = Vec::new();
        let mut matches = cursor.matches(&support.query, tree.root_node(), bytes);
        while let Some(m) = matches.next() {
            for cap in m.captures {
                let scope = support
                    .capture_scopes
                    .get(cap.index as usize)
                    .copied()
                    .unwrap_or(ScopeId::Default);
                // Default-scope spans contribute no color and would stomp
                // on earlier real spans during flatten. Captures like
                // `@spell`/`@nospell`/`@conceal`/`@none` in the djot grammar
                // are structural advice for other tools; skip them.
                if scope == ScopeId::Default {
                    continue;
                }
                let range = cap.node.byte_range();
                if range.start < range.end {
                    spans.push(HighlightSpan {
                        start: range.start,
                        end: range.end,
                        scope,
                    });
                }
            }
        }
        spans.sort_by_key(|s| (s.start, std::cmp::Reverse(s.end)));
        spans
    }
}

impl Default for Highlighter {
    fn default() -> Self {
        Self::new()
    }
}

// === Vendored language entry points ===
//
// Each parser.c exports a `tree_sitter_<lang>()` function returning a
// Language. We declare them here.
unsafe extern "C" {
    fn tree_sitter_go() -> Language;
    fn tree_sitter_mshell() -> Language;
    fn tree_sitter_djot() -> Language;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn go_parses_and_highlights_a_keyword() {
        let h = Highlighter::new();
        let mut parser = h.parser_for("go").expect("go parser");
        let src = b"package main\n\nfunc add(a int, b int) int { return a + b }\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("go", &tree, src);
        assert!(!spans.is_empty(), "expected at least one highlight span");
        // The token `func` should land on a keyword scope.
        let func_pos = src.windows(4).position(|w| w == b"func").unwrap();
        let span = spans
            .iter()
            .find(|s| s.start == func_pos && s.end == func_pos + 4)
            .expect("highlight span for `func` not found");
        assert_eq!(span.scope, ScopeId::Keyword);
    }

    #[test]
    fn shebang_detection_handles_direct_and_env() {
        assert_eq!(Highlighter::language_for_shebang(b"#!/usr/bin/msh\n"), Some("mshell"));
        assert_eq!(Highlighter::language_for_shebang(b"#!/usr/local/bin/mshell\n"), Some("mshell"));
        assert_eq!(Highlighter::language_for_shebang(b"#!/usr/bin/env msh\n"), Some("mshell"));
        assert_eq!(Highlighter::language_for_shebang(b"#!/usr/bin/env mshell\n"), Some("mshell"));
        assert_eq!(Highlighter::language_for_shebang(b"#!/usr/bin/env -S msh\n"), Some("mshell"));
        assert_eq!(Highlighter::language_for_shebang(b"#!/usr/bin/env FOO=bar msh\n"), Some("mshell"));
        assert_eq!(Highlighter::language_for_shebang(b"#!/bin/bash\n"), None);
        assert_eq!(Highlighter::language_for_shebang(b"hello world\n"), None);
        assert_eq!(Highlighter::language_for_shebang(b""), None);
    }

    #[test]
    fn incremental_reparse_matches_fresh_parse() {
        // After an edit, applying `tree.edit(&InputEdit)` to the old tree
        // and reparsing must produce a tree structurally identical to a
        // from-scratch parse of the new content. That's the load-bearing
        // contract for incremental tree-sitter — verify it on a real
        // grammar (go) with a non-trivial edit.
        use crate::buffer::Buffer;
        fn collect(buf: &Buffer) -> Vec<u8> {
            let mut v = Vec::new();
            for s in buf.slices() {
                v.extend_from_slice(s);
            }
            v
        }
        let h = Highlighter::new();
        let mut parser = h.parser_for("go").expect("go parser");

        let mut buf = Buffer::from_bytes(b"package main\n\nfunc f() {}\n".to_vec());
        let bytes_v1 = collect(&buf);
        let tree_v1 = parser.parse(&bytes_v1, None).expect("v1 parse");

        buf.insert(13, b"\nvar X = 1\n"); // insert a var decl mid-file
        let edits = buf.drain_pending_edits();
        let mut edited_tree = tree_v1.clone();
        for e in &edits {
            edited_tree.edit(&tree_sitter::InputEdit {
                start_byte: e.start_byte,
                old_end_byte: e.old_end_byte,
                new_end_byte: e.new_end_byte,
                start_position: tree_sitter::Point {
                    row: e.start_position.row,
                    column: e.start_position.column,
                },
                old_end_position: tree_sitter::Point {
                    row: e.old_end_position.row,
                    column: e.old_end_position.column,
                },
                new_end_position: tree_sitter::Point {
                    row: e.new_end_position.row,
                    column: e.new_end_position.column,
                },
            });
        }
        let bytes_v2 = collect(&buf);
        let incremental = parser
            .parse(&bytes_v2, Some(&edited_tree))
            .expect("incremental parse");
        let fresh = parser.parse(&bytes_v2, None).expect("fresh parse");

        // Same S-expression = same tree shape.
        assert_eq!(
            incremental.root_node().to_sexp(),
            fresh.root_node().to_sexp(),
            "incremental and fresh parses diverged"
        );
    }

    #[test]
    fn djot_parses_and_highlights_a_heading() {
        let h = Highlighter::new();
        let mut parser = h.parser_for("djot").expect("djot parser");
        let src = b"# Title\n\nSome text with `code`.\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("djot", &tree, src);
        assert!(!spans.is_empty(), "expected at least one highlight span");
        // `markup.heading` is routed to Keyword in theme.rs.
        assert!(spans.iter().any(|s| s.scope == ScopeId::Keyword));
        // `markup.raw` (inline code) is routed to String.
        assert!(spans.iter().any(|s| s.scope == ScopeId::String));
    }

    #[test]
    fn markdown_extensions_route_to_djot() {
        assert_eq!(
            Highlighter::language_for_path(std::path::Path::new("README.md")),
            Some("djot")
        );
        assert_eq!(
            Highlighter::language_for_path(std::path::Path::new("notes.dj")),
            Some("djot")
        );
    }

    #[test]
    fn mshell_parses_and_highlights_a_comment() {
        let h = Highlighter::new();
        let mut parser = h.parser_for("mshell").expect("mshell parser");
        let src = b"# a comment\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("mshell", &tree, src);
        assert!(spans.iter().any(|s| s.scope == ScopeId::Comment));
    }
}
