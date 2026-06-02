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
    /// Already-decoded events waiting to be handed out one at a time. Used by
    /// win32-input-mode records whose repeat count expands to several presses.
    pending: VecDeque<Event>,
}

impl Parser {
    pub fn new() -> Self {
        Self {
            buf: VecDeque::new(),
            pending: VecDeque::new(),
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
            return Some(normalize_event(Event::Key(KeyEvent::plain(Key::Esc))));
        }
        None
    }

    /// Pull the next decoded event, or `None` if buffer is empty / contains
    /// only a partial sequence.
    pub fn next_event(&mut self) -> Option<Event> {
        self.next_event_raw().map(normalize_event)
    }

    fn next_event_raw(&mut self) -> Option<Event> {
        if let Some(ev) = self.pending.pop_front() {
            return Some(ev);
        }
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
        if final_byte == b'_' {
            // Windows Terminal win32-input-mode record. It may be a press we
            // ignore (key-up, lone modifier); when so, skip it and pull the
            // next event so one ignored record doesn't stall the read burst —
            // the bytes are already consumed, so recursing is safe.
            return match self.decode_win32(&params) {
                Some(ev) => Some(ev),
                None => self.next_event_raw(),
            };
        }
        Some(decode_csi(&params, final_byte))
    }

    /// Decode a win32-input-mode record (`ESC [ Vk;Sc;Uc;Kd;Cs;Rc _`, enabled
    /// via `CSI ?9001h`). Windows Terminal speaks this instead of the kitty
    /// protocol, so it's the only way to see disambiguated modifiers there.
    /// The output is normalized into the same `KeyEvent` vocabulary as the
    /// kitty/legacy paths, so the modal layer stays protocol-agnostic. Returns
    /// `None` for key-up and modifier-only records (nothing to act on); repeat
    /// counts above 1 enqueue the extra presses on `self.pending`.
    fn decode_win32(&mut self, params: &[u8]) -> Option<Event> {
        // dwControlKeyState bits, per the Win32 console API.
        const RIGHT_ALT: u32 = 0x0001;
        const LEFT_ALT: u32 = 0x0002;
        const RIGHT_CTRL: u32 = 0x0004;
        const LEFT_CTRL: u32 = 0x0008;
        const SHIFT_DOWN: u32 = 0x0010;

        let parts = parse_params(params);
        let vk = parts.first().copied().unwrap_or(0);
        let uc = parts.get(2).copied().unwrap_or(0);
        let key_down = parts.get(3).copied().unwrap_or(1) != 0;
        let cs = parts.get(4).copied().unwrap_or(0);
        let repeat = parts.get(5).copied().unwrap_or(1).max(1);

        if !key_down {
            return None;
        }

        let mut mods = Mods::NONE;
        if cs & (LEFT_CTRL | RIGHT_CTRL) != 0 {
            mods = mods | Mods::CTRL;
        }
        if cs & (LEFT_ALT | RIGHT_ALT) != 0 {
            mods = mods | Mods::ALT;
        }
        if cs & SHIFT_DOWN != 0 {
            mods = mods | Mods::SHIFT;
        }

        let key = match vk {
            0x08 => Key::Backspace,
            0x09 => Key::Tab,
            0x0D => Key::Enter,
            0x1B => Key::Esc,
            0x20 => Key::Char(' '),
            0x21 => Key::PageUp,
            0x22 => Key::PageDown,
            0x23 => Key::End,
            0x24 => Key::Home,
            0x25 => Key::Left,
            0x26 => Key::Up,
            0x27 => Key::Right,
            0x28 => Key::Down,
            0x2D => Key::Insert,
            0x2E => Key::Delete,
            0x70..=0x7B => Key::F((vk - 0x70 + 1) as u8),
            // Letters: take the base key from the virtual-key code and keep the
            // SHIFT bit so `normalize_event` folds it to uppercase exactly like
            // the kitty/legacy paths. This keeps `Ctrl-Shift-h` arriving as
            // `Char('H') + CTRL` regardless of which terminal produced it.
            0x41..=0x5A => Key::Char((vk as u8 - 0x41 + b'a') as char),
            // Lone modifier / lock keys carry no character: ignore them.
            0x10..=0x12 | 0x14 | 0x90 | 0x91 | 0xA0..=0xA5 => return None,
            _ => {
                // Digits, punctuation, symbols: the reported UnicodeChar already
                // reflects layout and shift, so trust it and drop SHIFT to avoid
                // double-counting against the produced glyph. Control-code chars
                // (e.g. Ctrl+symbol) aren't bound, so skip them.
                let c = char::from_u32(uc).filter(|c| !c.is_control())?;
                mods = Mods(mods.0 & !Mods::SHIFT.0);
                Key::Char(c)
            }
        };

        for _ in 1..repeat {
            self.pending.push_back(Event::Key(KeyEvent::with(key, mods)));
        }
        Some(Event::Key(KeyEvent::with(key, mods)))
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

/// Split a semicolon-separated CSI/win32 parameter string into decimal values.
/// Empty or non-numeric segments parse to 0. Shared by the standard CSI and
/// win32-input-mode decoders.
fn parse_params(params: &[u8]) -> Vec<u32> {
    params
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
        .collect()
}

fn decode_csi(params: &[u8], final_byte: u8) -> Event {
    let parts = parse_params(params);
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

/// Collapse `Shift + ASCII lowercase letter` to `uppercase letter` with no
/// SHIFT modifier. Both the legacy encoding (raw 'N' byte) and the kitty
/// disambiguated form (`CSI 110;2u`) thus produce the same `KeyEvent`, which
/// lets handlers match on a single canonical key.
fn normalize_event(event: Event) -> Event {
    let Event::Key(mut k) = event;
    if k.mods.contains(Mods::SHIFT) {
        if let Key::Char(c) = k.key {
            if c.is_ascii_lowercase() {
                k.key = Key::Char(c.to_ascii_uppercase());
                k.mods = Mods(k.mods.0 & !Mods::SHIFT.0);
            }
        }
    }
    Event::Key(k)
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Feed `bytes` and drain every decoded key event (as the main loop does).
    fn keys(bytes: &[u8]) -> Vec<KeyEvent> {
        let mut p = Parser::new();
        p.feed(bytes);
        let mut out = Vec::new();
        while let Some(Event::Key(k)) = p.next_event() {
            out.push(k);
        }
        out
    }

    // win32-input-mode record: `ESC [ Vk;Sc;Uc;Kd;Cs;Rc _`.

    #[test]
    fn win32_ctrl_shift_letter_normalizes_like_kitty() {
        // Ctrl-Shift-h: Vk=0x48('H'), Uc=8, keydown, Cs=LEFT_CTRL|SHIFT=0x18.
        let k = keys(b"\x1b[72;35;8;1;24;1_");
        assert_eq!(k, vec![KeyEvent::with(Key::Char('H'), Mods::CTRL)]);
    }

    #[test]
    fn win32_plain_and_shifted_letters() {
        assert_eq!(keys(b"\x1b[65;30;97;1;0;1_"), vec![KeyEvent::plain(Key::Char('a'))]);
        // Shift+a: Uc=65, Cs=SHIFT -> folds to uppercase with SHIFT stripped.
        assert_eq!(keys(b"\x1b[65;30;65;1;16;1_"), vec![KeyEvent::plain(Key::Char('A'))]);
    }

    #[test]
    fn win32_shifted_symbol_uses_unicode_and_drops_shift() {
        // Shift+1 = '!' on a US layout: trust Uc, no lingering SHIFT.
        assert_eq!(keys(b"\x1b[49;2;33;1;16;1_"), vec![KeyEvent::plain(Key::Char('!'))]);
    }

    #[test]
    fn win32_named_key() {
        assert_eq!(keys(b"\x1b[13;28;13;1;0;1_"), vec![KeyEvent::plain(Key::Enter)]);
    }

    #[test]
    fn win32_keyup_is_skipped_without_stalling_the_burst() {
        // 'a' key-up then 'b' key-down in one burst: only 'b' surfaces, and the
        // skipped up-record must not halt draining of the rest of the buffer.
        let k = keys(b"\x1b[65;30;97;0;0;1_\x1b[66;48;98;1;0;1_");
        assert_eq!(k, vec![KeyEvent::plain(Key::Char('b'))]);
    }

    #[test]
    fn win32_lone_modifier_is_ignored() {
        // Shift pressed by itself (Vk=0x10) produces no key event.
        assert_eq!(keys(b"\x1b[16;42;0;1;16;1_"), vec![]);
    }

    #[test]
    fn win32_repeat_count_expands_to_multiple_presses() {
        // Held 'l' with RepeatCount=3.
        let k = keys(b"\x1b[76;38;108;1;0;3_");
        assert_eq!(k, vec![KeyEvent::plain(Key::Char('l')); 3]);
    }

    #[test]
    fn kitty_path_still_works_alongside_win32() {
        // Legacy Ctrl-h and a kitty CSI-u 'a' should be unaffected.
        assert_eq!(keys(b"\x08"), vec![KeyEvent::with(Key::Char('h'), Mods::CTRL)]);
        assert_eq!(keys(b"\x1b[97u"), vec![KeyEvent::plain(Key::Char('a'))]);
    }
}
