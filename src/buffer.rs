use std::io;
use std::path::Path;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Source {
    Original,
    Append,
}

#[derive(Debug, Clone, Copy)]
struct Piece {
    source: Source,
    start: usize,
    len: usize,
}

pub struct Buffer {
    original: Vec<u8>,
    append: Vec<u8>,
    pieces: Vec<Piece>,
}

impl Buffer {
    pub fn empty() -> Self {
        Self {
            original: Vec::new(),
            append: Vec::new(),
            pieces: Vec::new(),
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

    pub fn insert(&mut self, offset: usize, text: &[u8]) {
        if text.is_empty() {
            return;
        }
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
