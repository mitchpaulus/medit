#!/bin/sh
# medit installer
#
#   curl -fsSL https://my.com/install.sh | sh -
#
# Builds medit from source with cargo and installs the `medit` binary into
# your cargo bin directory (usually ~/.cargo/bin). Everything the editor needs
# (tree-sitter grammars and highlight queries) is embedded in the binary, so
# the result is self-contained.

set -eu

REPO="${MEDIT_REPO:-https://github.com/mitchpaulus/medit}"
# Branch/tag/commit to install. Defaults to the default branch.
REF="${MEDIT_REF:-}"

err() { printf 'medit-install: %s\n' "$*" >&2; }

need_cmd() {
	if ! command -v "$1" >/dev/null 2>&1; then
		return 1
	fi
	return 0
}

main() {
	# Rust toolchain is required to build from source.
	if ! need_cmd cargo; then
		err "cargo (Rust toolchain) was not found on your PATH."
		err ""
		err "Install Rust, then re-run this installer:"
		err "    curl --proto '=https' --tlsv1.2 -fsSL https://sh.rustup.rs | sh"
		err ""
		err "After installing, restart your shell or run:"
		err "    . \"\$HOME/.cargo/env\""
		exit 1
	fi

	# build.rs compiles the vendored tree-sitter parsers via the `cc` crate,
	# so a C compiler must be available.
	if ! need_cmd cc && ! need_cmd gcc && ! need_cmd clang; then
		err "No C compiler (cc/gcc/clang) found; one is required to build the"
		err "bundled tree-sitter grammars. Install your platform's build tools:"
		err "    Debian/Ubuntu : sudo apt-get install build-essential"
		err "    Fedora        : sudo dnf install gcc"
		err "    macOS         : xcode-select --install"
		exit 1
	fi

	set -- install --git "$REPO" --locked --force
	if [ -n "$REF" ]; then
		# Pick the right selector if the caller pinned a ref.
		case "$REF" in
			v*|[0-9]*) set -- "$@" --tag "$REF" ;;
			*)         set -- "$@" --branch "$REF" ;;
		esac
	fi

	err "Building and installing medit from $REPO ..."
	cargo "$@"

	if need_cmd medit; then
		err "Done. 'medit' is on your PATH:"
		command -v medit >&2
	else
		bindir="${CARGO_HOME:-$HOME/.cargo}/bin"
		err "Done. Installed to $bindir/medit"
		err "Add it to your PATH if it isn't already:"
		err "    export PATH=\"$bindir:\$PATH\""
	fi
}

main "$@"
