mod term;

use std::io::{self, Read};
use std::path::{Path, PathBuf};

use medit::buffer::Buffer;
use medit::core::{
    ExAction, LspAction, Mode, ObjectKind, Registers, SearchState, Selections, all_matches,
    byte_at_line, byte_at_line_cached, collect_bytes, display_col, handle_ex, handle_insert,
    handle_normal, handle_search, line_index, line_index_cached, line_start, next_char_or_end,
    snap_to_char_or_last, utf8_len,
};
use medit::highlight::{Highlighter, flatten_to_byte_scopes};
use medit::input::{Event, Key, KeyEvent, Mods, Parser};
use medit::lsp::{self, LspClient};
use medit::theme::{self, ScopeId};
use medit::trace;
use term::{RawMode, Screen};

const SEL_BG: &str = "\x1b[48;5;24m";
const MATCH_BG: &str = "\x1b[48;5;94m";
const LINENO_FG: &str = "\x1b[38;5;240m";

/// Per-buffer editor state. The main loop holds a `Vec<EditorBuffer>` and a
/// `current` index; switching buffers means moving the index.
struct EditorBuffer {
    buffer: Buffer,
    sels: Selections,
    top_line: usize,
    path: Option<PathBuf>,
    /// Syntax highlighting state. `lang_id` is set when the file extension
    /// matches a registered grammar; `tree` is the most recent parse;
    /// `flat_scopes` is a dense byte → scope lookup for the renderer.
    lang_id: Option<&'static str>,
    tree: Option<tree_sitter::Tree>,
    flat_scopes: Vec<ScopeId>,
    /// Cached flat byte view of `buffer`. Refreshed lazily by
    /// `refresh_bytes_cache` when `buffer.version()` doesn't match
    /// `cached_version`. Saves the per-frame `collect_bytes` walk for
    /// read-only consumers (the renderer and `ensure_visible`).
    cached_bytes: Vec<u8>,
    /// `line_starts[k]` is the byte offset of the start of line `k`. Always
    /// has at least one entry (0 for the first line). Built alongside
    /// `cached_bytes`. Lets `line_index_cached` use binary search and
    /// `byte_at_line_cached` index in O(1).
    line_starts: Vec<usize>,
    cached_version: Option<u64>,
}

impl EditorBuffer {
    fn new(buffer: Buffer, path: Option<PathBuf>) -> Self {
        let lang_id = path.as_deref().and_then(Highlighter::language_for_path);
        Self {
            buffer,
            sels: Selections::new(),
            top_line: 0,
            path,
            lang_id,
            tree: None,
            flat_scopes: Vec::new(),
            cached_bytes: Vec::new(),
            line_starts: vec![0],
            cached_version: None,
        }
    }

    fn display_name(&self) -> String {
        self.path
            .as_ref()
            .and_then(|p| p.file_name())
            .and_then(|s| s.to_str())
            .map(|s| s.to_string())
            .unwrap_or_else(|| "[no name]".to_string())
    }
}

/// Ensure `eb.cached_bytes` and `eb.line_starts` reflect the current
/// buffer state. Cheap when versions match; otherwise rebuilds both in a
/// single linear pass.
fn refresh_bytes_cache(eb: &mut EditorBuffer) {
    let v = eb.buffer.version();
    if eb.cached_version == Some(v) {
        return;
    }
    eb.cached_bytes.clear();
    eb.cached_bytes.reserve(eb.buffer.len());
    eb.line_starts.clear();
    eb.line_starts.push(0);
    for slice in eb.buffer.slices() {
        let base = eb.cached_bytes.len();
        eb.cached_bytes.extend_from_slice(slice);
        // Index newline positions as we copy; recording byte offsets of
        // the byte *after* each '\n' (i.e. the start of the next line).
        for (i, &b) in slice.iter().enumerate() {
            if b == b'\n' {
                eb.line_starts.push(base + i + 1);
            }
        }
    }
    eb.cached_version = Some(v);
}

