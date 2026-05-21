mod term;

use std::collections::HashMap;
use std::io::{self, Read};
use std::path::{Path, PathBuf};

use medit::buffer::Buffer;
use medit::core::{
    ExAction, LspAction, Mode, ObjectKind, Registers, SearchState, Selections, all_matches,
    byte_at_line, byte_at_line_cached, collect_bytes, display_col, handle_ex, handle_insert,
    handle_normal, handle_search, line_index, line_index_cached, line_start, next_char_or_end,
    save_buffer, snap_to_char_or_last, utf8_len,
};
use medit::highlight::{Highlighter, flatten_to_byte_scopes};
use medit::indent::Indenter;
use medit::input::{Event, Key, KeyEvent, Mods, Parser};
use medit::lsp::{self, LspClient};
use medit::theme::{self, ScopeId};
use medit::trace;
use medit::watch::{DiskMeta, FileWatcher};
use term::{RawMode, Screen};

const SEL_BG: &str = "\x1b[48;5;24m";
const MATCH_BG: &str = "\x1b[48;5;94m";
const LINENO_FG: &str = "\x1b[38;5;240m";

// Diagnostic underlines: curly underline (`4:3`) with severity-tinted
// underline color (`58:5:N`). Terminals that don't support curly fall
// back to a straight underline.
const DIAG_UL_ERROR: &str = "\x1b[4:3;58:5:9m";
const DIAG_UL_WARN: &str = "\x1b[4:3;58:5:11m";
const DIAG_UL_INFO: &str = "\x1b[4:3;58:5:14m";
const DIAG_UL_HINT: &str = "\x1b[4:3;58:5:8m";

fn diag_ul_for(sev: medit::lsp::DiagnosticSeverity) -> &'static str {
    use medit::lsp::DiagnosticSeverity::*;
    match sev {
        Error => DIAG_UL_ERROR,
        Warning => DIAG_UL_WARN,
        Information => DIAG_UL_INFO,
        Hint => DIAG_UL_HINT,
    }
}

/// Per-buffer editor state. The main loop holds a `Vec<EditorBuffer>` and a
/// `current` index; switching buffers means moving the index.
struct EditorBuffer {
    buffer: Buffer,
    sels: Selections,
    top_line: usize,
    path: Option<PathBuf>,
    /// Syntax highlighting state. `lang_id` is set when the file extension
    /// matches a registered grammar; `tree` is the most recent parse;
    /// `flat_scopes` is a dense byte → scope lookup for the renderer.
    lang_id: Option<&'static str>,
    tree: Option<tree_sitter::Tree>,
    flat_scopes: Vec<ScopeId>,
    /// Cached flat byte view of `buffer`. Refreshed lazily by
    /// `refresh_bytes_cache` when `buffer.version()` doesn't match
    /// `cached_version`. Saves the per-frame `collect_bytes` walk for
    /// read-only consumers (the renderer and `ensure_visible`).
    cached_bytes: Vec<u8>,
    /// `line_starts[k]` is the byte offset of the start of line `k`. Always
    /// has at least one entry (0 for the first line). Built alongside
    /// `cached_bytes`. Lets `line_index_cached` use binary search and
    /// `byte_at_line_cached` index in O(1).
    line_starts: Vec<usize>,
    cached_version: Option<u64>,
    /// `buffer.version()` that `tree`/`flat_scopes` were built from. When
    /// the buffer moves past this, the highlight is stale and the next
    /// frame re-parses.
    highlight_version: Option<u64>,
    /// Last `buffer.version()` we sent to the LSP server (via didOpen or
    /// didChange). When the buffer moves past this and we're not in
    /// insert mode, fire a didChange to resync.
    lsp_synced_version: Option<u64>,
    /// `buffer.version()` at the moment we last wrote this buffer to disk
    /// (or `Some(0)` for a freshly-loaded file, since it matches disk).
    /// `None` for a never-saved scratch buffer with no path. Drives the
    /// dirty check that protects quit paths.
    saved_version: Option<u64>,
    /// Stat snapshot of the file on disk at the moment we last read from
    /// or wrote to it. `None` when there's no backing file (yet). Drives
    /// the external-change detector — both on save (conflict check) and
    /// in the watcher path (whether a notify event actually changed
    /// anything relative to what we last saw).
    disk_meta: Option<DiskMeta>,
    /// Set by the watcher path when the file changed on disk and we
    /// couldn't auto-reload (because the buffer was dirty). Surfaces in
    /// the status bar so the user knows there's a conflict to resolve.
    external_change_pending: bool,
}

impl EditorBuffer {
    fn new(buffer: Buffer, path: Option<PathBuf>) -> Self {
        let lang_id = path
            .as_deref()
            .and_then(Highlighter::language_for_path)
            .or_else(|| Highlighter::language_for_shebang(&collect_bytes(&buffer)));
        let saved_version = if path.is_some() { Some(0) } else { None };
        let disk_meta = path.as_deref().and_then(|p| DiskMeta::read(p).ok());
        Self {
            buffer,
            sels: Selections::new(),
            top_line: 0,
            path,
            lang_id,
            tree: None,
            flat_scopes: Vec::new(),
            cached_bytes: Vec::new(),
            line_starts: vec![0],
            cached_version: None,
            highlight_version: None,
            lsp_synced_version: None,
            // A file-backed buffer matches disk on load; a scratch buffer
            // without a path has nothing to compare against until saved.
            saved_version,
            disk_meta,
            external_change_pending: false,
        }
    }

    /// True when there are unsaved changes worth prompting about.
    fn is_dirty(&self) -> bool {
        match self.saved_version {
            Some(v) => v != self.buffer.version(),
            None => self.buffer.version() != 0,
        }
    }

    fn display_name(&self) -> String {
        self.path
            .as_ref()
            .and_then(|p| p.file_name())
            .and_then(|s| s.to_str())
            .map(|s| s.to_string())
            .unwrap_or_else(|| "[no name]".to_string())
    }
}

/// Ensure `eb.cached_bytes` and `eb.line_starts` reflect the current
/// buffer state. Cheap when versions match; otherwise rebuilds both in a
/// single linear pass.
fn refresh_bytes_cache(eb: &mut EditorBuffer) {
    let v = eb.buffer.version();
    if eb.cached_version == Some(v) {
        return;
    }
    eb.cached_bytes.clear();
    eb.cached_bytes.reserve(eb.buffer.len());
    eb.line_starts.clear();
    eb.line_starts.push(0);
    for slice in eb.buffer.slices() {
        let base = eb.cached_bytes.len();
        eb.cached_bytes.extend_from_slice(slice);
        // Index newline positions as we copy; recording byte offsets of
        // the byte *after* each '\n' (i.e. the start of the next line).
        for (i, &b) in slice.iter().enumerate() {
            if b == b'\n' {
                eb.line_starts.push(base + i + 1);
            }
        }
    }
    eb.cached_version = Some(v);
}

/// Cached counterpart to `core::ensure_visible`. Same semantics
/// (including `SCROLLOFF`), but uses the cached line-starts index for
/// O(log L) line lookup.
fn ensure_visible_indexed(
    line_starts: &[usize],
    head: usize,
    top_line: &mut usize,
    viewport_rows: usize,
) {
    if viewport_rows == 0 {
        return;
    }
    let head_line = line_index_cached(line_starts, head);
    let off = medit::core::SCROLLOFF.min(viewport_rows.saturating_sub(1) / 2);
    let top_zone_end = top_line.saturating_add(off);
    let bottom_zone_start = top_line.saturating_add(viewport_rows).saturating_sub(off);
    if head_line < top_zone_end {
        *top_line = head_line.saturating_sub(off);
    } else if head_line >= bottom_zone_start {
        *top_line = head_line + off + 1 - viewport_rows;
    }
}

/// Re-parse `eb` and rebuild its `flat_scopes`. Drains any pending edits
/// from the buffer and applies them to the existing tree via `tree.edit`
/// before calling `parser.parse(..., Some(&old_tree))`, so tree-sitter can
/// reuse unchanged subtrees instead of reparsing the whole buffer. No-op
/// when the buffer hasn't moved since the last call.
fn reparse_and_highlight(eb: &mut EditorBuffer, hl: &Highlighter) {
    let lang_id = match eb.lang_id {
        Some(l) => l,
        None => return,
    };
    let v = eb.buffer.version();
    if eb.highlight_version == Some(v) {
        // Even if we skip, swallow any edits the buffer may have queued so
        // they don't accumulate against a stale tree later.
        let _ = eb.buffer.drain_pending_edits();
        return;
    }
    let mut parser = match hl.parser_for(lang_id) {
        Some(p) => p,
        None => return,
    };

    let edits = eb.buffer.drain_pending_edits();
    if let Some(tree) = eb.tree.as_mut() {
        for e in &edits {
            tree.edit(&edit_to_ts(e));
        }
    }

    let bytes = collect_bytes(&eb.buffer);
    let tree = match parser.parse(&bytes, eb.tree.as_ref()) {
        Some(t) => t,
        None => return,
    };
    let spans = hl.highlight(lang_id, &tree, &bytes);
    eb.flat_scopes = flatten_to_byte_scopes(&spans, bytes.len());
    eb.tree = Some(tree);
    eb.highlight_version = Some(v);
}

