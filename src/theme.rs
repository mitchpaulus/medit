//! Syntax highlighting scopes and color theme. Edited in source — there is
//! no theme config file. Add a new scope by extending `ScopeId`, mapping
//! capture names to it in `scope_for_capture`, and assigning an ANSI fg
//! sequence in `fg_for_scope`.
//!
//! Scope name resolution follows the tree-sitter convention: a capture
//! like `function.method` is resolved by trying the full name first, then
//! falling back to progressively shorter prefixes (`function`).

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ScopeId {
    Default,
    Keyword,
    Function,
    Type,
    Constant,
    String,
    StringEscape,
    Number,
    Comment,
    Operator,
    Punctuation,
    Variable,
    VariableStore,
    VariableRetrieve,
    EnvVariable,
    Attribute,
    Tag,
}

/// Resolve a capture name to a ScopeId. Tree-sitter `highlights.scm`
/// captures use dotted names (`function.method`, `keyword.return`); we
/// strip suffixes until something matches or we run out.
pub fn scope_for_capture(name: &str) -> ScopeId {
    let mut n = name;
    loop {
        if let Some(s) = exact_scope(n) {
            return s;
        }
        match n.rfind('.') {
            Some(i) => n = &n[..i],
            None => return ScopeId::Default,
        }
    }
}

fn exact_scope(name: &str) -> Option<ScopeId> {
    Some(match name {
        "keyword" => ScopeId::Keyword,
        "function" | "method" => ScopeId::Function,
        "type" => ScopeId::Type,
        "constant" | "boolean" => ScopeId::Constant,
        "string" => ScopeId::String,
        "escape" => ScopeId::StringEscape,
        "number" => ScopeId::Number,
        "comment" => ScopeId::Comment,
        "operator" => ScopeId::Operator,
        "punctuation" => ScopeId::Punctuation,
        "variable.store" => ScopeId::VariableStore,
        "variable.retrieve" => ScopeId::VariableRetrieve,
        "variable.builtin" => ScopeId::EnvVariable,
        "variable" | "parameter" => ScopeId::Variable,
        "attribute" | "label" => ScopeId::Attribute,
        "tag" => ScopeId::Tag,
        // Markup captures from the djot grammar (also used for .md files).
        // Routed onto existing scopes so headings/links/code stand out
        // without growing the ScopeId enum.
        "markup.heading" => ScopeId::Keyword,
        "markup.link.url" => ScopeId::Type,
        "markup.link.label" | "markup.link" => ScopeId::Function,
        "markup.raw" | "markup.raw.block" | "markup.math" => ScopeId::String,
        "markup.quote" => ScopeId::Comment,
        "markup.list" => ScopeId::Punctuation,
        "markup.strong" => ScopeId::Constant,
        "property" => ScopeId::Attribute,
        _ => return None,
    })
}

/// ANSI foreground color sequence for a scope. `Default` returns the
/// terminal default. Edit these to retheme.
pub fn fg_for_scope(scope: ScopeId) -> &'static str {
    match scope {
        ScopeId::Default => "\x1b[39m",
        ScopeId::Keyword => "\x1b[38;5;141m",     // soft purple
        ScopeId::Function => "\x1b[38;5;221m",    // warm yellow
        ScopeId::Type => "\x1b[38;5;110m",        // pale cyan
        ScopeId::Constant => "\x1b[38;5;209m",    // coral
        ScopeId::String => "\x1b[38;5;108m",      // moss green
        ScopeId::StringEscape => "\x1b[38;5;180m", // tan
        ScopeId::Number => "\x1b[38;5;173m",      // copper
        ScopeId::Comment => "\x1b[38;5;243m",     // mid gray
        ScopeId::Operator => "\x1b[38;5;188m",    // light gray
        ScopeId::Punctuation => "\x1b[38;5;188m",
        ScopeId::Variable => "\x1b[39m",
        ScopeId::VariableStore => "\x1b[38;5;174m",    // dusty rose — writes
        ScopeId::VariableRetrieve => "\x1b[38;5;152m", // pale aqua — reads
        ScopeId::EnvVariable => "\x1b[38;5;144m",      // warm khaki — env
        ScopeId::Attribute => "\x1b[38;5;179m",   // olive
        ScopeId::Tag => "\x1b[38;5;75m",          // soft blue
    }
}
