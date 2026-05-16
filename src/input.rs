use std::collections::VecDeque;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Mods(u8);

impl Mods {
    pub const NONE: Mods = Mods(0);
    pub const SHIFT: Mods = Mods(0b001);
    pub const ALT: Mods = Mods(0b010);
    pub const CTRL: Mods = Mods(0b100);

    fn from_csi_param(p: u32) -> Self {
        let bits = p.saturating_sub(1) as u8;
        Mods(bits & 0b111)
    }

    pub fn contains(self, other: Mods) -> bool {
        (self.0 & other.0) == other.0
    }
    pub fn is_empty(self) -> bool {
        self.0 == 0
    }
}

impl std::ops::BitOr for Mods {
    type Output = Mods;
    fn bitor(self, rhs: Mods) -> Mods {
        Mods(self.0 | rhs.0)
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Key {
    Char(char),
    Enter,
    Tab,
    Backspace,
    Esc,
    Up,
    Down,
    Left,
    Right,
    Home,
    End,
    PageUp,
    PageDown,
    Insert,
    Delete,
    F(u8),
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct KeyEvent {
    pub key: Key,
    pub mods: Mods,
}

impl KeyEvent {
    fn plain(key: Key) -> Self {
        Self {
            key,
            mods: Mods::NONE,
        }
    }
    fn with(key: Key, mods: Mods) -> Self {
        Self { key, mods }
    }
}

#[derive(Debug)]
pub enum Event {
    Key(KeyEvent),
}

pub struct Parser {
    buf: VecDeque<u8>,
}

impl Parser {
    pub fn new() -> Self {
        Self {
            buf: VecDeque::new(),
        }
    }

    pub fn feed(&mut self, bytes: &[u8]) {
        self.buf.extend(bytes.iter().copied());
    }

    /// Resolve any pending partial sequence when no more input is expected.
    /// A lone trailing ESC byte (not yet followed by `[` / `O` to form a
    /// CSI/SS3 sequence) is emitted as a plain `Key::Esc`. Used by tests and
    /// at shutdown. In the live loop the terminal's own timing resolves this.
    pub fn flush(&mut self) -> Option<Event> {
        if self.buf.front() == Some(&0x1B) && self.buf.len() == 1 {
            self.buf.pop_front();
            return Some(Event::Key(KeyEvent::plain(Key::Esc)));
        }
        None
    }

    /// Pull the next decoded event, or `None` if buffer is empty / contains
    /// only a partial sequence.
    pub fn next_event(&mut self) -> Option<Event> {
        let first = *self.buf.front()?;
        match first {
            0x1B => {
                if self.buf.len() < 2 {
                    return None;
                }
                self.parse_escape()
            }
            0x7F => {
                self.buf.pop_front();
                Some(Event::Key(KeyEvent::plain(Key::Backspace)))
            }
            b'\r' | b'\n' => {
                self.buf.pop_front();
                Some(Event::Key(KeyEvent::plain(Key::Enter)))
            }
            b'\t' => {
                self.buf.pop_front();
                Some(Event::Key(KeyEvent::plain(Key::Tab)))
            }
            b if b < 0x20 => {
                // Ctrl+letter: 0x01='a' ... 0x1A='z'. 0x00 is Ctrl+Space.
                self.buf.pop_front();
                let letter = if b == 0 {
                    ' '
                } else {
                    (b + b'a' - 1) as char
                };
                Some(Event::Key(KeyEvent::with(Key::Char(letter), Mods::CTRL)))
            }
            _ => self.parse_char(),
        }
    }

    fn parse_char(&mut self) -> Option<Event> {
        let first = *self.buf.front()?;
        let needed = if first & 0x80 == 0 {
            1
        } else if first & 0xE0 == 0xC0 {
            2
        } else if first & 0xF0 == 0xE0 {
            3
        } else if first & 0xF8 == 0xF0 {
            4
        } else {
            1
        };
        if self.buf.len() < needed {
            return None;
        }
        let mut bytes = [0u8; 4];
        for i in 0..needed {
            bytes[i] = self.buf[i];
        }
        let c = match std::str::from_utf8(&bytes[..needed]) {
            Ok(s) => s.chars().next()?,
            Err(_) => char::REPLACEMENT_CHARACTER,
        };
        for _ in 0..needed {
            self.buf.pop_front();
        }
        Some(Event::Key(KeyEvent::plain(Key::Char(c))))
    }

    fn parse_escape(&mut self) -> Option<Event> {
        match self.buf[1] {
            b'[' => self.parse_csi(),
            b'O' => self.parse_ss3(),
            second if second.is_ascii_graphic() => {
                // Legacy Alt+key. Shouldn't arrive under kitty protocol, but handle.
                self.buf.pop_front(); // discard ESC
                let inner = self.next_event()?;
                let Event::Key(k) = inner;
                Some(Event::Key(KeyEvent::with(k.key, k.mods | Mods::ALT)))
            }
            _ => {
                self.buf.pop_front();
                Some(Event::Key(KeyEvent::plain(Key::Esc)))
            }
        }
    }

    fn parse_csi(&mut self) -> Option<Event> {
        // Find the final byte (0x40-0x7E). Bytes 2..end are parameters/intermediates.
        let mut end = 2;
        loop {
            if end >= self.buf.len() {
                return None;
            }
            let b = self.buf[end];
            if (0x40..=0x7E).contains(&b) {
                break;
            }
            end += 1;
        }
        let params: Vec<u8> = (2..end).map(|i| self.buf[i]).collect();
        let final_byte = self.buf[end];
        for _ in 0..=end {
            self.buf.pop_front();
        }
        Some(decode_csi(&params, final_byte))
    }

    fn parse_ss3(&mut self) -> Option<Event> {
        if self.buf.len() < 3 {
            return None;
        }
        let c = self.buf[2];
        for _ in 0..3 {
            self.buf.pop_front();
        }
        let key = match c {
            b'P' => Key::F(1),
            b'Q' => Key::F(2),
            b'R' => Key::F(3),
            b'S' => Key::F(4),
            b'H' => Key::Home,
            b'F' => Key::End,
            _ => Key::Esc,
        };
        Some(Event::Key(KeyEvent::plain(key)))
    }
}

fn decode_csi(params: &[u8], final_byte: u8) -> Event {
    let parts: Vec<u32> = params
        .split(|&b| b == b';')
        .map(|seg| {
            let mut n: u32 = 0;
            for &d in seg {
                if d.is_ascii_digit() {
                    n = n.saturating_mul(10).saturating_add((d - b'0') as u32);
                }
            }
            n
        })
        .collect();
    let p1 = parts.first().copied().unwrap_or(1);
    let p2 = parts.get(1).copied().unwrap_or(1);
    let mods = Mods::from_csi_param(p2);

    let key = match final_byte {
        b'A' => Key::Up,
        b'B' => Key::Down,
        b'C' => Key::Right,
        b'D' => Key::Left,
        b'H' => Key::Home,
        b'F' => Key::End,
        b'~' => match p1 {
            1 | 7 => Key::Home,
            4 | 8 => Key::End,
            2 => Key::Insert,
            3 => Key::Delete,
            5 => Key::PageUp,
            6 => Key::PageDown,
            11 => Key::F(1),
            12 => Key::F(2),
            13 => Key::F(3),
            14 => Key::F(4),
            15 => Key::F(5),
            17 => Key::F(6),
            18 => Key::F(7),
            19 => Key::F(8),
            20 => Key::F(9),
            21 => Key::F(10),
            23 => Key::F(11),
            24 => Key::F(12),
            _ => Key::Char('?'),
        },
        b'u' => {
            // Kitty CSI u: p1 = unicode codepoint of base key, p2 = modifiers (+1 encoded).
            match p1 {
                13 => Key::Enter,
                9 => Key::Tab,
                127 => Key::Backspace,
                27 => Key::Esc,
                cp => char::from_u32(cp).map(Key::Char).unwrap_or(Key::Char('?')),
            }
        }
        _ => Key::Char('?'),
    };
    Event::Key(KeyEvent::with(key, mods))
}