fn edit_to_ts(e: &medit::buffer::Edit) -> tree_sitter::InputEdit {
    tree_sitter::InputEdit {
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
    }
}

/// Compute the SGR transition string needed to go from `(cur_fg, cur_bg)`
/// to `(new_fg, new_bg)`. Returns an empty string if no change is needed.
/// Emits only the channels that changed (and uses minimal-form resets for
/// single-channel transitions to default).
/// Write the minimal SGR transition from (cur_*) to (new_*) directly
/// into `out`. No-op when state matches. Hot path — must not allocate.
///
/// `ul` is a full SGR string like `"\x1b[4;58:5:9m"` (curly underline,
/// red): it enables underline + sets underline color. The "off" form
/// is `\x1b[24;59m`.
fn append_style_transition(
    out: &mut Vec<u8>,
    cur_fg: Option<&str>,
    cur_bg: Option<&str>,
    cur_ul: Option<&str>,
    new_fg: Option<&str>,
    new_bg: Option<&str>,
    new_ul: Option<&str>,
) {
    if cur_fg == new_fg && cur_bg == new_bg && cur_ul == new_ul {
        return;
    }
    let fg_to_default = cur_fg.is_some() && new_fg.is_none();
    let bg_to_default = cur_bg.is_some() && new_bg.is_none();
    let ul_to_default = cur_ul.is_some() && new_ul.is_none();
    if fg_to_default && bg_to_default && ul_to_default {
        out.extend_from_slice(b"\x1b[0m");
        return;
    }
    if fg_to_default {
        out.extend_from_slice(b"\x1b[39m");
    }
    if bg_to_default {
        out.extend_from_slice(b"\x1b[49m");
    }
    if ul_to_default {
        out.extend_from_slice(b"\x1b[24;59m");
    }
    if new_fg != cur_fg {
        if let Some(f) = new_fg {
            out.extend_from_slice(f.as_bytes());
        }
    }
    if new_bg != cur_bg {
        if let Some(b) = new_bg {
            out.extend_from_slice(b.as_bytes());
        }
    }
    if new_ul != cur_ul {
        if let Some(u) = new_ul {
            out.extend_from_slice(u.as_bytes());
        }
    }
}

/// Write `\x1b[row;colH` directly into `out` without allocating an
/// intermediate `String`. Hot path.
fn append_cursor_pos(out: &mut Vec<u8>, row: u16, col: u16) {
    out.push(0x1b);
    out.push(b'[');
    append_u16(out, row);
    out.push(b';');
    append_u16(out, col);
    out.push(b'H');
}

fn append_u16(out: &mut Vec<u8>, mut n: u16) {
    if n == 0 {
        out.push(b'0');
        return;
    }
    let mut buf = [0u8; 5];
    let mut i = 0;
    while n > 0 {
        buf[i] = b'0' + (n % 10) as u8;
        n /= 10;
        i += 1;
    }
    while i > 0 {
        i -= 1;
        out.push(buf[i]);
    }
}

/// Emit a styled cell at `(row, col)` directly into the screen's back
/// buffer. Handles cursor-position coalescing (skips the position escape
/// when the terminal cursor is already at the target) and SGR
/// coalescing (only emits transitions when style state actually changed).
/// Updates `cursor_at`, `style_fg`, `style_bg` in place. No allocations.
#[allow(clippy::too_many_arguments)]
fn emit_styled_cell(
    screen: &mut Screen,
    cursor_at: &mut Option<(u16, u16)>,
    style_fg: &mut Option<&'static str>,
    style_bg: &mut Option<&'static str>,
    style_ul: &mut Option<&'static str>,
    row: u16,
    col: u16,
    width: u16,
    new_fg: Option<&'static str>,
    new_bg: Option<&'static str>,
    new_ul: Option<&'static str>,
    body: &[u8],
) {
    let back = screen.back_mut();
    if *cursor_at != Some((row, col)) {
        append_cursor_pos(back, row, col);
    }
    append_style_transition(
        back, *style_fg, *style_bg, *style_ul, new_fg, new_bg, new_ul,
    );
    back.extend_from_slice(body);
    *cursor_at = Some((row, col + width));
    *style_fg = new_fg;
    *style_bg = new_bg;
    *style_ul = new_ul;
}

/// Render a bordered popup containing `d.message` at a position adjacent
/// to the cursor. Box-drawing chars are emitted as UTF-8 directly. The
/// popup overlays buffer cells — it's drawn after the main pass, so it
/// "wins" any conflicting cell. Severity tints the border.
/// Render a modal prompt centered on the screen: bold title row, body
/// lines below, then dim choice hints. Box-drawing chars; the SGR
/// sequences are reset after each cell so the surrounding view doesn't
/// inherit them.
fn draw_prompt(screen: &mut Screen, prompt: &Prompt, rows: u16, cols: u16) {
    const BORDER: &str = "\x1b[38;5;110m";
    const BOLD: &str = "\x1b[1m";
    const DIM: &str = "\x1b[38;5;243m";
    const RESET: &str = "\x1b[0m";

    // Build the lines that go inside the box. Choices share one row
    // (joined by `  ·  `) when they fit.
    let mut lines: Vec<String> = Vec::new();
    lines.push(prompt.title.clone());
    lines.push(String::new());
    for b in &prompt.body {
        lines.push(b.clone());
    }
    if !prompt.choices.is_empty() {
        lines.push(String::new());
        let mut choice_line = String::new();
        for (i, (key, desc)) in prompt.choices.iter().enumerate() {
            if i > 0 {
                choice_line.push_str("  ·  ");
            }
            choice_line.push_str(&format!("[{}] {}", key, desc));
        }
        lines.push(choice_line);
    }

    let max_text = lines.iter().map(|l| l.chars().count()).max().unwrap_or(0);
    let inner_w = max_text + 4; // 2-char padding either side
    let box_w = inner_w as u16 + 2; // +2 for vertical borders
    let box_h = lines.len() as u16 + 2; // +2 for horizontal borders

    if box_w >= cols || box_h >= rows {
        // Pathological tiny window — skip rather than wrap-mangle.
        return;
    }
    let top = (rows.saturating_sub(box_h)) / 2;
    let left = (cols.saturating_sub(box_w)) / 2;

    let mut top_line = String::with_capacity(box_w as usize * 4);
    top_line.push_str(BORDER);
    top_line.push('╭');
    for _ in 0..inner_w {
        top_line.push('─');
    }
    top_line.push('╮');
    top_line.push_str(RESET);
    screen.write_at(top, left, &top_line);

    for (i, line) in lines.iter().enumerate() {
        let visible_len = line.chars().count();
        let pad_total = inner_w.saturating_sub(visible_len);
        // Center each line inside the box.
        let pad_left = pad_total / 2;
        let pad_right = pad_total - pad_left;

        let mut row_str = String::with_capacity(box_w as usize * 4);
        row_str.push_str(BORDER);
        row_str.push('│');
        row_str.push_str(RESET);
        for _ in 0..pad_left {
            row_str.push(' ');
        }
        // Style by row: title (first non-empty) bold, choices (last
        // non-empty) dim, body neutral.
        let is_title = i == 0;
        let is_choices = i + 1 == lines.len() && !prompt.choices.is_empty();
        if is_title {
            row_str.push_str(BOLD);
            row_str.push_str(line);
            row_str.push_str(RESET);
        } else if is_choices {
            row_str.push_str(DIM);
            row_str.push_str(line);
            row_str.push_str(RESET);
        } else {
            row_str.push_str(line);
        }
        for _ in 0..pad_right {
            row_str.push(' ');
        }
        row_str.push_str(BORDER);
        row_str.push('│');
        row_str.push_str(RESET);
        screen.write_at(top + 1 + i as u16, left, &row_str);
    }

    let mut bot_line = String::with_capacity(box_w as usize * 4);
    bot_line.push_str(BORDER);
    bot_line.push('╰');
    for _ in 0..inner_w {
        bot_line.push('─');
    }
    bot_line.push('╯');
    bot_line.push_str(RESET);
    screen.write_at(top + box_h - 1, left, &bot_line);
}

