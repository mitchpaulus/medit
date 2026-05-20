use std::io;
use std::path::Path;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Source {
    Original,
    Append,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
struct Piece {
    source: Source,
    start: usize,
    len: usize,
}

/// Snapshot of editor cursor state, stored alongside each undo entry so that
/// undo/redo restore both the buffer and the user's cursor position.
#[derive(Debug, Clone, Copy)]
pub struct CursorSnapshot {
    pub anchor: usize,
    pub head: usize,
    pub desired_col: usize,
}

/// `(row, byte-column)` pair for tree-sitter incremental-parse edits. Column
/// is bytes within the line, not display cells.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct Point {
    pub row: usize,
    pub column: usize,
}

/// One mutation's worth of context for incremental tree-sitter parsing.
/// Field-for-field compatible with `tree_sitter::InputEdit`; converted in
/// the editor layer to keep this module free of the tree-sitter dep.
#[derive(Debug, Clone, Copy)]
pub struct Edit {
    pub start_byte: usize,
    pub old_end_byte: usize,
    pub new_end_byte: usize,
    pub start_position: Point,
    pub old_end_position: Point,
    pub new_end_position: Point,
}

#[derive(Clone)]
struct UndoEntry {
    pieces: Vec<Piece>,
    cursor: CursorSnapshot,
}

pub struct Buffer {
    original: Vec<u8>,
    append: Vec<u8>,
    pieces: Vec<Piece>,
    undo_stack: Vec<UndoEntry>,
    redo_stack: Vec<UndoEntry>,
    /// When `Some`, the next mutating call (`insert` or `delete`) will first
    /// snapshot the current `pieces` and the saved cursor onto `undo_stack`.
    /// Consumed on commit. Multiple mutations between commit points collapse
    /// into one undo step (coarse-grained, Vim-like).
    pending_commit: Option<CursorSnapshot>,
    /// Monotonically incremented on every successful mutation. Lets
    /// downstream caches (notably the flat-bytes cache in the editor
    /// front-end) invalidate without re-comparing piece tables.
    version: u64,
    /// `line_starts[k]` is the byte offset of the start of line `k`. Always
    /// has `[0]` even for empty buffers. Maintained incrementally on every
    /// mutation so position-lookup is O(log L) without a separate scan.
    line_starts: Vec<usize>,
    /// Mutations recorded since the last `drain_pending_edits` call. The
    /// syntax-highlight layer drains these to feed `tree.edit` for
    /// incremental tree-sitter reparsing.
    pending_edits: Vec<Edit>,
}

impl Buffer {
    pub fn empty() -> Self {
        Self {
            original: Vec::new(),
            append: Vec::new(),
            pieces: Vec::new(),
            undo_stack: Vec::new(),
            redo_stack: Vec::new(),
            pending_commit: None,
            version: 0,
            line_starts: vec![0],
            pending_edits: Vec::new(),
        }
    }

    pub fn from_bytes(content: Vec<u8>) -> Self {
        let pieces = if content.is_empty() {
            Vec::new()
        } else {
            vec![Piece {
                source: Source::Original,
                start: 0,
                len: content.len(),
            }]
        };
        let mut line_starts = vec![0];
        for (i, &b) in content.iter().enumerate() {
            if b == b'\n' {
                line_starts.push(i + 1);
            }
        }
        Self {
            original: content,
            append: Vec::new(),
            pieces,
            undo_stack: Vec::new(),
            redo_stack: Vec::new(),
            pending_commit: None,
            version: 0,
            line_starts,
            pending_edits: Vec::new(),
        }
    }

    pub fn open(path: &Path) -> io::Result<Self> {
        let content = std::fs::read(path)?;
        Ok(Self::from_bytes(content))
    }

    pub fn len(&self) -> usize {
        self.pieces.iter().map(|p| p.len).sum()
    }

    pub fn is_empty(&self) -> bool {
        self.pieces.is_empty()
    }

    fn piece_slice(&self, p: &Piece) -> &[u8] {
        let src = match p.source {
            Source::Original => &self.original,
            Source::Append => &self.append,
        };
        let end = p.start.saturating_add(p.len).min(src.len());
        let start = p.start.min(end);
        &src[start..end]
    }

