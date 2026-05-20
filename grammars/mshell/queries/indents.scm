; Indentation rules for mshell.
;
; This file uses the capture names supported by nvim-treesitter
; (`@indent.begin`, `@indent.end`, `@indent.align`) as well as the
; capture names supported by Helix (`@indent`, `@outdent`). Editors that
; don't recognize a capture simply ignore it, so the same file works for
; both.

; Container nodes — their children indent one level deeper.
[
  (list)
  (quotation)
  (dict)
  (grid)
] @indent @indent.begin

; Closing delimiters dedent back out.
"]"  @outdent @indent.end
")"  @outdent @indent.end
"}"  @outdent @indent.end
"|]" @outdent @indent.end

; Help Neovim align continuation lines with the opening delimiter when
; the user prefers visual alignment over a fixed-width indent.
[
  "["
  "("
  "{"
  "[|"
] @indent.align