fn draw_diag_popup(
    screen: &mut Screen,
    d: &medit::lsp::Diagnostic,
    cur_row: u16,
    cur_col: u16,
    gutter: u16,
    cols: u16,
    viewport_rows: u16,
) {
    // Wrap the message into lines of at most `max_text` chars. Word-wrap
    // on spaces when possible, hard-break otherwise.
    let max_text: usize = (cols as usize).saturating_sub(6).max(20).min(60);
    let mut lines: Vec<String> = Vec::new();
    for raw_line in d.message.lines() {
        let mut remaining = raw_line.trim_end();
        if remaining.is_empty() {
            lines.push(String::new());
            continue;
        }
        while remaining.chars().count() > max_text {
            let take = remaining
                .char_indices()
                .take(max_text)
                .last()
                .map(|(idx, ch)| idx + ch.len_utf8())
                .unwrap_or(remaining.len());
            // Try to break at a space within the window.
            let head_slice = &remaining[..take];
            let split = head_slice.rfind(' ').map(|p| p + 1).unwrap_or(take);
            lines.push(remaining[..split].trim_end().to_string());
            remaining = remaining[split..].trim_start();
            if remaining.is_empty() {
                break;
            }
        }
        if !remaining.is_empty() {
            lines.push(remaining.to_string());
        }
    }
    if lines.is_empty() {
        return;
    }
    // Cap to ~6 lines so the popup can't dominate the viewport.
    let max_rows: usize = 6;
    if lines.len() > max_rows {
        lines.truncate(max_rows);
        if let Some(last) = lines.last_mut() {
            if last.chars().count() > max_text.saturating_sub(1) {
                last.truncate(last.char_indices().nth(max_text.saturating_sub(1)).map(|(i,_)| i).unwrap_or(last.len()));
            }
            last.push('…');
        }
    }
    let width_text = lines.iter().map(|l| l.chars().count()).max().unwrap_or(0);
    let inner_w = width_text + 2; // 1-char padding either side
    let box_w = inner_w as u16 + 2; // +2 for vertical borders
    let box_h = lines.len() as u16 + 2; // +2 for horizontal borders

    // Anchor: prefer one row below the cursor; flip above if no room.
    // Horizontally: align to the cursor's column, but clamp inside the
    // viewport.
    let mut top: u16 = cur_row.saturating_add(1);
    if top + box_h - 1 > viewport_rows {
        top = cur_row.saturating_sub(box_h);
        if top == 0 {
            // Cursor near top with no room above; force it below and let
            // it clip into the status row rather than disappear.
            top = 1;
        }
    }
    let anchor_col = cur_col.saturating_add(gutter);
    let mut left: u16 = anchor_col.saturating_sub(1).max(1);
    if left + box_w - 1 > cols {
        left = cols.saturating_sub(box_w - 1).max(1);
    }

    let border = diag_border_fg_for(d.severity);
    // Top border.
    let mut top_line = String::with_capacity(box_w as usize * 3);
    top_line.push_str(border);
    top_line.push('┌');
    for _ in 0..inner_w { top_line.push('─'); }
    top_line.push('┐');
    top_line.push_str("\x1b[0m");
    screen.write_at(top, left, &top_line);

    for (i, line) in lines.iter().enumerate() {
        let pad = inner_w - 1 - line.chars().count();
        let mut row_str = String::with_capacity(box_w as usize * 3);
        row_str.push_str(border);
        row_str.push('│');
        row_str.push_str("\x1b[0m");
        row_str.push(' ');
        row_str.push_str(line);
        for _ in 0..pad { row_str.push(' '); }
        row_str.push_str(border);
        row_str.push('│');
        row_str.push_str("\x1b[0m");
        screen.write_at(top + 1 + i as u16, left, &row_str);
    }

    let mut bot_line = String::with_capacity(box_w as usize * 3);
    bot_line.push_str(border);
    bot_line.push('└');
    for _ in 0..inner_w { bot_line.push('─'); }
    bot_line.push('┘');
    bot_line.push_str("\x1b[0m");
    screen.write_at(top + box_h - 1, left, &bot_line);
}

fn diag_border_fg_for(sev: medit::lsp::DiagnosticSeverity) -> &'static str {
    use medit::lsp::DiagnosticSeverity::*;
    match sev {
        Error => "\x1b[38;5;9m",
        Warning => "\x1b[38;5;11m",
        Information => "\x1b[38;5;14m",
        Hint => "\x1b[38;5;8m",
    }
}

fn draw_lineno(screen: &mut Screen, row: u16, lineno: usize, gutter: u16) {
    // Wrap the line number with explicit resets so style state is
    // predictable on either side (caller can assume default after).
    let digits = gutter.saturating_sub(1) as usize;
    let text = format!(
        "\x1b[0m{}{:>width$} \x1b[0m",
        LINENO_FG,
        lineno,
        width = digits
    );
    screen.write_at(row, 1, &text);
}

fn print_help() {
    println!(
        "medit \u{2014} a small modal text editor

USAGE:
    medit [FILE]
    medit -h | --help

ARGS:
    FILE    Optional path to open. If the file doesn't exist, starts with an
            empty buffer; `:w` will create it on save.

Keybindings and Ex commands are documented in doc/medit.html."
    );
}

