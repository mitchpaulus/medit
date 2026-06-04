//! End-to-end checks for the `%` match-pair motion against the real vendored
//! mshell grammar. Parses source, then asserts the selection `match_pair`
//! produces spans the expected bracket group / keyword block.

use medit::core::match_pair;
use medit::highlight::Highlighter;

/// Parse `src` as mshell and return the substring selected by `%` with the
/// cursor at byte `head`. The selection is Kakoune-inclusive, so the covered
/// text is `src[min..=max]`.
fn selected(src: &str, head: usize) -> Option<String> {
    let hl = Highlighter::new();
    let mut parser = hl.parser_for("mshell").expect("mshell parser");
    let tree = parser.parse(src.as_bytes(), None).expect("parse");
    let (anchor, h) = match_pair(src.as_bytes(), Some(&tree), head)?;
    let (lo, hi) = (anchor.min(h), anchor.max(h));
    Some(src[lo..=hi].to_string())
}

/// Byte offset of the first occurrence of `needle` in `src`.
fn at(src: &str, needle: &str) -> usize {
    src.find(needle).expect("needle present")
}

#[test]
fn definition_block_from_def_and_end() {
    let src = "def square (int -- int) dup * end\n";
    let block = "def square (int -- int) dup * end";
    // On `def`.
    assert_eq!(selected(src, at(src, "def")).as_deref(), Some(block));
    // On `end` (last char).
    let end_last = at(src, "end") + 2;
    assert_eq!(selected(src, end_last).as_deref(), Some(block));
}

#[test]
fn quotation_brackets_both_ends() {
    let src = "( 1 2 + )\n";
    let q = "( 1 2 + )";
    assert_eq!(selected(src, at(src, "(")).as_deref(), Some(q));
    assert_eq!(selected(src, at(src, ")")).as_deref(), Some(q));
}

#[test]
fn list_brackets() {
    let src = "[1 2 3]\n";
    assert_eq!(selected(src, at(src, "[")).as_deref(), Some("[1 2 3]"));
    assert_eq!(selected(src, at(src, "]")).as_deref(), Some("[1 2 3]"));
}

#[test]
fn if_block_ignores_else_branch_as_one_region() {
    // The condition (`true`) is outside the if_block; the block runs if..end.
    let src = "true if \"a\" wl else \"b\" wl end\n";
    let block = "if \"a\" wl else \"b\" wl end";
    assert_eq!(selected(src, at(src, "if")).as_deref(), Some(block));
    let end_last = src.rfind("end").unwrap() + 2;
    assert_eq!(selected(src, end_last).as_deref(), Some(block));
}

#[test]
fn nested_prefix_quote_blocks_respect_nesting() {
    let src = "[[1 2 3] [4 5 6]] map. filter. 5 > end end\n";
    // Outer block starts at `map.` and closes at the LAST `end`.
    let outer = "map. filter. 5 > end end";
    assert_eq!(selected(src, at(src, "map.")).as_deref(), Some(outer));
    // Inner block starts at `filter.` and closes at the FIRST `end`.
    let inner = "filter. 5 > end";
    assert_eq!(selected(src, at(src, "filter.")).as_deref(), Some(inner));
    // The first `end` belongs to the inner block.
    let first_end_last = at(src, "end") + 2;
    assert_eq!(selected(src, first_end_last).as_deref(), Some(inner));
    // The last `end` belongs to the outer block.
    let last_end_last = src.rfind("end").unwrap() + 2;
    assert_eq!(selected(src, last_end_last).as_deref(), Some(outer));
}

#[test]
fn match_block_from_keyword() {
    let src = "10 match int : wl, _ : wl, end\n";
    let block = "match int : wl, _ : wl, end";
    assert_eq!(selected(src, at(src, "match")).as_deref(), Some(block));
}

#[test]
fn forward_scan_when_not_on_a_delimiter() {
    // Cursor on `true` (offset 0) — not a delimiter; `%` scans right to `if`.
    let src = "true if \"a\" wl end\n";
    let block = "if \"a\" wl end";
    assert_eq!(selected(src, 0).as_deref(), Some(block));
}

#[test]
fn no_match_returns_none() {
    // A line with no bracket or block delimiter at/after the cursor.
    let src = "1 2 + dup\n";
    assert_eq!(selected(src, 0), None);
}

/// As `selected`, but with no parse tree — exercises the byte-based bracket
/// fallback used for buffers without a registered grammar.
fn selected_no_tree(src: &str, head: usize) -> Option<String> {
    let (anchor, h) = match_pair(src.as_bytes(), None, head)?;
    let (lo, hi) = (anchor.min(h), anchor.max(h));
    Some(src[lo..=hi].to_string())
}

#[test]
fn byte_fallback_matches_nested_brackets() {
    let src = "foo (a (b) c) bar\n";
    let outer = "(a (b) c)";
    // On the outer '(' — nesting is respected, jumps to the outer ')'.
    assert_eq!(selected_no_tree(src, at(src, "(")).as_deref(), Some(outer));
    // On the outer ')'.
    let close = src.rfind(')').unwrap();
    assert_eq!(selected_no_tree(src, close).as_deref(), Some(outer));
    // Forward-scan: cursor on `foo`, first bracket to the right is the outer '('.
    assert_eq!(selected_no_tree(src, 0).as_deref(), Some(outer));
}

#[test]
fn byte_fallback_braces_and_squares() {
    assert_eq!(selected_no_tree("x {1 2} y\n", 2).as_deref(), Some("{1 2}"));
    assert_eq!(selected_no_tree("[a b]\n", 0).as_deref(), Some("[a b]"));
}
