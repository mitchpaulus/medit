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
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum SearchKind {
    /// `/`: find next match; selection jumps to the first match.
    #[default]
    Find,
    /// `s`: select all matches within the current primary selection; each
    /// match becomes its own selection.
    SelectWithin,
}

#[derive(Default)]
pub struct SearchState {
    pub pattern: Option<regex::bytes::Regex>,
    pub preview: Option<regex::bytes::Regex>,
    pub start: Option<CursorSnapshot>,
    pub kind: SearchKind,
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

/// A non-empty collection of selections, one of which is "primary". The
/// primary determines viewport scroll, the cursor position rendered as a
/// block, and which selection drives modes like Search (where we move only
/// the primary as the user types).
pub struct Selections {
    list: Vec<Selection>,
    primary: usize,
}

impl Selections {
    pub fn new() -> Self {
        Self {
            list: vec![Selection::new()],
            primary: 0,
        }
    }

    pub fn primary(&self) -> &Selection {
        &self.list[self.primary]
    }

    pub fn primary_mut(&mut self) -> &mut Selection {
        &mut self.list[self.primary]
    }

    pub fn primary_index(&self) -> usize {
        self.primary
    }

    pub fn iter(&self) -> impl Iterator<Item = &Selection> {
        self.list.iter()
    }

    pub fn iter_mut(&mut self) -> impl Iterator<Item = &mut Selection> {
        self.list.iter_mut()
    }

    pub fn len(&self) -> usize {
        self.list.len()
    }

    pub fn reduce_to_primary(&mut self) {
        let p = self.list[self.primary];
        self.list = vec![p];
        self.primary = 0;
    }

    /// Replace the whole selection list. `primary` must be a valid index
    /// into `selections`; ignored otherwise.
    pub fn replace(&mut self, selections: Vec<Selection>, primary: usize) {
        if selections.is_empty() {
            return;
        }
        self.primary = primary.min(selections.len() - 1);
        self.list = selections;
    }

    /// Iterate selections in buffer order, returning indices into the
    /// internal list. Used by ops that need a deterministic mutation order
    /// for offset adjustment.
    fn indices_by_position(&self) -> Vec<usize> {
        let mut idx: Vec<usize> = (0..self.list.len()).collect();
        idx.sort_by_key(|&i| self.list[i].min());
        idx
    }

    /// Append a new selection and make it primary.
    pub fn append_as_primary(&mut self, sel: Selection) {
        self.list.push(sel);
        self.primary = self.list.len() - 1;
    }

    /// Set primary to a specific index (clamped to valid range).
    pub fn set_primary(&mut self, idx: usize) {
        if !self.list.is_empty() {
            self.primary = idx.min(self.list.len() - 1);
        }
    }

    /// Rotate which selection is primary by `step` (positive = forward in
    /// the list, negative = backward), wrapping around.
    pub fn rotate_primary(&mut self, step: i32) {
        if self.list.is_empty() {
            return;
        }
        let n = self.list.len() as i32;
        let mut p = self.primary as i32 + step;
        p = ((p % n) + n) % n;
        self.primary = p as usize;
    }
}

impl Default for Selections {
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

#[derive(Debug, Clone, Copy)]
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

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ObjectKind {
    Inner,
    Around,
}

/// `f` / `F` / `t` / `T` line-bounded char search variants.
/// - `To` lands the head on the matched char (`f`, `F`).
/// - `Till` lands one char shy of the match (`t`, `T`).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum FindOp {
    ForwardTo,
    BackwardTo,
    ForwardTill,
    BackwardTill,
}

/// Out-of-band action requested by the modal layer that the main loop has
/// to dispatch (because it needs resources the handler doesn't have, e.g.
/// the LSP client). Cleared after handling.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LspAction {
    GotoDefinition,
    NextDiagnostic,
    PrevDiagnostic,
}

/// `]` and `[` prefixes for jump-list-style navigation. Consume a follow-up
/// key (`d` for diagnostics, future: `e`/`q`/...).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum BracketDir {
    Next,
    Prev,
}

/// Actions requested from Ex mode that touch the buffer registry (which
/// `handle_ex` doesn't have access to). The main loop dispatches and
/// clears.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum ExAction {
    OpenFile(std::path::PathBuf),
    NextBuffer,
    PrevBuffer,
    ListBuffers,
}

/// Compute the byte range `[start, end)` of a text object containing
/// `offset`. Returns `None` if no object of that kind exists here. Used by
/// `<a-i>X` / `<a-a>X` text-object selectors.
pub fn text_object(bytes: &[u8], offset: usize, kind: ObjectKind, key: Key) -> Option<(usize, usize)> {
    match key {
        Key::Char('w') => word_object(bytes, offset, kind),
        Key::Char('p') => paragraph_object(bytes, offset, kind),
        Key::Char('"') => quoted_object(bytes, offset, kind, b'"'),
        Key::Char('\'') => quoted_object(bytes, offset, kind, b'\''),
        Key::Char('`') => quoted_object(bytes, offset, kind, b'`'),
        Key::Char('(') | Key::Char(')') => bracket_object(bytes, offset, kind, b'(', b')'),
        Key::Char('{') | Key::Char('}') => bracket_object(bytes, offset, kind, b'{', b'}'),
        Key::Char('[') | Key::Char(']') => bracket_object(bytes, offset, kind, b'[', b']'),
        _ => None,
    }
}

fn apply_object_for_all(sels: &mut Selections, bytes: &[u8], kind: ObjectKind, key: Key) {
    for sel in sels.iter_mut() {
        if let Some((s, e)) = text_object(bytes, sel.head, kind, key) {
            sel.anchor = s;
            sel.head = if e > s {
                snap_to_char_or_last(bytes, e - 1).max(s)
            } else {
                s
            };
            sel.desired_col = display_col(bytes, line_start(bytes, sel.head), sel.head);
        }
    }
}