fn main() -> io::Result<()> {
    trace::init_from_env();
    let arg1 = std::env::args().nth(1);
    if let Some(a) = arg1.as_deref()
        && (a == "-h" || a == "--help")
    {
        print_help();
        return Ok(());
    }
    let initial_path: Option<PathBuf> = arg1.map(PathBuf::from);
    let initial_buffer = match initial_path.as_ref() {
        Some(p) if p.exists() => Buffer::open(p)?,
        _ => Buffer::empty(),
    };
    let highlighter = Highlighter::new();
    let indenter = Indenter::new();
    let mut buffers: Vec<EditorBuffer> = {
        let mut eb = EditorBuffer::new(initial_buffer, initial_path);
        reparse_and_highlight(&mut eb, &highlighter);
        vec![eb]
    };
    let mut current: usize = 0;

    // Filesystem watcher for open files. Best-effort: if construction
    // fails (e.g. on a platform we don't support yet) we proceed without
    // it and rely on the save-time conflict check alone.
    let mut watcher: Option<FileWatcher> = FileWatcher::new().ok();
    if let Some(w) = watcher.as_mut() {
        if let Some(p) = buffers[0].path.as_deref() {
            let _ = w.watch(p);
        }
    }

    let mut mode = Mode::Normal;
    let mut registers = Registers::default();
    let mut ex_input = String::new();
    let mut ex_message = String::new();
    let mut pending_j = false;
    let mut pending_g = false;
    let mut pending_z = false;
    let mut pending_find: Option<medit::core::FindOp> = None;
    let mut pending_bracket: Option<medit::core::BracketDir> = None;
    let mut pending_object: Option<ObjectKind> = None;
    let mut pending_lsp_action: Option<LspAction> = None;
    let mut pending_ex_action: Option<ExAction> = None;
    let mut search_input = String::new();
    let mut search_state = SearchState::default();
    let mut last_key: Option<KeyEvent> = None;
    let mut last_bytes: Vec<u8> = Vec::new();
    // Active modal prompt, if any. When `Some`, the next keypress is
    // consumed by `handle_prompt` instead of being routed to the active
    // mode, and the prompt box overlays the editor view.
    let mut prompt: Option<Prompt> = None;

    // LSP. We spawn one server per language, on demand, the first time we
    // open a file of that language (initial buffer or via `:e`). All
    // buffers of a given language share the same client.
    let mut lsp_clients: HashMap<&'static str, LspClient> = HashMap::new();
    if let Some(p) = buffers[0].path.clone() {
        maybe_start_lsp_and_open(&mut lsp_clients, &p, &mut buffers[0]);
    }

    let _raw = RawMode::enable()?;
    let mut screen = Screen::enter()?;
    term::install_sigwinch_handler()?;

    // Populate cache before the first frame; subsequent frames refresh in
    // the main loop.
    refresh_bytes_cache(&mut buffers[current]);
    render_all(
        &mut screen,
        &buffers,
        current,
        mode,
        &ex_input,
        &search_input,
        &search_state,
        &ex_message,
        last_key.as_ref(),
        &last_bytes,
        &lsp_clients,
        prompt.as_ref(),
    )?;

    let stdin = io::stdin();
    let mut handle = stdin.lock();
    let mut io_buf = [0u8; 64];
    let mut parser = Parser::new();

    loop {
        if term::take_resize_flag() {
            screen.refresh_size()?;
            let viewport_rows = screen.rows.saturating_sub(1) as usize;
            {
                let cur = &mut buffers[current];
                refresh_bytes_cache(cur);
                let head = cur.sels.primary().head;
                ensure_visible_indexed(&cur.line_starts, head, &mut cur.top_line, viewport_rows);
            }
            render_all(
                &mut screen,
                &buffers,
                current,
                mode,
                &ex_input,
                &search_input,
                &search_state,
                &ex_message,
                last_key.as_ref(),
                &last_bytes,
                &lsp_clients,
                prompt.as_ref(),
            )?;
        }
        let n = match handle.read(&mut io_buf) {
            Ok(0) => break,
            Ok(n) => n,
            Err(e) if e.kind() == io::ErrorKind::Interrupted => continue,
            Err(e) => return Err(e),
        };
        // Frame timing starts after the blocking read so we don't measure
        // input-wait latency.
        let frame_start = trace::tic();
        let handle_start = trace::tic();
        last_bytes = io_buf[..n].to_vec();
        parser.feed(&io_buf[..n]);
        // After consuming all complete events from this read burst, fall back
        // to `flush()` so a lone trailing ESC byte (Esc key in non-kitty
        // terminals) resolves to `Key::Esc` instead of waiting indefinitely
        // for a follow-up byte that never arrives.
        while let Some(event) = parser.next_event().or_else(|| parser.flush()) {
            let Event::Key(k) = event;
            last_key = Some(k);
            // Intercept any active prompt: the next keypress is consumed
            // by `handle_prompt` regardless of which mode we were in
            // when the prompt went up.
            if let Some(p) = prompt.take() {
                match handle_prompt(
                    &p,
                    k,
                    &mut buffers,
                    &mut current,
                    &highlighter,
                    &mut ex_message,
                ) {
                    PromptOutcome::Quit => return Ok(()),
                    PromptOutcome::Dismiss => continue,
                }
            }
            if k.mods.contains(Mods::CTRL) && k.key == Key::Char('c') {
                match attempt_quit(&buffers) {
                    QuitOutcome::Quit => return Ok(()),
                    QuitOutcome::Prompt => {
                        prompt = Some(build_quit_prompt(&buffers));
                        continue;
                    }
                }
            }
            if mode == Mode::Normal {
                ex_message.clear();
            }
            match mode {
                Mode::Normal => {
                    let viewport_rows = screen.rows.saturating_sub(1) as usize;
                    let cur = &mut buffers[current];
                    refresh_bytes_cache(cur);
                    // Split the borrow: handle_normal needs `&mut cur.buffer`
                    // *and* immutable views of `cur.cached_bytes` /
                    // `cur.line_starts`. The cache stays valid for the
                    // duration of the call — mutating ops inside re-collect
                    // their own fresh bytes.
                    let EditorBuffer {
                        buffer,
                        sels,
                        top_line,
                        cached_bytes,
                        line_starts,
                        ..
                    } = cur;
                    if handle_normal(
                        buffer,
                        sels,
                        &mut mode,
                        &mut registers,
                        &mut pending_g,
                        &mut pending_z,
                        &mut pending_object,
                        &mut pending_find,
                        &mut pending_bracket,
                        &mut search_state,
                        &mut pending_lsp_action,
                        top_line,
                        viewport_rows,
                        cached_bytes,
                        line_starts,
                        k,
                    ) {
                        // Normal-mode `q` closes the active buffer. Clean
                        // buffers close immediately; dirty buffers raise a
                        // close-confirm prompt. Closing the last buffer
                        // exits the editor.
                        match attempt_close_current(&mut buffers, &mut current) {
                            CloseOutcome::Closed => continue,
                            CloseOutcome::QuitEditor => return Ok(()),
                            CloseOutcome::Prompt => {
                                prompt = Some(build_close_buffer_prompt(&buffers, current));
                                continue;
                            }
                        }
                    }
                    if mode == Mode::Ex {
                        ex_input.clear();
                    }
                    if mode == Mode::Search {
                        search_input.clear();
                    }
                    if let Some(action) = pending_lsp_action.take() {
                        dispatch_lsp(
                            action,
                            &mut lsp_clients,
                            &mut buffers,
                            &mut current,
                            &highlighter,
                            watcher.as_mut(),
                            &mut ex_message,
                        );
                    }
                }
                Mode::Insert => {
                    let cur = &mut buffers[current];
                    // Smart-indent closure: bracket-counting on the raw
                    // bytes (no tree required), robust against in-progress
                    // brackets the user hasn't closed yet.
                    let indent_fn: Option<Box<dyn Fn(&[u8], usize) -> String>> =
                        cur.lang_id.map(|lang| {
                            let indenter = &indenter;
                            Box::new(move |bytes: &[u8], pos: usize| {
                                indenter.indent_for(lang, bytes, pos)
                            }) as Box<dyn Fn(&[u8], usize) -> String>
                        });
                    handle_insert(
                        &mut cur.buffer,
                        &mut cur.sels,
                        &mut mode,
                        &mut pending_j,
                        &mut registers,
                        indent_fn.as_deref(),
                        k,
                    );
                }
                Mode::Ex => {
                    let path_owned = buffers[current].path.clone();
                    let _ = handle_ex(
                        &buffers[current].buffer,
                        &mut mode,
                        &mut ex_input,
                        &mut ex_message,
                        &mut pending_ex_action,
                        path_owned.as_deref(),
                        k,
                    );
                    if let Some(action) = pending_ex_action.take() {
                        match dispatch_ex_action(
                            action,
                            &mut buffers,
                            &mut current,
                            &mut lsp_clients,
                            &highlighter,
                            watcher.as_mut(),
                            &mut prompt,
                            &mut ex_message,
                        ) {
                            AfterAction::Continue => {}
                            AfterAction::Quit => return Ok(()),
                        }
                    }
                }
                Mode::Search => {
                    let cur = &mut buffers[current];
                    handle_search(
                        &cur.buffer,
                        &mut cur.sels,
                        &mut mode,
                        &mut search_input,
                        &mut search_state,
                        &mut ex_message,
                        k,
                    );
                }
            }
        }
        let handle_ns = trace::toc(handle_start);
        // After the input burst settles, if we're not actively typing in
        // insert mode and the buffer has moved past what the LSP server
        // last saw, push a didChange. Fires on Esc/`jf` out of insert
        // mode and after any normal-mode mutation.
        if mode != Mode::Insert {
            sync_lsp_if_dirty(&mut buffers[current], &mut lsp_clients);
        }
        // Drain anything each LSP reader thread has parked since the last
        // wake (diagnostics, etc.) so they're visible in this frame.
        for client in lsp_clients.values_mut() {
            client.poll();
        }
        // Drain the filesystem watcher: clean buffers auto-reload from
        // disk, dirty buffers get marked with a pending conflict and
        // raise a Conflict prompt.
        if let Some(w) = watcher.as_ref() {
            apply_watcher_events(w, &mut buffers, &highlighter, &mut prompt, &mut ex_message);
        }
        let render_start = trace::tic();
        {
            let viewport_rows = screen.rows.saturating_sub(1) as usize;
            let cur = &mut buffers[current];
            refresh_bytes_cache(cur);
            // Re-parse + rebuild flat_scopes when the buffer has moved.
            // Otherwise stale byte ranges land scopes on the wrong text.
            reparse_and_highlight(cur, &highlighter);
            let head = cur.sels.primary().head;
            ensure_visible_indexed(&cur.line_starts, head, &mut cur.top_line, viewport_rows);
        }
        render_all(
            &mut screen,
            &buffers,
            current,
            mode,
            &ex_input,
            &search_input,
            &search_state,
            &ex_message,
            last_key.as_ref(),
            &last_bytes,
            &lsp_clients,
            prompt.as_ref(),
        )?;
        let render_ns = trace::toc(render_start);
        let total_ns = trace::toc(frame_start);
        trace::emit_frame(
            total_ns,
            handle_ns,
            render_ns,
            buffers[current].buffer.len(),
        );
    }
    Ok(())
}

/// If the current buffer has been mutated since the last LSP sync,
/// send a full-text `didChange`. Called from the main loop on every
/// transition out of insert mode (and after every normal-mode op),
/// keyed off `buffer.version()`. Looks up the right server by the
/// buffer's language.
fn sync_lsp_if_dirty(eb: &mut EditorBuffer, clients: &mut HashMap<&'static str, LspClient>) {
    let path = match eb.path.as_ref() {
        Some(p) => p,
        None => return,
    };
    let lang = match eb.lang_id {
        Some(l) => l,
        None => return,
    };
    let client = match clients.get_mut(lang) {
        Some(c) => c,
        None => return,
    };
    let cur_ver = eb.buffer.version();
    if eb.lsp_synced_version == Some(cur_ver) {
        return;
    }
    if eb.lsp_synced_version.is_none() {
        // We never sent didOpen for this buffer. Don't fire didChange —
        // the server would reject an unknown URI.
        return;
    }
    let uri = match lsp::path_to_uri(path) {
        Ok(u) => u,
        Err(_) => return,
    };
    let text = String::from_utf8_lossy(&collect_bytes(&eb.buffer)).into_owned();
    if client.did_change(&uri, cur_ver, &text).is_ok() {
        eb.lsp_synced_version = Some(cur_ver);
    }
}

/// Spawn an LSP server for `path` (if it's a recognized language) and send
/// didOpen for its current buffer content. No-op if the language isn't
/// recognized or if spawn fails. A separate server is spawned per language
/// the first time a file of that language is opened.
fn maybe_start_lsp_and_open(
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    path: &Path,
    eb: &mut EditorBuffer,
) {
    let lang_id = match eb.lang_id {
        Some(l) => l,
        None => return,
    };
    if !lsp_clients.contains_key(lang_id) {
        let (program, args) = match Highlighter::lsp_command_for_lang(lang_id) {
            Some(c) => c,
            None => return,
        };
        let cwd = std::env::current_dir().unwrap_or_else(|_| PathBuf::from("."));
        let root_uri = match lsp::path_to_uri(&cwd) {
            Ok(u) => u,
            Err(_) => return,
        };
        match LspClient::spawn(program, args, &root_uri) {
            Ok(c) => {
                lsp_clients.insert(lang_id, c);
            }
            Err(_) => return,
        }
    }
    if let (Some(client), Ok(uri)) = (lsp_clients.get_mut(lang_id), lsp::path_to_uri(path)) {
        let text = String::from_utf8_lossy(&collect_bytes(&eb.buffer)).into_owned();
        if client.did_open(&uri, lang_id, &text).is_ok() {
            eb.lsp_synced_version = Some(eb.buffer.version());
        }
    }
}

