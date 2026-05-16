mod buffer;
mod input;
mod term;

use std::io::{self, Read};
use std::path::PathBuf;

use buffer::Buffer;
use input::{Event, Key, KeyEvent, Mods, Parser};
use term::{RawMode, Screen};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Mode {
    Normal,
    Insert,
}

struct Selection {
    anchor: usize,
    head: usize,
    desired_col: usize,
}

impl Selection {
    fn new() -> Self {
        Self {
            anchor: 0,
            head: 0,
            desired_col: 1,
        }
    }

    fn min(&self) -> usize {
        self.anchor.min(self.head)
    }
    fn max(&self) -> usize {
        self.anchor.max(self.head)
    }
}

fn main() -> io::Result<()> {
    let path: Option<PathBuf> = std::env::args().nth(1).map(PathBuf::from);
    let mut buffer = match path.as_ref() {
        Some(p) => Buffer::open(p)?,
        None => Buffer::empty(),
    };
    let mut sel = Selection::new();
    let mut mode = Mode::Normal;
    let mut top_line: usize = 0;
    let mut last_key: Option<KeyEvent> = None;
    let mut last_bytes: Vec<u8> = Vec::new();

    let _raw = RawMode::enable()?;
    let mut screen = Screen::enter()?;
    term::install_sigwinch_handler()?;

    render(
        &mut screen,
        &buffer,
        &sel,
        mode,
        top_line,
        path.as_deref(),
        last_key.as_ref(),
        &last_bytes,
    )?;

    let stdin = io::stdin();
    let mut handle = stdin.lock();
    let mut io_buf = [0u8; 64];
    let mut parser = Parser::new();

    loop {
        if term::take_resize_flag() {
            screen.refresh_size()?;
            let viewport_rows = screen.rows.saturating_sub(1) as usize;
            let bytes = collect_bytes(&buffer);
            ensure_visible(&bytes, sel.head, &mut top_line, viewport_rows);
            render(
                &mut screen,
                &buffer,
                &sel,
                mode,
                top_line,
                path.as_deref(),
                last_key.as_ref(),
                &last_bytes,
            )?;
        }
        let n = match handle.read(&mut io_buf) {
            Ok(0) => break,
            Ok(n) => n,
            Err(e) if e.kind() == io::ErrorKind::Interrupted => continue,
            Err(e) => return Err(e),
        };
        last_bytes = io_buf[..n].to_vec();
        parser.feed(&io_buf[..n]);
        while let Some(event) = parser.next_event() {
            let Event::Key(k) = event;
            last_key = Some(k);
            // Emergency exit (works in any mode)
            if k.mods.contains(Mods::CTRL) && k.key == Key::Char('c') {
                return Ok(());
            }
            match mode {
                Mode::Normal => {
                    if handle_normal(&mut buffer, &mut sel, &mut mode, k) {
                        return Ok(());
                    }
                }
                Mode::Insert => {
                    handle_insert(&mut buffer, &mut sel, &mut mode, k);
                }
            }
        }
        let viewport_rows = screen.rows.saturating_sub(1) as usize;
        let bytes = collect_bytes(&buffer);
        ensure_visible(&bytes, sel.head, &mut top_line, viewport_rows);
        render(
            &mut screen,
            &buffer,
            &sel,
            mode,
            top_line,
            path.as_deref(),
            last_key.as_ref(),
            &last_bytes,
        )?;
    }
    Ok(())
}