/// Cached counterpart to `core::ensure_visible`. Same semantics, but uses
/// the cached line-starts index for O(log L) line lookup.
fn ensure_visible_indexed(
    line_starts: &[usize],
    head: usize,
    top_line: &mut usize,
    viewport_rows: usize,
) {
    if viewport_rows == 0 {
        return;
    }
    let head_line = line_index_cached(line_starts, head);
    if head_line < *top_line {
        *top_line = head_line;
    } else if head_line >= top_line.saturating_add(viewport_rows) {
        *top_line = head_line + 1 - viewport_rows;
    }
}

/// Re-parse `eb` from scratch and rebuild its `flat_scopes`. Called after
/// the buffer is loaded/replaced. Incremental updates (post-edit) are a
/// separate, later step.
fn reparse_and_highlight(eb: &mut EditorBuffer, hl: &Highlighter) {
    let lang_id = match eb.lang_id {
        Some(l) => l,
        None => return,
    };
    let mut parser = match hl.parser_for(lang_id) {
        Some(p) => p,
        None => return,
    };
    let bytes = collect_bytes(&eb.buffer);
    let tree = match parser.parse(&bytes, eb.tree.as_ref()) {
        Some(t) => t,
        None => return,
    };
    let spans = hl.highlight(lang_id, &tree, &bytes);
    eb.flat_scopes = flatten_to_byte_scopes(&spans, bytes.len());
    eb.tree = Some(tree);
}

/// Compute the SGR transition string needed to go from `(cur_fg, cur_bg)`
/// to `(new_fg, new_bg)`. Returns an empty string if no change is needed.
/// Emits only the channels that changed (and uses minimal-form resets for
/// single-channel transitions to default).
/// Write the minimal SGR transition from (cur_fg, cur_bg) to (new_fg, new_bg)
/// directly into `out`. No-op when state matches. Hot path — must not
/// allocate.
fn append_style_transition(
    out: &mut Vec<u8>,
    cur_fg: Option<&str>,
    cur_bg: Option<&str>,
    new_fg: Option<&str>,
    new_bg: Option<&str>,
) {
    if cur_fg == new_fg && cur_bg == new_bg {
        return;
    }
    let fg_to_default = cur_fg.is_some() && new_fg.is_none();
    let bg_to_default = cur_bg.is_some() && new_bg.is_none();
    if fg_to_default && bg_to_default {
        out.extend_from_slice(b"\x1b[0m");
        return;
    }
    if fg_to_default {
        out.extend_from_slice(b"\x1b[39m");
    }
    if bg_to_default {
        out.extend_from_slice(b"\x1b[49m");
    }
    if new_fg != cur_fg {
        if let Some(f) = new_fg {
            out.extend_from_slice(f.as_bytes());
        }
    }
    if new_bg != cur_bg {
        if let Some(b) = new_bg {
            out.extend_from_slice(b.as_bytes());
        }
    }
}

/// Write `\x1b[row;colH` directly into `out` without allocating an
/// intermediate `String`. Hot path.
fn append_cursor_pos(out: &mut Vec<u8>, row: u16, col: u16) {
    out.push(0x1b);
    out.push(b'[');
    append_u16(out, row);
    out.push(b';');
    append_u16(out, col);
    out.push(b'H');
}

fn append_u16(out: &mut Vec<u8>, mut n: u16) {
    if n == 0 {
        out.push(b'0');
        return;
    }
    let mut buf = [0u8; 5];
    let mut i = 0;
    while n > 0 {
        buf[i] = b'0' + (n % 10) as u8;
        n /= 10;
        i += 1;
    }
    while i > 0 {
        i -= 1;
        out.push(buf[i]);
    }
}

