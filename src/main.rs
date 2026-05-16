mod input;
mod term;

use std::io::{self, Read};

use input::{Event, Key, KeyEvent, Mods, Parser};
use term::{RawMode, Screen};

fn main() -> io::Result<()> {
    let _raw = RawMode::enable()?;
    let mut screen = Screen::enter()?;
    term::install_sigwinch_handler()?;
    screen.draw_banner()?;

    let stdin = io::stdin();
    let mut handle = stdin.lock();
    let mut buf = [0u8; 64];
    let mut parser = Parser::new();

    loop {
        if term::take_resize_flag() {
            screen.refresh_size()?;
            screen.draw_banner()?;
        }
        let n = match handle.read(&mut buf) {
            Ok(0) => break,
            Ok(n) => n,
            Err(e) if e.kind() == io::ErrorKind::Interrupted => continue,
            Err(e) => return Err(e),
        };
        parser.feed(&buf[..n]);
        while let Some(event) = parser.next_event() {
            if is_quit(&event) {
                return Ok(());
            }
            screen.show_text(&format_event(&event))?;
        }
    }
    Ok(())
}

fn is_quit(event: &Event) -> bool {
    let Event::Key(k) = event;
    matches!(
        k,
        KeyEvent {
            key: Key::Char('q'),
            mods,
        } if mods.is_empty()
    ) || matches!(
        k,
        KeyEvent {
            key: Key::Char('c'),
            mods,
        } if mods.contains(Mods::CTRL)
    )
}

fn format_event(event: &Event) -> String {
    let Event::Key(k) = event;
    let mut s = String::from("key: ");
    if k.mods.contains(Mods::CTRL) {
        s.push_str("Ctrl-");
    }
    if k.mods.contains(Mods::ALT) {
        s.push_str("Alt-");
    }
    if k.mods.contains(Mods::SHIFT) {
        s.push_str("Shift-");
    }
    match k.key {
        Key::Char(c) => s.push_str(&format!("{:?}", c)),
        Key::Enter => s.push_str("Enter"),
        Key::Tab => s.push_str("Tab"),
        Key::Backspace => s.push_str("Backspace"),
        Key::Esc => s.push_str("Esc"),
        Key::Up => s.push_str("Up"),
        Key::Down => s.push_str("Down"),
        Key::Left => s.push_str("Left"),
        Key::Right => s.push_str("Right"),
        Key::Home => s.push_str("Home"),
        Key::End => s.push_str("End"),
        Key::PageUp => s.push_str("PageUp"),
        Key::PageDown => s.push_str("PageDown"),
        Key::Insert => s.push_str("Insert"),
        Key::Delete => s.push_str("Delete"),
        Key::F(n) => s.push_str(&format!("F{}", n)),
    }
    s
}