/// Handle an `LspAction` queued by the modal layer. For goto-definition we
/// send the request, then either:
/// - Same-file result: jump the cursor in the current buffer.
/// - Cross-file result: open or switch to that file as a new buffer, then
///   jump the cursor there.
fn dispatch_lsp(
    action: LspAction,
    clients: &mut HashMap<&'static str, LspClient>,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    highlighter: &Highlighter,
    watcher: Option<&mut FileWatcher>,
    ex_message: &mut String,
) {
    let lang = match buffers[*current].lang_id {
        Some(l) => l,
        None => {
            *ex_message = "no LSP server for this file".to_string();
            return;
        }
    };
    let cur_uri = match buffers[*current]
        .path
        .as_ref()
        .and_then(|p| lsp::path_to_uri(p).ok())
    {
        Some(u) => u,
        None => {
            *ex_message = "LSP: current buffer has no URI".to_string();
            return;
        }
    };
    match action {
        LspAction::GotoDefinition => {
            let (line, character) = {
                let cur = &buffers[*current];
                let bytes = collect_bytes(&cur.buffer);
                let head = cur.sels.primary().head;
                let line = line_index(&bytes, head) as u32;
                let line_start_byte = byte_at_line(&bytes, line as usize);
                let character = head.saturating_sub(line_start_byte) as u32;
                (line, character)
            };
            let loc = {
                let client = match clients.get_mut(lang) {
                    Some(c) => c,
                    None => {
                        *ex_message = "no LSP server for this file".to_string();
                        return;
                    }
                };
                match client.definition(&cur_uri, line, character) {
                    Ok(Some(loc)) => loc,
                    Ok(None) => {
                        *ex_message = "no definition found".to_string();
                        return;
                    }
                    Err(e) => {
                        *ex_message = format!("LSP error: {}", e);
                        return;
                    }
                }
            };
            // If the definition is in another file, open it (or switch to
            // an already-open buffer) before jumping the cursor.
            if loc.uri != cur_uri {
                let target_path = match lsp::uri_to_path(&loc.uri) {
                    Some(p) => p,
                    None => {
                        *ex_message = format!("LSP: cannot parse target URI: {}", loc.uri);
                        return;
                    }
                };
                if !open_or_switch_to(
                    buffers,
                    current,
                    &target_path,
                    clients,
                    highlighter,
                    watcher,
                    ex_message,
                ) {
                    return;
                }
            }
            // Now buffers[current] is the target buffer; jump the cursor.
            let cur = &mut buffers[*current];
            let bytes = collect_bytes(&cur.buffer);
            let target_line_start = byte_at_line(&bytes, loc.line as usize);
            let target = target_line_start.saturating_add(loc.character as usize);
            let new_head = snap_to_char_or_last(&bytes, target);
            cur.sels.reduce_to_primary();
            let p = cur.sels.primary_mut();
            p.anchor = new_head;
            p.head = new_head;
            p.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
        }
        LspAction::NextDiagnostic | LspAction::PrevDiagnostic => {
            let client = match clients.get_mut(lang) {
                Some(c) => c,
                None => {
                    *ex_message = "no LSP server for this file".to_string();
                    return;
                }
            };
            let next = matches!(action, LspAction::NextDiagnostic);
            let diags = client.diagnostics_for(&cur_uri);
            if diags.is_empty() {
                *ex_message = "no diagnostics".to_string();
                return;
            }
            let cur = &mut buffers[*current];
            let bytes = collect_bytes(&cur.buffer);
            let head = cur.sels.primary().head;
            let cur_line = line_index(&bytes, head) as u32;
            let line_start_byte = byte_at_line(&bytes, cur_line as usize);
            let cur_char = head.saturating_sub(line_start_byte) as u32;
            let target = if next {
                diags
                    .iter()
                    .find(|d| {
                        (d.start_line, d.start_character) > (cur_line, cur_char)
                    })
                    .or_else(|| diags.first())
            } else {
                diags
                    .iter()
                    .rev()
                    .find(|d| {
                        (d.start_line, d.start_character) < (cur_line, cur_char)
                    })
                    .or_else(|| diags.last())
            };
            let d = match target {
                Some(d) => d,
                None => return,
            };
            let target_line_start = byte_at_line(&bytes, d.start_line as usize);
            let target_byte =
                target_line_start.saturating_add(d.start_character as usize);
            let new_head = snap_to_char_or_last(&bytes, target_byte);
            cur.sels.reduce_to_primary();
            let p = cur.sels.primary_mut();
            p.anchor = new_head;
            p.head = new_head;
            p.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
        }
    }
}

/// Open `path` as a new buffer (or switch to it if already open). On a new
/// open, runs the syntax highlighter and notifies the LSP server via
/// `didOpen` if applicable. Returns `false` and sets `ex_message` on
/// failure (e.g. can't read the file).
/// Modal-overlay prompt rendered as a bold, centered box on top of the
/// editor view. Used for blocking decisions the user has to resolve
/// before continuing (unsaved-changes confirm, disk-conflict resolution).
/// The next keystroke is consumed by the prompt and routed via
/// `handle_prompt` based on `kind`.
struct Prompt {
    title: String,
    body: Vec<String>,
    /// Pairs of `(key-hint, description)` shown beneath the body.
    choices: Vec<(&'static str, &'static str)>,
    kind: PromptKind,
}

/// What domain the prompt is for, controlling how a keypress resolves.
enum PromptKind {
    /// `Ctrl+C` with at least one dirty buffer anywhere. `y` saves all
    /// and quits, `n` discards and quits, anything else cancels.
    QuitConfirm,
    /// `q` / `:q` / `:wq` on a buffer with unsaved edits. `y` saves and
    /// closes the buffer, `n` discards and closes, anything else cancels.
    /// If the closed buffer was the last open, the editor exits.
    CloseBufferConfirm { buffer_index: usize },
    /// External change detected on a buffer with unsaved edits. `r`
    /// reloads from disk (losing edits), `o` overwrites disk (losing
    /// external edits), anything else cancels.
    Conflict { buffer_index: usize },
}

/// Result of handling one keypress while a prompt is active.
enum PromptOutcome {
    /// Resolve the prompt and continue editing.
    Dismiss,
    /// Exit the editor.
    Quit,
}

/// Outcome of a quit request — either the editor can exit cleanly, or
/// there are unsaved buffers and the caller should raise a confirm prompt.
enum QuitOutcome {
    Quit,
    Prompt,
}

/// Build the QuitConfirm prompt with a dirty-buffer count and the standard
/// y/n/cancel hints.
fn build_quit_prompt(buffers: &[EditorBuffer]) -> Prompt {
    let n_dirty = buffers.iter().filter(|b| b.is_dirty()).count();
    let names: Vec<String> = buffers
        .iter()
        .filter(|b| b.is_dirty())
        .take(4)
        .map(|b| b.display_name())
        .collect();
    let mut body = vec![format!("{} buffer(s) have unsaved changes:", n_dirty)];
    for n in &names {
        body.push(format!("  • {}", n));
    }
    if n_dirty > names.len() {
        body.push(format!("  • … and {} more", n_dirty - names.len()));
    }
    Prompt {
        title: "Unsaved changes".to_string(),
        body,
        choices: vec![
            ("y", "save all & quit"),
            ("n", "discard & quit"),
            ("any other", "cancel"),
        ],
        kind: PromptKind::QuitConfirm,
    }
}

/// Build the close-buffer confirm prompt for `buffer_index`.
fn build_close_buffer_prompt(buffers: &[EditorBuffer], buffer_index: usize) -> Prompt {
    let name = buffers
        .get(buffer_index)
        .map(|b| b.display_name())
        .unwrap_or_else(|| "?".to_string());
    Prompt {
        title: "Close buffer with unsaved changes".to_string(),
        body: vec![format!("\"{}\" has unsaved edits.", name)],
        choices: vec![
            ("y", "save & close"),
            ("n", "discard & close"),
            ("any other", "cancel"),
        ],
        kind: PromptKind::CloseBufferConfirm { buffer_index },
    }
}

/// Build the disk-conflict prompt for `buffer_index` (assumed to be a
/// buffer with both unsaved edits and an externally-modified file on disk).
fn build_conflict_prompt(buffers: &[EditorBuffer], buffer_index: usize) -> Prompt {
    let name = buffers
        .get(buffer_index)
        .map(|b| b.display_name())
        .unwrap_or_else(|| "?".to_string());
    Prompt {
        title: "File changed on disk".to_string(),
        body: vec![
            format!("\"{}\" was modified externally", name),
            "while you also have unsaved edits.".to_string(),
        ],
        choices: vec![
            ("r", "reload from disk (lose your edits)"),
            ("o", "overwrite disk (lose external edits)"),
            ("any other", "cancel"),
        ],
        kind: PromptKind::Conflict { buffer_index },
    }
}

/// Decide what to do when something requests a full-editor quit (e.g.
/// `Ctrl+C`). Caller raises the prompt itself; this just reports whether
/// one's needed.
fn attempt_quit(buffers: &[EditorBuffer]) -> QuitOutcome {
    if buffers.iter().any(|b| b.is_dirty()) {
        QuitOutcome::Prompt
    } else {
        QuitOutcome::Quit
    }
}

/// Outcome of an attempt to close the current buffer.
enum CloseOutcome {
    /// Buffer is clean and was removed. Caller should check if `buffers`
    /// is now empty and exit if so.
    Closed,
    /// Buffer was the last one and is clean — exit the editor entirely.
    QuitEditor,
    /// Buffer is dirty; caller raises a CloseBufferConfirm prompt.
    Prompt,
}

