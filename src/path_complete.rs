//! Filesystem path completion for insert mode (bound to `Alt-/`).
//!
//! Given the buffer bytes and a cursor offset, work out the path being typed
//! and list matching directory entries as [`CompletionItem`]s. This is the
//! only completion source that touches the filesystem, so it lives here
//! rather than in `completion.rs` (which is deliberately pure).
//!
//! Two cross-cutting behaviors:
//!
//! - **Cross-platform separators.** Both `/` and `\` are recognized as path
//!   separators when reading the typed text, so the same code works on
//!   Windows and Unix. The separator written *back* when descending into a
//!   directory mirrors the one the user typed (or [`std::path::MAIN_SEPARATOR`]
//!   when they typed none).
//!
//! - **Spaces in paths.** A path may contain spaces. We start from the
//!   whitespace-delimited word nearest the cursor; if its directory part
//!   doesn't resolve to a real directory with matching entries, the candidate
//!   is expanded leftward one word at a time until a directory does resolve —
//!   bounded by [`MAX_PATH_LOOKBACK`] so a long line can't trigger an unbounded
//!   backward scan.

use std::path::{Path, PathBuf};

use crate::completion::CompletionItem;

/// Largest number of characters to look back from the cursor while hunting
/// for the path's root. Bounds the space-tolerant word expansion on long
/// lines. Adjustable.
pub const MAX_PATH_LOOKBACK: usize = 200;

/// A resolved path-completion request, ready to drive the popup.
pub struct PathCompletion {
    /// Byte offset where the replacement starts — the beginning of the
    /// partial filename (just past the last separator). On accept,
    /// `[anchor..cursor]` is replaced with the chosen entry name.
    pub anchor: usize,
    /// The partial filename typed so far (may be empty, e.g. right after a
    /// trailing separator). Used as the initial popup filter prefix.
    pub prefix: String,
    /// Matching directory entries, directories first then files, each
    /// alphabetical (case-insensitive). Directory `insert_text` carries a
    /// trailing separator so accepting one descends a level.
    pub items: Vec<CompletionItem>,
    /// The string-quote (`'`, `"`, `` ` ``) that opens the path, when it's
    /// being typed inside a string literal. Lets the caller auto-close the
    /// quote when a file (not a directory) is accepted. `None` for unquoted
    /// paths.
    pub quote: Option<char>,
}

fn is_sep(b: u8) -> bool {
    b == b'/' || b == b'\\'
}

fn is_blank(b: u8) -> bool {
    b == b' ' || b == b'\t'
}

fn is_quote(b: u8) -> bool {
    b == b'\'' || b == b'"' || b == b'`'
}

/// Offset of the nearest string-quote (`'`, `"`, `` ` ``) to the left of
/// `cursor` on its line, if any. Used to bound a path being typed inside a
/// string literal.
fn nearest_quote_left(bytes: &[u8], cursor: usize, line_start: usize) -> Option<usize> {
    let mut p = cursor;
    while p > line_start {
        p -= 1;
        if is_quote(bytes[p]) {
            return Some(p);
        }
    }
    None
}

/// Offset of the start of the line containing `offset`.
fn line_start(bytes: &[u8], offset: usize) -> usize {
    let mut p = offset;
    while p > 0 {
        if bytes[p - 1] == b'\n' {
            return p;
        }
        p -= 1;
    }
    0
}

/// How a candidate path string splits into a directory part and a partial
/// filename. Borrows the partial out of the candidate bytes.
struct Split<'a> {
    /// Directory text (everything before the last separator). Empty when the
    /// candidate has no separator, or when the separator is leading (root).
    dir: String,
    /// `true` if the candidate contained a separator at all.
    had_sep: bool,
    /// The partial filename after the last separator (or the whole candidate
    /// when there's no separator). May contain spaces.
    partial: &'a str,
    /// The separator character the user typed, or the platform default when
    /// the candidate had none. Used when writing a trailing separator back.
    sep: char,
    /// Buffer offset where `partial` begins.
    anchor: usize,
}

