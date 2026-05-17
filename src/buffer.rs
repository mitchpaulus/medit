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
        Self {
            original: content,
            append: Vec::new(),
            pieces,
            undo_stack: Vec::new(),
            redo_stack: Vec::new(),
            pending_commit: None,
            version: 0,
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
        let current_pieces = std::mem::replace(&mut self.pieces, entry.pieces);
        self.redo_stack.push(UndoEntry {
            pieces: current_pieces,
            cursor: current_cursor,
        });
        self.pending_commit = None;
        self.version = self.version.wrapping_add(1);
        Some(entry.cursor)
    }

    /// Re-apply the most recently undone commit. Returns the saved cursor.
    pub fn redo(&mut self, current_cursor: CursorSnapshot) -> Option<CursorSnapshot> {
        let entry = self.redo_stack.pop()?;
        let current_pieces = std::mem::replace(&mut self.pieces, entry.pieces);
        self.undo_stack.push(UndoEntry {
            pieces: current_pieces,
            cursor: current_cursor,
        });
        self.pending_commit = None;
        self.version = self.version.wrapping_add(1);
        Some(entry.cursor)
    }

    /// Monotonically incremented on every successful mutation. Cheap stable
    /// key for downstream caches (e.g. flat-bytes vec) to detect when their
    /// view of the buffer is stale.
    pub fn version(&self) -> u64 {
        self.version
    }

    pub fn insert(&mut self, offset: usize, text: &[u8]) {
        if text.is_empty() {
            return;
        }
        self.version = self.version.wrapping_add(1);
        self.maybe_commit();
        let total = self.len();
        let offset = offset.min(total);
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
        self.version = self.version.wrapping_add(1);
        self.maybe_commit();
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
}