/// Try to close `buffers[current]`. Clean buffers close immediately;
/// dirty buffers ask the caller to raise a confirm prompt. If closing
/// the last remaining buffer, this asks the caller to exit the editor.
fn attempt_close_current(buffers: &mut Vec<EditorBuffer>, current: &mut usize) -> CloseOutcome {
    let idx = *current;
    let dirty = buffers.get(idx).map(|b| b.is_dirty()).unwrap_or(false);
    if dirty {
        return CloseOutcome::Prompt;
    }
    let was_last = buffers.len() <= 1;
    close_buffer_at(buffers, current, idx);
    if was_last {
        CloseOutcome::QuitEditor
    } else {
        CloseOutcome::Closed
    }
}

/// Remove `buffers[idx]` and adjust `current` so it still points at a
/// valid buffer (the one to the left, if any). No-op when `idx` is out
/// of range.
fn close_buffer_at(buffers: &mut Vec<EditorBuffer>, current: &mut usize, idx: usize) {
    if idx >= buffers.len() {
        return;
    }
    buffers.remove(idx);
    if buffers.is_empty() {
        *current = 0;
    } else if *current >= buffers.len() {
        *current = buffers.len() - 1;
    } else if *current > idx {
        *current -= 1;
    }
}

/// Route a keystroke into the active prompt. Returns whether to dismiss
/// the prompt (and continue) or exit the editor. Side effects (writes,
/// reloads, status messages) happen here per `prompt.kind`.
fn handle_prompt(
    prompt: &Prompt,
    k: KeyEvent,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    highlighter: &Highlighter,
    ex_message: &mut String,
) -> PromptOutcome {
    match prompt.kind {
        PromptKind::QuitConfirm => match k.key {
            Key::Char('y') | Key::Char('Y') => {
                for eb in buffers.iter_mut() {
                    if !eb.is_dirty() {
                        continue;
                    }
                    let path = match eb.path.clone() {
                        Some(p) => p,
                        None => {
                            *ex_message = format!(
                                "\"{}\" has no path — use :w <path> first",
                                eb.display_name()
                            );
                            return PromptOutcome::Dismiss;
                        }
                    };
                    if let (Some(prev), Ok(now)) = (eb.disk_meta, DiskMeta::read(&path)) {
                        if prev != now {
                            *ex_message = format!(
                                "\"{}\" changed on disk — resolve with :w! or :e!",
                                path.display()
                            );
                            eb.external_change_pending = true;
                            return PromptOutcome::Dismiss;
                        }
                    }
                    if let Err(e) = save_buffer(&eb.buffer, &path) {
                        *ex_message = format!("write {} failed: {}", path.display(), e);
                        return PromptOutcome::Dismiss;
                    }
                    eb.saved_version = Some(eb.buffer.version());
                    eb.disk_meta = DiskMeta::read(&path).ok();
                    eb.external_change_pending = false;
                }
                PromptOutcome::Quit
            }
            Key::Char('n') | Key::Char('N') => PromptOutcome::Quit,
            _ => {
                *ex_message = "quit cancelled".to_string();
                PromptOutcome::Dismiss
            }
        },
        PromptKind::CloseBufferConfirm { buffer_index } => match k.key {
            Key::Char('y') | Key::Char('Y') => {
                let eb = match buffers.get_mut(buffer_index) {
                    Some(b) => b,
                    None => return PromptOutcome::Dismiss,
                };
                if !save_current(eb, false, ex_message) {
                    return PromptOutcome::Dismiss;
                }
                let was_last = buffers.len() <= 1;
                close_buffer_at(buffers, current, buffer_index);
                if was_last {
                    PromptOutcome::Quit
                } else {
                    PromptOutcome::Dismiss
                }
            }
            Key::Char('n') | Key::Char('N') => {
                let was_last = buffers.len() <= 1;
                close_buffer_at(buffers, current, buffer_index);
                if was_last {
                    PromptOutcome::Quit
                } else {
                    PromptOutcome::Dismiss
                }
            }
            _ => {
                *ex_message = "close cancelled".to_string();
                PromptOutcome::Dismiss
            }
        },
        PromptKind::Conflict { buffer_index } => match k.key {
            Key::Char('r') | Key::Char('R') => {
                let eb = match buffers.get_mut(buffer_index) {
                    Some(b) => b,
                    None => return PromptOutcome::Dismiss,
                };
                reload_from_disk(eb, highlighter, ex_message);
                PromptOutcome::Dismiss
            }
            Key::Char('o') | Key::Char('O') => {
                let eb = match buffers.get_mut(buffer_index) {
                    Some(b) => b,
                    None => return PromptOutcome::Dismiss,
                };
                save_current(eb, true, ex_message);
                PromptOutcome::Dismiss
            }
            _ => {
                *ex_message = "conflict deferred — use :e! or :w! when ready".to_string();
                PromptOutcome::Dismiss
            }
        },
    }
}

/// Save `eb` to its current path. Updates `saved_version` and
/// `disk_meta` on success. Returns `false` (and sets `ex_message`) if
/// the buffer has no path, the write fails, or — unless `force` is
/// `true` — the on-disk file has been modified externally since we
/// last read or wrote it.
fn save_current(eb: &mut EditorBuffer, force: bool, ex_message: &mut String) -> bool {
    let path = match eb.path.clone() {
        Some(p) => p,
        None => {
            *ex_message = "no file name (use :w <path>)".to_string();
            return false;
        }
    };
    if !force {
        if let (Some(prev), Ok(now)) = (eb.disk_meta, DiskMeta::read(&path)) {
            if prev != now {
                *ex_message = format!(
                    "\"{}\" changed on disk — :w! overwrites, :e! reloads",
                    path.display()
                );
                eb.external_change_pending = true;
                return false;
            }
        }
    }
    match save_buffer(&eb.buffer, &path) {
        Ok(()) => {
            eb.saved_version = Some(eb.buffer.version());
            eb.disk_meta = DiskMeta::read(&path).ok();
            eb.external_change_pending = false;
            *ex_message = format!("\"{}\" written", path.display());
            true
        }
        Err(e) => {
            *ex_message = format!("write failed: {}", e);
            false
        }
    }
}

/// Reload the buffer from its backing file, discarding in-memory edits
/// and undo history. Resets all derived caches (tree, scopes, line
/// index) and clamps the cursor into the new buffer. No-op for a
/// scratch buffer with no path.
fn reload_from_disk(
    eb: &mut EditorBuffer,
    highlighter: &Highlighter,
    ex_message: &mut String,
) -> bool {
    let path = match eb.path.clone() {
        Some(p) => p,
        None => {
            *ex_message = "no file to reload".to_string();
            return false;
        }
    };
    let new_buffer = match Buffer::open(&path) {
        Ok(b) => b,
        Err(e) => {
            *ex_message = format!("reload failed: {}", e);
            return false;
        }
    };
    eb.buffer = new_buffer;
    eb.tree = None;
    eb.cached_version = None;
    eb.highlight_version = None;
    eb.lsp_synced_version = None;
    eb.saved_version = Some(0);
    eb.disk_meta = DiskMeta::read(&path).ok();
    eb.external_change_pending = false;
    // Clamp cursor into the reloaded buffer.
    let new_len = eb.buffer.len();
    eb.sels.reduce_to_primary();
    {
        let primary = eb.sels.primary_mut();
        primary.head = primary.head.min(new_len);
        primary.anchor = primary.anchor.min(new_len);
    }
    eb.top_line = 0;
    refresh_bytes_cache(eb);
    reparse_and_highlight(eb, highlighter);
    true
}

fn open_or_switch_to(
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    path: &Path,
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    highlighter: &Highlighter,
    watcher: Option<&mut FileWatcher>,
    ex_message: &mut String,
) -> bool {
    if let Some(idx) = buffers
        .iter()
        .position(|b| b.path.as_deref() == Some(path))
    {
        *current = idx;
        return true;
    }
    let buffer = if path.exists() {
        match Buffer::open(path) {
            Ok(b) => b,
            Err(e) => {
                *ex_message = format!("open failed: {}", e);
                return false;
            }
        }
    } else {
        Buffer::empty()
    };
    let mut eb = EditorBuffer::new(buffer, Some(path.to_path_buf()));
    reparse_and_highlight(&mut eb, highlighter);
    buffers.push(eb);
    *current = buffers.len() - 1;
    // Spawn the appropriate LSP server lazily (no-op if already running
    // for that language) and send didOpen for the new file.
    maybe_start_lsp_and_open(lsp_clients, path, &mut buffers[*current]);
    if let Some(w) = watcher {
        let _ = w.watch(path);
    }
    true
}