/// Split `candidate` (a byte slice starting at buffer offset `start`) at its
/// last `/` or `\`.
fn split_candidate(candidate: &[u8], start: usize) -> Split<'_> {
    let last_sep = candidate.iter().rposition(|&b| is_sep(b));
    match last_sep {
        Some(i) => Split {
            dir: String::from_utf8_lossy(&candidate[..i]).into_owned(),
            had_sep: true,
            partial: std::str::from_utf8(&candidate[i + 1..]).unwrap_or(""),
            sep: candidate[i] as char,
            anchor: start + i + 1,
        },
        None => Split {
            dir: String::new(),
            had_sep: false,
            partial: std::str::from_utf8(candidate).unwrap_or(""),
            sep: std::path::MAIN_SEPARATOR,
            anchor: start,
        },
    }
}

/// Start of the non-whitespace token ending at `cursor` (walking left over
/// non-blank bytes only). Equals `cursor` when the cursor sits at line start
/// or right after whitespace — i.e. an empty partial, which resolves to the
/// current directory.
fn token_start(bytes: &[u8], cursor: usize, bound: usize) -> usize {
    let mut p = cursor;
    while p > bound && !is_blank(bytes[p - 1]) {
        p -= 1;
    }
    p
}

/// Move `from` left past one whitespace-delimited word (skipping any
/// whitespace immediately to its left first). Returns the new start, or
/// `None` once there's nothing left within `bound`.
fn expand_word_left(bytes: &[u8], from: usize, bound: usize) -> Option<usize> {
    let mut p = from;
    while p > bound && is_blank(bytes[p - 1]) {
        p -= 1;
    }
    while p > bound && !is_blank(bytes[p - 1]) {
        p -= 1;
    }
    if p == from {
        None
    } else {
        Some(p)
    }
}

fn home_dir() -> Option<PathBuf> {
    std::env::var_os("HOME")
        .or_else(|| std::env::var_os("USERPROFILE"))
        .map(PathBuf::from)
}

/// Resolve a directory string to a filesystem path, honoring `~`, absolute
/// paths, and cwd-relative paths. `had_sep` distinguishes "no separator at
/// all" (complete in the current directory) from a leading-separator root.
fn resolve_dir(dir: &str, had_sep: bool, sep: char) -> Option<PathBuf> {
    if !had_sep {
        return std::env::current_dir().ok();
    }
    if dir.is_empty() {
        // The candidate began with a separator: filesystem root.
        return Some(PathBuf::from(sep.to_string()));
    }
    if let Some(rest) = dir.strip_prefix('~') {
        let home = home_dir()?;
        let rest = rest.trim_start_matches(['/', '\\']);
        return Some(if rest.is_empty() { home } else { home.join(rest) });
    }
    let p = PathBuf::from(dir);
    if p.is_absolute() {
        Some(p)
    } else {
        Some(std::env::current_dir().ok()?.join(p))
    }
}

fn sort_key(name: &str, is_dir: bool) -> String {
    // Directories sort ahead of files; within each bucket, case-insensitive.
    let bucket = if is_dir { '0' } else { '1' };
    format!("{}{}", bucket, name.to_lowercase())
}