/// Emit a styled cell at `(row, col)` directly into the screen's back
/// buffer. Handles cursor-position coalescing (skips the position escape
/// when the terminal cursor is already at the target) and SGR
/// coalescing (only emits transitions when style state actually changed).
/// Updates `cursor_at`, `style_fg`, `style_bg` in place. No allocations.
#[allow(clippy::too_many_arguments)]
fn emit_styled_cell(
    screen: &mut Screen,
    cursor_at: &mut Option<(u16, u16)>,
    style_fg: &mut Option<&'static str>,
    style_bg: &mut Option<&'static str>,
    row: u16,
    col: u16,
    width: u16,
    new_fg: Option<&'static str>,
    new_bg: Option<&'static str>,
    body: &[u8],
) {
    let back = screen.back_mut();
    if *cursor_at != Some((row, col)) {
        append_cursor_pos(back, row, col);
    }
    append_style_transition(back, *style_fg, *style_bg, new_fg, new_bg);
    back.extend_from_slice(body);
    *cursor_at = Some((row, col + width));
    *style_fg = new_fg;
    *style_bg = new_bg;
}

fn draw_lineno(screen: &mut Screen, row: u16, lineno: usize, gutter: u16) {
    // Wrap the line number with explicit resets so style state is
    // predictable on either side (caller can assume default after).
    let digits = gutter.saturating_sub(1) as usize;
    let text = format!(
        "\x1b[0m{}{:>width$} \x1b[0m",
        LINENO_FG,
        lineno,
        width = digits
    );
    screen.write_at(row, 1, &text);
}