    /// Iterator over piece byte slices in buffer order.
    pub fn slices(&self) -> impl Iterator<Item = &[u8]> {
        self.pieces.iter().map(|p| self.piece_slice(p))
    }

    /// Locate which piece contains the absolute offset.
    /// Returns `(piece_index, offset_within_piece)`. If `offset >= len()`
    /// returns `(pieces.len(), 0)`.
    fn locate(&self, offset: usize) -> (usize, usize) {
        let mut acc = 0usize;
        for (i, p) in self.pieces.iter().enumerate() {
            let next = acc.saturating_add(p.len);
            if offset < next {
                return (i, offset - acc);
            }
            acc = next;
        }
        (self.pieces.len(), 0)
    }

    /// Mark a point where the next mutation should snapshot for undo. The
    /// `cursor` is the state to restore on undo. Multiple mutations between
    /// mark points collapse into one undo step.
    pub fn mark_commit_point(&mut self, cursor: CursorSnapshot) {
        self.pending_commit = Some(cursor);
    }

    /// GURQ-orithm: if `redo_stack` is non-empty when a new commit lands,
    /// don't throw away the redo states. Fold them into the undo stack as
    /// "forward replay + backward replay" so the full history of where the
    /// user has been is preserved and reachable by walking undo. The trade-off
    /// is exponential memory growth in pathological cases (alternating
    /// edit/undo loops), which is fine for a personal editor.
    ///
    /// Without redos pending, this is the boring "snapshot once" commit.
    fn maybe_commit(&mut self) {
        let cursor = match self.pending_commit.take() {
            Some(c) => c,
            None => return,
        };
        let pre_snapshot = UndoEntry {
            pieces: self.pieces.clone(),
            cursor,
        };
        if self.redo_stack.is_empty() {
            self.undo_stack.push(pre_snapshot);
            return;
        }
        // Forward replay: walk redo top→bottom (= iter().rev()) and push
        // each entry onto undo so that undoing later visits them in the
        // original forward order.
        self.undo_stack.push(pre_snapshot.clone());
        for entry in self.redo_stack.iter().rev() {
            self.undo_stack.push(entry.clone());
        }
        // Backward replay: walk redo bottom→top, skipping the deepest entry
        // (which is the forward-most state we just landed on via the forward
        // replay). Then push the pre-edit state one more time so undoing
        // from the upcoming new state lands back at the pre-edit cursor.
        for entry in self.redo_stack.iter().skip(1) {
            self.undo_stack.push(entry.clone());
        }
        self.undo_stack.push(pre_snapshot);
        self.redo_stack.clear();
    }

    /// Pop the most recent commit. Returns the saved cursor snapshot (to
    /// restore) if anything was undone. The caller passes its current cursor
    /// so it can be saved on the redo stack.
    pub fn undo(&mut self, current_cursor: CursorSnapshot) -> Option<CursorSnapshot> {
        let entry = self.undo_stack.pop()?;
        let old_len = self.len();
        let old_end_pos = self.position_at(old_len);
        let current_pieces = std::mem::replace(&mut self.pieces, entry.pieces);
        self.redo_stack.push(UndoEntry {
            pieces: current_pieces,
            cursor: current_cursor,
        });
        self.pending_commit = None;
        self.version = self.version.wrapping_add(1);
        self.rebuild_line_starts();
        let new_len = self.len();
        let new_end_pos = self.position_at(new_len);
        self.pending_edits.push(Edit {
            start_byte: 0,
            old_end_byte: old_len,
            new_end_byte: new_len,
            start_position: Point::default(),
            old_end_position: old_end_pos,
            new_end_position: new_end_pos,
        });
        Some(entry.cursor)
    }