/// List entries of `dir` whose name starts with `partial` (case-insensitive).
/// Hidden entries (leading `.`) are shown only when `partial` itself starts
/// with `.`. Directory items carry a trailing `sep` in both label and
/// `insert_text` so the popup shows them as directories and accepting one
/// descends a level.
fn list_dir(dir: &Path, partial: &str, sep: char) -> Vec<CompletionItem> {
    let read = match std::fs::read_dir(dir) {
        Ok(r) => r,
        Err(_) => return Vec::new(),
    };
    let partial_lower = partial.to_lowercase();
    let want_hidden = partial.starts_with('.');
    let mut items = Vec::new();
    for entry in read.flatten() {
        let name = match entry.file_name().into_string() {
            Ok(n) => n,
            Err(_) => continue,
        };
        if name.starts_with('.') && !want_hidden {
            continue;
        }
        if !name.to_lowercase().starts_with(&partial_lower) {
            continue;
        }
        let is_dir = entry.file_type().map(|t| t.is_dir()).unwrap_or(false);
        let display = if is_dir {
            format!("{}{}", name, sep)
        } else {
            name.clone()
        };
        items.push(CompletionItem {
            label: display.clone(),
            // Filter against the bare name so live narrowing matches the
            // typed prefix even for directories (whose label has a trailing
            // separator).
            filter_text: name.clone(),
            insert_text: display,
            sort_text: sort_key(&name, is_dir),
            detail: None,
        });
    }
    items.sort_by(|a, b| a.sort_text.cmp(&b.sort_text).then(a.label.cmp(&b.label)));
    items
}

/// Whether a separator just typed at `cursor - 1` should auto-open path
/// completion. Requires a non-blank character immediately before the
/// separator, so a deliberate path fragment (`./`, `../`, `~/`, `src/`)
/// triggers but a bare `<space>/` — division, or the ambiguous start of an
/// absolute path after a word — does not. For an absolute path, type `./`
/// for a local one or use the explicit `Alt-/`. The explicit trigger and
/// in-session descent are unaffected; this gates only the initial auto-open.
pub fn separator_should_autotrigger(bytes: &[u8], cursor: usize) -> bool {
    if cursor == 0 || !is_sep(bytes[cursor - 1]) {
        return false;
    }
    // Require a non-whitespace path character immediately before the
    // separator. Whitespace (including a line start via newline) or buffer
    // start before it suppresses the auto-trigger.
    cursor >= 2 && !bytes[cursor - 2].is_ascii_whitespace()
}

/// Resolve a single candidate path region `[start, cursor)` to completions.
/// Returns `None` when its directory part doesn't resolve or has no matching
/// entries.
fn resolve_candidate(bytes: &[u8], start: usize, cursor: usize) -> Option<PathCompletion> {
    let split = split_candidate(&bytes[start..cursor], start);
    let dir = resolve_dir(&split.dir, split.had_sep, split.sep)?;
    let items = list_dir(&dir, split.partial, split.sep);
    if items.is_empty() {
        None
    } else {
        Some(PathCompletion {
            anchor: split.anchor,
            prefix: split.partial.to_string(),
            items,
            quote: None,
        })
    }
}

