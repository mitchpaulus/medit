This is the design requirements for a terminal text editor, whose only sole user is me.

Requirements

- Written in Rust
- It must have a concept of multiple cursors
- It must integrate the basics of the LSP, only over stdio
  - Goto Definition
- No dependencies unless required
- Pure Rust if possible
- It should be a modal editor like Vim
- It must have a really nice "Compile-mode" functionality like emacs
- It should prioritize startup time, even on huge files
- Low latency is key
- Generally uses Vim keybindings/Emacs readline bindings in insert mode
- Very well done built-in completion UI
- Simple spell checking