fn main() -> io::Result<()> {
    trace::init_from_env();
    let initial_path: Option<PathBuf> = std::env::args().nth(1).map(PathBuf::from);
    let initial_buffer = match initial_path.as_ref() {
        Some(p) if p.exists() => Buffer::open(p)?,
        _ => Buffer::empty(),
    };
    let highlighter = Highlighter::new();
    let mut buffers: Vec<EditorBuffer> = {
        let mut eb = EditorBuffer::new(initial_buffer, initial_path);
        reparse_and_highlight(&mut eb, &highlighter);
        vec![eb]
    };
    let mut current: usize = 0;

    let mut mode = Mode::Normal;
    let mut registers = Registers::default();
    let mut ex_input = String::new();
    let mut ex_message = String::new();
    let mut pending_j = false;
    let mut pending_g = false;
    let mut pending_z = false;
    let mut pending_find: Option<medit::core::FindOp> = None;
    let mut pending_object: Option<ObjectKind> = None;
    let mut pending_lsp_action: Option<LspAction> = None;
    let mut pending_ex_action: Option<ExAction> = None;
    let mut search_input = String::new();
    let mut search_state = SearchState::default();
    let mut last_key: Option<KeyEvent> = None;
    let mut last_bytes: Vec<u8> = Vec::new();

    // LSP. We spawn a server on demand the first time we open a Go file
    // (initial buffer or via `:e`). One client serves all buffers.
    let mut lsp_client: Option<LspClient> = None;
    if let Some(p) = buffers[0].path.clone() {
        maybe_start_lsp_and_open(&mut lsp_client, &p, &buffers[0].buffer);
    }

    let _raw = RawMode::enable()?;
    let mut screen = Screen::enter()?;
    term::install_sigwinch_handler()?;

    // Populate cache before the first frame; subsequent frames refresh in
    // the main loop.
    refresh_bytes_cache(&mut buffers[current]);
    render_all(
        &mut screen,
        &buffers,
        current,
        mode,
        &ex_input,
        &search_input,
        &search_state,
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
            {
                let cur = &mut buffers[current];
                refresh_bytes_cache(cur);
                let head = cur.sels.primary().head;
                ensure_visible_indexed(&cur.line_starts, head, &mut cur.top_line, viewport_rows);
            }
            render_all(
                &mut screen,
                &buffers,
                current,
                mode,
                &ex_input,
                &search_input,
                &search_state,
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
        // Frame timing starts after the blocking read so we don't measure
        // input-wait latency.
        let frame_start = trace::tic();
        let handle_start = trace::tic();
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
                    let viewport_rows = screen.rows.saturating_sub(1) as usize;
                    let cur = &mut buffers[current];
                    refresh_bytes_cache(cur);
                    // Split the borrow: handle_normal needs `&mut cur.buffer`
                    // *and* immutable views of `cur.cached_bytes` /
                    // `cur.line_starts`. The cache stays valid for the
                    // duration of the call — mutating ops inside re-collect
                    // their own fresh bytes.
                    let EditorBuffer {
                        buffer,
                        sels,
                        top_line,
                        cached_bytes,
                        line_starts,
                        ..
                    } = cur;
                    if handle_normal(
                        buffer,
                        sels,
                        &mut mode,
                        &mut registers,
                        &mut pending_g,
                        &mut pending_z,
                        &mut pending_object,
                        &mut pending_find,
                        &mut search_state,
                        &mut pending_lsp_action,
                        top_line,
                        viewport_rows,
                        cached_bytes,
                        line_starts,
                        k,
                    ) {
                        return Ok(());
                    }
                    if mode == Mode::Ex {
                        ex_input.clear();
                    }
                    if mode == Mode::Search {
                        search_input.clear();
                    }
                    if let Some(action) = pending_lsp_action.take() {
                        dispatch_lsp(
                            action,
                            lsp_client.as_mut(),
                            &mut buffers,
                            &mut current,
                            &highlighter,
                            &mut ex_message,
                        );
                    }
                }
                Mode::Insert => {
                    let cur = &mut buffers[current];
                    handle_insert(
                        &mut cur.buffer,
                        &mut cur.sels,
                        &mut mode,
                        &mut pending_j,
                        &mut registers,
                        k,
                    );
                }
                Mode::Ex => {
                    let path_owned = buffers[current].path.clone();
                    let quit = handle_ex(
                        &buffers[current].buffer,
                        &mut mode,
                        &mut ex_input,
                        &mut ex_message,
                        &mut pending_ex_action,
                        path_owned.as_deref(),
                        k,
                    );
                    if let Some(action) = pending_ex_action.take() {
                        dispatch_ex_action(
                            action,
                            &mut buffers,
                            &mut current,
                            lsp_client.as_mut(),
                            &highlighter,
                            &mut ex_message,
                        );
                        // If LSP needs to be started lazily for a newly-
                        // opened file:
                        if lsp_client.is_none() {
                            let p_opt = buffers[current].path.clone();
                            if let Some(p) = p_opt {
                                maybe_start_lsp_and_open(
                                    &mut lsp_client,
                                    &p,
                                    &buffers[current].buffer,
                                );
                            }
                        }
                    }
                    if quit {
                        return Ok(());
                    }
                }
                Mode::Search => {
                    let cur = &mut buffers[current];
                    handle_search(
                        &cur.buffer,
                        &mut cur.sels,
                        &mut mode,
                        &mut search_input,
                        &mut search_state,
                        &mut ex_message,
                        k,
                    );
                }
            }
        }
        let handle_ns = trace::toc(handle_start);
        let render_start = trace::tic();
        {
            let viewport_rows = screen.rows.saturating_sub(1) as usize;
            let cur = &mut buffers[current];
            refresh_bytes_cache(cur);
            let head = cur.sels.primary().head;
            ensure_visible_indexed(&cur.line_starts, head, &mut cur.top_line, viewport_rows);
        }
        render_all(
            &mut screen,
            &buffers,
            current,
            mode,
            &ex_input,
            &search_input,
            &search_state,
            &ex_message,
            last_key.as_ref(),
            &last_bytes,
        )?;
        let render_ns = trace::toc(render_start);
        let total_ns = trace::toc(frame_start);
        trace::emit_frame(
            total_ns,
            handle_ns,
            render_ns,
            buffers[current].buffer.len(),
        );
    }
    Ok(())
}

