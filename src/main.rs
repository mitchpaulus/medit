mod term;

use std::io::{self, Read};
use std::path::PathBuf;

use medit::buffer::Buffer;
use medit::core::{
    Mode, Registers, Selection, byte_at_line, collect_bytes, ensure_visible, handle_ex,
    handle_insert, handle_normal, line_index, utf8_len,
};
use medit::input::{Event, Key, KeyEvent, Mods, Parser};
use term::{RawMode, Screen};

const SEL_BG: &str = "\x1b[48;5;24m";
const RESET_BG: &str = "\x1b[49m";

fn main() -> io::Result<()> {
    let path: Option<PathBuf> = std::env::args().nth(1).map(PathBuf::from);
    let mut buffer = match path.as_ref() {
        Some(p) if p.exists() => Buffer::open(p)?,
        _ => Buffer::empty(),
    };
    let mut sel = Selection::new();
    let mut mode = Mode::Normal;
    let mut registers = Registers::default();
    let mut top_line: usize = 0;
    let mut ex_input = String::new();
    let mut ex_message = String::new();
    let mut pending_j = false;
    let mut pending_g = false;
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
        &ex_input,
        &ex_message,
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
                &ex_input,
                &ex_message,
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
            if k.mods.contains(Mods::CTRL) && k.key == Key::Char('c') {
                return Ok(());
            }
            if mode == Mode::Normal {
                ex_message.clear();
            }
            match mode {
                Mode::Normal => {
                    if handle_normal(
                        &mut buffer,
                        &mut sel,
                        &mut mode,
                        &mut registers,
                        &mut pending_g,
                        k,
                    ) {
                        return Ok(());
                    }
                    if mode == Mode::Ex {
                        ex_input.clear();
                    }
                }
                Mode::Insert => {
                    handle_insert(&mut buffer, &mut sel, &mut mode, &mut pending_j, k);
                }
                Mode::Ex => {
                    if handle_ex(
                        &buffer,
                        &mut mode,
                        &mut ex_input,
                        &mut ex_message,
                        path.as_deref(),
                        k,
                    ) {
                        return Ok(());
                    }
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
            &ex_input,
            &ex_message,
            last_key.as_ref(),
            &last_bytes,
        )?;
    }
    Ok(())
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
fn render(
    screen: &mut Screen,
    buffer: &Buffer,
    sel: &Selection,
    mode: Mode,
    top_line: usize,
    path: Option<&std::path::Path>,
    ex_input: &str,
    ex_message: &str,
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
    let mut i = start_byte;

    loop {
        if i == head && row <= viewport_rows {
            cur_row = row;
            cur_col = col.max(1).min(cols.max(1));
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
        Mode::Ex => "X",
    };
    let cols_usize = cols as usize;

    let (status, final_cur_row, final_cur_col) = if mode == Mode::Ex {
        let prompt = format!(":{}", ex_input);
        let col_pos = (prompt.chars().count() as u16).saturating_add(1).max(1);
        (prompt, screen.rows, col_pos)
    } else if !ex_message.is_empty() {
        (format!(" {} ", ex_message), cur_row, cur_col)
    } else {
        let s = format!(
            " [{}] {} · ln {} col {} · sel {}b · last:{} raw:{} ",
            mode_str, path_str, abs_line, cur_col, sel_size, key_str, bytes_str
        );
        (s, cur_row, cur_col)
    };

    let mut padded: String = status.chars().take(cols_usize).collect();
    while padded.chars().count() < cols_usize {
        padded.push(' ');
    }
    let status_text = if mode == Mode::Ex {
        padded
    } else {
        format!("\x1b[7m{}\x1b[0m", padded)
    };
    screen.write_at(screen.rows, 1, &status_text);

    let block_cursor = mode == Mode::Normal;
    screen.set_cursor_shape(block_cursor);
    screen.end_frame(final_cur_row, final_cur_col)
}
