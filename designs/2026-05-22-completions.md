Here are design thoughts on completion:

- Async - needs to handle slow, unresponsive LSP servers
- The triggers are going to be very file type specific and intricate
- The LSP will be main source, but certain file types will have other sources that won't have to rely on the LSP server.
- The prefix/fuzzy matching will also be conditional in different cases.
- Debouncing by default


Initial keybinds:

- Tab/Enter, accept current top item
- <C-n>/<C-p>, move up and down (scoped to only when the dialog is showing.)


For v1:

 1. Parallel non-blocking LSP path (A) vs full async refactor (B)?

Full async refactor

 2. Continuous didChange in insert mode, or only-before-completion?

Be performance conscious, only right before completion.

 3. Auto-trigger threshold: N=1, N=2, or trigger-chars only + manual <C-Space>?

This will be file type specific. Right now let's start with Python and mshell.

Python:

  - After a '.'
  - N = 2 otherwise

Mshell:

  - After a '@' for variable name matching. The '@' needs to be part of the request so the LSP knows it's doing a variable name completion.

 4. Prefix or fuzzy match for v1?

- Case-insensitive prefix for now

 5. Multi-cursor: disable completion when >1 cursor, or primary-only insert?

- disable on multi cursor for now.
