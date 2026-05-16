//! Headless editor core: buffer state, selection, modes, motions, and the
//! per-mode keystroke handlers. Pure logic, no terminal I/O.

use std::io;

use crate::buffer::{Buffer, CursorSnapshot};
use crate::input::{Key, KeyEvent, Mods};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Mode {
    Normal,
    Insert,
    Ex,
    Search,
}

#[derive(Default)]
pub struct Registers {
    pub default: Vec<u8>,
}

/// Search machinery.
///
/// - `pattern` is the last *committed* regex (after `Enter`), used by `n`/`N`
///   to repeat searches in normal mode.
/// - `preview` is the regex compiled from the current incremental input
///   while in `Mode::Search`. Used by the renderer to highlight matches as
///   the user types.
/// - `start` is the selection captured on `/` entry, so `Esc` can revert and
///   so incremental forward searches start from a stable position rather
///   than chasing themselves through the buffer.
#[derive(Default)]
pub struct SearchState {
    pub pattern: Option<regex::bytes::Regex>,
    pub preview: Option<regex::bytes::Regex>,
    pub start: Option<CursorSnapshot>,
}

#[derive(Debug, Clone, Copy)]
pub struct Selection {
    pub anchor: usize,
    pub head: usize,
    pub desired_col: usize,
}

impl Selection {
    pub fn new() -> Self {
        Self {
            anchor: 0,
            head: 0,
            desired_col: 1,
        }
    }

    pub fn min(&self) -> usize {
        self.anchor.min(self.head)
    }

    pub fn max(&self) -> usize {
        self.anchor.max(self.head)
    }
}

impl Default for Selection {
    fn default() -> Self {
        Self::new()
    }
}

fn snapshot_of(sel: &Selection) -> CursorSnapshot {
    CursorSnapshot {
        anchor: sel.anchor,
        head: sel.head,
        desired_col: sel.desired_col,
    }
}

fn apply_snapshot(sel: &mut Selection, snap: CursorSnapshot) {
    sel.anchor = snap.anchor;
    sel.head = snap.head;
    sel.desired_col = snap.desired_col;
}

pub enum Motion {
    Left,
    Right,
    Up,
    Down,
    LineStart,
    LineEnd,
    NextWord,
    PrevWord,
    EndWord,
}

