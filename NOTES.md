# medit — working notes

Scratchpad for implementation. Not the design doc (`design.md` is owned by the user). Anything load-bearing belongs in `design.md` once stable.

## Locked-in decisions (2026-05-15 session)

### Stack
- **Language:** Rust, single bin crate (no library split — original "consumable by my shell" requirement dropped).
- **Crate policy:** std + libc + small curated set. Each addition justified.
  - Expected: `libc` (or `nix`), `serde` + `serde_json` (LSP), `regex` (search + compile-mode errors), maybe `memmap2`.
  - **Open:** confirm `serde_json` is acceptable. Hand-rolling JSON for LSP is a tarpit.
- **Concurrency:** std threads + `mpsc` channels. No async runtime.
- **Terminal:** Direct termios via libc/nix. ANSI escape sequences by hand. SIGWINCH for resize. No crossterm, no ratatui.
- **Config:** None. Edit source directly.

### Buffer
- **Piece table** over mmap'd original + append-only edit buffer. Lazy line index.
- **Cursor type:** `Vec<Selection>` kept sorted, non-overlapping, normalized after every edit. Designed for multi-cursor from day one even though only one is visible most of the time.
- **Undo:** operation log over the piece table.

### Modal grammar (locked; see `design.md` rewrite for full table)
- Modes: Normal, Insert, Visual (char `v` + line `V` — NO visual-block), Search (regex), Ex (`:`), Multi-cursor overlay.
- `[count] operator [count] (motion | text-object)`. `.` repeats last change. Doubled-op = linewise.
- Operators: `d c y > < = gu gU g~ !`. `D C Y` to EOL. **`Y` yanks to EOL, not whole line** (deliberate Vim deviation).
- Registers: `""` default, `"+` system clipboard, `"_` blackhole. No named/numbered.
- Insert→Normal: `Esc` OR `jf` (short timeout, ~200ms). `jf` is user muscle memory — must work.
- Leader: `<Space>` (which-key style menus).
- Macros: deferred.

### Multi-cursor
- Derived from search, not a primitive.
- Entry: `*`/`g*` (Vim-style add-next / skip-and-add), or `g/` after a search to promote ALL matches.
- Exit: `,` collapses to primary (NOT `Esc` — Esc must stay safe for mode transitions).
- In multi-cursor state: every keystroke applies to all cursors identically.
- `<`/`>` rotate which cursor is primary.

### LSP (stdio, v1 scope)
- Diagnostics, goto-def (`gd`), references (`gr`), rename (`gn`), hover (`K`), completion.
- Per server: 1 process + reader thread + writes from UI thread. Channels back to UI.
- JSON-RPC framing: `Content-Length` header + body.

### Compile-mode (emacs-faithful)
- Async subprocess, reader thread pipes stdout/stderr to a dedicated buffer.
- ANSI SGR color subset (foreground colors at minimum; bold; reset).
- Per-language error regex registry. Ship: rustc, cargo, go, gcc/clang.
- `]e`/`[e` next/prev error → jump to file:line in a stack pane.
- Ex: `:make {cmd}`, `:recompile`.

### Spell check
- Trie + SCOWL en_US wordlist, mmap'd, length-prefixed format regenerable from source.
- Skip identifier-shaped tokens (CamelCase, snake_case, contains digits).
- SGR underline + color for misspellings.

### Window/split model
- **Tiling-WM style** (master + stack, like dwm). User does NOT choose orientation.
- One master pane (left), vertical stack (right).
- New views (compile, references, search results) open as stack panes automatically.
- Keybindings: `<Space>w m` swap master, `<Space>w j/k` focus stack, `<Space>w h/l` master↔stack, `<Space>w c` close, `<Space>w +/-` resize.
- No nested splits. Single-pane mode when only one buffer visible.

## Build roadmap

### M0 — Skeleton (start here)
- `cargo init` (bin crate).
- Termios raw-mode RAII guard via libc. `Drop` restores cooked mode AND on panic (use `std::panic::set_hook` or a guard that survives panic).
- SIGWINCH handler → channel poke. Don't do work in the handler itself.
- ANSI input parser. Cover plain keys, CSI cursor keys, modifiers (CSI-u / kitty keyboard protocol), bracketed paste, mouse (later). **This is bigger than it looks.**
- Frame loop: events → state → diff render → flush. Plain "hello world" buffer.

### M1 — Buffer & view
- Piece table impl with mmap. Lazy line index.
- `Selection` type and `Vec<Selection>` invariants (sorted, non-overlapping, normalize after edit).
- Undo log.
- Viewport + scroll. Open/edit/save real files.

### M2 — Modal grammar
- Spec out exact key→Action table before coding. (Already mostly done — see `design.md`.)
- Command engine as data. Actions take `&mut [Selection]` so multi-cursor is free.
- Insert-mode readline subset: `C-a C-e C-b C-f M-b M-f C-w M-d C-k C-u C-h`.
- `jf` Esc-replacement with ~200ms timeout: if `j` then `f` within window → exit insert; else emit `j` literally.

### M3 — LSP client
- JSON-RPC stdio with `Content-Length` framing.
- Reader thread per server; writes from UI thread.
- Implement in order: diagnostics → goto-def → hover → completion → references → rename.
- Handle: server lifecycle, `initialize`/`initialized` handshake, didOpen/didChange/didSave, capability negotiation.

### M4 — Completion UI
- Popup widget: merge buffer-words + LSP completion items.
- Substring + camelCase scoring.
- `C-n`/`C-p` to navigate; `Tab` to accept.

### M5 — Compile-mode
- Async `Command` spawn; reader thread → output buffer.
- ANSI SGR parser (subset).
- Error regex registry. `next-error`/`recompile`.

### M6 — Spell check
- Wordlist loader (build-time tool to generate the binary format).
- Trie lookup hot path.
- Token classifier to skip identifiers.

### M7 — Window/split model
- Could come earlier (M3 wants a place to put diagnostics); maybe move ahead of M3.

## Risks & open items

1. **Input parser scope.** Terminal modifier-encoding varies (kitty, foot, wezterm, xterm). Decide target terminals early. If kitty keyboard protocol → can distinguish `C-i` from `Tab`, `C-m` from `Enter`. Otherwise legacy encodings restrict the keymap.
2. **`serde_json` for LSP.** Confirm it's allowed in curated set. Strong recommendation: yes.
3. **`mmap` on edited files.** Piece-table preserves the original mmap'd region read-only; new content goes into the append buffer. Save = write a fresh file then rename. Don't write back into the mmap.
4. **Compile-mode is M5-sized work.** Not a weekend. Plan accordingly.
5. **No async runtime + many LSP servers.** Each is 1 process + 1 reader thread + channels. Manageable for 3–4 servers; not a problem.
6. **`jf` timeout in raw mode.** No keyboard auto-repeat suppression — implementation is purely "did we see `f` within Nms of `j`." Pick N empirically (start at 200ms).
7. **Multi-cursor edge cases.** What if two cursors' edits would overlap (e.g. both type into the same word)? Normalize-after-edit must merge overlapping selections. Decide policy: merge silently, or warn.

## Conventions for this codebase

- Module layout TBD; will emerge from M0/M1. Likely top-level modules: `term` (raw mode + input parser + render), `buffer` (piece table), `cursor` (selections), `mode` (modal grammar), `lsp`, `compile`, `spell`, `ui` (popup, statusline), `wm` (tiling layout).
- No `unsafe` outside the `term` module (termios FFI) and possibly `mmap` wrapper.
- Tests live alongside code. Integration tests in `tests/` for end-to-end editor behavior using a virtual terminal harness.
