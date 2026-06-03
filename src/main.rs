mod term;

use std::collections::HashMap;
use std::io::{self, Read};
use std::path::{Path, PathBuf};
use std::sync::mpsc;
use std::thread;
use std::time::{Duration, Instant};

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
use medit::jumps::{JumpEntry, JumpList};
use medit::lsp::{self, CompletionTrigger, LspClient, LspEvent, Message as LspMessage};
use medit::theme::{self, ScopeId};
use medit::trace;
use medit::watch::{DiskMeta, FileWatcher};
use term::{RawMode, Screen};

/// Tagged message into the main loop. Every wake-up of the editor —
/// keypress, terminal resize, LSP message, animation tick — arrives here
/// so the loop has a single uniform `recv`.
enum MainEvent {
    /// One read-burst worth of stdin bytes.
    Input(Vec<u8>),
    /// SIGWINCH (Unix) or a console-size-poll change (Windows).
    Resize,
    /// A parsed LSP message tagged with the language id of the client
    /// it came from. Funneled through `LspClient::handle_message` to
    /// produce editor-facing events.
    LspMessage(&'static str, LspMessage),
    /// Periodic animation tick. Only consumed when something is animating
    /// (currently: the LSP spinner).
    Tick,
}

/// Per-outstanding-request metadata held by the editor. Lets us resolve
/// an `LspEvent` back to the buffer/version/UI-state that originated the
/// request, and drop the response if the buffer has moved on (edits)
/// since then.
struct RequestMeta {
    /// Path of the buffer that originated the request. Used to find the
    /// buffer at response time (buffer indices can shuffle).
    buf_path: Option<PathBuf>,
    /// `buffer.version()` at send time. Stale responses (different
    /// version now) are dropped per the v1 design.
    buffer_version: u64,
    /// Goto-definition records a pre-jump location so `Ctrl+O` returns
    /// here. We capture it at request time, not response time, because
    /// the user may have already moved on by the time the reply arrives.
    pre_jump: Option<JumpEntry>,
}

/// Per-language outstanding-request tables. Indexed first by language id
/// (matching `lsp_clients`), then by request id.
type Outstanding = HashMap<&'static str, HashMap<u64, RequestMeta>>;

/// ASCII spinner glyphs, rotated through on each `MainEvent::Tick` while
/// any LSP request is outstanding.
const SPINNER: &[char] = &['|', '/', '-', '\\'];

/// Time after the most recent qualifying keystroke before a queued
/// completion request is actually sent. Picked to balance LSP traffic
/// against perceived latency.
const COMPLETION_DEBOUNCE: Duration = Duration::from_millis(50);

/// Editor-side completion state. Tracks the in-flight request id, the
/// returned items, the current filter prefix, the highlighted item,
/// and any pending (debounced) trigger waiting to fire.
struct CompletionUi {
    /// Latest in-flight request id; stale responses (id mismatch) are
    /// dropped on arrival.
    request_id: Option<u64>,
    /// Byte offset where the replacement starts. Fixed at trigger time
    /// — the suffix grows from `anchor` to the cursor as the user
    /// types more characters.
    anchor: usize,
    /// Current `[anchor..cursor]` text used for client-side filtering.
    /// Kept in sync with the buffer on every insert-mode keystroke.
    prefix: String,
    /// Items from the most recent matched response, already
    /// `(sortText, label)`-sorted by `completion::parse_response`.
    items: Vec<medit::completion::CompletionItem>,
    /// Indices into `items` matching `prefix` (case-insensitive
    /// prefix match). The popup walks `filtered` in order.
    filtered: Vec<usize>,
    /// Selected index within `filtered`.
    selected: usize,
    /// Server flagged the response as incomplete. v1 still uses
    /// client-side filtering; we just record the flag for later
    /// behavior.
    is_incomplete: bool,
    /// Debounced trigger waiting to fire. `None` when nothing is
    /// queued (no recent trigger, or already fired).
    pending: Option<PendingTrigger>,
    /// `true` while the popup is showing filesystem path completions
    /// (opened with `Alt-/`). Path sessions accept, refilter, and descend
    /// directories through their own logic rather than the word/LSP path.
    is_path_session: bool,
    /// When the path is being typed inside a string literal, the opening
    /// quote char — used to auto-close the string when a file is accepted.
    path_quote: Option<char>,
}

struct PendingTrigger {
    anchor: usize,
    trigger: CompletionTrigger,
    deadline: Instant,
}

impl CompletionUi {
    fn new() -> Self {
        Self {
            request_id: None,
            anchor: 0,
            prefix: String::new(),
            items: Vec::new(),
            filtered: Vec::new(),
            selected: 0,
            is_incomplete: false,
            pending: None,
            is_path_session: false,
            path_quote: None,
        }
    }

    fn is_visible(&self) -> bool {
        !self.filtered.is_empty()
    }

    /// Populate the popup synchronously (buffer-word source — no LSP round
    /// trip). Sets the replacement anchor/prefix and filters the supplied
    /// items immediately. `is_incomplete` is false: the full candidate set
    /// is known, so an empty filter means the session should close.
    fn set_items(
        &mut self,
        items: Vec<medit::completion::CompletionItem>,
        anchor: usize,
        prefix: String,
    ) {
        self.request_id = None;
        self.is_incomplete = false;
        self.is_path_session = false;
        self.path_quote = None;
        self.anchor = anchor;
        self.filtered = medit::completion::filter_items(&items, &prefix);
        self.prefix = prefix;
        self.items = items;
        self.selected = 0;
    }

    /// Populate the popup with filesystem path items (the `Alt-/` source)
    /// and flag the session so subsequent keys route through path logic.
    fn set_path_items(&mut self, pc: medit::path_complete::PathCompletion) {
        let quote = pc.quote;
        self.set_items(pc.items, pc.anchor, pc.prefix);
        self.is_path_session = true;
        self.path_quote = quote;
    }