/// Spawn an LSP server for `path` (if it's a recognized language) and send
/// didOpen for its current buffer content. No-op if a server is already
/// running, or if the language isn't recognized, or if spawn fails. Adds
/// new files to an existing server when called repeatedly.
fn maybe_start_lsp_and_open(
    lsp_client: &mut Option<LspClient>,
    path: &Path,
    buffer: &Buffer,
) {
    let lang_id = match path.extension().and_then(|e| e.to_str()) {
        Some("go") => "go",
        _ => return,
    };
    if lsp_client.is_none() {
        let cwd = std::env::current_dir().unwrap_or_else(|_| PathBuf::from("."));
        let root_uri = match lsp::path_to_uri(&cwd) {
            Ok(u) => u,
            Err(_) => return,
        };
        match LspClient::spawn("gopls", &root_uri) {
            Ok(c) => *lsp_client = Some(c),
            Err(_) => return,
        }
    }
    if let (Some(client), Ok(uri)) = (lsp_client.as_mut(), lsp::path_to_uri(path)) {
        let text = String::from_utf8_lossy(&collect_bytes(buffer)).into_owned();
        let _ = client.did_open(&uri, lang_id, &text);
    }
}

/// Handle an `LspAction` queued by the modal layer. For goto-definition we
/// send the request, then either:
/// - Same-file result: jump the cursor in the current buffer.
/// - Cross-file result: open or switch to that file as a new buffer, then
///   jump the cursor there.
fn dispatch_lsp(
    action: LspAction,
    client: Option<&mut LspClient>,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    highlighter: &Highlighter,
    ex_message: &mut String,
) {
    let client = match client {
        Some(c) => c,
        None => {
            *ex_message = "no LSP server for this file".to_string();
            return;
        }
    };
    let cur_uri = match buffers[*current]
        .path
        .as_ref()
        .and_then(|p| lsp::path_to_uri(p).ok())
    {
        Some(u) => u,
        None => {
            *ex_message = "LSP: current buffer has no URI".to_string();
            return;
        }
    };
    match action {
        LspAction::GotoDefinition => {
            let (line, character) = {
                let cur = &buffers[*current];
                let bytes = collect_bytes(&cur.buffer);
                let head = cur.sels.primary().head;
                let line = line_index(&bytes, head) as u32;
                let line_start_byte = byte_at_line(&bytes, line as usize);
                let character = head.saturating_sub(line_start_byte) as u32;
                (line, character)
            };
            let loc = match client.definition(&cur_uri, line, character) {
                Ok(Some(loc)) => loc,
                Ok(None) => {
                    *ex_message = "no definition found".to_string();
                    return;
                }
                Err(e) => {
                    *ex_message = format!("LSP error: {}", e);
                    return;
                }
            };
            // If the definition is in another file, open it (or switch to
            // an already-open buffer) before jumping the cursor.
            if loc.uri != cur_uri {
                let target_path = match lsp::uri_to_path(&loc.uri) {
                    Some(p) => p,
                    None => {
                        *ex_message = format!("LSP: cannot parse target URI: {}", loc.uri);
                        return;
                    }
                };
                if !open_or_switch_to(
                    buffers,
                    current,
                    &target_path,
                    Some(client),
                    highlighter,
                    ex_message,
                ) {
                    return;
                }
            }
            // Now buffers[current] is the target buffer; jump the cursor.
            let cur = &mut buffers[*current];
            let bytes = collect_bytes(&cur.buffer);
            let target_line_start = byte_at_line(&bytes, loc.line as usize);
            let target = target_line_start.saturating_add(loc.character as usize);
            let new_head = snap_to_char_or_last(&bytes, target);
            cur.sels.reduce_to_primary();
            let p = cur.sels.primary_mut();
            p.anchor = new_head;
            p.head = new_head;
            p.desired_col = display_col(&bytes, line_start(&bytes, new_head), new_head);
        }
    }
}

