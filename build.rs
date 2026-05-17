//! Compile the vendored tree-sitter grammar parsers into a static library
//! that gets linked into the editor. Each language lives under
//! `grammars/<lang>/src/{parser.c,scanner.c}` (scanner is optional).
//! Headers shared across grammars are in `grammars/include/`.
//!
//! Adding a language: drop its sources under `grammars/<lang>/`, add an
//! entry to `LANGUAGES` below, and declare its `tree_sitter_<lang>` fn
//! in `src/highlight.rs`.

use std::path::Path;

/// (directory name under grammars/, c-symbol name).
/// The c-symbol is the language function name exported by parser.c —
/// usually matches the dir, with `-` translated to `_`.
const LANGUAGES: &[(&str, &str)] = &[("go", "go")];

fn main() {
    println!("cargo:rerun-if-changed=grammars");

    for (dir, sym) in LANGUAGES {
        let grammar_dir = Path::new("grammars").join(dir);
        let src_dir = grammar_dir.join("src");
        let parser_c = src_dir.join("parser.c");
        if !parser_c.exists() {
            panic!("missing {}", parser_c.display());
        }
        let mut build = cc::Build::new();
        build
            .include(&src_dir)
            .include("grammars/include")
            .file(&parser_c)
            // tree-sitter parsers do a lot of fall-through switches; the
            // generated C has plenty of unused defines / variables.
            .flag_if_supported("-Wno-unused-but-set-variable")
            .flag_if_supported("-Wno-unused-parameter")
            .flag_if_supported("-Wno-unused-value")
            .flag_if_supported("-Wno-unused-variable")
            .warnings(false);

        let scanner_c = src_dir.join("scanner.c");
        let scanner_cc = src_dir.join("scanner.cc");
        if scanner_c.exists() {
            build.file(&scanner_c);
        } else if scanner_cc.exists() {
            build.cpp(true).file(&scanner_cc);
        }

        // Each grammar becomes its own static lib: libtree_sitter_<sym>.a.
        let lib_name = format!("tree_sitter_{}", sym);
        build.compile(&lib_name);
    }
}