    /// Clear all state — popup closes, in-flight request is forgotten
    /// (its eventual response will be dropped on id mismatch).
    fn close(&mut self) {
        self.request_id = None;
        self.items.clear();
        self.filtered.clear();
        self.selected = 0;
        self.is_incomplete = false;
        self.pending = None;
        self.prefix.clear();
        self.is_path_session = false;
        self.path_quote = None;
    }
}

/// Spawn the thread that reads raw bytes from stdin in a loop and
/// forwards each read-burst onto `tx` as `MainEvent::Input`. SIGWINCH
/// interrupts the blocking read with `EINTR`; the thread also drains the
/// resize flag set by `term::install_sigwinch_handler` so the resize
/// becomes visible to the main loop promptly.
fn spawn_stdin_thread(tx: mpsc::Sender<MainEvent>) {
    thread::spawn(move || {
        let stdin = io::stdin();
        let mut handle = stdin.lock();
        let mut io_buf = [0u8; 64];
        loop {
            // Drain a pending resize first; SIGWINCH may have set the
            // flag while the previous read was returning.
            if term::take_resize_flag() && tx.send(MainEvent::Resize).is_err() {
                break;
            }
            match handle.read(&mut io_buf) {
                Ok(0) => break,
                Ok(n) => {
                    if tx.send(MainEvent::Input(io_buf[..n].to_vec())).is_err() {
                        break;
                    }
                }
                Err(e) if e.kind() == io::ErrorKind::Interrupted => {
                    // SIGWINCH or similar — loop to drain the flag and
                    // retry the read.
                    continue;
                }
                Err(_) => break,
            }
        }
    });
}

/// Spawn the animation/heartbeat thread. Fires `MainEvent::Tick` every
/// 100ms so the main loop can advance the LSP spinner during idle, and
/// also forwards Windows-side resize-poll events (where SIGWINCH isn't
/// available) by draining the same `take_resize_flag` state.
fn spawn_tick_thread(tx: mpsc::Sender<MainEvent>) {
    thread::spawn(move || {
        loop {
            thread::sleep(Duration::from_millis(100));
            // On Windows the install_sigwinch_handler shim spawns a
            // size-poll thread that flips the same flag. Drain it here
            // so resize doesn't wait for the next keystroke.
            if term::take_resize_flag() && tx.send(MainEvent::Resize).is_err() {
                break;
            }
            if tx.send(MainEvent::Tick).is_err() {
                break;
            }
        }
    });
}

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
    /// Number of visual columns scrolled off the left edge. The horizontal
    /// analog of `top_line`: the whole viewport shifts together so the
    /// cursor stays visible on long lines (no soft-wrap). Recomputed each
    /// frame from the cursor's visual column by `ensure_visible_horizontal`.
    left_col: usize,
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
            left_col: 0,
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

/// Width of the line-number gutter (including its trailing space) for a
/// buffer with `total_lines` lines on a terminal `cols` wide. Single source
/// of truth shared by the renderer and the horizontal-scroll calculation so
/// they always agree on `content_cols`. Returns 0 when the terminal is too
/// narrow to afford a gutter.
fn gutter_for(total_lines: usize, cols: u16) -> u16 {
    let line_digits = total_lines.to_string().len() as u16;
    if cols > line_digits + 2 {
        line_digits + 1
    } else {
        0
    }
}

/// Visual column (1-based, in screen cells) of byte offset `head` within
/// the line starting at `line_start`. Mirrors the renderer's advance rules
/// exactly: tabs round up to the next multiple of 4, control bytes take two
/// cells (`^X`), every other character takes one. Used to drive horizontal
/// scrolling and the status-bar column readout.
fn visual_col_at(bytes: &[u8], line_start: usize, head: usize) -> u16 {
    let mut col: u16 = 1;
    let mut i = line_start;
    while i < head {
        match bytes.get(i) {
            None | Some(b'\n') => break,
            Some(b'\r') => i += 1,
            Some(b'\t') => {
                let advance = 4 - ((col as usize - 1) % 4);
                col = col.saturating_add(advance as u16);
                i += 1;
            }
            Some(&c) if c < 0x20 => {
                col = col.saturating_add(2);
                i += 1;
            }
            Some(&b) => {
                col = col.saturating_add(1);
                i += utf8_len(b).max(1);
            }
        }
    }
    col
}

/// Adjust `left_col` so the cursor's visual column stays inside the visible
/// window `[left_col+1, left_col+content_cols]`. Only scrolls when the
/// cursor would actually fall outside it, so a line that fits the viewport
/// never scrolls (and the view snaps back to column 0 on short lines).
fn ensure_visible_horizontal(
    head_vcol: u16,
    line_end_vcol: u16,
    left_col: &mut usize,
    content_cols: u16,
) {
    if content_cols == 0 {
        return;
    }
    let v = head_vcol as usize;
    let cc = content_cols as usize;
    if v <= *left_col {
        *left_col = v.saturating_sub(1);
    } else if v > *left_col + cc {
        *left_col = v - cc;
    }
    // Never scroll past the end of the current line into empty space. This
    // also snaps the view back toward column 0 when the whole line fits
    // (e.g. moving from a long line down to a short one), instead of leaving
    // the cursor stranded against the left edge showing only the line's tail.
    let max_left = (line_end_vcol as usize).saturating_sub(cc);
    *left_col = (*left_col).min(max_left);
}

/// Clip a run of `width` cells starting at 1-based visual column `col` to
/// the horizontal window `[left_col+1, left_col+content_cols]`. Returns the
/// 1-based screen content column to draw at, the number of visible cells,
/// and how many leading cells were clipped off (so a per-cell body can be
/// sliced); `None` when the run is entirely scrolled out of view.
fn clip_run(col: u16, width: u16, left_col: u16, content_cols: u16) -> Option<(u16, u16, usize)> {
    let start = col as u32;
    let end = start + width.max(1) as u32 - 1; // inclusive, 1-based
    let win_lo = left_col as u32 + 1;
    let win_hi = left_col as u32 + content_cols as u32;
    let lo = start.max(win_lo);
    let hi = end.min(win_hi);
    if hi < lo {
        return None;
    }
    let screen_col = (lo - left_col as u32) as u16; // 1-based within content
    let vis_width = (hi - lo + 1) as u16;
    let clipped_left = (lo - start) as usize;
    Some((screen_col, vis_width, clipped_left))
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

/// LSP hover popup. Wraps `text` into lines, draws a bordered box near
/// the cursor (below if there's room, above otherwise) with a cyan border
/// so it visually parallels the diag popup without being mistaken for one.
/// Render the completion popup. Anchored at the *replacement-start*
/// screen column (not the cursor), so as the user types more
/// characters of the prefix the popup stays put. Shows up to 8 items
/// with the selected row reverse-video-highlighted; flips above the
/// cursor when the box would overflow the viewport.
fn draw_completion_popup(
    screen: &mut Screen,
    comp: &CompletionUi,
    bytes: &[u8],
    line_starts: &[usize],
    cursor_byte: usize,
    cur_row: u16,
    cur_col: u16,
    gutter: u16,
    cols: u16,
    viewport_rows: u16,
) {
    const MAX_ROWS: usize = 8;
    const BORDER: &str = "\x1b[38;5;139m"; // muted purple
    const SEL: &str = "\x1b[7m"; // reverse video for the selected row

    if comp.filtered.is_empty() {
        return;
    }

    // Anchor the box at the byte where the completion replacement
    // begins. On the normal "user typed into one line" path, anchor
    // and cursor share a line and the column delta is just the
    // visible width of the typed prefix.
    let cursor_line = line_index_cached(line_starts, cursor_byte);
    let anchor_line = line_index_cached(line_starts, comp.anchor);
    let anchor_text_col = if anchor_line == cursor_line && comp.anchor <= cursor_byte {
        let line_start = byte_at_line_cached(line_starts, cursor_line, bytes.len());
        let cur_dc = display_col(bytes, line_start, cursor_byte);
        let anch_dc = display_col(bytes, line_start, comp.anchor);
        let delta: usize = cur_dc.saturating_sub(anch_dc);
        cur_col.saturating_sub(delta as u16).max(1)
    } else {
        cur_col
    };

    let take = comp.filtered.len().min(MAX_ROWS);
    // Scroll the visible window so the highlighted row is in view.
    let last_window_start = comp.filtered.len().saturating_sub(take);
    let win_start = comp
        .selected
        .saturating_sub(MAX_ROWS.saturating_sub(1))
        .min(last_window_start);

    // Compute text-area width: max of (label-width + 2 + detail-width)
    // over visible rows, then clipped so the box fits in the terminal
    // and labels stay readable.
    let mut text_w: usize = 0;
    for &i in comp.filtered[win_start..(win_start + take)].iter() {
        let it = &comp.items[i];
        let mut w = it.label.chars().count();
        if let Some(d) = it.detail.as_deref() {
            if !d.is_empty() {
                w += 2 + d.chars().count();
            }
        }
        text_w = text_w.max(w);
    }
    // Bound width: never exceed the terminal, and cap at 60 columns so
    // long detail strings don't make the box absurd.
    let max_text_w = (cols as usize).saturating_sub(6).min(60);
    text_w = text_w.min(max_text_w).max(8);

    let inner_w = text_w + 2; // one space pad on each side of text
    let box_w: u16 = inner_w as u16 + 2; // plus the two vertical borders
    let box_h: u16 = take as u16 + 2; // plus top/bottom borders

    // Prefer below the cursor; flip above if it would clip past the
    // last viewport row. `viewport_rows` is the count of buffer-content
    // rows (the status row sits at `viewport_rows + 1`).
    let mut top: u16 = cur_row.saturating_add(1);
    if top + box_h - 1 > viewport_rows {
        top = cur_row.saturating_sub(box_h);
        if top == 0 {
            top = 1;
        }
    }

    let anchor_screen_col = anchor_text_col.saturating_add(gutter);
    let mut left: u16 = anchor_screen_col.saturating_sub(1).max(1);
    if box_w > 0 && left + box_w - 1 > cols {
        left = cols.saturating_sub(box_w - 1).max(1);
    }

    // Top border.
    let mut top_str = String::with_capacity(box_w as usize * 3);
    top_str.push_str(BORDER);
    top_str.push('┌');
    for _ in 0..inner_w {
        top_str.push('─');
    }
    top_str.push('┐');
    top_str.push_str("\x1b[0m");
    screen.write_at(top, left, &top_str);

    // Body rows.
    for k in 0..take {
        let it = &comp.items[comp.filtered[win_start + k]];
        let is_selected = (win_start + k) == comp.selected;
        let label_chars = it.label.chars().count();
        let detail_str = it
            .detail
            .as_deref()
            .filter(|s| !s.is_empty())
            .unwrap_or("");
        let detail_chars = detail_str.chars().count();
        // Fit label + "  " + detail into text_w columns. If the
        // combined width overflows, drop the detail and truncate
        // the label.
        let (lab, det) = if detail_chars > 0 && label_chars + 2 + detail_chars <= text_w {
            (it.label.clone(), Some(detail_str.to_string()))
        } else {
            let truncated: String = it.label.chars().take(text_w).collect();
            (truncated, None)
        };

        let mut row_str = String::with_capacity(box_w as usize * 4);
        row_str.push_str(BORDER);
        row_str.push('│');
        row_str.push_str("\x1b[0m");
        if is_selected {
            row_str.push_str(SEL);
        }
        // Left inner pad.
        row_str.push(' ');
        // Body text: label, then (if room) two spaces and detail.
        let mut written: usize = 0;
        for ch in lab.chars() {
            row_str.push(ch);
            written += 1;
        }
        if let Some(d) = det.as_deref() {
            row_str.push(' ');
            row_str.push(' ');
            written += 2;
            for ch in d.chars() {
                row_str.push(ch);
                written += 1;
            }
        }
        // Right pad up to text_w.
        for _ in written..text_w {
            row_str.push(' ');
        }
        // Right inner pad.
        row_str.push(' ');
        if is_selected {
            row_str.push_str("\x1b[0m");
        }
        row_str.push_str(BORDER);
        row_str.push('│');
        row_str.push_str("\x1b[0m");
        screen.write_at(top + 1 + k as u16, left, &row_str);
    }

    // Bottom border.
    let mut bot_str = String::with_capacity(box_w as usize * 3);
    bot_str.push_str(BORDER);
    bot_str.push('└');
    for _ in 0..inner_w {
        bot_str.push('─');
    }
    bot_str.push('┘');
    bot_str.push_str("\x1b[0m");
    screen.write_at(top + box_h - 1, left, &bot_str);
}

fn draw_hover_popup(
    screen: &mut Screen,
    text: &str,
    cur_row: u16,
    cur_col: u16,
    gutter: u16,
    cols: u16,
    viewport_rows: u16,
) {
    const BORDER: &str = "\x1b[38;5;110m"; // pale cyan
    let max_text: usize = (cols as usize).saturating_sub(6).max(20).min(80);
    let lines = wrap_text(text, max_text, 16);
    if lines.is_empty() {
        return;
    }
    draw_box_at_cursor(
        screen,
        &lines,
        cur_row,
        cur_col,
        gutter,
        cols,
        viewport_rows,
        BORDER,
    );
}

/// Word-wrap `text` to `max_text` columns. Caps at `max_rows` lines,
/// trimming the last with an ellipsis. Returns one entry per visible line.
fn wrap_text(text: &str, max_text: usize, max_rows: usize) -> Vec<String> {
    let mut lines: Vec<String> = Vec::new();
    for raw_line in text.lines() {
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
    if lines.len() > max_rows {
        lines.truncate(max_rows);
        if let Some(last) = lines.last_mut() {
            if last.chars().count() > max_text.saturating_sub(1) {
                let cut = last
                    .char_indices()
                    .nth(max_text.saturating_sub(1))
                    .map(|(i, _)| i)
                    .unwrap_or(last.len());
                last.truncate(cut);
            }
            last.push('…');
        }
    }
    lines
}

/// Render a bordered box of `lines` anchored to the cursor. Prefers
/// placing the box one row below the cursor; flips above if it would
/// clip past the viewport. Used by both diag and hover popups.
fn draw_box_at_cursor(
    screen: &mut Screen,
    lines: &[String],
    cur_row: u16,
    cur_col: u16,
    gutter: u16,
    cols: u16,
    viewport_rows: u16,
    border: &str,
) {
    let width_text = lines.iter().map(|l| l.chars().count()).max().unwrap_or(0);
    let inner_w = width_text + 2;
    let box_w = inner_w as u16 + 2;
    let box_h = lines.len() as u16 + 2;

    let mut top: u16 = cur_row.saturating_add(1);
    if top + box_h - 1 > viewport_rows {
        top = cur_row.saturating_sub(box_h);
        if top == 0 {
            top = 1;
        }
    }
    let anchor_col = cur_col.saturating_add(gutter);
    let mut left: u16 = anchor_col.saturating_sub(1).max(1);
    if left + box_w - 1 > cols {
        left = cols.saturating_sub(box_w - 1).max(1);
    }

    let mut top_line = String::with_capacity(box_w as usize * 3);
    top_line.push_str(border);
    top_line.push('┌');
    for _ in 0..inner_w {
        top_line.push('─');
    }
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
        for _ in 0..pad {
            row_str.push(' ');
        }
        row_str.push_str(border);
        row_str.push('│');
        row_str.push_str("\x1b[0m");
        screen.write_at(top + 1 + i as u16, left, &row_str);
    }

    let mut bot_line = String::with_capacity(box_w as usize * 3);
    bot_line.push_str(border);
    bot_line.push('└');
    for _ in 0..inner_w {
        bot_line.push('─');
    }
    bot_line.push('┘');
    bot_line.push_str("\x1b[0m");
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

/// Recompute scroll/highlight for the current buffer and draw one frame.
/// Factored out of the main loop so input coalescing can call it from a
/// single place — every queued event is processed first, then this renders
/// exactly once, which is what keeps held-key repeats from piling up a
/// backlog of (synchronized-output) frames the terminal plays back behind
/// the cursor.
#[allow(clippy::too_many_arguments)]
fn present(
    screen: &mut Screen,
    buffers: &mut [EditorBuffer],
    current: usize,
    highlighter: &Highlighter,
    mode: Mode,
    ex_input: &str,
    search_input: &str,
    search_state: &SearchState,
    ex_message: &str,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
    lsp_clients: &HashMap<&'static str, LspClient>,
    prompt: Option<&Prompt>,
    hover: Option<&str>,
    spinner_idx: usize,
    comp: &CompletionUi,
) -> io::Result<()> {
    let viewport_rows = screen.rows.saturating_sub(1) as usize;
    {
        let cur = &mut buffers[current];
        refresh_bytes_cache(cur);
        // Re-parse + rebuild flat_scopes when the buffer has moved.
        reparse_and_highlight(cur, highlighter);
        let head = cur.sels.primary().head;
        ensure_visible_indexed(&cur.line_starts, head, &mut cur.top_line, viewport_rows);
        // Horizontal scroll: keep the cursor's visual column on screen.
        let gutter = gutter_for(cur.line_starts.len(), screen.cols);
        let content_cols = screen.cols.saturating_sub(gutter);
        let head_line = line_index_cached(&cur.line_starts, head);
        let line_start = cur.line_starts.get(head_line).copied().unwrap_or(0);
        let line_end = cur
            .line_starts
            .get(head_line + 1)
            .copied()
            .unwrap_or(cur.cached_bytes.len());
        let head_vcol = visual_col_at(&cur.cached_bytes, line_start, head);
        let line_end_vcol = visual_col_at(&cur.cached_bytes, line_start, line_end);
        ensure_visible_horizontal(head_vcol, line_end_vcol, &mut cur.left_col, content_cols);
    }
    let spinner_glyph = if lsp_clients.values().any(|c| c.has_outstanding()) {
        Some(SPINNER[spinner_idx % SPINNER.len()])
    } else {
        None
    };
    render_all(
        screen,
        buffers,
        current,
        mode,
        ex_input,
        search_input,
        search_state,
        ex_message,
        last_key,
        last_bytes,
        lsp_clients,
        prompt,
        hover,
        spinner_glyph,
        Some(comp),
    )
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
    let mut pending_replace = false;
    let mut pending_lsp_action: Option<LspAction> = None;
    let mut pending_jump_action: Option<medit::core::JumpAction> = None;
    let mut pending_ex_action: Option<ExAction> = None;
    let mut jumps = JumpList::new();
    let mut search_input = String::new();
    let mut search_state = SearchState::default();
    let mut last_key: Option<KeyEvent> = None;
    let mut last_bytes: Vec<u8> = Vec::new();
    // Active modal prompt, if any. When `Some`, the next keypress is
    // consumed by `handle_prompt` instead of being routed to the active
    // mode, and the prompt box overlays the editor view.
    let mut prompt: Option<Prompt> = None;
    // LSP hover text to display in a popup near the cursor. Set by `gh`
    // (and similar) and cleared on the next normal-mode keystroke.
    let mut hover: Option<String> = None;

    // LSP. We spawn one server per language, on demand, the first time we
    // open a file of that language (initial buffer or via `:e`). All
    // buffers of a given language share the same client.
    let mut lsp_clients: HashMap<&'static str, LspClient> = HashMap::new();
    // Per-language table of in-flight requests. Indexed first by lang_id
    // (matching `lsp_clients`), then by the LSP request id. Populated by
    // `dispatch_lsp` and drained by `handle_lsp_event` as responses
    // arrive.
    let mut outstanding: Outstanding = HashMap::new();
    // Spinner cursor — advanced once per `MainEvent::Tick` while at least
    // one LSP request is outstanding.
    let mut spinner_idx: usize = 0;
    // Completion state for the current insert-mode session.
    let mut comp = CompletionUi::new();

    let _raw = RawMode::enable()?;
    let mut screen = Screen::enter()?;
    term::install_sigwinch_handler()?;

    // Unified event channel. All wake sources — stdin, SIGWINCH, LSP
    // reader threads, animation ticks — funnel through this channel so
    // the main loop has a single uniform `recv`.
    let (main_tx, main_rx) = mpsc::channel::<MainEvent>();
    spawn_stdin_thread(main_tx.clone());
    spawn_tick_thread(main_tx.clone());

    // LSP spawn happens after `main_tx` exists so the new client's reader
    // thread can forward into the unified channel.
    if let Some(p) = buffers[0].path.clone() {
        maybe_start_lsp_and_open(&mut lsp_clients, &p, &mut buffers[0], &main_tx);
    }

    // Populate cache before the first frame; subsequent frames refresh in
    // the main loop.
    refresh_bytes_cache(&mut buffers[current]);
    present(
        &mut screen,
        &mut buffers,
        current,
        &highlighter,
        mode,
        &ex_input,
        &search_input,
        &search_state,
        &ex_message,
        last_key.as_ref(),
        &last_bytes,
        &lsp_clients,
        prompt.as_ref(),
        hover.as_deref(),
        spinner_idx,
        &comp,
    )?;

    let mut parser = Parser::new();
    // Coalesced rendering: events are processed as fast as they arrive and
    // mark the screen dirty; we only paint once the event queue drains.
    // Holding a key (which streams a burst of `Input` events) thus collapses
    // into a single frame per idle moment instead of one frame per keystroke,
    // so the display can't fall behind the cursor.
    let mut dirty = false;
    let mut pending_handle_ns: u64 = 0;

    loop {
        let event = match main_rx.try_recv() {
            Ok(e) => e,
            Err(mpsc::TryRecvError::Empty) => {
                // Caught up on input — flush a pending frame, then block.
                if dirty {
                    let render_start = trace::tic();
                    present(
                        &mut screen,
                        &mut buffers,
                        current,
                        &highlighter,
                        mode,
                        &ex_input,
                        &search_input,
                        &search_state,
                        &ex_message,
                        last_key.as_ref(),
                        &last_bytes,
                        &lsp_clients,
                        prompt.as_ref(),
                        hover.as_deref(),
                        spinner_idx,
                        &comp,
                    )?;
                    let render_ns = trace::toc(render_start);
                    trace::emit_frame(
                        pending_handle_ns + render_ns,
                        pending_handle_ns,
                        render_ns,
                        buffers[current].buffer.len(),
                    );
                    pending_handle_ns = 0;
                    dirty = false;
                }
                match main_rx.recv() {
                    Ok(e) => e,
                    // All senders dropped — shouldn't happen unless every
                    // spawned thread has died, but treat as graceful exit.
                    Err(_) => break,
                }
            }
            Err(mpsc::TryRecvError::Disconnected) => break,
        };
        let handle_start = trace::tic();
        let mut should_render = false;

        match event {
            MainEvent::Resize => {
                screen.refresh_size()?;
                let viewport_rows = screen.rows.saturating_sub(1) as usize;
                {
                    let cur = &mut buffers[current];
                    refresh_bytes_cache(cur);
                    let head = cur.sels.primary().head;
                    ensure_visible_indexed(
                        &cur.line_starts,
                        head,
                        &mut cur.top_line,
                        viewport_rows,
                    );
                }
                should_render = true;
            }
            MainEvent::LspMessage(lang, msg) => {
                let events = if let Some(client) = lsp_clients.get_mut(lang) {
                    client.handle_message(msg)
                } else {
                    Vec::new()
                };
                for ev in events {
                    handle_lsp_event(
                        lang,
                        ev,
                        &mut outstanding,
                        &mut buffers,
                        &mut current,
                        &mut lsp_clients,
                        &highlighter,
                        watcher.as_mut(),
                        &mut hover,
                        &mut jumps,
                        &mut ex_message,
                        &mut comp,
                        &main_tx,
                    );
                }
                should_render = true;
            }
            MainEvent::Tick => {
                let busy = lsp_clients.values().any(|c| c.has_outstanding());
                if busy {
                    spinner_idx = spinner_idx.wrapping_add(1);
                    should_render = true;
                }
            }
            MainEvent::Input(bytes) => {
                last_bytes = bytes.clone();
                parser.feed(&bytes);
                // After consuming all complete events from this read
                // burst, fall back to `flush()` so a lone trailing ESC
                // byte (Esc key in non-kitty terminals) resolves to
                // `Key::Esc` instead of waiting indefinitely for a
                // follow-up byte that never arrives.
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
                // Hover popup is informational; dismiss on the next
                // keystroke just like the status-bar message.
                hover = None;
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
                        &mut pending_replace,
                        &mut search_state,
                        &mut pending_lsp_action,
                        &mut pending_jump_action,
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
                            &mut outstanding,
                            &mut ex_message,
                        );
                    }
                    if let Some(action) = pending_jump_action.take() {
                        dispatch_jump(
                            action,
                            &mut jumps,
                            &mut buffers,
                            &mut current,
                            &mut lsp_clients,
                            &highlighter,
                            watcher.as_mut(),
                            &mut ex_message,
                            &main_tx,
                        );
                    }
                }
                Mode::Insert => {
                    let cur = &mut buffers[current];
                    // First: if the popup is showing, give it a shot
                    // at consuming the key (Tab/Enter accept, C-n/C-p
                    // and Up/Down navigate, Esc dismiss). Any of those
                    // skip the normal insert-mode handler so the key
                    // doesn't double-act (Tab inserting a tab after
                    // accepting, Esc exiting insert after dismissing).
                    match handle_completion_keys(&mut comp, cur, k) {
                        CompletionKeyOutcome::NotIntercepted => {}
                        CompletionKeyOutcome::InterceptedNoChange => {
                            // Navigate/dismiss — buffer unchanged.
                            // Re-running trigger detection here would
                            // see the trigger char still in front of
                            // the cursor and re-arm the debounce,
                            // wiping the popup.
                            continue;
                        }
                        CompletionKeyOutcome::InterceptedAccepted => {
                            // Accept rewrote `[anchor..cursor]`.
                            // Re-detect so a follow-up trigger
                            // character at the end of the inserted
                            // text (chained completions) still fires.
                            update_completion_after_insert(&mut comp, &buffers[current]);
                            continue;
                        }
                    }
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
                    // After every insert-mode mutation: refilter any
                    // open popup and arm/refresh the debounce if the
                    // new buffer state matches a trigger. If the key
                    // moved us out of insert mode (Esc, `jf`), the
                    // post-loop `mode != Insert` close fires below.
                    if mode == Mode::Insert {
                        update_completion_after_insert(&mut comp, &buffers[current]);
                    }
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
                            &main_tx,
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
                // After the input burst settles, if we're not actively
                // typing in insert mode and the buffer has moved past
                // what the LSP server last saw, push a didChange. Fires
                // on Esc/`jf` out of insert mode and after any
                // normal-mode mutation.
                if mode != Mode::Insert {
                    sync_lsp_if_dirty(&mut buffers[current], &mut lsp_clients);
                    // Leaving insert mode closes any open completion
                    // popup and abandons any queued (debounced) trigger.
                    comp.close();
                }
                should_render = true;
            }
        }

        // Fire any pending completion request whose debounce has
        // expired. Runs once per main-loop iteration (whether woken by
        // Input, Tick, or LspMessage) so the 50ms debounce is honored
        // up to the heartbeat granularity.
        maybe_fire_completion(
            &mut comp,
            &mut buffers,
            current,
            &mut lsp_clients,
            &mut outstanding,
        );

        // Drain the filesystem watcher: clean buffers auto-reload from
        // disk, dirty buffers get marked with a pending conflict and
        // raise a Conflict prompt. Cheap when no events queued.
        if let Some(w) = watcher.as_ref() {
            if apply_watcher_events(w, &mut buffers, &highlighter, &mut prompt, &mut ex_message)
            {
                should_render = true;
            }
        }

        // Don't paint yet — accumulate the dirty flag and loop back to drain
        // any other queued events first. The actual frame is rendered at the
        // top of the loop once `try_recv` reports the queue is empty.
        pending_handle_ns += trace::toc(handle_start);
        dirty |= should_render;
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
///
/// The new client's reader thread forwards every server message into
/// `main_tx` tagged with `lang_id`; the main loop dispatches each through
/// `LspClient::handle_message`.
fn maybe_start_lsp_and_open(
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    path: &Path,
    eb: &mut EditorBuffer,
    main_tx: &mpsc::Sender<MainEvent>,
) {
    let lang_id = match eb.lang_id {
        Some(l) => l,
        None => return,
    };
    if !lsp_clients.contains_key(lang_id) {
        let (program, args) = match Highlighter::lsp_command_for_lang(lang_id) {
            Some(c) => c,
            None => {
                trace::note(&format!("lsp_spawn: no LSP configured for lang={}", lang_id));
                return;
            }
        };
        let cwd = std::env::current_dir().unwrap_or_else(|_| PathBuf::from("."));
        let root_uri = match lsp::path_to_uri(&cwd) {
            Ok(u) => u,
            Err(_) => return,
        };
        let tx = main_tx.clone();
        let forward = move |msg: LspMessage| {
            // Sender returns Err only when main has exited; in that case
            // the editor is tearing down and there's nothing useful to do.
            let _ = tx.send(MainEvent::LspMessage(lang_id, msg));
        };
        match LspClient::spawn(program, args, &root_uri, forward) {
            Ok(c) => {
                trace::note(&format!(
                    "lsp_spawn: ok lang={} program={} trigger_chars={:?}",
                    lang_id, program, c.completion_trigger_chars()
                ));
                lsp_clients.insert(lang_id, c);
            }
            Err(e) => {
                trace::note(&format!(
                    "lsp_spawn: failed lang={} program={} args={:?} err={}",
                    lang_id, program, args, e
                ));
                return;
            }
        }
    }
    if let (Some(client), Ok(uri)) = (lsp_clients.get_mut(lang_id), lsp::path_to_uri(path)) {
        let text = String::from_utf8_lossy(&collect_bytes(&eb.buffer)).into_owned();
        match client.did_open(&uri, lang_id, &text) {
            Ok(()) => {
                trace::note(&format!("lsp_open: lang={} uri={}", lang_id, uri));
                eb.lsp_synced_version = Some(eb.buffer.version());
            }
            Err(e) => {
                trace::note(&format!("lsp_open: failed lang={} err={}", lang_id, e));
            }
        }
    }
}

/// Handle a queued `JumpAction`. Navigates to the target jump entry,
/// opening or switching to its buffer as needed. The current location is
/// captured first so a follow-up jump in the opposite direction returns
/// here.
fn dispatch_jump(
    action: medit::core::JumpAction,
    jumps: &mut JumpList,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    highlighter: &Highlighter,
    watcher: Option<&mut FileWatcher>,
    ex_message: &mut String,
    main_tx: &mpsc::Sender<MainEvent>,
) {
    let current_entry = buffers[*current].path.clone().map(|p| JumpEntry {
        path: p,
        offset: buffers[*current].sels.primary().head,
    });
    let target = match action {
        medit::core::JumpAction::Back => jumps.back(current_entry),
        medit::core::JumpAction::Forward => jumps.forward(current_entry),
    };
    let target = match target {
        Some(t) => t,
        None => {
            *ex_message = match action {
                medit::core::JumpAction::Back => "no earlier jumps".to_string(),
                medit::core::JumpAction::Forward => "no later jumps".to_string(),
            };
            return;
        }
    };
    if !open_or_switch_to(
        buffers,
        current,
        &target.path,
        lsp_clients,
        highlighter,
        watcher,
        ex_message,
        main_tx,
    ) {
        return;
    }
    let cur = &mut buffers[*current];
    let bytes = collect_bytes(&cur.buffer);
    let new_head = snap_to_char_or_last(&bytes, target.offset);
    cur.sels.reduce_to_primary();
    let p = cur.sels.primary_mut();
    p.anchor = new_head;
    p.head = new_head;
    p.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
}

/// Handle an `LspAction` queued by the modal layer. Definition and hover
/// fire async — `did_change` first to sync the server's view of the
/// buffer, then `<kind>_async`. The response lands later as an
/// `LspEvent` via the main loop and gets resolved in
/// `handle_lsp_event`. Diagnostics navigation is fully local (cached
/// diagnostics) so it stays synchronous here.
fn dispatch_lsp(
    action: LspAction,
    clients: &mut HashMap<&'static str, LspClient>,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    outstanding: &mut Outstanding,
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
            let (line, character) = cursor_line_col(&buffers[*current]);
            // Sync the server first so its position lookup matches our
            // current buffer state. Cheap if we're already in sync.
            sync_lsp_if_dirty(&mut buffers[*current], clients);
            let client = match clients.get_mut(lang) {
                Some(c) => c,
                None => {
                    *ex_message = "no LSP server for this file".to_string();
                    return;
                }
            };
            let id = match client.definition_async(&cur_uri, line, character) {
                Ok(id) => id,
                Err(e) => {
                    *ex_message = format!("LSP error: {}", e);
                    return;
                }
            };
            // Pre-jump location captured now (not at response time): the
            // user's cursor at *invocation* is what `Ctrl+O` should
            // return to, even if they keep moving around while waiting.
            let pre_jump = buffers[*current].path.clone().map(|p| JumpEntry {
                path: p,
                offset: buffers[*current].sels.primary().head,
            });
            let meta = RequestMeta {
                buf_path: buffers[*current].path.clone(),
                buffer_version: buffers[*current].buffer.version(),
                pre_jump,
            };
            outstanding.entry(lang).or_default().insert(id, meta);
        }
        LspAction::Hover => {
            let (line, character) = cursor_line_col(&buffers[*current]);
            sync_lsp_if_dirty(&mut buffers[*current], clients);
            let client = match clients.get_mut(lang) {
                Some(c) => c,
                None => {
                    *ex_message = "no LSP server for this file".to_string();
                    return;
                }
            };
            let id = match client.hover_async(&cur_uri, line, character) {
                Ok(id) => id,
                Err(e) => {
                    *ex_message = format!("LSP error: {}", e);
                    return;
                }
            };
            let meta = RequestMeta {
                buf_path: buffers[*current].path.clone(),
                buffer_version: buffers[*current].buffer.version(),
                pre_jump: None,
            };
            outstanding.entry(lang).or_default().insert(id, meta);
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

/// What happened to an insert-mode keystroke after the completion
/// layer looked at it.
enum CompletionKeyOutcome {
    /// Popup didn't claim the key; pass it through to `handle_insert`.
    NotIntercepted,
    /// Popup consumed the key but didn't mutate the buffer (navigate
    /// or dismiss). The caller should NOT re-run trigger detection —
    /// the surrounding bytes are unchanged, and re-detecting would
    /// fire a new completion request and wipe the popup.
    InterceptedNoChange,
    /// Popup consumed the key by accepting an item, which mutated the
    /// buffer. The caller should re-run trigger detection so a
    /// follow-up trigger character in the inserted text (e.g.
    /// `foo.` → re-fire on the trailing `.`) is honored.
    InterceptedAccepted,
}

/// Try to handle an insert-mode keystroke as a completion-popup
/// interaction.
/// - Tab/Enter when the popup is showing accept the highlighted item.
/// - Down/Up and Ctrl-N/Ctrl-P navigate the selection.
/// - Esc with the popup showing closes the popup without exiting
///   insert mode (the next Esc behaves normally).
fn handle_completion_keys(
    comp: &mut CompletionUi,
    eb: &mut EditorBuffer,
    k: KeyEvent,
) -> CompletionKeyOutcome {
    // Alt-/ : open a path-only completion popup from the filesystem,
    // regardless of language or whether another popup is showing. Synchronous
    // (no LSP round trip), so we fill it right here.
    if k.mods == Mods::ALT && k.key == Key::Char('/') {
        open_path_completion(comp, eb);
        return CompletionKeyOutcome::InterceptedNoChange;
    }
    // Path sessions accept (and chain into directories) through their own
    // handler so the generic word/LSP accept doesn't run.
    if comp.is_path_session
        && comp.is_visible()
        && k.mods.is_empty()
        && (k.key == Key::Tab || k.key == Key::Enter)
    {
        accept_path_completion(comp, eb);
        return CompletionKeyOutcome::InterceptedNoChange;
    }
    // Ctrl-n with no popup open: manually force completion on the word
    // prefix under the cursor, at any length (the manual counterpart to the
    // automatic triggers). We arm a debounced `Invoked` request anchored at
    // the word start; `maybe_fire_completion` serves it from the buffer
    // (markdown) or the LSP server later this iteration. When the popup is
    // already open, Ctrl-n falls through to the "next item" handler below.
    if !comp.is_visible() && k.mods.contains(Mods::CTRL) && k.key == Key::Char('n') {
        if eb.sels.len() == 1 {
            let cursor = eb.sels.primary().head;
            let bytes = collect_bytes(&eb.buffer);
            let anchor = medit::completion::ident_prefix_start(&bytes, cursor);
            comp.pending = Some(PendingTrigger {
                anchor,
                trigger: CompletionTrigger::Invoked,
                deadline: Instant::now(),
            });
        }
        return CompletionKeyOutcome::InterceptedNoChange;
    }
    if !comp.is_visible() {
        return CompletionKeyOutcome::NotIntercepted;
    }
    if k.mods.is_empty() && (k.key == Key::Tab || k.key == Key::Enter) {
        accept_completion(comp, eb);
        return CompletionKeyOutcome::InterceptedAccepted;
    }
    let nav_next = (k.mods.is_empty() && k.key == Key::Down)
        || (k.mods.contains(Mods::CTRL) && k.key == Key::Char('n'));
    let nav_prev = (k.mods.is_empty() && k.key == Key::Up)
        || (k.mods.contains(Mods::CTRL) && k.key == Key::Char('p'));
    if nav_next {
        if !comp.filtered.is_empty() {
            comp.selected = (comp.selected + 1) % comp.filtered.len();
        }
        return CompletionKeyOutcome::InterceptedNoChange;
    }
    if nav_prev {
        if !comp.filtered.is_empty() {
            let n = comp.filtered.len();
            comp.selected = (comp.selected + n - 1) % n;
        }
        return CompletionKeyOutcome::InterceptedNoChange;
    }
    if k.key == Key::Esc {
        comp.close();
        return CompletionKeyOutcome::InterceptedNoChange;
    }
    CompletionKeyOutcome::NotIntercepted
}

/// Apply the highlighted completion item to the buffer: replace
/// `[anchor..cursor]` with the item's `insert_text`, move the cursor
/// to the end of the inserted text, and close the popup. No-op (just
/// closes) if there's nothing selectable, multi-cursor is engaged, or
/// the anchor is no longer in front of the cursor.
fn accept_completion(comp: &mut CompletionUi, eb: &mut EditorBuffer) {
    let item_idx = match comp.filtered.get(comp.selected) {
        Some(&i) => i,
        None => {
            comp.close();
            return;
        }
    };
    let insert_text = comp.items[item_idx].insert_text.clone();
    if eb.sels.len() > 1 {
        comp.close();
        return;
    }
    let cursor = eb.sels.primary().head;
    if comp.anchor > cursor {
        comp.close();
        return;
    }
    let range_len = cursor - comp.anchor;
    if range_len > 0 {
        eb.buffer.delete(comp.anchor, range_len);
    }
    eb.buffer.insert(comp.anchor, insert_text.as_bytes());
    let new_head = comp.anchor + insert_text.len();
    let bytes = collect_bytes(&eb.buffer);
    let p = eb.sels.primary_mut();
    p.head = new_head;
    p.anchor = new_head;
    p.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
    comp.close();
}

/// Open the `Alt-/` filesystem path popup at the primary cursor. Gathers
/// matching entries synchronously; closes any existing popup when there's
/// nothing to offer or multi-cursor is engaged.
fn open_path_completion(comp: &mut CompletionUi, eb: &EditorBuffer) {
    if eb.sels.len() != 1 {
        comp.close();
        return;
    }
    let cursor = eb.sels.primary().head;
    let bytes = collect_bytes(&eb.buffer);
    match medit::path_complete::complete(&bytes, cursor) {
        Some(pc) => comp.set_path_items(pc),
        None => comp.close(),
    }
}

/// Accept the highlighted path item: replace `[anchor..cursor]` with its
/// `insert_text`. When the item is a directory (its text ends with a
/// separator) re-open path completion one level deeper so the user can keep
/// walking the tree; otherwise the popup closes.
fn accept_path_completion(comp: &mut CompletionUi, eb: &mut EditorBuffer) {
    let item_idx = match comp.filtered.get(comp.selected) {
        Some(&i) => i,
        None => {
            comp.close();
            return;
        }
    };
    let insert_text = comp.items[item_idx].insert_text.clone();
    if eb.sels.len() != 1 {
        comp.close();
        return;
    }
    let cursor = eb.sels.primary().head;
    if comp.anchor > cursor {
        comp.close();
        return;
    }
    let range_len = cursor - comp.anchor;
    if range_len > 0 {
        eb.buffer.delete(comp.anchor, range_len);
    }
    eb.buffer.insert(comp.anchor, insert_text.as_bytes());
    let mut new_head = comp.anchor + insert_text.len();
    let descended = insert_text.ends_with(['/', '\\']);

    // Accepting a file (not a directory) inside a string literal closes the
    // quote for you — unless the matching quote is already right there.
    if !descended
        && let Some(qc) = comp.path_quote
    {
        let here = collect_bytes(&eb.buffer);
        if here.get(new_head) != Some(&(qc as u8)) {
            let mut buf = [0u8; 4];
            let s = qc.encode_utf8(&mut buf);
            eb.buffer.insert(new_head, s.as_bytes());
            new_head += s.len();
        }
    }

    let bytes = collect_bytes(&eb.buffer);
    let p = eb.sels.primary_mut();
    p.head = new_head;
    p.anchor = new_head;
    p.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);

    comp.close();
    if descended
        && let Some(pc) = medit::path_complete::complete(&bytes, new_head)
    {
        comp.set_path_items(pc);
    }
}

/// Refilter (or re-gather) the path popup after an insert-mode mutation.
/// Typing a separator descends a level; other characters narrow the current
/// listing, falling back to a fresh gather when the narrowed filter empties
/// (e.g. a space extended the directory part).
fn update_path_completion_after_insert(comp: &mut CompletionUi, eb: &EditorBuffer) {
    if eb.sels.len() != 1 {
        comp.close();
        return;
    }
    let cursor = eb.sels.primary().head;
    let bytes = collect_bytes(&eb.buffer);
    if comp.anchor > cursor || cursor > bytes.len() {
        comp.close();
        return;
    }
    let typed_sep = cursor > 0 && (bytes[cursor - 1] == b'/' || bytes[cursor - 1] == b'\\');
    if typed_sep {
        match medit::path_complete::complete(&bytes, cursor) {
            Some(pc) => comp.set_path_items(pc),
            None => comp.close(),
        }
        return;
    }
    comp.prefix = String::from_utf8_lossy(&bytes[comp.anchor..cursor]).into_owned();
    comp.filtered = medit::completion::filter_items(&comp.items, &comp.prefix);
    if comp.filtered.is_empty() {
        match medit::path_complete::complete(&bytes, cursor) {
            Some(pc) => comp.set_path_items(pc),
            None => comp.close(),
        }
    } else {
        comp.selected = 0;
    }
}

/// Recompute completion state after an insert-mode mutation. Refilters
/// the popup against the new prefix if one is open, and arms a
/// debounced completion request if the keystroke landed on a trigger
/// (per the language's `CompletionTriggers`). Closes the popup when
/// multi-cursor is engaged, when the language doesn't have completion
/// rules, or when the cursor moved out of `[anchor..]`.
fn update_completion_after_insert(comp: &mut CompletionUi, eb: &EditorBuffer) {
    // Path sessions are language-independent and filesystem-backed; they
    // refilter/re-gather on their own rather than via language triggers.
    if comp.is_path_session {
        update_path_completion_after_insert(comp, eb);
        return;
    }
    if eb.sels.len() > 1 {
        trace::note("update_completion: skip (multi-cursor)");
        comp.close();
        return;
    }
    let cursor = eb.sels.primary().head;
    let bytes = collect_bytes(&eb.buffer);

    // Auto-trigger: typing a path separator (with a non-whitespace char
    // before it, e.g. `./`, `../`, `src/`) opens path completion when it
    // resolves to a real directory. Self-limiting — in non-path contexts
    // `complete` finds no resolving directory and returns None, so nothing
    // pops up. Runs before the language check so it works in any buffer.
    if medit::path_complete::separator_should_autotrigger(&bytes, cursor)
        && let Some(pc) = medit::path_complete::complete(&bytes, cursor)
    {
        comp.set_path_items(pc);
        return;
    }

    let lang = match eb.lang_id {
        Some(l) => l,
        None => {
            trace::note("update_completion: skip (no lang_id)");
            comp.close();
            return;
        }
    };
    let triggers = match medit::completion::triggers_for(lang) {
        Some(t) => t,
        None => {
            trace::note(&format!("update_completion: skip (no triggers for lang={})", lang));
            comp.close();
            return;
        }
    };

    // Refilter the existing popup against the new prefix. If the
    // cursor moved out of the replacement range (e.g. backspace past
    // the anchor, or the cursor jumped) close the popup. When the
    // most recent server response was flagged `isIncomplete`, keep
    // the session open even if the filter empties — the upcoming
    // re-request may bring matches for the extended prefix.
    let mut session_alive = false;
    if !comp.items.is_empty() {
        if comp.anchor > cursor || cursor > bytes.len() {
            comp.close();
        } else {
            comp.prefix = String::from_utf8_lossy(&bytes[comp.anchor..cursor]).into_owned();
            comp.filtered = medit::completion::filter_items(&comp.items, &comp.prefix);
            if comp.filtered.is_empty() && !comp.is_incomplete {
                comp.close();
            } else {
                comp.selected = 0;
                session_alive = true;
            }
        }
    }

    // Trigger detection wins over an incomplete refresh: a fresh
    // trigger (`.` or `@` or a new identifier boundary) starts a new
    // session, replacing the anchor/trigger kind.
    let decision = medit::completion::detect(&bytes, cursor, &triggers);
    if let medit::completion::TriggerDecision::Trigger {
        anchor,
        trigger_char,
        ..
    } = decision
    {
        let trigger = match trigger_char {
            Some(ch) => CompletionTrigger::Character(ch),
            None => CompletionTrigger::Invoked,
        };
        trace::note(&format!(
            "update_completion: trigger fired lang={} anchor={} cursor={} kind={:?}",
            lang, anchor, cursor, trigger,
        ));
        comp.pending = Some(PendingTrigger {
            anchor,
            trigger,
            deadline: Instant::now() + COMPLETION_DEBOUNCE,
        });
        return;
    }

    // No fresh trigger. If the popup session is still alive and the
    // server flagged the previous result as `isIncomplete`, arm a
    // re-request with `CompletionTrigger::Incomplete`. The 50ms
    // debounce naturally collapses bursts of keystrokes into one
    // request.
    if session_alive && comp.is_incomplete && comp.anchor <= cursor {
        comp.pending = Some(PendingTrigger {
            anchor: comp.anchor,
            trigger: CompletionTrigger::Incomplete,
            deadline: Instant::now() + COMPLETION_DEBOUNCE,
        });
    }
}

/// Fire any pending completion request whose debounce window has
/// elapsed. Called once per main-loop iteration. Sends `did_change`
/// first so the server's position lookup matches the editor's view.
fn maybe_fire_completion(
    comp: &mut CompletionUi,
    buffers: &mut [EditorBuffer],
    current: usize,
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    outstanding: &mut Outstanding,
) {
    let ready = matches!(comp.pending.as_ref(), Some(p) if p.deadline <= Instant::now());
    if !ready {
        return;
    }
    let pending = comp.pending.take().unwrap();
    let cur = &mut buffers[current];
    // Re-check guards: the user may have changed something between
    // arming and firing.
    if cur.sels.len() > 1 {
        trace::note("fire_completion: skip (multi-cursor)");
        return;
    }
    let cursor = cur.sels.primary().head;
    if pending.anchor > cursor {
        // User deleted past the anchor while waiting; abandon.
        trace::note("fire_completion: skip (cursor moved past anchor)");
        return;
    }
    let lang = match cur.lang_id {
        Some(l) => l,
        None => {
            trace::note("fire_completion: skip (no lang_id)");
            return;
        }
    };

    // Buffer-word source (markdown/djot): no server round trip — gather
    // matching words from the buffer and fill the popup synchronously.
    if medit::completion::is_buffer_source(lang) {
        let bytes = collect_bytes(&cur.buffer);
        let prefix = String::from_utf8_lossy(&bytes[pending.anchor..cursor]).into_owned();
        let items = medit::completion::buffer_word_items(&bytes, &prefix);
        trace::note(&format!(
            "fire_completion: buffer source lang={} prefix={:?} items={}",
            lang,
            prefix,
            items.len()
        ));
        if items.is_empty() {
            return;
        }
        comp.set_items(items, pending.anchor, prefix);
        return;
    }

    let cur_uri = match cur.path.as_ref().and_then(|p| lsp::path_to_uri(p).ok()) {
        Some(u) => u,
        None => {
            trace::note("fire_completion: skip (no path/uri)");
            return;
        }
    };
    // Sync the server first — completion `position` would mean
    // nothing if the document's content differs from what we have.
    sync_lsp_if_dirty(cur, lsp_clients);
    let client = match lsp_clients.get_mut(lang) {
        Some(c) => c,
        None => {
            trace::note(&format!("fire_completion: skip (no LSP client for lang={})", lang));
            return;
        }
    };
    let bytes = collect_bytes(&cur.buffer);
    let line = line_index(&bytes, cursor) as u32;
    let line_start_byte = byte_at_line(&bytes, line as usize);
    let character = cursor.saturating_sub(line_start_byte) as u32;
    let id = match client.completion_async(&cur_uri, line, character, pending.trigger) {
        Ok(id) => id,
        Err(e) => {
            trace::note(&format!("fire_completion: send failed: {}", e));
            return;
        }
    };
    trace::note(&format!(
        "fire_completion: sent id={} lang={} line={} char={} trigger={:?}",
        id, lang, line, character, pending.trigger,
    ));
    let meta = RequestMeta {
        buf_path: cur.path.clone(),
        buffer_version: cur.buffer.version(),
        pre_jump: None,
    };
    outstanding.entry(lang).or_default().insert(id, meta);
    // Mark this as the latest request; any earlier completion
    // responses still in flight will be dropped on arrival.
    comp.request_id = Some(id);
    comp.anchor = pending.anchor;
    // For new sessions (Character/Invoked), wipe stale items so the
    // popup doesn't show last-session matches. For an Incomplete
    // refresh, keep the current items visible until the new response
    // replaces them — the user just keeps typing, no need to flicker.
    let is_refresh = matches!(pending.trigger, CompletionTrigger::Incomplete);
    if !is_refresh {
        comp.items.clear();
        comp.filtered.clear();
        comp.selected = 0;
    }
}

/// Resolve the buffer's primary-cursor head into LSP `(line, character)`
/// coordinates. Both definition and hover request paths need this.
fn cursor_line_col(eb: &EditorBuffer) -> (u32, u32) {
    let bytes = collect_bytes(&eb.buffer);
    let head = eb.sels.primary().head;
    let line = line_index(&bytes, head) as u32;
    let line_start_byte = byte_at_line(&bytes, line as usize);
    let character = head.saturating_sub(line_start_byte) as u32;
    (line, character)
}

/// Find a buffer by path. Returns its index in `buffers` or `None`.
fn buffer_index_by_path(buffers: &[EditorBuffer], path: &Path) -> Option<usize> {
    buffers.iter().position(|b| b.path.as_deref() == Some(path))
}

/// Apply an `LspEvent` produced by `LspClient::handle_message`. Looks up
/// the originating buffer (by path), drops on edit-version mismatch,
/// then updates editor state accordingly.
fn handle_lsp_event(
    lang: &'static str,
    event: LspEvent,
    outstanding: &mut Outstanding,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    lsp_clients: &mut HashMap<&'static str, LspClient>,
    highlighter: &Highlighter,
    watcher: Option<&mut FileWatcher>,
    hover: &mut Option<String>,
    jumps: &mut JumpList,
    ex_message: &mut String,
    comp: &mut CompletionUi,
    main_tx: &mpsc::Sender<MainEvent>,
) {
    let (id, take_meta): (u64, bool) = match &event {
        LspEvent::Hover { id, .. } => (*id, true),
        LspEvent::Definition { id, .. } => (*id, true),
        LspEvent::Completion { id, .. } => (*id, true),
        LspEvent::DiagnosticsUpdated { .. } => (0, false),
    };
    let meta = if take_meta {
        outstanding.get_mut(lang).and_then(|m| m.remove(&id))
    } else {
        None
    };

    match event {
        LspEvent::DiagnosticsUpdated { .. } => {
            // The client already updated its internal cache. Re-render
            // will pick it up; nothing else to do.
        }
        LspEvent::Hover { result, .. } => {
            let meta = match meta {
                Some(m) => m,
                // Unknown id (already cancelled, or response for a
                // request from a previous editor session). Drop.
                None => return,
            };
            let idx = match meta.buf_path.as_deref().and_then(|p| buffer_index_by_path(buffers, p)) {
                Some(i) => i,
                // Buffer was closed before the response landed.
                None => return,
            };
            if buffers[idx].buffer.version() != meta.buffer_version {
                // User edited the buffer since the request was sent.
                // The position the server resolved no longer maps to
                // the same token; drop.
                return;
            }
            match result {
                Ok(Some(text)) => *hover = Some(text),
                Ok(None) => *ex_message = "no hover info".to_string(),
                Err(e) => *ex_message = format!("LSP error: {}", e.message),
            }
        }
        LspEvent::Definition { result, .. } => {
            let meta = match meta {
                Some(m) => m,
                None => return,
            };
            let idx = match meta.buf_path.as_deref().and_then(|p| buffer_index_by_path(buffers, p)) {
                Some(i) => i,
                None => return,
            };
            if buffers[idx].buffer.version() != meta.buffer_version {
                return;
            }
            let loc = match result {
                Ok(Some(loc)) => loc,
                Ok(None) => {
                    *ex_message = "no definition found".to_string();
                    return;
                }
                Err(e) => {
                    *ex_message = format!("LSP error: {}", e.message);
                    return;
                }
            };
            // Switch to the buffer that originated the request before
            // jumping — if the user moved to a different buffer while
            // waiting, jumping in the current one would be confusing.
            *current = idx;
            if let Some(pj) = meta.pre_jump {
                jumps.record(pj);
            }
            // Decide whether the result is in a different file. We
            // re-derive the originating uri rather than threading it
            // through meta — it'd be wrong if the buffer was renamed.
            let cur_uri = buffers[*current]
                .path
                .as_ref()
                .and_then(|p| lsp::path_to_uri(p).ok());
            let cross_file = match cur_uri.as_deref() {
                Some(u) => u != loc.uri,
                None => true,
            };
            if cross_file {
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
                    lsp_clients,
                    highlighter,
                    watcher,
                    ex_message,
                    main_tx,
                ) {
                    return;
                }
            }
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
        LspEvent::Completion { id, result } => {
            // Stale by id: there's a newer completion request in
            // flight (or the popup was closed), so this response is
            // no longer authoritative.
            if comp.request_id != Some(id) {
                trace::note(&format!(
                    "completion_resp: drop stale id={} (current={:?})",
                    id, comp.request_id
                ));
                return;
            }
            let meta = match meta {
                Some(m) => m,
                None => {
                    trace::note(&format!("completion_resp: id={} no meta", id));
                    return;
                }
            };
            let idx = match meta
                .buf_path
                .as_deref()
                .and_then(|p| buffer_index_by_path(buffers, p))
            {
                Some(i) => i,
                None => {
                    trace::note(&format!("completion_resp: id={} originating buffer gone", id));
                    comp.request_id = None;
                    return;
                }
            };
            // Stale by version: the user edited the buffer since the
            // request was sent (and we sync didChange before each
            // completion, so the version we sent was `buffer_version`).
            if buffers[idx].buffer.version() != meta.buffer_version {
                trace::note(&format!(
                    "completion_resp: drop id={} buffer-version mismatch (sent={}, now={})",
                    id, meta.buffer_version, buffers[idx].buffer.version()
                ));
                comp.request_id = None;
                return;
            }
            let raw = match result {
                Ok(v) => v,
                Err(e) => {
                    trace::note(&format!("completion_resp: id={} server error: {}", id, e.message));
                    comp.request_id = None;
                    return;
                }
            };
            let parsed = medit::completion::parse_response(&raw);
            trace::note(&format!(
                "completion_resp: id={} parsed items={} incomplete={}",
                id, parsed.items.len(), parsed.is_incomplete
            ));
            comp.items = parsed.items;
            comp.is_incomplete = parsed.is_incomplete;
            comp.request_id = None;
            // Compute the filter prefix from the buffer right now. The
            // cursor may have moved between request and response
            // (within the same buffer version: cursor moves don't bump
            // version), so re-read it.
            let cursor = buffers[idx].sels.primary().head;
            let bytes = collect_bytes(&buffers[idx].buffer);
            comp.prefix = if comp.anchor <= cursor && cursor <= bytes.len() {
                String::from_utf8_lossy(&bytes[comp.anchor..cursor]).into_owned()
            } else {
                String::new()
            };
            comp.filtered = medit::completion::filter_items(&comp.items, &comp.prefix);
            comp.selected = 0;
            trace::note(&format!(
                "completion_resp: id={} prefix={:?} filtered={}",
                id, comp.prefix, comp.filtered.len()
            ));
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
    eb.left_col = 0;
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
    main_tx: &mpsc::Sender<MainEvent>,
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
    maybe_start_lsp_and_open(lsp_clients, path, &mut buffers[*current], main_tx);
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
) -> bool {
    let changed = watcher.poll();
    if changed.is_empty() {
        return false;
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
    true
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
    main_tx: &mpsc::Sender<MainEvent>,
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
                main_tx,
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
    hover: Option<&str>,
    spinner: Option<char>,
    comp: Option<&CompletionUi>,
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
    // Diagnostics are hidden while the user is actively editing —
    // pre-`didChange` underlines on stale text are noisy and we resync
    // continually during insert mode for completion. They're rendered
    // again as soon as the user returns to normal mode.
    let diagnostics: &[medit::lsp::Diagnostic] = if mode == Mode::Insert {
        &[]
    } else {
        match (cur.lang_id, cur.path.as_ref()) {
            (Some(lang), Some(p)) => match lsp::path_to_uri(p) {
                Ok(uri) => lsp_clients
                    .get(lang)
                    .map(|c| c.diagnostics_for(&uri))
                    .unwrap_or(&[]),
                Err(_) => &[],
            },
            _ => &[],
        }
    };
    render(
        screen,
        &cur.cached_bytes,
        &cur.line_starts,
        &cur.sels,
        &cur.flat_scopes,
        mode,
        cur.top_line,
        cur.left_col,
        &buffer_label,
        ex_input,
        search_input,
        search,
        ex_message,
        last_key,
        last_bytes,
        diagnostics,
        prompt,
        hover,
        spinner,
        comp,
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
    left_col: usize,
    buffer_label: &str,
    ex_input: &str,
    search_input: &str,
    search: &SearchState,
    ex_message: &str,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
    diagnostics: &[medit::lsp::Diagnostic],
    prompt: Option<&Prompt>,
    hover: Option<&str>,
    spinner: Option<char>,
    comp: Option<&CompletionUi>,
) -> io::Result<()> {
    screen.begin_frame();
    let cols = screen.cols;
    let viewport_rows = screen.rows.saturating_sub(1);
    // Erase every content row to end-of-line up front (in place of a
    // full-screen clear). Covers rows the buffer doesn't reach, so short
    // buffers and upward scrolls don't leave stale glyphs behind. The
    // status row is repainted full-width below, so it isn't cleared here.
    for r in 1..=viewport_rows {
        screen.clear_row(r);
    }
    let primary = sels.primary();
    let head = primary.head;
    let start_byte = byte_at_line_cached(line_starts, top_line, bytes.len());

    // `line_starts.len()` is always at least 1 (we always seed with 0); the
    // total number of newline-terminated lines is `line_starts.len()` and
    // the visible-line count is the same (we count trailing partial lines).
    let total_lines = line_starts.len();
    let gutter: u16 = gutter_for(total_lines, cols);
    let content_cols = cols.saturating_sub(gutter);
    // Visual columns hidden off the left edge, clamped to `u16` for the
    // per-cell math below (the cursor is always kept on screen, so a value
    // this large only arises on absurdly long lines).
    let left_col: u16 = left_col.min(u16::MAX as usize) as u16;

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
    // True 1-based visual column of the cursor (pre horizontal-scroll
    // offset), for the status-bar readout. `cur_col` is the on-screen
    // column after subtracting `left_col`.
    let mut cur_vcol: u16 = 1;
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
            cur_col = col.saturating_sub(left_col).max(1).min(content_cols.max(1));
            cur_vcol = col;
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
                // Tabs only need a visible body when there's something to
                // paint (selection bg, search highlight, or a diagnostic
                // underline); otherwise we just advance. Clip the run to the
                // horizontal window so a partially-scrolled tab paints only
                // its visible cells.
                if let (true, Some((scol, w, _))) = (
                    bg.is_some() || ul_seq.is_some(),
                    clip_run(col, advance as u16, left_col, content_cols),
                ) {
                    const SPACES: &[u8; 4] = b"    ";
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        &mut style_ul,
                        row,
                        scol + gutter,
                        w,
                        fg_seq,
                        bg,
                        ul_seq,
                        &SPACES[..w as usize],
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
                if let Some((scol, w, off)) = clip_run(col, 2, left_col, content_cols) {
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        &mut style_ul,
                        row,
                        scol + gutter,
                        w,
                        fg_seq,
                        bg,
                        ul_seq,
                        &body[off..off + w as usize],
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
                if let Some((scol, _, _)) = clip_run(col, 1, left_col, content_cols) {
                    let glyph = bytes.get(i..end).unwrap_or(b"?");
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        &mut style_ul,
                        row,
                        scol + gutter,
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
        // The spinner glyph occupies a single column between the mode
        // tag and the buffer label so it doesn't shift other elements
        // as it appears/disappears (we draw a space when no spinner).
        let spinner_ch = spinner.unwrap_or(' ');
        let s = format!(
            " [{}] {} {} · ln {} col {} · {}sel {}b · last:{} raw:{} ",
            mode_str,
            spinner_ch,
            buffer_label,
            abs_line,
            cur_vcol,
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

    // LSP hover popup, anchored near the cursor. Drawn before the modal
    // prompt so a prompt (if active) still wins.
    if let Some(text) = hover {
        draw_hover_popup(screen, text, cur_row, cur_col, gutter, cols, viewport_rows);
    }

    // Completion popup. Anchored at the replacement-start column, not
    // the cursor, so it stays put as the user types more characters
    // of the prefix. Drawn after hover so the active completion wins
    // visually if both happen to be set.
    if let Some(c) = comp {
        if c.is_visible() {
            draw_completion_popup(
                screen,
                c,
                bytes,
                line_starts,
                head,
                cur_row,
                cur_col,
                gutter,
                cols,
                viewport_rows,
            );
        }
    }

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

#[cfg(test)]
mod horizontal_scroll_tests {
    use super::{clip_run, ensure_visible_horizontal, visual_col_at};

    #[test]
    fn visual_col_counts_plain_chars() {
        assert_eq!(visual_col_at(b"abc", 0, 0), 1);
        assert_eq!(visual_col_at(b"abc", 0, 1), 2);
        assert_eq!(visual_col_at(b"abc", 0, 3), 4);
    }

    #[test]
    fn visual_col_expands_tabs_to_multiples_of_four() {
        // A leading tab advances to column 5 (1 -> 5).
        assert_eq!(visual_col_at(b"\tx", 0, 1), 5);
        // "ab\tc": a(1->2) b(2->3) tab rounds 3 up by 2 -> 5, so 'c' is col 5.
        assert_eq!(visual_col_at(b"ab\tc", 0, 3), 5);
    }

    #[test]
    fn visual_col_control_chars_take_two_cells() {
        // ^A renders as two cells, so the following char starts at column 3.
        assert_eq!(visual_col_at(b"\x01x", 0, 1), 3);
    }

    #[test]
    fn ensure_horizontal_scrolls_right_when_cursor_past_edge() {
        let mut left = 0usize;
        ensure_visible_horizontal(15, 100, &mut left, 10);
        assert_eq!(left, 5, "cursor at col 15 in a 10-wide window -> left edge col 6");
    }

    #[test]
    fn ensure_horizontal_no_scroll_when_visible() {
        let mut left = 0usize;
        ensure_visible_horizontal(5, 100, &mut left, 10);
        assert_eq!(left, 0);
    }

    #[test]
    fn ensure_horizontal_snaps_back_on_short_line() {
        // Was scrolled far right; cursor now on a line that fits entirely.
        let mut left = 50usize;
        ensure_visible_horizontal(8, 8, &mut left, 10);
        assert_eq!(left, 0, "a line that fits the viewport never stays scrolled");
    }

    #[test]
    fn ensure_horizontal_never_scrolls_past_line_end() {
        // Line ends at visual col 20, window is 10 wide: max useful left is 10.
        let mut left = 0usize;
        ensure_visible_horizontal(20, 20, &mut left, 10);
        assert_eq!(left, 10);
    }

    #[test]
    fn clip_run_visible_cell() {
        // No horizontal offset: column maps straight through.
        assert_eq!(clip_run(5, 1, 0, 10), Some((5, 1, 0)));
    }

    #[test]
    fn clip_run_offsets_by_left_col() {
        // With 5 columns hidden, visual col 6 lands at screen content col 1.
        assert_eq!(clip_run(6, 1, 5, 10), Some((1, 1, 0)));
    }

    #[test]
    fn clip_run_drops_offscreen_cells() {
        assert_eq!(clip_run(11, 1, 0, 10), None); // past the right edge
        assert_eq!(clip_run(3, 1, 5, 10), None); // scrolled off the left
    }

    #[test]
    fn clip_run_clips_a_partially_scrolled_run() {
        // A 4-wide tab at cols 4..=7 with 5 cols hidden: cols 6,7 remain,
        // drawn at screen col 1, with the first two cells clipped away.
        assert_eq!(clip_run(4, 4, 5, 10), Some((1, 2, 2)));
    }
}
