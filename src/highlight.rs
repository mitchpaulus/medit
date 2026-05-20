//! Syntax highlighting via tree-sitter. Each supported language ships a
//! vendored grammar (under `grammars/<lang>/`) compiled by `build.rs`,
//! a `highlights.scm` query that maps tree nodes to capture names, and
//! a mapping from those capture names to ANSI fg colors via `theme.rs`.
//!
//! Adding a language: drop one entry in the `LANGS` table at the bottom
//! of this file — name, extern fn, query strings, and the aliases users
//! might write (extensions, shebangs, fence names) plus an optional LSP
//! command. All resolution functions (`language_for_path`, shebang,
//! injection, LSP) walk this same table.
//!
//! Public surface:
//! - `Highlighter`: holds all known languages' Parser + Query.
//! - `HighlightSpan`: a (byte range, scope) the renderer can consume.
//! - `Highlighter::language_for_path(path)`: pick a language by file
//!   extension. Returns `None` for unknown files (plain rendering).

use std::collections::HashMap;

use tree_sitter::{Language, Parser, Query, QueryCursor, StreamingIterator, Tree};

use crate::theme::{self, ScopeId};

/// Static declaration for one supported language. Single source of truth
/// for every "is this language?" lookup the editor performs.
pub struct LangSpec {
    /// Canonical id used everywhere internally (lookup key, file-type tag,
    /// LSP key). Always lowercase.
    pub name: &'static str,
    /// `tree_sitter_<lang>()` entry point compiled in via `build.rs`.
    pub language: unsafe extern "C" fn() -> Language,
    /// Highlight query (S-expression tree-sitter query).
    pub highlights: &'static str,
    /// Optional language-injections query. Currently only djot ships one.
    pub injections: Option<&'static str>,
    /// File extensions (no leading `.`) that resolve to this language.
    pub extensions: &'static [&'static str],
    /// Shebang interpreter basenames (e.g. `"msh"`, `"python3"`).
    pub shebangs: &'static [&'static str],
    /// Fenced-code-block info strings that route a code block to this
    /// language (e.g. `"go"`, `"rs"`/`"rust"`). Matched case-insensitively.
    pub fence_names: &'static [&'static str],
    /// LSP server command + args, when one exists.
    pub lsp: Option<(&'static str, &'static [&'static str])>,
}

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
    /// Optional injections query. Captures `@injection.content` and
    /// `@injection.language` on subranges that should be highlighted with
    /// another grammar (e.g. fenced code blocks in djot/markdown).
    injections_query: Option<Query>,
    injections_lang_idx: Option<u32>,
    injections_content_idx: Option<u32>,
}

pub struct Highlighter {
    langs: HashMap<&'static str, LangSupport>,
}

impl Highlighter {
    pub fn new() -> Self {
        let mut h = Self {
            langs: HashMap::new(),
        };
        for spec in LANGS {
            h.register(spec);
        }
        h
    }

    fn register(&mut self, spec: &LangSpec) {
        let language = unsafe { (spec.language)() };
        let query = match Query::new(&language, spec.highlights) {
            Ok(q) => q,
            Err(e) => {
                eprintln!("highlight: failed to compile {} query: {}", spec.name, e);
                return;
            }
        };
        let capture_scopes: Vec<ScopeId> = query
            .capture_names()
            .iter()
            .map(|n| theme::scope_for_capture(n))
            .collect();
        let (injections_query, injections_lang_idx, injections_content_idx) =
            if let Some(src) = spec.injections {
                match Query::new(&language, src) {
                    Ok(q) => {
                        let lang_idx = q.capture_index_for_name("injection.language");
                        let content_idx = q.capture_index_for_name("injection.content");
                        (Some(q), lang_idx, content_idx)
                    }
                    Err(e) => {
                        eprintln!(
                            "highlight: failed to compile {} injections: {}",
                            spec.name, e
                        );
                        (None, None, None)
                    }
                }
            } else {
                (None, None, None)
            };
        self.langs.insert(
            spec.name,
            LangSupport {
                language,
                query,
                capture_scopes,
                injections_query,
                injections_lang_idx,
                injections_content_idx,
            },
        );
    }