/// Returns `true` if this key was a quit request.
pub fn handle_normal(
    buffer: &mut Buffer,
    sel: &mut Selection,
    mode: &mut Mode,
    registers: &mut Registers,
    pending_g: &mut bool,
    search: &mut SearchState,
    k: KeyEvent,
) -> bool {
    let bytes = collect_bytes(buffer);

    // Resolve g-prefix from previous keystroke. `gg` is the only mapping for
    // now; any other follow-up to a pending `g` is silently dropped (Vim-style
    // unknown-command behavior).
    if *pending_g {
        *pending_g = false;
        if k.mods.is_empty() && k.key == Key::Char('g') {
            let new_head = if bytes.is_empty() {
                0
            } else {
                snap_to_char_or_last(&bytes, 0)
            };
            sel.anchor = new_head;
            sel.head = new_head;
            sel.desired_col = 1;
        }
        return false;
    }

    // Start a g-prefix if a bare `g` was pressed.
    if k.mods.is_empty() && k.key == Key::Char('g') {
        *pending_g = true;
        return false;
    }

    if k.mods.is_empty() && k.key == Key::Char('q') {
        return true;
    }

    // G: jump to start of last non-empty line. Slides (collapses).
    if k.mods.is_empty() && k.key == Key::Char('G') {
        let new_head = last_line_start(&bytes);
        let new_head = snap_to_char_or_last(&bytes, new_head);
        sel.anchor = new_head;
        sel.head = new_head;
        sel.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
        return false;
    }

    // / enters Search mode; n / N repeat last search forward / backward.
    if k.mods.is_empty() && k.key == Key::Char('/') {
        search.start = Some(snapshot_of(sel));
        search.preview = None;
        *mode = Mode::Search;
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('n') {
        if let Some(re) = search.pattern.as_ref() {
            find_and_select(sel, &bytes, re, true);
        }
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('N') {
        if let Some(re) = search.pattern.as_ref() {
            find_and_select(sel, &bytes, re, false);
        }
        return false;
    }

    if k.mods.is_empty() {
        match k.key {
            Key::Char('i') => {
                let min = sel.min();
                sel.anchor = min;
                sel.head = min;
                buffer.mark_commit_point(snapshot_of(sel));
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('a') => {
                let after = next_char_or_end(&bytes, sel.max());
                sel.anchor = after;
                sel.head = after;
                buffer.mark_commit_point(snapshot_of(sel));
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('u') => {
                op_undo(buffer, sel);
                return false;
            }
            Key::Char('U') => {
                op_redo(buffer, sel);
                return false;
            }
            Key::Char(';') => {
                sel.anchor = sel.head;
                return false;
            }
            Key::Char(':') => {
                *mode = Mode::Ex;
                return false;
            }
            Key::Char('d') => {
                op_delete(buffer, sel, registers);
                return false;
            }
            Key::Char('c') => {
                op_change(buffer, sel, mode, registers);
                return false;
            }
            Key::Char('y') => {
                op_yank(buffer, sel, registers);
                return false;
            }
            Key::Char('p') => {
                op_paste_after(buffer, sel, registers);
                return false;
            }
            Key::Char('P') => {
                op_paste_before(buffer, sel, registers);
                return false;
            }
            Key::Char('o') => {
                op_open_below(buffer, sel, mode);
                return false;
            }
            Key::Char('O') => {
                op_open_above(buffer, sel, mode);
                return false;
            }
            _ => {}
        }
    }

    let (motion, extend) = match k.key {
        Key::Char('h') => (Some(Motion::Left), false),
        Key::Char('H') => (Some(Motion::Left), true),
        Key::Char('l') => (Some(Motion::Right), false),
        Key::Char('L') => (Some(Motion::Right), true),
        Key::Char('k') => (Some(Motion::Up), false),
        Key::Char('K') => (Some(Motion::Up), true),
        Key::Char('j') => (Some(Motion::Down), false),
        Key::Char('J') => (Some(Motion::Down), true),
        Key::Char('w') => (Some(Motion::NextWord), false),
        Key::Char('W') => (Some(Motion::NextWord), true),
        Key::Char('b') => (Some(Motion::PrevWord), false),
        Key::Char('B') => (Some(Motion::PrevWord), true),
        Key::Char('e') => (Some(Motion::EndWord), false),
        Key::Char('E') => (Some(Motion::EndWord), true),
        Key::Left => (Some(Motion::Left), k.mods.contains(Mods::SHIFT)),
        Key::Right => (Some(Motion::Right), k.mods.contains(Mods::SHIFT)),
        Key::Up => (Some(Motion::Up), k.mods.contains(Mods::SHIFT)),
        Key::Down => (Some(Motion::Down), k.mods.contains(Mods::SHIFT)),
        Key::Home => (Some(Motion::LineStart), k.mods.contains(Mods::SHIFT)),
        Key::End => (Some(Motion::LineEnd), k.mods.contains(Mods::SHIFT)),
        _ => (None, false),
    };

    if let Some(m) = motion {
        apply_motion(&bytes, sel, m, extend);
    }

    false
}

pub fn handle_insert(
    buffer: &mut Buffer,
    sel: &mut Selection,
    mode: &mut Mode,
    pending_j: &mut bool,
    k: KeyEvent,
) {
    // `jf` Esc-replacement: see `[[feedback-modal-keybindings]]`.
    // If a previous keystroke buffered a literal `j`, this keystroke decides.
    // Pressing `f` collapses the pair to a mode-exit. Anything else emits the
    // buffered `j` first, then processes this key normally. Esc clears the
    // buffered `j` silently. Limitation: with no follow-up key, the `j`
    // stays buffered until something else is typed — a timeout-driven flush
    // is the proper fix and lives behind non-blocking I/O.
    if *pending_j {
        *pending_j = false;
        match k.key {
            Key::Char('f') if k.mods.is_empty() => {
                exit_insert_mode(buffer, sel, mode);
                return;
            }
            Key::Esc => {
                exit_insert_mode(buffer, sel, mode);
                return;
            }
            _ => {
                // Insert the buffered 'j', then fall through to process this
                // key normally on the post-`j` state.
                buffer.insert(sel.head, b"j");
                sel.head += 1;
            }
        }
    }

    match k.key {
        Key::Esc => exit_insert_mode(buffer, sel, mode),
        Key::Enter => {
            buffer.insert(sel.head, b"\n");
            sel.head += 1;
        }
        Key::Backspace => {
            if sel.head > 0 {
                let bytes = collect_bytes(buffer);
                let new_head = prev_char(&bytes, sel.head);
                let len = sel.head - new_head;
                buffer.delete(new_head, len);
                sel.head = new_head;
                if sel.anchor > sel.head {
                    sel.anchor = sel.anchor.saturating_sub(len);
                }
            }
        }
        Key::Tab => {
            buffer.insert(sel.head, b"\t");
            sel.head += 1;
        }
        Key::Left | Key::Right | Key::Up | Key::Down | Key::Home | Key::End => {
            let bytes = collect_bytes(buffer);
            let motion = match k.key {
                Key::Left => Motion::Left,
                Key::Right => Motion::Right,
                Key::Up => Motion::Up,
                Key::Down => Motion::Down,
                Key::Home => Motion::LineStart,
                Key::End => Motion::LineEnd,
                _ => return,
            };
            apply_motion(&bytes, sel, motion, false);
            sel.anchor = sel.head;
        }
        Key::Char(c) => {
            if k.mods.contains(Mods::CTRL) || k.mods.contains(Mods::ALT) {
                return;
            }
            if c == 'j' && k.mods.is_empty() {
                *pending_j = true;
                return;
            }
            let mut buf = [0u8; 4];
            let s = c.encode_utf8(&mut buf);
            buffer.insert(sel.head, s.as_bytes());
            sel.head += s.len();
        }
        _ => {}
    }
}

fn exit_insert_mode(buffer: &Buffer, sel: &mut Selection, mode: &mut Mode) {
    *mode = Mode::Normal;
    let bytes = collect_bytes(buffer);
    if sel.head > sel.anchor {
        sel.head = prev_char(&bytes, sel.head);
    }
    sel.head = snap_to_char_or_last(&bytes, sel.head);
    sel.anchor = snap_to_char_or_last(&bytes, sel.anchor);
}

pub fn handle_search(
    buffer: &Buffer,
    sel: &mut Selection,
    mode: &mut Mode,
    search_input: &mut String,
    search: &mut SearchState,
    ex_message: &mut String,
    k: KeyEvent,
) {
    match k.key {
        Key::Esc => {
            *mode = Mode::Normal;
            search_input.clear();
            // Revert selection to where it was on `/`.
            if let Some(start) = search.start.take() {
                apply_snapshot(sel, start);
            }
            search.preview = None;
        }
        Key::Enter => {
            let pat = search_input.clone();
            *mode = Mode::Normal;
            search_input.clear();
            search.start = None;
            search.preview = None;
            if pat.is_empty() {
                return;
            }
            match regex::bytes::Regex::new(&pat) {
                Ok(re) => {
                    // sel already reflects the first match from incremental
                    // updates; if nothing matched, sel reverted to start.
                    let bytes = collect_bytes(buffer);
                    if re.find(&bytes).is_none() {
                        *ex_message = format!("no match: /{}", pat);
                    }
                    search.pattern = Some(re);
                }
                Err(e) => {
                    *ex_message = format!("regex error: {}", e);
                }
            }
        }
        Key::Backspace => {
            if search_input.pop().is_none() {
                *mode = Mode::Normal;
                if let Some(start) = search.start.take() {
                    apply_snapshot(sel, start);
                }
                search.preview = None;
                return;
            }
            update_search_preview(buffer, sel, search, search_input);
        }
        Key::Char(c) => {
            if k.mods.contains(Mods::CTRL) || k.mods.contains(Mods::ALT) {
                return;
            }
            search_input.push(c);
            update_search_preview(buffer, sel, search, search_input);
        }
        _ => {}
    }
}

/// Recompile the incremental regex from `input` and move the selection to
/// the first match starting at or after `search.start`'s head. On compile
/// failure or no match, the selection reverts to the captured start and
/// no preview is published (so the live highlight clears).
fn update_search_preview(
    buffer: &Buffer,
    sel: &mut Selection,
    search: &mut SearchState,
    input: &str,
) {
    let start = match search.start {
        Some(s) => s,
        None => return,
    };
    if input.is_empty() {
        apply_snapshot(sel, start);
        search.preview = None;
        return;
    }
    let re = match regex::bytes::Regex::new(input) {
        Ok(re) => re,
        Err(_) => {
            // Invalid regex (often: in-flight, e.g. trailing `(`). Don't
            // change sel; just clear preview so the highlight goes away
            // until the user fixes it.
            search.preview = None;
            return;
        }
    };
    let bytes = collect_bytes(buffer);
    apply_snapshot(sel, start);
    let from = next_char_or_end(&bytes, start.head);
    let first = re.find_at(&bytes, from).or_else(|| re.find(&bytes));
    if let Some(m) = first {
        apply_match(sel, &bytes, m.start(), m.end());
    }
    search.preview = Some(re);
}

/// Collect all matches of `re` in `bytes` as (start, end) byte ranges. Used
/// by the renderer to draw live incremental-search highlights.
pub fn all_matches(bytes: &[u8], re: &regex::bytes::Regex) -> Vec<(usize, usize)> {
    re.find_iter(bytes).map(|m| (m.start(), m.end())).collect()
}

/// Find a match and update `sel` to cover it. Forward search starts AFTER the
/// current head's char; backward search finds the last match strictly before
/// the current selection's start. Wraps around if no match is found in the
/// primary direction. Returns true if any match was found.
fn find_and_select(
    sel: &mut Selection,
    bytes: &[u8],
    re: &regex::bytes::Regex,
    forward: bool,
) -> bool {
    if bytes.is_empty() {
        return false;
    }
    if forward {
        let start = next_char_or_end(bytes, sel.head);
        if let Some(m) = re.find_at(bytes, start) {
            apply_match(sel, bytes, m.start(), m.end());
            return true;
        }
        if let Some(m) = re.find(bytes) {
            apply_match(sel, bytes, m.start(), m.end());
            return true;
        }
        false
    } else {
        let before = sel.min();
        let candidates: Vec<_> = re
            .find_iter(bytes)
            .take_while(|m| m.end() <= before)
            .collect();
        if let Some(m) = candidates.last() {
            apply_match(sel, bytes, m.start(), m.end());
            return true;
        }
        if let Some(m) = re.find_iter(bytes).last() {
            apply_match(sel, bytes, m.start(), m.end());
            return true;
        }
        false
    }
}

fn apply_match(sel: &mut Selection, bytes: &[u8], start: usize, end: usize) {
    if start >= end {
        sel.anchor = start;
        sel.head = start;
    } else {
        sel.anchor = start;
        sel.head = snap_to_char_or_last(bytes, end - 1).max(start);
    }
    sel.desired_col = display_col(bytes, line_start(bytes, sel.head), sel.head);
}

/// Handles a key while in Ex mode. Returns `true` if a quit command was issued.
pub fn handle_ex(
    buffer: &Buffer,
    mode: &mut Mode,
    ex_input: &mut String,
    ex_message: &mut String,
    path: Option<&std::path::Path>,
    k: KeyEvent,
) -> bool {
    match k.key {
        Key::Esc => {
            *mode = Mode::Normal;
            ex_input.clear();
            false
        }
        Key::Enter => {
            let cmd = ex_input.trim().to_string();
            *mode = Mode::Normal;
            ex_input.clear();
            execute_ex(buffer, path, &cmd, ex_message)
        }
        Key::Backspace => {
            if ex_input.pop().is_none() {
                *mode = Mode::Normal;
            }
            false
        }
        Key::Char(c) => {
            if k.mods.contains(Mods::CTRL) || k.mods.contains(Mods::ALT) {
                return false;
            }
            ex_input.push(c);
            false
        }
        _ => false,
    }
}

pub fn execute_ex(
    buffer: &Buffer,
    path: Option<&std::path::Path>,
    cmd: &str,
    message: &mut String,
) -> bool {
    match cmd {
        "" => false,
        "w" => match path {
            Some(p) => match save_buffer(buffer, p) {
                Ok(()) => {
                    *message = format!("\"{}\" written", p.display());
                    false
                }
                Err(e) => {
                    *message = format!("write failed: {}", e);
                    false
                }
            },
            None => {
                *message = "no file name (use :w <path>)".to_string();
                false
            }
        },
        "q" => true,
        "wq" => match path {
            Some(p) => match save_buffer(buffer, p) {
                Ok(()) => true,
                Err(e) => {
                    *message = format!("write failed: {}", e);
                    false
                }
            },
            None => {
                *message = "no file name (use :w <path>)".to_string();
                false
            }
        },
        other => {
            *message = format!("unknown command: :{}", other);
            false
        }
    }
}

pub fn save_buffer(buffer: &Buffer, path: &std::path::Path) -> io::Result<()> {
    use std::io::Write;
    let parent = path.parent().unwrap_or_else(|| std::path::Path::new("."));
    let file_name = path
        .file_name()
        .ok_or_else(|| io::Error::new(io::ErrorKind::InvalidInput, "path has no file name"))?;
    let mut temp_name = std::ffi::OsString::from(".medit-tmp-");
    temp_name.push(file_name);
    let temp_path = parent.join(temp_name);
    {
        let mut f = std::fs::File::create(&temp_path)?;
        for slice in buffer.slices() {
            f.write_all(slice)?;
        }
        f.sync_all()?;
    }
    std::fs::rename(&temp_path, path)?;
    Ok(())
}

pub fn apply_motion(bytes: &[u8], sel: &mut Selection, motion: Motion, extend: bool) {
    let old_head = sel.head;
    let (new_head, update_desired) = match motion {
        Motion::Left => (prev_char(bytes, sel.head), true),
        Motion::Right => (next_char(bytes, sel.head), true),
        Motion::Up => {
            let ls = line_start(bytes, sel.head);
            if ls == 0 {
                return;
            }
            let prev_ls = line_start(bytes, ls - 1);
            (offset_at_col(bytes, prev_ls, sel.desired_col), false)
        }
        Motion::Down => {
            let le = line_end(bytes, sel.head);
            if le >= bytes.len() {
                return;
            }
            (offset_at_col(bytes, le + 1, sel.desired_col), false)
        }
        Motion::LineStart => (line_start(bytes, sel.head), true),
        Motion::LineEnd => (end_of_line(bytes, sel.head), true),
        Motion::NextWord => (motion_word_forward(bytes, sel.head), true),
        Motion::PrevWord => (motion_word_backward(bytes, sel.head), true),
        Motion::EndWord => (motion_word_end(bytes, sel.head), true),
    };

    let is_object = matches!(
        motion,
        Motion::NextWord | Motion::PrevWord | Motion::EndWord
    );
    sel.head = new_head;
    if !extend {
        sel.anchor = if is_object { old_head } else { new_head };
    }
    if update_desired {
        sel.desired_col = display_col(bytes, line_start(bytes, new_head), new_head);
    }
}

// ===== Operators =====

pub fn op_yank(buffer: &Buffer, sel: &Selection, registers: &mut Registers) {
    let bytes = collect_bytes(buffer);
    if bytes.is_empty() {
        return;
    }
    let min = sel.min();
    let last_byte = next_char_or_end(&bytes, sel.max());
    if last_byte > min {
        registers.default = bytes[min..last_byte].to_vec();
    }
}

pub fn op_delete(buffer: &mut Buffer, sel: &mut Selection, registers: &mut Registers) {
    let bytes = collect_bytes(buffer);
    if bytes.is_empty() {
        return;
    }
    let min = sel.min();
    let last_byte = next_char_or_end(&bytes, sel.max());
    let length = last_byte.saturating_sub(min);
    if length > 0 {
        registers.default = bytes[min..last_byte].to_vec();
        buffer.mark_commit_point(snapshot_of(sel));
        buffer.delete(min, length);
    }
    let new_bytes = collect_bytes(buffer);
    let new_head = snap_to_char_or_last(&new_bytes, min);
    sel.head = new_head;
    sel.anchor = new_head;
    sel.desired_col = display_col(&new_bytes, line_start(&new_bytes, new_head), new_head);
}

pub fn op_change(
    buffer: &mut Buffer,
    sel: &mut Selection,
    mode: &mut Mode,
    registers: &mut Registers,
) {
    let bytes = collect_bytes(buffer);
    let min = sel.min();
    let last_byte = next_char_or_end(&bytes, sel.max());
    let length = last_byte.saturating_sub(min);
    if length > 0 {
        registers.default = bytes[min..last_byte].to_vec();
        buffer.mark_commit_point(snapshot_of(sel));
        buffer.delete(min, length);
    } else {
        buffer.mark_commit_point(snapshot_of(sel));
    }
    sel.head = min;
    sel.anchor = min;
    *mode = Mode::Insert;
}

pub fn op_paste_after(buffer: &mut Buffer, sel: &mut Selection, registers: &Registers) {
    if registers.default.is_empty() {
        return;
    }
    let bytes = collect_bytes(buffer);
    let insert_at = if bytes.is_empty() {
        0
    } else {
        let max = sel.max();
        if bytes.get(max) == Some(&b'\n') {
            max
        } else {
            next_char_or_end(&bytes, max)
        }
    };
    let len = registers.default.len();
    buffer.mark_commit_point(snapshot_of(sel));
    buffer.insert(insert_at, &registers.default);
    sel.anchor = insert_at;
    let new_bytes = collect_bytes(buffer);
    let target = insert_at + len - 1;
    sel.head = snap_to_char_or_last(&new_bytes, target);
    sel.desired_col = display_col(&new_bytes, line_start(&new_bytes, sel.head), sel.head);
}

pub fn op_paste_before(buffer: &mut Buffer, sel: &mut Selection, registers: &Registers) {
    if registers.default.is_empty() {
        return;
    }
    let insert_at = sel.min();
    let len = registers.default.len();
    buffer.mark_commit_point(snapshot_of(sel));
    buffer.insert(insert_at, &registers.default);
    sel.anchor = insert_at;
    let new_bytes = collect_bytes(buffer);
    let target = insert_at + len - 1;
    sel.head = snap_to_char_or_last(&new_bytes, target);
    sel.desired_col = display_col(&new_bytes, line_start(&new_bytes, sel.head), sel.head);
}

pub fn op_open_below(buffer: &mut Buffer, sel: &mut Selection, mode: &mut Mode) {
    let bytes = collect_bytes(buffer);
    let le = line_end(&bytes, sel.head);
    buffer.mark_commit_point(snapshot_of(sel));
    buffer.insert(le, b"\n");
    sel.head = le + 1;
    sel.anchor = le + 1;
    *mode = Mode::Insert;
}

pub fn op_open_above(buffer: &mut Buffer, sel: &mut Selection, mode: &mut Mode) {
    let bytes = collect_bytes(buffer);
    let ls = line_start(&bytes, sel.head);
    buffer.mark_commit_point(snapshot_of(sel));
    buffer.insert(ls, b"\n");
    sel.head = ls;
    sel.anchor = ls;
    *mode = Mode::Insert;
}

pub fn op_undo(buffer: &mut Buffer, sel: &mut Selection) {
    if let Some(snap) = buffer.undo(snapshot_of(sel)) {
        apply_snapshot(sel, snap);
        // Defensive clamp in case the saved offsets fall outside the
        // restored buffer (shouldn't happen with paired commits, but cheap).
        let bytes = collect_bytes(buffer);
        sel.head = snap_to_char_or_last(&bytes, sel.head);
        sel.anchor = snap_to_char_or_last(&bytes, sel.anchor);
    }
}

/// Byte offset of the start of the last non-empty line in the buffer.
/// For empty buffer or single-line buffer (including ones with a trailing
/// newline), returns 0.
pub fn last_line_start(bytes: &[u8]) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let mut p = bytes.len();
    while p > 0 {
        p -= 1;
        if bytes[p] == b'\n' && p + 1 < bytes.len() {
            return p + 1;
        }
    }
    0
}

pub fn op_redo(buffer: &mut Buffer, sel: &mut Selection) {
    if let Some(snap) = buffer.redo(snapshot_of(sel)) {
        apply_snapshot(sel, snap);
        let bytes = collect_bytes(buffer);
        sel.head = snap_to_char_or_last(&bytes, sel.head);
        sel.anchor = snap_to_char_or_last(&bytes, sel.anchor);
    }
}

// ===== Word motions =====

pub fn is_word_byte(b: u8) -> bool {
    b.is_ascii_alphanumeric() || b == b'_' || b >= 0x80
}

pub fn is_whitespace_byte(b: u8) -> bool {
    matches!(b, b' ' | b'\t' | b'\n' | b'\r')
}

pub fn motion_word_forward(bytes: &[u8], from: usize) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let mut i = from;
    if let Some(&b) = bytes.get(i) {
        i = (i + utf8_len(b)).min(bytes.len());
    }
    while i < bytes.len() && is_whitespace_byte(bytes[i]) {
        i += 1;
    }
    if let Some(&b) = bytes.get(i) {
        let word = is_word_byte(b);
        while i < bytes.len() {
            let bi = bytes[i];
            if is_whitespace_byte(bi) || is_word_byte(bi) != word {
                break;
            }
            i += utf8_len(bi);
        }
    }
    if i > from {
        prev_char(bytes, i)
    } else {
        from
    }
}

pub fn motion_word_backward(bytes: &[u8], from: usize) -> usize {
    if from == 0 {
        return 0;
    }
    let mut i = prev_char(bytes, from);
    while i > 0 && bytes.get(i).map_or(false, |&b| is_whitespace_byte(b)) {
        i = prev_char(bytes, i);
    }
    let word = match bytes.get(i) {
        Some(&b) => is_word_byte(b),
        None => return i,
    };
    while i > 0 {
        let p = prev_char(bytes, i);
        let bp = match bytes.get(p) {
            Some(&b) => b,
            None => break,
        };
        if is_whitespace_byte(bp) || is_word_byte(bp) != word {
            break;
        }
        i = p;
    }
    i
}

pub fn motion_word_end(bytes: &[u8], from: usize) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let mut i = from;
    if let Some(&b) = bytes.get(i) {
        i = (i + utf8_len(b)).min(bytes.len());
    }
    while i < bytes.len() && is_whitespace_byte(bytes[i]) {
        i += 1;
    }
    if let Some(&b) = bytes.get(i) {
        let word = is_word_byte(b);
        let mut last = i;
        while i < bytes.len() {
            let bi = bytes[i];
            if is_whitespace_byte(bi) || is_word_byte(bi) != word {
                break;
            }
            last = i;
            i += utf8_len(bi);
        }
        last
    } else {
        prev_char(bytes, bytes.len())
    }
}

// ===== Buffer helpers =====

pub fn collect_bytes(buffer: &Buffer) -> Vec<u8> {
    let mut v = Vec::with_capacity(buffer.len());
    for s in buffer.slices() {
        v.extend_from_slice(s);
    }
    v
}

pub fn utf8_len(first: u8) -> usize {
    if first & 0x80 == 0 {
        1
    } else if first & 0xE0 == 0xC0 {
        2
    } else if first & 0xF0 == 0xE0 {
        3
    } else if first & 0xF8 == 0xF0 {
        4
    } else {
        1
    }
}

pub fn prev_char(bytes: &[u8], offset: usize) -> usize {
    if offset == 0 {
        return 0;
    }
    let mut p = offset - 1;
    while p > 0 {
        match bytes.get(p) {
            Some(&b) if b & 0xC0 == 0x80 => p -= 1,
            _ => break,
        }
    }
    p
}

pub fn next_char(bytes: &[u8], offset: usize) -> usize {
    let b = match bytes.get(offset) {
        Some(&b) => b,
        None => return offset,
    };
    let n = utf8_len(b);
    let candidate = offset + n;
    if candidate >= bytes.len() {
        offset
    } else {
        candidate
    }
}

pub fn next_char_or_end(bytes: &[u8], offset: usize) -> usize {
    let b = match bytes.get(offset) {
        Some(&b) => b,
        None => return bytes.len(),
    };
    (offset + utf8_len(b)).min(bytes.len())
}

pub fn snap_to_char_or_last(bytes: &[u8], offset: usize) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let clamped = offset.min(bytes.len());
    if clamped == bytes.len() {
        return prev_char(bytes, bytes.len());
    }
    let mut p = clamped;
    while p > 0 {
        match bytes.get(p) {
            Some(&b) if b & 0xC0 == 0x80 => p -= 1,
            _ => break,
        }
    }
    p
}