/// Drain `notify` events and decide what to do per buffer. For each
/// affected buffer:
/// - If the on-disk file actually matches our last-seen stat, ignore
///   (notify is noisy: chmod, touch with no content change, etc.).
/// - If the buffer has no in-memory changes, auto-reload from disk.
/// - Otherwise mark a pending external change and raise a Conflict
///   prompt unless one's already up (avoid stomping an existing prompt).
fn apply_watcher_events(
    watcher: &FileWatcher,
    buffers: &mut [EditorBuffer],
    highlighter: &Highlighter,
    prompt: &mut Option<Prompt>,
    ex_message: &mut String,
) {
    let changed = watcher.poll();
    if changed.is_empty() {
        return;
    }
    let mut conflict_index: Option<usize> = None;
    for path in &changed {
        // notify reports parent-directory events with the full file path;
        // match against each buffer's stored path. Canonicalize both sides
        // so symlinks / `./` prefixes don't mask a hit.
        let target = path.canonicalize().unwrap_or_else(|_| path.clone());
        for (idx, eb) in buffers.iter_mut().enumerate() {
            let eb_path = match eb.path.clone() {
                Some(p) => p,
                None => continue,
            };
            let eb_canon = eb_path.canonicalize().unwrap_or_else(|_| eb_path.clone());
            if eb_canon != target {
                continue;
            }
            // Restat: skip events that don't actually move (mtime, size).
            let now = match DiskMeta::read(&eb_path) {
                Ok(m) => m,
                Err(_) => continue,
            };
            if Some(now) == eb.disk_meta {
                continue;
            }
            if eb.is_dirty() {
                eb.external_change_pending = true;
                if conflict_index.is_none() {
                    conflict_index = Some(idx);
                }
            } else {
                let mut tmp_msg = String::new();
                if reload_from_disk(eb, highlighter, &mut tmp_msg) {
                    *ex_message = format!("\"{}\" auto-reloaded from disk", eb_path.display());
                } else {
                    *ex_message = tmp_msg;
                }
            }
        }
    }
    // Raise the conflict prompt last, only if nothing else is already
    // queued — we don't want to stomp on a quit-confirm in progress.
    if prompt.is_none() {
        if let Some(idx) = conflict_index {
            *prompt = Some(build_conflict_prompt(buffers, idx));
        }
    }
}

/// What the main loop should do after handling an `ExAction`. Quit
/// commands can ask the loop to exit. Prompts are raised directly via
/// the `prompt` out-param.
enum AfterAction {
    Continue,
    Quit,
}

/// Handle a buffer-list-level Ex action. Loads/switches/lists buffers,
/// runs saves, raises prompts for dirty closes, and signals quit-related
/// transitions back to the main loop.
fn dispatch_ex_action(
    action: ExAction,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    highlighter: &Highlighter,
    watcher: Option<&mut FileWatcher>,
    prompt: &mut Option<Prompt>,
    ex_message: &mut String,
) -> AfterAction {
    match action {
        ExAction::OpenFile(path) => {
            open_or_switch_to(
                buffers,
                current,
                &path,
                lsp_clients,
                highlighter,
                watcher,
                ex_message,
            );
            AfterAction::Continue
        }
        ExAction::NextBuffer => {
            if buffers.len() > 1 {
                *current = (*current + 1) % buffers.len();
            }
            AfterAction::Continue
        }
        ExAction::PrevBuffer => {
            if buffers.len() > 1 {
                *current = (*current + buffers.len() - 1) % buffers.len();
            }
            AfterAction::Continue
        }
        ExAction::ListBuffers => {
            let parts: Vec<String> = buffers
                .iter()
                .enumerate()
                .map(|(i, b)| {
                    let marker = if i == *current { "*" } else { " " };
                    format!("{}{} {}", marker, i + 1, b.display_name())
                })
                .collect();
            *ex_message = parts.join("  ");
            AfterAction::Continue
        }
        ExAction::Save => {
            save_current(&mut buffers[*current], false, ex_message);
            AfterAction::Continue
        }
        ExAction::ForceSave => {
            save_current(&mut buffers[*current], true, ex_message);
            AfterAction::Continue
        }
        ExAction::SaveAndQuit => {
            if !save_current(&mut buffers[*current], false, ex_message) {
                return AfterAction::Continue;
            }
            // After saving, the active buffer is clean — close it. If
            // that was the last buffer, exit the editor.
            match attempt_close_current(buffers, current) {
                CloseOutcome::Closed => AfterAction::Continue,
                CloseOutcome::QuitEditor => AfterAction::Quit,
                // Shouldn't happen: we just saved, so buffer is clean.
                CloseOutcome::Prompt => AfterAction::Continue,
            }
        }
        ExAction::Quit => match attempt_close_current(buffers, current) {
            CloseOutcome::Closed => AfterAction::Continue,
            CloseOutcome::QuitEditor => AfterAction::Quit,
            CloseOutcome::Prompt => {
                *prompt = Some(build_close_buffer_prompt(buffers, *current));
                AfterAction::Continue
            }
        },
        ExAction::ForceQuit => {
            let was_last = buffers.len() <= 1;
            let idx = *current;
            close_buffer_at(buffers, current, idx);
            if was_last {
                AfterAction::Quit
            } else {
                AfterAction::Continue
            }
        }
        ExAction::Reload => {
            reload_from_disk(&mut buffers[*current], highlighter, ex_message);
            AfterAction::Continue
        }
    }
}

fn format_key(k: &KeyEvent) -> String {
    let mut s = String::new();
    if k.mods.contains(Mods::CTRL) {
        s.push_str("C-");
    }
    if k.mods.contains(Mods::ALT) {
        s.push_str("A-");
    }
    if k.mods.contains(Mods::SHIFT) {
        s.push_str("S-");
    }
    match k.key {
        Key::Char(c) if (c.is_ascii_graphic() || c == ' ') => s.push_str(&format!("{:?}", c)),
        Key::Char(c) => s.push_str(&format!("U+{:04X}", c as u32)),
        Key::Enter => s.push_str("Enter"),
        Key::Tab => s.push_str("Tab"),
        Key::Backspace => s.push_str("Bksp"),
        Key::Esc => s.push_str("Esc"),
        Key::Up => s.push_str("Up"),
        Key::Down => s.push_str("Down"),
        Key::Left => s.push_str("Left"),
        Key::Right => s.push_str("Right"),
        Key::Home => s.push_str("Home"),
        Key::End => s.push_str("End"),
        Key::PageUp => s.push_str("PgUp"),
        Key::PageDown => s.push_str("PgDn"),
        Key::Insert => s.push_str("Ins"),
        Key::Delete => s.push_str("Del"),
        Key::F(n) => s.push_str(&format!("F{}", n)),
    }
    s
}

fn format_bytes(bytes: &[u8]) -> String {
    let mut s = String::new();
    for b in bytes {
        if b.is_ascii_graphic() || *b == b' ' {
            s.push(*b as char);
        } else {
            s.push_str(&format!("\\x{:02x}", b));
        }
    }
    s
}

#[allow(clippy::too_many_arguments)]
fn render_all(
    screen: &mut Screen,
    buffers: &[EditorBuffer],
    current: usize,
    mode: Mode,
    ex_input: &str,
    search_input: &str,
    search: &SearchState,
    ex_message: &str,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
    lsp_clients: &HashMap<&'static str, LspClient>,
    prompt: Option<&Prompt>,
) -> io::Result<()> {
    let cur = &buffers[current];
    let buffer_count = buffers.len();
    let dirty_marker = if cur.is_dirty() { " [+]" } else { "" };
    let conflict_marker = if cur.external_change_pending {
        " [disk!]"
    } else {
        ""
    };
    let buffer_label = if buffer_count > 1 {
        format!(
            "[{}/{}] {}{}{}",
            current + 1,
            buffer_count,
            cur.display_name(),
            dirty_marker,
            conflict_marker,
        )
    } else {
        format!(
            "{}{}{}",
            cur.display_name(),
            dirty_marker,
            conflict_marker
        )
    };
    let diagnostics: &[medit::lsp::Diagnostic] = match (cur.lang_id, cur.path.as_ref()) {
        (Some(lang), Some(p)) => match lsp::path_to_uri(p) {
            Ok(uri) => lsp_clients
                .get(lang)
                .map(|c| c.diagnostics_for(&uri))
                .unwrap_or(&[]),
            Err(_) => &[],
        },
        _ => &[],
    };
    render(
        screen,
        &cur.cached_bytes,
        &cur.line_starts,
        &cur.sels,
        &cur.flat_scopes,
        mode,
        cur.top_line,
        &buffer_label,
        ex_input,
        search_input,
        search,
        ex_message,
        last_key,
        last_bytes,
        diagnostics,
        prompt,
    )
}

