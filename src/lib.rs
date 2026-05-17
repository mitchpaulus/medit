//! medit's headless editor core. The binary in `main.rs` wraps this with
//! terminal I/O, rendering, and the main loop. Tests in `tests/` drive this
//! library directly via byte-level keystroke input.

pub mod buffer;
pub mod core;
pub mod input;
pub mod lsp;