pub fn line_start(bytes: &[u8], offset: usize) -> usize {
    if offset == 0 {
        return 0;
    }
    let mut p = offset;
    while p > 0 {
        p -= 1;
        if bytes.get(p) == Some(&b'\n') {
            return p + 1;
        }
    }
    0
}

pub fn line_end(bytes: &[u8], offset: usize) -> usize {
    let mut p = offset;
    while p < bytes.len() {
        if bytes.get(p) == Some(&b'\n') {
            return p;
        }
        p += 1;
    }
    bytes.len()
}

pub fn end_of_line(bytes: &[u8], offset: usize) -> usize {
    let ls = line_start(bytes, offset);
    let le = line_end(bytes, offset);
    if le == ls {
        return ls;
    }
    prev_char(bytes, le)
}

pub fn line_index(bytes: &[u8], offset: usize) -> usize {
    let end = offset.min(bytes.len());
    bytes[..end].iter().filter(|&&b| b == b'\n').count()
}

pub fn byte_at_line(bytes: &[u8], line: usize) -> usize {
    if line == 0 {
        return 0;
    }
    let mut seen = 0usize;
    for (i, &b) in bytes.iter().enumerate() {
        if b == b'\n' {
            seen += 1;
            if seen == line {
                return i + 1;
            }
        }
    }
    bytes.len()
}