/// Returns `true` if this key was a quit request.
fn handle_normal(
    buffer: &mut Buffer,
    sel: &mut Selection,
    mode: &mut Mode,
    k: KeyEvent,
) -> bool {
    let bytes = collect_bytes(buffer);

    // Quit (placeholder until `:q`)
    if k.mods.is_empty() && k.key == Key::Char('q') {
        return true;
    }

    // Mode entry, operators, and selection ops
    if k.mods.is_empty() {
        match k.key {
            Key::Char('i') => {
                let min = sel.min();
                sel.anchor = min;
                sel.head = min;
                *mode = Mode::Insert;
                return false;
            }
            Key::Char('a') => {
                let after = next_char_or_end(&bytes, sel.max());
                sel.anchor = after;
                sel.head = after;
                *mode = Mode::Insert;
                return false;
            }
            Key::Char(';') => {
                sel.anchor = sel.head;
                return false;
            }
            Key::Char('d') => {
                op_delete(buffer, sel);
                return false;
            }
            Key::Char('c') => {
                op_change(buffer, sel, mode);
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

    // Motions: lowercase moves, uppercase (or Shift+) extends.
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

enum Motion {
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

fn apply_motion(bytes: &[u8], sel: &mut Selection, motion: Motion, extend: bool) {
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

fn is_word_byte(b: u8) -> bool {
    b.is_ascii_alphanumeric() || b == b'_' || b >= 0x80
}

fn is_whitespace_byte(b: u8) -> bool {
    matches!(b, b' ' | b'\t' | b'\n' | b'\r')
}

fn motion_word_forward(bytes: &[u8], from: usize) -> usize {
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

fn motion_word_backward(bytes: &[u8], from: usize) -> usize {
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

fn motion_word_end(bytes: &[u8], from: usize) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let mut i = from;
    // If currently on whitespace or at start of a word, advance one then skip ws
    if let Some(&b) = bytes.get(i) {
        if is_whitespace_byte(b) {
            while i < bytes.len() && is_whitespace_byte(bytes[i]) {
                i += 1;
            }
        } else {
            // Advance one char to make `e` repeatable past current word
            let next = (i + utf8_len(b)).min(bytes.len());
            // If next char is whitespace or different class, we're already at end; just stay
            let advance = match bytes.get(next) {
                Some(&nb) => !is_whitespace_byte(nb) && is_word_byte(nb) == is_word_byte(b),
                None => false,
            };
            if advance {
                i = next;
            }
            while i < bytes.len() && is_whitespace_byte(bytes[i]) {
                i += 1;
            }
        }
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
        from
    }
}

fn op_delete(buffer: &mut Buffer, sel: &mut Selection) {
    let bytes = collect_bytes(buffer);
    if bytes.is_empty() {
        return;
    }
    let min = sel.min();
    let last_byte = next_char_or_end(&bytes, sel.max());
    let length = last_byte.saturating_sub(min);
    if length > 0 {
        buffer.delete(min, length);
    }
    let new_bytes = collect_bytes(buffer);
    let new_head = snap_to_char_or_last(&new_bytes, min);
    sel.head = new_head;
    sel.anchor = new_head;
    sel.desired_col = display_col(&new_bytes, line_start(&new_bytes, new_head), new_head);
}

fn op_change(buffer: &mut Buffer, sel: &mut Selection, mode: &mut Mode) {
    let bytes = collect_bytes(buffer);
    let min = sel.min();
    let last_byte = next_char_or_end(&bytes, sel.max());
    let length = last_byte.saturating_sub(min);
    if length > 0 {
        buffer.delete(min, length);
    }
    sel.head = min;
    sel.anchor = min;
    *mode = Mode::Insert;
}

fn op_open_below(buffer: &mut Buffer, sel: &mut Selection, mode: &mut Mode) {
    let bytes = collect_bytes(buffer);
    let le = line_end(&bytes, sel.head);
    buffer.insert(le, b"\n");
    sel.head = le + 1;
    sel.anchor = le + 1;
    *mode = Mode::Insert;
}

fn op_open_above(buffer: &mut Buffer, sel: &mut Selection, mode: &mut Mode) {
    let bytes = collect_bytes(buffer);
    let ls = line_start(&bytes, sel.head);
    buffer.insert(ls, b"\n");
    sel.head = ls;
    sel.anchor = ls;
    *mode = Mode::Insert;
}

fn handle_insert(
    buffer: &mut Buffer,
    sel: &mut Selection,
    mode: &mut Mode,
    k: KeyEvent,
) {
    match k.key {
        Key::Esc => {
            *mode = Mode::Normal;
            let bytes = collect_bytes(buffer);
            // If we inserted anything, pull head back to last inserted char so
            // selection covers what was just typed.
            if sel.head > sel.anchor {
                sel.head = prev_char(&bytes, sel.head);
            }
            // Snap to a valid char boundary; if head is past end, fall back to
            // the last char.
            sel.head = snap_to_char_or_last(&bytes, sel.head);
            sel.anchor = snap_to_char_or_last(&bytes, sel.anchor);
            return;
        }
        Key::Enter => {
            buffer.insert(sel.head, b"\n");
            sel.head += 1;
            return;
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
            return;
        }
        Key::Tab => {
            buffer.insert(sel.head, b"\t");
            sel.head += 1;
            return;
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
            return;
        }
        Key::Char(c) => {
            if k.mods.contains(Mods::CTRL) || k.mods.contains(Mods::ALT) {
                // Reserved for emacs readline bindings later; ignore for now.
                return;
            }
            let mut buf = [0u8; 4];
            let s = c.encode_utf8(&mut buf);
            buffer.insert(sel.head, s.as_bytes());
            sel.head += s.len();
            return;
        }
        _ => {}
    }
}

/// Like `next_char` but allows landing on `bytes.len()` (one-past-end), which
/// is the natural caret position for "insert after" in insert mode.
fn next_char_or_end(bytes: &[u8], offset: usize) -> usize {
    let b = match bytes.get(offset) {
        Some(&b) => b,
        None => return bytes.len(),
    };
    (offset + utf8_len(b)).min(bytes.len())
}

/// Snap `offset` to a valid char boundary, never past the last char (so the
/// caller always lands ON a character in normal mode). For empty buffers,
/// returns 0.
fn snap_to_char_or_last(bytes: &[u8], offset: usize) -> usize {
    if bytes.is_empty() {
        return 0;
    }
    let clamped = offset.min(bytes.len());
    if clamped == bytes.len() {
        return prev_char(bytes, bytes.len());
    }
    // Walk back to a leading byte if we're inside a multibyte char.
    let mut p = clamped;
    while p > 0 {
        match bytes.get(p) {
            Some(&b) if b & 0xC0 == 0x80 => p -= 1,
            _ => break,
        }
    }
    p
}

const SEL_BG: &str = "\x1b[48;5;24m";
const RESET_BG: &str = "\x1b[49m";

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

fn render(
    screen: &mut Screen,
    buffer: &Buffer,
    sel: &Selection,
    mode: Mode,
    top_line: usize,
    path: Option<&std::path::Path>,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
) -> io::Result<()> {
    screen.begin_frame();
    let bytes = collect_bytes(buffer);
    let cols = screen.cols;
    let viewport_rows = screen.rows.saturating_sub(1);
    let sel_min = sel.min();
    let sel_max = sel.max();
    let head = sel.head;
    let start_byte = byte_at_line(&bytes, top_line);

    let mut row: u16 = 1;
    let mut col: u16 = 1;
    let mut cur_row: u16 = 1;
    let mut cur_col: u16 = 1;
    let mut head_visible = false;
    let mut i = start_byte;

    loop {
        if i == head && row <= viewport_rows {
            cur_row = row;
            cur_col = col.max(1).min(cols.max(1));
            head_visible = true;
        }
        if i >= bytes.len() || row > viewport_rows {
            break;
        }
        let b = match bytes.get(i) {
            Some(&b) => b,
            None => break,
        };
        let in_span = mode == Mode::Normal && i >= sel_min && i <= sel_max && i != head;
        match b {
            b'\n' => {
                row = row.saturating_add(1);
                col = 1;
                i += 1;
            }
            b'\r' => {
                i += 1;
            }
            b'\t' => {
                let advance = 4 - ((col as usize - 1) % 4);
                if in_span && col <= cols {
                    let spaces = " ".repeat(advance);
                    let s = format!("{}{}{}", SEL_BG, spaces, RESET_BG);
                    screen.write_at(row, col, &s);
                }
                col = col.saturating_add(advance as u16);
                i += 1;
            }
            c if c < 0x20 => {
                let letter = (c + 0x40) as char;
                let body = format!("^{}", letter);
                if col <= cols {
                    if in_span {
                        screen.write_at(row, col, &format!("{}{}{}", SEL_BG, body, RESET_BG));
                    } else {
                        screen.write_at(row, col, &body);
                    }
                }
                col = col.saturating_add(2);
                i += 1;
            }
            _ => {
                let n = utf8_len(b);
                let end = (i + n).min(bytes.len());
                let s = std::str::from_utf8(&bytes[i..end]).unwrap_or("?");
                if col <= cols {
                    if in_span {
                        screen.write_at(row, col, &format!("{}{}{}", SEL_BG, s, RESET_BG));
                    } else {
                        screen.write_at(row, col, s);
                    }
                }
                col = col.saturating_add(1);
                i = end;
            }
        }
    }

    let _ = head_visible;
    let path_str = path.and_then(|p| p.to_str()).unwrap_or("[no file]");
    let sel_size = sel_max.saturating_sub(sel_min) + if bytes.is_empty() { 0 } else { 1 };
    let key_str = last_key.map(format_key).unwrap_or_else(|| "-".to_string());
    let bytes_str = if last_bytes.is_empty() {
        "-".to_string()
    } else {
        format_bytes(last_bytes)
    };
    let abs_line = line_index(&bytes, sel.head) + 1;
    let mode_str = match mode {
        Mode::Normal => "N",
        Mode::Insert => "I",
    };
    let status = format!(
        " [{}] {} · ln {} col {} · sel {}b · last:{} raw:{} ",
        mode_str, path_str, abs_line, cur_col, sel_size, key_str, bytes_str
    );
    let cols_usize = cols as usize;
    let mut padded: String = status.chars().take(cols_usize).collect();
    while padded.chars().count() < cols_usize {
        padded.push(' ');
    }
    let status_text = format!("\x1b[7m{}\x1b[0m", padded);
    screen.write_at(screen.rows, 1, &status_text);

    screen.set_cursor_shape(mode == Mode::Normal);
    screen.end_frame(cur_row, cur_col)
}

fn line_index(bytes: &[u8], offset: usize) -> usize {
    let end = offset.min(bytes.len());
    bytes[..end].iter().filter(|&&b| b == b'\n').count()
}

fn byte_at_line(bytes: &[u8], line: usize) -> usize {
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

fn ensure_visible(bytes: &[u8], head: usize, top_line: &mut usize, viewport_rows: usize) {
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

fn collect_bytes(buffer: &Buffer) -> Vec<u8> {
    let mut v = Vec::with_capacity(buffer.len());
    for s in buffer.slices() {
        v.extend_from_slice(s);
    }
    v
}

fn utf8_len(first: u8) -> usize {
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

fn prev_char(bytes: &[u8], offset: usize) -> usize {
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

/// Advance to the next char start. Per Kakoune-style "selection ≥ 1 char",
/// will not move past the last character (won't land at `bytes.len()`).
fn next_char(bytes: &[u8], offset: usize) -> usize {
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

fn line_start(bytes: &[u8], offset: usize) -> usize {
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

fn line_end(bytes: &[u8], offset: usize) -> usize {
    let mut p = offset;
    while p < bytes.len() {
        if bytes.get(p) == Some(&b'\n') {
            return p;
        }
        p += 1;
    }
    bytes.len()
}

/// Offset of the last character on the line containing `offset`.
/// For an empty line, returns the line start.
fn end_of_line(bytes: &[u8], offset: usize) -> usize {
    let ls = line_start(bytes, offset);
    let le = line_end(bytes, offset);
    if le == ls {
        return ls;
    }
    prev_char(bytes, le)
}

fn display_col(bytes: &[u8], from: usize, offset: usize) -> usize {
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

fn offset_at_col(bytes: &[u8], from: usize, target_col: usize) -> usize {
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
