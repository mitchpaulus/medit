# medit

A small modal text editor. Vim-like motions, Kakoune-like selection-first
editing, multi-cursor.

## Installation

### Quick install

```sh
curl -fsSL https://my.com/install.sh | sh -
```

This builds `medit` from source and installs it into your cargo bin directory
(usually `~/.cargo/bin`). It requires the [Rust toolchain](https://rustup.rs)
and a C compiler; the script checks for both and tells you what to install if
either is missing.

### With cargo (if you already have Rust)

Everything `medit` needs — the tree-sitter grammars and highlight queries — is
embedded in the binary, so a single `cargo install` produces a self-contained
executable:

```sh
cargo install --git https://github.com/mitchpaulus/medit --locked
```

`--locked` uses the committed `Cargo.lock`; drop it to let cargo re-resolve
dependencies. Building also needs a C compiler (`cc`/`gcc`/`clang`) for the
vendored tree-sitter parsers.

## Documentation

See [`doc/medit.html`](doc/medit.html) for the full keybinding reference.