pub fn ensure_visible(bytes: &[u8], head: usize, top_line: &mut usize, viewport_rows: usize) {
    if viewport_rows == 0 {
        return;
    }
    let head_line = line_index(bytes, head);
    if head_line < *top_line {
        *top_line = head_line;
    } else if head_line >= top_line.saturating_add(viewport_rows) {
        *top_line = head_line + 1 - viewport_rows;
    }
}

pub fn display_col(bytes: &[u8], from: usize, offset: usize) -> usize {
    let mut col: usize = 1;
    let mut i = from;
    while i < offset {
        let b = match bytes.get(i) {
            Some(&b) => b,
            None => break,
        };
        match b {
            b'\n' => break,
            b'\t' => {
                col += 4 - ((col - 1) % 4);
                i += 1;
            }
            b'\r' => {
                i += 1;
            }
            c if c < 0x20 => {
                col += 2;
                i += 1;
            }
            _ => {
                let n = utf8_len(b);
                col += 1;
                i += n.max(1);
            }
        }
    }
    col
}

pub fn offset_at_col(bytes: &[u8], from: usize, target_col: usize) -> usize {
    let mut col: usize = 1;
    let mut i = from;
    let mut last_char_start = from;
    while i < bytes.len() {
        let b = match bytes.get(i) {
            Some(&b) => b,
            None => break,
        };
        if b == b'\n' {
            return last_char_start;
        }
        if col >= target_col {
            return i;
        }
        last_char_start = i;
        match b {
            b'\t' => {
                col += 4 - ((col - 1) % 4);
                i += 1;
            }
            b'\r' => {
                i += 1;
            }
            c if c < 0x20 => {
                col += 2;
                i += 1;
            }
            _ => {
                let n = utf8_len(b);
                col += 1;
                i += n.max(1);
            }
        }
    }
    if i >= bytes.len() && last_char_start < bytes.len() {
        last_char_start
    } else {
        i
    }
}