/// Open `path` as a new buffer (or switch to it if already open). On a new
/// open, runs the syntax highlighter and notifies the LSP server via
/// `didOpen` if applicable. Returns `false` and sets `ex_message` on
/// failure (e.g. can't read the file).
fn open_or_switch_to(
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    path: &Path,
    lsp_client: Option<&mut LspClient>,
    highlighter: &Highlighter,
    ex_message: &mut String,
) -> bool {
    if let Some(idx) = buffers
        .iter()
        .position(|b| b.path.as_deref() == Some(path))
    {
        *current = idx;
        return true;
    }
    let buffer = if path.exists() {
        match Buffer::open(path) {
            Ok(b) => b,
            Err(e) => {
                *ex_message = format!("open failed: {}", e);
                return false;
            }
        }
    } else {
        Buffer::empty()
    };
    let mut eb = EditorBuffer::new(buffer, Some(path.to_path_buf()));
    reparse_and_highlight(&mut eb, highlighter);
    buffers.push(eb);
    *current = buffers.len() - 1;
    if let Some(client) = lsp_client {
        let lang_id = match path.extension().and_then(|e| e.to_str()) {
            Some("go") => Some("go"),
            _ => None,
        };
        if let Some(lang_id) = lang_id {
            if let Ok(uri) = lsp::path_to_uri(path) {
                let text =
                    String::from_utf8_lossy(&collect_bytes(&buffers[*current].buffer)).into_owned();
                let _ = client.did_open(&uri, lang_id, &text);
            }
        }
    }
    true
}