/// Compute filesystem path completions for the cursor position. Returns
/// `None` when nothing resolves (no directory with matching entries within
/// the lookback window).
pub fn complete(bytes: &[u8], cursor: usize) -> Option<PathCompletion> {
    if cursor > bytes.len() {
        return None;
    }
    let ls = line_start(bytes, cursor);

    // Paths are often typed inside string literals (`"./x"`, `'x'`, markdown
    // `` `x` ``). When a quote opens to the left on this line, the path is the
    // region from just past it to the cursor — spaces included, no look-back
    // needed. Try that first; fall back to the whitespace logic if it doesn't
    // resolve (e.g. an apostrophe in prose like `it's /home/`).
    if let Some(q) = nearest_quote_left(bytes, cursor, ls)
        && let Some(mut pc) = resolve_candidate(bytes, q + 1, cursor)
    {
        pc.quote = Some(bytes[q] as char);
        return Some(pc);
    }

    let bound = cursor.saturating_sub(MAX_PATH_LOOKBACK).max(ls);

    // Iteration 1 is the current token. When it's empty (cursor at line
    // start or right after whitespace), there's no path being typed: list the
    // current directory and stop — no leftward look-back. Look-back exists
    // only to absorb spaces *within* a non-empty path token, so it's gated on
    // a non-empty token below.
    let mut start = token_start(bytes, cursor, bound);
    let token_empty = start == cursor;
    loop {
        if let Some(pc) = resolve_candidate(bytes, start, cursor) {
            return Some(pc);
        }
        if token_empty || start <= bound {
            return None;
        }
        start = expand_word_left(bytes, start, bound)?;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use std::path::PathBuf;

    fn split(s: &str) -> Split<'_> {
        split_candidate(s.as_bytes(), 0)
    }

    #[test]
    fn split_unix_separator() {
        let sp = split("/home/user/fi");
        assert_eq!(sp.dir, "/home/user");
        assert!(sp.had_sep);
        assert_eq!(sp.partial, "fi");
        assert_eq!(sp.sep, '/');
        assert_eq!(sp.anchor, "/home/user/".len());
    }

    #[test]
    fn split_windows_separator() {
        let sp = split("C:\\Users\\me\\fi");
        assert_eq!(sp.dir, "C:\\Users\\me");
        assert!(sp.had_sep);
        assert_eq!(sp.partial, "fi");
        assert_eq!(sp.sep, '\\');
    }

    #[test]
    fn split_no_separator_is_cwd() {
        let sp = split("fi");
        assert!(!sp.had_sep);
        assert_eq!(sp.partial, "fi");
        assert_eq!(sp.anchor, 0);
    }

    #[test]
    fn split_partial_keeps_spaces() {
        let sp = split("/home/my fi");
        assert_eq!(sp.dir, "/home");
        assert_eq!(sp.partial, "my fi");
    }

    /// Make a unique temp directory for one test.
    fn temp_dir(tag: &str) -> PathBuf {
        let mut d = std::env::temp_dir();
        d.push(format!("medit_pathcomp_{}_{}", std::process::id(), tag));
        let _ = fs::remove_dir_all(&d);
        fs::create_dir_all(&d).unwrap();
        d
    }

    fn labels(pc: &PathCompletion) -> Vec<String> {
        pc.items.iter().map(|i| i.label.clone()).collect()
    }

    #[test]
    fn completes_files_in_dir() {
        let dir = temp_dir("files");
        fs::write(dir.join("file1.txt"), b"").unwrap();
        fs::write(dir.join("file2.txt"), b"").unwrap();
        fs::write(dir.join("other.md"), b"").unwrap();

        let line = format!("cat {}/fi", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(pc.prefix, "fi");
        assert_eq!(pc.quote, None);
        // anchor sits at the start of "fi"
        assert_eq!(&line[pc.anchor..], "fi");
        let mut ls = labels(&pc);
        ls.sort();
        assert_eq!(ls, vec!["file1.txt", "file2.txt"]);

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn directory_entries_get_trailing_separator_and_sort_first() {
        let dir = temp_dir("dirs");
        fs::create_dir(dir.join("apple_dir")).unwrap();
        fs::write(dir.join("apple_file"), b"").unwrap();

        let line = format!("{}/apple", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(
            labels(&pc),
            vec!["apple_dir/".to_string(), "apple_file".to_string()]
        );
        // Directory item descends on accept.
        assert_eq!(pc.items[0].insert_text, "apple_dir/");

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn resolves_path_with_spaces_by_expanding_left() {
        let dir = temp_dir("with space");
        fs::write(dir.join("report.txt"), b"").unwrap();
        assert!(dir.to_str().unwrap().contains(' '));

        // The directory part itself contains a space; the nearest word
        // ("space/re") won't resolve, so it must expand left to pick up the
        // whole "...with space" directory.
        let line = format!("cat {}/re", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(pc.prefix, "re");
        assert_eq!(labels(&pc), vec!["report.txt".to_string()]);
        assert_eq!(&line[pc.anchor..], "re");

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn empty_partial_after_trailing_separator_lists_all() {
        let dir = temp_dir("trailing");
        fs::write(dir.join("a.txt"), b"").unwrap();
        fs::write(dir.join("b.txt"), b"").unwrap();

        let line = format!("{}/", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(pc.prefix, "");
        assert_eq!(pc.anchor, line.len());
        let mut ls = labels(&pc);
        ls.sort();
        assert_eq!(ls, vec!["a.txt", "b.txt"]);

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn no_prefix_lists_current_directory() {
        // Unit tests run with the working directory at the crate root, so
        // Cargo.toml is always present. An empty buffer means an empty token.
        let pc = complete(b"", 0).expect("cwd listing");
        assert_eq!(pc.prefix, "");
        assert_eq!(pc.anchor, 0);
        assert!(pc.items.iter().any(|i| i.label == "Cargo.toml"));
    }

    #[test]
    fn empty_token_after_space_lists_current_directory() {
        let line = "cat ";
        let pc = complete(line.as_bytes(), line.len()).expect("cwd listing");
        assert_eq!(pc.prefix, "");
        assert_eq!(pc.anchor, line.len());
        assert!(pc.items.iter().any(|i| i.label == "Cargo.toml"));
    }

    fn autotrig(s: &str) -> bool {
        separator_should_autotrigger(s.as_bytes(), s.len())
    }

    #[test]
    fn autotrigger_fires_after_path_character() {
        assert!(autotrig("./"));
        assert!(autotrig("../"));
        assert!(autotrig("~/"));
        assert!(autotrig("src/"));
        assert!(autotrig("a/b/"));
        assert!(autotrig("foo\\")); // windows separator
    }

    #[test]
    fn autotrigger_suppressed_after_whitespace_or_start() {
        assert!(!autotrig("cat /")); // space before
        assert!(!autotrig("x\t/")); // tab before
        assert!(!autotrig("/")); // buffer start, nothing before
        assert!(!autotrig("a\n/")); // line start (newline before)
        assert!(!autotrig("abc")); // not a separator at all
        assert!(!autotrig("")); // empty
    }

    #[test]
    fn completes_inside_double_quotes() {
        let dir = temp_dir("dquote");
        fs::write(dir.join("file1.txt"), b"").unwrap();
        fs::write(dir.join("file2.txt"), b"").unwrap();

        let line = format!("see \"{}/fi", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(pc.prefix, "fi");
        assert_eq!(pc.quote, Some('"'));
        // Replacement starts at the partial, leaving the quote and dir intact.
        assert_eq!(&line[pc.anchor..], "fi");
        let mut ls = labels(&pc);
        ls.sort();
        assert_eq!(ls, vec!["file1.txt", "file2.txt"]);

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn completes_inside_single_quotes_with_spaces() {
        // Single-quoted path whose directory contains a space: the quote
        // bounds the path, so the whole region resolves without look-back.
        let dir = temp_dir("squote space");
        fs::write(dir.join("report.txt"), b"").unwrap();

        let line = format!("open '{}/re", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(pc.prefix, "re");
        assert_eq!(pc.quote, Some('\''));
        assert_eq!(labels(&pc), vec!["report.txt".to_string()]);

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn completes_inside_backticks() {
        let dir = temp_dir("backtick");
        fs::create_dir(dir.join("assets")).unwrap();

        let line = format!("see `{}/as", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(labels(&pc), vec!["assets/".to_string()]);

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn quote_falls_back_to_unquoted_path() {
        // An apostrophe in prose must not block a following real path.
        let dir = temp_dir("fallback");
        fs::write(dir.join("notes.md"), b"").unwrap();

        let line = format!("it's {}/no", dir.display());
        let pc = complete(line.as_bytes(), line.len()).expect("some completion");
        assert_eq!(labels(&pc), vec!["notes.md".to_string()]);
        // Resolved via the unquoted fallback, so no auto-close quote.
        assert_eq!(pc.quote, None);

        fs::remove_dir_all(&dir).ok();
    }

    #[test]
    fn no_match_returns_none() {
        let dir = temp_dir("nomatch");
        fs::write(dir.join("file.txt"), b"").unwrap();
        let line = format!("{}/zzz", dir.display());
        assert!(complete(line.as_bytes(), line.len()).is_none());
        fs::remove_dir_all(&dir).ok();
    }
}