fn word_object(bytes: &[u8], offset: usize, kind: ObjectKind) -> Option<(usize, usize)> {
    if offset >= bytes.len() {
        return None;
    }
    if !is_word_byte(bytes[offset]) {
        return None;
    }
    // Find start
    let mut start = offset;
    while start > 0 {
        let p = prev_char(bytes, start);
        if bytes.get(p).map_or(false, |&b| is_word_byte(b)) {
            start = p;
        } else {
            break;
        }
    }
    // Find end (exclusive)
    let mut end = offset;
    while end < bytes.len() {
        let b = match bytes.get(end) {
            Some(&b) => b,
            None => break,
        };
        if !is_word_byte(b) {
            break;
        }
        end += utf8_len(b);
    }
    if matches!(kind, ObjectKind::Around) {
        // Include trailing whitespace (Vim's `aw` semantics).
        while end < bytes.len() && bytes[end] == b' ' {
            end += 1;
        }
    }
    Some((start, end))
}

fn paragraph_object(bytes: &[u8], offset: usize, kind: ObjectKind) -> Option<(usize, usize)> {
    if bytes.is_empty() {
        return None;
    }
    // Walk back to first non-blank line of this paragraph.
    let mut start = line_start(bytes, offset);
    while start > 0 {
        let prev_line_end = start - 1;
        let prev_line_start = line_start(bytes, prev_line_end);
        if prev_line_start == prev_line_end {
            // prev line is blank; stop.
            break;
        }
        start = prev_line_start;
    }
    // Walk forward to last non-blank line.
    let mut end = line_end(bytes, offset);
    loop {
        if end >= bytes.len() {
            break;
        }
        let next_line_start = end + 1;
        if next_line_start >= bytes.len() {
            break;
        }
        let next_line_end = line_end(bytes, next_line_start);
        if next_line_start == next_line_end {
            // next line is blank; stop.
            break;
        }
        end = next_line_end;
    }
    if matches!(kind, ObjectKind::Around) {
        // Include trailing blank line(s).
        while end < bytes.len() && bytes[end] == b'\n' {
            end += 1;
        }
    }
    Some((start, end))
}

fn quoted_object(bytes: &[u8], offset: usize, kind: ObjectKind, q: u8) -> Option<(usize, usize)> {
    if bytes.is_empty() {
        return None;
    }
    // Find left quote at or before offset.
    let mut left = None;
    let mut i = offset.min(bytes.len().saturating_sub(1));
    loop {
        if bytes.get(i) == Some(&q) {
            left = Some(i);
            break;
        }
        if i == 0 {
            break;
        }
        i -= 1;
    }
    let left = left?;
    // Find right quote strictly after left.
    let mut right = None;
    let mut j = left + 1;
    while j < bytes.len() {
        if bytes[j] == q {
            right = Some(j);
            break;
        }
        j += 1;
    }
    let right = right?;
    match kind {
        ObjectKind::Inner => Some((left + 1, right)),
        ObjectKind::Around => Some((left, right + 1)),
    }
}

fn bracket_object(
    bytes: &[u8],
    offset: usize,
    kind: ObjectKind,
    open: u8,
    close: u8,
) -> Option<(usize, usize)> {
    if bytes.is_empty() {
        return None;
    }
    // If offset is on a closing bracket, treat as just-inside.
    let start_search = if bytes.get(offset) == Some(&close) && offset > 0 {
        offset - 1
    } else {
        offset
    };
    // Walk back with depth counting.
    let mut depth: i32 = 1;
    let mut i = start_search;
    let left = loop {
        if i >= bytes.len() {
            return None;
        }
        let b = bytes[i];
        if b == close && i != start_search {
            depth += 1;
        } else if b == open {
            depth -= 1;
            if depth == 0 {
                break i;
            }
        }
        if i == 0 {
            return None;
        }
        i -= 1;
    };
    // Walk forward with depth counting.
    let mut depth: i32 = 1;
    let mut j = left + 1;
    let right = loop {
        if j >= bytes.len() {
            return None;
        }
        let b = bytes[j];
        if b == open {
            depth += 1;
        } else if b == close {
            depth -= 1;
            if depth == 0 {
                break j;
            }
        }
        j += 1;
    };
    match kind {
        ObjectKind::Inner => Some((left + 1, right)),
        ObjectKind::Around => Some((left, right + 1)),
    }
}