    /// Re-apply the most recently undone commit. Returns the saved cursor.
    pub fn redo(&mut self, current_cursor: CursorSnapshot) -> Option<CursorSnapshot> {
        let entry = self.redo_stack.pop()?;
        let old_len = self.len();
        let old_end_pos = self.position_at(old_len);
        let current_pieces = std::mem::replace(&mut self.pieces, entry.pieces);
        self.undo_stack.push(UndoEntry {
            pieces: current_pieces,
            cursor: current_cursor,
        });
        self.pending_commit = None;
        self.version = self.version.wrapping_add(1);
        self.rebuild_line_starts();
        let new_len = self.len();
        let new_end_pos = self.position_at(new_len);
        self.pending_edits.push(Edit {
            start_byte: 0,
            old_end_byte: old_len,
            new_end_byte: new_len,
            start_position: Point::default(),
            old_end_position: old_end_pos,
            new_end_position: new_end_pos,
        });
        Some(entry.cursor)
    }

    /// Monotonically incremented on every successful mutation. Cheap stable
    /// key for downstream caches (e.g. flat-bytes vec) to detect when their
    /// view of the buffer is stale.
    pub fn version(&self) -> u64 {
        self.version
    }

    /// `(row, byte-column)` of `offset` in the current buffer. Clamped to
    /// `len()`. O(log L) via binary search over `line_starts`.
    pub fn position_at(&self, offset: usize) -> Point {
        let offset = offset.min(self.len());
        let idx = match self.line_starts.binary_search(&offset) {
            Ok(i) => i,
            Err(i) => i.saturating_sub(1),
        };
        let line_start = self.line_starts.get(idx).copied().unwrap_or(0);
        Point {
            row: idx,
            column: offset - line_start,
        }
    }

    /// Take ownership of the queued edits and clear the log. The
    /// highlight layer drains these every reparse to feed `tree.edit`.
    pub fn drain_pending_edits(&mut self) -> Vec<Edit> {
        std::mem::take(&mut self.pending_edits)
    }

    /// Compute the position at `start_pos` plus `text`. Walks text once to
    /// count newlines and locate the column after the last newline.
    fn position_after_text(start_pos: Point, text: &[u8]) -> Point {
        let nl_count = text.iter().filter(|&&b| b == b'\n').count();
        if nl_count == 0 {
            Point {
                row: start_pos.row,
                column: start_pos.column + text.len(),
            }
        } else {
            let last_nl = text
                .iter()
                .rposition(|&b| b == b'\n')
                .expect("nl_count > 0");
            Point {
                row: start_pos.row + nl_count,
                column: text.len() - last_nl - 1,
            }
        }
    }

    /// Splice newlines from `text` into `line_starts` for an insertion at
    /// `offset`. Shifts existing entries beyond `offset` by `text.len()`.
    fn update_line_starts_insert(&mut self, offset: usize, text: &[u8]) {
        let split = self.line_starts.partition_point(|&s| s <= offset);
        for s in self.line_starts.iter_mut().skip(split) {
            *s += text.len();
        }
        let mut new_starts: Vec<usize> = Vec::new();
        for (i, &b) in text.iter().enumerate() {
            if b == b'\n' {
                new_starts.push(offset + i + 1);
            }
        }
        if !new_starts.is_empty() {
            self.line_starts.splice(split..split, new_starts);
        }
    }

    /// Remove line starts inside `(offset, end]` and shift entries past
    /// `end` left by `end - offset`. Matches the semantics of `delete`.
    fn update_line_starts_delete(&mut self, offset: usize, end: usize) {
        let length = end - offset;
        let remove_from = self.line_starts.partition_point(|&s| s <= offset);
        let remove_to = self.line_starts.partition_point(|&s| s <= end);
        if remove_from < remove_to {
            self.line_starts.drain(remove_from..remove_to);
        }
        for s in self.line_starts.iter_mut().skip(remove_from) {
            *s -= length;
        }
    }

    /// Walk pieces once and rebuild `line_starts` from scratch. Called
    /// from `undo`/`redo` where the piece-table is swapped wholesale.
    fn rebuild_line_starts(&mut self) {
        let pieces_copy = self.pieces.clone();
        let mut new_starts = vec![0usize];
        let mut acc = 0usize;
        for p in &pieces_copy {
            let slice = self.piece_slice(p);
            for (i, &b) in slice.iter().enumerate() {
                if b == b'\n' {
                    new_starts.push(acc + i + 1);
                }
            }
            acc += slice.len();
        }
        self.line_starts = new_starts;
    }