#[allow(clippy::too_many_arguments)]
fn render(
    screen: &mut Screen,
    bytes: &[u8],
    line_starts: &[usize],
    sels: &Selections,
    scopes: &[ScopeId],
    mode: Mode,
    top_line: usize,
    buffer_label: &str,
    ex_input: &str,
    search_input: &str,
    search: &SearchState,
    ex_message: &str,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
    diagnostics: &[medit::lsp::Diagnostic],
    prompt: Option<&Prompt>,
) -> io::Result<()> {
    screen.begin_frame();
    let cols = screen.cols;
    let viewport_rows = screen.rows.saturating_sub(1);
    let primary = sels.primary();
    let head = primary.head;
    let start_byte = byte_at_line_cached(line_starts, top_line, bytes.len());

    // `line_starts.len()` is always at least 1 (we always seed with 0); the
    // total number of newline-terminated lines is `line_starts.len()` and
    // the visible-line count is the same (we count trailing partial lines).
    let total_lines = line_starts.len();
    let line_digits = total_lines.to_string().len() as u16;
    let gutter: u16 = if cols > line_digits + 2 {
        line_digits + 1
    } else {
        0
    };
    let content_cols = cols.saturating_sub(gutter);

    let sel_ranges: Vec<(usize, usize)> = sels
        .iter()
        .map(|s| {
            let lo = s.min();
            let hi = next_char_or_end(bytes, s.max());
            (lo, hi)
        })
        .collect();
    let in_any_selection =
        |i: usize| -> bool { sel_ranges.iter().any(|&(s, e)| i >= s && i < e) };
    let sel_min = primary.min();
    let sel_max = primary.max();

    let preview_matches: Vec<(usize, usize)> = match (mode, search.preview.as_ref()) {
        (Mode::Search, Some(re)) => all_matches(bytes, re),
        _ => Vec::new(),
    };
    let in_preview =
        |i: usize| -> bool { preview_matches.iter().any(|&(s, e)| i >= s && i < e) };

    // Pre-resolve diagnostic line/character → byte ranges using the
    // line-starts cache. LSP empty-range diagnostics (start == end) get
    // widened to one byte so they're still visible.
    let diag_ranges: Vec<(usize, usize, medit::lsp::DiagnosticSeverity, usize)> = diagnostics
        .iter()
        .enumerate()
        .filter_map(|(idx, d)| {
            let sl = *line_starts.get(d.start_line as usize)?;
            let el = line_starts
                .get(d.end_line as usize)
                .copied()
                .unwrap_or(bytes.len());
            let start = (sl + d.start_character as usize).min(bytes.len());
            let mut end = (el + d.end_character as usize).min(bytes.len());
            if end <= start {
                end = (start + 1).min(bytes.len());
            }
            Some((start, end, d.severity, idx))
        })
        .collect();
    let diag_ul = |i: usize| -> Option<&'static str> {
        diag_ranges
            .iter()
            .find(|&&(s, e, _, _)| i >= s && i < e)
            .map(|&(_, _, sev, _)| diag_ul_for(sev))
    };

    let mut row: u16 = 1;
    let mut col: u16 = 1;
    let mut cur_row: u16 = 1;
    let mut cur_col: u16 = 1;
    let mut i = start_byte;
    let mut current_lineno = top_line + 1;
    // Tracked SGR + cursor state.
    // - `style_fg/bg`: last emitted SGR fg/bg. Cells emit transition strings
    //   only when this changes.
    // - `cursor_at`: where the terminal cursor is *after* the most recent
    //   emit. If a cell wants to write at exactly that position we can skip
    //   the `\x1b[r;cH` escape entirely (terminal advances cursor with each
    //   printed glyph). Reset to `None` on any discontinuity (a skipped
    //   cell, row change without a line-number, etc.).
    let mut style_fg: Option<&'static str> = None;
    let mut style_bg: Option<&'static str> = None;
    let mut style_ul: Option<&'static str> = None;
    let mut cursor_at: Option<(u16, u16)> = None;
    if gutter > 0 && row <= viewport_rows {
        draw_lineno(screen, row, current_lineno, gutter);
        cursor_at = Some((row, gutter + 1));
    }

    loop {
        if i == head && row <= viewport_rows {
            cur_row = row;
            cur_col = col.max(1).min(content_cols.max(1));
        }
        if i >= bytes.len() || row > viewport_rows {
            break;
        }
        let b = match bytes.get(i) {
            Some(&b) => b,
            None => break,
        };
        let show_selection = matches!(mode, Mode::Normal | Mode::Search);
        let cursor_on_buffer = matches!(mode, Mode::Normal | Mode::Insert);
        let in_sel =
            show_selection && in_any_selection(i) && !(cursor_on_buffer && i == head);
        let in_match = !in_sel && in_preview(i);
        let bg: Option<&'static str> = if in_sel {
            Some(SEL_BG)
        } else if in_match {
            Some(MATCH_BG)
        } else {
            None
        };
        let scope = scopes.get(i).copied().unwrap_or(ScopeId::Default);
        let fg_seq: Option<&'static str> = if scope == ScopeId::Default {
            None
        } else {
            Some(theme::fg_for_scope(scope))
        };
        let ul_seq: Option<&'static str> = diag_ul(i);
        match b {
            b'\n' => {
                row = row.saturating_add(1);
                col = 1;
                current_lineno += 1;
                if gutter > 0 && row <= viewport_rows {
                    draw_lineno(screen, row, current_lineno, gutter);
                    cursor_at = Some((row, gutter + 1));
                    style_fg = None;
                    style_bg = None;
                    style_ul = None;
                } else {
                    cursor_at = None;
                }
                i += 1;
            }
            b'\r' => {
                i += 1;
            }
            b'\t' => {
                let advance = 4 - ((col as usize - 1) % 4);
                if (bg.is_some() || ul_seq.is_some()) && col <= content_cols {
                    // Tabs only need a visible body when there's something
                    // to paint (selection bg, search highlight, or a
                    // diagnostic underline); otherwise we just advance.
                    const SPACES: &[u8; 4] = b"    ";
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        &mut style_ul,
                        row,
                        col + gutter,
                        advance as u16,
                        fg_seq,
                        bg,
                        ul_seq,
                        &SPACES[..advance],
                    );
                } else {
                    cursor_at = None;
                }
                col = col.saturating_add(advance as u16);
                i += 1;
            }
            c if c < 0x20 => {
                let letter = c + 0x40;
                let body = [b'^', letter];
                if col <= content_cols {
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        &mut style_ul,
                        row,
                        col + gutter,
                        2,
                        fg_seq,
                        bg,
                        ul_seq,
                        &body,
                    );
                } else {
                    cursor_at = None;
                }
                col = col.saturating_add(2);
                i += 1;
            }
            _ => {
                let n = utf8_len(b);
                let end = (i + n).min(bytes.len());
                if col <= content_cols {
                    let glyph = bytes.get(i..end).unwrap_or(b"?");
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        &mut style_ul,
                        row,
                        col + gutter,
                        1,
                        fg_seq,
                        bg,
                        ul_seq,
                        glyph,
                    );
                } else {
                    cursor_at = None;
                }
                col = col.saturating_add(1);
                i = end;
            }
        }
    }

    // End of buffer rendering — reset SGR so the status bar starts clean.
    if style_fg.is_some() || style_bg.is_some() || style_ul.is_some() {
        screen.append_raw("\x1b[0m");
    }

    // Diagnostic popup: if the cursor sits inside a diagnostic range,
    // render a bordered box anchored just below (or above) the cursor's
    // line with the diagnostic's message.
    let hovered_diag = diag_ranges
        .iter()
        .find(|&&(s, e, _, _)| head >= s && head < e)
        .map(|&(_, _, _, idx)| &diagnostics[idx]);
    if let Some(d) = hovered_diag {
        draw_diag_popup(screen, d, cur_row, cur_col, gutter, cols, viewport_rows);
    }

    let primary_size = sel_max.saturating_sub(sel_min) + if bytes.is_empty() { 0 } else { 1 };
    let multi_label = if sels.len() > 1 {
        format!("{} sels · ", sels.len())
    } else {
        String::new()
    };
    let key_str = last_key.map(format_key).unwrap_or_else(|| "-".to_string());
    let bytes_str = if last_bytes.is_empty() {
        "-".to_string()
    } else {
        format_bytes(last_bytes)
    };
    let abs_line = line_index_cached(line_starts, head) + 1;
    let mode_str = match mode {
        Mode::Normal => "N",
        Mode::Insert => "I",
        Mode::Ex => "X",
        Mode::Search => "S",
    };
    let cols_usize = cols as usize;
    let is_prompt = matches!(mode, Mode::Ex | Mode::Search);

    let viewport_cur_col = cur_col.saturating_add(gutter);
    let (status, final_cur_row, final_cur_col) = if is_prompt {
        let (prefix, input) = if mode == Mode::Ex {
            (":", ex_input)
        } else {
            ("/", search_input)
        };
        let prompt = format!("{}{}", prefix, input);
        let col_pos = (prompt.chars().count() as u16).saturating_add(1).max(1);
        (prompt, screen.rows, col_pos)
    } else if !ex_message.is_empty() {
        (format!(" {} ", ex_message), cur_row, viewport_cur_col)
    } else {
        let s = format!(
            " [{}] {} · ln {} col {} · {}sel {}b · last:{} raw:{} ",
            mode_str,
            buffer_label,
            abs_line,
            cur_col,
            multi_label,
            primary_size,
            key_str,
            bytes_str
        );
        (s, cur_row, viewport_cur_col)
    };

    let mut padded: String = status.chars().take(cols_usize).collect();
    while padded.chars().count() < cols_usize {
        padded.push(' ');
    }
    let status_text = if is_prompt {
        padded
    } else {
        format!("\x1b[7m{}\x1b[0m", padded)
    };
    screen.write_at(screen.rows, 1, &status_text);

    // Modal prompt overlays everything else, including the diag popup
    // and status bar. Drawn last so its bytes are the most recent in the
    // frame and visually win.
    if let Some(p) = prompt {
        draw_prompt(screen, p, screen.rows, cols);
    }

    let block_cursor = mode == Mode::Normal;
    screen.set_cursor_shape(block_cursor);
    screen.end_frame(final_cur_row, final_cur_col)
}