    /// Map an injection-language string (the text in a fenced code block's
    /// info line, like `go` / `msh` / `markdown`) to a registered grammar.
    /// Case-insensitive; returns `None` for unsupported languages so the
    /// block falls back to the parent grammar's default rendering.
    fn lang_id_for_injection(&self, name: &str) -> Option<&'static str> {
        let n = name.trim().to_ascii_lowercase();
        LANGS
            .iter()
            .find(|s| s.fence_names.iter().any(|f| f.eq_ignore_ascii_case(&n)))
            .map(|s| s.name)
    }

    /// Map a file extension to a registered language id.
    pub fn language_for_path(path: &std::path::Path) -> Option<&'static str> {
        let ext = path.extension()?.to_str()?;
        LANGS
            .iter()
            .find(|s| s.extensions.iter().any(|e| *e == ext))
            .map(|s| s.name)
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
        LANGS
            .iter()
            .find(|s| s.shebangs.iter().any(|sb| *sb == interp))
            .map(|s| s.name)
    }

    /// LSP server command (program + args) for a language id, if one is
    /// registered. Walks the `LANGS` table.
    pub fn lsp_command_for_lang(
        lang: &str,
    ) -> Option<(&'static str, &'static [&'static str])> {
        LANGS.iter().find(|s| s.name == lang).and_then(|s| s.lsp)
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
    /// If `lang_id`'s grammar ships an injections query (e.g. djot for
    /// fenced code blocks), each injection content range is parsed with
    /// the embedded language and its spans are merged in.
    pub fn highlight(&self, lang_id: &str, tree: &Tree, bytes: &[u8]) -> Vec<HighlightSpan> {
        let mut spans: Vec<HighlightSpan> = Vec::new();
        self.collect_spans(lang_id, tree, bytes, 0, &mut spans);
        spans.sort_by_key(|s| (s.start, std::cmp::Reverse(s.end)));
        spans
    }

    /// Append highlight spans for `bytes` parsed by `lang_id`, offsetting
    /// each span by `byte_offset` so they're expressed in the parent
    /// buffer's coordinates. Recurses into language injections.
    fn collect_spans(
        &self,
        lang_id: &str,
        tree: &Tree,
        bytes: &[u8],
        byte_offset: usize,
        out: &mut Vec<HighlightSpan>,
    ) {
        let support = match self.langs.get(lang_id) {
            Some(s) => s,
            None => return,
        };

        let mut cursor = QueryCursor::new();
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
                    out.push(HighlightSpan {
                        start: range.start + byte_offset,
                        end: range.end + byte_offset,
                        scope,
                    });
                }
            }
        }

        // Language injections: for each `@injection.language` + `@injection.content`
        // pair, recursively highlight the content with the embedded grammar.
        let inj_query = match support.injections_query.as_ref() {
            Some(q) => q,
            None => return,
        };
        let (lang_idx, content_idx) =
            match (support.injections_lang_idx, support.injections_content_idx) {
                (Some(l), Some(c)) => (l, c),
                _ => return,
            };
        let mut inj_cursor = QueryCursor::new();
        let mut inj_matches = inj_cursor.matches(inj_query, tree.root_node(), bytes);
        while let Some(m) = inj_matches.next() {
            let mut inj_lang: Option<&'static str> = None;
            let mut content_range: Option<(usize, usize)> = None;
            for cap in m.captures {
                if cap.index == lang_idx {
                    let r = cap.node.byte_range();
                    if let Ok(name) = std::str::from_utf8(&bytes[r.start..r.end]) {
                        inj_lang = self.lang_id_for_injection(name);
                    }
                } else if cap.index == content_idx {
                    let r = cap.node.byte_range();
                    content_range = Some((r.start, r.end));
                }
            }
            if let (Some(inj_lang), Some((cs, ce))) = (inj_lang, content_range) {
                if ce <= cs {
                    continue;
                }
                // Skip the trivial recursive case: a djot block embedded in
                // a djot file. We'd re-highlight the same content with the
                // same scopes; the parent pass already covers it.
                if inj_lang == lang_id {
                    continue;
                }
                let inj_support = match self.langs.get(inj_lang) {
                    Some(s) => s,
                    None => continue,
                };
                let mut parser = Parser::new();
                if parser.set_language(&inj_support.language).is_err() {
                    continue;
                }
                let slice = &bytes[cs..ce];
                let inj_tree = match parser.parse(slice, None) {
                    Some(t) => t,
                    None => continue,
                };
                // Punch a Default-scope hole over the injection content so
                // the parent's broad `markup.raw.block` (green) doesn't
                // bleed through bytes the injected grammar didn't paint.
                // Specific injection spans get layered on top below.
                out.push(HighlightSpan {
                    start: byte_offset + cs,
                    end: byte_offset + ce,
                    scope: ScopeId::Default,
                });
                self.collect_spans(inj_lang, &inj_tree, slice, byte_offset + cs, out);
            }
        }
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
// Language. Declared here, referenced from the `LANGS` table below.
unsafe extern "C" {
    fn tree_sitter_go() -> Language;
    fn tree_sitter_mshell() -> Language;
    fn tree_sitter_djot() -> Language;
}