    pub fn insert(&mut self, offset: usize, text: &[u8]) {
        if text.is_empty() {
            return;
        }
        let total = self.len();
        let offset = offset.min(total);

        // Record the edit using pre-mutation positions.
        let start_pos = self.position_at(offset);
        let new_end_pos = Self::position_after_text(start_pos, text);
        self.pending_edits.push(Edit {
            start_byte: offset,
            old_end_byte: offset,
            new_end_byte: offset + text.len(),
            start_position: start_pos,
            old_end_position: start_pos,
            new_end_position: new_end_pos,
        });

        self.version = self.version.wrapping_add(1);
        self.maybe_commit();
        self.update_line_starts_insert(offset, text);

        let start = self.append.len();
        self.append.extend_from_slice(text);
        let new_piece = Piece {
            source: Source::Append,
            start,
            len: text.len(),
        };
        let (pi, po) = self.locate(offset);
        if pi == self.pieces.len() {
            self.pieces.push(new_piece);
            return;
        }
        if po == 0 {
            self.pieces.insert(pi, new_piece);
            return;
        }
        let old = match self.pieces.get(pi).copied() {
            Some(p) => p,
            None => return,
        };
        let left = Piece {
            source: old.source,
            start: old.start,
            len: po,
        };
        let right = Piece {
            source: old.source,
            start: old.start + po,
            len: old.len - po,
        };
        if let Some(slot) = self.pieces.get_mut(pi) {
            *slot = left;
        }
        self.pieces.insert(pi + 1, new_piece);
        self.pieces.insert(pi + 2, right);
    }