/// Returns `true` if this key was a quit request.
/// `cached_bytes` / `cached_line_starts`: pre-built flat byte view and
/// line-starts index from the caller's cache. Both stay valid through
/// this call provided no mutating op is invoked; mutating ops (`d`, `c`,
/// `p`, etc.) each re-collect their own fresh bytes internally so they
/// don't rely on these slices.
#[allow(clippy::too_many_arguments)]
pub fn handle_normal(
    buffer: &mut Buffer,
    sels: &mut Selections,
    mode: &mut Mode,
    registers: &mut Registers,
    pending_g: &mut bool,
    pending_z: &mut bool,
    pending_object: &mut Option<ObjectKind>,
    pending_find: &mut Option<FindOp>,
    pending_bracket: &mut Option<BracketDir>,
    search: &mut SearchState,
    lsp_action: &mut Option<LspAction>,
    top_line: &mut usize,
    viewport_rows: usize,
    cached_bytes: &[u8],
    cached_line_starts: &[usize],
    k: KeyEvent,
) -> bool {
    let bytes: &[u8] = cached_bytes;
    let line_starts: &[usize] = cached_line_starts;

    // Resolve text-object selector pending from a previous Alt-i / Alt-a.
    if let Some(kind) = pending_object.take() {
        if k.mods.is_empty() {
            apply_object_for_all(sels, bytes, kind, k.key);
        }
        return false;
    }

    // Consume the follow-up key for a pending `]` / `[` prefix.
    if let Some(dir) = pending_bracket.take() {
        if k.mods.is_empty() {
            if let Key::Char('d') = k.key {
                *lsp_action = Some(match dir {
                    BracketDir::Next => LspAction::NextDiagnostic,
                    BracketDir::Prev => LspAction::PrevDiagnostic,
                });
            }
        }
        return false;
    }

    if k.mods.is_empty() && k.key == Key::Char(']') {
        *pending_bracket = Some(BracketDir::Next);
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('[') {
        *pending_bracket = Some(BracketDir::Prev);
        return false;
    }

    // Consume the char argument for a pending `f`/`F`/`t`/`T`. Search
    // within the current line of each selection; selections whose line
    // has no match are left in place. Collapses the selection (Vim-style
    // move).
    if let Some(op) = pending_find.take() {
        if let Key::Char(c) = k.key {
            for sel in sels.iter_mut() {
                if let Some(off) = find_char_on_line(bytes, sel.head, c, op) {
                    sel.head = off;
                    sel.anchor = off;
                }
            }
        }
        return false;
    }

    // Alt+i / Alt+a enter "select inner / around object" pending state.
    if k.mods == Mods::ALT && k.key == Key::Char('i') {
        *pending_object = Some(ObjectKind::Inner);
        return false;
    }
    if k.mods == Mods::ALT && k.key == Key::Char('a') {
        *pending_object = Some(ObjectKind::Around);
        return false;
    }

    if *pending_g {
        *pending_g = false;
        if k.mods.is_empty() {
            match k.key {
                Key::Char('g') => {
                    sels.reduce_to_primary();
                    let new_head = if bytes.is_empty() {
                        0
                    } else {
                        snap_to_char_or_last(bytes, 0)
                    };
                    let sel = sels.primary_mut();
                    sel.anchor = new_head;
                    sel.head = new_head;
                    sel.desired_col = 1;
                }
                Key::Char('d') => {
                    *lsp_action = Some(LspAction::GotoDefinition);
                }
                _ => {}
            }
        }
        return false;
    }

    if k.mods.is_empty() && k.key == Key::Char('g') {
        *pending_g = true;
        return false;
    }

    // z-prefix: `zz` centers the cursor's line in the viewport.
    if *pending_z {
        *pending_z = false;
        if k.mods.is_empty() && k.key == Key::Char('z') {
            let head_line = line_index(bytes, sels.primary().head);
            let half = viewport_rows / 2;
            *top_line = head_line.saturating_sub(half);
        }
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('z') {
        *pending_z = true;
        return false;
    }

    // `f<c>` / `F<c>` / `t<c>` / `T<c>`: line-bounded char search.
    // `f`/`F` land on the char; `t`/`T` land one position shy. Sets a
    // pending-find flag that consumes the very next keystroke as the
    // char argument.
    if k.mods.is_empty() {
        let op = match k.key {
            Key::Char('f') => Some(FindOp::ForwardTo),
            Key::Char('F') => Some(FindOp::BackwardTo),
            Key::Char('t') => Some(FindOp::ForwardTill),
            Key::Char('T') => Some(FindOp::BackwardTill),
            _ => None,
        };
        if let Some(op) = op {
            *pending_find = Some(op);
            return false;
        }
    }

    // Ctrl+D / Ctrl+U: move down/up 10 lines (per-cursor).
    if k.mods == Mods::CTRL && k.key == Key::Char('d') {
        for sel in sels.iter_mut() {
            move_line_relative_cached(bytes, line_starts, sel, 10);
        }
        return false;
    }
    if k.mods == Mods::CTRL && k.key == Key::Char('u') {
        for sel in sels.iter_mut() {
            move_line_relative_cached(bytes, line_starts, sel, -10);
        }
        return false;
    }

    // `{` and `}` jump by paragraph. `}` lands on the last non-blank line of
    // the current paragraph (or the next, if already there); `{` lands on
    // the first non-blank line. Unlike Vim, we never stop on the blank line
    // between paragraphs.
    if k.mods.is_empty() && k.key == Key::Char('}') {
        for sel in sels.iter_mut() {
            let new_head = paragraph_end_forward(bytes, sel.head);
            sel.head = new_head;
            sel.anchor = new_head;
            sel.desired_col = display_col(bytes, line_start(bytes, new_head), new_head);
        }
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('{') {
        for sel in sels.iter_mut() {
            let new_head = paragraph_start_backward(bytes, sel.head);
            sel.head = new_head;
            sel.anchor = new_head;
            sel.desired_col = display_col(bytes, line_start(bytes, new_head), new_head);
        }
        return false;
    }

    if k.mods.is_empty() && k.key == Key::Char('q') {
        return true;
    }

    // G: jump to start of last non-empty line. Slides (collapses to primary).
    if k.mods.is_empty() && k.key == Key::Char('G') {
        sels.reduce_to_primary();
        let new_head = snap_to_char_or_last(bytes, last_line_start(bytes));
        let sel = sels.primary_mut();
        sel.anchor = new_head;
        sel.head = new_head;
        sel.desired_col = display_col(bytes, line_start(bytes, new_head), new_head);
        return false;
    }

    // / enters Search mode (single-cursor); on Enter the primary jumps to
    // the first match and all other selections collapse to primary.
    if k.mods.is_empty() && k.key == Key::Char('/') {
        sels.reduce_to_primary();
        search.start = Some(snapshot_of(sels.primary()));
        search.preview = None;
        search.kind = SearchKind::Find;
        *mode = Mode::Search;
        return false;
    }
    // s: enter Search mode in "select-within" kind. On Enter, replace
    // selections with one per match found inside the current primary's
    // range.
    if k.mods.is_empty() && k.key == Key::Char('s') {
        search.start = Some(snapshot_of(sels.primary()));
        search.preview = None;
        search.kind = SearchKind::SelectWithin;
        *mode = Mode::Search;
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('n') {
        if let Some(re) = search.pattern.as_ref() {
            sels.reduce_to_primary();
            find_and_select(sels.primary_mut(), bytes, re, true);
        }
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('N') {
        if let Some(re) = search.pattern.as_ref() {
            sels.reduce_to_primary();
            find_and_select(sels.primary_mut(), bytes, re, false);
        }
        return false;
    }
    // Ctrl+J / Ctrl+K: add the next / previous occurrence of whatever's
    // most natural to search for. If the primary selection is extended
    // (anchor ≠ head), use its bytes as a literal pattern. Otherwise fall
    // back to the last committed search regex. The derived pattern also
    // becomes the new search pattern so n/N continue iterating it.
    if k.mods == Mods::CTRL && k.key == Key::Char('j') {
        add_next_smart(sels, bytes, search, true);
        return false;
    }
    if k.mods == Mods::CTRL && k.key == Key::Char('k') {
        add_next_smart(sels, bytes, search, false);
        return false;
    }

    // Multi-cursor management.
    if k.mods.is_empty() && k.key == Key::Char(',') {
        sels.reduce_to_primary();
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('<') {
        sels.rotate_primary(-1);
        return false;
    }
    if k.mods.is_empty() && k.key == Key::Char('>') {
        sels.rotate_primary(1);
        return false;
    }

    if k.mods.is_empty() {
        match k.key {
            Key::Char('i') => {
                for sel in sels.iter_mut() {
                    let min = sel.min();
                    sel.anchor = min;
                    sel.head = min;
                }
                buffer.mark_commit_point(snapshot_of(sels.primary()));
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('a') => {
                for sel in sels.iter_mut() {
                    let after = next_char_or_end(bytes, sel.max());
                    sel.anchor = after;
                    sel.head = after;
                }
                buffer.mark_commit_point(snapshot_of(sels.primary()));
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('I') => {
                for sel in sels.iter_mut() {
                    let ls = line_start(bytes, sel.head);
                    sel.anchor = ls;
                    sel.head = ls;
                }
                buffer.mark_commit_point(snapshot_of(sels.primary()));
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('A') => {
                for sel in sels.iter_mut() {
                    let le = line_end(bytes, sel.head);
                    sel.anchor = le;
                    sel.head = le;
                }
                buffer.mark_commit_point(snapshot_of(sels.primary()));
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('u') => {
                sels.reduce_to_primary();
                op_undo(buffer, sels.primary_mut());
                return false;
            }
            Key::Char('U') => {
                sels.reduce_to_primary();
                op_redo(buffer, sels.primary_mut());
                return false;
            }
            Key::Char(';') => {
                for sel in sels.iter_mut() {
                    sel.anchor = sel.head;
                }
                return false;
            }
            Key::Char(':') => {
                *mode = Mode::Ex;
                return false;
            }
            Key::Char('d') => {
                op_delete_multi(buffer, sels, registers);
                return false;
            }
            Key::Char('c') => {
                op_change_multi(buffer, sels, mode, registers);
                return false;
            }
            Key::Char('y') => {
                op_yank(buffer, sels.primary(), registers);
                return false;
            }
            Key::Char('p') => {
                sels.reduce_to_primary();
                op_paste_after(buffer, sels.primary_mut(), registers);
                return false;
            }
            Key::Char('P') => {
                sels.reduce_to_primary();
                op_paste_before(buffer, sels.primary_mut(), registers);
                return false;
            }
            Key::Char('o') => {
                sels.reduce_to_primary();
                op_open_below(buffer, sels.primary_mut(), mode);
                return false;
            }
            Key::Char('O') => {
                sels.reduce_to_primary();
                op_open_above(buffer, sels.primary_mut(), mode);
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
        for sel in sels.iter_mut() {
            apply_motion(bytes, sel, m, extend);
        }
    }

    false
}

pub fn handle_insert(
    buffer: &mut Buffer,
    sels: &mut Selections,
    mode: &mut Mode,
    pending_j: &mut bool,
    registers: &mut Registers,
    k: KeyEvent,
) {
    if *pending_j {
        *pending_j = false;
        match k.key {
            Key::Char('f') if k.mods.is_empty() => {
                exit_insert_mode_multi(buffer, sels, mode);
                return;
            }
            Key::Esc => {
                exit_insert_mode_multi(buffer, sels, mode);
                return;
            }
            _ => {
                insert_text_multi(buffer, sels, b"j");
            }
        }
    }

    match k.key {
        Key::Esc => exit_insert_mode_multi(buffer, sels, mode),
        Key::Enter => insert_text_multi(buffer, sels, b"\n"),
        Key::Backspace => backspace_multi(buffer, sels),
        Key::Tab => insert_text_multi(buffer, sels, b"\t"),
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
            for sel in sels.iter_mut() {
                apply_motion(&bytes, sel, motion, false);
                sel.anchor = sel.head;
            }
        }
        Key::Char(c) => {
            if k.mods.contains(Mods::ALT) {
                // Emacs-readline meta bindings.
                match c {
                    'b' => {
                        let bytes = collect_bytes(buffer);
                        move_in_insert(&bytes, sels, |b, s| {
                            s.head = motion_word_backward(b, s.head);
                        });
                    }
                    'f' => {
                        let bytes = collect_bytes(buffer);
                        move_in_insert(&bytes, sels, |b, s| {
                            // motion_word_forward lands on the last char of
                            // the word (Kakoune semantics); emacs M-f lands
                            // one past, so we bump by next_char_or_end.
                            let end = motion_word_forward(b, s.head);
                            s.head = next_char_or_end(b, end);
                        });
                    }
                    _ => {}
                }
                return;
            }
            if k.mods.contains(Mods::CTRL) {
                // Emacs-readline ctrl bindings.
                match c {
                    'a' => {
                        let bytes = collect_bytes(buffer);
                        move_in_insert(&bytes, sels, |b, s| s.head = line_start(b, s.head));
                    }
                    'e' => {
                        let bytes = collect_bytes(buffer);
                        move_in_insert(&bytes, sels, |b, s| s.head = line_end(b, s.head));
                    }
                    'b' => {
                        let bytes = collect_bytes(buffer);
                        move_in_insert(&bytes, sels, |b, s| s.head = prev_char(b, s.head));
                    }
                    'f' => {
                        let bytes = collect_bytes(buffer);
                        move_in_insert(&bytes, sels, |b, s| s.head = next_char_or_end(b, s.head));
                    }
                    'w' => delete_word_backward_multi(buffer, sels),
                    'k' => kill_to_line_end_multi(buffer, sels, registers),
                    'u' => kill_to_line_start_multi(buffer, sels, registers),
                    _ => {}
                }
                return;
            }
            if c == 'j' && k.mods.is_empty() {
                *pending_j = true;
                return;
            }
            let mut buf = [0u8; 4];
            let s = c.encode_utf8(&mut buf);
            insert_text_multi(buffer, sels, s.as_bytes());
        }
        _ => {}
    }
}

/// Insert `text` at every selection's head, shifting later selections by
/// the cumulative byte delta as we go.
fn insert_text_multi(buffer: &mut Buffer, sels: &mut Selections, text: &[u8]) {
    if text.is_empty() {
        return;
    }
    let indices = sels.indices_by_position();
    let mut shift: i64 = 0;
    let n = text.len() as i64;
    for &idx in &indices {
        let sel = &mut sels.list[idx];
        sel.anchor = (sel.anchor as i64 + shift).max(0) as usize;
        sel.head = (sel.head as i64 + shift).max(0) as usize;
        buffer.insert(sel.head, text);
        sel.head += text.len();
        shift += n;
    }
}

/// Cursor-moving helper for insert-mode keybindings. Computes the new head
/// for each selection via `update`, then collapses the selection so the
/// cursor sits at that position with anchor matching.
fn move_in_insert<F>(bytes: &[u8], sels: &mut Selections, mut update: F)
where
    F: FnMut(&[u8], &mut Selection),
{
    for sel in sels.iter_mut() {
        update(bytes, sel);
        sel.anchor = sel.head;
        sel.desired_col = display_col(bytes, line_start(bytes, sel.head), sel.head);
    }
}

/// `C-k` in insert mode: kill from each head to that line's end. If the
/// head is already at the line break, deletes the break itself (joining
/// with the next line), matching emacs's kill-line behavior. The primary
/// selection's killed content is stashed in the default register.
fn kill_to_line_end_multi(buffer: &mut Buffer, sels: &mut Selections, registers: &mut Registers) {
    let initial = collect_bytes(buffer);
    let primary = *sels.primary();
    let p_end = {
        let le = line_end(&initial, primary.head);
        if le == primary.head && primary.head < initial.len() && initial[primary.head] == b'\n' {
            primary.head + 1
        } else {
            le
        }
    };
    if p_end > primary.head {
        registers.default = initial[primary.head..p_end].to_vec();
    }

    let indices = sels.indices_by_position();
    let mut shift: i64 = 0;
    for &idx in &indices {
        let now = collect_bytes(buffer);
        let sel = &mut sels.list[idx];
        sel.anchor = (sel.anchor as i64 + shift).max(0) as usize;
        sel.head = (sel.head as i64 + shift).max(0) as usize;
        let le = line_end(&now, sel.head);
        let target = if le == sel.head && sel.head < now.len() && now[sel.head] == b'\n' {
            sel.head + 1
        } else {
            le
        };
        let len = target.saturating_sub(sel.head);
        if len > 0 {
            buffer.delete(sel.head, len);
            shift -= len as i64;
        }
        sel.anchor = sel.head;
    }
}

/// `C-u` in insert mode: kill from each line's start to the head. The
/// primary selection's killed content is stashed in the default register.
fn kill_to_line_start_multi(buffer: &mut Buffer, sels: &mut Selections, registers: &mut Registers) {
    let initial = collect_bytes(buffer);
    let primary = *sels.primary();
    let p_ls = line_start(&initial, primary.head);
    if primary.head > p_ls {
        registers.default = initial[p_ls..primary.head].to_vec();
    }

    let indices = sels.indices_by_position();
    let mut shift: i64 = 0;
    for &idx in &indices {
        let now = collect_bytes(buffer);
        let sel = &mut sels.list[idx];
        sel.anchor = (sel.anchor as i64 + shift).max(0) as usize;
        sel.head = (sel.head as i64 + shift).max(0) as usize;
        let ls = line_start(&now, sel.head);
        let len = sel.head.saturating_sub(ls);
        if len > 0 {
            buffer.delete(ls, len);
            sel.head = ls;
            shift -= len as i64;
        }
        sel.anchor = sel.head;
    }
}

/// Delete from the previous word start to each selection's head. The
/// "previous word start" follows the same rule as the `b` motion: skip any
/// whitespace immediately before the head, then walk back through one
/// run of word/non-word characters.
fn delete_word_backward_multi(buffer: &mut Buffer, sels: &mut Selections) {
    let indices = sels.indices_by_position();
    let mut shift: i64 = 0;
    for &idx in &indices {
        let now = collect_bytes(buffer);
        let sel = &mut sels.list[idx];
        sel.anchor = (sel.anchor as i64 + shift).max(0) as usize;
        sel.head = (sel.head as i64 + shift).max(0) as usize;
        if sel.head == 0 {
            continue;
        }
        let new_head = motion_word_backward(&now, sel.head);
        if new_head >= sel.head {
            continue;
        }
        let len = sel.head - new_head;
        buffer.delete(new_head, len);
        sel.head = new_head;
        if sel.anchor > sel.head {
            sel.anchor = sel.anchor.saturating_sub(len);
        }
        shift -= len as i64;
    }
}

/// Backspace before each selection's head, shifting subsequent selections.
fn backspace_multi(buffer: &mut Buffer, sels: &mut Selections) {
    let indices = sels.indices_by_position();
    let mut shift: i64 = 0;
    for &idx in &indices {
        let now = collect_bytes(buffer);
        let sel = &mut sels.list[idx];
        sel.anchor = (sel.anchor as i64 + shift).max(0) as usize;
        sel.head = (sel.head as i64 + shift).max(0) as usize;
        if sel.head == 0 {
            continue;
        }
        let new_head = prev_char(&now, sel.head);
        let len = sel.head - new_head;
        buffer.delete(new_head, len);
        sel.head = new_head;
        if sel.anchor > sel.head {
            sel.anchor = sel.anchor.saturating_sub(len);
        }
        shift -= len as i64;
    }
}

fn exit_insert_mode_multi(buffer: &Buffer, sels: &mut Selections, mode: &mut Mode) {
    *mode = Mode::Normal;
    let bytes = collect_bytes(buffer);
    for sel in sels.iter_mut() {
        if sel.head > sel.anchor {
            sel.head = prev_char(&bytes, sel.head);
        }
        sel.head = snap_to_char_or_last(&bytes, sel.head);
        sel.anchor = snap_to_char_or_last(&bytes, sel.anchor);
    }
}

pub fn handle_search(
    buffer: &Buffer,
    sels: &mut Selections,
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
            if let Some(start) = search.start.take() {
                apply_snapshot(sels.primary_mut(), start);
            }
            search.preview = None;
            search.kind = SearchKind::Find;
        }
        Key::Enter => {
            let pat = search_input.clone();
            *mode = Mode::Normal;
            search_input.clear();
            let kind = search.kind;
            let start = search.start.take();
            search.preview = None;
            search.kind = SearchKind::Find;
            if pat.is_empty() {
                return;
            }
            match compile_search_regex(&pat) {
                Ok(re) => match kind {
                    SearchKind::Find => {
                        let bytes = collect_bytes(buffer);
                        if re.find(&bytes).is_none() {
                            *ex_message = format!("no match: /{}", pat);
                        }
                        // Primary already on first match via incremental preview.
                        search.pattern = Some(re);
                    }
                    SearchKind::SelectWithin => {
                        let orig = match start {
                            Some(s) => s,
                            None => {
                                search.pattern = Some(re);
                                return;
                            }
                        };
                        let bytes = collect_bytes(buffer);
                        let range_min = orig.anchor.min(orig.head);
                        let range_max = orig.anchor.max(orig.head);
                        let range_end = next_char_or_end(&bytes, range_max);
                        let slice = &bytes[range_min..range_end];
                        let new_sels: Vec<Selection> = re
                            .find_iter(slice)
                            .map(|m| {
                                let s = range_min + m.start();
                                let e = range_min + m.end();
                                let head = if e > s {
                                    snap_to_char_or_last(&bytes, e - 1).max(s)
                                } else {
                                    s
                                };
                                Selection {
                                    anchor: s,
                                    head,
                                    desired_col: display_col(
                                        &bytes,
                                        line_start(&bytes, head),
                                        head,
                                    ),
                                }
                            })
                            .collect();
                        if new_sels.is_empty() {
                            *ex_message = format!("no matches: s/{}/", pat);
                        } else {
                            sels.replace(new_sels, 0);
                        }
                        search.pattern = Some(re);
                    }
                },
                Err(e) => {
                    *ex_message = format!("regex error: {}", e);
                }
            }
        }
        Key::Backspace => {
            if search_input.pop().is_none() {
                *mode = Mode::Normal;
                if let Some(start) = search.start.take() {
                    apply_snapshot(sels.primary_mut(), start);
                }
                search.preview = None;
                search.kind = SearchKind::Find;
                return;
            }
            update_search_preview(buffer, sels, search, search_input);
        }
        Key::Char(c) => {
            if k.mods.contains(Mods::CTRL) || k.mods.contains(Mods::ALT) {
                return;
            }
            search_input.push(c);
            update_search_preview(buffer, sels, search, search_input);
        }
        _ => {}
    }
}

/// Recompile the incremental regex from `input`. For `Find` searches, also
/// move the primary selection to the first match starting at or after
/// `search.start`'s head. For `SelectWithin`, just update the preview
/// highlight; selection list doesn't change until Enter.
fn update_search_preview(
    buffer: &Buffer,
    sels: &mut Selections,
    search: &mut SearchState,
    input: &str,
) {
    let start = match search.start {
        Some(s) => s,
        None => return,
    };
    if input.is_empty() {
        if matches!(search.kind, SearchKind::Find) {
            apply_snapshot(sels.primary_mut(), start);
        }
        search.preview = None;
        return;
    }
    let re = match compile_search_regex(input) {
        Ok(re) => re,
        Err(_) => {
            search.preview = None;
            return;
        }
    };
    let bytes = collect_bytes(buffer);
    if matches!(search.kind, SearchKind::Find) {
        apply_snapshot(sels.primary_mut(), start);
        let from = next_char_or_end(&bytes, start.head);
        let first = re.find_at(&bytes, from).or_else(|| re.find(&bytes));
        if let Some(m) = first {
            apply_match(sels.primary_mut(), &bytes, m.start(), m.end());
        }
    }
    search.preview = Some(re);
}

/// Collect all matches of `re` in `bytes` as (start, end) byte ranges. Used
/// by the renderer to draw live incremental-search highlights.
pub fn all_matches(bytes: &[u8], re: &regex::bytes::Regex) -> Vec<(usize, usize)> {
    re.find_iter(bytes).map(|m| (m.start(), m.end())).collect()
}

/// Compile a search pattern with the conventions an editor user expects:
/// multi-line mode on so `^` and `$` match per-line anchors (matching
/// Kakoune's default).
fn compile_search_regex(pat: &str) -> Result<regex::bytes::Regex, regex::Error> {
    regex::bytes::RegexBuilder::new(pat)
        .multi_line(true)
        .build()
}

/// `Ctrl+J`/`Ctrl+K` handler: figure out what to search for, then add the
/// next match as a new selection. Prefers the primary's extended-selection
/// content (as a literal pattern); falls back to the last committed search
/// pattern. The chosen pattern is promoted to `search.pattern` so n/N
/// continue with the same thing.
fn add_next_smart(
    sels: &mut Selections,
    bytes: &[u8],
    search: &mut SearchState,
    forward: bool,
) {
    let primary = *sels.primary();
    let extended = primary.anchor != primary.head;
    if extended {
        let min = primary.min();
        let last = next_char_or_end(bytes, primary.max());
        let sel_bytes = &bytes[min..last];
        let pat_str = match std::str::from_utf8(sel_bytes) {
            Ok(s) => regex::escape(s),
            Err(_) => return,
        };
        let re = match compile_search_regex(&pat_str) {
            Ok(r) => r,
            Err(_) => return,
        };
        add_next_match(sels, bytes, &re, forward);
        search.pattern = Some(re);
    } else if let Some(re) = search.pattern.as_ref() {
        add_next_match(sels, bytes, re, forward);
    }
}

/// Find the next match (in `forward` direction) relative to the primary
/// selection and append it to the selections list as the new primary.
/// Wraps at the buffer edge. No-op if the match is already in the list or
/// if no match exists at all.
fn add_next_match(
    sels: &mut Selections,
    bytes: &[u8],
    re: &regex::bytes::Regex,
    forward: bool,
) {
    if bytes.is_empty() {
        return;
    }
    let primary = *sels.primary();
    let m = if forward {
        let from = next_char_or_end(bytes, primary.max());
        re.find_at(bytes, from)
            .or_else(|| re.find(bytes))
            .map(|m| (m.start(), m.end()))
    } else {
        let candidates: Vec<_> = re
            .find_iter(bytes)
            .take_while(|m| m.end() <= primary.min())
            .map(|m| (m.start(), m.end()))
            .collect();
        candidates
            .last()
            .copied()
            .or_else(|| re.find_iter(bytes).last().map(|m| (m.start(), m.end())))
    };
    let (s, e) = match m {
        Some(p) => p,
        None => return,
    };
    // Dedupe: if this exact range is already a selection, just promote it
    // to primary instead of adding a duplicate.
    let existing = sels
        .iter()
        .position(|sel| sel.min() == s && next_char_or_end(bytes, sel.max()) == e);
    if let Some(idx) = existing {
        sels.set_primary(idx);
        return;
    }
    let head = if e > s {
        snap_to_char_or_last(bytes, e - 1).max(s)
    } else {
        s
    };
    let new_sel = Selection {
        anchor: s,
        head,
        desired_col: display_col(bytes, line_start(bytes, head), head),
    };
    sels.append_as_primary(new_sel);
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
    ex_action: &mut Option<ExAction>,
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
            execute_ex(buffer, path, &cmd, ex_message, ex_action)
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
    action: &mut Option<ExAction>,
) -> bool {
    // Commands with arguments: `:e <path>` opens a file.
    if let Some(rest) = cmd.strip_prefix("e ") {
        let p = std::path::PathBuf::from(rest.trim());
        if p.as_os_str().is_empty() {
            *message = "usage: :e <path>".to_string();
        } else {
            *action = Some(ExAction::OpenFile(p));
        }
        return false;
    }
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
        "bn" | "bnext" => {
            *action = Some(ExAction::NextBuffer);
            false
        }
        "bp" | "bprev" | "bprevious" => {
            *action = Some(ExAction::PrevBuffer);
            false
        }
        "ls" | "buffers" => {
            *action = Some(ExAction::ListBuffers);
            false
        }
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

/// Delete every selection's contents. Selections are processed in buffer
/// order; later selections shift down as earlier deletes consume bytes.
/// Sets the default register to the primary's deleted text (multi-cursor
/// yank semantics are out of scope here).
pub fn op_delete_multi(buffer: &mut Buffer, sels: &mut Selections, registers: &mut Registers) {
    let initial = collect_bytes(buffer);
    if initial.is_empty() {
        return;
    }
    let primary_idx = sels.primary;
    {
        let p = &sels.list[primary_idx];
        let p_last = next_char_or_end(&initial, p.max());
        if p_last > p.min() {
            registers.default = initial[p.min()..p_last].to_vec();
        }
    }
    buffer.mark_commit_point(snapshot_of(sels.primary()));

    let indices = sels.indices_by_position();
    let mut shift: i64 = 0;
    for &idx in &indices {
        let now = collect_bytes(buffer);
        let sel = &mut sels.list[idx];
        sel.anchor = (sel.anchor as i64 + shift).max(0) as usize;
        sel.head = (sel.head as i64 + shift).max(0) as usize;
        let min = sel.min();
        let last = next_char_or_end(&now, sel.max());
        let len = last.saturating_sub(min);
        if len > 0 {
            buffer.delete(min, len);
            shift -= len as i64;
        }
        sel.anchor = min;
        sel.head = min;
    }
    let final_bytes = collect_bytes(buffer);
    for sel in sels.list.iter_mut() {
        sel.head = snap_to_char_or_last(&final_bytes, sel.head);
        sel.anchor = snap_to_char_or_last(&final_bytes, sel.anchor);
        sel.desired_col = display_col(&final_bytes, line_start(&final_bytes, sel.head), sel.head);
    }
}

/// Delete every selection's contents then enter insert mode (multi-cursor
/// change). Each cursor lands at the position where its deletion happened.
pub fn op_change_multi(
    buffer: &mut Buffer,
    sels: &mut Selections,
    mode: &mut Mode,
    registers: &mut Registers,
) {
    op_delete_multi(buffer, sels, registers);
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

fn line_is_blank(bytes: &[u8], line: usize) -> bool {
    let s = byte_at_line(bytes, line);
    let e = line_end(bytes, s);
    s == e
}

/// Move a selection up or down by `delta` lines, preserving `desired_col`.
/// Positive delta moves down, negative moves up. Clamps at buffer edges.
pub fn move_line_relative(bytes: &[u8], sel: &mut Selection, delta: i64) {
    if bytes.is_empty() {
        return;
    }
    let total = line_index(bytes, bytes.len());
    let current = line_index(bytes, sel.head) as i64;
    let target = (current + delta).max(0).min(total as i64) as usize;
    let line_start_byte = byte_at_line(bytes, target);
    let new_head = offset_at_col(bytes, line_start_byte, sel.desired_col);
    sel.head = new_head;
    sel.anchor = new_head;
}

/// Find the byte offset of the last non-blank line of the next paragraph
/// (or the current one, if the cursor isn't already at its end). Never
/// lands on a blank separator line. Returns the original offset if there's
/// no paragraph forward of here.
pub fn paragraph_end_forward(bytes: &[u8], from: usize) -> usize {
    if bytes.is_empty() {
        return from;
    }
    let total = line_index(bytes, bytes.len());
    let start_line = line_index(bytes, from);
    let mut line = start_line;
    if line_is_blank(bytes, line) {
        while line <= total && line_is_blank(bytes, line) {
            line += 1;
        }
        if line > total {
            return from;
        }
    }
    while line < total && !line_is_blank(bytes, line + 1) {
        line += 1;
    }
    if line == start_line {
        // Already at end of current paragraph; advance to end of next.
        if line >= total {
            return from;
        }
        line += 1;
        while line <= total && line_is_blank(bytes, line) {
            line += 1;
        }
        if line > total {
            return from;
        }
        while line < total && !line_is_blank(bytes, line + 1) {
            line += 1;
        }
    }
    byte_at_line(bytes, line)
}

/// Symmetric counterpart to `paragraph_end_forward`: jump to the first
/// non-blank line of the current paragraph, or the previous paragraph if
/// the cursor is already at the start.
pub fn paragraph_start_backward(bytes: &[u8], from: usize) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let start_line = line_index(bytes, from);
    let mut line = start_line;
    if line_is_blank(bytes, line) {
        while line > 0 && line_is_blank(bytes, line) {
            line -= 1;
        }
        if line_is_blank(bytes, line) {
            return from;
        }
    }
    while line > 0 && !line_is_blank(bytes, line - 1) {
        line -= 1;
    }
    if line == start_line {
        if line == 0 {
            return from;
        }
        line -= 1;
        while line > 0 && line_is_blank(bytes, line) {
            line -= 1;
        }
        if line_is_blank(bytes, line) {
            return from;
        }
        while line > 0 && !line_is_blank(bytes, line - 1) {
            line -= 1;
        }
    }
    byte_at_line(bytes, line)
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
    let traced = crate::trace::enabled();
    let start = if traced {
        Some(crate::trace::tic())
    } else {
        None
    };
    let mut v = Vec::with_capacity(buffer.len());
    for s in buffer.slices() {
        v.extend_from_slice(s);
    }
    if let Some(s) = start {
        crate::trace::record_collect(crate::trace::toc(s));
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

/// Search for `target` within the current line per `op`. The search
/// excludes `from` itself so repeating advances. `Till` variants land
/// the head one char away from the matched byte. Returns `None` if no
/// match on the current line.
pub fn find_char_on_line(
    bytes: &[u8],
    from: usize,
    target: char,
    op: FindOp,
) -> Option<usize> {
    if !target.is_ascii() {
        // Restrict to ASCII for now — multi-byte char matching needs a
        // proper codepoint walk; not worth it until someone asks.
        return None;
    }
    let needle = target as u8;
    let ls = line_start(bytes, from);
    let le = line_end(bytes, from);
    let (match_pos, till) = match op {
        FindOp::ForwardTo | FindOp::ForwardTill => {
            let start = from.saturating_add(1).min(le);
            let pos = bytes
                .get(start..le)
                .and_then(|s| s.iter().position(|&b| b == needle))
                .map(|p| start + p)?;
            (pos, matches!(op, FindOp::ForwardTill))
        }
        FindOp::BackwardTo | FindOp::BackwardTill => {
            let end = from.min(le);
            let pos = bytes
                .get(ls..end)
                .and_then(|s| s.iter().rposition(|&b| b == needle))
                .map(|p| ls + p)?;
            (pos, matches!(op, FindOp::BackwardTill))
        }
    };
    if !till {
        return Some(match_pos);
    }
    match op {
        FindOp::ForwardTill => Some(prev_char(bytes, match_pos)),
        FindOp::BackwardTill => Some(next_char(bytes, match_pos)),
        _ => unreachable!(),
    }
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

/// O(log L) line lookup for a byte offset, using a pre-built line-starts
/// index. `line_starts[k]` must be the byte offset of the start of line
/// `k`; the caller is responsible for keeping this in sync with edits.
pub fn line_index_cached(line_starts: &[usize], offset: usize) -> usize {
    match line_starts.binary_search(&offset) {
        Ok(idx) => idx,
        Err(idx) => idx.saturating_sub(1),
    }
}

/// O(1) "start byte of line `line`" lookup. Returns `bytes_len` if the
/// requested line is past the end of the buffer.
pub fn byte_at_line_cached(line_starts: &[usize], line: usize, bytes_len: usize) -> usize {
    line_starts.get(line).copied().unwrap_or(bytes_len)
}

/// Cached version of `move_line_relative` that uses a pre-built line
/// index. Same semantics; just no O(N) walks.
pub fn move_line_relative_cached(
    bytes: &[u8],
    line_starts: &[usize],
    sel: &mut Selection,
    delta: i64,
) {
    if bytes.is_empty() {
        return;
    }
    let total = line_starts.len().saturating_sub(1);
    let current = line_index_cached(line_starts, sel.head) as i64;
    let target = (current + delta).max(0).min(total as i64) as usize;
    let line_start_byte = byte_at_line_cached(line_starts, target, bytes.len());
    let new_head = offset_at_col(bytes, line_start_byte, sel.desired_col);
    sel.head = new_head;
    sel.anchor = new_head;
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