/// Single source of truth for every language the editor knows. To add a
/// new language: vendor its grammar under `grammars/<name>/`, add an
/// entry to `build.rs::LANGUAGES`, declare its `tree_sitter_<name>` fn
/// above, and append one `LangSpec` block here. No other edits required.
static LANGS: &[LangSpec] = &[
    LangSpec {
        name: "go",
        language: tree_sitter_go,
        highlights: include_str!("../grammars/go/queries/highlights.scm"),
        injections: None,
        extensions: &["go"],
        shebangs: &[],
        fence_names: &["go"],
        lsp: Some(("gopls", &[])),
    },
    LangSpec {
        name: "mshell",
        language: tree_sitter_mshell,
        highlights: include_str!("../grammars/mshell/queries/highlights.scm"),
        injections: None,
        extensions: &["msh", "mshell"],
        shebangs: &["msh", "mshell"],
        fence_names: &["msh", "mshell"],
        lsp: Some(("msh", &["lsp"])),
    },
    // Djot doubles as the markdown grammar — close enough that reading
    // other-people's markdown stays useful. Split if it starts mis-parsing
    // common constructs.
    LangSpec {
        name: "djot",
        language: tree_sitter_djot,
        highlights: include_str!("../grammars/djot/queries/highlights.scm"),
        injections: Some(include_str!("../grammars/djot/queries/injections.scm")),
        extensions: &["dj", "djot", "md", "markdown"],
        shebangs: &[],
        fence_names: &["djot", "markdown", "md"],
        lsp: None,
    },
];

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
    fn djot_injects_go_into_fenced_code_block() {
        let h = Highlighter::new();
        let mut parser = h.parser_for("djot").expect("djot parser");
        let src = b"# Title\n\n```go\nfunc f() {}\n```\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("djot", &tree, src);
        // The `func` keyword inside the fenced block should be highlighted
        // by the go grammar — that means a Keyword span must land on the
        // `func` byte range inside the code block.
        let func_pos = src
            .windows(4)
            .position(|w| w == b"func")
            .expect("find func");
        let hit = spans
            .iter()
            .find(|s| s.start == func_pos && s.end == func_pos + 4 && s.scope == ScopeId::Keyword);
        assert!(
            hit.is_some(),
            "expected an injected Keyword span for `func` at byte {}; got {:?}",
            func_pos,
            spans
                .iter()
                .filter(|s| s.start >= func_pos && s.end <= func_pos + 4)
                .collect::<Vec<_>>()
        );
    }

    #[test]
    fn known_language_fence_does_not_paint_unknown_tokens_green() {
        // In a ```go``` fence, bytes the go grammar doesn't capture (e.g.
        // the whitespace between `var` and `x`) should land on Default —
        // not the djot parent's `markup.raw.block` (String/green).
        let h = Highlighter::new();
        let mut parser = h.parser_for("djot").expect("djot parser");
        let src = b"```go\nvar x int\n```\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("djot", &tree, src);
        let scopes = flatten_to_byte_scopes(&spans, src.len());
        // The space byte right after `var` is captured by neither grammar.
        let var_pos = src
            .windows(3)
            .position(|w| w == b"var")
            .expect("find var");
        let space_pos = var_pos + 3;
        assert_eq!(src[space_pos], b' ');
        assert_eq!(
            scopes[space_pos],
            ScopeId::Default,
            "uncolored whitespace inside a known-language fence should be Default, got {:?}",
            scopes[space_pos]
        );
        // The opening fence bytes themselves should still carry the parent
        // grammar's styling (Punctuation for the ``` markers).
        assert_eq!(scopes[0], ScopeId::Punctuation);
    }

    #[test]
    fn unknown_language_fence_keeps_parent_block_color() {
        // A fence with an unknown language should *not* punch the hole —
        // its body stays styled by the parent grammar's `markup.raw.block`.
        let h = Highlighter::new();
        let mut parser = h.parser_for("djot").expect("djot parser");
        let src = b"```rust\nfn x() {}\n```\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("djot", &tree, src);
        let scopes = flatten_to_byte_scopes(&spans, src.len());
        let x_pos = src.iter().position(|&b| b == b'x').expect("find x");
        assert_eq!(scopes[x_pos], ScopeId::String);
    }

    #[test]
    fn djot_injects_mshell_into_fenced_code_block() {
        let h = Highlighter::new();
        let mut parser = h.parser_for("djot").expect("djot parser");
        let src = b"```msh\n# a comment\n```\n";
        let tree = parser.parse(src.as_slice(), None).expect("parse");
        let spans = h.highlight("djot", &tree, src);
        // mshell's `# a comment` must produce a Comment span inside.
        let comment_pos = src
            .windows(11)
            .position(|w| w == b"# a comment")
            .expect("find comment");
        let hit = spans
            .iter()
            .find(|s| s.start == comment_pos && s.scope == ScopeId::Comment);
        assert!(hit.is_some(), "expected Comment span from mshell injection");
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