    pub fn delete(&mut self, offset: usize, length: usize) {
        if length == 0 {
            return;
        }
        let total = self.len();
        let end = offset.saturating_add(length).min(total);
        if offset >= end {
            return;
        }

        // Record the edit using pre-mutation positions (old_end_position
        // references the layout before any bytes are removed).
        let start_pos = self.position_at(offset);
        let old_end_pos = self.position_at(end);
        self.pending_edits.push(Edit {
            start_byte: offset,
            old_end_byte: end,
            new_end_byte: offset,
            start_position: start_pos,
            old_end_position: old_end_pos,
            new_end_position: start_pos,
        });

        self.version = self.version.wrapping_add(1);
        self.maybe_commit();
        self.update_line_starts_delete(offset, end);

        let mut remaining = end - offset;
        let (mut pi, po) = self.locate(offset);

        if po > 0 {
            let p = match self.pieces.get(pi).copied() {
                Some(p) => p,
                None => return,
            };
            let avail = p.len - po;
            if avail > remaining {
                let left = Piece {
                    source: p.source,
                    start: p.start,
                    len: po,
                };
                let right = Piece {
                    source: p.source,
                    start: p.start + po + remaining,
                    len: p.len - po - remaining,
                };
                if let Some(slot) = self.pieces.get_mut(pi) {
                    *slot = left;
                }
                self.pieces.insert(pi + 1, right);
                return;
            } else {
                if let Some(slot) = self.pieces.get_mut(pi) {
                    slot.len = po;
                }
                remaining -= avail;
                pi += 1;
            }
        }

        while remaining > 0 && pi < self.pieces.len() {
            let p = match self.pieces.get(pi).copied() {
                Some(p) => p,
                None => break,
            };
            if p.len <= remaining {
                remaining -= p.len;
                self.pieces.remove(pi);
            } else {
                if let Some(slot) = self.pieces.get_mut(pi) {
                    slot.start += remaining;
                    slot.len -= remaining;
                }
                remaining = 0;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn collect(b: &Buffer) -> Vec<u8> {
        let mut v = Vec::new();
        for s in b.slices() {
            v.extend_from_slice(s);
        }
        v
    }

    #[test]
    fn empty() {
        let b = Buffer::empty();
        assert_eq!(b.len(), 0);
        assert!(b.is_empty());
        assert_eq!(collect(&b), b"");
    }

    #[test]
    fn from_bytes_roundtrip() {
        let b = Buffer::from_bytes(b"hello".to_vec());
        assert_eq!(b.len(), 5);
        assert_eq!(collect(&b), b"hello");
    }

    #[test]
    fn insert_at_start() {
        let mut b = Buffer::from_bytes(b"world".to_vec());
        b.insert(0, b"hello ");
        assert_eq!(collect(&b), b"hello world");
    }

    #[test]
    fn insert_at_end() {
        let mut b = Buffer::from_bytes(b"hello".to_vec());
        b.insert(5, b" world");
        assert_eq!(collect(&b), b"hello world");
    }

    #[test]
    fn insert_in_middle_splits_piece() {
        let mut b = Buffer::from_bytes(b"helo".to_vec());
        b.insert(2, b"l");
        assert_eq!(collect(&b), b"hello");
    }

    #[test]
    fn insert_into_empty() {
        let mut b = Buffer::empty();
        b.insert(0, b"x");
        assert_eq!(collect(&b), b"x");
        assert_eq!(b.len(), 1);
    }

    #[test]
    fn delete_within_single_piece() {
        let mut b = Buffer::from_bytes(b"hello world".to_vec());
        b.delete(5, 1);
        assert_eq!(collect(&b), b"helloworld");
    }

    #[test]
    fn delete_across_pieces() {
        let mut b = Buffer::from_bytes(b"hello".to_vec());
        b.insert(5, b" world");
        b.insert(11, b"!");
        b.delete(3, 5);
        assert_eq!(collect(&b), b"helrld!");
    }

    #[test]
    fn delete_past_end_saturates() {
        let mut b = Buffer::from_bytes(b"hello".to_vec());
        b.delete(3, 1000);
        assert_eq!(collect(&b), b"hel");
    }

    #[test]
    fn delete_zero_is_noop() {
        let mut b = Buffer::from_bytes(b"hello".to_vec());
        b.delete(2, 0);
        assert_eq!(collect(&b), b"hello");
    }

    #[test]
    fn insert_then_delete_inserted() {
        let mut b = Buffer::from_bytes(b"ac".to_vec());
        b.insert(1, b"b");
        assert_eq!(collect(&b), b"abc");
        b.delete(1, 1);
        assert_eq!(collect(&b), b"ac");
    }

    /// Recompute line_starts from a freshly-collected byte view. Used by
    /// tests to confirm the incrementally-maintained `line_starts` matches
    /// what a from-scratch scan would produce.
    fn expected_line_starts(content: &[u8]) -> Vec<usize> {
        let mut v = vec![0usize];
        for (i, &b) in content.iter().enumerate() {
            if b == b'\n' {
                v.push(i + 1);
            }
        }
        v
    }

    #[test]
    fn line_starts_initialized_from_bytes() {
        let b = Buffer::from_bytes(b"abc\ndef\nghi".to_vec());
        assert_eq!(b.line_starts, vec![0, 4, 8]);
    }

    #[test]
    fn line_starts_after_insert_in_middle() {
        let mut b = Buffer::from_bytes(b"abc\ndef".to_vec());
        b.insert(2, b"X\nY");
        // Buffer becomes "abX\nYc\ndef"; line_starts should be [0, 4, 7].
        let bytes = collect(&b);
        assert_eq!(bytes, b"abX\nYc\ndef");
        assert_eq!(b.line_starts, expected_line_starts(&bytes));
    }

    #[test]
    fn line_starts_after_insert_at_line_boundary() {
        // Insert at the start of an existing line — the existing line_start
        // must NOT shift, but new newlines in `text` still create entries.
        let mut b = Buffer::from_bytes(b"abc\ndef".to_vec());
        b.insert(4, b"X\n");
        let bytes = collect(&b);
        assert_eq!(bytes, b"abc\nX\ndef");
        assert_eq!(b.line_starts, expected_line_starts(&bytes));
    }

    #[test]
    fn line_starts_after_delete_spanning_newline() {
        let mut b = Buffer::from_bytes(b"abcdef\nghi".to_vec());
        b.delete(2, 5); // removes "cdef\n"
        let bytes = collect(&b);
        assert_eq!(bytes, b"abghi");
        assert_eq!(b.line_starts, expected_line_starts(&bytes));
    }

    #[test]
    fn line_starts_after_delete_multiple_lines() {
        let mut b = Buffer::from_bytes(b"a\nb\nc\nd".to_vec());
        b.delete(2, 2); // removes "b\n"
        let bytes = collect(&b);
        assert_eq!(bytes, b"a\nc\nd");
        assert_eq!(b.line_starts, expected_line_starts(&bytes));
    }

    #[test]
    fn position_at_returns_row_and_byte_column() {
        let b = Buffer::from_bytes(b"abc\ndef\nghi".to_vec());
        assert_eq!(b.position_at(0), Point { row: 0, column: 0 });
        assert_eq!(b.position_at(2), Point { row: 0, column: 2 });
        assert_eq!(b.position_at(4), Point { row: 1, column: 0 });
        assert_eq!(b.position_at(6), Point { row: 1, column: 2 });
        assert_eq!(b.position_at(10), Point { row: 2, column: 2 });
        // Past-end clamps to the last position.
        assert_eq!(b.position_at(999), Point { row: 2, column: 3 });
    }

    #[test]
    fn insert_pushes_edit_with_correct_positions() {
        let mut b = Buffer::from_bytes(b"abc\ndef".to_vec());
        b.insert(5, b"X\nY"); // inserts after 'd'
        let edits = b.drain_pending_edits();
        assert_eq!(edits.len(), 1);
        let e = edits[0];
        assert_eq!(e.start_byte, 5);
        assert_eq!(e.old_end_byte, 5);
        assert_eq!(e.new_end_byte, 8);
        assert_eq!(e.start_position, Point { row: 1, column: 1 });
        assert_eq!(e.old_end_position, Point { row: 1, column: 1 });
        // After insert: "abc\ndX\nYef" — new_end lands on second line, col 1.
        assert_eq!(e.new_end_position, Point { row: 2, column: 1 });
    }

    #[test]
    fn delete_pushes_edit_with_pre_mutation_old_end() {
        let mut b = Buffer::from_bytes(b"abc\ndef\nghi".to_vec());
        b.delete(2, 5); // removes "c\ndef" — crosses one newline
        let edits = b.drain_pending_edits();
        assert_eq!(edits.len(), 1);
        let e = edits[0];
        assert_eq!(e.start_byte, 2);
        assert_eq!(e.old_end_byte, 7);
        assert_eq!(e.new_end_byte, 2);
        assert_eq!(e.start_position, Point { row: 0, column: 2 });
        // old_end_position is measured against the PRE-edit layout.
        assert_eq!(e.old_end_position, Point { row: 1, column: 3 });
        assert_eq!(e.new_end_position, Point { row: 0, column: 2 });
    }

    #[test]
    fn drain_pending_edits_empties_log() {
        let mut b = Buffer::from_bytes(b"abc".to_vec());
        b.insert(1, b"x");
        b.delete(2, 1);
        assert_eq!(b.drain_pending_edits().len(), 2);
        assert!(b.drain_pending_edits().is_empty());
    }

    #[test]
    fn undo_rebuilds_line_starts_and_logs_whole_buffer_edit() {
        let mut b = Buffer::from_bytes(b"abc".to_vec());
        let cur = CursorSnapshot {
            anchor: 0,
            head: 0,
            desired_col: 1,
        };
        b.mark_commit_point(cur);
        b.insert(3, b"\nXY");
        // Drain the insert's edit log before undoing so we can isolate
        // the edit produced by undo itself.
        let _ = b.drain_pending_edits();
        b.undo(CursorSnapshot {
            anchor: 6,
            head: 6,
            desired_col: 1,
        });
        let bytes = collect(&b);
        assert_eq!(bytes, b"abc");
        assert_eq!(b.line_starts, expected_line_starts(&bytes));
        let edits = b.drain_pending_edits();
        assert_eq!(edits.len(), 1);
        let e = edits[0];
        assert_eq!(e.start_byte, 0);
        assert_eq!(e.old_end_byte, 6);
        assert_eq!(e.new_end_byte, 3);
    }
}
