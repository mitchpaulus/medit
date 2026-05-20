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
    fn mshell_parses_and_highlights_a_comment() {
        let h = Highlighter::new();
        let mut parser = h.parser_for("mshell").expect("mshell parser");
        let src = b"# a comment\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("mshell", &tree, src);
        assert!(spans.iter().any(|s| s.scope == ScopeId::Comment));
    }
}
