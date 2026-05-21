//! Global jump list. Stack-of-stacks shaped like undo: navigating away
//! from a place pushes the origin onto `back`; `Ctrl+O` pops it and
//! moves the editor there, recording the just-departed point on
//! `forward`. A fresh recorded jump clears `forward` (standard
//! redo-stack semantics).
//!
//! The list is intentionally not auto-populated by every motion — Vim's
//! "paragraph-and-friends" model spams it. Today the only producer is
//! `gd` (goto-definition); future jumpy ops should call `record` too.

use std::path::PathBuf;

#[derive(Debug, Clone)]
pub struct JumpEntry {
    pub path: PathBuf,
    pub offset: usize,
}

#[derive(Default)]
pub struct JumpList {
    back: Vec<JumpEntry>,
    forward: Vec<JumpEntry>,
}

impl JumpList {
    pub fn new() -> Self {
        Self::default()
    }

    /// Record a jump origin. Drops the forward stack — once you make a
    /// new jump, the redo lineage from before is no longer reachable.
    pub fn record(&mut self, entry: JumpEntry) {
        self.back.push(entry);
        self.forward.clear();
    }

    /// Pop the top of the back stack. If `current` is provided, push it
    /// onto the forward stack so a later `forward` call can return.
    /// `current` can be `None` for buffers with no path — the jump
    /// still works, but the inverse step won't bring you back here.
    pub fn back(&mut self, current: Option<JumpEntry>) -> Option<JumpEntry> {
        let prev = self.back.pop()?;
        if let Some(c) = current {
            self.forward.push(c);
        }
        Some(prev)
    }

    /// Mirror of `back`: pop the forward stack, push `current` onto back.
    pub fn forward(&mut self, current: Option<JumpEntry>) -> Option<JumpEntry> {
        let next = self.forward.pop()?;
        if let Some(c) = current {
            self.back.push(c);
        }
        Some(next)
    }

    pub fn back_len(&self) -> usize {
        self.back.len()
    }

    pub fn forward_len(&self) -> usize {
        self.forward.len()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn entry(p: &str, off: usize) -> JumpEntry {
        JumpEntry {
            path: PathBuf::from(p),
            offset: off,
        }
    }

    #[test]
    fn record_then_back_returns_entry() {
        let mut j = JumpList::new();
        j.record(entry("a.rs", 10));
        let here = entry("b.rs", 20);
        let got = j.back(Some(here.clone())).unwrap();
        assert_eq!(got.path, PathBuf::from("a.rs"));
        assert_eq!(got.offset, 10);
        // The departed location is now on forward.
        assert_eq!(j.forward_len(), 1);
        assert_eq!(j.back_len(), 0);
    }

    #[test]
    fn back_returns_in_lifo_order() {
        let mut j = JumpList::new();
        j.record(entry("a", 1));
        j.record(entry("b", 2));
        j.record(entry("c", 3));
        let here = entry("d", 99);
        assert_eq!(j.back(Some(here.clone())).unwrap().path, PathBuf::from("c"));
        assert_eq!(j.back(Some(here.clone())).unwrap().path, PathBuf::from("b"));
        assert_eq!(j.back(Some(here.clone())).unwrap().path, PathBuf::from("a"));
        assert!(j.back(Some(here)).is_none());
    }

    #[test]
    fn back_then_forward_round_trips() {
        let mut j = JumpList::new();
        j.record(entry("a", 1));
        let here = entry("b", 2);
        let prev = j.back(Some(here.clone())).unwrap();
        assert_eq!(prev.path, PathBuf::from("a"));
        let restored = j.forward(Some(prev)).unwrap();
        assert_eq!(restored.path, PathBuf::from("b"));
    }

    #[test]
    fn new_record_clears_forward() {
        let mut j = JumpList::new();
        j.record(entry("a", 1));
        j.back(Some(entry("b", 2)));
        assert_eq!(j.forward_len(), 1);
        j.record(entry("c", 3));
        assert_eq!(j.forward_len(), 0);
    }

    #[test]
    fn back_without_current_still_pops() {
        // No-path buffers can't push themselves onto forward but should
        // still be able to navigate backwards.
        let mut j = JumpList::new();
        j.record(entry("a", 1));
        let got = j.back(None).unwrap();
        assert_eq!(got.path, PathBuf::from("a"));
        assert_eq!(j.forward_len(), 0);
    }
}
