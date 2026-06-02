use std::io::{self, Write};
use std::sync::atomic::{AtomicBool, Ordering};

#[cfg(unix)]
use std::os::fd::AsRawFd;

// ---------------------------------------------------------------------------
// RawMode
// ---------------------------------------------------------------------------

#[cfg(unix)]
pub struct RawMode {
    original: libc::termios,
    fd: i32,
}

#[cfg(unix)]
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

#[cfg(unix)]
impl Drop for RawMode {
    fn drop(&mut self) {
        unsafe {
            libc::tcsetattr(self.fd, libc::TCSAFLUSH, &self.original);
        }
    }
}

#[cfg(windows)]
pub struct RawMode {
    stdin_handle: win::Handle,
    stdout_handle: win::Handle,
    original_in: u32,
    original_out: u32,
}

#[cfg(windows)]
impl RawMode {
    pub fn enable() -> io::Result<Self> {
        unsafe {
            let stdin_handle = win::GetStdHandle(win::STD_INPUT_HANDLE);
            let stdout_handle = win::GetStdHandle(win::STD_OUTPUT_HANDLE);
            if stdin_handle == win::INVALID_HANDLE || stdout_handle == win::INVALID_HANDLE {
                return Err(io::Error::last_os_error());
            }
            let mut original_in: u32 = 0;
            if win::GetConsoleMode(stdin_handle, &mut original_in) == 0 {
                return Err(io::Error::last_os_error());
            }
            let mut original_out: u32 = 0;
            if win::GetConsoleMode(stdout_handle, &mut original_out) == 0 {
                return Err(io::Error::last_os_error());
            }
            // Disable line input, echo, processed input (Ctrl-C as signal,
            // etc.). Enable virtual terminal input so the console emits
            // ANSI escape sequences for arrow keys, modifiers, mouse, etc.
            let new_in = (original_in
                & !(win::ENABLE_LINE_INPUT
                    | win::ENABLE_ECHO_INPUT
                    | win::ENABLE_PROCESSED_INPUT))
                | win::ENABLE_VIRTUAL_TERMINAL_INPUT;
            if win::SetConsoleMode(stdin_handle, new_in) == 0 {
                return Err(io::Error::last_os_error());
            }
            // Enable virtual terminal output so our SGR / cursor escape
            // sequences are interpreted instead of printed literally.
            let new_out = original_out
                | win::ENABLE_PROCESSED_OUTPUT
                | win::ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if win::SetConsoleMode(stdout_handle, new_out) == 0 {
                return Err(io::Error::last_os_error());
            }
            Ok(Self {
                stdin_handle,
                stdout_handle,
                original_in,
                original_out,
            })
        }
    }
}

#[cfg(windows)]
impl Drop for RawMode {
    fn drop(&mut self) {
        unsafe {
            win::SetConsoleMode(self.stdin_handle, self.original_in);
            win::SetConsoleMode(self.stdout_handle, self.original_out);
        }
    }
}

// ---------------------------------------------------------------------------
// Screen
// ---------------------------------------------------------------------------

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
        // Enable Windows Terminal's win32-input-mode alongside the kitty push.
        // The two are mutually exclusive in practice: kitty terminals honor
        // `>17u` and ignore this unknown DEC private mode, while WT ignores
        // `>17u` and honors this — reporting every key as an `ESC [ … _` record
        // that carries full modifier state (so e.g. Ctrl-Shift is no longer
        // indistinguishable from a bare control byte). See `decode_win32`.
        out.write_all(b"\x1b[?9001h")?;
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
        // Open a synchronized update (DEC private mode 2026) so the terminal
        // buffers the whole frame and swaps it in atomically — it never
        // displays a half-drawn or momentarily-blanked intermediate state,
        // which is what causes flicker when redrawing the full screen every
        // frame. Closed in `end_frame`. Terminals that don't implement 2026
        // ignore the private-mode set/reset harmlessly.
        //
        // Then hide the cursor + home. We deliberately do NOT erase the whole
        // display (`\x1b[2J`) here: the renderer erases each row to
        // end-of-line (`clear_row`) just before overwriting it, avoiding both
        // the full repaint and (on some terminals) `2J` spilling cleared rows
        // into scrollback.
        self.back.extend_from_slice(b"\x1b[?2026h\x1b[?25l\x1b[H");
    }

    /// Position at the start of `row` and erase it to end-of-line. The
    /// renderer calls this for every viewport row in lieu of a per-frame
    /// full-screen clear; rows past the buffer's end are erased the same
    /// way so a short buffer never leaves stale content behind.
    pub fn clear_row(&mut self, row: u16) {
        let _ = write!(self.back, "\x1b[{};1H\x1b[K", row);
    }

    pub fn write_at(&mut self, row: u16, col: u16, text: &str) {
        let _ = write!(self.back, "\x1b[{};{}H{}", row, col, text);
    }

    /// Append raw bytes to the back buffer without any cursor positioning.
    /// Used for emitting SGR transitions that span cells.
    pub fn append_raw(&mut self, text: &str) {
        self.back.extend_from_slice(text.as_bytes());
    }

    /// Direct access to the back buffer for hot-path rendering that wants
    /// to emit bytes without going through `format!`/`String` allocations.
    pub fn back_mut(&mut self) -> &mut Vec<u8> {
        &mut self.back
    }

    /// Set the terminal cursor shape. `block` = block cursor (normal mode);
    /// `false` = bar cursor (insert mode). Steady, not blinking.
    pub fn set_cursor_shape(&mut self, block: bool) {
        let seq: &[u8] = if block { b"\x1b[2 q" } else { b"\x1b[6 q" };
        self.back.extend_from_slice(seq);
    }

    pub fn end_frame(&mut self, cursor_row: u16, cursor_col: u16) -> io::Result<()> {
        // Position + reveal the cursor, then close the synchronized update so
        // the terminal presents the completed frame in one atomic swap.
        // `\x1b[?2026l` must be the final bytes of the frame.
        let _ = write!(self.back, "\x1b[{};{}H\x1b[?25h", cursor_row, cursor_col);
        self.back.extend_from_slice(b"\x1b[?2026l");
        let mut out = io::stdout();
        out.write_all(&self.back)?;
        out.flush()
    }
}

