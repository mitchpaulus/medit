; Comments
(line_comment) @comment

; Strings
(string)                @string
(single_quoted_string)  @string
(format_string)         @string.special
(path)                  @string.special.path

; Numbers and dates
(integer)   @number
(float)     @number.float
(datetime)  @constant.builtin

; Booleans
(boolean) @constant.builtin.boolean

; Keywords
(keyword)      @keyword
(type_keyword) @type.builtin

; Block keywords now consumed as literals by definition/match_block/if_block
"def"   @keyword
"match" @keyword
"if"    @keyword
"else"  @keyword
"else*" @keyword
"*if"   @keyword
"end"   @keyword

; Built-in functions / stack operators
(builtin) @function.builtin

; Variables
(var_retrieve) @variable
(var_store)    @variable

; Environment variables
(env_retrieve) @variable.builtin
(env_store)    @variable.builtin
(env_check)    @variable.builtin
(positional)   @variable.parameter

; Prefix-quote references like `filter.`
(prefix_quote) @function

; Field getters like `:name`, `:'children'`
(getter) @property

; Indexers
(indexer)        @operator
(start_indexer)  @operator
(end_indexer)    @operator
(slice_indexer)  @operator

; Execution / capture / redirection operators
(execute_operator)    @operator
(redirect_operator)   @operator
(comparison_operator) @operator
(match_arm_dup)       @operator

; General punctuation
(punctuation) @punctuation.delimiter

; Structural separators: dict/grid/match commas and dict/match `:`
"," @punctuation.delimiter
":" @punctuation.delimiter

; Brackets
"["  @punctuation.bracket
"]"  @punctuation.bracket
"("  @punctuation.bracket
")"  @punctuation.bracket
"{"  @punctuation.bracket
"}"  @punctuation.bracket
"[|" @punctuation.bracket
"|]" @punctuation.bracket
