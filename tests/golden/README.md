# Golden behavior tests

Each `.json` file in this directory describes one editor scenario. The runner
loads each file, sets up an initial `Buffer + Selection + Mode`, feeds raw
keystroke bytes through medit's input parser and per-mode handlers, then
compares the resulting state to the expected outcome.

These files are the **language-portable contract**. Any future port of medit
(Rust → Go → whatever) should be able to write its own runner that drives the
same JSON files and pass the same tests.

## Schema

```json
{
  "name": "human-readable description",
  "initial": "buffer text with selection markers",
  "keys": "raw byte sequence (JSON string with \\u escapes)",
  "expected": "buffer text after keys, with selection markers",

  "mode": "normal",
  "expected_mode": "normal"
}
```

| Field           | Required | Notes                                                                      |
|-----------------|----------|----------------------------------------------------------------------------|
| `name`          | yes      | Short descriptive label                                                    |
| `initial`       | yes      | Initial buffer content + selection markers. UTF-8.                         |
| `keys`          | yes      | Raw bytes fed to the input parser. JSON string; use `\u` for non-printable |
| `expected`      | yes      | Final buffer content + selection markers                                   |
| `mode`          | no       | Starting mode: `"normal"` (default), `"insert"`, `"ex"`                    |
| `expected_mode` | no       | Asserted final mode. Default: same as starting `mode`                      |

## Selection markers

Selection is marked in `initial` and `expected` with bracket pairs around the
selected text:

- **`<...>`** — forward selection. Anchor at the opening `<`, head at the
  character just before the closing `>`. Single-char selection: `<x>`.
- **`>...<`** — reversed selection. Head at the opening `>`, anchor at the
  character just before the closing `<`.
- **No markers** — anchor and head both at offset 0 (empty selection at
  buffer start).

Selection markers are not currently escapable. If your test text legitimately
needs `<` or `>`, rewrite the test text to avoid them.

### Examples

```
hello <wo>rld
        ^^ selection covers "wo", head on 'o' (forward)

hello >wo<rld
        ^^ selection covers "wo", head on 'w' (reversed)

<h>ello
 ^ single-char selection on 'h'
```

## Key bytes

`keys` is a raw byte stream — exactly what a terminal would send. Use JSON's
`\u` escapes for non-printable bytes:

| Key        | Bytes               | JSON              |
|------------|---------------------|-------------------|
| `Esc`      | `0x1B`              | `""`        |
| `Enter`    | `0x0D` or `0x0A`    | `"\r"` or `"\n"`  |
| `Backspace`| `0x7F`              | `""`        |
| `Tab`      | `0x09`              | `"\t"`            |
| `Ctrl-c`   | `0x03`              | `""`        |
| `Up`       | `\x1b[A`            | `"[A"`      |
| `Shift+Up` | `\x1b[1;2A`         | `"[1;2A"`   |

Plain printable bytes are themselves: `"dw"` means press `d` then `w`.

## File naming

`<area>_<scenario>.json`. Examples: `motion_w.json`, `delete_word_boundary.json`,
`paste_after_empty_line.json`. Keep names short and grepable.