impl Drop for Screen {
    fn drop(&mut self) {
        let mut out = io::stdout();
        let _ = out.write_all(b"\x1b[<u");
        let _ = out.write_all(b"\x1b[?9001l"); // disable win32-input-mode
        let _ = out.write_all(b"\x1b[0 q");
        let _ = out.write_all(b"\x1b[?25h\x1b[?1049l");
        let _ = out.flush();
    }
}

// ---------------------------------------------------------------------------
// term_size
// ---------------------------------------------------------------------------

#[cfg(unix)]
pub fn term_size() -> io::Result<(u16, u16)> {
    let mut ws: libc::winsize = unsafe { std::mem::zeroed() };
    let fd = io::stdout().as_raw_fd();
    if unsafe { libc::ioctl(fd, libc::TIOCGWINSZ, &mut ws) } != 0 {
        return Err(io::Error::last_os_error());
    }
    Ok((ws.ws_col, ws.ws_row))
}

#[cfg(windows)]
pub fn term_size() -> io::Result<(u16, u16)> {
    unsafe {
        let h = win::GetStdHandle(win::STD_OUTPUT_HANDLE);
        if h == win::INVALID_HANDLE {
            return Err(io::Error::last_os_error());
        }
        let mut info: win::ConsoleScreenBufferInfo = std::mem::zeroed();
        if win::GetConsoleScreenBufferInfo(h, &mut info) == 0 {
            return Err(io::Error::last_os_error());
        }
        let cols = (info.sr_window.right - info.sr_window.left + 1).max(0) as u16;
        let rows = (info.sr_window.bottom - info.sr_window.top + 1).max(0) as u16;
        Ok((cols, rows))
    }
}

// ---------------------------------------------------------------------------
// Resize detection
// ---------------------------------------------------------------------------

static RESIZED: AtomicBool = AtomicBool::new(false);

#[cfg(unix)]
extern "C" fn sigwinch_handler(_: libc::c_int) {
    RESIZED.store(true, Ordering::Relaxed);
}

#[cfg(unix)]
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

/// On Windows there's no SIGWINCH. We poll the console window size from
/// a background thread and set the resize flag when it changes. The main
/// loop's blocking stdin read still won't be interrupted, so the redraw
/// fires on the next keystroke after a resize — acceptable for now.
#[cfg(windows)]
pub fn install_sigwinch_handler() -> io::Result<()> {
    let initial = term_size().unwrap_or((0, 0));
    std::thread::spawn(move || {
        let mut last = initial;
        loop {
            std::thread::sleep(std::time::Duration::from_millis(200));
            if let Ok(cur) = term_size() {
                if cur != last {
                    last = cur;
                    RESIZED.store(true, Ordering::Relaxed);
                }
            }
        }
    });
    Ok(())
}

pub fn take_resize_flag() -> bool {
    RESIZED.swap(false, Ordering::Relaxed)
}

// ---------------------------------------------------------------------------
// Windows console API bindings
// ---------------------------------------------------------------------------

#[cfg(windows)]
mod win {
    pub type Handle = *mut core::ffi::c_void;

    pub const INVALID_HANDLE: Handle = -1isize as Handle;

    // GetStdHandle ids are negative DWORDs; passed as u32 here.
    pub const STD_INPUT_HANDLE: u32 = (-10i32) as u32;
    pub const STD_OUTPUT_HANDLE: u32 = (-11i32) as u32;

    pub const ENABLE_PROCESSED_INPUT: u32 = 0x0001;
    pub const ENABLE_LINE_INPUT: u32 = 0x0002;
    pub const ENABLE_ECHO_INPUT: u32 = 0x0004;
    pub const ENABLE_VIRTUAL_TERMINAL_INPUT: u32 = 0x0200;

    pub const ENABLE_PROCESSED_OUTPUT: u32 = 0x0001;
    pub const ENABLE_VIRTUAL_TERMINAL_PROCESSING: u32 = 0x0004;

    #[repr(C)]
    #[derive(Default, Clone, Copy)]
    pub struct Coord {
        pub x: i16,
        pub y: i16,
    }

    #[repr(C)]
    #[derive(Default, Clone, Copy)]
    pub struct SmallRect {
        pub left: i16,
        pub top: i16,
        pub right: i16,
        pub bottom: i16,
    }

    #[repr(C)]
    #[derive(Default, Clone, Copy)]
    pub struct ConsoleScreenBufferInfo {
        pub dw_size: Coord,
        pub dw_cursor_position: Coord,
        pub w_attributes: u16,
        pub sr_window: SmallRect,
        pub dw_maximum_window_size: Coord,
    }

    #[link(name = "kernel32")]
    unsafe extern "system" {
        pub fn GetStdHandle(n_std_handle: u32) -> Handle;
        pub fn GetConsoleMode(h_console: Handle, lp_mode: *mut u32) -> i32;
        pub fn SetConsoleMode(h_console: Handle, dw_mode: u32) -> i32;
        pub fn GetConsoleScreenBufferInfo(
            h_console: Handle,
            lp_info: *mut ConsoleScreenBufferInfo,
        ) -> i32;
    }
}
