mod buffer;
mod input;
mod term;

use std::io::{self, Read};
use std::path::PathBuf;

use buffer::Buffer;
use input::{Event, Key, KeyEvent, Mods, Parser};
use term::{RawMode, Screen};

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

    fn move_to(&mut self, new_head: usize, extend: bool) {
        self.head = new_head;
        if !extend {
            self.anchor = new_head;
        }
    }
}

fn main() -> io::Result<()> {
    let path: Option<PathBuf> = std::env::args().nth(1).map(PathBuf::from);
    let buffer = match path.as_ref() {
        Some(p) => Buffer::open(p)?,
        None => Buffer::empty(),
    };
    let mut sel = Selection::new();
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
            if is_quit(&k) {
                return Ok(());
            }
            handle_navigation(&buffer, &mut sel, k);
        }
        let viewport_rows = screen.rows.saturating_sub(1) as usize;
        let bytes = collect_bytes(&buffer);
        ensure_visible(&bytes, sel.head, &mut top_line, viewport_rows);
        // Always re-render after a read so debug indicators update even when
        // the parser produced no event (e.g. incomplete sequence).
        render(
            &mut screen,
            &buffer,
            &sel,
            top_line,
            path.as_deref(),
            last_key.as_ref(),
            &last_bytes,
        )?;
    }
    Ok(())
}

fn is_quit(k: &KeyEvent) -> bool {
    (k.mods.is_empty() && k.key == Key::Char('q'))
        || (k.mods.contains(Mods::CTRL) && k.key == Key::Char('c'))
}

fn handle_navigation(buffer: &Buffer, sel: &mut Selection, k: KeyEvent) -> bool {
    let bytes = collect_bytes(buffer);
    let extend = k.mods.contains(Mods::SHIFT);
    match k.key {
        Key::Left => {
            let new_head = prev_char(&bytes, sel.head);
            sel.move_to(new_head, extend);
            sel.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
            true
        }
        Key::Right => {
            let new_head = next_char(&bytes, sel.head);
            sel.move_to(new_head, extend);
            sel.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
            true
        }
        Key::Up => {
            let ls = line_start(&bytes, sel.head);
            if ls == 0 {
                return false;
            }
            let prev_ls = line_start(&bytes, ls - 1);
            let new_head = offset_at_col(&bytes, prev_ls, sel.desired_col);
            sel.move_to(new_head, extend);
            true
        }
        Key::Down => {
            let le = line_end(&bytes, sel.head);
            if le >= bytes.len() {
                return false;
            }
            let new_head = offset_at_col(&bytes, le + 1, sel.desired_col);
            sel.move_to(new_head, extend);
            true
        }
        Key::Home => {
            let new_head = line_start(&bytes, sel.head);
            sel.move_to(new_head, extend);
            sel.desired_col = 1;
            true
        }
        Key::End => {
            let new_head = end_of_line(&bytes, sel.head);
            sel.move_to(new_head, extend);
            sel.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
            true
        }
        _ => false,
    }
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
        let in_span = i >= sel_min && i <= sel_max && i != head;
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
    let status = format!(
        " {} · ln {} col {} · sel {}b · last:{} raw:{} ",
        path_str, abs_line, cur_col, sel_size, key_str, bytes_str
    );
    let cols_usize = cols as usize;
    let mut padded: String = status.chars().take(cols_usize).collect();
    while padded.chars().count() < cols_usize {
        padded.push(' ');
    }
    let status_text = format!("\x1b[7m{}\x1b[0m", padded);
    screen.write_at(screen.rows, 1, &status_text);

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
