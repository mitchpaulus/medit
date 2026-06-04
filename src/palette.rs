//! Command palette — a discoverable, fuzzy-searchable list of editor
//! commands that overlays the view. The binary (`main.rs`) owns the
//! rendering and the key plumbing; this module owns the command registry,
//! the live overlay state, and the filtering.
//!
//! Adding a command is a single line in [`commands`]. A command's behavior
//! is a [`PaletteAction`]: either a reused [`ExAction`] (so existing Ex
//! dispatch handles it) or a palette-specific variant for things that live
//! only in the binary's view state.

use crate::core::ExAction;

/// What a palette command does when chosen.
#[derive(Clone)]
pub enum PaletteAction {
    /// Reuse the existing Ex dispatch (`dispatch_ex_action`) — e.g. write
    /// file, next/previous buffer. Keeps one source of truth for those.
    Ex(ExAction),
    /// Toggle the editor-wide "visualize control characters" view flag.
    /// Lives in the binary's local view state, so it can't be an
    /// `ExAction`.
    ToggleWhitespace,
}

/// One entry in the palette registry: a human-readable title and the
/// action it runs.
pub struct Command {
    pub title: &'static str,
    pub action: PaletteAction,
}

/// The command registry — the single source of truth for what the palette
/// offers. Add a command by adding a line here.
pub fn commands() -> Vec<Command> {
    vec![
        Command {
            title: "Write file",
            action: PaletteAction::Ex(ExAction::Save),
        },
        Command {
            title: "Toggle whitespace display",
            action: PaletteAction::ToggleWhitespace,
        },
        Command {
            title: "Buffer: next",
            action: PaletteAction::Ex(ExAction::NextBuffer),
        },
        Command {
            title: "Buffer: previous",
            action: PaletteAction::Ex(ExAction::PrevBuffer),
        },
    ]
}

/// Live palette overlay state: the typed query, the full command list, the
/// indices currently matching the query (best-first), and which of those is
/// selected.
pub struct CommandPalette {
    pub query: String,
    pub commands: Vec<Command>,
    /// Indices into `commands` matching `query`. An empty query matches all.
    pub filtered: Vec<usize>,
    /// Index into `filtered` of the highlighted row. Always either 0 (when
    /// `filtered` is empty) or a valid index.
    pub selected: usize,
}

impl CommandPalette {
    /// Open a fresh palette: empty query, every command visible, first row
    /// selected.
    pub fn new() -> Self {
        let commands = commands();
        let filtered = (0..commands.len()).collect();
        Self {
            query: String::new(),
            commands,
            filtered,
            selected: 0,
        }
    }

    /// Rebuild `filtered` from the current `query` and reset the selection
    /// to the top. An empty query matches everything; otherwise each command
    /// title is tested with a case-insensitive subsequence match.
    fn refilter(&mut self) {
        self.filtered.clear();
        for (i, cmd) in self.commands.iter().enumerate() {
            if self.query.is_empty() || fuzzy_match(&self.query, cmd.title) {
                self.filtered.push(i);
            }
        }
        self.selected = 0;
    }

    pub fn insert_char(&mut self, c: char) {
        self.query.push(c);
        self.refilter();
    }

    pub fn backspace(&mut self) {
        self.query.pop();
        self.refilter();
    }

    /// Move the highlight up one row, saturating at the top.
    pub fn move_up(&mut self) {
        self.selected = self.selected.saturating_sub(1);
    }

    /// Move the highlight down one row, clamped to the last match.
    pub fn move_down(&mut self) {
        if self.filtered.len() > 1 {
            self.selected = (self.selected + 1).min(self.filtered.len() - 1);
        }
    }

    /// The action of the currently highlighted command, or `None` when the
    /// filtered list is empty.
    pub fn selected_action(&self) -> Option<&PaletteAction> {
        let cmd_idx = *self.filtered.get(self.selected)?;
        self.commands.get(cmd_idx).map(|c| &c.action)
    }
}

impl Default for CommandPalette {
    fn default() -> Self {
        Self::new()
    }
}

/// Case-insensitive subsequence match: every char of `needle` appears in
/// `haystack` in order (not necessarily contiguously). Empty needle always
/// matches. This is the classic fuzzy-finder feel — typing `bn` matches
/// "Buffer: next".
fn fuzzy_match(needle: &str, haystack: &str) -> bool {
    let mut hay = haystack.chars().flat_map(char::to_lowercase);
    'outer: for nc in needle.chars().flat_map(char::to_lowercase) {
        for hc in hay.by_ref() {
            if hc == nc {
                continue 'outer;
            }
        }
        return false;
    }
    true
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fuzzy_subsequence() {
        assert!(fuzzy_match("", "anything"));
        assert!(fuzzy_match("bn", "Buffer: next"));
        assert!(fuzzy_match("write", "Write file"));
        assert!(fuzzy_match("WF", "Write file"));
        assert!(!fuzzy_match("zzz", "Write file"));
        assert!(!fuzzy_match("nb", "Buffer: next")); // order matters
    }

    #[test]
    fn filter_narrows_and_resets_selection() {
        let mut p = CommandPalette::new();
        assert_eq!(p.filtered.len(), p.commands.len());
        p.move_down();
        p.insert_char('w');
        // Query change resets selection to the top.
        assert_eq!(p.selected, 0);
        // "Write file" matches "w".
        assert!(!p.filtered.is_empty());
        assert!(p.selected_action().is_some());
    }

    #[test]
    fn navigation_clamps_when_empty() {
        let mut p = CommandPalette::new();
        for c in "zzzzz".chars() {
            p.insert_char(c);
        }
        assert!(p.filtered.is_empty());
        p.move_down();
        p.move_up();
        assert_eq!(p.selected, 0);
        assert!(p.selected_action().is_none());
    }
}