/// Handle a buffer-list-level Ex action. Loads/switches/lists buffers and
/// notifies the LSP server about newly opened files.
fn dispatch_ex_action(
    action: ExAction,
    buffers: &mut Vec<EditorBuffer>,
    current: &mut usize,
    lsp_client: Option<&mut LspClient>,
    highlighter: &Highlighter,
    ex_message: &mut String,
) {
    match action {
        ExAction::OpenFile(path) => {
            open_or_switch_to(buffers, current, &path, lsp_client, highlighter, ex_message);
        }
        ExAction::NextBuffer => {
            if buffers.len() > 1 {
                *current = (*current + 1) % buffers.len();
            }
        }
        ExAction::PrevBuffer => {
            if buffers.len() > 1 {
                *current = (*current + buffers.len() - 1) % buffers.len();
            }
        }
        ExAction::ListBuffers => {
            let parts: Vec<String> = buffers
                .iter()
                .enumerate()
                .map(|(i, b)| {
                    let marker = if i == *current { "*" } else { " " };
                    format!("{}{} {}", marker, i + 1, b.display_name())
                })
                .collect();
            *ex_message = parts.join("  ");
        }
    }
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
fn render_all(
    screen: &mut Screen,
    buffers: &[EditorBuffer],
    current: usize,
    mode: Mode,
    ex_input: &str,
    search_input: &str,
    search: &SearchState,
    ex_message: &str,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
) -> io::Result<()> {
    let cur = &buffers[current];
    let buffer_count = buffers.len();
    let buffer_label = if buffer_count > 1 {
        format!("[{}/{}] {}", current + 1, buffer_count, cur.display_name())
    } else {
        cur.display_name()
    };
    render(
        screen,
        &cur.cached_bytes,
        &cur.line_starts,
        &cur.sels,
        &cur.flat_scopes,
        mode,
        cur.top_line,
        &buffer_label,
        ex_input,
        search_input,
        search,
        ex_message,
        last_key,
        last_bytes,
    )
}

#[allow(clippy::too_many_arguments)]
fn render(
    screen: &mut Screen,
    bytes: &[u8],
    line_starts: &[usize],
    sels: &Selections,
    scopes: &[ScopeId],
    mode: Mode,
    top_line: usize,
    buffer_label: &str,
    ex_input: &str,
    search_input: &str,
    search: &SearchState,
    ex_message: &str,
    last_key: Option<&KeyEvent>,
    last_bytes: &[u8],
) -> io::Result<()> {
    screen.begin_frame();
    let cols = screen.cols;
    let viewport_rows = screen.rows.saturating_sub(1);
    let primary = sels.primary();
    let head = primary.head;
    let start_byte = byte_at_line_cached(line_starts, top_line, bytes.len());

    // `line_starts.len()` is always at least 1 (we always seed with 0); the
    // total number of newline-terminated lines is `line_starts.len()` and
    // the visible-line count is the same (we count trailing partial lines).
    let total_lines = line_starts.len();
    let line_digits = total_lines.to_string().len() as u16;
    let gutter: u16 = if cols > line_digits + 2 {
        line_digits + 1
    } else {
        0
    };
    let content_cols = cols.saturating_sub(gutter);

    let sel_ranges: Vec<(usize, usize)> = sels
        .iter()
        .map(|s| {
            let lo = s.min();
            let hi = next_char_or_end(bytes, s.max());
            (lo, hi)
        })
        .collect();
    let in_any_selection =
        |i: usize| -> bool { sel_ranges.iter().any(|&(s, e)| i >= s && i < e) };
    let sel_min = primary.min();
    let sel_max = primary.max();

    let preview_matches: Vec<(usize, usize)> = match (mode, search.preview.as_ref()) {
        (Mode::Search, Some(re)) => all_matches(bytes, re),
        _ => Vec::new(),
    };
    let in_preview =
        |i: usize| -> bool { preview_matches.iter().any(|&(s, e)| i >= s && i < e) };

    let mut row: u16 = 1;
    let mut col: u16 = 1;
    let mut cur_row: u16 = 1;
    let mut cur_col: u16 = 1;
    let mut i = start_byte;
    let mut current_lineno = top_line + 1;
    // Tracked SGR + cursor state.
    // - `style_fg/bg`: last emitted SGR fg/bg. Cells emit transition strings
    //   only when this changes.
    // - `cursor_at`: where the terminal cursor is *after* the most recent
    //   emit. If a cell wants to write at exactly that position we can skip
    //   the `\x1b[r;cH` escape entirely (terminal advances cursor with each
    //   printed glyph). Reset to `None` on any discontinuity (a skipped
    //   cell, row change without a line-number, etc.).
    let mut style_fg: Option<&'static str> = None;
    let mut style_bg: Option<&'static str> = None;
    let mut cursor_at: Option<(u16, u16)> = None;
    if gutter > 0 && row <= viewport_rows {
        draw_lineno(screen, row, current_lineno, gutter);
        cursor_at = Some((row, gutter + 1));
    }

    loop {
        if i == head && row <= viewport_rows {
            cur_row = row;
            cur_col = col.max(1).min(content_cols.max(1));
        }
        if i >= bytes.len() || row > viewport_rows {
            break;
        }
        let b = match bytes.get(i) {
            Some(&b) => b,
            None => break,
        };
        let show_selection = matches!(mode, Mode::Normal | Mode::Search);
        let cursor_on_buffer = matches!(mode, Mode::Normal | Mode::Insert);
        let in_sel =
            show_selection && in_any_selection(i) && !(cursor_on_buffer && i == head);
        let in_match = !in_sel && in_preview(i);
        let bg: Option<&'static str> = if in_sel {
            Some(SEL_BG)
        } else if in_match {
            Some(MATCH_BG)
        } else {
            None
        };
        let scope = scopes.get(i).copied().unwrap_or(ScopeId::Default);
        let fg_seq: Option<&'static str> = if scope == ScopeId::Default {
            None
        } else {
            Some(theme::fg_for_scope(scope))
        };
        match b {
            b'\n' => {
                row = row.saturating_add(1);
                col = 1;
                current_lineno += 1;
                if gutter > 0 && row <= viewport_rows {
                    draw_lineno(screen, row, current_lineno, gutter);
                    cursor_at = Some((row, gutter + 1));
                    style_fg = None;
                    style_bg = None;
                } else {
                    cursor_at = None;
                }
                i += 1;
            }
            b'\r' => {
                i += 1;
            }
            b'\t' => {
                let advance = 4 - ((col as usize - 1) % 4);
                if bg.is_some() && col <= content_cols {
                    // Tabs only need a visible body when there's a bg to
                    // paint; otherwise we just advance the column counter
                    // and let the next emit position past the gap.
                    const SPACES: &[u8; 4] = b"    ";
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        row,
                        col + gutter,
                        advance as u16,
                        fg_seq,
                        bg,
                        &SPACES[..advance],
                    );
                } else {
                    cursor_at = None;
                }
                col = col.saturating_add(advance as u16);
                i += 1;
            }
            c if c < 0x20 => {
                let letter = c + 0x40;
                let body = [b'^', letter];
                if col <= content_cols {
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        row,
                        col + gutter,
                        2,
                        fg_seq,
                        bg,
                        &body,
                    );
                } else {
                    cursor_at = None;
                }
                col = col.saturating_add(2);
                i += 1;
            }
            _ => {
                let n = utf8_len(b);
                let end = (i + n).min(bytes.len());
                if col <= content_cols {
                    let glyph = bytes.get(i..end).unwrap_or(b"?");
                    emit_styled_cell(
                        screen,
                        &mut cursor_at,
                        &mut style_fg,
                        &mut style_bg,
                        row,
                        col + gutter,
                        1,
                        fg_seq,
                        bg,
                        glyph,
                    );
                } else {
                    cursor_at = None;
                }
                col = col.saturating_add(1);
                i = end;
            }
        }
    }

    // End of buffer rendering — reset SGR so the status bar starts clean.
    if style_fg.is_some() || style_bg.is_some() {
        screen.append_raw("\x1b[0m");
    }

    let primary_size = sel_max.saturating_sub(sel_min) + if bytes.is_empty() { 0 } else { 1 };
    let multi_label = if sels.len() > 1 {
        format!("{} sels · ", sels.len())
    } else {
        String::new()
    };
    let key_str = last_key.map(format_key).unwrap_or_else(|| "-".to_string());
    let bytes_str = if last_bytes.is_empty() {
        "-".to_string()
    } else {
        format_bytes(last_bytes)
    };
    let abs_line = line_index_cached(line_starts, head) + 1;
    let mode_str = match mode {
        Mode::Normal => "N",
        Mode::Insert => "I",
        Mode::Ex => "X",
        Mode::Search => "S",
    };
    let cols_usize = cols as usize;
    let is_prompt = matches!(mode, Mode::Ex | Mode::Search);

    let viewport_cur_col = cur_col.saturating_add(gutter);
    let (status, final_cur_row, final_cur_col) = if is_prompt {
        let (prefix, input) = if mode == Mode::Ex {
            (":", ex_input)
        } else {
            ("/", search_input)
        };
        let prompt = format!("{}{}", prefix, input);
        let col_pos = (prompt.chars().count() as u16).saturating_add(1).max(1);
        (prompt, screen.rows, col_pos)
    } else if !ex_message.is_empty() {
        (format!(" {} ", ex_message), cur_row, viewport_cur_col)
    } else {
        let s = format!(
            " [{}] {} · ln {} col {} · {}sel {}b · last:{} raw:{} ",
            mode_str,
            buffer_label,
            abs_line,
            cur_col,
            multi_label,
            primary_size,
            key_str,
            bytes_str
        );
        (s, cur_row, viewport_cur_col)
    };

    let mut padded: String = status.chars().take(cols_usize).collect();
    while padded.chars().count() < cols_usize {
        padded.push(' ');
    }
    let status_text = if is_prompt {
        padded
    } else {
        format!("\x1b[7m{}\x1b[0m", padded)
    };
    screen.write_at(screen.rows, 1, &status_text);

    let block_cursor = mode == Mode::Normal;
    screen.set_cursor_shape(block_cursor);
    screen.end_frame(final_cur_row, final_cur_col)
}
