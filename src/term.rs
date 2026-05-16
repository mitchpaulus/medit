use std::io::{self, Write};
use std::os::fd::AsRawFd;
use std::sync::atomic::{AtomicBool, Ordering};

pub struct RawMode {
    original: libc::termios,
    fd: i32,
}

impl RawMode {
    pub fn enable() -> io::Result<Self> {
        let fd = io::stdin().as_raw_fd();
        let mut original: libc::termios = unsafe { std::mem::zeroed() };
        if unsafe { libc::tcgetattr(fd, &mut original) } != 0 {
            return Err(io::Error::last_os_error());
        }
        let mut raw = original;
        unsafe { libc::cfmakeraw(&mut raw) };
        if unsafe { libc::tcsetattr(fd, libc::TCSAFLUSH, &raw) } != 0 {
            return Err(io::Error::last_os_error());
        }
        Ok(Self { original, fd })
    }
}

impl Drop for RawMode {
    fn drop(&mut self) {
        unsafe {
            libc::tcsetattr(self.fd, libc::TCSAFLUSH, &self.original);
        }
    }
}

pub struct Screen {
    pub cols: u16,
    pub rows: u16,
    back: Vec<u8>,
}

impl Screen {
    pub fn enter() -> io::Result<Self> {
        let mut out = io::stdout();
        out.write_all(b"\x1b[?1049h")?;
        out.write_all(b"\x1b[>17u")?;
        out.flush()?;
        let (cols, rows) = term_size()?;
        Ok(Self {
            cols,
            rows,
            back: Vec::with_capacity(8192),
        })
    }

    pub fn refresh_size(&mut self) -> io::Result<()> {
        let (cols, rows) = term_size()?;
        self.cols = cols;
        self.rows = rows;
        Ok(())
    }

    pub fn begin_frame(&mut self) {
        self.back.clear();
        // Hide cursor + clear screen + home
        self.back.extend_from_slice(b"\x1b[?25l\x1b[2J\x1b[H");
    }

    pub fn write_at(&mut self, row: u16, col: u16, text: &str) {
        let _ = write!(self.back, "\x1b[{};{}H{}", row, col, text);
    }

    /// Set the terminal cursor shape. `block` = block cursor (normal mode);
    /// `false` = bar cursor (insert mode). Steady, not blinking.
    pub fn set_cursor_shape(&mut self, block: bool) {
        let seq: &[u8] = if block { b"\x1b[2 q" } else { b"\x1b[6 q" };
        self.back.extend_from_slice(seq);
    }

    pub fn end_frame(&mut self, cursor_row: u16, cursor_col: u16) -> io::Result<()> {
        let _ = write!(self.back, "\x1b[{};{}H\x1b[?25h", cursor_row, cursor_col);
        let mut out = io::stdout();
        out.write_all(&self.back)?;
        out.flush()
    }
}

impl Drop for Screen {
    fn drop(&mut self) {
        let mut out = io::stdout();
        let _ = out.write_all(b"\x1b[<u");
        let _ = out.write_all(b"\x1b[0 q");
        let _ = out.write_all(b"\x1b[?25h\x1b[?1049l");
        let _ = out.flush();
    }
}

pub fn term_size() -> io::Result<(u16, u16)> {
    let mut ws: libc::winsize = unsafe { std::mem::zeroed() };
    let fd = io::stdout().as_raw_fd();
    if unsafe { libc::ioctl(fd, libc::TIOCGWINSZ, &mut ws) } != 0 {
        return Err(io::Error::last_os_error());
    }
    Ok((ws.ws_col, ws.ws_row))
}

static RESIZED: AtomicBool = AtomicBool::new(false);

extern "C" fn sigwinch_handler(_: libc::c_int) {
    RESIZED.store(true, Ordering::Relaxed);
}

pub fn install_sigwinch_handler() -> io::Result<()> {
    unsafe {
        let mut sa: libc::sigaction = std::mem::zeroed();
        sa.sa_sigaction = sigwinch_handler as *const () as usize;
        // No SA_RESTART: read() should return EINTR so the loop can react.
        sa.sa_flags = 0;
        libc::sigemptyset(&mut sa.sa_mask);
        if libc::sigaction(libc::SIGWINCH, &sa, std::ptr::null_mut()) != 0 {
            return Err(io::Error::last_os_error());
        }
    }
    Ok(())
}

pub fn take_resize_flag() -> bool {
    RESIZED.swap(false, Ordering::Relaxed)
}
