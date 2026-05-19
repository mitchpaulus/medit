#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 54
#define LARGE_STATE_COUNT 53
#define SYMBOL_COUNT 308
#define ALIAS_COUNT 0
#define TOKEN_COUNT 293
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_LBRACK = 2,
  anon_sym_RBRACK = 3,
  anon_sym_LPAREN = 4,
  anon_sym_RPAREN = 5,
  anon_sym_LBRACE = 6,
  anon_sym_RBRACE = 7,
  anon_sym_LBRACK_PIPE = 8,
  anon_sym_PIPE_RBRACK = 9,
  sym_line_comment = 10,
  anon_sym_true = 11,
  anon_sym_false = 12,
  anon_sym_def = 13,
  anon_sym_end = 14,
  anon_sym_if = 15,
  anon_sym_iff = 16,
  anon_sym_else = 17,
  anon_sym_else_STAR = 18,
  anon_sym_STARif = 19,
  anon_sym_loop = 20,
  anon_sym_match = 21,
  anon_sym_break = 22,
  anon_sym_continue = 23,
  anon_sym_soe = 24,
  anon_sym_not = 25,
  anon_sym_and = 26,
  anon_sym_or = 27,
  anon_sym_read = 28,
  anon_sym_str = 29,
  anon_sym_as = 30,
  anon_sym_type = 31,
  anon_sym_try = 32,
  anon_sym_fail = 33,
  anon_sym_pure = 34,
  anon_sym_VER = 35,
  anon_sym_x = 36,
  anon_sym_int = 37,
  anon_sym_float = 38,
  anon_sym_bool = 39,
  anon_sym_dup = 40,
  anon_sym_swap = 41,
  anon_sym_drop = 42,
  anon_sym_over = 43,
  anon_sym_pick = 44,
  anon_sym_rot = 45,
  anon_sym_DASHrot = 46,
  anon_sym_nip = 47,
  anon_sym_w = 48,
  anon_sym_wl = 49,
  anon_sym_we = 50,
  anon_sym_wle = 51,
  anon_sym_len = 52,
  anon_sym_args = 53,
  anon_sym_glob = 54,
  anon_sym_toFloat = 55,
  anon_sym_toInt = 56,
  anon_sym_toPath = 57,
  anon_sym_toDt = 58,
  anon_sym_toGrid = 59,
  anon_sym_toCsv = 60,
  anon_sym_toCsvCell = 61,
  anon_sym_exit = 62,
  anon_sym_prompt = 63,
  anon_sym_stdin = 64,
  anon_sym_COLON_COLON = 65,
  anon_sym_foldl = 66,
  anon_sym_map = 67,
  anon_sym_each = 68,
  anon_sym_eachWhile = 69,
  anon_sym_filter = 70,
  anon_sym_append = 71,
  anon_sym_extend = 72,
  anon_sym_concat = 73,
  anon_sym_reverse = 74,
  anon_sym_sort = 75,
  anon_sym_sortV = 76,
  anon_sym_sortBy = 77,
  anon_sym_sortByCmp = 78,
  anon_sym_uniq = 79,
  anon_sym_zip = 80,
  anon_sym_enumerate = 81,
  anon_sym_enumerateN = 82,
  anon_sym_chunk = 83,
  anon_sym_pop = 84,
  anon_sym_take = 85,
  anon_sym_takeWhile = 86,
  anon_sym_skip = 87,
  anon_sym_dropWhile = 88,
  anon_sym_nth = 89,
  anon_sym_insert = 90,
  anon_sym_setAt = 91,
  anon_sym_del = 92,
  anon_sym_sum = 93,
  anon_sym_max = 94,
  anon_sym_max2 = 95,
  anon_sym_min = 96,
  anon_sym_min2 = 97,
  anon_sym_abs = 98,
  anon_sym_inc = 99,
  anon_sym_mod = 100,
  anon_sym_floor = 101,
  anon_sym_ceil = 102,
  anon_sym_round = 103,
  anon_sym_lines = 104,
  anon_sym_unlines = 105,
  anon_sym_unlinesCrLf = 106,
  anon_sym_split = 107,
  anon_sym_wsplit = 108,
  anon_sym_tsplit = 109,
  anon_sym_join = 110,
  anon_sym_trim = 111,
  anon_sym_trimStart = 112,
  anon_sym_trimEnd = 113,
  anon_sym_startsWith = 114,
  anon_sym_endsWith = 115,
  anon_sym_lower = 116,
  anon_sym_upper = 117,
  anon_sym_title = 118,
  anon_sym_leftPad = 119,
  anon_sym_findReplace = 120,
  anon_sym_in = 121,
  anon_sym_index = 122,
  anon_sym_lastIndexOf = 123,
  anon_sym_countSubStr = 124,
  anon_sym_parseJson = 125,
  anon_sym_parseCsv = 126,
  anon_sym_parseHtml = 127,
  anon_sym_parseExcel = 128,
  anon_sym_readFile = 129,
  anon_sym_readFileBytes = 130,
  anon_sym_readTsvFile = 131,
  anon_sym_writeFile = 132,
  anon_sym_appendFile = 133,
  anon_sym_fileExists = 134,
  anon_sym_isDir = 135,
  anon_sym_isFile = 136,
  anon_sym_fileSize = 137,
  anon_sym_cp = 138,
  anon_sym_mv = 139,
  anon_sym_rm = 140,
  anon_sym_rmf = 141,
  anon_sym_mkdir = 142,
  anon_sym_mkdirp = 143,
  anon_sym_cd = 144,
  anon_sym_pwd = 145,
  anon_sym_tempFile = 146,
  anon_sym_tempFileExt = 147,
  anon_sym_tempDir = 148,
  anon_sym_lsDir = 149,
  anon_sym_files = 150,
  anon_sym_dirs = 151,
  anon_sym_absPath = 152,
  anon_sym_dirname = 153,
  anon_sym_basename = 154,
  anon_sym_ext = 155,
  anon_sym_stem = 156,
  anon_sym_isCmd = 157,
  anon_sym_hardLink = 158,
  anon_sym_sha256sum = 159,
  anon_sym_md5 = 160,
  anon_sym_now = 161,
  anon_sym_date = 162,
  anon_sym_year = 163,
  anon_sym_month = 164,
  anon_sym_day = 165,
  anon_sym_hour = 166,
  anon_sym_minute = 167,
  anon_sym_dateFmt = 168,
  anon_sym_isoDateFmt = 169,
  anon_sym_isoDateTimeFmt = 170,
  anon_sym_isWeekend = 171,
  anon_sym_isWeekday = 172,
  anon_sym_dow = 173,
  anon_sym_addDays = 174,
  anon_sym_toUnixTime = 175,
  anon_sym_toUnixTimeMilli = 176,
  anon_sym_toUnixTimeMicro = 177,
  anon_sym_toUnixTimeNano = 178,
  anon_sym_fromUnixTime = 179,
  anon_sym_fromUnixTimeMilli = 180,
  anon_sym_fromUnixTimeMicro = 181,
  anon_sym_fromUnixTimeNano = 182,
  anon_sym_toOleDate = 183,
  anon_sym_fromOleDate = 184,
  anon_sym_utcToCst = 185,
  anon_sym_cstToUtc = 186,
  anon_sym_reMatch = 187,
  anon_sym_reFindAll = 188,
  anon_sym_reFindAllIndex = 189,
  anon_sym_reReplace = 190,
  anon_sym_reSplit = 191,
  anon_sym_just = 192,
  anon_sym_none = 193,
  anon_sym_isNone = 194,
  anon_sym_maybe = 195,
  anon_sym_bind = 196,
  anon_sym_psub = 197,
  anon_sym_typeof = 198,
  anon_sym_runtime = 199,
  anon_sym_hostname = 200,
  anon_sym_httpGet = 201,
  anon_sym_httpPost = 202,
  anon_sym_urlEncode = 203,
  anon_sym_base64encode = 204,
  anon_sym_base64decode = 205,
  anon_sym_utf8Str = 206,
  anon_sym_utf8Bytes = 207,
  anon_sym_get = 208,
  anon_sym_getDef = 209,
  anon_sym_set = 210,
  anon_sym_setd = 211,
  anon_sym_keys = 212,
  anon_sym_values = 213,
  anon_sym_keyValues = 214,
  anon_sym_all = 215,
  anon_sym_any = 216,
  anon_sym_cartesian = 217,
  anon_sym_groupBy = 218,
  anon_sym_listToDict = 219,
  anon_sym_repeat = 220,
  anon_sym_seq = 221,
  anon_sym_tab = 222,
  anon_sym_select = 223,
  anon_sym_exclude = 224,
  anon_sym_derive = 225,
  anon_sym_updateCol = 226,
  anon_sym_gridValues = 227,
  anon_sym_leftJoin = 228,
  anon_sym_outerJoin = 229,
  anon_sym_linearSearch = 230,
  anon_sym_linearSearchIndex = 231,
  anon_sym_binPaths = 232,
  anon_sym_wt = 233,
  anon_sym_tt = 234,
  anon_sym_ttFile = 235,
  anon_sym_uw = 236,
  anon_sym_tuw = 237,
  anon_sym_strCmp = 238,
  anon_sym_floatCmp = 239,
  anon_sym_versionSortCmp = 240,
  anon_sym_id = 241,
  anon_sym_2id = 242,
  anon_sym_3id = 243,
  anon_sym_2unpack = 244,
  anon_sym_2apply = 245,
  anon_sym_2each = 246,
  anon_sym_2tuple = 247,
  anon_sym_DOTs = 248,
  anon_sym_DOTb = 249,
  anon_sym_DOTdef = 250,
  anon_sym_DOTenv = 251,
  sym_string = 252,
  sym_format_string = 253,
  sym_single_quoted_string = 254,
  sym_path = 255,
  sym_datetime = 256,
  sym_float = 257,
  sym_integer = 258,
  sym_env_store = 259,
  sym_env_check = 260,
  sym_env_retrieve = 261,
  sym_positional = 262,
  sym_var_retrieve = 263,
  sym_var_store = 264,
  sym_slice_indexer = 265,
  sym_indexer = 266,
  sym_end_indexer = 267,
  sym_start_indexer = 268,
  sym_match_arm_dup = 269,
  sym_prefix_quote = 270,
  anon_sym_GT = 271,
  anon_sym_GT_GT = 272,
  anon_sym_2_GT = 273,
  anon_sym_2_GT_GT = 274,
  anon_sym_AMP_GT = 275,
  anon_sym_AMP_GT_GT = 276,
  anon_sym_LT = 277,
  anon_sym_LT_GT = 278,
  anon_sym_STAR = 279,
  anon_sym_STARb = 280,
  anon_sym_CARET = 281,
  anon_sym_CARETb = 282,
  anon_sym_SEMI = 283,
  anon_sym_BANG = 284,
  anon_sym_QMARK = 285,
  anon_sym_BANG_EQ = 286,
  anon_sym_LT_EQ = 287,
  anon_sym_GT_EQ = 288,
  anon_sym_AMP = 289,
  anon_sym_PIPE = 290,
  anon_sym_COMMA = 291,
  anon_sym_COLON = 292,
  sym_source_file = 293,
  sym__word = 294,
  sym_list = 295,
  sym_quotation = 296,
  sym_dict = 297,
  sym_grid = 298,
  sym_boolean = 299,
  sym_keyword = 300,
  sym_type_keyword = 301,
  sym_builtin = 302,
  sym_redirect_operator = 303,
  sym_execute_operator = 304,
  sym_comparison_operator = 305,
  sym_punctuation = 306,
  aux_sym_source_file_repeat1 = 307,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK_PIPE] = "[|",
  [anon_sym_PIPE_RBRACK] = "|]",
  [sym_line_comment] = "line_comment",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [anon_sym_def] = "def",
  [anon_sym_end] = "end",
  [anon_sym_if] = "if",
  [anon_sym_iff] = "iff",
  [anon_sym_else] = "else",
  [anon_sym_else_STAR] = "else*",
  [anon_sym_STARif] = "*if",
  [anon_sym_loop] = "loop",
  [anon_sym_match] = "match",
  [anon_sym_break] = "break",
  [anon_sym_continue] = "continue",
  [anon_sym_soe] = "soe",
  [anon_sym_not] = "not",
  [anon_sym_and] = "and",
  [anon_sym_or] = "or",
  [anon_sym_read] = "read",
  [anon_sym_str] = "str",
  [anon_sym_as] = "as",
  [anon_sym_type] = "type",
  [anon_sym_try] = "try",
  [anon_sym_fail] = "fail",
  [anon_sym_pure] = "pure",
  [anon_sym_VER] = "VER",
  [anon_sym_x] = "x",
  [anon_sym_int] = "int",
  [anon_sym_float] = "float",
  [anon_sym_bool] = "bool",
  [anon_sym_dup] = "dup",
  [anon_sym_swap] = "swap",
  [anon_sym_drop] = "drop",
  [anon_sym_over] = "over",
  [anon_sym_pick] = "pick",
  [anon_sym_rot] = "rot",
  [anon_sym_DASHrot] = "-rot",
  [anon_sym_nip] = "nip",
  [anon_sym_w] = "w",
  [anon_sym_wl] = "wl",
  [anon_sym_we] = "we",
  [anon_sym_wle] = "wle",
  [anon_sym_len] = "len",
  [anon_sym_args] = "args",
  [anon_sym_glob] = "glob",
  [anon_sym_toFloat] = "toFloat",
  [anon_sym_toInt] = "toInt",
  [anon_sym_toPath] = "toPath",
  [anon_sym_toDt] = "toDt",
  [anon_sym_toGrid] = "toGrid",
  [anon_sym_toCsv] = "toCsv",
  [anon_sym_toCsvCell] = "toCsvCell",
  [anon_sym_exit] = "exit",
  [anon_sym_prompt] = "prompt",
  [anon_sym_stdin] = "stdin",
  [anon_sym_COLON_COLON] = "::",
  [anon_sym_foldl] = "foldl",
  [anon_sym_map] = "map",
  [anon_sym_each] = "each",
  [anon_sym_eachWhile] = "eachWhile",
  [anon_sym_filter] = "filter",
  [anon_sym_append] = "append",
  [anon_sym_extend] = "extend",
  [anon_sym_concat] = "concat",
  [anon_sym_reverse] = "reverse",
  [anon_sym_sort] = "sort",
  [anon_sym_sortV] = "sortV",
  [anon_sym_sortBy] = "sortBy",
  [anon_sym_sortByCmp] = "sortByCmp",
  [anon_sym_uniq] = "uniq",
  [anon_sym_zip] = "zip",
  [anon_sym_enumerate] = "enumerate",
  [anon_sym_enumerateN] = "enumerateN",
  [anon_sym_chunk] = "chunk",
  [anon_sym_pop] = "pop",
  [anon_sym_take] = "take",
  [anon_sym_takeWhile] = "takeWhile",
  [anon_sym_skip] = "skip",
  [anon_sym_dropWhile] = "dropWhile",
  [anon_sym_nth] = "nth",
  [anon_sym_insert] = "insert",
  [anon_sym_setAt] = "setAt",
  [anon_sym_del] = "del",
  [anon_sym_sum] = "sum",
  [anon_sym_max] = "max",
  [anon_sym_max2] = "max2",
  [anon_sym_min] = "min",
  [anon_sym_min2] = "min2",
  [anon_sym_abs] = "abs",
  [anon_sym_inc] = "inc",
  [anon_sym_mod] = "mod",
  [anon_sym_floor] = "floor",
  [anon_sym_ceil] = "ceil",
  [anon_sym_round] = "round",
  [anon_sym_lines] = "lines",
  [anon_sym_unlines] = "unlines",
  [anon_sym_unlinesCrLf] = "unlinesCrLf",
  [anon_sym_split] = "split",
  [anon_sym_wsplit] = "wsplit",
  [anon_sym_tsplit] = "tsplit",
  [anon_sym_join] = "join",
  [anon_sym_trim] = "trim",
  [anon_sym_trimStart] = "trimStart",
  [anon_sym_trimEnd] = "trimEnd",
  [anon_sym_startsWith] = "startsWith",
  [anon_sym_endsWith] = "endsWith",
  [anon_sym_lower] = "lower",
  [anon_sym_upper] = "upper",
  [anon_sym_title] = "title",
  [anon_sym_leftPad] = "leftPad",
  [anon_sym_findReplace] = "findReplace",
  [anon_sym_in] = "in",
  [anon_sym_index] = "index",
  [anon_sym_lastIndexOf] = "lastIndexOf",
  [anon_sym_countSubStr] = "countSubStr",
  [anon_sym_parseJson] = "parseJson",
  [anon_sym_parseCsv] = "parseCsv",
  [anon_sym_parseHtml] = "parseHtml",
  [anon_sym_parseExcel] = "parseExcel",
  [anon_sym_readFile] = "readFile",
  [anon_sym_readFileBytes] = "readFileBytes",
  [anon_sym_readTsvFile] = "readTsvFile",
  [anon_sym_writeFile] = "writeFile",
  [anon_sym_appendFile] = "appendFile",
  [anon_sym_fileExists] = "fileExists",
  [anon_sym_isDir] = "isDir",
  [anon_sym_isFile] = "isFile",
  [anon_sym_fileSize] = "fileSize",
  [anon_sym_cp] = "cp",
  [anon_sym_mv] = "mv",
  [anon_sym_rm] = "rm",
  [anon_sym_rmf] = "rmf",
  [anon_sym_mkdir] = "mkdir",
  [anon_sym_mkdirp] = "mkdirp",
  [anon_sym_cd] = "cd",
  [anon_sym_pwd] = "pwd",
  [anon_sym_tempFile] = "tempFile",
  [anon_sym_tempFileExt] = "tempFileExt",
  [anon_sym_tempDir] = "tempDir",
  [anon_sym_lsDir] = "lsDir",
  [anon_sym_files] = "files",
  [anon_sym_dirs] = "dirs",
  [anon_sym_absPath] = "absPath",
  [anon_sym_dirname] = "dirname",
  [anon_sym_basename] = "basename",
  [anon_sym_ext] = "ext",
  [anon_sym_stem] = "stem",
  [anon_sym_isCmd] = "isCmd",
  [anon_sym_hardLink] = "hardLink",
  [anon_sym_sha256sum] = "sha256sum",
  [anon_sym_md5] = "md5",
  [anon_sym_now] = "now",
  [anon_sym_date] = "date",
  [anon_sym_year] = "year",
  [anon_sym_month] = "month",
  [anon_sym_day] = "day",
  [anon_sym_hour] = "hour",
  [anon_sym_minute] = "minute",
  [anon_sym_dateFmt] = "dateFmt",
  [anon_sym_isoDateFmt] = "isoDateFmt",
  [anon_sym_isoDateTimeFmt] = "isoDateTimeFmt",
  [anon_sym_isWeekend] = "isWeekend",
  [anon_sym_isWeekday] = "isWeekday",
  [anon_sym_dow] = "dow",
  [anon_sym_addDays] = "addDays",
  [anon_sym_toUnixTime] = "toUnixTime",
  [anon_sym_toUnixTimeMilli] = "toUnixTimeMilli",
  [anon_sym_toUnixTimeMicro] = "toUnixTimeMicro",
  [anon_sym_toUnixTimeNano] = "toUnixTimeNano",
  [anon_sym_fromUnixTime] = "fromUnixTime",
  [anon_sym_fromUnixTimeMilli] = "fromUnixTimeMilli",
  [anon_sym_fromUnixTimeMicro] = "fromUnixTimeMicro",
  [anon_sym_fromUnixTimeNano] = "fromUnixTimeNano",
  [anon_sym_toOleDate] = "toOleDate",
  [anon_sym_fromOleDate] = "fromOleDate",
  [anon_sym_utcToCst] = "utcToCst",
  [anon_sym_cstToUtc] = "cstToUtc",
  [anon_sym_reMatch] = "reMatch",
  [anon_sym_reFindAll] = "reFindAll",
  [anon_sym_reFindAllIndex] = "reFindAllIndex",
  [anon_sym_reReplace] = "reReplace",
  [anon_sym_reSplit] = "reSplit",
  [anon_sym_just] = "just",
  [anon_sym_none] = "none",
  [anon_sym_isNone] = "isNone",
  [anon_sym_maybe] = "maybe",
  [anon_sym_bind] = "bind",
  [anon_sym_psub] = "psub",
  [anon_sym_typeof] = "typeof",
  [anon_sym_runtime] = "runtime",
  [anon_sym_hostname] = "hostname",
  [anon_sym_httpGet] = "httpGet",
  [anon_sym_httpPost] = "httpPost",
  [anon_sym_urlEncode] = "urlEncode",
  [anon_sym_base64encode] = "base64encode",
  [anon_sym_base64decode] = "base64decode",
  [anon_sym_utf8Str] = "utf8Str",
  [anon_sym_utf8Bytes] = "utf8Bytes",
  [anon_sym_get] = "get",
  [anon_sym_getDef] = "getDef",
  [anon_sym_set] = "set",
  [anon_sym_setd] = "setd",
  [anon_sym_keys] = "keys",
  [anon_sym_values] = "values",
  [anon_sym_keyValues] = "keyValues",
  [anon_sym_all] = "all",
  [anon_sym_any] = "any",
  [anon_sym_cartesian] = "cartesian",
  [anon_sym_groupBy] = "groupBy",
  [anon_sym_listToDict] = "listToDict",
  [anon_sym_repeat] = "repeat",
  [anon_sym_seq] = "seq",
  [anon_sym_tab] = "tab",
  [anon_sym_select] = "select",
  [anon_sym_exclude] = "exclude",
  [anon_sym_derive] = "derive",
  [anon_sym_updateCol] = "updateCol",
  [anon_sym_gridValues] = "gridValues",
  [anon_sym_leftJoin] = "leftJoin",
  [anon_sym_outerJoin] = "outerJoin",
  [anon_sym_linearSearch] = "linearSearch",
  [anon_sym_linearSearchIndex] = "linearSearchIndex",
  [anon_sym_binPaths] = "binPaths",
  [anon_sym_wt] = "wt",
  [anon_sym_tt] = "tt",
  [anon_sym_ttFile] = "ttFile",
  [anon_sym_uw] = "uw",
  [anon_sym_tuw] = "tuw",
  [anon_sym_strCmp] = "strCmp",
  [anon_sym_floatCmp] = "floatCmp",
  [anon_sym_versionSortCmp] = "versionSortCmp",
  [anon_sym_id] = "id",
  [anon_sym_2id] = "2id",
  [anon_sym_3id] = "3id",
  [anon_sym_2unpack] = "2unpack",
  [anon_sym_2apply] = "2apply",
  [anon_sym_2each] = "2each",
  [anon_sym_2tuple] = "2tuple",
  [anon_sym_DOTs] = ".s",
  [anon_sym_DOTb] = ".b",
  [anon_sym_DOTdef] = ".def",
  [anon_sym_DOTenv] = ".env",
  [sym_string] = "string",
  [sym_format_string] = "format_string",
  [sym_single_quoted_string] = "single_quoted_string",
  [sym_path] = "path",
  [sym_datetime] = "datetime",
  [sym_float] = "float",
  [sym_integer] = "integer",
  [sym_env_store] = "env_store",
  [sym_env_check] = "env_check",
  [sym_env_retrieve] = "env_retrieve",
  [sym_positional] = "positional",
  [sym_var_retrieve] = "var_retrieve",
  [sym_var_store] = "var_store",
  [sym_slice_indexer] = "slice_indexer",
  [sym_indexer] = "indexer",
  [sym_end_indexer] = "end_indexer",
  [sym_start_indexer] = "start_indexer",
  [sym_match_arm_dup] = "match_arm_dup",
  [sym_prefix_quote] = "prefix_quote",
  [anon_sym_GT] = ">",
  [anon_sym_GT_GT] = ">>",
  [anon_sym_2_GT] = "2>",
  [anon_sym_2_GT_GT] = "2>>",
  [anon_sym_AMP_GT] = "&>",
  [anon_sym_AMP_GT_GT] = "&>>",
  [anon_sym_LT] = "<",
  [anon_sym_LT_GT] = "<>",
  [anon_sym_STAR] = "*",
  [anon_sym_STARb] = "*b",
  [anon_sym_CARET] = "^",
  [anon_sym_CARETb] = "^b",
  [anon_sym_SEMI] = ";",
  [anon_sym_BANG] = "!",
  [anon_sym_QMARK] = "\?",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_AMP] = "&",
  [anon_sym_PIPE] = "|",
  [anon_sym_COMMA] = ",",
  [anon_sym_COLON] = ":",
  [sym_source_file] = "source_file",
  [sym__word] = "_word",
  [sym_list] = "list",
  [sym_quotation] = "quotation",
  [sym_dict] = "dict",
  [sym_grid] = "grid",
  [sym_boolean] = "boolean",
  [sym_keyword] = "keyword",
  [sym_type_keyword] = "type_keyword",
  [sym_builtin] = "builtin",
  [sym_redirect_operator] = "redirect_operator",
  [sym_execute_operator] = "execute_operator",
  [sym_comparison_operator] = "comparison_operator",
  [sym_punctuation] = "punctuation",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK_PIPE] = anon_sym_LBRACK_PIPE,
  [anon_sym_PIPE_RBRACK] = anon_sym_PIPE_RBRACK,
  [sym_line_comment] = sym_line_comment,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [anon_sym_def] = anon_sym_def,
  [anon_sym_end] = anon_sym_end,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_iff] = anon_sym_iff,
  [anon_sym_else] = anon_sym_else,
  [anon_sym_else_STAR] = anon_sym_else_STAR,
  [anon_sym_STARif] = anon_sym_STARif,
  [anon_sym_loop] = anon_sym_loop,
  [anon_sym_match] = anon_sym_match,
  [anon_sym_break] = anon_sym_break,
  [anon_sym_continue] = anon_sym_continue,
  [anon_sym_soe] = anon_sym_soe,
  [anon_sym_not] = anon_sym_not,
  [anon_sym_and] = anon_sym_and,
  [anon_sym_or] = anon_sym_or,
  [anon_sym_read] = anon_sym_read,
  [anon_sym_str] = anon_sym_str,
  [anon_sym_as] = anon_sym_as,
  [anon_sym_type] = anon_sym_type,
  [anon_sym_try] = anon_sym_try,
  [anon_sym_fail] = anon_sym_fail,
  [anon_sym_pure] = anon_sym_pure,
  [anon_sym_VER] = anon_sym_VER,
  [anon_sym_x] = anon_sym_x,
  [anon_sym_int] = anon_sym_int,
  [anon_sym_float] = anon_sym_float,
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_dup] = anon_sym_dup,
  [anon_sym_swap] = anon_sym_swap,
  [anon_sym_drop] = anon_sym_drop,
  [anon_sym_over] = anon_sym_over,
  [anon_sym_pick] = anon_sym_pick,
  [anon_sym_rot] = anon_sym_rot,
  [anon_sym_DASHrot] = anon_sym_DASHrot,
  [anon_sym_nip] = anon_sym_nip,
  [anon_sym_w] = anon_sym_w,
  [anon_sym_wl] = anon_sym_wl,
  [anon_sym_we] = anon_sym_we,
  [anon_sym_wle] = anon_sym_wle,
  [anon_sym_len] = anon_sym_len,
  [anon_sym_args] = anon_sym_args,
  [anon_sym_glob] = anon_sym_glob,
  [anon_sym_toFloat] = anon_sym_toFloat,
  [anon_sym_toInt] = anon_sym_toInt,
  [anon_sym_toPath] = anon_sym_toPath,
  [anon_sym_toDt] = anon_sym_toDt,
  [anon_sym_toGrid] = anon_sym_toGrid,
  [anon_sym_toCsv] = anon_sym_toCsv,
  [anon_sym_toCsvCell] = anon_sym_toCsvCell,
  [anon_sym_exit] = anon_sym_exit,
  [anon_sym_prompt] = anon_sym_prompt,
  [anon_sym_stdin] = anon_sym_stdin,
  [anon_sym_COLON_COLON] = anon_sym_COLON_COLON,
  [anon_sym_foldl] = anon_sym_foldl,
  [anon_sym_map] = anon_sym_map,
  [anon_sym_each] = anon_sym_each,
  [anon_sym_eachWhile] = anon_sym_eachWhile,
  [anon_sym_filter] = anon_sym_filter,
  [anon_sym_append] = anon_sym_append,
  [anon_sym_extend] = anon_sym_extend,
  [anon_sym_concat] = anon_sym_concat,
  [anon_sym_reverse] = anon_sym_reverse,
  [anon_sym_sort] = anon_sym_sort,
  [anon_sym_sortV] = anon_sym_sortV,
  [anon_sym_sortBy] = anon_sym_sortBy,
  [anon_sym_sortByCmp] = anon_sym_sortByCmp,
  [anon_sym_uniq] = anon_sym_uniq,
  [anon_sym_zip] = anon_sym_zip,
  [anon_sym_enumerate] = anon_sym_enumerate,
  [anon_sym_enumerateN] = anon_sym_enumerateN,
  [anon_sym_chunk] = anon_sym_chunk,
  [anon_sym_pop] = anon_sym_pop,
  [anon_sym_take] = anon_sym_take,
  [anon_sym_takeWhile] = anon_sym_takeWhile,
  [anon_sym_skip] = anon_sym_skip,
  [anon_sym_dropWhile] = anon_sym_dropWhile,
  [anon_sym_nth] = anon_sym_nth,
  [anon_sym_insert] = anon_sym_insert,
  [anon_sym_setAt] = anon_sym_setAt,
  [anon_sym_del] = anon_sym_del,
  [anon_sym_sum] = anon_sym_sum,
  [anon_sym_max] = anon_sym_max,
  [anon_sym_max2] = anon_sym_max2,
  [anon_sym_min] = anon_sym_min,
  [anon_sym_min2] = anon_sym_min2,
  [anon_sym_abs] = anon_sym_abs,
  [anon_sym_inc] = anon_sym_inc,
  [anon_sym_mod] = anon_sym_mod,
  [anon_sym_floor] = anon_sym_floor,
  [anon_sym_ceil] = anon_sym_ceil,
  [anon_sym_round] = anon_sym_round,
  [anon_sym_lines] = anon_sym_lines,
  [anon_sym_unlines] = anon_sym_unlines,
  [anon_sym_unlinesCrLf] = anon_sym_unlinesCrLf,
  [anon_sym_split] = anon_sym_split,
  [anon_sym_wsplit] = anon_sym_wsplit,
  [anon_sym_tsplit] = anon_sym_tsplit,
  [anon_sym_join] = anon_sym_join,
  [anon_sym_trim] = anon_sym_trim,
  [anon_sym_trimStart] = anon_sym_trimStart,
  [anon_sym_trimEnd] = anon_sym_trimEnd,
  [anon_sym_startsWith] = anon_sym_startsWith,
  [anon_sym_endsWith] = anon_sym_endsWith,
  [anon_sym_lower] = anon_sym_lower,
  [anon_sym_upper] = anon_sym_upper,
  [anon_sym_title] = anon_sym_title,
  [anon_sym_leftPad] = anon_sym_leftPad,
  [anon_sym_findReplace] = anon_sym_findReplace,
  [anon_sym_in] = anon_sym_in,
  [anon_sym_index] = anon_sym_index,
  [anon_sym_lastIndexOf] = anon_sym_lastIndexOf,
  [anon_sym_countSubStr] = anon_sym_countSubStr,
  [anon_sym_parseJson] = anon_sym_parseJson,
  [anon_sym_parseCsv] = anon_sym_parseCsv,
  [anon_sym_parseHtml] = anon_sym_parseHtml,
  [anon_sym_parseExcel] = anon_sym_parseExcel,
  [anon_sym_readFile] = anon_sym_readFile,
  [anon_sym_readFileBytes] = anon_sym_readFileBytes,
  [anon_sym_readTsvFile] = anon_sym_readTsvFile,
  [anon_sym_writeFile] = anon_sym_writeFile,
  [anon_sym_appendFile] = anon_sym_appendFile,
  [anon_sym_fileExists] = anon_sym_fileExists,
  [anon_sym_isDir] = anon_sym_isDir,
  [anon_sym_isFile] = anon_sym_isFile,
  [anon_sym_fileSize] = anon_sym_fileSize,
  [anon_sym_cp] = anon_sym_cp,
  [anon_sym_mv] = anon_sym_mv,
  [anon_sym_rm] = anon_sym_rm,
  [anon_sym_rmf] = anon_sym_rmf,
  [anon_sym_mkdir] = anon_sym_mkdir,
  [anon_sym_mkdirp] = anon_sym_mkdirp,
  [anon_sym_cd] = anon_sym_cd,
  [anon_sym_pwd] = anon_sym_pwd,
  [anon_sym_tempFile] = anon_sym_tempFile,
  [anon_sym_tempFileExt] = anon_sym_tempFileExt,
  [anon_sym_tempDir] = anon_sym_tempDir,
  [anon_sym_lsDir] = anon_sym_lsDir,
  [anon_sym_files] = anon_sym_files,
  [anon_sym_dirs] = anon_sym_dirs,
  [anon_sym_absPath] = anon_sym_absPath,
  [anon_sym_dirname] = anon_sym_dirname,
  [anon_sym_basename] = anon_sym_basename,
  [anon_sym_ext] = anon_sym_ext,
  [anon_sym_stem] = anon_sym_stem,
  [anon_sym_isCmd] = anon_sym_isCmd,
  [anon_sym_hardLink] = anon_sym_hardLink,
  [anon_sym_sha256sum] = anon_sym_sha256sum,
  [anon_sym_md5] = anon_sym_md5,
  [anon_sym_now] = anon_sym_now,
  [anon_sym_date] = anon_sym_date,
  [anon_sym_year] = anon_sym_year,
  [anon_sym_month] = anon_sym_month,
  [anon_sym_day] = anon_sym_day,
  [anon_sym_hour] = anon_sym_hour,
  [anon_sym_minute] = anon_sym_minute,
  [anon_sym_dateFmt] = anon_sym_dateFmt,
  [anon_sym_isoDateFmt] = anon_sym_isoDateFmt,
  [anon_sym_isoDateTimeFmt] = anon_sym_isoDateTimeFmt,
  [anon_sym_isWeekend] = anon_sym_isWeekend,
  [anon_sym_isWeekday] = anon_sym_isWeekday,
  [anon_sym_dow] = anon_sym_dow,
  [anon_sym_addDays] = anon_sym_addDays,
  [anon_sym_toUnixTime] = anon_sym_toUnixTime,
  [anon_sym_toUnixTimeMilli] = anon_sym_toUnixTimeMilli,
  [anon_sym_toUnixTimeMicro] = anon_sym_toUnixTimeMicro,
  [anon_sym_toUnixTimeNano] = anon_sym_toUnixTimeNano,
  [anon_sym_fromUnixTime] = anon_sym_fromUnixTime,
  [anon_sym_fromUnixTimeMilli] = anon_sym_fromUnixTimeMilli,
  [anon_sym_fromUnixTimeMicro] = anon_sym_fromUnixTimeMicro,
  [anon_sym_fromUnixTimeNano] = anon_sym_fromUnixTimeNano,
  [anon_sym_toOleDate] = anon_sym_toOleDate,
  [anon_sym_fromOleDate] = anon_sym_fromOleDate,
  [anon_sym_utcToCst] = anon_sym_utcToCst,
  [anon_sym_cstToUtc] = anon_sym_cstToUtc,
  [anon_sym_reMatch] = anon_sym_reMatch,
  [anon_sym_reFindAll] = anon_sym_reFindAll,
  [anon_sym_reFindAllIndex] = anon_sym_reFindAllIndex,
  [anon_sym_reReplace] = anon_sym_reReplace,
  [anon_sym_reSplit] = anon_sym_reSplit,
  [anon_sym_just] = anon_sym_just,
  [anon_sym_none] = anon_sym_none,
  [anon_sym_isNone] = anon_sym_isNone,
  [anon_sym_maybe] = anon_sym_maybe,
  [anon_sym_bind] = anon_sym_bind,
  [anon_sym_psub] = anon_sym_psub,
  [anon_sym_typeof] = anon_sym_typeof,
  [anon_sym_runtime] = anon_sym_runtime,
  [anon_sym_hostname] = anon_sym_hostname,
  [anon_sym_httpGet] = anon_sym_httpGet,
  [anon_sym_httpPost] = anon_sym_httpPost,
  [anon_sym_urlEncode] = anon_sym_urlEncode,
  [anon_sym_base64encode] = anon_sym_base64encode,
  [anon_sym_base64decode] = anon_sym_base64decode,
  [anon_sym_utf8Str] = anon_sym_utf8Str,
  [anon_sym_utf8Bytes] = anon_sym_utf8Bytes,
  [anon_sym_get] = anon_sym_get,
  [anon_sym_getDef] = anon_sym_getDef,
  [anon_sym_set] = anon_sym_set,
  [anon_sym_setd] = anon_sym_setd,
  [anon_sym_keys] = anon_sym_keys,
  [anon_sym_values] = anon_sym_values,
  [anon_sym_keyValues] = anon_sym_keyValues,
  [anon_sym_all] = anon_sym_all,
  [anon_sym_any] = anon_sym_any,
  [anon_sym_cartesian] = anon_sym_cartesian,
  [anon_sym_groupBy] = anon_sym_groupBy,
  [anon_sym_listToDict] = anon_sym_listToDict,
  [anon_sym_repeat] = anon_sym_repeat,
  [anon_sym_seq] = anon_sym_seq,
  [anon_sym_tab] = anon_sym_tab,
  [anon_sym_select] = anon_sym_select,
  [anon_sym_exclude] = anon_sym_exclude,
  [anon_sym_derive] = anon_sym_derive,
  [anon_sym_updateCol] = anon_sym_updateCol,
  [anon_sym_gridValues] = anon_sym_gridValues,
  [anon_sym_leftJoin] = anon_sym_leftJoin,
  [anon_sym_outerJoin] = anon_sym_outerJoin,
  [anon_sym_linearSearch] = anon_sym_linearSearch,
  [anon_sym_linearSearchIndex] = anon_sym_linearSearchIndex,
  [anon_sym_binPaths] = anon_sym_binPaths,
  [anon_sym_wt] = anon_sym_wt,
  [anon_sym_tt] = anon_sym_tt,
  [anon_sym_ttFile] = anon_sym_ttFile,
  [anon_sym_uw] = anon_sym_uw,
  [anon_sym_tuw] = anon_sym_tuw,
  [anon_sym_strCmp] = anon_sym_strCmp,
  [anon_sym_floatCmp] = anon_sym_floatCmp,
  [anon_sym_versionSortCmp] = anon_sym_versionSortCmp,
  [anon_sym_id] = anon_sym_id,
  [anon_sym_2id] = anon_sym_2id,
  [anon_sym_3id] = anon_sym_3id,
  [anon_sym_2unpack] = anon_sym_2unpack,
  [anon_sym_2apply] = anon_sym_2apply,
  [anon_sym_2each] = anon_sym_2each,
  [anon_sym_2tuple] = anon_sym_2tuple,
  [anon_sym_DOTs] = anon_sym_DOTs,
  [anon_sym_DOTb] = anon_sym_DOTb,
  [anon_sym_DOTdef] = anon_sym_DOTdef,
  [anon_sym_DOTenv] = anon_sym_DOTenv,
  [sym_string] = sym_string,
  [sym_format_string] = sym_format_string,
  [sym_single_quoted_string] = sym_single_quoted_string,
  [sym_path] = sym_path,
  [sym_datetime] = sym_datetime,
  [sym_float] = sym_float,
  [sym_integer] = sym_integer,
  [sym_env_store] = sym_env_store,
  [sym_env_check] = sym_env_check,
  [sym_env_retrieve] = sym_env_retrieve,
  [sym_positional] = sym_positional,
  [sym_var_retrieve] = sym_var_retrieve,
  [sym_var_store] = sym_var_store,
  [sym_slice_indexer] = sym_slice_indexer,
  [sym_indexer] = sym_indexer,
  [sym_end_indexer] = sym_end_indexer,
  [sym_start_indexer] = sym_start_indexer,
  [sym_match_arm_dup] = sym_match_arm_dup,
  [sym_prefix_quote] = sym_prefix_quote,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_GT_GT] = anon_sym_GT_GT,
  [anon_sym_2_GT] = anon_sym_2_GT,
  [anon_sym_2_GT_GT] = anon_sym_2_GT_GT,
  [anon_sym_AMP_GT] = anon_sym_AMP_GT,
  [anon_sym_AMP_GT_GT] = anon_sym_AMP_GT_GT,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_LT_GT] = anon_sym_LT_GT,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_STARb] = anon_sym_STARb,
  [anon_sym_CARET] = anon_sym_CARET,
  [anon_sym_CARETb] = anon_sym_CARETb,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_BANG] = anon_sym_BANG,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_AMP] = anon_sym_AMP,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_COLON] = anon_sym_COLON,
  [sym_source_file] = sym_source_file,
  [sym__word] = sym__word,
  [sym_list] = sym_list,
  [sym_quotation] = sym_quotation,
  [sym_dict] = sym_dict,
  [sym_grid] = sym_grid,
  [sym_boolean] = sym_boolean,
  [sym_keyword] = sym_keyword,
  [sym_type_keyword] = sym_type_keyword,
  [sym_builtin] = sym_builtin,
  [sym_redirect_operator] = sym_redirect_operator,
  [sym_execute_operator] = sym_execute_operator,
  [sym_comparison_operator] = sym_comparison_operator,
  [sym_punctuation] = sym_punctuation,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_line_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_def] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_iff] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_else] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_else_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STARif] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_loop] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_match] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_break] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_continue] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_soe] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_not] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_and] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_or] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_read] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_str] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_as] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_type] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_try] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fail] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pure] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_VER] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_x] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dup] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_swap] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_drop] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_over] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pick] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rot] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASHrot] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nip] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_w] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wl] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_we] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wle] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_len] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_args] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_glob] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toFloat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toInt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toPath] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toDt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toGrid] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toCsv] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toCsvCell] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_exit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_prompt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_stdin] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_foldl] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_map] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_each] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_eachWhile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_filter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_append] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_extend] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_concat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reverse] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sort] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sortV] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sortBy] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sortByCmp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uniq] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_zip] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_enumerate] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_enumerateN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_chunk] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pop] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_take] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_takeWhile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_skip] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dropWhile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nth] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_insert] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_setAt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_del] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sum] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_max] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_max2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_min] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_min2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_abs] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inc] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_mod] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_floor] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ceil] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_round] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_lines] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_unlines] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_unlinesCrLf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_split] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wsplit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tsplit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_join] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_trim] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_trimStart] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_trimEnd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_startsWith] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endsWith] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_lower] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_upper] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_title] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_leftPad] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_findReplace] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_in] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_index] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_lastIndexOf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_countSubStr] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_parseJson] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_parseCsv] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_parseHtml] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_parseExcel] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_readFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_readFileBytes] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_readTsvFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_writeFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_appendFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fileExists] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isDir] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fileSize] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_mv] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rm] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rmf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_mkdir] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_mkdirp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pwd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tempFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tempFileExt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tempDir] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_lsDir] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_files] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dirs] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_absPath] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dirname] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_basename] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ext] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_stem] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isCmd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_hardLink] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_sha256sum] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_md5] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_now] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_date] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_year] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_month] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_day] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_hour] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_minute] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dateFmt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isoDateFmt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isoDateTimeFmt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isWeekend] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isWeekday] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dow] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_addDays] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toUnixTime] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toUnixTimeMilli] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toUnixTimeMicro] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toUnixTimeNano] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fromUnixTime] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fromUnixTimeMilli] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fromUnixTimeMicro] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fromUnixTimeNano] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_toOleDate] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fromOleDate] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_utcToCst] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cstToUtc] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reMatch] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reFindAll] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reFindAllIndex] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reReplace] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_reSplit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_just] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_none] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_isNone] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_maybe] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bind] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_psub] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_typeof] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_runtime] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_hostname] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_httpGet] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_httpPost] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_urlEncode] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_base64encode] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_base64decode] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_utf8Str] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_utf8Bytes] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_get] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_getDef] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_set] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_setd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_keys] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_values] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_keyValues] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_all] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_any] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_cartesian] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_groupBy] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_listToDict] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_repeat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_seq] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tab] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_select] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_exclude] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_derive] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_updateCol] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_gridValues] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_leftJoin] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_outerJoin] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_linearSearch] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_linearSearchIndex] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_binPaths] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_wt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ttFile] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tuw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_strCmp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_floatCmp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_versionSortCmp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_id] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2id] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_3id] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2unpack] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2apply] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2each] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2tuple] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOTs] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOTb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOTdef] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOTenv] = {
    .visible = true,
    .named = false,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_format_string] = {
    .visible = true,
    .named = true,
  },
  [sym_single_quoted_string] = {
    .visible = true,
    .named = true,
  },
  [sym_path] = {
    .visible = true,
    .named = true,
  },
  [sym_datetime] = {
    .visible = true,
    .named = true,
  },
  [sym_float] = {
    .visible = true,
    .named = true,
  },
  [sym_integer] = {
    .visible = true,
    .named = true,
  },
  [sym_env_store] = {
    .visible = true,
    .named = true,
  },
  [sym_env_check] = {
    .visible = true,
    .named = true,
  },
  [sym_env_retrieve] = {
    .visible = true,
    .named = true,
  },
  [sym_positional] = {
    .visible = true,
    .named = true,
  },
  [sym_var_retrieve] = {
    .visible = true,
    .named = true,
  },
  [sym_var_store] = {
    .visible = true,
    .named = true,
  },
  [sym_slice_indexer] = {
    .visible = true,
    .named = true,
  },
  [sym_indexer] = {
    .visible = true,
    .named = true,
  },
  [sym_end_indexer] = {
    .visible = true,
    .named = true,
  },
  [sym_start_indexer] = {
    .visible = true,
    .named = true,
  },
  [sym_match_arm_dup] = {
    .visible = true,
    .named = true,
  },
  [sym_prefix_quote] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_2_GT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_GT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STARb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CARET] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CARETb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__word] = {
    .visible = false,
    .named = true,
  },
  [sym_list] = {
    .visible = true,
    .named = true,
  },
  [sym_quotation] = {
    .visible = true,
    .named = true,
  },
  [sym_dict] = {
    .visible = true,
    .named = true,
  },
  [sym_grid] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean] = {
    .visible = true,
    .named = true,
  },
  [sym_keyword] = {
    .visible = true,
    .named = true,
  },
  [sym_type_keyword] = {
    .visible = true,
    .named = true,
  },
  [sym_builtin] = {
    .visible = true,
    .named = true,
  },
  [sym_redirect_operator] = {
    .visible = true,
    .named = true,
  },
  [sym_execute_operator] = {
    .visible = true,
    .named = true,
  },
  [sym_comparison_operator] = {
    .visible = true,
    .named = true,
  },
  [sym_punctuation] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 2,
  [13] = 10,
  [14] = 11,
  [15] = 3,
  [16] = 4,
  [17] = 6,
  [18] = 7,
  [19] = 8,
  [20] = 9,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 31,
  [38] = 33,
  [39] = 34,
  [40] = 36,
  [41] = 23,
  [42] = 24,
  [43] = 27,
  [44] = 32,
  [45] = 30,
  [46] = 25,
  [47] = 21,
  [48] = 28,
  [49] = 35,
  [50] = 22,
  [51] = 29,
  [52] = 26,
  [53] = 53,
};

static TSCharacterRange sym_var_retrieve_character_set_1[] = {
  {0, 0x08}, {0x0e, 0x1f}, {'%', '%'}, {'+', '+'}, {'-', '9'}, {'=', '='}, {'A', 'Z'}, {'\\', '\\'},
  {'_', '_'}, {'a', 'z'}, {'~', 0x10ffff},
};

static TSCharacterRange sym_var_store_character_set_1[] = {
  {0, 0x08}, {0x0e, 0x1f}, {'!', '!'}, {'%', '%'}, {'+', '+'}, {'-', '9'}, {'=', '='}, {'A', 'Z'},
  {'\\', '\\'}, {'_', '_'}, {'a', 'z'}, {'~', 0x10ffff},
};

static TSCharacterRange sym_identifier_character_set_1[] = {
  {0, 0x08}, {0x0e, 0x1f}, {'%', '%'}, {'+', '+'}, {'-', '/'}, {'=', '='}, {'A', 'Z'}, {'\\', '\\'},
  {'_', '_'}, {'a', 'z'}, {'~', 0x10ffff},
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(24);
      ADVANCE_MAP(
        '!', 79,
        '"', 1,
        '#', 33,
        '$', 3,
        '&', 84,
        '\'', 4,
        '(', 27,
        ')', 28,
        '*', 74,
        ',', 87,
        '-', 99,
        '.', 94,
        '2', 54,
        '3', 54,
        ':', 88,
        ';', 78,
        '<', 72,
        '>', 68,
        '?', 80,
        '@', 20,
        '[', 25,
        ']', 26,
        '^', 76,
        '`', 6,
        'e', 91,
        '{', 29,
        '|', 86,
        '}', 30,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(54);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('_' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      if (lookahead != 0) ADVANCE(102);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(42);
      if (lookahead == '\\') ADVANCE(21);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '\\') ADVANCE(22);
      if (lookahead != 0) ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(60);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(59);
      END_STATE();
    case 4:
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead != 0) ADVANCE(4);
      END_STATE();
    case 5:
      if (lookahead == '-') ADVANCE(15);
      END_STATE();
    case 6:
      if (lookahead == '`') ADVANCE(45);
      if (lookahead != 0) ADVANCE(6);
      END_STATE();
    case 7:
      if (lookahead == 'f') ADVANCE(35);
      END_STATE();
    case 8:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 9:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(63);
      END_STATE();
    case 10:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(5);
      END_STATE();
    case 11:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(49);
      END_STATE();
    case 12:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 13:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 14:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
      END_STATE();
    case 15:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(11);
      END_STATE();
    case 16:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(13);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(18);
      END_STATE();
    case 20:
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(61);
      END_STATE();
    case 21:
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(1);
      END_STATE();
    case 22:
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(2);
      END_STATE();
    case 23:
      if (eof) ADVANCE(24);
      ADVANCE_MAP(
        '!', 79,
        '"', 1,
        '#', 33,
        '$', 3,
        '&', 84,
        '\'', 4,
        '(', 27,
        ')', 28,
        '*', 74,
        ',', 87,
        '-', 99,
        '.', 94,
        '2', 54,
        '3', 54,
        ':', 88,
        ';', 78,
        '<', 72,
        '>', 68,
        '?', 80,
        '@', 20,
        '[', 25,
        ']', 26,
        '^', 76,
        '`', 6,
        'e', 91,
        '{', 29,
        '|', 85,
        '}', 30,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(54);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('_' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      if (lookahead != 0) ADVANCE(102);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '|') ADVANCE(31);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_LBRACK_PIPE);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_PIPE_RBRACK);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(33);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_else_STAR);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_STARif);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_DASHrot);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_COLON_COLON);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_DOTs);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_DOTb);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_DOTdef);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_DOTenv);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_format_string);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_single_quoted_string);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_path);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_datetime);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_datetime);
      if (lookahead == ':') ADVANCE(17);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_datetime);
      if (lookahead == ':') ADVANCE(19);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_datetime);
      if (lookahead == 'T') ADVANCE(16);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_float);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '-') ADVANCE(14);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == ':') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(55);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == ':') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(51);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == ':') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(52);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == ':') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(53);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == ':') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(55);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_integer);
      if (lookahead == '.') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_env_store);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_env_check);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_env_retrieve);
      if (lookahead == '!') ADVANCE(57);
      if (lookahead == '?') ADVANCE(58);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(59);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_positional);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(60);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_var_retrieve);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(61);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_var_store);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_slice_indexer);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(63);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_indexer);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_end_indexer);
      if (lookahead == ':') ADVANCE(64);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_start_indexer);
      if (lookahead == '-') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(63);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_match_arm_dup);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(83);
      if (lookahead == '>') ADVANCE(69);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_AMP_GT);
      if (lookahead == '>') ADVANCE(71);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_AMP_GT_GT);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(82);
      if (lookahead == '>') ADVANCE(73);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_LT_GT);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_STAR);
      if (lookahead == 'b') ADVANCE(75);
      if (lookahead == 'i') ADVANCE(7);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_STARb);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_CARET);
      if (lookahead == 'b') ADVANCE(77);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_CARETb);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_BANG);
      if (lookahead == '=') ADVANCE(81);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_AMP);
      if (lookahead == '>') ADVANCE(70);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_PIPE);
      if (lookahead == ']') ADVANCE(32);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == '-') ADVANCE(8);
      if (lookahead == ':') ADVANCE(37);
      if (lookahead == '>') ADVANCE(67);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '!') ADVANCE(62);
      if (lookahead == '*') ADVANCE(34);
      if ((!eof && set_contains(sym_var_store_character_set_1, 12, lookahead))) ADVANCE(93);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '!') ADVANCE(62);
      if (lookahead == 'e') ADVANCE(89);
      if ((!eof && set_contains(sym_var_store_character_set_1, 12, lookahead))) ADVANCE(93);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '!') ADVANCE(62);
      if (lookahead == 'l') ADVANCE(92);
      if ((!eof && set_contains(sym_var_store_character_set_1, 12, lookahead))) ADVANCE(93);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '!') ADVANCE(62);
      if (lookahead == 's') ADVANCE(90);
      if ((!eof && set_contains(sym_var_store_character_set_1, 12, lookahead))) ADVANCE(93);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '!') ADVANCE(62);
      if ((!eof && set_contains(sym_var_store_character_set_1, 12, lookahead))) ADVANCE(93);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(39);
      if (lookahead == 'd') ADVANCE(95);
      if (lookahead == 'e') ADVANCE(97);
      if (lookahead == 's') ADVANCE(38);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(96);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(40);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(101);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(100);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(98);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(56);
      if ((!eof && set_contains(sym_identifier_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(36);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(41);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_identifier);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(102);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ADVANCE_MAP(
        'V', 1,
        'a', 2,
        'b', 3,
        'c', 4,
        'd', 5,
        'e', 6,
        'f', 7,
        'g', 8,
        'h', 9,
        'i', 10,
        'j', 11,
        'k', 12,
        'l', 13,
        'm', 14,
        'n', 15,
        'o', 16,
        'p', 17,
        'r', 18,
        's', 19,
        't', 20,
        'u', 21,
        'v', 22,
        'w', 23,
        'x', 24,
        'y', 25,
        'z', 26,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          lookahead == 'q') ADVANCE(27);
      END_STATE();
    case 1:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'E') ADVANCE(29);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '.', 28,
        'b', 30,
        'd', 31,
        'l', 32,
        'n', 33,
        'p', 34,
        'r', 35,
        's', 36,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 3:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(37);
      if (lookahead == 'i') ADVANCE(38);
      if (lookahead == 'o') ADVANCE(39);
      if (lookahead == 'r') ADVANCE(40);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 4:
      ADVANCE_MAP(
        '.', 28,
        'a', 41,
        'd', 42,
        'e', 43,
        'h', 44,
        'o', 45,
        'p', 46,
        's', 47,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 5:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(48);
      if (lookahead == 'e') ADVANCE(49);
      if (lookahead == 'i') ADVANCE(50);
      if (lookahead == 'o') ADVANCE(51);
      if (lookahead == 'r') ADVANCE(52);
      if (lookahead == 'u') ADVANCE(53);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 6:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(54);
      if (lookahead == 'l') ADVANCE(55);
      if (lookahead == 'n') ADVANCE(56);
      if (lookahead == 'x') ADVANCE(57);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 7:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(58);
      if (lookahead == 'i') ADVANCE(59);
      if (lookahead == 'l') ADVANCE(60);
      if (lookahead == 'o') ADVANCE(61);
      if (lookahead == 'r') ADVANCE(62);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 8:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(63);
      if (lookahead == 'l') ADVANCE(64);
      if (lookahead == 'r') ADVANCE(65);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 9:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(66);
      if (lookahead == 'o') ADVANCE(67);
      if (lookahead == 't') ADVANCE(68);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 10:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(69);
      if (lookahead == 'f') ADVANCE(70);
      if (lookahead == 'n') ADVANCE(71);
      if (lookahead == 's') ADVANCE(72);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 11:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(73);
      if (lookahead == 'u') ADVANCE(74);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 12:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(75);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 13:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(76);
      if (lookahead == 'e') ADVANCE(77);
      if (lookahead == 'i') ADVANCE(78);
      if (lookahead == 'o') ADVANCE(79);
      if (lookahead == 's') ADVANCE(80);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 14:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(81);
      if (lookahead == 'd') ADVANCE(82);
      if (lookahead == 'i') ADVANCE(83);
      if (lookahead == 'k') ADVANCE(84);
      if (lookahead == 'o') ADVANCE(85);
      if (lookahead == 'v') ADVANCE(86);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 15:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(87);
      if (lookahead == 'o') ADVANCE(88);
      if (lookahead == 't') ADVANCE(89);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 16:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(90);
      if (lookahead == 'u') ADVANCE(91);
      if (lookahead == 'v') ADVANCE(92);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 17:
      ADVANCE_MAP(
        '.', 28,
        'a', 93,
        'i', 94,
        'o', 95,
        'r', 96,
        's', 97,
        'u', 98,
        'w', 99,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 18:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(100);
      if (lookahead == 'm') ADVANCE(101);
      if (lookahead == 'o') ADVANCE(102);
      if (lookahead == 'u') ADVANCE(103);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 19:
      ADVANCE_MAP(
        '.', 28,
        'e', 104,
        'h', 105,
        'k', 106,
        'o', 107,
        'p', 108,
        't', 109,
        'u', 110,
        'w', 111,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 20:
      ADVANCE_MAP(
        '.', 28,
        'a', 112,
        'e', 113,
        'i', 114,
        'o', 115,
        'r', 116,
        's', 117,
        't', 118,
        'u', 119,
        'y', 120,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 21:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(121);
      if (lookahead == 'p') ADVANCE(122);
      if (lookahead == 'r') ADVANCE(123);
      if (lookahead == 't') ADVANCE(124);
      if (lookahead == 'w') ADVANCE(125);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 22:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(126);
      if (lookahead == 'e') ADVANCE(127);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_w);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(128);
      if (lookahead == 'l') ADVANCE(129);
      if (lookahead == 'r') ADVANCE(130);
      if (lookahead == 's') ADVANCE(131);
      if (lookahead == 't') ADVANCE(132);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_x);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 25:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(133);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 26:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(134);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 27:
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(sym_prefix_quote);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 29:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'R') ADVANCE(135);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 30:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(136);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 31:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(137);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 32:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(138);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 33:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(139);
      if (lookahead == 'y') ADVANCE(140);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 34:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(141);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 35:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'g') ADVANCE(142);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_as);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 37:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(143);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 38:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(144);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 39:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(145);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 40:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(146);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 41:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(147);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_cd);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 43:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(148);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 44:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(149);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 45:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(150);
      if (lookahead == 'u') ADVANCE(151);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_cp);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 47:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(152);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 48:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(153);
      if (lookahead == 'y') ADVANCE(154);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 49:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(155);
      if (lookahead == 'l') ADVANCE(156);
      if (lookahead == 'r') ADVANCE(157);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 50:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(158);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 51:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'w') ADVANCE(159);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 52:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(160);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 53:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(161);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 54:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(162);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 55:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(163);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 56:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(164);
      if (lookahead == 'u') ADVANCE(165);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 57:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(166);
      if (lookahead == 'i') ADVANCE(167);
      if (lookahead == 't') ADVANCE(168);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 58:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(169);
      if (lookahead == 'l') ADVANCE(170);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 59:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(171);
      if (lookahead == 'n') ADVANCE(172);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 60:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(173);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 61:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(174);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 62:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(175);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 63:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(176);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 64:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(177);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 65:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(178);
      if (lookahead == 'o') ADVANCE(179);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 66:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(180);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 67:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(181);
      if (lookahead == 'u') ADVANCE(182);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 68:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(183);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_id);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_if);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(184);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_in);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(185);
      if (lookahead == 'd') ADVANCE(186);
      if (lookahead == 's') ADVANCE(187);
      if (lookahead == 't') ADVANCE(188);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 72:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(189);
      if (lookahead == 'D') ADVANCE(190);
      if (lookahead == 'F') ADVANCE(191);
      if (lookahead == 'N') ADVANCE(192);
      if (lookahead == 'W') ADVANCE(193);
      if (lookahead == 'o') ADVANCE(194);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 73:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(195);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 74:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(196);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 75:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(197);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 76:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(198);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 77:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(199);
      if (lookahead == 'n') ADVANCE(200);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 78:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(201);
      if (lookahead == 's') ADVANCE(202);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 79:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(203);
      if (lookahead == 'w') ADVANCE(204);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 80:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(205);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 81:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(206);
      if (lookahead == 't') ADVANCE(207);
      if (lookahead == 'x') ADVANCE(208);
      if (lookahead == 'y') ADVANCE(209);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 82:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '5') ADVANCE(210);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 83:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(211);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 84:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(212);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 85:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(213);
      if (lookahead == 'n') ADVANCE(214);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_mv);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 87:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(215);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 88:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(216);
      if (lookahead == 't') ADVANCE(217);
      if (lookahead == 'w') ADVANCE(218);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 89:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(219);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_or);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 91:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(220);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 92:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(221);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 93:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(222);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 94:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(223);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 95:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(224);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 96:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(225);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 97:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(226);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 98:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(227);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 99:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(228);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 100:
      ADVANCE_MAP(
        '.', 28,
        'F', 229,
        'M', 230,
        'R', 231,
        'S', 232,
        'a', 233,
        'p', 234,
        'v', 235,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_rm);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(236);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 102:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(237);
      if (lookahead == 'u') ADVANCE(238);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 103:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(239);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 104:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(240);
      if (lookahead == 'q') ADVANCE(241);
      if (lookahead == 't') ADVANCE(242);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 105:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(243);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 106:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(244);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 107:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(245);
      if (lookahead == 'r') ADVANCE(246);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 108:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(247);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 109:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(248);
      if (lookahead == 'd') ADVANCE(249);
      if (lookahead == 'e') ADVANCE(250);
      if (lookahead == 'r') ADVANCE(251);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 110:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(252);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 111:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(253);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 112:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'b') ADVANCE(254);
      if (lookahead == 'k') ADVANCE(255);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 113:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(256);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 114:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(257);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 115:
      ADVANCE_MAP(
        '.', 28,
        'C', 258,
        'D', 259,
        'F', 260,
        'G', 261,
        'I', 262,
        'O', 263,
        'P', 264,
        'U', 265,
      );
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 116:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(266);
      if (lookahead == 'u') ADVANCE(267);
      if (lookahead == 'y') ADVANCE(268);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 117:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(269);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_tt);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(270);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 119:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'w') ADVANCE(271);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 120:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(272);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 121:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(273);
      if (lookahead == 'l') ADVANCE(274);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 122:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(275);
      if (lookahead == 'p') ADVANCE(276);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 123:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(277);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 124:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(278);
      if (lookahead == 'f') ADVANCE(279);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_uw);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 126:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(280);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 127:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(281);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_we);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_wl);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(282);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 130:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(283);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 131:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(284);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_wt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 133:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(285);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 134:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(286);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(anon_sym_VER);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(anon_sym_abs);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'P') ADVANCE(287);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 137:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(288);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(anon_sym_all);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(anon_sym_and);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(anon_sym_any);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 141:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(289);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 142:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(290);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 143:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(291);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 144:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'P') ADVANCE(292);
      if (lookahead == 'd') ADVANCE(293);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 145:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(294);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 146:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(295);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 147:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(296);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 148:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(297);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 149:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(298);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 150:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(299);
      if (lookahead == 't') ADVANCE(300);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 151:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(301);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 152:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'T') ADVANCE(302);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 153:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(303);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(anon_sym_day);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(anon_sym_def);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(anon_sym_del);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 157:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(304);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 158:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(305);
      if (lookahead == 's') ADVANCE(306);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(anon_sym_dow);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 160:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(307);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(anon_sym_dup);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 162:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(308);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 163:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(309);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(anon_sym_end);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(310);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 165:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(311);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 166:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(312);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 167:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(313);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(anon_sym_ext);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(314);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 169:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(315);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 170:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(316);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 171:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(317);
      if (lookahead == 't') ADVANCE(318);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 172:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(319);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 173:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(320);
      if (lookahead == 'o') ADVANCE(321);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 174:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(322);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 175:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(323);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(anon_sym_get);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(324);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 177:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'b') ADVANCE(325);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 178:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(326);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 179:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(327);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 180:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(328);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 181:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(329);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 182:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(330);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 183:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(331);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(anon_sym_iff);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_inc);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 186:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(332);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 187:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(333);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(anon_sym_int);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 189:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(334);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 190:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(335);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 191:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(336);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 192:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(337);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 193:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(338);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 194:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(339);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 195:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(340);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 196:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(341);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 197:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'V') ADVANCE(342);
      if (lookahead == 's') ADVANCE(343);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 198:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(344);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 199:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(345);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(anon_sym_len);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 201:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(346);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 202:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(347);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 203:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(348);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 204:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(349);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 205:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(350);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_map);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 207:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(351);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_max);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '2') ADVANCE(352);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 209:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'b') ADVANCE(353);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_md5);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_min);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '2') ADVANCE(354);
      if (lookahead == 'u') ADVANCE(355);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 212:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(356);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_mod);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 214:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(357);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_nip);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 216:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(358);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_not);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_now);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_nth);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 220:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(359);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 221:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(360);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 222:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(361);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 223:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'k') ADVANCE(362);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(anon_sym_pop);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 225:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(363);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 226:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'b') ADVANCE(364);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 227:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(365);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(anon_sym_pwd);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 229:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(366);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 230:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(367);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 231:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(368);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 232:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(369);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 233:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(370);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 234:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(371);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 235:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(372);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(anon_sym_rmf);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(anon_sym_rot);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 238:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(373);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 239:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(374);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 240:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(375);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_seq);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_set);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'A') ADVANCE(376);
      if (lookahead == 'd') ADVANCE(377);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 243:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '2') ADVANCE(378);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 244:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(379);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_soe);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 246:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(380);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 247:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(381);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 248:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(382);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 249:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(383);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 250:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(384);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_str);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(385);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_sum);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 253:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(386);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(anon_sym_tab);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 255:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(387);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 256:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(388);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 257:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(389);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 258:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(390);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 259:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(391);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 260:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(392);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 261:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(393);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 262:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(394);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 263:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(395);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 264:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(396);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 265:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(397);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 266:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(398);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 267:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(399);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_try);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 269:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(400);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 270:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(401);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(anon_sym_tuw);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 272:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(402);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 273:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'q') ADVANCE(403);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 274:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(404);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 275:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(405);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 276:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(406);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 277:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'E') ADVANCE(407);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 278:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'T') ADVANCE(408);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 279:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '8') ADVANCE(409);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 280:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(410);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 281:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(411);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(anon_sym_wle);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 283:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(412);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 284:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(413);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 285:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(414);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(anon_sym_zip);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 287:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(415);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 288:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(416);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 289:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(417);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(anon_sym_args);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 291:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '6') ADVANCE(418);
      if (lookahead == 'n') ADVANCE(419);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 292:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(420);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_bind);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(anon_sym_bool);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 295:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'k') ADVANCE(421);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 296:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(422);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_ceil);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 298:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'k') ADVANCE(423);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 299:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(424);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 300:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(425);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 301:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(426);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 302:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(427);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_date);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(428);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 304:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'v') ADVANCE(429);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 305:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(430);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(anon_sym_dirs);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_drop);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'W') ADVANCE(431);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_each);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'W') ADVANCE(432);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(anon_sym_else);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 310:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'W') ADVANCE(433);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 311:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(434);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 312:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(435);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(anon_sym_exit);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 314:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(436);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(anon_sym_fail);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 316:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(437);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 317:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'E') ADVANCE(438);
      if (lookahead == 'S') ADVANCE(439);
      if (lookahead == 's') ADVANCE(440);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 318:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(441);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 319:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'R') ADVANCE(442);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 320:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(443);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 321:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(444);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 322:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(445);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 323:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'O') ADVANCE(446);
      if (lookahead == 'U') ADVANCE(447);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 324:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(448);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(anon_sym_glob);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 326:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'V') ADVANCE(449);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 327:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(450);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 328:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'L') ADVANCE(451);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 329:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(452);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(anon_sym_hour);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 331:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'G') ADVANCE(453);
      if (lookahead == 'P') ADVANCE(454);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 332:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(455);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 333:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(456);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 334:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(457);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 335:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(458);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 336:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(459);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 337:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(460);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 338:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(461);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 339:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(462);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(anon_sym_join);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(anon_sym_just);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 342:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(463);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(anon_sym_keys);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 344:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'I') ADVANCE(464);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 345:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'J') ADVANCE(465);
      if (lookahead == 'P') ADVANCE(466);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 346:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(467);
      if (lookahead == 's') ADVANCE(468);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 347:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'T') ADVANCE(469);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(anon_sym_loop);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 349:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(470);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 350:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(471);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 351:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(472);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(anon_sym_max2);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 353:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(473);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(anon_sym_min2);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 355:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(474);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 356:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(475);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 357:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(476);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(anon_sym_none);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 359:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(477);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(anon_sym_over);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 361:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(478);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(anon_sym_pick);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 363:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(479);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(anon_sym_psub);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(anon_sym_pure);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 366:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(480);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 367:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(481);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 368:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(482);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 369:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(483);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(anon_sym_read);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(484);
      if (lookahead == 'T') ADVANCE(485);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 371:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(486);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 372:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(487);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 373:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(488);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 374:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(489);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 375:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(490);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 376:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(491);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(anon_sym_setd);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 378:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '5') ADVANCE(492);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(anon_sym_skip);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(anon_sym_sort);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'B') ADVANCE(493);
      if (lookahead == 'V') ADVANCE(494);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 381:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(495);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 382:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(496);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 383:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(497);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(anon_sym_stem);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 385:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(498);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(anon_sym_swap);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(anon_sym_take);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'W') ADVANCE(499);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 388:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(500);
      if (lookahead == 'F') ADVANCE(501);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 389:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(502);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 390:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'v') ADVANCE(503);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(anon_sym_toDt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 392:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(504);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 393:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(505);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 394:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(506);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 395:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(507);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 396:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(508);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 397:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(509);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(anon_sym_trim);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'E') ADVANCE(510);
      if (lookahead == 'S') ADVANCE(511);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(anon_sym_true);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 400:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(512);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 401:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(513);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(anon_sym_type);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(514);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(anon_sym_uniq);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 404:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(515);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 405:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(516);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 406:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(517);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 407:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(518);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 408:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(519);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 409:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'B') ADVANCE(520);
      if (lookahead == 'S') ADVANCE(521);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 410:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(522);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 411:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(523);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 412:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(524);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 413:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(525);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(anon_sym_year);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 415:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(526);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 416:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(527);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 417:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(528);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 418:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '4') ADVANCE(529);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 419:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(530);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 420:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(531);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 421:
      ACCEPT_TOKEN(anon_sym_break);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 422:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(532);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 423:
      ACCEPT_TOKEN(anon_sym_chunk);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 424:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(533);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 425:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(534);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 426:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'S') ADVANCE(535);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 427:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'U') ADVANCE(536);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 428:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(537);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 429:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(538);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 430:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(539);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 431:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(540);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 432:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(541);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 433:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(542);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 434:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(543);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 435:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(544);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 436:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(545);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 437:
      ACCEPT_TOKEN(anon_sym_false);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 438:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(546);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 439:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(547);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 440:
      ACCEPT_TOKEN(anon_sym_files);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 441:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(548);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 442:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(549);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 443:
      ACCEPT_TOKEN(anon_sym_float);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(550);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 444:
      ACCEPT_TOKEN(anon_sym_floor);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 445:
      ACCEPT_TOKEN(anon_sym_foldl);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 446:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(551);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 447:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(552);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 448:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(553);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 449:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(554);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 450:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'B') ADVANCE(555);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 451:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(556);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 452:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(557);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 453:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(558);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 454:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(559);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 455:
      ACCEPT_TOKEN(anon_sym_index);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 456:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(560);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 457:
      ACCEPT_TOKEN(anon_sym_isCmd);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 458:
      ACCEPT_TOKEN(anon_sym_isDir);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 459:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(561);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 460:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(562);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 461:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'k') ADVANCE(563);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 462:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(564);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 463:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(565);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 464:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(566);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 465:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(567);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 466:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(568);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 467:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(569);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 468:
      ACCEPT_TOKEN(anon_sym_lines);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 469:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(570);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 470:
      ACCEPT_TOKEN(anon_sym_lower);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 471:
      ACCEPT_TOKEN(anon_sym_lsDir);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 472:
      ACCEPT_TOKEN(anon_sym_match);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 473:
      ACCEPT_TOKEN(anon_sym_maybe);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 474:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(571);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 475:
      ACCEPT_TOKEN(anon_sym_mkdir);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(572);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 476:
      ACCEPT_TOKEN(anon_sym_month);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 477:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'J') ADVANCE(573);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 478:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(574);
      if (lookahead == 'E') ADVANCE(575);
      if (lookahead == 'H') ADVANCE(576);
      if (lookahead == 'J') ADVANCE(577);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 479:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(578);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 480:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(579);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 481:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(580);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 482:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(581);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 483:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(582);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 484:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(583);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 485:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(584);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 486:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(585);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 487:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(586);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 488:
      ACCEPT_TOKEN(anon_sym_round);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 489:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(587);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 490:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(588);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 491:
      ACCEPT_TOKEN(anon_sym_setAt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 492:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == '6') ADVANCE(589);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 493:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(590);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 494:
      ACCEPT_TOKEN(anon_sym_sortV);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 495:
      ACCEPT_TOKEN(anon_sym_split);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 496:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(591);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 497:
      ACCEPT_TOKEN(anon_sym_stdin);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 498:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(592);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 499:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(593);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 500:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(594);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 501:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(595);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 502:
      ACCEPT_TOKEN(anon_sym_title);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 503:
      ACCEPT_TOKEN(anon_sym_toCsv);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(596);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 504:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(597);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 505:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(598);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 506:
      ACCEPT_TOKEN(anon_sym_toInt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 507:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(599);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 508:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(600);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 509:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(601);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 510:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(602);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 511:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(603);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 512:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(604);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 513:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(605);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 514:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(606);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 515:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(607);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 516:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(608);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 517:
      ACCEPT_TOKEN(anon_sym_upper);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 518:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(609);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 519:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(610);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 520:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(611);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 521:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(612);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 522:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(613);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 523:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(614);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 524:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(615);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 525:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(616);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 526:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(617);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 527:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(618);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 528:
      ACCEPT_TOKEN(anon_sym_append);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(619);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 529:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(620);
      if (lookahead == 'e') ADVANCE(621);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 530:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(622);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 531:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(623);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 532:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(624);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 533:
      ACCEPT_TOKEN(anon_sym_concat);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 534:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(625);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 535:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(626);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 536:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(627);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 537:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(628);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 538:
      ACCEPT_TOKEN(anon_sym_derive);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 539:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(629);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 540:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(630);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 541:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(631);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 542:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(632);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 543:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(633);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 544:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(634);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 545:
      ACCEPT_TOKEN(anon_sym_extend);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 546:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(635);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 547:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'z') ADVANCE(636);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 548:
      ACCEPT_TOKEN(anon_sym_filter);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 549:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(637);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 550:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(638);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 551:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(639);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 552:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(640);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 553:
      ACCEPT_TOKEN(anon_sym_getDef);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 554:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(641);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 555:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(642);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 556:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(643);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 557:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(644);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 558:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(645);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 559:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(646);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 560:
      ACCEPT_TOKEN(anon_sym_insert);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 561:
      ACCEPT_TOKEN(anon_sym_isFile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 562:
      ACCEPT_TOKEN(anon_sym_isNone);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 563:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(647);
      if (lookahead == 'e') ADVANCE(648);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 564:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(649);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 565:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(650);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 566:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(651);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 567:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(652);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 568:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(653);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 569:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'S') ADVANCE(654);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 570:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(655);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 571:
      ACCEPT_TOKEN(anon_sym_minute);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 572:
      ACCEPT_TOKEN(anon_sym_mkdirp);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 573:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(656);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 574:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(657);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 575:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(658);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 576:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(659);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 577:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(660);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 578:
      ACCEPT_TOKEN(anon_sym_prompt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 579:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'A') ADVANCE(661);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 580:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(662);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 581:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(663);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 582:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(664);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 583:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(665);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 584:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'v') ADVANCE(666);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 585:
      ACCEPT_TOKEN(anon_sym_repeat);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 586:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(667);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 587:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(668);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 588:
      ACCEPT_TOKEN(anon_sym_select);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 589:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(669);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 590:
      ACCEPT_TOKEN(anon_sym_sortBy);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(670);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 591:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'W') ADVANCE(671);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 592:
      ACCEPT_TOKEN(anon_sym_strCmp);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 593:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(672);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 594:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(673);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 595:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(674);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 596:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(675);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 597:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(676);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 598:
      ACCEPT_TOKEN(anon_sym_toGrid);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 599:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(677);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 600:
      ACCEPT_TOKEN(anon_sym_toPath);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 601:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'T') ADVANCE(678);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 602:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(679);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 603:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(680);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 604:
      ACCEPT_TOKEN(anon_sym_tsplit);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 605:
      ACCEPT_TOKEN(anon_sym_ttFile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 606:
      ACCEPT_TOKEN(anon_sym_typeof);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 607:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(681);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 608:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(682);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 609:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(683);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 610:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(684);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 611:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(685);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 612:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(686);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 613:
      ACCEPT_TOKEN(anon_sym_values);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 614:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(687);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 615:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(688);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 616:
      ACCEPT_TOKEN(anon_sym_wsplit);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 617:
      ACCEPT_TOKEN(anon_sym_absPath);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 618:
      ACCEPT_TOKEN(anon_sym_addDays);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 619:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(689);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 620:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(690);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 621:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(691);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 622:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(692);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 623:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(693);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 624:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(694);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 625:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(695);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 626:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'b') ADVANCE(696);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 627:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(697);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 628:
      ACCEPT_TOKEN(anon_sym_dateFmt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 629:
      ACCEPT_TOKEN(anon_sym_dirname);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 630:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(698);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 631:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(699);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 632:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(700);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 633:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(701);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 634:
      ACCEPT_TOKEN(anon_sym_exclude);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 635:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(702);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 636:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(703);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 637:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(704);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 638:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(705);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 639:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'D') ADVANCE(706);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 640:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(707);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 641:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(708);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 642:
      ACCEPT_TOKEN(anon_sym_groupBy);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 643:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'k') ADVANCE(709);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 644:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(710);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 645:
      ACCEPT_TOKEN(anon_sym_httpGet);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 646:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(711);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 647:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(712);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 648:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(713);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 649:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(714);
      if (lookahead == 'T') ADVANCE(715);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 650:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(716);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 651:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(717);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 652:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(718);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 653:
      ACCEPT_TOKEN(anon_sym_leftPad);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 654:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(719);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 655:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(720);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 656:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(721);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 657:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'v') ADVANCE(722);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 658:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(723);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 659:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(724);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 660:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(725);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 661:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(726);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 662:
      ACCEPT_TOKEN(anon_sym_reMatch);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 663:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(727);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 664:
      ACCEPT_TOKEN(anon_sym_reSplit);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 665:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(728);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 666:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(729);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 667:
      ACCEPT_TOKEN(anon_sym_reverse);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 668:
      ACCEPT_TOKEN(anon_sym_runtime);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 669:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'u') ADVANCE(730);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 670:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(731);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 671:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(732);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 672:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(733);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 673:
      ACCEPT_TOKEN(anon_sym_tempDir);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 674:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(734);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 675:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(735);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 676:
      ACCEPT_TOKEN(anon_sym_toFloat);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 677:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(736);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 678:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(737);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 679:
      ACCEPT_TOKEN(anon_sym_trimEnd);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 680:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(738);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 681:
      ACCEPT_TOKEN(anon_sym_unlines);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(739);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 682:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(740);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 683:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(741);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 684:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(742);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 685:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(743);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 686:
      ACCEPT_TOKEN(anon_sym_utf8Str);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 687:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'S') ADVANCE(744);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 688:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(745);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 689:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(746);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 690:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(747);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 691:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(748);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 692:
      ACCEPT_TOKEN(anon_sym_basename);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 693:
      ACCEPT_TOKEN(anon_sym_binPaths);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 694:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(749);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 695:
      ACCEPT_TOKEN(anon_sym_continue);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 696:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'S') ADVANCE(750);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 697:
      ACCEPT_TOKEN(anon_sym_cstToUtc);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 698:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(751);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 699:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(752);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 700:
      ACCEPT_TOKEN(anon_sym_endsWith);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 701:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(753);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 702:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(754);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 703:
      ACCEPT_TOKEN(anon_sym_fileSize);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 704:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(755);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 705:
      ACCEPT_TOKEN(anon_sym_floatCmp);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 706:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(756);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 707:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'T') ADVANCE(757);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 708:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(758);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 709:
      ACCEPT_TOKEN(anon_sym_hardLink);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 710:
      ACCEPT_TOKEN(anon_sym_hostname);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 711:
      ACCEPT_TOKEN(anon_sym_httpPost);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 712:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(759);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 713:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(760);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 714:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(761);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 715:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(762);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 716:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(763);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 717:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(764);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 718:
      ACCEPT_TOKEN(anon_sym_leftJoin);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 719:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(765);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 720:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(766);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 721:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(767);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 722:
      ACCEPT_TOKEN(anon_sym_parseCsv);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 723:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(768);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 724:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(769);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 725:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(770);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 726:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(771);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 727:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(772);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 728:
      ACCEPT_TOKEN(anon_sym_readFile);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'B') ADVANCE(773);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 729:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(774);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 730:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(775);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 731:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(776);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 732:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(777);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 733:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(778);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 734:
      ACCEPT_TOKEN(anon_sym_tempFile);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'E') ADVANCE(779);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 735:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(780);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 736:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(781);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 737:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(782);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 738:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(783);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 739:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(784);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 740:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(785);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 741:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(786);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 742:
      ACCEPT_TOKEN(anon_sym_utcToCst);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 743:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(787);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 744:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(788);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 745:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(789);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 746:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(790);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 747:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(791);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 748:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(792);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 749:
      ACCEPT_TOKEN(anon_sym_cartesian);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 750:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(793);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 751:
      ACCEPT_TOKEN(anon_sym_dropWhile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 752:
      ACCEPT_TOKEN(anon_sym_eachWhile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 753:
      ACCEPT_TOKEN(anon_sym_enumerate);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'N') ADVANCE(794);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 754:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(795);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 755:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(796);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 756:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(797);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 757:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(798);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 758:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(799);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 759:
      ACCEPT_TOKEN(anon_sym_isWeekday);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 760:
      ACCEPT_TOKEN(anon_sym_isWeekend);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 761:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(800);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 762:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(801);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 763:
      ACCEPT_TOKEN(anon_sym_keyValues);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 764:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'O') ADVANCE(802);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 765:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(803);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 766:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(804);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 767:
      ACCEPT_TOKEN(anon_sym_outerJoin);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 768:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(805);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 769:
      ACCEPT_TOKEN(anon_sym_parseHtml);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 770:
      ACCEPT_TOKEN(anon_sym_parseJson);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 771:
      ACCEPT_TOKEN(anon_sym_reFindAll);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'I') ADVANCE(806);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 772:
      ACCEPT_TOKEN(anon_sym_reReplace);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 773:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'y') ADVANCE(807);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 774:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(808);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 775:
      ACCEPT_TOKEN(anon_sym_sha256sum);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 776:
      ACCEPT_TOKEN(anon_sym_sortByCmp);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 777:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(809);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 778:
      ACCEPT_TOKEN(anon_sym_takeWhile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 779:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(810);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 780:
      ACCEPT_TOKEN(anon_sym_toCsvCell);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 781:
      ACCEPT_TOKEN(anon_sym_toOleDate);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 782:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(811);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 783:
      ACCEPT_TOKEN(anon_sym_trimStart);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 784:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'L') ADVANCE(812);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 785:
      ACCEPT_TOKEN(anon_sym_updateCol);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 786:
      ACCEPT_TOKEN(anon_sym_urlEncode);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 787:
      ACCEPT_TOKEN(anon_sym_utf8Bytes);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 788:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(813);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 789:
      ACCEPT_TOKEN(anon_sym_writeFile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 790:
      ACCEPT_TOKEN(anon_sym_appendFile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 791:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(814);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 792:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(815);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 793:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(816);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 794:
      ACCEPT_TOKEN(anon_sym_enumerateN);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 795:
      ACCEPT_TOKEN(anon_sym_fileExists);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 796:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(817);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 797:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(818);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 798:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(819);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 799:
      ACCEPT_TOKEN(anon_sym_gridValues);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 800:
      ACCEPT_TOKEN(anon_sym_isoDateFmt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 801:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(820);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 802:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(821);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 803:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(822);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 804:
      ACCEPT_TOKEN(anon_sym_listToDict);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 805:
      ACCEPT_TOKEN(anon_sym_parseExcel);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 806:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(823);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 807:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(824);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 808:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(825);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 809:
      ACCEPT_TOKEN(anon_sym_startsWith);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 810:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(826);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 811:
      ACCEPT_TOKEN(anon_sym_toUnixTime);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'M') ADVANCE(827);
      if (lookahead == 'N') ADVANCE(828);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 812:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'f') ADVANCE(829);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 813:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(830);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 814:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(831);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 815:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(832);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 816:
      ACCEPT_TOKEN(anon_sym_countSubStr);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 817:
      ACCEPT_TOKEN(anon_sym_findReplace);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 818:
      ACCEPT_TOKEN(anon_sym_fromOleDate);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 819:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(833);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 820:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'F') ADVANCE(834);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 821:
      ACCEPT_TOKEN(anon_sym_lastIndexOf);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 822:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'h') ADVANCE(835);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 823:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(836);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 824:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(837);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 825:
      ACCEPT_TOKEN(anon_sym_readTsvFile);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 826:
      ACCEPT_TOKEN(anon_sym_tempFileExt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 827:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(838);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 828:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(839);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 829:
      ACCEPT_TOKEN(anon_sym_unlinesCrLf);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 830:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'C') ADVANCE(840);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 831:
      ACCEPT_TOKEN(anon_sym_base64decode);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 832:
      ACCEPT_TOKEN(anon_sym_base64encode);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 833:
      ACCEPT_TOKEN(anon_sym_fromUnixTime);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'M') ADVANCE(841);
      if (lookahead == 'N') ADVANCE(842);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 834:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(843);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 835:
      ACCEPT_TOKEN(anon_sym_linearSearch);
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'I') ADVANCE(844);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 836:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(845);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 837:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 's') ADVANCE(846);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 838:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(847);
      if (lookahead == 'l') ADVANCE(848);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 839:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(849);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 840:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'm') ADVANCE(850);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 841:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(851);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 842:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'a') ADVANCE(852);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 843:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 't') ADVANCE(853);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 844:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(854);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 845:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(855);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 846:
      ACCEPT_TOKEN(anon_sym_readFileBytes);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 847:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(856);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 848:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(857);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 849:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(858);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 850:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'p') ADVANCE(859);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 851:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'c') ADVANCE(860);
      if (lookahead == 'l') ADVANCE(861);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 852:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'n') ADVANCE(862);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 853:
      ACCEPT_TOKEN(anon_sym_isoDateTimeFmt);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 854:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'd') ADVANCE(863);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 855:
      ACCEPT_TOKEN(anon_sym_reFindAllIndex);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 856:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(864);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 857:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(865);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 858:
      ACCEPT_TOKEN(anon_sym_toUnixTimeNano);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 859:
      ACCEPT_TOKEN(anon_sym_versionSortCmp);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 860:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'r') ADVANCE(866);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 861:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'l') ADVANCE(867);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 862:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(868);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 863:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'e') ADVANCE(869);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 864:
      ACCEPT_TOKEN(anon_sym_toUnixTimeMicro);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 865:
      ACCEPT_TOKEN(anon_sym_toUnixTimeMilli);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 866:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'o') ADVANCE(870);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 867:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(871);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 868:
      ACCEPT_TOKEN(anon_sym_fromUnixTimeNano);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 869:
      if (lookahead == '.') ADVANCE(28);
      if (lookahead == 'x') ADVANCE(872);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 870:
      ACCEPT_TOKEN(anon_sym_fromUnixTimeMicro);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 871:
      ACCEPT_TOKEN(anon_sym_fromUnixTimeMilli);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    case 872:
      ACCEPT_TOKEN(anon_sym_linearSearchIndex);
      if (lookahead == '.') ADVANCE(28);
      if ((!eof && set_contains(sym_var_retrieve_character_set_1, 11, lookahead))) ADVANCE(27);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 23},
  [2] = {.lex_state = 23},
  [3] = {.lex_state = 23},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 23},
  [6] = {.lex_state = 23},
  [7] = {.lex_state = 23},
  [8] = {.lex_state = 23},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 23},
  [11] = {.lex_state = 23},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 23},
  [14] = {.lex_state = 23},
  [15] = {.lex_state = 23},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 23},
  [18] = {.lex_state = 23},
  [19] = {.lex_state = 23},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 23},
  [22] = {.lex_state = 23},
  [23] = {.lex_state = 23},
  [24] = {.lex_state = 23},
  [25] = {.lex_state = 23},
  [26] = {.lex_state = 23},
  [27] = {.lex_state = 23},
  [28] = {.lex_state = 23},
  [29] = {.lex_state = 23},
  [30] = {.lex_state = 23},
  [31] = {.lex_state = 23},
  [32] = {.lex_state = 23},
  [33] = {.lex_state = 23},
  [34] = {.lex_state = 23},
  [35] = {.lex_state = 23},
  [36] = {.lex_state = 23},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK_PIPE] = ACTIONS(1),
    [anon_sym_PIPE_RBRACK] = ACTIONS(1),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [anon_sym_def] = ACTIONS(1),
    [anon_sym_end] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_iff] = ACTIONS(1),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_else_STAR] = ACTIONS(1),
    [anon_sym_STARif] = ACTIONS(1),
    [anon_sym_loop] = ACTIONS(1),
    [anon_sym_match] = ACTIONS(1),
    [anon_sym_break] = ACTIONS(1),
    [anon_sym_continue] = ACTIONS(1),
    [anon_sym_soe] = ACTIONS(1),
    [anon_sym_not] = ACTIONS(1),
    [anon_sym_and] = ACTIONS(1),
    [anon_sym_or] = ACTIONS(1),
    [anon_sym_read] = ACTIONS(1),
    [anon_sym_str] = ACTIONS(1),
    [anon_sym_as] = ACTIONS(1),
    [anon_sym_type] = ACTIONS(1),
    [anon_sym_try] = ACTIONS(1),
    [anon_sym_fail] = ACTIONS(1),
    [anon_sym_pure] = ACTIONS(1),
    [anon_sym_VER] = ACTIONS(1),
    [anon_sym_x] = ACTIONS(1),
    [anon_sym_int] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_dup] = ACTIONS(1),
    [anon_sym_swap] = ACTIONS(1),
    [anon_sym_drop] = ACTIONS(1),
    [anon_sym_over] = ACTIONS(1),
    [anon_sym_pick] = ACTIONS(1),
    [anon_sym_rot] = ACTIONS(1),
    [anon_sym_DASHrot] = ACTIONS(1),
    [anon_sym_nip] = ACTIONS(1),
    [anon_sym_w] = ACTIONS(1),
    [anon_sym_wl] = ACTIONS(1),
    [anon_sym_we] = ACTIONS(1),
    [anon_sym_wle] = ACTIONS(1),
    [anon_sym_len] = ACTIONS(1),
    [anon_sym_args] = ACTIONS(1),
    [anon_sym_glob] = ACTIONS(1),
    [anon_sym_toFloat] = ACTIONS(1),
    [anon_sym_toInt] = ACTIONS(1),
    [anon_sym_toPath] = ACTIONS(1),
    [anon_sym_toDt] = ACTIONS(1),
    [anon_sym_toGrid] = ACTIONS(1),
    [anon_sym_toCsv] = ACTIONS(1),
    [anon_sym_toCsvCell] = ACTIONS(1),
    [anon_sym_exit] = ACTIONS(1),
    [anon_sym_prompt] = ACTIONS(1),
    [anon_sym_stdin] = ACTIONS(1),
    [anon_sym_COLON_COLON] = ACTIONS(1),
    [anon_sym_foldl] = ACTIONS(1),
    [anon_sym_map] = ACTIONS(1),
    [anon_sym_each] = ACTIONS(1),
    [anon_sym_eachWhile] = ACTIONS(1),
    [anon_sym_filter] = ACTIONS(1),
    [anon_sym_append] = ACTIONS(1),
    [anon_sym_extend] = ACTIONS(1),
    [anon_sym_concat] = ACTIONS(1),
    [anon_sym_reverse] = ACTIONS(1),
    [anon_sym_sort] = ACTIONS(1),
    [anon_sym_sortV] = ACTIONS(1),
    [anon_sym_sortBy] = ACTIONS(1),
    [anon_sym_sortByCmp] = ACTIONS(1),
    [anon_sym_uniq] = ACTIONS(1),
    [anon_sym_zip] = ACTIONS(1),
    [anon_sym_enumerate] = ACTIONS(1),
    [anon_sym_enumerateN] = ACTIONS(1),
    [anon_sym_chunk] = ACTIONS(1),
    [anon_sym_pop] = ACTIONS(1),
    [anon_sym_take] = ACTIONS(1),
    [anon_sym_takeWhile] = ACTIONS(1),
    [anon_sym_skip] = ACTIONS(1),
    [anon_sym_dropWhile] = ACTIONS(1),
    [anon_sym_nth] = ACTIONS(1),
    [anon_sym_insert] = ACTIONS(1),
    [anon_sym_setAt] = ACTIONS(1),
    [anon_sym_del] = ACTIONS(1),
    [anon_sym_sum] = ACTIONS(1),
    [anon_sym_max] = ACTIONS(1),
    [anon_sym_max2] = ACTIONS(1),
    [anon_sym_min] = ACTIONS(1),
    [anon_sym_min2] = ACTIONS(1),
    [anon_sym_abs] = ACTIONS(1),
    [anon_sym_inc] = ACTIONS(1),
    [anon_sym_mod] = ACTIONS(1),
    [anon_sym_floor] = ACTIONS(1),
    [anon_sym_ceil] = ACTIONS(1),
    [anon_sym_round] = ACTIONS(1),
    [anon_sym_lines] = ACTIONS(1),
    [anon_sym_unlines] = ACTIONS(1),
    [anon_sym_unlinesCrLf] = ACTIONS(1),
    [anon_sym_split] = ACTIONS(1),
    [anon_sym_wsplit] = ACTIONS(1),
    [anon_sym_tsplit] = ACTIONS(1),
    [anon_sym_join] = ACTIONS(1),
    [anon_sym_trim] = ACTIONS(1),
    [anon_sym_trimStart] = ACTIONS(1),
    [anon_sym_trimEnd] = ACTIONS(1),
    [anon_sym_startsWith] = ACTIONS(1),
    [anon_sym_endsWith] = ACTIONS(1),
    [anon_sym_lower] = ACTIONS(1),
    [anon_sym_upper] = ACTIONS(1),
    [anon_sym_title] = ACTIONS(1),
    [anon_sym_leftPad] = ACTIONS(1),
    [anon_sym_findReplace] = ACTIONS(1),
    [anon_sym_in] = ACTIONS(1),
    [anon_sym_index] = ACTIONS(1),
    [anon_sym_lastIndexOf] = ACTIONS(1),
    [anon_sym_countSubStr] = ACTIONS(1),
    [anon_sym_parseJson] = ACTIONS(1),
    [anon_sym_parseCsv] = ACTIONS(1),
    [anon_sym_parseHtml] = ACTIONS(1),
    [anon_sym_parseExcel] = ACTIONS(1),
    [anon_sym_readFile] = ACTIONS(1),
    [anon_sym_readFileBytes] = ACTIONS(1),
    [anon_sym_readTsvFile] = ACTIONS(1),
    [anon_sym_writeFile] = ACTIONS(1),
    [anon_sym_appendFile] = ACTIONS(1),
    [anon_sym_fileExists] = ACTIONS(1),
    [anon_sym_isDir] = ACTIONS(1),
    [anon_sym_isFile] = ACTIONS(1),
    [anon_sym_fileSize] = ACTIONS(1),
    [anon_sym_cp] = ACTIONS(1),
    [anon_sym_mv] = ACTIONS(1),
    [anon_sym_rm] = ACTIONS(1),
    [anon_sym_rmf] = ACTIONS(1),
    [anon_sym_mkdir] = ACTIONS(1),
    [anon_sym_mkdirp] = ACTIONS(1),
    [anon_sym_cd] = ACTIONS(1),
    [anon_sym_pwd] = ACTIONS(1),
    [anon_sym_tempFile] = ACTIONS(1),
    [anon_sym_tempFileExt] = ACTIONS(1),
    [anon_sym_tempDir] = ACTIONS(1),
    [anon_sym_lsDir] = ACTIONS(1),
    [anon_sym_files] = ACTIONS(1),
    [anon_sym_dirs] = ACTIONS(1),
    [anon_sym_absPath] = ACTIONS(1),
    [anon_sym_dirname] = ACTIONS(1),
    [anon_sym_basename] = ACTIONS(1),
    [anon_sym_ext] = ACTIONS(1),
    [anon_sym_stem] = ACTIONS(1),
    [anon_sym_isCmd] = ACTIONS(1),
    [anon_sym_hardLink] = ACTIONS(1),
    [anon_sym_sha256sum] = ACTIONS(1),
    [anon_sym_md5] = ACTIONS(1),
    [anon_sym_now] = ACTIONS(1),
    [anon_sym_date] = ACTIONS(1),
    [anon_sym_year] = ACTIONS(1),
    [anon_sym_month] = ACTIONS(1),
    [anon_sym_day] = ACTIONS(1),
    [anon_sym_hour] = ACTIONS(1),
    [anon_sym_minute] = ACTIONS(1),
    [anon_sym_dateFmt] = ACTIONS(1),
    [anon_sym_isoDateFmt] = ACTIONS(1),
    [anon_sym_isoDateTimeFmt] = ACTIONS(1),
    [anon_sym_isWeekend] = ACTIONS(1),
    [anon_sym_isWeekday] = ACTIONS(1),
    [anon_sym_dow] = ACTIONS(1),
    [anon_sym_addDays] = ACTIONS(1),
    [anon_sym_toUnixTime] = ACTIONS(1),
    [anon_sym_toUnixTimeMilli] = ACTIONS(1),
    [anon_sym_toUnixTimeMicro] = ACTIONS(1),
    [anon_sym_toUnixTimeNano] = ACTIONS(1),
    [anon_sym_fromUnixTime] = ACTIONS(1),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(1),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(1),
    [anon_sym_fromUnixTimeNano] = ACTIONS(1),
    [anon_sym_toOleDate] = ACTIONS(1),
    [anon_sym_fromOleDate] = ACTIONS(1),
    [anon_sym_utcToCst] = ACTIONS(1),
    [anon_sym_cstToUtc] = ACTIONS(1),
    [anon_sym_reMatch] = ACTIONS(1),
    [anon_sym_reFindAll] = ACTIONS(1),
    [anon_sym_reFindAllIndex] = ACTIONS(1),
    [anon_sym_reReplace] = ACTIONS(1),
    [anon_sym_reSplit] = ACTIONS(1),
    [anon_sym_just] = ACTIONS(1),
    [anon_sym_none] = ACTIONS(1),
    [anon_sym_isNone] = ACTIONS(1),
    [anon_sym_maybe] = ACTIONS(1),
    [anon_sym_bind] = ACTIONS(1),
    [anon_sym_psub] = ACTIONS(1),
    [anon_sym_typeof] = ACTIONS(1),
    [anon_sym_runtime] = ACTIONS(1),
    [anon_sym_hostname] = ACTIONS(1),
    [anon_sym_httpGet] = ACTIONS(1),
    [anon_sym_httpPost] = ACTIONS(1),
    [anon_sym_urlEncode] = ACTIONS(1),
    [anon_sym_base64encode] = ACTIONS(1),
    [anon_sym_base64decode] = ACTIONS(1),
    [anon_sym_utf8Str] = ACTIONS(1),
    [anon_sym_utf8Bytes] = ACTIONS(1),
    [anon_sym_get] = ACTIONS(1),
    [anon_sym_getDef] = ACTIONS(1),
    [anon_sym_set] = ACTIONS(1),
    [anon_sym_setd] = ACTIONS(1),
    [anon_sym_keys] = ACTIONS(1),
    [anon_sym_values] = ACTIONS(1),
    [anon_sym_keyValues] = ACTIONS(1),
    [anon_sym_all] = ACTIONS(1),
    [anon_sym_any] = ACTIONS(1),
    [anon_sym_cartesian] = ACTIONS(1),
    [anon_sym_groupBy] = ACTIONS(1),
    [anon_sym_listToDict] = ACTIONS(1),
    [anon_sym_repeat] = ACTIONS(1),
    [anon_sym_seq] = ACTIONS(1),
    [anon_sym_tab] = ACTIONS(1),
    [anon_sym_select] = ACTIONS(1),
    [anon_sym_exclude] = ACTIONS(1),
    [anon_sym_derive] = ACTIONS(1),
    [anon_sym_updateCol] = ACTIONS(1),
    [anon_sym_gridValues] = ACTIONS(1),
    [anon_sym_leftJoin] = ACTIONS(1),
    [anon_sym_outerJoin] = ACTIONS(1),
    [anon_sym_linearSearch] = ACTIONS(1),
    [anon_sym_linearSearchIndex] = ACTIONS(1),
    [anon_sym_binPaths] = ACTIONS(1),
    [anon_sym_wt] = ACTIONS(1),
    [anon_sym_tt] = ACTIONS(1),
    [anon_sym_ttFile] = ACTIONS(1),
    [anon_sym_uw] = ACTIONS(1),
    [anon_sym_tuw] = ACTIONS(1),
    [anon_sym_strCmp] = ACTIONS(1),
    [anon_sym_floatCmp] = ACTIONS(1),
    [anon_sym_versionSortCmp] = ACTIONS(1),
    [anon_sym_id] = ACTIONS(1),
    [anon_sym_2id] = ACTIONS(1),
    [anon_sym_3id] = ACTIONS(1),
    [anon_sym_2unpack] = ACTIONS(1),
    [anon_sym_2apply] = ACTIONS(1),
    [anon_sym_2each] = ACTIONS(1),
    [anon_sym_2tuple] = ACTIONS(1),
    [anon_sym_DOTs] = ACTIONS(1),
    [anon_sym_DOTb] = ACTIONS(1),
    [anon_sym_DOTdef] = ACTIONS(1),
    [anon_sym_DOTenv] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_format_string] = ACTIONS(1),
    [sym_single_quoted_string] = ACTIONS(1),
    [sym_path] = ACTIONS(1),
    [sym_datetime] = ACTIONS(1),
    [sym_float] = ACTIONS(1),
    [sym_integer] = ACTIONS(1),
    [sym_env_store] = ACTIONS(1),
    [sym_env_check] = ACTIONS(1),
    [sym_env_retrieve] = ACTIONS(1),
    [sym_positional] = ACTIONS(1),
    [sym_var_retrieve] = ACTIONS(1),
    [sym_var_store] = ACTIONS(1),
    [sym_slice_indexer] = ACTIONS(1),
    [sym_indexer] = ACTIONS(1),
    [sym_end_indexer] = ACTIONS(1),
    [sym_start_indexer] = ACTIONS(1),
    [sym_match_arm_dup] = ACTIONS(1),
    [sym_prefix_quote] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_GT_GT] = ACTIONS(1),
    [anon_sym_2_GT] = ACTIONS(1),
    [anon_sym_2_GT_GT] = ACTIONS(1),
    [anon_sym_AMP_GT] = ACTIONS(1),
    [anon_sym_AMP_GT_GT] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_LT_GT] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_STARb] = ACTIONS(1),
    [anon_sym_CARET] = ACTIONS(1),
    [anon_sym_CARETb] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_AMP] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(53),
    [sym__word] = STATE(5),
    [sym_list] = STATE(5),
    [sym_quotation] = STATE(5),
    [sym_dict] = STATE(5),
    [sym_grid] = STATE(5),
    [sym_boolean] = STATE(5),
    [sym_keyword] = STATE(5),
    [sym_type_keyword] = STATE(5),
    [sym_builtin] = STATE(5),
    [sym_redirect_operator] = STATE(5),
    [sym_execute_operator] = STATE(5),
    [sym_comparison_operator] = STATE(5),
    [sym_punctuation] = STATE(5),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_identifier] = ACTIONS(7),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(29),
    [sym_format_string] = ACTIONS(29),
    [sym_single_quoted_string] = ACTIONS(29),
    [sym_path] = ACTIONS(29),
    [sym_datetime] = ACTIONS(29),
    [sym_float] = ACTIONS(29),
    [sym_integer] = ACTIONS(7),
    [sym_env_store] = ACTIONS(29),
    [sym_env_check] = ACTIONS(29),
    [sym_env_retrieve] = ACTIONS(7),
    [sym_positional] = ACTIONS(29),
    [sym_var_retrieve] = ACTIONS(29),
    [sym_var_store] = ACTIONS(29),
    [sym_slice_indexer] = ACTIONS(29),
    [sym_indexer] = ACTIONS(29),
    [sym_end_indexer] = ACTIONS(7),
    [sym_start_indexer] = ACTIONS(7),
    [sym_match_arm_dup] = ACTIONS(29),
    [sym_prefix_quote] = ACTIONS(7),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [2] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(45),
    [sym_identifier] = ACTIONS(47),
    [anon_sym_LBRACK] = ACTIONS(50),
    [anon_sym_RBRACK] = ACTIONS(45),
    [anon_sym_LPAREN] = ACTIONS(53),
    [anon_sym_RPAREN] = ACTIONS(45),
    [anon_sym_LBRACE] = ACTIONS(56),
    [anon_sym_RBRACE] = ACTIONS(45),
    [anon_sym_LBRACK_PIPE] = ACTIONS(59),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(62),
    [anon_sym_false] = ACTIONS(62),
    [anon_sym_def] = ACTIONS(65),
    [anon_sym_end] = ACTIONS(65),
    [anon_sym_if] = ACTIONS(65),
    [anon_sym_iff] = ACTIONS(65),
    [anon_sym_else] = ACTIONS(65),
    [anon_sym_else_STAR] = ACTIONS(68),
    [anon_sym_STARif] = ACTIONS(68),
    [anon_sym_loop] = ACTIONS(65),
    [anon_sym_match] = ACTIONS(65),
    [anon_sym_break] = ACTIONS(65),
    [anon_sym_continue] = ACTIONS(65),
    [anon_sym_soe] = ACTIONS(65),
    [anon_sym_not] = ACTIONS(65),
    [anon_sym_and] = ACTIONS(65),
    [anon_sym_or] = ACTIONS(65),
    [anon_sym_read] = ACTIONS(65),
    [anon_sym_str] = ACTIONS(65),
    [anon_sym_as] = ACTIONS(65),
    [anon_sym_type] = ACTIONS(65),
    [anon_sym_try] = ACTIONS(65),
    [anon_sym_fail] = ACTIONS(65),
    [anon_sym_pure] = ACTIONS(65),
    [anon_sym_VER] = ACTIONS(65),
    [anon_sym_x] = ACTIONS(65),
    [anon_sym_int] = ACTIONS(71),
    [anon_sym_float] = ACTIONS(71),
    [anon_sym_bool] = ACTIONS(71),
    [anon_sym_dup] = ACTIONS(74),
    [anon_sym_swap] = ACTIONS(74),
    [anon_sym_drop] = ACTIONS(74),
    [anon_sym_over] = ACTIONS(74),
    [anon_sym_pick] = ACTIONS(74),
    [anon_sym_rot] = ACTIONS(74),
    [anon_sym_DASHrot] = ACTIONS(74),
    [anon_sym_nip] = ACTIONS(74),
    [anon_sym_w] = ACTIONS(74),
    [anon_sym_wl] = ACTIONS(74),
    [anon_sym_we] = ACTIONS(74),
    [anon_sym_wle] = ACTIONS(74),
    [anon_sym_len] = ACTIONS(74),
    [anon_sym_args] = ACTIONS(74),
    [anon_sym_glob] = ACTIONS(74),
    [anon_sym_toFloat] = ACTIONS(74),
    [anon_sym_toInt] = ACTIONS(74),
    [anon_sym_toPath] = ACTIONS(74),
    [anon_sym_toDt] = ACTIONS(74),
    [anon_sym_toGrid] = ACTIONS(74),
    [anon_sym_toCsv] = ACTIONS(74),
    [anon_sym_toCsvCell] = ACTIONS(74),
    [anon_sym_exit] = ACTIONS(74),
    [anon_sym_prompt] = ACTIONS(74),
    [anon_sym_stdin] = ACTIONS(74),
    [anon_sym_COLON_COLON] = ACTIONS(77),
    [anon_sym_foldl] = ACTIONS(74),
    [anon_sym_map] = ACTIONS(74),
    [anon_sym_each] = ACTIONS(74),
    [anon_sym_eachWhile] = ACTIONS(74),
    [anon_sym_filter] = ACTIONS(74),
    [anon_sym_append] = ACTIONS(74),
    [anon_sym_extend] = ACTIONS(74),
    [anon_sym_concat] = ACTIONS(74),
    [anon_sym_reverse] = ACTIONS(74),
    [anon_sym_sort] = ACTIONS(74),
    [anon_sym_sortV] = ACTIONS(74),
    [anon_sym_sortBy] = ACTIONS(74),
    [anon_sym_sortByCmp] = ACTIONS(74),
    [anon_sym_uniq] = ACTIONS(74),
    [anon_sym_zip] = ACTIONS(74),
    [anon_sym_enumerate] = ACTIONS(74),
    [anon_sym_enumerateN] = ACTIONS(74),
    [anon_sym_chunk] = ACTIONS(74),
    [anon_sym_pop] = ACTIONS(74),
    [anon_sym_take] = ACTIONS(74),
    [anon_sym_takeWhile] = ACTIONS(74),
    [anon_sym_skip] = ACTIONS(74),
    [anon_sym_dropWhile] = ACTIONS(74),
    [anon_sym_nth] = ACTIONS(74),
    [anon_sym_insert] = ACTIONS(74),
    [anon_sym_setAt] = ACTIONS(74),
    [anon_sym_del] = ACTIONS(74),
    [anon_sym_sum] = ACTIONS(74),
    [anon_sym_max] = ACTIONS(74),
    [anon_sym_max2] = ACTIONS(74),
    [anon_sym_min] = ACTIONS(74),
    [anon_sym_min2] = ACTIONS(74),
    [anon_sym_abs] = ACTIONS(74),
    [anon_sym_inc] = ACTIONS(74),
    [anon_sym_mod] = ACTIONS(74),
    [anon_sym_floor] = ACTIONS(74),
    [anon_sym_ceil] = ACTIONS(74),
    [anon_sym_round] = ACTIONS(74),
    [anon_sym_lines] = ACTIONS(74),
    [anon_sym_unlines] = ACTIONS(74),
    [anon_sym_unlinesCrLf] = ACTIONS(74),
    [anon_sym_split] = ACTIONS(74),
    [anon_sym_wsplit] = ACTIONS(74),
    [anon_sym_tsplit] = ACTIONS(74),
    [anon_sym_join] = ACTIONS(74),
    [anon_sym_trim] = ACTIONS(74),
    [anon_sym_trimStart] = ACTIONS(74),
    [anon_sym_trimEnd] = ACTIONS(74),
    [anon_sym_startsWith] = ACTIONS(74),
    [anon_sym_endsWith] = ACTIONS(74),
    [anon_sym_lower] = ACTIONS(74),
    [anon_sym_upper] = ACTIONS(74),
    [anon_sym_title] = ACTIONS(74),
    [anon_sym_leftPad] = ACTIONS(74),
    [anon_sym_findReplace] = ACTIONS(74),
    [anon_sym_in] = ACTIONS(74),
    [anon_sym_index] = ACTIONS(74),
    [anon_sym_lastIndexOf] = ACTIONS(74),
    [anon_sym_countSubStr] = ACTIONS(74),
    [anon_sym_parseJson] = ACTIONS(74),
    [anon_sym_parseCsv] = ACTIONS(74),
    [anon_sym_parseHtml] = ACTIONS(74),
    [anon_sym_parseExcel] = ACTIONS(74),
    [anon_sym_readFile] = ACTIONS(74),
    [anon_sym_readFileBytes] = ACTIONS(74),
    [anon_sym_readTsvFile] = ACTIONS(74),
    [anon_sym_writeFile] = ACTIONS(74),
    [anon_sym_appendFile] = ACTIONS(74),
    [anon_sym_fileExists] = ACTIONS(74),
    [anon_sym_isDir] = ACTIONS(74),
    [anon_sym_isFile] = ACTIONS(74),
    [anon_sym_fileSize] = ACTIONS(74),
    [anon_sym_cp] = ACTIONS(74),
    [anon_sym_mv] = ACTIONS(74),
    [anon_sym_rm] = ACTIONS(74),
    [anon_sym_rmf] = ACTIONS(74),
    [anon_sym_mkdir] = ACTIONS(74),
    [anon_sym_mkdirp] = ACTIONS(74),
    [anon_sym_cd] = ACTIONS(74),
    [anon_sym_pwd] = ACTIONS(74),
    [anon_sym_tempFile] = ACTIONS(74),
    [anon_sym_tempFileExt] = ACTIONS(74),
    [anon_sym_tempDir] = ACTIONS(74),
    [anon_sym_lsDir] = ACTIONS(74),
    [anon_sym_files] = ACTIONS(74),
    [anon_sym_dirs] = ACTIONS(74),
    [anon_sym_absPath] = ACTIONS(74),
    [anon_sym_dirname] = ACTIONS(74),
    [anon_sym_basename] = ACTIONS(74),
    [anon_sym_ext] = ACTIONS(74),
    [anon_sym_stem] = ACTIONS(74),
    [anon_sym_isCmd] = ACTIONS(74),
    [anon_sym_hardLink] = ACTIONS(74),
    [anon_sym_sha256sum] = ACTIONS(74),
    [anon_sym_md5] = ACTIONS(74),
    [anon_sym_now] = ACTIONS(74),
    [anon_sym_date] = ACTIONS(74),
    [anon_sym_year] = ACTIONS(74),
    [anon_sym_month] = ACTIONS(74),
    [anon_sym_day] = ACTIONS(74),
    [anon_sym_hour] = ACTIONS(74),
    [anon_sym_minute] = ACTIONS(74),
    [anon_sym_dateFmt] = ACTIONS(74),
    [anon_sym_isoDateFmt] = ACTIONS(74),
    [anon_sym_isoDateTimeFmt] = ACTIONS(74),
    [anon_sym_isWeekend] = ACTIONS(74),
    [anon_sym_isWeekday] = ACTIONS(74),
    [anon_sym_dow] = ACTIONS(74),
    [anon_sym_addDays] = ACTIONS(74),
    [anon_sym_toUnixTime] = ACTIONS(74),
    [anon_sym_toUnixTimeMilli] = ACTIONS(74),
    [anon_sym_toUnixTimeMicro] = ACTIONS(74),
    [anon_sym_toUnixTimeNano] = ACTIONS(74),
    [anon_sym_fromUnixTime] = ACTIONS(74),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(74),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(74),
    [anon_sym_fromUnixTimeNano] = ACTIONS(74),
    [anon_sym_toOleDate] = ACTIONS(74),
    [anon_sym_fromOleDate] = ACTIONS(74),
    [anon_sym_utcToCst] = ACTIONS(74),
    [anon_sym_cstToUtc] = ACTIONS(74),
    [anon_sym_reMatch] = ACTIONS(74),
    [anon_sym_reFindAll] = ACTIONS(74),
    [anon_sym_reFindAllIndex] = ACTIONS(74),
    [anon_sym_reReplace] = ACTIONS(74),
    [anon_sym_reSplit] = ACTIONS(74),
    [anon_sym_just] = ACTIONS(74),
    [anon_sym_none] = ACTIONS(74),
    [anon_sym_isNone] = ACTIONS(74),
    [anon_sym_maybe] = ACTIONS(74),
    [anon_sym_bind] = ACTIONS(74),
    [anon_sym_psub] = ACTIONS(74),
    [anon_sym_typeof] = ACTIONS(74),
    [anon_sym_runtime] = ACTIONS(74),
    [anon_sym_hostname] = ACTIONS(74),
    [anon_sym_httpGet] = ACTIONS(74),
    [anon_sym_httpPost] = ACTIONS(74),
    [anon_sym_urlEncode] = ACTIONS(74),
    [anon_sym_base64encode] = ACTIONS(74),
    [anon_sym_base64decode] = ACTIONS(74),
    [anon_sym_utf8Str] = ACTIONS(74),
    [anon_sym_utf8Bytes] = ACTIONS(74),
    [anon_sym_get] = ACTIONS(74),
    [anon_sym_getDef] = ACTIONS(74),
    [anon_sym_set] = ACTIONS(74),
    [anon_sym_setd] = ACTIONS(74),
    [anon_sym_keys] = ACTIONS(74),
    [anon_sym_values] = ACTIONS(74),
    [anon_sym_keyValues] = ACTIONS(74),
    [anon_sym_all] = ACTIONS(74),
    [anon_sym_any] = ACTIONS(74),
    [anon_sym_cartesian] = ACTIONS(74),
    [anon_sym_groupBy] = ACTIONS(74),
    [anon_sym_listToDict] = ACTIONS(74),
    [anon_sym_repeat] = ACTIONS(74),
    [anon_sym_seq] = ACTIONS(74),
    [anon_sym_tab] = ACTIONS(74),
    [anon_sym_select] = ACTIONS(74),
    [anon_sym_exclude] = ACTIONS(74),
    [anon_sym_derive] = ACTIONS(74),
    [anon_sym_updateCol] = ACTIONS(74),
    [anon_sym_gridValues] = ACTIONS(74),
    [anon_sym_leftJoin] = ACTIONS(74),
    [anon_sym_outerJoin] = ACTIONS(74),
    [anon_sym_linearSearch] = ACTIONS(74),
    [anon_sym_linearSearchIndex] = ACTIONS(74),
    [anon_sym_binPaths] = ACTIONS(74),
    [anon_sym_wt] = ACTIONS(74),
    [anon_sym_tt] = ACTIONS(74),
    [anon_sym_ttFile] = ACTIONS(74),
    [anon_sym_uw] = ACTIONS(74),
    [anon_sym_tuw] = ACTIONS(74),
    [anon_sym_strCmp] = ACTIONS(74),
    [anon_sym_floatCmp] = ACTIONS(74),
    [anon_sym_versionSortCmp] = ACTIONS(74),
    [anon_sym_id] = ACTIONS(74),
    [anon_sym_2id] = ACTIONS(74),
    [anon_sym_3id] = ACTIONS(74),
    [anon_sym_2unpack] = ACTIONS(74),
    [anon_sym_2apply] = ACTIONS(74),
    [anon_sym_2each] = ACTIONS(74),
    [anon_sym_2tuple] = ACTIONS(74),
    [anon_sym_DOTs] = ACTIONS(74),
    [anon_sym_DOTb] = ACTIONS(74),
    [anon_sym_DOTdef] = ACTIONS(74),
    [anon_sym_DOTenv] = ACTIONS(74),
    [sym_string] = ACTIONS(80),
    [sym_format_string] = ACTIONS(80),
    [sym_single_quoted_string] = ACTIONS(80),
    [sym_path] = ACTIONS(80),
    [sym_datetime] = ACTIONS(80),
    [sym_float] = ACTIONS(80),
    [sym_integer] = ACTIONS(47),
    [sym_env_store] = ACTIONS(80),
    [sym_env_check] = ACTIONS(80),
    [sym_env_retrieve] = ACTIONS(47),
    [sym_positional] = ACTIONS(80),
    [sym_var_retrieve] = ACTIONS(80),
    [sym_var_store] = ACTIONS(80),
    [sym_slice_indexer] = ACTIONS(80),
    [sym_indexer] = ACTIONS(80),
    [sym_end_indexer] = ACTIONS(47),
    [sym_start_indexer] = ACTIONS(47),
    [sym_match_arm_dup] = ACTIONS(80),
    [sym_prefix_quote] = ACTIONS(47),
    [anon_sym_GT] = ACTIONS(83),
    [anon_sym_GT_GT] = ACTIONS(86),
    [anon_sym_2_GT] = ACTIONS(83),
    [anon_sym_2_GT_GT] = ACTIONS(83),
    [anon_sym_AMP_GT] = ACTIONS(83),
    [anon_sym_AMP_GT_GT] = ACTIONS(86),
    [anon_sym_LT] = ACTIONS(83),
    [anon_sym_LT_GT] = ACTIONS(86),
    [anon_sym_STAR] = ACTIONS(83),
    [anon_sym_STARb] = ACTIONS(86),
    [anon_sym_CARET] = ACTIONS(83),
    [anon_sym_CARETb] = ACTIONS(86),
    [anon_sym_SEMI] = ACTIONS(89),
    [anon_sym_BANG] = ACTIONS(92),
    [anon_sym_QMARK] = ACTIONS(89),
    [anon_sym_BANG_EQ] = ACTIONS(95),
    [anon_sym_LT_EQ] = ACTIONS(95),
    [anon_sym_GT_EQ] = ACTIONS(95),
    [anon_sym_AMP] = ACTIONS(98),
    [anon_sym_PIPE] = ACTIONS(101),
    [anon_sym_COMMA] = ACTIONS(101),
    [anon_sym_COLON] = ACTIONS(98),
  },
  [3] = {
    [sym__word] = STATE(8),
    [sym_list] = STATE(8),
    [sym_quotation] = STATE(8),
    [sym_dict] = STATE(8),
    [sym_grid] = STATE(8),
    [sym_boolean] = STATE(8),
    [sym_keyword] = STATE(8),
    [sym_type_keyword] = STATE(8),
    [sym_builtin] = STATE(8),
    [sym_redirect_operator] = STATE(8),
    [sym_execute_operator] = STATE(8),
    [sym_comparison_operator] = STATE(8),
    [sym_punctuation] = STATE(8),
    [aux_sym_source_file_repeat1] = STATE(8),
    [sym_identifier] = ACTIONS(104),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_RBRACE] = ACTIONS(106),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(108),
    [sym_format_string] = ACTIONS(108),
    [sym_single_quoted_string] = ACTIONS(108),
    [sym_path] = ACTIONS(108),
    [sym_datetime] = ACTIONS(108),
    [sym_float] = ACTIONS(108),
    [sym_integer] = ACTIONS(104),
    [sym_env_store] = ACTIONS(108),
    [sym_env_check] = ACTIONS(108),
    [sym_env_retrieve] = ACTIONS(104),
    [sym_positional] = ACTIONS(108),
    [sym_var_retrieve] = ACTIONS(108),
    [sym_var_store] = ACTIONS(108),
    [sym_slice_indexer] = ACTIONS(108),
    [sym_indexer] = ACTIONS(108),
    [sym_end_indexer] = ACTIONS(104),
    [sym_start_indexer] = ACTIONS(104),
    [sym_match_arm_dup] = ACTIONS(108),
    [sym_prefix_quote] = ACTIONS(104),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [4] = {
    [sym__word] = STATE(9),
    [sym_list] = STATE(9),
    [sym_quotation] = STATE(9),
    [sym_dict] = STATE(9),
    [sym_grid] = STATE(9),
    [sym_boolean] = STATE(9),
    [sym_keyword] = STATE(9),
    [sym_type_keyword] = STATE(9),
    [sym_builtin] = STATE(9),
    [sym_redirect_operator] = STATE(9),
    [sym_execute_operator] = STATE(9),
    [sym_comparison_operator] = STATE(9),
    [sym_punctuation] = STATE(9),
    [aux_sym_source_file_repeat1] = STATE(9),
    [sym_identifier] = ACTIONS(110),
    [anon_sym_LBRACK] = ACTIONS(112),
    [anon_sym_LPAREN] = ACTIONS(114),
    [anon_sym_LBRACE] = ACTIONS(116),
    [anon_sym_LBRACK_PIPE] = ACTIONS(118),
    [anon_sym_PIPE_RBRACK] = ACTIONS(120),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(122),
    [anon_sym_false] = ACTIONS(122),
    [anon_sym_def] = ACTIONS(124),
    [anon_sym_end] = ACTIONS(124),
    [anon_sym_if] = ACTIONS(124),
    [anon_sym_iff] = ACTIONS(124),
    [anon_sym_else] = ACTIONS(124),
    [anon_sym_else_STAR] = ACTIONS(126),
    [anon_sym_STARif] = ACTIONS(126),
    [anon_sym_loop] = ACTIONS(124),
    [anon_sym_match] = ACTIONS(124),
    [anon_sym_break] = ACTIONS(124),
    [anon_sym_continue] = ACTIONS(124),
    [anon_sym_soe] = ACTIONS(124),
    [anon_sym_not] = ACTIONS(124),
    [anon_sym_and] = ACTIONS(124),
    [anon_sym_or] = ACTIONS(124),
    [anon_sym_read] = ACTIONS(124),
    [anon_sym_str] = ACTIONS(124),
    [anon_sym_as] = ACTIONS(124),
    [anon_sym_type] = ACTIONS(124),
    [anon_sym_try] = ACTIONS(124),
    [anon_sym_fail] = ACTIONS(124),
    [anon_sym_pure] = ACTIONS(124),
    [anon_sym_VER] = ACTIONS(124),
    [anon_sym_x] = ACTIONS(124),
    [anon_sym_int] = ACTIONS(128),
    [anon_sym_float] = ACTIONS(128),
    [anon_sym_bool] = ACTIONS(128),
    [anon_sym_dup] = ACTIONS(130),
    [anon_sym_swap] = ACTIONS(130),
    [anon_sym_drop] = ACTIONS(130),
    [anon_sym_over] = ACTIONS(130),
    [anon_sym_pick] = ACTIONS(130),
    [anon_sym_rot] = ACTIONS(130),
    [anon_sym_DASHrot] = ACTIONS(130),
    [anon_sym_nip] = ACTIONS(130),
    [anon_sym_w] = ACTIONS(130),
    [anon_sym_wl] = ACTIONS(130),
    [anon_sym_we] = ACTIONS(130),
    [anon_sym_wle] = ACTIONS(130),
    [anon_sym_len] = ACTIONS(130),
    [anon_sym_args] = ACTIONS(130),
    [anon_sym_glob] = ACTIONS(130),
    [anon_sym_toFloat] = ACTIONS(130),
    [anon_sym_toInt] = ACTIONS(130),
    [anon_sym_toPath] = ACTIONS(130),
    [anon_sym_toDt] = ACTIONS(130),
    [anon_sym_toGrid] = ACTIONS(130),
    [anon_sym_toCsv] = ACTIONS(130),
    [anon_sym_toCsvCell] = ACTIONS(130),
    [anon_sym_exit] = ACTIONS(130),
    [anon_sym_prompt] = ACTIONS(130),
    [anon_sym_stdin] = ACTIONS(130),
    [anon_sym_COLON_COLON] = ACTIONS(132),
    [anon_sym_foldl] = ACTIONS(130),
    [anon_sym_map] = ACTIONS(130),
    [anon_sym_each] = ACTIONS(130),
    [anon_sym_eachWhile] = ACTIONS(130),
    [anon_sym_filter] = ACTIONS(130),
    [anon_sym_append] = ACTIONS(130),
    [anon_sym_extend] = ACTIONS(130),
    [anon_sym_concat] = ACTIONS(130),
    [anon_sym_reverse] = ACTIONS(130),
    [anon_sym_sort] = ACTIONS(130),
    [anon_sym_sortV] = ACTIONS(130),
    [anon_sym_sortBy] = ACTIONS(130),
    [anon_sym_sortByCmp] = ACTIONS(130),
    [anon_sym_uniq] = ACTIONS(130),
    [anon_sym_zip] = ACTIONS(130),
    [anon_sym_enumerate] = ACTIONS(130),
    [anon_sym_enumerateN] = ACTIONS(130),
    [anon_sym_chunk] = ACTIONS(130),
    [anon_sym_pop] = ACTIONS(130),
    [anon_sym_take] = ACTIONS(130),
    [anon_sym_takeWhile] = ACTIONS(130),
    [anon_sym_skip] = ACTIONS(130),
    [anon_sym_dropWhile] = ACTIONS(130),
    [anon_sym_nth] = ACTIONS(130),
    [anon_sym_insert] = ACTIONS(130),
    [anon_sym_setAt] = ACTIONS(130),
    [anon_sym_del] = ACTIONS(130),
    [anon_sym_sum] = ACTIONS(130),
    [anon_sym_max] = ACTIONS(130),
    [anon_sym_max2] = ACTIONS(130),
    [anon_sym_min] = ACTIONS(130),
    [anon_sym_min2] = ACTIONS(130),
    [anon_sym_abs] = ACTIONS(130),
    [anon_sym_inc] = ACTIONS(130),
    [anon_sym_mod] = ACTIONS(130),
    [anon_sym_floor] = ACTIONS(130),
    [anon_sym_ceil] = ACTIONS(130),
    [anon_sym_round] = ACTIONS(130),
    [anon_sym_lines] = ACTIONS(130),
    [anon_sym_unlines] = ACTIONS(130),
    [anon_sym_unlinesCrLf] = ACTIONS(130),
    [anon_sym_split] = ACTIONS(130),
    [anon_sym_wsplit] = ACTIONS(130),
    [anon_sym_tsplit] = ACTIONS(130),
    [anon_sym_join] = ACTIONS(130),
    [anon_sym_trim] = ACTIONS(130),
    [anon_sym_trimStart] = ACTIONS(130),
    [anon_sym_trimEnd] = ACTIONS(130),
    [anon_sym_startsWith] = ACTIONS(130),
    [anon_sym_endsWith] = ACTIONS(130),
    [anon_sym_lower] = ACTIONS(130),
    [anon_sym_upper] = ACTIONS(130),
    [anon_sym_title] = ACTIONS(130),
    [anon_sym_leftPad] = ACTIONS(130),
    [anon_sym_findReplace] = ACTIONS(130),
    [anon_sym_in] = ACTIONS(130),
    [anon_sym_index] = ACTIONS(130),
    [anon_sym_lastIndexOf] = ACTIONS(130),
    [anon_sym_countSubStr] = ACTIONS(130),
    [anon_sym_parseJson] = ACTIONS(130),
    [anon_sym_parseCsv] = ACTIONS(130),
    [anon_sym_parseHtml] = ACTIONS(130),
    [anon_sym_parseExcel] = ACTIONS(130),
    [anon_sym_readFile] = ACTIONS(130),
    [anon_sym_readFileBytes] = ACTIONS(130),
    [anon_sym_readTsvFile] = ACTIONS(130),
    [anon_sym_writeFile] = ACTIONS(130),
    [anon_sym_appendFile] = ACTIONS(130),
    [anon_sym_fileExists] = ACTIONS(130),
    [anon_sym_isDir] = ACTIONS(130),
    [anon_sym_isFile] = ACTIONS(130),
    [anon_sym_fileSize] = ACTIONS(130),
    [anon_sym_cp] = ACTIONS(130),
    [anon_sym_mv] = ACTIONS(130),
    [anon_sym_rm] = ACTIONS(130),
    [anon_sym_rmf] = ACTIONS(130),
    [anon_sym_mkdir] = ACTIONS(130),
    [anon_sym_mkdirp] = ACTIONS(130),
    [anon_sym_cd] = ACTIONS(130),
    [anon_sym_pwd] = ACTIONS(130),
    [anon_sym_tempFile] = ACTIONS(130),
    [anon_sym_tempFileExt] = ACTIONS(130),
    [anon_sym_tempDir] = ACTIONS(130),
    [anon_sym_lsDir] = ACTIONS(130),
    [anon_sym_files] = ACTIONS(130),
    [anon_sym_dirs] = ACTIONS(130),
    [anon_sym_absPath] = ACTIONS(130),
    [anon_sym_dirname] = ACTIONS(130),
    [anon_sym_basename] = ACTIONS(130),
    [anon_sym_ext] = ACTIONS(130),
    [anon_sym_stem] = ACTIONS(130),
    [anon_sym_isCmd] = ACTIONS(130),
    [anon_sym_hardLink] = ACTIONS(130),
    [anon_sym_sha256sum] = ACTIONS(130),
    [anon_sym_md5] = ACTIONS(130),
    [anon_sym_now] = ACTIONS(130),
    [anon_sym_date] = ACTIONS(130),
    [anon_sym_year] = ACTIONS(130),
    [anon_sym_month] = ACTIONS(130),
    [anon_sym_day] = ACTIONS(130),
    [anon_sym_hour] = ACTIONS(130),
    [anon_sym_minute] = ACTIONS(130),
    [anon_sym_dateFmt] = ACTIONS(130),
    [anon_sym_isoDateFmt] = ACTIONS(130),
    [anon_sym_isoDateTimeFmt] = ACTIONS(130),
    [anon_sym_isWeekend] = ACTIONS(130),
    [anon_sym_isWeekday] = ACTIONS(130),
    [anon_sym_dow] = ACTIONS(130),
    [anon_sym_addDays] = ACTIONS(130),
    [anon_sym_toUnixTime] = ACTIONS(130),
    [anon_sym_toUnixTimeMilli] = ACTIONS(130),
    [anon_sym_toUnixTimeMicro] = ACTIONS(130),
    [anon_sym_toUnixTimeNano] = ACTIONS(130),
    [anon_sym_fromUnixTime] = ACTIONS(130),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(130),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(130),
    [anon_sym_fromUnixTimeNano] = ACTIONS(130),
    [anon_sym_toOleDate] = ACTIONS(130),
    [anon_sym_fromOleDate] = ACTIONS(130),
    [anon_sym_utcToCst] = ACTIONS(130),
    [anon_sym_cstToUtc] = ACTIONS(130),
    [anon_sym_reMatch] = ACTIONS(130),
    [anon_sym_reFindAll] = ACTIONS(130),
    [anon_sym_reFindAllIndex] = ACTIONS(130),
    [anon_sym_reReplace] = ACTIONS(130),
    [anon_sym_reSplit] = ACTIONS(130),
    [anon_sym_just] = ACTIONS(130),
    [anon_sym_none] = ACTIONS(130),
    [anon_sym_isNone] = ACTIONS(130),
    [anon_sym_maybe] = ACTIONS(130),
    [anon_sym_bind] = ACTIONS(130),
    [anon_sym_psub] = ACTIONS(130),
    [anon_sym_typeof] = ACTIONS(130),
    [anon_sym_runtime] = ACTIONS(130),
    [anon_sym_hostname] = ACTIONS(130),
    [anon_sym_httpGet] = ACTIONS(130),
    [anon_sym_httpPost] = ACTIONS(130),
    [anon_sym_urlEncode] = ACTIONS(130),
    [anon_sym_base64encode] = ACTIONS(130),
    [anon_sym_base64decode] = ACTIONS(130),
    [anon_sym_utf8Str] = ACTIONS(130),
    [anon_sym_utf8Bytes] = ACTIONS(130),
    [anon_sym_get] = ACTIONS(130),
    [anon_sym_getDef] = ACTIONS(130),
    [anon_sym_set] = ACTIONS(130),
    [anon_sym_setd] = ACTIONS(130),
    [anon_sym_keys] = ACTIONS(130),
    [anon_sym_values] = ACTIONS(130),
    [anon_sym_keyValues] = ACTIONS(130),
    [anon_sym_all] = ACTIONS(130),
    [anon_sym_any] = ACTIONS(130),
    [anon_sym_cartesian] = ACTIONS(130),
    [anon_sym_groupBy] = ACTIONS(130),
    [anon_sym_listToDict] = ACTIONS(130),
    [anon_sym_repeat] = ACTIONS(130),
    [anon_sym_seq] = ACTIONS(130),
    [anon_sym_tab] = ACTIONS(130),
    [anon_sym_select] = ACTIONS(130),
    [anon_sym_exclude] = ACTIONS(130),
    [anon_sym_derive] = ACTIONS(130),
    [anon_sym_updateCol] = ACTIONS(130),
    [anon_sym_gridValues] = ACTIONS(130),
    [anon_sym_leftJoin] = ACTIONS(130),
    [anon_sym_outerJoin] = ACTIONS(130),
    [anon_sym_linearSearch] = ACTIONS(130),
    [anon_sym_linearSearchIndex] = ACTIONS(130),
    [anon_sym_binPaths] = ACTIONS(130),
    [anon_sym_wt] = ACTIONS(130),
    [anon_sym_tt] = ACTIONS(130),
    [anon_sym_ttFile] = ACTIONS(130),
    [anon_sym_uw] = ACTIONS(130),
    [anon_sym_tuw] = ACTIONS(130),
    [anon_sym_strCmp] = ACTIONS(130),
    [anon_sym_floatCmp] = ACTIONS(130),
    [anon_sym_versionSortCmp] = ACTIONS(130),
    [anon_sym_id] = ACTIONS(130),
    [anon_sym_2id] = ACTIONS(130),
    [anon_sym_3id] = ACTIONS(130),
    [anon_sym_2unpack] = ACTIONS(130),
    [anon_sym_2apply] = ACTIONS(130),
    [anon_sym_2each] = ACTIONS(130),
    [anon_sym_2tuple] = ACTIONS(130),
    [anon_sym_DOTs] = ACTIONS(130),
    [anon_sym_DOTb] = ACTIONS(130),
    [anon_sym_DOTdef] = ACTIONS(130),
    [anon_sym_DOTenv] = ACTIONS(130),
    [sym_string] = ACTIONS(134),
    [sym_format_string] = ACTIONS(134),
    [sym_single_quoted_string] = ACTIONS(134),
    [sym_path] = ACTIONS(134),
    [sym_datetime] = ACTIONS(134),
    [sym_float] = ACTIONS(134),
    [sym_integer] = ACTIONS(110),
    [sym_env_store] = ACTIONS(134),
    [sym_env_check] = ACTIONS(134),
    [sym_env_retrieve] = ACTIONS(110),
    [sym_positional] = ACTIONS(134),
    [sym_var_retrieve] = ACTIONS(134),
    [sym_var_store] = ACTIONS(134),
    [sym_slice_indexer] = ACTIONS(134),
    [sym_indexer] = ACTIONS(134),
    [sym_end_indexer] = ACTIONS(110),
    [sym_start_indexer] = ACTIONS(110),
    [sym_match_arm_dup] = ACTIONS(134),
    [sym_prefix_quote] = ACTIONS(110),
    [anon_sym_GT] = ACTIONS(136),
    [anon_sym_GT_GT] = ACTIONS(138),
    [anon_sym_2_GT] = ACTIONS(136),
    [anon_sym_2_GT_GT] = ACTIONS(136),
    [anon_sym_AMP_GT] = ACTIONS(136),
    [anon_sym_AMP_GT_GT] = ACTIONS(138),
    [anon_sym_LT] = ACTIONS(136),
    [anon_sym_LT_GT] = ACTIONS(138),
    [anon_sym_STAR] = ACTIONS(136),
    [anon_sym_STARb] = ACTIONS(138),
    [anon_sym_CARET] = ACTIONS(136),
    [anon_sym_CARETb] = ACTIONS(138),
    [anon_sym_SEMI] = ACTIONS(140),
    [anon_sym_BANG] = ACTIONS(142),
    [anon_sym_QMARK] = ACTIONS(140),
    [anon_sym_BANG_EQ] = ACTIONS(144),
    [anon_sym_LT_EQ] = ACTIONS(144),
    [anon_sym_GT_EQ] = ACTIONS(144),
    [anon_sym_AMP] = ACTIONS(146),
    [anon_sym_PIPE] = ACTIONS(146),
    [anon_sym_COMMA] = ACTIONS(148),
    [anon_sym_COLON] = ACTIONS(146),
  },
  [5] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(150),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [6] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_RBRACK] = ACTIONS(156),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [7] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_RPAREN] = ACTIONS(158),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [8] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_RBRACE] = ACTIONS(160),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [9] = {
    [sym__word] = STATE(12),
    [sym_list] = STATE(12),
    [sym_quotation] = STATE(12),
    [sym_dict] = STATE(12),
    [sym_grid] = STATE(12),
    [sym_boolean] = STATE(12),
    [sym_keyword] = STATE(12),
    [sym_type_keyword] = STATE(12),
    [sym_builtin] = STATE(12),
    [sym_redirect_operator] = STATE(12),
    [sym_execute_operator] = STATE(12),
    [sym_comparison_operator] = STATE(12),
    [sym_punctuation] = STATE(12),
    [aux_sym_source_file_repeat1] = STATE(12),
    [sym_identifier] = ACTIONS(162),
    [anon_sym_LBRACK] = ACTIONS(112),
    [anon_sym_LPAREN] = ACTIONS(114),
    [anon_sym_LBRACE] = ACTIONS(116),
    [anon_sym_LBRACK_PIPE] = ACTIONS(118),
    [anon_sym_PIPE_RBRACK] = ACTIONS(164),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(122),
    [anon_sym_false] = ACTIONS(122),
    [anon_sym_def] = ACTIONS(124),
    [anon_sym_end] = ACTIONS(124),
    [anon_sym_if] = ACTIONS(124),
    [anon_sym_iff] = ACTIONS(124),
    [anon_sym_else] = ACTIONS(124),
    [anon_sym_else_STAR] = ACTIONS(126),
    [anon_sym_STARif] = ACTIONS(126),
    [anon_sym_loop] = ACTIONS(124),
    [anon_sym_match] = ACTIONS(124),
    [anon_sym_break] = ACTIONS(124),
    [anon_sym_continue] = ACTIONS(124),
    [anon_sym_soe] = ACTIONS(124),
    [anon_sym_not] = ACTIONS(124),
    [anon_sym_and] = ACTIONS(124),
    [anon_sym_or] = ACTIONS(124),
    [anon_sym_read] = ACTIONS(124),
    [anon_sym_str] = ACTIONS(124),
    [anon_sym_as] = ACTIONS(124),
    [anon_sym_type] = ACTIONS(124),
    [anon_sym_try] = ACTIONS(124),
    [anon_sym_fail] = ACTIONS(124),
    [anon_sym_pure] = ACTIONS(124),
    [anon_sym_VER] = ACTIONS(124),
    [anon_sym_x] = ACTIONS(124),
    [anon_sym_int] = ACTIONS(128),
    [anon_sym_float] = ACTIONS(128),
    [anon_sym_bool] = ACTIONS(128),
    [anon_sym_dup] = ACTIONS(130),
    [anon_sym_swap] = ACTIONS(130),
    [anon_sym_drop] = ACTIONS(130),
    [anon_sym_over] = ACTIONS(130),
    [anon_sym_pick] = ACTIONS(130),
    [anon_sym_rot] = ACTIONS(130),
    [anon_sym_DASHrot] = ACTIONS(130),
    [anon_sym_nip] = ACTIONS(130),
    [anon_sym_w] = ACTIONS(130),
    [anon_sym_wl] = ACTIONS(130),
    [anon_sym_we] = ACTIONS(130),
    [anon_sym_wle] = ACTIONS(130),
    [anon_sym_len] = ACTIONS(130),
    [anon_sym_args] = ACTIONS(130),
    [anon_sym_glob] = ACTIONS(130),
    [anon_sym_toFloat] = ACTIONS(130),
    [anon_sym_toInt] = ACTIONS(130),
    [anon_sym_toPath] = ACTIONS(130),
    [anon_sym_toDt] = ACTIONS(130),
    [anon_sym_toGrid] = ACTIONS(130),
    [anon_sym_toCsv] = ACTIONS(130),
    [anon_sym_toCsvCell] = ACTIONS(130),
    [anon_sym_exit] = ACTIONS(130),
    [anon_sym_prompt] = ACTIONS(130),
    [anon_sym_stdin] = ACTIONS(130),
    [anon_sym_COLON_COLON] = ACTIONS(132),
    [anon_sym_foldl] = ACTIONS(130),
    [anon_sym_map] = ACTIONS(130),
    [anon_sym_each] = ACTIONS(130),
    [anon_sym_eachWhile] = ACTIONS(130),
    [anon_sym_filter] = ACTIONS(130),
    [anon_sym_append] = ACTIONS(130),
    [anon_sym_extend] = ACTIONS(130),
    [anon_sym_concat] = ACTIONS(130),
    [anon_sym_reverse] = ACTIONS(130),
    [anon_sym_sort] = ACTIONS(130),
    [anon_sym_sortV] = ACTIONS(130),
    [anon_sym_sortBy] = ACTIONS(130),
    [anon_sym_sortByCmp] = ACTIONS(130),
    [anon_sym_uniq] = ACTIONS(130),
    [anon_sym_zip] = ACTIONS(130),
    [anon_sym_enumerate] = ACTIONS(130),
    [anon_sym_enumerateN] = ACTIONS(130),
    [anon_sym_chunk] = ACTIONS(130),
    [anon_sym_pop] = ACTIONS(130),
    [anon_sym_take] = ACTIONS(130),
    [anon_sym_takeWhile] = ACTIONS(130),
    [anon_sym_skip] = ACTIONS(130),
    [anon_sym_dropWhile] = ACTIONS(130),
    [anon_sym_nth] = ACTIONS(130),
    [anon_sym_insert] = ACTIONS(130),
    [anon_sym_setAt] = ACTIONS(130),
    [anon_sym_del] = ACTIONS(130),
    [anon_sym_sum] = ACTIONS(130),
    [anon_sym_max] = ACTIONS(130),
    [anon_sym_max2] = ACTIONS(130),
    [anon_sym_min] = ACTIONS(130),
    [anon_sym_min2] = ACTIONS(130),
    [anon_sym_abs] = ACTIONS(130),
    [anon_sym_inc] = ACTIONS(130),
    [anon_sym_mod] = ACTIONS(130),
    [anon_sym_floor] = ACTIONS(130),
    [anon_sym_ceil] = ACTIONS(130),
    [anon_sym_round] = ACTIONS(130),
    [anon_sym_lines] = ACTIONS(130),
    [anon_sym_unlines] = ACTIONS(130),
    [anon_sym_unlinesCrLf] = ACTIONS(130),
    [anon_sym_split] = ACTIONS(130),
    [anon_sym_wsplit] = ACTIONS(130),
    [anon_sym_tsplit] = ACTIONS(130),
    [anon_sym_join] = ACTIONS(130),
    [anon_sym_trim] = ACTIONS(130),
    [anon_sym_trimStart] = ACTIONS(130),
    [anon_sym_trimEnd] = ACTIONS(130),
    [anon_sym_startsWith] = ACTIONS(130),
    [anon_sym_endsWith] = ACTIONS(130),
    [anon_sym_lower] = ACTIONS(130),
    [anon_sym_upper] = ACTIONS(130),
    [anon_sym_title] = ACTIONS(130),
    [anon_sym_leftPad] = ACTIONS(130),
    [anon_sym_findReplace] = ACTIONS(130),
    [anon_sym_in] = ACTIONS(130),
    [anon_sym_index] = ACTIONS(130),
    [anon_sym_lastIndexOf] = ACTIONS(130),
    [anon_sym_countSubStr] = ACTIONS(130),
    [anon_sym_parseJson] = ACTIONS(130),
    [anon_sym_parseCsv] = ACTIONS(130),
    [anon_sym_parseHtml] = ACTIONS(130),
    [anon_sym_parseExcel] = ACTIONS(130),
    [anon_sym_readFile] = ACTIONS(130),
    [anon_sym_readFileBytes] = ACTIONS(130),
    [anon_sym_readTsvFile] = ACTIONS(130),
    [anon_sym_writeFile] = ACTIONS(130),
    [anon_sym_appendFile] = ACTIONS(130),
    [anon_sym_fileExists] = ACTIONS(130),
    [anon_sym_isDir] = ACTIONS(130),
    [anon_sym_isFile] = ACTIONS(130),
    [anon_sym_fileSize] = ACTIONS(130),
    [anon_sym_cp] = ACTIONS(130),
    [anon_sym_mv] = ACTIONS(130),
    [anon_sym_rm] = ACTIONS(130),
    [anon_sym_rmf] = ACTIONS(130),
    [anon_sym_mkdir] = ACTIONS(130),
    [anon_sym_mkdirp] = ACTIONS(130),
    [anon_sym_cd] = ACTIONS(130),
    [anon_sym_pwd] = ACTIONS(130),
    [anon_sym_tempFile] = ACTIONS(130),
    [anon_sym_tempFileExt] = ACTIONS(130),
    [anon_sym_tempDir] = ACTIONS(130),
    [anon_sym_lsDir] = ACTIONS(130),
    [anon_sym_files] = ACTIONS(130),
    [anon_sym_dirs] = ACTIONS(130),
    [anon_sym_absPath] = ACTIONS(130),
    [anon_sym_dirname] = ACTIONS(130),
    [anon_sym_basename] = ACTIONS(130),
    [anon_sym_ext] = ACTIONS(130),
    [anon_sym_stem] = ACTIONS(130),
    [anon_sym_isCmd] = ACTIONS(130),
    [anon_sym_hardLink] = ACTIONS(130),
    [anon_sym_sha256sum] = ACTIONS(130),
    [anon_sym_md5] = ACTIONS(130),
    [anon_sym_now] = ACTIONS(130),
    [anon_sym_date] = ACTIONS(130),
    [anon_sym_year] = ACTIONS(130),
    [anon_sym_month] = ACTIONS(130),
    [anon_sym_day] = ACTIONS(130),
    [anon_sym_hour] = ACTIONS(130),
    [anon_sym_minute] = ACTIONS(130),
    [anon_sym_dateFmt] = ACTIONS(130),
    [anon_sym_isoDateFmt] = ACTIONS(130),
    [anon_sym_isoDateTimeFmt] = ACTIONS(130),
    [anon_sym_isWeekend] = ACTIONS(130),
    [anon_sym_isWeekday] = ACTIONS(130),
    [anon_sym_dow] = ACTIONS(130),
    [anon_sym_addDays] = ACTIONS(130),
    [anon_sym_toUnixTime] = ACTIONS(130),
    [anon_sym_toUnixTimeMilli] = ACTIONS(130),
    [anon_sym_toUnixTimeMicro] = ACTIONS(130),
    [anon_sym_toUnixTimeNano] = ACTIONS(130),
    [anon_sym_fromUnixTime] = ACTIONS(130),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(130),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(130),
    [anon_sym_fromUnixTimeNano] = ACTIONS(130),
    [anon_sym_toOleDate] = ACTIONS(130),
    [anon_sym_fromOleDate] = ACTIONS(130),
    [anon_sym_utcToCst] = ACTIONS(130),
    [anon_sym_cstToUtc] = ACTIONS(130),
    [anon_sym_reMatch] = ACTIONS(130),
    [anon_sym_reFindAll] = ACTIONS(130),
    [anon_sym_reFindAllIndex] = ACTIONS(130),
    [anon_sym_reReplace] = ACTIONS(130),
    [anon_sym_reSplit] = ACTIONS(130),
    [anon_sym_just] = ACTIONS(130),
    [anon_sym_none] = ACTIONS(130),
    [anon_sym_isNone] = ACTIONS(130),
    [anon_sym_maybe] = ACTIONS(130),
    [anon_sym_bind] = ACTIONS(130),
    [anon_sym_psub] = ACTIONS(130),
    [anon_sym_typeof] = ACTIONS(130),
    [anon_sym_runtime] = ACTIONS(130),
    [anon_sym_hostname] = ACTIONS(130),
    [anon_sym_httpGet] = ACTIONS(130),
    [anon_sym_httpPost] = ACTIONS(130),
    [anon_sym_urlEncode] = ACTIONS(130),
    [anon_sym_base64encode] = ACTIONS(130),
    [anon_sym_base64decode] = ACTIONS(130),
    [anon_sym_utf8Str] = ACTIONS(130),
    [anon_sym_utf8Bytes] = ACTIONS(130),
    [anon_sym_get] = ACTIONS(130),
    [anon_sym_getDef] = ACTIONS(130),
    [anon_sym_set] = ACTIONS(130),
    [anon_sym_setd] = ACTIONS(130),
    [anon_sym_keys] = ACTIONS(130),
    [anon_sym_values] = ACTIONS(130),
    [anon_sym_keyValues] = ACTIONS(130),
    [anon_sym_all] = ACTIONS(130),
    [anon_sym_any] = ACTIONS(130),
    [anon_sym_cartesian] = ACTIONS(130),
    [anon_sym_groupBy] = ACTIONS(130),
    [anon_sym_listToDict] = ACTIONS(130),
    [anon_sym_repeat] = ACTIONS(130),
    [anon_sym_seq] = ACTIONS(130),
    [anon_sym_tab] = ACTIONS(130),
    [anon_sym_select] = ACTIONS(130),
    [anon_sym_exclude] = ACTIONS(130),
    [anon_sym_derive] = ACTIONS(130),
    [anon_sym_updateCol] = ACTIONS(130),
    [anon_sym_gridValues] = ACTIONS(130),
    [anon_sym_leftJoin] = ACTIONS(130),
    [anon_sym_outerJoin] = ACTIONS(130),
    [anon_sym_linearSearch] = ACTIONS(130),
    [anon_sym_linearSearchIndex] = ACTIONS(130),
    [anon_sym_binPaths] = ACTIONS(130),
    [anon_sym_wt] = ACTIONS(130),
    [anon_sym_tt] = ACTIONS(130),
    [anon_sym_ttFile] = ACTIONS(130),
    [anon_sym_uw] = ACTIONS(130),
    [anon_sym_tuw] = ACTIONS(130),
    [anon_sym_strCmp] = ACTIONS(130),
    [anon_sym_floatCmp] = ACTIONS(130),
    [anon_sym_versionSortCmp] = ACTIONS(130),
    [anon_sym_id] = ACTIONS(130),
    [anon_sym_2id] = ACTIONS(130),
    [anon_sym_3id] = ACTIONS(130),
    [anon_sym_2unpack] = ACTIONS(130),
    [anon_sym_2apply] = ACTIONS(130),
    [anon_sym_2each] = ACTIONS(130),
    [anon_sym_2tuple] = ACTIONS(130),
    [anon_sym_DOTs] = ACTIONS(130),
    [anon_sym_DOTb] = ACTIONS(130),
    [anon_sym_DOTdef] = ACTIONS(130),
    [anon_sym_DOTenv] = ACTIONS(130),
    [sym_string] = ACTIONS(166),
    [sym_format_string] = ACTIONS(166),
    [sym_single_quoted_string] = ACTIONS(166),
    [sym_path] = ACTIONS(166),
    [sym_datetime] = ACTIONS(166),
    [sym_float] = ACTIONS(166),
    [sym_integer] = ACTIONS(162),
    [sym_env_store] = ACTIONS(166),
    [sym_env_check] = ACTIONS(166),
    [sym_env_retrieve] = ACTIONS(162),
    [sym_positional] = ACTIONS(166),
    [sym_var_retrieve] = ACTIONS(166),
    [sym_var_store] = ACTIONS(166),
    [sym_slice_indexer] = ACTIONS(166),
    [sym_indexer] = ACTIONS(166),
    [sym_end_indexer] = ACTIONS(162),
    [sym_start_indexer] = ACTIONS(162),
    [sym_match_arm_dup] = ACTIONS(166),
    [sym_prefix_quote] = ACTIONS(162),
    [anon_sym_GT] = ACTIONS(136),
    [anon_sym_GT_GT] = ACTIONS(138),
    [anon_sym_2_GT] = ACTIONS(136),
    [anon_sym_2_GT_GT] = ACTIONS(136),
    [anon_sym_AMP_GT] = ACTIONS(136),
    [anon_sym_AMP_GT_GT] = ACTIONS(138),
    [anon_sym_LT] = ACTIONS(136),
    [anon_sym_LT_GT] = ACTIONS(138),
    [anon_sym_STAR] = ACTIONS(136),
    [anon_sym_STARb] = ACTIONS(138),
    [anon_sym_CARET] = ACTIONS(136),
    [anon_sym_CARETb] = ACTIONS(138),
    [anon_sym_SEMI] = ACTIONS(140),
    [anon_sym_BANG] = ACTIONS(142),
    [anon_sym_QMARK] = ACTIONS(140),
    [anon_sym_BANG_EQ] = ACTIONS(144),
    [anon_sym_LT_EQ] = ACTIONS(144),
    [anon_sym_GT_EQ] = ACTIONS(144),
    [anon_sym_AMP] = ACTIONS(146),
    [anon_sym_PIPE] = ACTIONS(146),
    [anon_sym_COMMA] = ACTIONS(148),
    [anon_sym_COLON] = ACTIONS(146),
  },
  [10] = {
    [sym__word] = STATE(6),
    [sym_list] = STATE(6),
    [sym_quotation] = STATE(6),
    [sym_dict] = STATE(6),
    [sym_grid] = STATE(6),
    [sym_boolean] = STATE(6),
    [sym_keyword] = STATE(6),
    [sym_type_keyword] = STATE(6),
    [sym_builtin] = STATE(6),
    [sym_redirect_operator] = STATE(6),
    [sym_execute_operator] = STATE(6),
    [sym_comparison_operator] = STATE(6),
    [sym_punctuation] = STATE(6),
    [aux_sym_source_file_repeat1] = STATE(6),
    [sym_identifier] = ACTIONS(168),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_RBRACK] = ACTIONS(170),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(172),
    [sym_format_string] = ACTIONS(172),
    [sym_single_quoted_string] = ACTIONS(172),
    [sym_path] = ACTIONS(172),
    [sym_datetime] = ACTIONS(172),
    [sym_float] = ACTIONS(172),
    [sym_integer] = ACTIONS(168),
    [sym_env_store] = ACTIONS(172),
    [sym_env_check] = ACTIONS(172),
    [sym_env_retrieve] = ACTIONS(168),
    [sym_positional] = ACTIONS(172),
    [sym_var_retrieve] = ACTIONS(172),
    [sym_var_store] = ACTIONS(172),
    [sym_slice_indexer] = ACTIONS(172),
    [sym_indexer] = ACTIONS(172),
    [sym_end_indexer] = ACTIONS(168),
    [sym_start_indexer] = ACTIONS(168),
    [sym_match_arm_dup] = ACTIONS(172),
    [sym_prefix_quote] = ACTIONS(168),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [11] = {
    [sym__word] = STATE(7),
    [sym_list] = STATE(7),
    [sym_quotation] = STATE(7),
    [sym_dict] = STATE(7),
    [sym_grid] = STATE(7),
    [sym_boolean] = STATE(7),
    [sym_keyword] = STATE(7),
    [sym_type_keyword] = STATE(7),
    [sym_builtin] = STATE(7),
    [sym_redirect_operator] = STATE(7),
    [sym_execute_operator] = STATE(7),
    [sym_comparison_operator] = STATE(7),
    [sym_punctuation] = STATE(7),
    [aux_sym_source_file_repeat1] = STATE(7),
    [sym_identifier] = ACTIONS(174),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_RPAREN] = ACTIONS(176),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(178),
    [sym_format_string] = ACTIONS(178),
    [sym_single_quoted_string] = ACTIONS(178),
    [sym_path] = ACTIONS(178),
    [sym_datetime] = ACTIONS(178),
    [sym_float] = ACTIONS(178),
    [sym_integer] = ACTIONS(174),
    [sym_env_store] = ACTIONS(178),
    [sym_env_check] = ACTIONS(178),
    [sym_env_retrieve] = ACTIONS(174),
    [sym_positional] = ACTIONS(178),
    [sym_var_retrieve] = ACTIONS(178),
    [sym_var_store] = ACTIONS(178),
    [sym_slice_indexer] = ACTIONS(178),
    [sym_indexer] = ACTIONS(178),
    [sym_end_indexer] = ACTIONS(174),
    [sym_start_indexer] = ACTIONS(174),
    [sym_match_arm_dup] = ACTIONS(178),
    [sym_prefix_quote] = ACTIONS(174),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [12] = {
    [sym__word] = STATE(12),
    [sym_list] = STATE(12),
    [sym_quotation] = STATE(12),
    [sym_dict] = STATE(12),
    [sym_grid] = STATE(12),
    [sym_boolean] = STATE(12),
    [sym_keyword] = STATE(12),
    [sym_type_keyword] = STATE(12),
    [sym_builtin] = STATE(12),
    [sym_redirect_operator] = STATE(12),
    [sym_execute_operator] = STATE(12),
    [sym_comparison_operator] = STATE(12),
    [sym_punctuation] = STATE(12),
    [aux_sym_source_file_repeat1] = STATE(12),
    [sym_identifier] = ACTIONS(180),
    [anon_sym_LBRACK] = ACTIONS(183),
    [anon_sym_LPAREN] = ACTIONS(186),
    [anon_sym_LBRACE] = ACTIONS(189),
    [anon_sym_LBRACK_PIPE] = ACTIONS(192),
    [anon_sym_PIPE_RBRACK] = ACTIONS(45),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(195),
    [anon_sym_false] = ACTIONS(195),
    [anon_sym_def] = ACTIONS(198),
    [anon_sym_end] = ACTIONS(198),
    [anon_sym_if] = ACTIONS(198),
    [anon_sym_iff] = ACTIONS(198),
    [anon_sym_else] = ACTIONS(198),
    [anon_sym_else_STAR] = ACTIONS(201),
    [anon_sym_STARif] = ACTIONS(201),
    [anon_sym_loop] = ACTIONS(198),
    [anon_sym_match] = ACTIONS(198),
    [anon_sym_break] = ACTIONS(198),
    [anon_sym_continue] = ACTIONS(198),
    [anon_sym_soe] = ACTIONS(198),
    [anon_sym_not] = ACTIONS(198),
    [anon_sym_and] = ACTIONS(198),
    [anon_sym_or] = ACTIONS(198),
    [anon_sym_read] = ACTIONS(198),
    [anon_sym_str] = ACTIONS(198),
    [anon_sym_as] = ACTIONS(198),
    [anon_sym_type] = ACTIONS(198),
    [anon_sym_try] = ACTIONS(198),
    [anon_sym_fail] = ACTIONS(198),
    [anon_sym_pure] = ACTIONS(198),
    [anon_sym_VER] = ACTIONS(198),
    [anon_sym_x] = ACTIONS(198),
    [anon_sym_int] = ACTIONS(204),
    [anon_sym_float] = ACTIONS(204),
    [anon_sym_bool] = ACTIONS(204),
    [anon_sym_dup] = ACTIONS(207),
    [anon_sym_swap] = ACTIONS(207),
    [anon_sym_drop] = ACTIONS(207),
    [anon_sym_over] = ACTIONS(207),
    [anon_sym_pick] = ACTIONS(207),
    [anon_sym_rot] = ACTIONS(207),
    [anon_sym_DASHrot] = ACTIONS(207),
    [anon_sym_nip] = ACTIONS(207),
    [anon_sym_w] = ACTIONS(207),
    [anon_sym_wl] = ACTIONS(207),
    [anon_sym_we] = ACTIONS(207),
    [anon_sym_wle] = ACTIONS(207),
    [anon_sym_len] = ACTIONS(207),
    [anon_sym_args] = ACTIONS(207),
    [anon_sym_glob] = ACTIONS(207),
    [anon_sym_toFloat] = ACTIONS(207),
    [anon_sym_toInt] = ACTIONS(207),
    [anon_sym_toPath] = ACTIONS(207),
    [anon_sym_toDt] = ACTIONS(207),
    [anon_sym_toGrid] = ACTIONS(207),
    [anon_sym_toCsv] = ACTIONS(207),
    [anon_sym_toCsvCell] = ACTIONS(207),
    [anon_sym_exit] = ACTIONS(207),
    [anon_sym_prompt] = ACTIONS(207),
    [anon_sym_stdin] = ACTIONS(207),
    [anon_sym_COLON_COLON] = ACTIONS(210),
    [anon_sym_foldl] = ACTIONS(207),
    [anon_sym_map] = ACTIONS(207),
    [anon_sym_each] = ACTIONS(207),
    [anon_sym_eachWhile] = ACTIONS(207),
    [anon_sym_filter] = ACTIONS(207),
    [anon_sym_append] = ACTIONS(207),
    [anon_sym_extend] = ACTIONS(207),
    [anon_sym_concat] = ACTIONS(207),
    [anon_sym_reverse] = ACTIONS(207),
    [anon_sym_sort] = ACTIONS(207),
    [anon_sym_sortV] = ACTIONS(207),
    [anon_sym_sortBy] = ACTIONS(207),
    [anon_sym_sortByCmp] = ACTIONS(207),
    [anon_sym_uniq] = ACTIONS(207),
    [anon_sym_zip] = ACTIONS(207),
    [anon_sym_enumerate] = ACTIONS(207),
    [anon_sym_enumerateN] = ACTIONS(207),
    [anon_sym_chunk] = ACTIONS(207),
    [anon_sym_pop] = ACTIONS(207),
    [anon_sym_take] = ACTIONS(207),
    [anon_sym_takeWhile] = ACTIONS(207),
    [anon_sym_skip] = ACTIONS(207),
    [anon_sym_dropWhile] = ACTIONS(207),
    [anon_sym_nth] = ACTIONS(207),
    [anon_sym_insert] = ACTIONS(207),
    [anon_sym_setAt] = ACTIONS(207),
    [anon_sym_del] = ACTIONS(207),
    [anon_sym_sum] = ACTIONS(207),
    [anon_sym_max] = ACTIONS(207),
    [anon_sym_max2] = ACTIONS(207),
    [anon_sym_min] = ACTIONS(207),
    [anon_sym_min2] = ACTIONS(207),
    [anon_sym_abs] = ACTIONS(207),
    [anon_sym_inc] = ACTIONS(207),
    [anon_sym_mod] = ACTIONS(207),
    [anon_sym_floor] = ACTIONS(207),
    [anon_sym_ceil] = ACTIONS(207),
    [anon_sym_round] = ACTIONS(207),
    [anon_sym_lines] = ACTIONS(207),
    [anon_sym_unlines] = ACTIONS(207),
    [anon_sym_unlinesCrLf] = ACTIONS(207),
    [anon_sym_split] = ACTIONS(207),
    [anon_sym_wsplit] = ACTIONS(207),
    [anon_sym_tsplit] = ACTIONS(207),
    [anon_sym_join] = ACTIONS(207),
    [anon_sym_trim] = ACTIONS(207),
    [anon_sym_trimStart] = ACTIONS(207),
    [anon_sym_trimEnd] = ACTIONS(207),
    [anon_sym_startsWith] = ACTIONS(207),
    [anon_sym_endsWith] = ACTIONS(207),
    [anon_sym_lower] = ACTIONS(207),
    [anon_sym_upper] = ACTIONS(207),
    [anon_sym_title] = ACTIONS(207),
    [anon_sym_leftPad] = ACTIONS(207),
    [anon_sym_findReplace] = ACTIONS(207),
    [anon_sym_in] = ACTIONS(207),
    [anon_sym_index] = ACTIONS(207),
    [anon_sym_lastIndexOf] = ACTIONS(207),
    [anon_sym_countSubStr] = ACTIONS(207),
    [anon_sym_parseJson] = ACTIONS(207),
    [anon_sym_parseCsv] = ACTIONS(207),
    [anon_sym_parseHtml] = ACTIONS(207),
    [anon_sym_parseExcel] = ACTIONS(207),
    [anon_sym_readFile] = ACTIONS(207),
    [anon_sym_readFileBytes] = ACTIONS(207),
    [anon_sym_readTsvFile] = ACTIONS(207),
    [anon_sym_writeFile] = ACTIONS(207),
    [anon_sym_appendFile] = ACTIONS(207),
    [anon_sym_fileExists] = ACTIONS(207),
    [anon_sym_isDir] = ACTIONS(207),
    [anon_sym_isFile] = ACTIONS(207),
    [anon_sym_fileSize] = ACTIONS(207),
    [anon_sym_cp] = ACTIONS(207),
    [anon_sym_mv] = ACTIONS(207),
    [anon_sym_rm] = ACTIONS(207),
    [anon_sym_rmf] = ACTIONS(207),
    [anon_sym_mkdir] = ACTIONS(207),
    [anon_sym_mkdirp] = ACTIONS(207),
    [anon_sym_cd] = ACTIONS(207),
    [anon_sym_pwd] = ACTIONS(207),
    [anon_sym_tempFile] = ACTIONS(207),
    [anon_sym_tempFileExt] = ACTIONS(207),
    [anon_sym_tempDir] = ACTIONS(207),
    [anon_sym_lsDir] = ACTIONS(207),
    [anon_sym_files] = ACTIONS(207),
    [anon_sym_dirs] = ACTIONS(207),
    [anon_sym_absPath] = ACTIONS(207),
    [anon_sym_dirname] = ACTIONS(207),
    [anon_sym_basename] = ACTIONS(207),
    [anon_sym_ext] = ACTIONS(207),
    [anon_sym_stem] = ACTIONS(207),
    [anon_sym_isCmd] = ACTIONS(207),
    [anon_sym_hardLink] = ACTIONS(207),
    [anon_sym_sha256sum] = ACTIONS(207),
    [anon_sym_md5] = ACTIONS(207),
    [anon_sym_now] = ACTIONS(207),
    [anon_sym_date] = ACTIONS(207),
    [anon_sym_year] = ACTIONS(207),
    [anon_sym_month] = ACTIONS(207),
    [anon_sym_day] = ACTIONS(207),
    [anon_sym_hour] = ACTIONS(207),
    [anon_sym_minute] = ACTIONS(207),
    [anon_sym_dateFmt] = ACTIONS(207),
    [anon_sym_isoDateFmt] = ACTIONS(207),
    [anon_sym_isoDateTimeFmt] = ACTIONS(207),
    [anon_sym_isWeekend] = ACTIONS(207),
    [anon_sym_isWeekday] = ACTIONS(207),
    [anon_sym_dow] = ACTIONS(207),
    [anon_sym_addDays] = ACTIONS(207),
    [anon_sym_toUnixTime] = ACTIONS(207),
    [anon_sym_toUnixTimeMilli] = ACTIONS(207),
    [anon_sym_toUnixTimeMicro] = ACTIONS(207),
    [anon_sym_toUnixTimeNano] = ACTIONS(207),
    [anon_sym_fromUnixTime] = ACTIONS(207),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(207),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(207),
    [anon_sym_fromUnixTimeNano] = ACTIONS(207),
    [anon_sym_toOleDate] = ACTIONS(207),
    [anon_sym_fromOleDate] = ACTIONS(207),
    [anon_sym_utcToCst] = ACTIONS(207),
    [anon_sym_cstToUtc] = ACTIONS(207),
    [anon_sym_reMatch] = ACTIONS(207),
    [anon_sym_reFindAll] = ACTIONS(207),
    [anon_sym_reFindAllIndex] = ACTIONS(207),
    [anon_sym_reReplace] = ACTIONS(207),
    [anon_sym_reSplit] = ACTIONS(207),
    [anon_sym_just] = ACTIONS(207),
    [anon_sym_none] = ACTIONS(207),
    [anon_sym_isNone] = ACTIONS(207),
    [anon_sym_maybe] = ACTIONS(207),
    [anon_sym_bind] = ACTIONS(207),
    [anon_sym_psub] = ACTIONS(207),
    [anon_sym_typeof] = ACTIONS(207),
    [anon_sym_runtime] = ACTIONS(207),
    [anon_sym_hostname] = ACTIONS(207),
    [anon_sym_httpGet] = ACTIONS(207),
    [anon_sym_httpPost] = ACTIONS(207),
    [anon_sym_urlEncode] = ACTIONS(207),
    [anon_sym_base64encode] = ACTIONS(207),
    [anon_sym_base64decode] = ACTIONS(207),
    [anon_sym_utf8Str] = ACTIONS(207),
    [anon_sym_utf8Bytes] = ACTIONS(207),
    [anon_sym_get] = ACTIONS(207),
    [anon_sym_getDef] = ACTIONS(207),
    [anon_sym_set] = ACTIONS(207),
    [anon_sym_setd] = ACTIONS(207),
    [anon_sym_keys] = ACTIONS(207),
    [anon_sym_values] = ACTIONS(207),
    [anon_sym_keyValues] = ACTIONS(207),
    [anon_sym_all] = ACTIONS(207),
    [anon_sym_any] = ACTIONS(207),
    [anon_sym_cartesian] = ACTIONS(207),
    [anon_sym_groupBy] = ACTIONS(207),
    [anon_sym_listToDict] = ACTIONS(207),
    [anon_sym_repeat] = ACTIONS(207),
    [anon_sym_seq] = ACTIONS(207),
    [anon_sym_tab] = ACTIONS(207),
    [anon_sym_select] = ACTIONS(207),
    [anon_sym_exclude] = ACTIONS(207),
    [anon_sym_derive] = ACTIONS(207),
    [anon_sym_updateCol] = ACTIONS(207),
    [anon_sym_gridValues] = ACTIONS(207),
    [anon_sym_leftJoin] = ACTIONS(207),
    [anon_sym_outerJoin] = ACTIONS(207),
    [anon_sym_linearSearch] = ACTIONS(207),
    [anon_sym_linearSearchIndex] = ACTIONS(207),
    [anon_sym_binPaths] = ACTIONS(207),
    [anon_sym_wt] = ACTIONS(207),
    [anon_sym_tt] = ACTIONS(207),
    [anon_sym_ttFile] = ACTIONS(207),
    [anon_sym_uw] = ACTIONS(207),
    [anon_sym_tuw] = ACTIONS(207),
    [anon_sym_strCmp] = ACTIONS(207),
    [anon_sym_floatCmp] = ACTIONS(207),
    [anon_sym_versionSortCmp] = ACTIONS(207),
    [anon_sym_id] = ACTIONS(207),
    [anon_sym_2id] = ACTIONS(207),
    [anon_sym_3id] = ACTIONS(207),
    [anon_sym_2unpack] = ACTIONS(207),
    [anon_sym_2apply] = ACTIONS(207),
    [anon_sym_2each] = ACTIONS(207),
    [anon_sym_2tuple] = ACTIONS(207),
    [anon_sym_DOTs] = ACTIONS(207),
    [anon_sym_DOTb] = ACTIONS(207),
    [anon_sym_DOTdef] = ACTIONS(207),
    [anon_sym_DOTenv] = ACTIONS(207),
    [sym_string] = ACTIONS(213),
    [sym_format_string] = ACTIONS(213),
    [sym_single_quoted_string] = ACTIONS(213),
    [sym_path] = ACTIONS(213),
    [sym_datetime] = ACTIONS(213),
    [sym_float] = ACTIONS(213),
    [sym_integer] = ACTIONS(180),
    [sym_env_store] = ACTIONS(213),
    [sym_env_check] = ACTIONS(213),
    [sym_env_retrieve] = ACTIONS(180),
    [sym_positional] = ACTIONS(213),
    [sym_var_retrieve] = ACTIONS(213),
    [sym_var_store] = ACTIONS(213),
    [sym_slice_indexer] = ACTIONS(213),
    [sym_indexer] = ACTIONS(213),
    [sym_end_indexer] = ACTIONS(180),
    [sym_start_indexer] = ACTIONS(180),
    [sym_match_arm_dup] = ACTIONS(213),
    [sym_prefix_quote] = ACTIONS(180),
    [anon_sym_GT] = ACTIONS(216),
    [anon_sym_GT_GT] = ACTIONS(219),
    [anon_sym_2_GT] = ACTIONS(216),
    [anon_sym_2_GT_GT] = ACTIONS(216),
    [anon_sym_AMP_GT] = ACTIONS(216),
    [anon_sym_AMP_GT_GT] = ACTIONS(219),
    [anon_sym_LT] = ACTIONS(216),
    [anon_sym_LT_GT] = ACTIONS(219),
    [anon_sym_STAR] = ACTIONS(216),
    [anon_sym_STARb] = ACTIONS(219),
    [anon_sym_CARET] = ACTIONS(216),
    [anon_sym_CARETb] = ACTIONS(219),
    [anon_sym_SEMI] = ACTIONS(222),
    [anon_sym_BANG] = ACTIONS(225),
    [anon_sym_QMARK] = ACTIONS(222),
    [anon_sym_BANG_EQ] = ACTIONS(228),
    [anon_sym_LT_EQ] = ACTIONS(228),
    [anon_sym_GT_EQ] = ACTIONS(228),
    [anon_sym_AMP] = ACTIONS(231),
    [anon_sym_PIPE] = ACTIONS(231),
    [anon_sym_COMMA] = ACTIONS(234),
    [anon_sym_COLON] = ACTIONS(231),
  },
  [13] = {
    [sym__word] = STATE(17),
    [sym_list] = STATE(17),
    [sym_quotation] = STATE(17),
    [sym_dict] = STATE(17),
    [sym_grid] = STATE(17),
    [sym_boolean] = STATE(17),
    [sym_keyword] = STATE(17),
    [sym_type_keyword] = STATE(17),
    [sym_builtin] = STATE(17),
    [sym_redirect_operator] = STATE(17),
    [sym_execute_operator] = STATE(17),
    [sym_comparison_operator] = STATE(17),
    [sym_punctuation] = STATE(17),
    [aux_sym_source_file_repeat1] = STATE(17),
    [sym_identifier] = ACTIONS(237),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_RBRACK] = ACTIONS(239),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(241),
    [sym_format_string] = ACTIONS(241),
    [sym_single_quoted_string] = ACTIONS(241),
    [sym_path] = ACTIONS(241),
    [sym_datetime] = ACTIONS(241),
    [sym_float] = ACTIONS(241),
    [sym_integer] = ACTIONS(237),
    [sym_env_store] = ACTIONS(241),
    [sym_env_check] = ACTIONS(241),
    [sym_env_retrieve] = ACTIONS(237),
    [sym_positional] = ACTIONS(241),
    [sym_var_retrieve] = ACTIONS(241),
    [sym_var_store] = ACTIONS(241),
    [sym_slice_indexer] = ACTIONS(241),
    [sym_indexer] = ACTIONS(241),
    [sym_end_indexer] = ACTIONS(237),
    [sym_start_indexer] = ACTIONS(237),
    [sym_match_arm_dup] = ACTIONS(241),
    [sym_prefix_quote] = ACTIONS(237),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [14] = {
    [sym__word] = STATE(18),
    [sym_list] = STATE(18),
    [sym_quotation] = STATE(18),
    [sym_dict] = STATE(18),
    [sym_grid] = STATE(18),
    [sym_boolean] = STATE(18),
    [sym_keyword] = STATE(18),
    [sym_type_keyword] = STATE(18),
    [sym_builtin] = STATE(18),
    [sym_redirect_operator] = STATE(18),
    [sym_execute_operator] = STATE(18),
    [sym_comparison_operator] = STATE(18),
    [sym_punctuation] = STATE(18),
    [aux_sym_source_file_repeat1] = STATE(18),
    [sym_identifier] = ACTIONS(243),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_RPAREN] = ACTIONS(245),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(247),
    [sym_format_string] = ACTIONS(247),
    [sym_single_quoted_string] = ACTIONS(247),
    [sym_path] = ACTIONS(247),
    [sym_datetime] = ACTIONS(247),
    [sym_float] = ACTIONS(247),
    [sym_integer] = ACTIONS(243),
    [sym_env_store] = ACTIONS(247),
    [sym_env_check] = ACTIONS(247),
    [sym_env_retrieve] = ACTIONS(243),
    [sym_positional] = ACTIONS(247),
    [sym_var_retrieve] = ACTIONS(247),
    [sym_var_store] = ACTIONS(247),
    [sym_slice_indexer] = ACTIONS(247),
    [sym_indexer] = ACTIONS(247),
    [sym_end_indexer] = ACTIONS(243),
    [sym_start_indexer] = ACTIONS(243),
    [sym_match_arm_dup] = ACTIONS(247),
    [sym_prefix_quote] = ACTIONS(243),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [15] = {
    [sym__word] = STATE(19),
    [sym_list] = STATE(19),
    [sym_quotation] = STATE(19),
    [sym_dict] = STATE(19),
    [sym_grid] = STATE(19),
    [sym_boolean] = STATE(19),
    [sym_keyword] = STATE(19),
    [sym_type_keyword] = STATE(19),
    [sym_builtin] = STATE(19),
    [sym_redirect_operator] = STATE(19),
    [sym_execute_operator] = STATE(19),
    [sym_comparison_operator] = STATE(19),
    [sym_punctuation] = STATE(19),
    [aux_sym_source_file_repeat1] = STATE(19),
    [sym_identifier] = ACTIONS(249),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_RBRACE] = ACTIONS(251),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(253),
    [sym_format_string] = ACTIONS(253),
    [sym_single_quoted_string] = ACTIONS(253),
    [sym_path] = ACTIONS(253),
    [sym_datetime] = ACTIONS(253),
    [sym_float] = ACTIONS(253),
    [sym_integer] = ACTIONS(249),
    [sym_env_store] = ACTIONS(253),
    [sym_env_check] = ACTIONS(253),
    [sym_env_retrieve] = ACTIONS(249),
    [sym_positional] = ACTIONS(253),
    [sym_var_retrieve] = ACTIONS(253),
    [sym_var_store] = ACTIONS(253),
    [sym_slice_indexer] = ACTIONS(253),
    [sym_indexer] = ACTIONS(253),
    [sym_end_indexer] = ACTIONS(249),
    [sym_start_indexer] = ACTIONS(249),
    [sym_match_arm_dup] = ACTIONS(253),
    [sym_prefix_quote] = ACTIONS(249),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [16] = {
    [sym__word] = STATE(20),
    [sym_list] = STATE(20),
    [sym_quotation] = STATE(20),
    [sym_dict] = STATE(20),
    [sym_grid] = STATE(20),
    [sym_boolean] = STATE(20),
    [sym_keyword] = STATE(20),
    [sym_type_keyword] = STATE(20),
    [sym_builtin] = STATE(20),
    [sym_redirect_operator] = STATE(20),
    [sym_execute_operator] = STATE(20),
    [sym_comparison_operator] = STATE(20),
    [sym_punctuation] = STATE(20),
    [aux_sym_source_file_repeat1] = STATE(20),
    [sym_identifier] = ACTIONS(255),
    [anon_sym_LBRACK] = ACTIONS(112),
    [anon_sym_LPAREN] = ACTIONS(114),
    [anon_sym_LBRACE] = ACTIONS(116),
    [anon_sym_LBRACK_PIPE] = ACTIONS(118),
    [anon_sym_PIPE_RBRACK] = ACTIONS(257),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(122),
    [anon_sym_false] = ACTIONS(122),
    [anon_sym_def] = ACTIONS(124),
    [anon_sym_end] = ACTIONS(124),
    [anon_sym_if] = ACTIONS(124),
    [anon_sym_iff] = ACTIONS(124),
    [anon_sym_else] = ACTIONS(124),
    [anon_sym_else_STAR] = ACTIONS(126),
    [anon_sym_STARif] = ACTIONS(126),
    [anon_sym_loop] = ACTIONS(124),
    [anon_sym_match] = ACTIONS(124),
    [anon_sym_break] = ACTIONS(124),
    [anon_sym_continue] = ACTIONS(124),
    [anon_sym_soe] = ACTIONS(124),
    [anon_sym_not] = ACTIONS(124),
    [anon_sym_and] = ACTIONS(124),
    [anon_sym_or] = ACTIONS(124),
    [anon_sym_read] = ACTIONS(124),
    [anon_sym_str] = ACTIONS(124),
    [anon_sym_as] = ACTIONS(124),
    [anon_sym_type] = ACTIONS(124),
    [anon_sym_try] = ACTIONS(124),
    [anon_sym_fail] = ACTIONS(124),
    [anon_sym_pure] = ACTIONS(124),
    [anon_sym_VER] = ACTIONS(124),
    [anon_sym_x] = ACTIONS(124),
    [anon_sym_int] = ACTIONS(128),
    [anon_sym_float] = ACTIONS(128),
    [anon_sym_bool] = ACTIONS(128),
    [anon_sym_dup] = ACTIONS(130),
    [anon_sym_swap] = ACTIONS(130),
    [anon_sym_drop] = ACTIONS(130),
    [anon_sym_over] = ACTIONS(130),
    [anon_sym_pick] = ACTIONS(130),
    [anon_sym_rot] = ACTIONS(130),
    [anon_sym_DASHrot] = ACTIONS(130),
    [anon_sym_nip] = ACTIONS(130),
    [anon_sym_w] = ACTIONS(130),
    [anon_sym_wl] = ACTIONS(130),
    [anon_sym_we] = ACTIONS(130),
    [anon_sym_wle] = ACTIONS(130),
    [anon_sym_len] = ACTIONS(130),
    [anon_sym_args] = ACTIONS(130),
    [anon_sym_glob] = ACTIONS(130),
    [anon_sym_toFloat] = ACTIONS(130),
    [anon_sym_toInt] = ACTIONS(130),
    [anon_sym_toPath] = ACTIONS(130),
    [anon_sym_toDt] = ACTIONS(130),
    [anon_sym_toGrid] = ACTIONS(130),
    [anon_sym_toCsv] = ACTIONS(130),
    [anon_sym_toCsvCell] = ACTIONS(130),
    [anon_sym_exit] = ACTIONS(130),
    [anon_sym_prompt] = ACTIONS(130),
    [anon_sym_stdin] = ACTIONS(130),
    [anon_sym_COLON_COLON] = ACTIONS(132),
    [anon_sym_foldl] = ACTIONS(130),
    [anon_sym_map] = ACTIONS(130),
    [anon_sym_each] = ACTIONS(130),
    [anon_sym_eachWhile] = ACTIONS(130),
    [anon_sym_filter] = ACTIONS(130),
    [anon_sym_append] = ACTIONS(130),
    [anon_sym_extend] = ACTIONS(130),
    [anon_sym_concat] = ACTIONS(130),
    [anon_sym_reverse] = ACTIONS(130),
    [anon_sym_sort] = ACTIONS(130),
    [anon_sym_sortV] = ACTIONS(130),
    [anon_sym_sortBy] = ACTIONS(130),
    [anon_sym_sortByCmp] = ACTIONS(130),
    [anon_sym_uniq] = ACTIONS(130),
    [anon_sym_zip] = ACTIONS(130),
    [anon_sym_enumerate] = ACTIONS(130),
    [anon_sym_enumerateN] = ACTIONS(130),
    [anon_sym_chunk] = ACTIONS(130),
    [anon_sym_pop] = ACTIONS(130),
    [anon_sym_take] = ACTIONS(130),
    [anon_sym_takeWhile] = ACTIONS(130),
    [anon_sym_skip] = ACTIONS(130),
    [anon_sym_dropWhile] = ACTIONS(130),
    [anon_sym_nth] = ACTIONS(130),
    [anon_sym_insert] = ACTIONS(130),
    [anon_sym_setAt] = ACTIONS(130),
    [anon_sym_del] = ACTIONS(130),
    [anon_sym_sum] = ACTIONS(130),
    [anon_sym_max] = ACTIONS(130),
    [anon_sym_max2] = ACTIONS(130),
    [anon_sym_min] = ACTIONS(130),
    [anon_sym_min2] = ACTIONS(130),
    [anon_sym_abs] = ACTIONS(130),
    [anon_sym_inc] = ACTIONS(130),
    [anon_sym_mod] = ACTIONS(130),
    [anon_sym_floor] = ACTIONS(130),
    [anon_sym_ceil] = ACTIONS(130),
    [anon_sym_round] = ACTIONS(130),
    [anon_sym_lines] = ACTIONS(130),
    [anon_sym_unlines] = ACTIONS(130),
    [anon_sym_unlinesCrLf] = ACTIONS(130),
    [anon_sym_split] = ACTIONS(130),
    [anon_sym_wsplit] = ACTIONS(130),
    [anon_sym_tsplit] = ACTIONS(130),
    [anon_sym_join] = ACTIONS(130),
    [anon_sym_trim] = ACTIONS(130),
    [anon_sym_trimStart] = ACTIONS(130),
    [anon_sym_trimEnd] = ACTIONS(130),
    [anon_sym_startsWith] = ACTIONS(130),
    [anon_sym_endsWith] = ACTIONS(130),
    [anon_sym_lower] = ACTIONS(130),
    [anon_sym_upper] = ACTIONS(130),
    [anon_sym_title] = ACTIONS(130),
    [anon_sym_leftPad] = ACTIONS(130),
    [anon_sym_findReplace] = ACTIONS(130),
    [anon_sym_in] = ACTIONS(130),
    [anon_sym_index] = ACTIONS(130),
    [anon_sym_lastIndexOf] = ACTIONS(130),
    [anon_sym_countSubStr] = ACTIONS(130),
    [anon_sym_parseJson] = ACTIONS(130),
    [anon_sym_parseCsv] = ACTIONS(130),
    [anon_sym_parseHtml] = ACTIONS(130),
    [anon_sym_parseExcel] = ACTIONS(130),
    [anon_sym_readFile] = ACTIONS(130),
    [anon_sym_readFileBytes] = ACTIONS(130),
    [anon_sym_readTsvFile] = ACTIONS(130),
    [anon_sym_writeFile] = ACTIONS(130),
    [anon_sym_appendFile] = ACTIONS(130),
    [anon_sym_fileExists] = ACTIONS(130),
    [anon_sym_isDir] = ACTIONS(130),
    [anon_sym_isFile] = ACTIONS(130),
    [anon_sym_fileSize] = ACTIONS(130),
    [anon_sym_cp] = ACTIONS(130),
    [anon_sym_mv] = ACTIONS(130),
    [anon_sym_rm] = ACTIONS(130),
    [anon_sym_rmf] = ACTIONS(130),
    [anon_sym_mkdir] = ACTIONS(130),
    [anon_sym_mkdirp] = ACTIONS(130),
    [anon_sym_cd] = ACTIONS(130),
    [anon_sym_pwd] = ACTIONS(130),
    [anon_sym_tempFile] = ACTIONS(130),
    [anon_sym_tempFileExt] = ACTIONS(130),
    [anon_sym_tempDir] = ACTIONS(130),
    [anon_sym_lsDir] = ACTIONS(130),
    [anon_sym_files] = ACTIONS(130),
    [anon_sym_dirs] = ACTIONS(130),
    [anon_sym_absPath] = ACTIONS(130),
    [anon_sym_dirname] = ACTIONS(130),
    [anon_sym_basename] = ACTIONS(130),
    [anon_sym_ext] = ACTIONS(130),
    [anon_sym_stem] = ACTIONS(130),
    [anon_sym_isCmd] = ACTIONS(130),
    [anon_sym_hardLink] = ACTIONS(130),
    [anon_sym_sha256sum] = ACTIONS(130),
    [anon_sym_md5] = ACTIONS(130),
    [anon_sym_now] = ACTIONS(130),
    [anon_sym_date] = ACTIONS(130),
    [anon_sym_year] = ACTIONS(130),
    [anon_sym_month] = ACTIONS(130),
    [anon_sym_day] = ACTIONS(130),
    [anon_sym_hour] = ACTIONS(130),
    [anon_sym_minute] = ACTIONS(130),
    [anon_sym_dateFmt] = ACTIONS(130),
    [anon_sym_isoDateFmt] = ACTIONS(130),
    [anon_sym_isoDateTimeFmt] = ACTIONS(130),
    [anon_sym_isWeekend] = ACTIONS(130),
    [anon_sym_isWeekday] = ACTIONS(130),
    [anon_sym_dow] = ACTIONS(130),
    [anon_sym_addDays] = ACTIONS(130),
    [anon_sym_toUnixTime] = ACTIONS(130),
    [anon_sym_toUnixTimeMilli] = ACTIONS(130),
    [anon_sym_toUnixTimeMicro] = ACTIONS(130),
    [anon_sym_toUnixTimeNano] = ACTIONS(130),
    [anon_sym_fromUnixTime] = ACTIONS(130),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(130),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(130),
    [anon_sym_fromUnixTimeNano] = ACTIONS(130),
    [anon_sym_toOleDate] = ACTIONS(130),
    [anon_sym_fromOleDate] = ACTIONS(130),
    [anon_sym_utcToCst] = ACTIONS(130),
    [anon_sym_cstToUtc] = ACTIONS(130),
    [anon_sym_reMatch] = ACTIONS(130),
    [anon_sym_reFindAll] = ACTIONS(130),
    [anon_sym_reFindAllIndex] = ACTIONS(130),
    [anon_sym_reReplace] = ACTIONS(130),
    [anon_sym_reSplit] = ACTIONS(130),
    [anon_sym_just] = ACTIONS(130),
    [anon_sym_none] = ACTIONS(130),
    [anon_sym_isNone] = ACTIONS(130),
    [anon_sym_maybe] = ACTIONS(130),
    [anon_sym_bind] = ACTIONS(130),
    [anon_sym_psub] = ACTIONS(130),
    [anon_sym_typeof] = ACTIONS(130),
    [anon_sym_runtime] = ACTIONS(130),
    [anon_sym_hostname] = ACTIONS(130),
    [anon_sym_httpGet] = ACTIONS(130),
    [anon_sym_httpPost] = ACTIONS(130),
    [anon_sym_urlEncode] = ACTIONS(130),
    [anon_sym_base64encode] = ACTIONS(130),
    [anon_sym_base64decode] = ACTIONS(130),
    [anon_sym_utf8Str] = ACTIONS(130),
    [anon_sym_utf8Bytes] = ACTIONS(130),
    [anon_sym_get] = ACTIONS(130),
    [anon_sym_getDef] = ACTIONS(130),
    [anon_sym_set] = ACTIONS(130),
    [anon_sym_setd] = ACTIONS(130),
    [anon_sym_keys] = ACTIONS(130),
    [anon_sym_values] = ACTIONS(130),
    [anon_sym_keyValues] = ACTIONS(130),
    [anon_sym_all] = ACTIONS(130),
    [anon_sym_any] = ACTIONS(130),
    [anon_sym_cartesian] = ACTIONS(130),
    [anon_sym_groupBy] = ACTIONS(130),
    [anon_sym_listToDict] = ACTIONS(130),
    [anon_sym_repeat] = ACTIONS(130),
    [anon_sym_seq] = ACTIONS(130),
    [anon_sym_tab] = ACTIONS(130),
    [anon_sym_select] = ACTIONS(130),
    [anon_sym_exclude] = ACTIONS(130),
    [anon_sym_derive] = ACTIONS(130),
    [anon_sym_updateCol] = ACTIONS(130),
    [anon_sym_gridValues] = ACTIONS(130),
    [anon_sym_leftJoin] = ACTIONS(130),
    [anon_sym_outerJoin] = ACTIONS(130),
    [anon_sym_linearSearch] = ACTIONS(130),
    [anon_sym_linearSearchIndex] = ACTIONS(130),
    [anon_sym_binPaths] = ACTIONS(130),
    [anon_sym_wt] = ACTIONS(130),
    [anon_sym_tt] = ACTIONS(130),
    [anon_sym_ttFile] = ACTIONS(130),
    [anon_sym_uw] = ACTIONS(130),
    [anon_sym_tuw] = ACTIONS(130),
    [anon_sym_strCmp] = ACTIONS(130),
    [anon_sym_floatCmp] = ACTIONS(130),
    [anon_sym_versionSortCmp] = ACTIONS(130),
    [anon_sym_id] = ACTIONS(130),
    [anon_sym_2id] = ACTIONS(130),
    [anon_sym_3id] = ACTIONS(130),
    [anon_sym_2unpack] = ACTIONS(130),
    [anon_sym_2apply] = ACTIONS(130),
    [anon_sym_2each] = ACTIONS(130),
    [anon_sym_2tuple] = ACTIONS(130),
    [anon_sym_DOTs] = ACTIONS(130),
    [anon_sym_DOTb] = ACTIONS(130),
    [anon_sym_DOTdef] = ACTIONS(130),
    [anon_sym_DOTenv] = ACTIONS(130),
    [sym_string] = ACTIONS(259),
    [sym_format_string] = ACTIONS(259),
    [sym_single_quoted_string] = ACTIONS(259),
    [sym_path] = ACTIONS(259),
    [sym_datetime] = ACTIONS(259),
    [sym_float] = ACTIONS(259),
    [sym_integer] = ACTIONS(255),
    [sym_env_store] = ACTIONS(259),
    [sym_env_check] = ACTIONS(259),
    [sym_env_retrieve] = ACTIONS(255),
    [sym_positional] = ACTIONS(259),
    [sym_var_retrieve] = ACTIONS(259),
    [sym_var_store] = ACTIONS(259),
    [sym_slice_indexer] = ACTIONS(259),
    [sym_indexer] = ACTIONS(259),
    [sym_end_indexer] = ACTIONS(255),
    [sym_start_indexer] = ACTIONS(255),
    [sym_match_arm_dup] = ACTIONS(259),
    [sym_prefix_quote] = ACTIONS(255),
    [anon_sym_GT] = ACTIONS(136),
    [anon_sym_GT_GT] = ACTIONS(138),
    [anon_sym_2_GT] = ACTIONS(136),
    [anon_sym_2_GT_GT] = ACTIONS(136),
    [anon_sym_AMP_GT] = ACTIONS(136),
    [anon_sym_AMP_GT_GT] = ACTIONS(138),
    [anon_sym_LT] = ACTIONS(136),
    [anon_sym_LT_GT] = ACTIONS(138),
    [anon_sym_STAR] = ACTIONS(136),
    [anon_sym_STARb] = ACTIONS(138),
    [anon_sym_CARET] = ACTIONS(136),
    [anon_sym_CARETb] = ACTIONS(138),
    [anon_sym_SEMI] = ACTIONS(140),
    [anon_sym_BANG] = ACTIONS(142),
    [anon_sym_QMARK] = ACTIONS(140),
    [anon_sym_BANG_EQ] = ACTIONS(144),
    [anon_sym_LT_EQ] = ACTIONS(144),
    [anon_sym_GT_EQ] = ACTIONS(144),
    [anon_sym_AMP] = ACTIONS(146),
    [anon_sym_PIPE] = ACTIONS(146),
    [anon_sym_COMMA] = ACTIONS(148),
    [anon_sym_COLON] = ACTIONS(146),
  },
  [17] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_RBRACK] = ACTIONS(261),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [18] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_RPAREN] = ACTIONS(263),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [19] = {
    [sym__word] = STATE(2),
    [sym_list] = STATE(2),
    [sym_quotation] = STATE(2),
    [sym_dict] = STATE(2),
    [sym_grid] = STATE(2),
    [sym_boolean] = STATE(2),
    [sym_keyword] = STATE(2),
    [sym_type_keyword] = STATE(2),
    [sym_builtin] = STATE(2),
    [sym_redirect_operator] = STATE(2),
    [sym_execute_operator] = STATE(2),
    [sym_comparison_operator] = STATE(2),
    [sym_punctuation] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [sym_identifier] = ACTIONS(152),
    [anon_sym_LBRACK] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_LBRACE] = ACTIONS(13),
    [anon_sym_RBRACE] = ACTIONS(265),
    [anon_sym_LBRACK_PIPE] = ACTIONS(15),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(17),
    [anon_sym_false] = ACTIONS(17),
    [anon_sym_def] = ACTIONS(19),
    [anon_sym_end] = ACTIONS(19),
    [anon_sym_if] = ACTIONS(19),
    [anon_sym_iff] = ACTIONS(19),
    [anon_sym_else] = ACTIONS(19),
    [anon_sym_else_STAR] = ACTIONS(21),
    [anon_sym_STARif] = ACTIONS(21),
    [anon_sym_loop] = ACTIONS(19),
    [anon_sym_match] = ACTIONS(19),
    [anon_sym_break] = ACTIONS(19),
    [anon_sym_continue] = ACTIONS(19),
    [anon_sym_soe] = ACTIONS(19),
    [anon_sym_not] = ACTIONS(19),
    [anon_sym_and] = ACTIONS(19),
    [anon_sym_or] = ACTIONS(19),
    [anon_sym_read] = ACTIONS(19),
    [anon_sym_str] = ACTIONS(19),
    [anon_sym_as] = ACTIONS(19),
    [anon_sym_type] = ACTIONS(19),
    [anon_sym_try] = ACTIONS(19),
    [anon_sym_fail] = ACTIONS(19),
    [anon_sym_pure] = ACTIONS(19),
    [anon_sym_VER] = ACTIONS(19),
    [anon_sym_x] = ACTIONS(19),
    [anon_sym_int] = ACTIONS(23),
    [anon_sym_float] = ACTIONS(23),
    [anon_sym_bool] = ACTIONS(23),
    [anon_sym_dup] = ACTIONS(25),
    [anon_sym_swap] = ACTIONS(25),
    [anon_sym_drop] = ACTIONS(25),
    [anon_sym_over] = ACTIONS(25),
    [anon_sym_pick] = ACTIONS(25),
    [anon_sym_rot] = ACTIONS(25),
    [anon_sym_DASHrot] = ACTIONS(25),
    [anon_sym_nip] = ACTIONS(25),
    [anon_sym_w] = ACTIONS(25),
    [anon_sym_wl] = ACTIONS(25),
    [anon_sym_we] = ACTIONS(25),
    [anon_sym_wle] = ACTIONS(25),
    [anon_sym_len] = ACTIONS(25),
    [anon_sym_args] = ACTIONS(25),
    [anon_sym_glob] = ACTIONS(25),
    [anon_sym_toFloat] = ACTIONS(25),
    [anon_sym_toInt] = ACTIONS(25),
    [anon_sym_toPath] = ACTIONS(25),
    [anon_sym_toDt] = ACTIONS(25),
    [anon_sym_toGrid] = ACTIONS(25),
    [anon_sym_toCsv] = ACTIONS(25),
    [anon_sym_toCsvCell] = ACTIONS(25),
    [anon_sym_exit] = ACTIONS(25),
    [anon_sym_prompt] = ACTIONS(25),
    [anon_sym_stdin] = ACTIONS(25),
    [anon_sym_COLON_COLON] = ACTIONS(27),
    [anon_sym_foldl] = ACTIONS(25),
    [anon_sym_map] = ACTIONS(25),
    [anon_sym_each] = ACTIONS(25),
    [anon_sym_eachWhile] = ACTIONS(25),
    [anon_sym_filter] = ACTIONS(25),
    [anon_sym_append] = ACTIONS(25),
    [anon_sym_extend] = ACTIONS(25),
    [anon_sym_concat] = ACTIONS(25),
    [anon_sym_reverse] = ACTIONS(25),
    [anon_sym_sort] = ACTIONS(25),
    [anon_sym_sortV] = ACTIONS(25),
    [anon_sym_sortBy] = ACTIONS(25),
    [anon_sym_sortByCmp] = ACTIONS(25),
    [anon_sym_uniq] = ACTIONS(25),
    [anon_sym_zip] = ACTIONS(25),
    [anon_sym_enumerate] = ACTIONS(25),
    [anon_sym_enumerateN] = ACTIONS(25),
    [anon_sym_chunk] = ACTIONS(25),
    [anon_sym_pop] = ACTIONS(25),
    [anon_sym_take] = ACTIONS(25),
    [anon_sym_takeWhile] = ACTIONS(25),
    [anon_sym_skip] = ACTIONS(25),
    [anon_sym_dropWhile] = ACTIONS(25),
    [anon_sym_nth] = ACTIONS(25),
    [anon_sym_insert] = ACTIONS(25),
    [anon_sym_setAt] = ACTIONS(25),
    [anon_sym_del] = ACTIONS(25),
    [anon_sym_sum] = ACTIONS(25),
    [anon_sym_max] = ACTIONS(25),
    [anon_sym_max2] = ACTIONS(25),
    [anon_sym_min] = ACTIONS(25),
    [anon_sym_min2] = ACTIONS(25),
    [anon_sym_abs] = ACTIONS(25),
    [anon_sym_inc] = ACTIONS(25),
    [anon_sym_mod] = ACTIONS(25),
    [anon_sym_floor] = ACTIONS(25),
    [anon_sym_ceil] = ACTIONS(25),
    [anon_sym_round] = ACTIONS(25),
    [anon_sym_lines] = ACTIONS(25),
    [anon_sym_unlines] = ACTIONS(25),
    [anon_sym_unlinesCrLf] = ACTIONS(25),
    [anon_sym_split] = ACTIONS(25),
    [anon_sym_wsplit] = ACTIONS(25),
    [anon_sym_tsplit] = ACTIONS(25),
    [anon_sym_join] = ACTIONS(25),
    [anon_sym_trim] = ACTIONS(25),
    [anon_sym_trimStart] = ACTIONS(25),
    [anon_sym_trimEnd] = ACTIONS(25),
    [anon_sym_startsWith] = ACTIONS(25),
    [anon_sym_endsWith] = ACTIONS(25),
    [anon_sym_lower] = ACTIONS(25),
    [anon_sym_upper] = ACTIONS(25),
    [anon_sym_title] = ACTIONS(25),
    [anon_sym_leftPad] = ACTIONS(25),
    [anon_sym_findReplace] = ACTIONS(25),
    [anon_sym_in] = ACTIONS(25),
    [anon_sym_index] = ACTIONS(25),
    [anon_sym_lastIndexOf] = ACTIONS(25),
    [anon_sym_countSubStr] = ACTIONS(25),
    [anon_sym_parseJson] = ACTIONS(25),
    [anon_sym_parseCsv] = ACTIONS(25),
    [anon_sym_parseHtml] = ACTIONS(25),
    [anon_sym_parseExcel] = ACTIONS(25),
    [anon_sym_readFile] = ACTIONS(25),
    [anon_sym_readFileBytes] = ACTIONS(25),
    [anon_sym_readTsvFile] = ACTIONS(25),
    [anon_sym_writeFile] = ACTIONS(25),
    [anon_sym_appendFile] = ACTIONS(25),
    [anon_sym_fileExists] = ACTIONS(25),
    [anon_sym_isDir] = ACTIONS(25),
    [anon_sym_isFile] = ACTIONS(25),
    [anon_sym_fileSize] = ACTIONS(25),
    [anon_sym_cp] = ACTIONS(25),
    [anon_sym_mv] = ACTIONS(25),
    [anon_sym_rm] = ACTIONS(25),
    [anon_sym_rmf] = ACTIONS(25),
    [anon_sym_mkdir] = ACTIONS(25),
    [anon_sym_mkdirp] = ACTIONS(25),
    [anon_sym_cd] = ACTIONS(25),
    [anon_sym_pwd] = ACTIONS(25),
    [anon_sym_tempFile] = ACTIONS(25),
    [anon_sym_tempFileExt] = ACTIONS(25),
    [anon_sym_tempDir] = ACTIONS(25),
    [anon_sym_lsDir] = ACTIONS(25),
    [anon_sym_files] = ACTIONS(25),
    [anon_sym_dirs] = ACTIONS(25),
    [anon_sym_absPath] = ACTIONS(25),
    [anon_sym_dirname] = ACTIONS(25),
    [anon_sym_basename] = ACTIONS(25),
    [anon_sym_ext] = ACTIONS(25),
    [anon_sym_stem] = ACTIONS(25),
    [anon_sym_isCmd] = ACTIONS(25),
    [anon_sym_hardLink] = ACTIONS(25),
    [anon_sym_sha256sum] = ACTIONS(25),
    [anon_sym_md5] = ACTIONS(25),
    [anon_sym_now] = ACTIONS(25),
    [anon_sym_date] = ACTIONS(25),
    [anon_sym_year] = ACTIONS(25),
    [anon_sym_month] = ACTIONS(25),
    [anon_sym_day] = ACTIONS(25),
    [anon_sym_hour] = ACTIONS(25),
    [anon_sym_minute] = ACTIONS(25),
    [anon_sym_dateFmt] = ACTIONS(25),
    [anon_sym_isoDateFmt] = ACTIONS(25),
    [anon_sym_isoDateTimeFmt] = ACTIONS(25),
    [anon_sym_isWeekend] = ACTIONS(25),
    [anon_sym_isWeekday] = ACTIONS(25),
    [anon_sym_dow] = ACTIONS(25),
    [anon_sym_addDays] = ACTIONS(25),
    [anon_sym_toUnixTime] = ACTIONS(25),
    [anon_sym_toUnixTimeMilli] = ACTIONS(25),
    [anon_sym_toUnixTimeMicro] = ACTIONS(25),
    [anon_sym_toUnixTimeNano] = ACTIONS(25),
    [anon_sym_fromUnixTime] = ACTIONS(25),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(25),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(25),
    [anon_sym_fromUnixTimeNano] = ACTIONS(25),
    [anon_sym_toOleDate] = ACTIONS(25),
    [anon_sym_fromOleDate] = ACTIONS(25),
    [anon_sym_utcToCst] = ACTIONS(25),
    [anon_sym_cstToUtc] = ACTIONS(25),
    [anon_sym_reMatch] = ACTIONS(25),
    [anon_sym_reFindAll] = ACTIONS(25),
    [anon_sym_reFindAllIndex] = ACTIONS(25),
    [anon_sym_reReplace] = ACTIONS(25),
    [anon_sym_reSplit] = ACTIONS(25),
    [anon_sym_just] = ACTIONS(25),
    [anon_sym_none] = ACTIONS(25),
    [anon_sym_isNone] = ACTIONS(25),
    [anon_sym_maybe] = ACTIONS(25),
    [anon_sym_bind] = ACTIONS(25),
    [anon_sym_psub] = ACTIONS(25),
    [anon_sym_typeof] = ACTIONS(25),
    [anon_sym_runtime] = ACTIONS(25),
    [anon_sym_hostname] = ACTIONS(25),
    [anon_sym_httpGet] = ACTIONS(25),
    [anon_sym_httpPost] = ACTIONS(25),
    [anon_sym_urlEncode] = ACTIONS(25),
    [anon_sym_base64encode] = ACTIONS(25),
    [anon_sym_base64decode] = ACTIONS(25),
    [anon_sym_utf8Str] = ACTIONS(25),
    [anon_sym_utf8Bytes] = ACTIONS(25),
    [anon_sym_get] = ACTIONS(25),
    [anon_sym_getDef] = ACTIONS(25),
    [anon_sym_set] = ACTIONS(25),
    [anon_sym_setd] = ACTIONS(25),
    [anon_sym_keys] = ACTIONS(25),
    [anon_sym_values] = ACTIONS(25),
    [anon_sym_keyValues] = ACTIONS(25),
    [anon_sym_all] = ACTIONS(25),
    [anon_sym_any] = ACTIONS(25),
    [anon_sym_cartesian] = ACTIONS(25),
    [anon_sym_groupBy] = ACTIONS(25),
    [anon_sym_listToDict] = ACTIONS(25),
    [anon_sym_repeat] = ACTIONS(25),
    [anon_sym_seq] = ACTIONS(25),
    [anon_sym_tab] = ACTIONS(25),
    [anon_sym_select] = ACTIONS(25),
    [anon_sym_exclude] = ACTIONS(25),
    [anon_sym_derive] = ACTIONS(25),
    [anon_sym_updateCol] = ACTIONS(25),
    [anon_sym_gridValues] = ACTIONS(25),
    [anon_sym_leftJoin] = ACTIONS(25),
    [anon_sym_outerJoin] = ACTIONS(25),
    [anon_sym_linearSearch] = ACTIONS(25),
    [anon_sym_linearSearchIndex] = ACTIONS(25),
    [anon_sym_binPaths] = ACTIONS(25),
    [anon_sym_wt] = ACTIONS(25),
    [anon_sym_tt] = ACTIONS(25),
    [anon_sym_ttFile] = ACTIONS(25),
    [anon_sym_uw] = ACTIONS(25),
    [anon_sym_tuw] = ACTIONS(25),
    [anon_sym_strCmp] = ACTIONS(25),
    [anon_sym_floatCmp] = ACTIONS(25),
    [anon_sym_versionSortCmp] = ACTIONS(25),
    [anon_sym_id] = ACTIONS(25),
    [anon_sym_2id] = ACTIONS(25),
    [anon_sym_3id] = ACTIONS(25),
    [anon_sym_2unpack] = ACTIONS(25),
    [anon_sym_2apply] = ACTIONS(25),
    [anon_sym_2each] = ACTIONS(25),
    [anon_sym_2tuple] = ACTIONS(25),
    [anon_sym_DOTs] = ACTIONS(25),
    [anon_sym_DOTb] = ACTIONS(25),
    [anon_sym_DOTdef] = ACTIONS(25),
    [anon_sym_DOTenv] = ACTIONS(25),
    [sym_string] = ACTIONS(154),
    [sym_format_string] = ACTIONS(154),
    [sym_single_quoted_string] = ACTIONS(154),
    [sym_path] = ACTIONS(154),
    [sym_datetime] = ACTIONS(154),
    [sym_float] = ACTIONS(154),
    [sym_integer] = ACTIONS(152),
    [sym_env_store] = ACTIONS(154),
    [sym_env_check] = ACTIONS(154),
    [sym_env_retrieve] = ACTIONS(152),
    [sym_positional] = ACTIONS(154),
    [sym_var_retrieve] = ACTIONS(154),
    [sym_var_store] = ACTIONS(154),
    [sym_slice_indexer] = ACTIONS(154),
    [sym_indexer] = ACTIONS(154),
    [sym_end_indexer] = ACTIONS(152),
    [sym_start_indexer] = ACTIONS(152),
    [sym_match_arm_dup] = ACTIONS(154),
    [sym_prefix_quote] = ACTIONS(152),
    [anon_sym_GT] = ACTIONS(31),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_2_GT] = ACTIONS(31),
    [anon_sym_2_GT_GT] = ACTIONS(31),
    [anon_sym_AMP_GT] = ACTIONS(31),
    [anon_sym_AMP_GT_GT] = ACTIONS(33),
    [anon_sym_LT] = ACTIONS(31),
    [anon_sym_LT_GT] = ACTIONS(33),
    [anon_sym_STAR] = ACTIONS(31),
    [anon_sym_STARb] = ACTIONS(33),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_CARETb] = ACTIONS(33),
    [anon_sym_SEMI] = ACTIONS(35),
    [anon_sym_BANG] = ACTIONS(37),
    [anon_sym_QMARK] = ACTIONS(35),
    [anon_sym_BANG_EQ] = ACTIONS(39),
    [anon_sym_LT_EQ] = ACTIONS(39),
    [anon_sym_GT_EQ] = ACTIONS(39),
    [anon_sym_AMP] = ACTIONS(41),
    [anon_sym_PIPE] = ACTIONS(43),
    [anon_sym_COMMA] = ACTIONS(43),
    [anon_sym_COLON] = ACTIONS(41),
  },
  [20] = {
    [sym__word] = STATE(12),
    [sym_list] = STATE(12),
    [sym_quotation] = STATE(12),
    [sym_dict] = STATE(12),
    [sym_grid] = STATE(12),
    [sym_boolean] = STATE(12),
    [sym_keyword] = STATE(12),
    [sym_type_keyword] = STATE(12),
    [sym_builtin] = STATE(12),
    [sym_redirect_operator] = STATE(12),
    [sym_execute_operator] = STATE(12),
    [sym_comparison_operator] = STATE(12),
    [sym_punctuation] = STATE(12),
    [aux_sym_source_file_repeat1] = STATE(12),
    [sym_identifier] = ACTIONS(162),
    [anon_sym_LBRACK] = ACTIONS(112),
    [anon_sym_LPAREN] = ACTIONS(114),
    [anon_sym_LBRACE] = ACTIONS(116),
    [anon_sym_LBRACK_PIPE] = ACTIONS(118),
    [anon_sym_PIPE_RBRACK] = ACTIONS(267),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(122),
    [anon_sym_false] = ACTIONS(122),
    [anon_sym_def] = ACTIONS(124),
    [anon_sym_end] = ACTIONS(124),
    [anon_sym_if] = ACTIONS(124),
    [anon_sym_iff] = ACTIONS(124),
    [anon_sym_else] = ACTIONS(124),
    [anon_sym_else_STAR] = ACTIONS(126),
    [anon_sym_STARif] = ACTIONS(126),
    [anon_sym_loop] = ACTIONS(124),
    [anon_sym_match] = ACTIONS(124),
    [anon_sym_break] = ACTIONS(124),
    [anon_sym_continue] = ACTIONS(124),
    [anon_sym_soe] = ACTIONS(124),
    [anon_sym_not] = ACTIONS(124),
    [anon_sym_and] = ACTIONS(124),
    [anon_sym_or] = ACTIONS(124),
    [anon_sym_read] = ACTIONS(124),
    [anon_sym_str] = ACTIONS(124),
    [anon_sym_as] = ACTIONS(124),
    [anon_sym_type] = ACTIONS(124),
    [anon_sym_try] = ACTIONS(124),
    [anon_sym_fail] = ACTIONS(124),
    [anon_sym_pure] = ACTIONS(124),
    [anon_sym_VER] = ACTIONS(124),
    [anon_sym_x] = ACTIONS(124),
    [anon_sym_int] = ACTIONS(128),
    [anon_sym_float] = ACTIONS(128),
    [anon_sym_bool] = ACTIONS(128),
    [anon_sym_dup] = ACTIONS(130),
    [anon_sym_swap] = ACTIONS(130),
    [anon_sym_drop] = ACTIONS(130),
    [anon_sym_over] = ACTIONS(130),
    [anon_sym_pick] = ACTIONS(130),
    [anon_sym_rot] = ACTIONS(130),
    [anon_sym_DASHrot] = ACTIONS(130),
    [anon_sym_nip] = ACTIONS(130),
    [anon_sym_w] = ACTIONS(130),
    [anon_sym_wl] = ACTIONS(130),
    [anon_sym_we] = ACTIONS(130),
    [anon_sym_wle] = ACTIONS(130),
    [anon_sym_len] = ACTIONS(130),
    [anon_sym_args] = ACTIONS(130),
    [anon_sym_glob] = ACTIONS(130),
    [anon_sym_toFloat] = ACTIONS(130),
    [anon_sym_toInt] = ACTIONS(130),
    [anon_sym_toPath] = ACTIONS(130),
    [anon_sym_toDt] = ACTIONS(130),
    [anon_sym_toGrid] = ACTIONS(130),
    [anon_sym_toCsv] = ACTIONS(130),
    [anon_sym_toCsvCell] = ACTIONS(130),
    [anon_sym_exit] = ACTIONS(130),
    [anon_sym_prompt] = ACTIONS(130),
    [anon_sym_stdin] = ACTIONS(130),
    [anon_sym_COLON_COLON] = ACTIONS(132),
    [anon_sym_foldl] = ACTIONS(130),
    [anon_sym_map] = ACTIONS(130),
    [anon_sym_each] = ACTIONS(130),
    [anon_sym_eachWhile] = ACTIONS(130),
    [anon_sym_filter] = ACTIONS(130),
    [anon_sym_append] = ACTIONS(130),
    [anon_sym_extend] = ACTIONS(130),
    [anon_sym_concat] = ACTIONS(130),
    [anon_sym_reverse] = ACTIONS(130),
    [anon_sym_sort] = ACTIONS(130),
    [anon_sym_sortV] = ACTIONS(130),
    [anon_sym_sortBy] = ACTIONS(130),
    [anon_sym_sortByCmp] = ACTIONS(130),
    [anon_sym_uniq] = ACTIONS(130),
    [anon_sym_zip] = ACTIONS(130),
    [anon_sym_enumerate] = ACTIONS(130),
    [anon_sym_enumerateN] = ACTIONS(130),
    [anon_sym_chunk] = ACTIONS(130),
    [anon_sym_pop] = ACTIONS(130),
    [anon_sym_take] = ACTIONS(130),
    [anon_sym_takeWhile] = ACTIONS(130),
    [anon_sym_skip] = ACTIONS(130),
    [anon_sym_dropWhile] = ACTIONS(130),
    [anon_sym_nth] = ACTIONS(130),
    [anon_sym_insert] = ACTIONS(130),
    [anon_sym_setAt] = ACTIONS(130),
    [anon_sym_del] = ACTIONS(130),
    [anon_sym_sum] = ACTIONS(130),
    [anon_sym_max] = ACTIONS(130),
    [anon_sym_max2] = ACTIONS(130),
    [anon_sym_min] = ACTIONS(130),
    [anon_sym_min2] = ACTIONS(130),
    [anon_sym_abs] = ACTIONS(130),
    [anon_sym_inc] = ACTIONS(130),
    [anon_sym_mod] = ACTIONS(130),
    [anon_sym_floor] = ACTIONS(130),
    [anon_sym_ceil] = ACTIONS(130),
    [anon_sym_round] = ACTIONS(130),
    [anon_sym_lines] = ACTIONS(130),
    [anon_sym_unlines] = ACTIONS(130),
    [anon_sym_unlinesCrLf] = ACTIONS(130),
    [anon_sym_split] = ACTIONS(130),
    [anon_sym_wsplit] = ACTIONS(130),
    [anon_sym_tsplit] = ACTIONS(130),
    [anon_sym_join] = ACTIONS(130),
    [anon_sym_trim] = ACTIONS(130),
    [anon_sym_trimStart] = ACTIONS(130),
    [anon_sym_trimEnd] = ACTIONS(130),
    [anon_sym_startsWith] = ACTIONS(130),
    [anon_sym_endsWith] = ACTIONS(130),
    [anon_sym_lower] = ACTIONS(130),
    [anon_sym_upper] = ACTIONS(130),
    [anon_sym_title] = ACTIONS(130),
    [anon_sym_leftPad] = ACTIONS(130),
    [anon_sym_findReplace] = ACTIONS(130),
    [anon_sym_in] = ACTIONS(130),
    [anon_sym_index] = ACTIONS(130),
    [anon_sym_lastIndexOf] = ACTIONS(130),
    [anon_sym_countSubStr] = ACTIONS(130),
    [anon_sym_parseJson] = ACTIONS(130),
    [anon_sym_parseCsv] = ACTIONS(130),
    [anon_sym_parseHtml] = ACTIONS(130),
    [anon_sym_parseExcel] = ACTIONS(130),
    [anon_sym_readFile] = ACTIONS(130),
    [anon_sym_readFileBytes] = ACTIONS(130),
    [anon_sym_readTsvFile] = ACTIONS(130),
    [anon_sym_writeFile] = ACTIONS(130),
    [anon_sym_appendFile] = ACTIONS(130),
    [anon_sym_fileExists] = ACTIONS(130),
    [anon_sym_isDir] = ACTIONS(130),
    [anon_sym_isFile] = ACTIONS(130),
    [anon_sym_fileSize] = ACTIONS(130),
    [anon_sym_cp] = ACTIONS(130),
    [anon_sym_mv] = ACTIONS(130),
    [anon_sym_rm] = ACTIONS(130),
    [anon_sym_rmf] = ACTIONS(130),
    [anon_sym_mkdir] = ACTIONS(130),
    [anon_sym_mkdirp] = ACTIONS(130),
    [anon_sym_cd] = ACTIONS(130),
    [anon_sym_pwd] = ACTIONS(130),
    [anon_sym_tempFile] = ACTIONS(130),
    [anon_sym_tempFileExt] = ACTIONS(130),
    [anon_sym_tempDir] = ACTIONS(130),
    [anon_sym_lsDir] = ACTIONS(130),
    [anon_sym_files] = ACTIONS(130),
    [anon_sym_dirs] = ACTIONS(130),
    [anon_sym_absPath] = ACTIONS(130),
    [anon_sym_dirname] = ACTIONS(130),
    [anon_sym_basename] = ACTIONS(130),
    [anon_sym_ext] = ACTIONS(130),
    [anon_sym_stem] = ACTIONS(130),
    [anon_sym_isCmd] = ACTIONS(130),
    [anon_sym_hardLink] = ACTIONS(130),
    [anon_sym_sha256sum] = ACTIONS(130),
    [anon_sym_md5] = ACTIONS(130),
    [anon_sym_now] = ACTIONS(130),
    [anon_sym_date] = ACTIONS(130),
    [anon_sym_year] = ACTIONS(130),
    [anon_sym_month] = ACTIONS(130),
    [anon_sym_day] = ACTIONS(130),
    [anon_sym_hour] = ACTIONS(130),
    [anon_sym_minute] = ACTIONS(130),
    [anon_sym_dateFmt] = ACTIONS(130),
    [anon_sym_isoDateFmt] = ACTIONS(130),
    [anon_sym_isoDateTimeFmt] = ACTIONS(130),
    [anon_sym_isWeekend] = ACTIONS(130),
    [anon_sym_isWeekday] = ACTIONS(130),
    [anon_sym_dow] = ACTIONS(130),
    [anon_sym_addDays] = ACTIONS(130),
    [anon_sym_toUnixTime] = ACTIONS(130),
    [anon_sym_toUnixTimeMilli] = ACTIONS(130),
    [anon_sym_toUnixTimeMicro] = ACTIONS(130),
    [anon_sym_toUnixTimeNano] = ACTIONS(130),
    [anon_sym_fromUnixTime] = ACTIONS(130),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(130),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(130),
    [anon_sym_fromUnixTimeNano] = ACTIONS(130),
    [anon_sym_toOleDate] = ACTIONS(130),
    [anon_sym_fromOleDate] = ACTIONS(130),
    [anon_sym_utcToCst] = ACTIONS(130),
    [anon_sym_cstToUtc] = ACTIONS(130),
    [anon_sym_reMatch] = ACTIONS(130),
    [anon_sym_reFindAll] = ACTIONS(130),
    [anon_sym_reFindAllIndex] = ACTIONS(130),
    [anon_sym_reReplace] = ACTIONS(130),
    [anon_sym_reSplit] = ACTIONS(130),
    [anon_sym_just] = ACTIONS(130),
    [anon_sym_none] = ACTIONS(130),
    [anon_sym_isNone] = ACTIONS(130),
    [anon_sym_maybe] = ACTIONS(130),
    [anon_sym_bind] = ACTIONS(130),
    [anon_sym_psub] = ACTIONS(130),
    [anon_sym_typeof] = ACTIONS(130),
    [anon_sym_runtime] = ACTIONS(130),
    [anon_sym_hostname] = ACTIONS(130),
    [anon_sym_httpGet] = ACTIONS(130),
    [anon_sym_httpPost] = ACTIONS(130),
    [anon_sym_urlEncode] = ACTIONS(130),
    [anon_sym_base64encode] = ACTIONS(130),
    [anon_sym_base64decode] = ACTIONS(130),
    [anon_sym_utf8Str] = ACTIONS(130),
    [anon_sym_utf8Bytes] = ACTIONS(130),
    [anon_sym_get] = ACTIONS(130),
    [anon_sym_getDef] = ACTIONS(130),
    [anon_sym_set] = ACTIONS(130),
    [anon_sym_setd] = ACTIONS(130),
    [anon_sym_keys] = ACTIONS(130),
    [anon_sym_values] = ACTIONS(130),
    [anon_sym_keyValues] = ACTIONS(130),
    [anon_sym_all] = ACTIONS(130),
    [anon_sym_any] = ACTIONS(130),
    [anon_sym_cartesian] = ACTIONS(130),
    [anon_sym_groupBy] = ACTIONS(130),
    [anon_sym_listToDict] = ACTIONS(130),
    [anon_sym_repeat] = ACTIONS(130),
    [anon_sym_seq] = ACTIONS(130),
    [anon_sym_tab] = ACTIONS(130),
    [anon_sym_select] = ACTIONS(130),
    [anon_sym_exclude] = ACTIONS(130),
    [anon_sym_derive] = ACTIONS(130),
    [anon_sym_updateCol] = ACTIONS(130),
    [anon_sym_gridValues] = ACTIONS(130),
    [anon_sym_leftJoin] = ACTIONS(130),
    [anon_sym_outerJoin] = ACTIONS(130),
    [anon_sym_linearSearch] = ACTIONS(130),
    [anon_sym_linearSearchIndex] = ACTIONS(130),
    [anon_sym_binPaths] = ACTIONS(130),
    [anon_sym_wt] = ACTIONS(130),
    [anon_sym_tt] = ACTIONS(130),
    [anon_sym_ttFile] = ACTIONS(130),
    [anon_sym_uw] = ACTIONS(130),
    [anon_sym_tuw] = ACTIONS(130),
    [anon_sym_strCmp] = ACTIONS(130),
    [anon_sym_floatCmp] = ACTIONS(130),
    [anon_sym_versionSortCmp] = ACTIONS(130),
    [anon_sym_id] = ACTIONS(130),
    [anon_sym_2id] = ACTIONS(130),
    [anon_sym_3id] = ACTIONS(130),
    [anon_sym_2unpack] = ACTIONS(130),
    [anon_sym_2apply] = ACTIONS(130),
    [anon_sym_2each] = ACTIONS(130),
    [anon_sym_2tuple] = ACTIONS(130),
    [anon_sym_DOTs] = ACTIONS(130),
    [anon_sym_DOTb] = ACTIONS(130),
    [anon_sym_DOTdef] = ACTIONS(130),
    [anon_sym_DOTenv] = ACTIONS(130),
    [sym_string] = ACTIONS(166),
    [sym_format_string] = ACTIONS(166),
    [sym_single_quoted_string] = ACTIONS(166),
    [sym_path] = ACTIONS(166),
    [sym_datetime] = ACTIONS(166),
    [sym_float] = ACTIONS(166),
    [sym_integer] = ACTIONS(162),
    [sym_env_store] = ACTIONS(166),
    [sym_env_check] = ACTIONS(166),
    [sym_env_retrieve] = ACTIONS(162),
    [sym_positional] = ACTIONS(166),
    [sym_var_retrieve] = ACTIONS(166),
    [sym_var_store] = ACTIONS(166),
    [sym_slice_indexer] = ACTIONS(166),
    [sym_indexer] = ACTIONS(166),
    [sym_end_indexer] = ACTIONS(162),
    [sym_start_indexer] = ACTIONS(162),
    [sym_match_arm_dup] = ACTIONS(166),
    [sym_prefix_quote] = ACTIONS(162),
    [anon_sym_GT] = ACTIONS(136),
    [anon_sym_GT_GT] = ACTIONS(138),
    [anon_sym_2_GT] = ACTIONS(136),
    [anon_sym_2_GT_GT] = ACTIONS(136),
    [anon_sym_AMP_GT] = ACTIONS(136),
    [anon_sym_AMP_GT_GT] = ACTIONS(138),
    [anon_sym_LT] = ACTIONS(136),
    [anon_sym_LT_GT] = ACTIONS(138),
    [anon_sym_STAR] = ACTIONS(136),
    [anon_sym_STARb] = ACTIONS(138),
    [anon_sym_CARET] = ACTIONS(136),
    [anon_sym_CARETb] = ACTIONS(138),
    [anon_sym_SEMI] = ACTIONS(140),
    [anon_sym_BANG] = ACTIONS(142),
    [anon_sym_QMARK] = ACTIONS(140),
    [anon_sym_BANG_EQ] = ACTIONS(144),
    [anon_sym_LT_EQ] = ACTIONS(144),
    [anon_sym_GT_EQ] = ACTIONS(144),
    [anon_sym_AMP] = ACTIONS(146),
    [anon_sym_PIPE] = ACTIONS(146),
    [anon_sym_COMMA] = ACTIONS(148),
    [anon_sym_COLON] = ACTIONS(146),
  },
  [21] = {
    [ts_builtin_sym_end] = ACTIONS(269),
    [sym_identifier] = ACTIONS(271),
    [anon_sym_LBRACK] = ACTIONS(271),
    [anon_sym_RBRACK] = ACTIONS(269),
    [anon_sym_LPAREN] = ACTIONS(269),
    [anon_sym_RPAREN] = ACTIONS(269),
    [anon_sym_LBRACE] = ACTIONS(269),
    [anon_sym_RBRACE] = ACTIONS(269),
    [anon_sym_LBRACK_PIPE] = ACTIONS(269),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(271),
    [anon_sym_false] = ACTIONS(271),
    [anon_sym_def] = ACTIONS(271),
    [anon_sym_end] = ACTIONS(271),
    [anon_sym_if] = ACTIONS(271),
    [anon_sym_iff] = ACTIONS(271),
    [anon_sym_else] = ACTIONS(271),
    [anon_sym_else_STAR] = ACTIONS(269),
    [anon_sym_STARif] = ACTIONS(269),
    [anon_sym_loop] = ACTIONS(271),
    [anon_sym_match] = ACTIONS(271),
    [anon_sym_break] = ACTIONS(271),
    [anon_sym_continue] = ACTIONS(271),
    [anon_sym_soe] = ACTIONS(271),
    [anon_sym_not] = ACTIONS(271),
    [anon_sym_and] = ACTIONS(271),
    [anon_sym_or] = ACTIONS(271),
    [anon_sym_read] = ACTIONS(271),
    [anon_sym_str] = ACTIONS(271),
    [anon_sym_as] = ACTIONS(271),
    [anon_sym_type] = ACTIONS(271),
    [anon_sym_try] = ACTIONS(271),
    [anon_sym_fail] = ACTIONS(271),
    [anon_sym_pure] = ACTIONS(271),
    [anon_sym_VER] = ACTIONS(271),
    [anon_sym_x] = ACTIONS(271),
    [anon_sym_int] = ACTIONS(271),
    [anon_sym_float] = ACTIONS(271),
    [anon_sym_bool] = ACTIONS(271),
    [anon_sym_dup] = ACTIONS(271),
    [anon_sym_swap] = ACTIONS(271),
    [anon_sym_drop] = ACTIONS(271),
    [anon_sym_over] = ACTIONS(271),
    [anon_sym_pick] = ACTIONS(271),
    [anon_sym_rot] = ACTIONS(271),
    [anon_sym_DASHrot] = ACTIONS(271),
    [anon_sym_nip] = ACTIONS(271),
    [anon_sym_w] = ACTIONS(271),
    [anon_sym_wl] = ACTIONS(271),
    [anon_sym_we] = ACTIONS(271),
    [anon_sym_wle] = ACTIONS(271),
    [anon_sym_len] = ACTIONS(271),
    [anon_sym_args] = ACTIONS(271),
    [anon_sym_glob] = ACTIONS(271),
    [anon_sym_toFloat] = ACTIONS(271),
    [anon_sym_toInt] = ACTIONS(271),
    [anon_sym_toPath] = ACTIONS(271),
    [anon_sym_toDt] = ACTIONS(271),
    [anon_sym_toGrid] = ACTIONS(271),
    [anon_sym_toCsv] = ACTIONS(271),
    [anon_sym_toCsvCell] = ACTIONS(271),
    [anon_sym_exit] = ACTIONS(271),
    [anon_sym_prompt] = ACTIONS(271),
    [anon_sym_stdin] = ACTIONS(271),
    [anon_sym_COLON_COLON] = ACTIONS(269),
    [anon_sym_foldl] = ACTIONS(271),
    [anon_sym_map] = ACTIONS(271),
    [anon_sym_each] = ACTIONS(271),
    [anon_sym_eachWhile] = ACTIONS(271),
    [anon_sym_filter] = ACTIONS(271),
    [anon_sym_append] = ACTIONS(271),
    [anon_sym_extend] = ACTIONS(271),
    [anon_sym_concat] = ACTIONS(271),
    [anon_sym_reverse] = ACTIONS(271),
    [anon_sym_sort] = ACTIONS(271),
    [anon_sym_sortV] = ACTIONS(271),
    [anon_sym_sortBy] = ACTIONS(271),
    [anon_sym_sortByCmp] = ACTIONS(271),
    [anon_sym_uniq] = ACTIONS(271),
    [anon_sym_zip] = ACTIONS(271),
    [anon_sym_enumerate] = ACTIONS(271),
    [anon_sym_enumerateN] = ACTIONS(271),
    [anon_sym_chunk] = ACTIONS(271),
    [anon_sym_pop] = ACTIONS(271),
    [anon_sym_take] = ACTIONS(271),
    [anon_sym_takeWhile] = ACTIONS(271),
    [anon_sym_skip] = ACTIONS(271),
    [anon_sym_dropWhile] = ACTIONS(271),
    [anon_sym_nth] = ACTIONS(271),
    [anon_sym_insert] = ACTIONS(271),
    [anon_sym_setAt] = ACTIONS(271),
    [anon_sym_del] = ACTIONS(271),
    [anon_sym_sum] = ACTIONS(271),
    [anon_sym_max] = ACTIONS(271),
    [anon_sym_max2] = ACTIONS(271),
    [anon_sym_min] = ACTIONS(271),
    [anon_sym_min2] = ACTIONS(271),
    [anon_sym_abs] = ACTIONS(271),
    [anon_sym_inc] = ACTIONS(271),
    [anon_sym_mod] = ACTIONS(271),
    [anon_sym_floor] = ACTIONS(271),
    [anon_sym_ceil] = ACTIONS(271),
    [anon_sym_round] = ACTIONS(271),
    [anon_sym_lines] = ACTIONS(271),
    [anon_sym_unlines] = ACTIONS(271),
    [anon_sym_unlinesCrLf] = ACTIONS(271),
    [anon_sym_split] = ACTIONS(271),
    [anon_sym_wsplit] = ACTIONS(271),
    [anon_sym_tsplit] = ACTIONS(271),
    [anon_sym_join] = ACTIONS(271),
    [anon_sym_trim] = ACTIONS(271),
    [anon_sym_trimStart] = ACTIONS(271),
    [anon_sym_trimEnd] = ACTIONS(271),
    [anon_sym_startsWith] = ACTIONS(271),
    [anon_sym_endsWith] = ACTIONS(271),
    [anon_sym_lower] = ACTIONS(271),
    [anon_sym_upper] = ACTIONS(271),
    [anon_sym_title] = ACTIONS(271),
    [anon_sym_leftPad] = ACTIONS(271),
    [anon_sym_findReplace] = ACTIONS(271),
    [anon_sym_in] = ACTIONS(271),
    [anon_sym_index] = ACTIONS(271),
    [anon_sym_lastIndexOf] = ACTIONS(271),
    [anon_sym_countSubStr] = ACTIONS(271),
    [anon_sym_parseJson] = ACTIONS(271),
    [anon_sym_parseCsv] = ACTIONS(271),
    [anon_sym_parseHtml] = ACTIONS(271),
    [anon_sym_parseExcel] = ACTIONS(271),
    [anon_sym_readFile] = ACTIONS(271),
    [anon_sym_readFileBytes] = ACTIONS(271),
    [anon_sym_readTsvFile] = ACTIONS(271),
    [anon_sym_writeFile] = ACTIONS(271),
    [anon_sym_appendFile] = ACTIONS(271),
    [anon_sym_fileExists] = ACTIONS(271),
    [anon_sym_isDir] = ACTIONS(271),
    [anon_sym_isFile] = ACTIONS(271),
    [anon_sym_fileSize] = ACTIONS(271),
    [anon_sym_cp] = ACTIONS(271),
    [anon_sym_mv] = ACTIONS(271),
    [anon_sym_rm] = ACTIONS(271),
    [anon_sym_rmf] = ACTIONS(271),
    [anon_sym_mkdir] = ACTIONS(271),
    [anon_sym_mkdirp] = ACTIONS(271),
    [anon_sym_cd] = ACTIONS(271),
    [anon_sym_pwd] = ACTIONS(271),
    [anon_sym_tempFile] = ACTIONS(271),
    [anon_sym_tempFileExt] = ACTIONS(271),
    [anon_sym_tempDir] = ACTIONS(271),
    [anon_sym_lsDir] = ACTIONS(271),
    [anon_sym_files] = ACTIONS(271),
    [anon_sym_dirs] = ACTIONS(271),
    [anon_sym_absPath] = ACTIONS(271),
    [anon_sym_dirname] = ACTIONS(271),
    [anon_sym_basename] = ACTIONS(271),
    [anon_sym_ext] = ACTIONS(271),
    [anon_sym_stem] = ACTIONS(271),
    [anon_sym_isCmd] = ACTIONS(271),
    [anon_sym_hardLink] = ACTIONS(271),
    [anon_sym_sha256sum] = ACTIONS(271),
    [anon_sym_md5] = ACTIONS(271),
    [anon_sym_now] = ACTIONS(271),
    [anon_sym_date] = ACTIONS(271),
    [anon_sym_year] = ACTIONS(271),
    [anon_sym_month] = ACTIONS(271),
    [anon_sym_day] = ACTIONS(271),
    [anon_sym_hour] = ACTIONS(271),
    [anon_sym_minute] = ACTIONS(271),
    [anon_sym_dateFmt] = ACTIONS(271),
    [anon_sym_isoDateFmt] = ACTIONS(271),
    [anon_sym_isoDateTimeFmt] = ACTIONS(271),
    [anon_sym_isWeekend] = ACTIONS(271),
    [anon_sym_isWeekday] = ACTIONS(271),
    [anon_sym_dow] = ACTIONS(271),
    [anon_sym_addDays] = ACTIONS(271),
    [anon_sym_toUnixTime] = ACTIONS(271),
    [anon_sym_toUnixTimeMilli] = ACTIONS(271),
    [anon_sym_toUnixTimeMicro] = ACTIONS(271),
    [anon_sym_toUnixTimeNano] = ACTIONS(271),
    [anon_sym_fromUnixTime] = ACTIONS(271),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(271),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(271),
    [anon_sym_fromUnixTimeNano] = ACTIONS(271),
    [anon_sym_toOleDate] = ACTIONS(271),
    [anon_sym_fromOleDate] = ACTIONS(271),
    [anon_sym_utcToCst] = ACTIONS(271),
    [anon_sym_cstToUtc] = ACTIONS(271),
    [anon_sym_reMatch] = ACTIONS(271),
    [anon_sym_reFindAll] = ACTIONS(271),
    [anon_sym_reFindAllIndex] = ACTIONS(271),
    [anon_sym_reReplace] = ACTIONS(271),
    [anon_sym_reSplit] = ACTIONS(271),
    [anon_sym_just] = ACTIONS(271),
    [anon_sym_none] = ACTIONS(271),
    [anon_sym_isNone] = ACTIONS(271),
    [anon_sym_maybe] = ACTIONS(271),
    [anon_sym_bind] = ACTIONS(271),
    [anon_sym_psub] = ACTIONS(271),
    [anon_sym_typeof] = ACTIONS(271),
    [anon_sym_runtime] = ACTIONS(271),
    [anon_sym_hostname] = ACTIONS(271),
    [anon_sym_httpGet] = ACTIONS(271),
    [anon_sym_httpPost] = ACTIONS(271),
    [anon_sym_urlEncode] = ACTIONS(271),
    [anon_sym_base64encode] = ACTIONS(271),
    [anon_sym_base64decode] = ACTIONS(271),
    [anon_sym_utf8Str] = ACTIONS(271),
    [anon_sym_utf8Bytes] = ACTIONS(271),
    [anon_sym_get] = ACTIONS(271),
    [anon_sym_getDef] = ACTIONS(271),
    [anon_sym_set] = ACTIONS(271),
    [anon_sym_setd] = ACTIONS(271),
    [anon_sym_keys] = ACTIONS(271),
    [anon_sym_values] = ACTIONS(271),
    [anon_sym_keyValues] = ACTIONS(271),
    [anon_sym_all] = ACTIONS(271),
    [anon_sym_any] = ACTIONS(271),
    [anon_sym_cartesian] = ACTIONS(271),
    [anon_sym_groupBy] = ACTIONS(271),
    [anon_sym_listToDict] = ACTIONS(271),
    [anon_sym_repeat] = ACTIONS(271),
    [anon_sym_seq] = ACTIONS(271),
    [anon_sym_tab] = ACTIONS(271),
    [anon_sym_select] = ACTIONS(271),
    [anon_sym_exclude] = ACTIONS(271),
    [anon_sym_derive] = ACTIONS(271),
    [anon_sym_updateCol] = ACTIONS(271),
    [anon_sym_gridValues] = ACTIONS(271),
    [anon_sym_leftJoin] = ACTIONS(271),
    [anon_sym_outerJoin] = ACTIONS(271),
    [anon_sym_linearSearch] = ACTIONS(271),
    [anon_sym_linearSearchIndex] = ACTIONS(271),
    [anon_sym_binPaths] = ACTIONS(271),
    [anon_sym_wt] = ACTIONS(271),
    [anon_sym_tt] = ACTIONS(271),
    [anon_sym_ttFile] = ACTIONS(271),
    [anon_sym_uw] = ACTIONS(271),
    [anon_sym_tuw] = ACTIONS(271),
    [anon_sym_strCmp] = ACTIONS(271),
    [anon_sym_floatCmp] = ACTIONS(271),
    [anon_sym_versionSortCmp] = ACTIONS(271),
    [anon_sym_id] = ACTIONS(271),
    [anon_sym_2id] = ACTIONS(271),
    [anon_sym_3id] = ACTIONS(271),
    [anon_sym_2unpack] = ACTIONS(271),
    [anon_sym_2apply] = ACTIONS(271),
    [anon_sym_2each] = ACTIONS(271),
    [anon_sym_2tuple] = ACTIONS(271),
    [anon_sym_DOTs] = ACTIONS(271),
    [anon_sym_DOTb] = ACTIONS(271),
    [anon_sym_DOTdef] = ACTIONS(271),
    [anon_sym_DOTenv] = ACTIONS(271),
    [sym_string] = ACTIONS(269),
    [sym_format_string] = ACTIONS(269),
    [sym_single_quoted_string] = ACTIONS(269),
    [sym_path] = ACTIONS(269),
    [sym_datetime] = ACTIONS(269),
    [sym_float] = ACTIONS(269),
    [sym_integer] = ACTIONS(271),
    [sym_env_store] = ACTIONS(269),
    [sym_env_check] = ACTIONS(269),
    [sym_env_retrieve] = ACTIONS(271),
    [sym_positional] = ACTIONS(269),
    [sym_var_retrieve] = ACTIONS(269),
    [sym_var_store] = ACTIONS(269),
    [sym_slice_indexer] = ACTIONS(269),
    [sym_indexer] = ACTIONS(269),
    [sym_end_indexer] = ACTIONS(271),
    [sym_start_indexer] = ACTIONS(271),
    [sym_match_arm_dup] = ACTIONS(269),
    [sym_prefix_quote] = ACTIONS(271),
    [anon_sym_GT] = ACTIONS(271),
    [anon_sym_GT_GT] = ACTIONS(269),
    [anon_sym_2_GT] = ACTIONS(271),
    [anon_sym_2_GT_GT] = ACTIONS(271),
    [anon_sym_AMP_GT] = ACTIONS(271),
    [anon_sym_AMP_GT_GT] = ACTIONS(269),
    [anon_sym_LT] = ACTIONS(271),
    [anon_sym_LT_GT] = ACTIONS(269),
    [anon_sym_STAR] = ACTIONS(271),
    [anon_sym_STARb] = ACTIONS(269),
    [anon_sym_CARET] = ACTIONS(271),
    [anon_sym_CARETb] = ACTIONS(269),
    [anon_sym_SEMI] = ACTIONS(269),
    [anon_sym_BANG] = ACTIONS(271),
    [anon_sym_QMARK] = ACTIONS(269),
    [anon_sym_BANG_EQ] = ACTIONS(269),
    [anon_sym_LT_EQ] = ACTIONS(269),
    [anon_sym_GT_EQ] = ACTIONS(269),
    [anon_sym_AMP] = ACTIONS(271),
    [anon_sym_PIPE] = ACTIONS(269),
    [anon_sym_COMMA] = ACTIONS(269),
    [anon_sym_COLON] = ACTIONS(271),
  },
  [22] = {
    [ts_builtin_sym_end] = ACTIONS(273),
    [sym_identifier] = ACTIONS(275),
    [anon_sym_LBRACK] = ACTIONS(275),
    [anon_sym_RBRACK] = ACTIONS(273),
    [anon_sym_LPAREN] = ACTIONS(273),
    [anon_sym_RPAREN] = ACTIONS(273),
    [anon_sym_LBRACE] = ACTIONS(273),
    [anon_sym_RBRACE] = ACTIONS(273),
    [anon_sym_LBRACK_PIPE] = ACTIONS(273),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(275),
    [anon_sym_false] = ACTIONS(275),
    [anon_sym_def] = ACTIONS(275),
    [anon_sym_end] = ACTIONS(275),
    [anon_sym_if] = ACTIONS(275),
    [anon_sym_iff] = ACTIONS(275),
    [anon_sym_else] = ACTIONS(275),
    [anon_sym_else_STAR] = ACTIONS(273),
    [anon_sym_STARif] = ACTIONS(273),
    [anon_sym_loop] = ACTIONS(275),
    [anon_sym_match] = ACTIONS(275),
    [anon_sym_break] = ACTIONS(275),
    [anon_sym_continue] = ACTIONS(275),
    [anon_sym_soe] = ACTIONS(275),
    [anon_sym_not] = ACTIONS(275),
    [anon_sym_and] = ACTIONS(275),
    [anon_sym_or] = ACTIONS(275),
    [anon_sym_read] = ACTIONS(275),
    [anon_sym_str] = ACTIONS(275),
    [anon_sym_as] = ACTIONS(275),
    [anon_sym_type] = ACTIONS(275),
    [anon_sym_try] = ACTIONS(275),
    [anon_sym_fail] = ACTIONS(275),
    [anon_sym_pure] = ACTIONS(275),
    [anon_sym_VER] = ACTIONS(275),
    [anon_sym_x] = ACTIONS(275),
    [anon_sym_int] = ACTIONS(275),
    [anon_sym_float] = ACTIONS(275),
    [anon_sym_bool] = ACTIONS(275),
    [anon_sym_dup] = ACTIONS(275),
    [anon_sym_swap] = ACTIONS(275),
    [anon_sym_drop] = ACTIONS(275),
    [anon_sym_over] = ACTIONS(275),
    [anon_sym_pick] = ACTIONS(275),
    [anon_sym_rot] = ACTIONS(275),
    [anon_sym_DASHrot] = ACTIONS(275),
    [anon_sym_nip] = ACTIONS(275),
    [anon_sym_w] = ACTIONS(275),
    [anon_sym_wl] = ACTIONS(275),
    [anon_sym_we] = ACTIONS(275),
    [anon_sym_wle] = ACTIONS(275),
    [anon_sym_len] = ACTIONS(275),
    [anon_sym_args] = ACTIONS(275),
    [anon_sym_glob] = ACTIONS(275),
    [anon_sym_toFloat] = ACTIONS(275),
    [anon_sym_toInt] = ACTIONS(275),
    [anon_sym_toPath] = ACTIONS(275),
    [anon_sym_toDt] = ACTIONS(275),
    [anon_sym_toGrid] = ACTIONS(275),
    [anon_sym_toCsv] = ACTIONS(275),
    [anon_sym_toCsvCell] = ACTIONS(275),
    [anon_sym_exit] = ACTIONS(275),
    [anon_sym_prompt] = ACTIONS(275),
    [anon_sym_stdin] = ACTIONS(275),
    [anon_sym_COLON_COLON] = ACTIONS(273),
    [anon_sym_foldl] = ACTIONS(275),
    [anon_sym_map] = ACTIONS(275),
    [anon_sym_each] = ACTIONS(275),
    [anon_sym_eachWhile] = ACTIONS(275),
    [anon_sym_filter] = ACTIONS(275),
    [anon_sym_append] = ACTIONS(275),
    [anon_sym_extend] = ACTIONS(275),
    [anon_sym_concat] = ACTIONS(275),
    [anon_sym_reverse] = ACTIONS(275),
    [anon_sym_sort] = ACTIONS(275),
    [anon_sym_sortV] = ACTIONS(275),
    [anon_sym_sortBy] = ACTIONS(275),
    [anon_sym_sortByCmp] = ACTIONS(275),
    [anon_sym_uniq] = ACTIONS(275),
    [anon_sym_zip] = ACTIONS(275),
    [anon_sym_enumerate] = ACTIONS(275),
    [anon_sym_enumerateN] = ACTIONS(275),
    [anon_sym_chunk] = ACTIONS(275),
    [anon_sym_pop] = ACTIONS(275),
    [anon_sym_take] = ACTIONS(275),
    [anon_sym_takeWhile] = ACTIONS(275),
    [anon_sym_skip] = ACTIONS(275),
    [anon_sym_dropWhile] = ACTIONS(275),
    [anon_sym_nth] = ACTIONS(275),
    [anon_sym_insert] = ACTIONS(275),
    [anon_sym_setAt] = ACTIONS(275),
    [anon_sym_del] = ACTIONS(275),
    [anon_sym_sum] = ACTIONS(275),
    [anon_sym_max] = ACTIONS(275),
    [anon_sym_max2] = ACTIONS(275),
    [anon_sym_min] = ACTIONS(275),
    [anon_sym_min2] = ACTIONS(275),
    [anon_sym_abs] = ACTIONS(275),
    [anon_sym_inc] = ACTIONS(275),
    [anon_sym_mod] = ACTIONS(275),
    [anon_sym_floor] = ACTIONS(275),
    [anon_sym_ceil] = ACTIONS(275),
    [anon_sym_round] = ACTIONS(275),
    [anon_sym_lines] = ACTIONS(275),
    [anon_sym_unlines] = ACTIONS(275),
    [anon_sym_unlinesCrLf] = ACTIONS(275),
    [anon_sym_split] = ACTIONS(275),
    [anon_sym_wsplit] = ACTIONS(275),
    [anon_sym_tsplit] = ACTIONS(275),
    [anon_sym_join] = ACTIONS(275),
    [anon_sym_trim] = ACTIONS(275),
    [anon_sym_trimStart] = ACTIONS(275),
    [anon_sym_trimEnd] = ACTIONS(275),
    [anon_sym_startsWith] = ACTIONS(275),
    [anon_sym_endsWith] = ACTIONS(275),
    [anon_sym_lower] = ACTIONS(275),
    [anon_sym_upper] = ACTIONS(275),
    [anon_sym_title] = ACTIONS(275),
    [anon_sym_leftPad] = ACTIONS(275),
    [anon_sym_findReplace] = ACTIONS(275),
    [anon_sym_in] = ACTIONS(275),
    [anon_sym_index] = ACTIONS(275),
    [anon_sym_lastIndexOf] = ACTIONS(275),
    [anon_sym_countSubStr] = ACTIONS(275),
    [anon_sym_parseJson] = ACTIONS(275),
    [anon_sym_parseCsv] = ACTIONS(275),
    [anon_sym_parseHtml] = ACTIONS(275),
    [anon_sym_parseExcel] = ACTIONS(275),
    [anon_sym_readFile] = ACTIONS(275),
    [anon_sym_readFileBytes] = ACTIONS(275),
    [anon_sym_readTsvFile] = ACTIONS(275),
    [anon_sym_writeFile] = ACTIONS(275),
    [anon_sym_appendFile] = ACTIONS(275),
    [anon_sym_fileExists] = ACTIONS(275),
    [anon_sym_isDir] = ACTIONS(275),
    [anon_sym_isFile] = ACTIONS(275),
    [anon_sym_fileSize] = ACTIONS(275),
    [anon_sym_cp] = ACTIONS(275),
    [anon_sym_mv] = ACTIONS(275),
    [anon_sym_rm] = ACTIONS(275),
    [anon_sym_rmf] = ACTIONS(275),
    [anon_sym_mkdir] = ACTIONS(275),
    [anon_sym_mkdirp] = ACTIONS(275),
    [anon_sym_cd] = ACTIONS(275),
    [anon_sym_pwd] = ACTIONS(275),
    [anon_sym_tempFile] = ACTIONS(275),
    [anon_sym_tempFileExt] = ACTIONS(275),
    [anon_sym_tempDir] = ACTIONS(275),
    [anon_sym_lsDir] = ACTIONS(275),
    [anon_sym_files] = ACTIONS(275),
    [anon_sym_dirs] = ACTIONS(275),
    [anon_sym_absPath] = ACTIONS(275),
    [anon_sym_dirname] = ACTIONS(275),
    [anon_sym_basename] = ACTIONS(275),
    [anon_sym_ext] = ACTIONS(275),
    [anon_sym_stem] = ACTIONS(275),
    [anon_sym_isCmd] = ACTIONS(275),
    [anon_sym_hardLink] = ACTIONS(275),
    [anon_sym_sha256sum] = ACTIONS(275),
    [anon_sym_md5] = ACTIONS(275),
    [anon_sym_now] = ACTIONS(275),
    [anon_sym_date] = ACTIONS(275),
    [anon_sym_year] = ACTIONS(275),
    [anon_sym_month] = ACTIONS(275),
    [anon_sym_day] = ACTIONS(275),
    [anon_sym_hour] = ACTIONS(275),
    [anon_sym_minute] = ACTIONS(275),
    [anon_sym_dateFmt] = ACTIONS(275),
    [anon_sym_isoDateFmt] = ACTIONS(275),
    [anon_sym_isoDateTimeFmt] = ACTIONS(275),
    [anon_sym_isWeekend] = ACTIONS(275),
    [anon_sym_isWeekday] = ACTIONS(275),
    [anon_sym_dow] = ACTIONS(275),
    [anon_sym_addDays] = ACTIONS(275),
    [anon_sym_toUnixTime] = ACTIONS(275),
    [anon_sym_toUnixTimeMilli] = ACTIONS(275),
    [anon_sym_toUnixTimeMicro] = ACTIONS(275),
    [anon_sym_toUnixTimeNano] = ACTIONS(275),
    [anon_sym_fromUnixTime] = ACTIONS(275),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(275),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(275),
    [anon_sym_fromUnixTimeNano] = ACTIONS(275),
    [anon_sym_toOleDate] = ACTIONS(275),
    [anon_sym_fromOleDate] = ACTIONS(275),
    [anon_sym_utcToCst] = ACTIONS(275),
    [anon_sym_cstToUtc] = ACTIONS(275),
    [anon_sym_reMatch] = ACTIONS(275),
    [anon_sym_reFindAll] = ACTIONS(275),
    [anon_sym_reFindAllIndex] = ACTIONS(275),
    [anon_sym_reReplace] = ACTIONS(275),
    [anon_sym_reSplit] = ACTIONS(275),
    [anon_sym_just] = ACTIONS(275),
    [anon_sym_none] = ACTIONS(275),
    [anon_sym_isNone] = ACTIONS(275),
    [anon_sym_maybe] = ACTIONS(275),
    [anon_sym_bind] = ACTIONS(275),
    [anon_sym_psub] = ACTIONS(275),
    [anon_sym_typeof] = ACTIONS(275),
    [anon_sym_runtime] = ACTIONS(275),
    [anon_sym_hostname] = ACTIONS(275),
    [anon_sym_httpGet] = ACTIONS(275),
    [anon_sym_httpPost] = ACTIONS(275),
    [anon_sym_urlEncode] = ACTIONS(275),
    [anon_sym_base64encode] = ACTIONS(275),
    [anon_sym_base64decode] = ACTIONS(275),
    [anon_sym_utf8Str] = ACTIONS(275),
    [anon_sym_utf8Bytes] = ACTIONS(275),
    [anon_sym_get] = ACTIONS(275),
    [anon_sym_getDef] = ACTIONS(275),
    [anon_sym_set] = ACTIONS(275),
    [anon_sym_setd] = ACTIONS(275),
    [anon_sym_keys] = ACTIONS(275),
    [anon_sym_values] = ACTIONS(275),
    [anon_sym_keyValues] = ACTIONS(275),
    [anon_sym_all] = ACTIONS(275),
    [anon_sym_any] = ACTIONS(275),
    [anon_sym_cartesian] = ACTIONS(275),
    [anon_sym_groupBy] = ACTIONS(275),
    [anon_sym_listToDict] = ACTIONS(275),
    [anon_sym_repeat] = ACTIONS(275),
    [anon_sym_seq] = ACTIONS(275),
    [anon_sym_tab] = ACTIONS(275),
    [anon_sym_select] = ACTIONS(275),
    [anon_sym_exclude] = ACTIONS(275),
    [anon_sym_derive] = ACTIONS(275),
    [anon_sym_updateCol] = ACTIONS(275),
    [anon_sym_gridValues] = ACTIONS(275),
    [anon_sym_leftJoin] = ACTIONS(275),
    [anon_sym_outerJoin] = ACTIONS(275),
    [anon_sym_linearSearch] = ACTIONS(275),
    [anon_sym_linearSearchIndex] = ACTIONS(275),
    [anon_sym_binPaths] = ACTIONS(275),
    [anon_sym_wt] = ACTIONS(275),
    [anon_sym_tt] = ACTIONS(275),
    [anon_sym_ttFile] = ACTIONS(275),
    [anon_sym_uw] = ACTIONS(275),
    [anon_sym_tuw] = ACTIONS(275),
    [anon_sym_strCmp] = ACTIONS(275),
    [anon_sym_floatCmp] = ACTIONS(275),
    [anon_sym_versionSortCmp] = ACTIONS(275),
    [anon_sym_id] = ACTIONS(275),
    [anon_sym_2id] = ACTIONS(275),
    [anon_sym_3id] = ACTIONS(275),
    [anon_sym_2unpack] = ACTIONS(275),
    [anon_sym_2apply] = ACTIONS(275),
    [anon_sym_2each] = ACTIONS(275),
    [anon_sym_2tuple] = ACTIONS(275),
    [anon_sym_DOTs] = ACTIONS(275),
    [anon_sym_DOTb] = ACTIONS(275),
    [anon_sym_DOTdef] = ACTIONS(275),
    [anon_sym_DOTenv] = ACTIONS(275),
    [sym_string] = ACTIONS(273),
    [sym_format_string] = ACTIONS(273),
    [sym_single_quoted_string] = ACTIONS(273),
    [sym_path] = ACTIONS(273),
    [sym_datetime] = ACTIONS(273),
    [sym_float] = ACTIONS(273),
    [sym_integer] = ACTIONS(275),
    [sym_env_store] = ACTIONS(273),
    [sym_env_check] = ACTIONS(273),
    [sym_env_retrieve] = ACTIONS(275),
    [sym_positional] = ACTIONS(273),
    [sym_var_retrieve] = ACTIONS(273),
    [sym_var_store] = ACTIONS(273),
    [sym_slice_indexer] = ACTIONS(273),
    [sym_indexer] = ACTIONS(273),
    [sym_end_indexer] = ACTIONS(275),
    [sym_start_indexer] = ACTIONS(275),
    [sym_match_arm_dup] = ACTIONS(273),
    [sym_prefix_quote] = ACTIONS(275),
    [anon_sym_GT] = ACTIONS(275),
    [anon_sym_GT_GT] = ACTIONS(273),
    [anon_sym_2_GT] = ACTIONS(275),
    [anon_sym_2_GT_GT] = ACTIONS(275),
    [anon_sym_AMP_GT] = ACTIONS(275),
    [anon_sym_AMP_GT_GT] = ACTIONS(273),
    [anon_sym_LT] = ACTIONS(275),
    [anon_sym_LT_GT] = ACTIONS(273),
    [anon_sym_STAR] = ACTIONS(275),
    [anon_sym_STARb] = ACTIONS(273),
    [anon_sym_CARET] = ACTIONS(275),
    [anon_sym_CARETb] = ACTIONS(273),
    [anon_sym_SEMI] = ACTIONS(273),
    [anon_sym_BANG] = ACTIONS(275),
    [anon_sym_QMARK] = ACTIONS(273),
    [anon_sym_BANG_EQ] = ACTIONS(273),
    [anon_sym_LT_EQ] = ACTIONS(273),
    [anon_sym_GT_EQ] = ACTIONS(273),
    [anon_sym_AMP] = ACTIONS(275),
    [anon_sym_PIPE] = ACTIONS(273),
    [anon_sym_COMMA] = ACTIONS(273),
    [anon_sym_COLON] = ACTIONS(275),
  },
  [23] = {
    [ts_builtin_sym_end] = ACTIONS(277),
    [sym_identifier] = ACTIONS(279),
    [anon_sym_LBRACK] = ACTIONS(279),
    [anon_sym_RBRACK] = ACTIONS(277),
    [anon_sym_LPAREN] = ACTIONS(277),
    [anon_sym_RPAREN] = ACTIONS(277),
    [anon_sym_LBRACE] = ACTIONS(277),
    [anon_sym_RBRACE] = ACTIONS(277),
    [anon_sym_LBRACK_PIPE] = ACTIONS(277),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(279),
    [anon_sym_false] = ACTIONS(279),
    [anon_sym_def] = ACTIONS(279),
    [anon_sym_end] = ACTIONS(279),
    [anon_sym_if] = ACTIONS(279),
    [anon_sym_iff] = ACTIONS(279),
    [anon_sym_else] = ACTIONS(279),
    [anon_sym_else_STAR] = ACTIONS(277),
    [anon_sym_STARif] = ACTIONS(277),
    [anon_sym_loop] = ACTIONS(279),
    [anon_sym_match] = ACTIONS(279),
    [anon_sym_break] = ACTIONS(279),
    [anon_sym_continue] = ACTIONS(279),
    [anon_sym_soe] = ACTIONS(279),
    [anon_sym_not] = ACTIONS(279),
    [anon_sym_and] = ACTIONS(279),
    [anon_sym_or] = ACTIONS(279),
    [anon_sym_read] = ACTIONS(279),
    [anon_sym_str] = ACTIONS(279),
    [anon_sym_as] = ACTIONS(279),
    [anon_sym_type] = ACTIONS(279),
    [anon_sym_try] = ACTIONS(279),
    [anon_sym_fail] = ACTIONS(279),
    [anon_sym_pure] = ACTIONS(279),
    [anon_sym_VER] = ACTIONS(279),
    [anon_sym_x] = ACTIONS(279),
    [anon_sym_int] = ACTIONS(279),
    [anon_sym_float] = ACTIONS(279),
    [anon_sym_bool] = ACTIONS(279),
    [anon_sym_dup] = ACTIONS(279),
    [anon_sym_swap] = ACTIONS(279),
    [anon_sym_drop] = ACTIONS(279),
    [anon_sym_over] = ACTIONS(279),
    [anon_sym_pick] = ACTIONS(279),
    [anon_sym_rot] = ACTIONS(279),
    [anon_sym_DASHrot] = ACTIONS(279),
    [anon_sym_nip] = ACTIONS(279),
    [anon_sym_w] = ACTIONS(279),
    [anon_sym_wl] = ACTIONS(279),
    [anon_sym_we] = ACTIONS(279),
    [anon_sym_wle] = ACTIONS(279),
    [anon_sym_len] = ACTIONS(279),
    [anon_sym_args] = ACTIONS(279),
    [anon_sym_glob] = ACTIONS(279),
    [anon_sym_toFloat] = ACTIONS(279),
    [anon_sym_toInt] = ACTIONS(279),
    [anon_sym_toPath] = ACTIONS(279),
    [anon_sym_toDt] = ACTIONS(279),
    [anon_sym_toGrid] = ACTIONS(279),
    [anon_sym_toCsv] = ACTIONS(279),
    [anon_sym_toCsvCell] = ACTIONS(279),
    [anon_sym_exit] = ACTIONS(279),
    [anon_sym_prompt] = ACTIONS(279),
    [anon_sym_stdin] = ACTIONS(279),
    [anon_sym_COLON_COLON] = ACTIONS(277),
    [anon_sym_foldl] = ACTIONS(279),
    [anon_sym_map] = ACTIONS(279),
    [anon_sym_each] = ACTIONS(279),
    [anon_sym_eachWhile] = ACTIONS(279),
    [anon_sym_filter] = ACTIONS(279),
    [anon_sym_append] = ACTIONS(279),
    [anon_sym_extend] = ACTIONS(279),
    [anon_sym_concat] = ACTIONS(279),
    [anon_sym_reverse] = ACTIONS(279),
    [anon_sym_sort] = ACTIONS(279),
    [anon_sym_sortV] = ACTIONS(279),
    [anon_sym_sortBy] = ACTIONS(279),
    [anon_sym_sortByCmp] = ACTIONS(279),
    [anon_sym_uniq] = ACTIONS(279),
    [anon_sym_zip] = ACTIONS(279),
    [anon_sym_enumerate] = ACTIONS(279),
    [anon_sym_enumerateN] = ACTIONS(279),
    [anon_sym_chunk] = ACTIONS(279),
    [anon_sym_pop] = ACTIONS(279),
    [anon_sym_take] = ACTIONS(279),
    [anon_sym_takeWhile] = ACTIONS(279),
    [anon_sym_skip] = ACTIONS(279),
    [anon_sym_dropWhile] = ACTIONS(279),
    [anon_sym_nth] = ACTIONS(279),
    [anon_sym_insert] = ACTIONS(279),
    [anon_sym_setAt] = ACTIONS(279),
    [anon_sym_del] = ACTIONS(279),
    [anon_sym_sum] = ACTIONS(279),
    [anon_sym_max] = ACTIONS(279),
    [anon_sym_max2] = ACTIONS(279),
    [anon_sym_min] = ACTIONS(279),
    [anon_sym_min2] = ACTIONS(279),
    [anon_sym_abs] = ACTIONS(279),
    [anon_sym_inc] = ACTIONS(279),
    [anon_sym_mod] = ACTIONS(279),
    [anon_sym_floor] = ACTIONS(279),
    [anon_sym_ceil] = ACTIONS(279),
    [anon_sym_round] = ACTIONS(279),
    [anon_sym_lines] = ACTIONS(279),
    [anon_sym_unlines] = ACTIONS(279),
    [anon_sym_unlinesCrLf] = ACTIONS(279),
    [anon_sym_split] = ACTIONS(279),
    [anon_sym_wsplit] = ACTIONS(279),
    [anon_sym_tsplit] = ACTIONS(279),
    [anon_sym_join] = ACTIONS(279),
    [anon_sym_trim] = ACTIONS(279),
    [anon_sym_trimStart] = ACTIONS(279),
    [anon_sym_trimEnd] = ACTIONS(279),
    [anon_sym_startsWith] = ACTIONS(279),
    [anon_sym_endsWith] = ACTIONS(279),
    [anon_sym_lower] = ACTIONS(279),
    [anon_sym_upper] = ACTIONS(279),
    [anon_sym_title] = ACTIONS(279),
    [anon_sym_leftPad] = ACTIONS(279),
    [anon_sym_findReplace] = ACTIONS(279),
    [anon_sym_in] = ACTIONS(279),
    [anon_sym_index] = ACTIONS(279),
    [anon_sym_lastIndexOf] = ACTIONS(279),
    [anon_sym_countSubStr] = ACTIONS(279),
    [anon_sym_parseJson] = ACTIONS(279),
    [anon_sym_parseCsv] = ACTIONS(279),
    [anon_sym_parseHtml] = ACTIONS(279),
    [anon_sym_parseExcel] = ACTIONS(279),
    [anon_sym_readFile] = ACTIONS(279),
    [anon_sym_readFileBytes] = ACTIONS(279),
    [anon_sym_readTsvFile] = ACTIONS(279),
    [anon_sym_writeFile] = ACTIONS(279),
    [anon_sym_appendFile] = ACTIONS(279),
    [anon_sym_fileExists] = ACTIONS(279),
    [anon_sym_isDir] = ACTIONS(279),
    [anon_sym_isFile] = ACTIONS(279),
    [anon_sym_fileSize] = ACTIONS(279),
    [anon_sym_cp] = ACTIONS(279),
    [anon_sym_mv] = ACTIONS(279),
    [anon_sym_rm] = ACTIONS(279),
    [anon_sym_rmf] = ACTIONS(279),
    [anon_sym_mkdir] = ACTIONS(279),
    [anon_sym_mkdirp] = ACTIONS(279),
    [anon_sym_cd] = ACTIONS(279),
    [anon_sym_pwd] = ACTIONS(279),
    [anon_sym_tempFile] = ACTIONS(279),
    [anon_sym_tempFileExt] = ACTIONS(279),
    [anon_sym_tempDir] = ACTIONS(279),
    [anon_sym_lsDir] = ACTIONS(279),
    [anon_sym_files] = ACTIONS(279),
    [anon_sym_dirs] = ACTIONS(279),
    [anon_sym_absPath] = ACTIONS(279),
    [anon_sym_dirname] = ACTIONS(279),
    [anon_sym_basename] = ACTIONS(279),
    [anon_sym_ext] = ACTIONS(279),
    [anon_sym_stem] = ACTIONS(279),
    [anon_sym_isCmd] = ACTIONS(279),
    [anon_sym_hardLink] = ACTIONS(279),
    [anon_sym_sha256sum] = ACTIONS(279),
    [anon_sym_md5] = ACTIONS(279),
    [anon_sym_now] = ACTIONS(279),
    [anon_sym_date] = ACTIONS(279),
    [anon_sym_year] = ACTIONS(279),
    [anon_sym_month] = ACTIONS(279),
    [anon_sym_day] = ACTIONS(279),
    [anon_sym_hour] = ACTIONS(279),
    [anon_sym_minute] = ACTIONS(279),
    [anon_sym_dateFmt] = ACTIONS(279),
    [anon_sym_isoDateFmt] = ACTIONS(279),
    [anon_sym_isoDateTimeFmt] = ACTIONS(279),
    [anon_sym_isWeekend] = ACTIONS(279),
    [anon_sym_isWeekday] = ACTIONS(279),
    [anon_sym_dow] = ACTIONS(279),
    [anon_sym_addDays] = ACTIONS(279),
    [anon_sym_toUnixTime] = ACTIONS(279),
    [anon_sym_toUnixTimeMilli] = ACTIONS(279),
    [anon_sym_toUnixTimeMicro] = ACTIONS(279),
    [anon_sym_toUnixTimeNano] = ACTIONS(279),
    [anon_sym_fromUnixTime] = ACTIONS(279),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(279),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(279),
    [anon_sym_fromUnixTimeNano] = ACTIONS(279),
    [anon_sym_toOleDate] = ACTIONS(279),
    [anon_sym_fromOleDate] = ACTIONS(279),
    [anon_sym_utcToCst] = ACTIONS(279),
    [anon_sym_cstToUtc] = ACTIONS(279),
    [anon_sym_reMatch] = ACTIONS(279),
    [anon_sym_reFindAll] = ACTIONS(279),
    [anon_sym_reFindAllIndex] = ACTIONS(279),
    [anon_sym_reReplace] = ACTIONS(279),
    [anon_sym_reSplit] = ACTIONS(279),
    [anon_sym_just] = ACTIONS(279),
    [anon_sym_none] = ACTIONS(279),
    [anon_sym_isNone] = ACTIONS(279),
    [anon_sym_maybe] = ACTIONS(279),
    [anon_sym_bind] = ACTIONS(279),
    [anon_sym_psub] = ACTIONS(279),
    [anon_sym_typeof] = ACTIONS(279),
    [anon_sym_runtime] = ACTIONS(279),
    [anon_sym_hostname] = ACTIONS(279),
    [anon_sym_httpGet] = ACTIONS(279),
    [anon_sym_httpPost] = ACTIONS(279),
    [anon_sym_urlEncode] = ACTIONS(279),
    [anon_sym_base64encode] = ACTIONS(279),
    [anon_sym_base64decode] = ACTIONS(279),
    [anon_sym_utf8Str] = ACTIONS(279),
    [anon_sym_utf8Bytes] = ACTIONS(279),
    [anon_sym_get] = ACTIONS(279),
    [anon_sym_getDef] = ACTIONS(279),
    [anon_sym_set] = ACTIONS(279),
    [anon_sym_setd] = ACTIONS(279),
    [anon_sym_keys] = ACTIONS(279),
    [anon_sym_values] = ACTIONS(279),
    [anon_sym_keyValues] = ACTIONS(279),
    [anon_sym_all] = ACTIONS(279),
    [anon_sym_any] = ACTIONS(279),
    [anon_sym_cartesian] = ACTIONS(279),
    [anon_sym_groupBy] = ACTIONS(279),
    [anon_sym_listToDict] = ACTIONS(279),
    [anon_sym_repeat] = ACTIONS(279),
    [anon_sym_seq] = ACTIONS(279),
    [anon_sym_tab] = ACTIONS(279),
    [anon_sym_select] = ACTIONS(279),
    [anon_sym_exclude] = ACTIONS(279),
    [anon_sym_derive] = ACTIONS(279),
    [anon_sym_updateCol] = ACTIONS(279),
    [anon_sym_gridValues] = ACTIONS(279),
    [anon_sym_leftJoin] = ACTIONS(279),
    [anon_sym_outerJoin] = ACTIONS(279),
    [anon_sym_linearSearch] = ACTIONS(279),
    [anon_sym_linearSearchIndex] = ACTIONS(279),
    [anon_sym_binPaths] = ACTIONS(279),
    [anon_sym_wt] = ACTIONS(279),
    [anon_sym_tt] = ACTIONS(279),
    [anon_sym_ttFile] = ACTIONS(279),
    [anon_sym_uw] = ACTIONS(279),
    [anon_sym_tuw] = ACTIONS(279),
    [anon_sym_strCmp] = ACTIONS(279),
    [anon_sym_floatCmp] = ACTIONS(279),
    [anon_sym_versionSortCmp] = ACTIONS(279),
    [anon_sym_id] = ACTIONS(279),
    [anon_sym_2id] = ACTIONS(279),
    [anon_sym_3id] = ACTIONS(279),
    [anon_sym_2unpack] = ACTIONS(279),
    [anon_sym_2apply] = ACTIONS(279),
    [anon_sym_2each] = ACTIONS(279),
    [anon_sym_2tuple] = ACTIONS(279),
    [anon_sym_DOTs] = ACTIONS(279),
    [anon_sym_DOTb] = ACTIONS(279),
    [anon_sym_DOTdef] = ACTIONS(279),
    [anon_sym_DOTenv] = ACTIONS(279),
    [sym_string] = ACTIONS(277),
    [sym_format_string] = ACTIONS(277),
    [sym_single_quoted_string] = ACTIONS(277),
    [sym_path] = ACTIONS(277),
    [sym_datetime] = ACTIONS(277),
    [sym_float] = ACTIONS(277),
    [sym_integer] = ACTIONS(279),
    [sym_env_store] = ACTIONS(277),
    [sym_env_check] = ACTIONS(277),
    [sym_env_retrieve] = ACTIONS(279),
    [sym_positional] = ACTIONS(277),
    [sym_var_retrieve] = ACTIONS(277),
    [sym_var_store] = ACTIONS(277),
    [sym_slice_indexer] = ACTIONS(277),
    [sym_indexer] = ACTIONS(277),
    [sym_end_indexer] = ACTIONS(279),
    [sym_start_indexer] = ACTIONS(279),
    [sym_match_arm_dup] = ACTIONS(277),
    [sym_prefix_quote] = ACTIONS(279),
    [anon_sym_GT] = ACTIONS(279),
    [anon_sym_GT_GT] = ACTIONS(277),
    [anon_sym_2_GT] = ACTIONS(279),
    [anon_sym_2_GT_GT] = ACTIONS(279),
    [anon_sym_AMP_GT] = ACTIONS(279),
    [anon_sym_AMP_GT_GT] = ACTIONS(277),
    [anon_sym_LT] = ACTIONS(279),
    [anon_sym_LT_GT] = ACTIONS(277),
    [anon_sym_STAR] = ACTIONS(279),
    [anon_sym_STARb] = ACTIONS(277),
    [anon_sym_CARET] = ACTIONS(279),
    [anon_sym_CARETb] = ACTIONS(277),
    [anon_sym_SEMI] = ACTIONS(277),
    [anon_sym_BANG] = ACTIONS(279),
    [anon_sym_QMARK] = ACTIONS(277),
    [anon_sym_BANG_EQ] = ACTIONS(277),
    [anon_sym_LT_EQ] = ACTIONS(277),
    [anon_sym_GT_EQ] = ACTIONS(277),
    [anon_sym_AMP] = ACTIONS(279),
    [anon_sym_PIPE] = ACTIONS(277),
    [anon_sym_COMMA] = ACTIONS(277),
    [anon_sym_COLON] = ACTIONS(279),
  },
  [24] = {
    [ts_builtin_sym_end] = ACTIONS(281),
    [sym_identifier] = ACTIONS(283),
    [anon_sym_LBRACK] = ACTIONS(283),
    [anon_sym_RBRACK] = ACTIONS(281),
    [anon_sym_LPAREN] = ACTIONS(281),
    [anon_sym_RPAREN] = ACTIONS(281),
    [anon_sym_LBRACE] = ACTIONS(281),
    [anon_sym_RBRACE] = ACTIONS(281),
    [anon_sym_LBRACK_PIPE] = ACTIONS(281),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(283),
    [anon_sym_false] = ACTIONS(283),
    [anon_sym_def] = ACTIONS(283),
    [anon_sym_end] = ACTIONS(283),
    [anon_sym_if] = ACTIONS(283),
    [anon_sym_iff] = ACTIONS(283),
    [anon_sym_else] = ACTIONS(283),
    [anon_sym_else_STAR] = ACTIONS(281),
    [anon_sym_STARif] = ACTIONS(281),
    [anon_sym_loop] = ACTIONS(283),
    [anon_sym_match] = ACTIONS(283),
    [anon_sym_break] = ACTIONS(283),
    [anon_sym_continue] = ACTIONS(283),
    [anon_sym_soe] = ACTIONS(283),
    [anon_sym_not] = ACTIONS(283),
    [anon_sym_and] = ACTIONS(283),
    [anon_sym_or] = ACTIONS(283),
    [anon_sym_read] = ACTIONS(283),
    [anon_sym_str] = ACTIONS(283),
    [anon_sym_as] = ACTIONS(283),
    [anon_sym_type] = ACTIONS(283),
    [anon_sym_try] = ACTIONS(283),
    [anon_sym_fail] = ACTIONS(283),
    [anon_sym_pure] = ACTIONS(283),
    [anon_sym_VER] = ACTIONS(283),
    [anon_sym_x] = ACTIONS(283),
    [anon_sym_int] = ACTIONS(283),
    [anon_sym_float] = ACTIONS(283),
    [anon_sym_bool] = ACTIONS(283),
    [anon_sym_dup] = ACTIONS(283),
    [anon_sym_swap] = ACTIONS(283),
    [anon_sym_drop] = ACTIONS(283),
    [anon_sym_over] = ACTIONS(283),
    [anon_sym_pick] = ACTIONS(283),
    [anon_sym_rot] = ACTIONS(283),
    [anon_sym_DASHrot] = ACTIONS(283),
    [anon_sym_nip] = ACTIONS(283),
    [anon_sym_w] = ACTIONS(283),
    [anon_sym_wl] = ACTIONS(283),
    [anon_sym_we] = ACTIONS(283),
    [anon_sym_wle] = ACTIONS(283),
    [anon_sym_len] = ACTIONS(283),
    [anon_sym_args] = ACTIONS(283),
    [anon_sym_glob] = ACTIONS(283),
    [anon_sym_toFloat] = ACTIONS(283),
    [anon_sym_toInt] = ACTIONS(283),
    [anon_sym_toPath] = ACTIONS(283),
    [anon_sym_toDt] = ACTIONS(283),
    [anon_sym_toGrid] = ACTIONS(283),
    [anon_sym_toCsv] = ACTIONS(283),
    [anon_sym_toCsvCell] = ACTIONS(283),
    [anon_sym_exit] = ACTIONS(283),
    [anon_sym_prompt] = ACTIONS(283),
    [anon_sym_stdin] = ACTIONS(283),
    [anon_sym_COLON_COLON] = ACTIONS(281),
    [anon_sym_foldl] = ACTIONS(283),
    [anon_sym_map] = ACTIONS(283),
    [anon_sym_each] = ACTIONS(283),
    [anon_sym_eachWhile] = ACTIONS(283),
    [anon_sym_filter] = ACTIONS(283),
    [anon_sym_append] = ACTIONS(283),
    [anon_sym_extend] = ACTIONS(283),
    [anon_sym_concat] = ACTIONS(283),
    [anon_sym_reverse] = ACTIONS(283),
    [anon_sym_sort] = ACTIONS(283),
    [anon_sym_sortV] = ACTIONS(283),
    [anon_sym_sortBy] = ACTIONS(283),
    [anon_sym_sortByCmp] = ACTIONS(283),
    [anon_sym_uniq] = ACTIONS(283),
    [anon_sym_zip] = ACTIONS(283),
    [anon_sym_enumerate] = ACTIONS(283),
    [anon_sym_enumerateN] = ACTIONS(283),
    [anon_sym_chunk] = ACTIONS(283),
    [anon_sym_pop] = ACTIONS(283),
    [anon_sym_take] = ACTIONS(283),
    [anon_sym_takeWhile] = ACTIONS(283),
    [anon_sym_skip] = ACTIONS(283),
    [anon_sym_dropWhile] = ACTIONS(283),
    [anon_sym_nth] = ACTIONS(283),
    [anon_sym_insert] = ACTIONS(283),
    [anon_sym_setAt] = ACTIONS(283),
    [anon_sym_del] = ACTIONS(283),
    [anon_sym_sum] = ACTIONS(283),
    [anon_sym_max] = ACTIONS(283),
    [anon_sym_max2] = ACTIONS(283),
    [anon_sym_min] = ACTIONS(283),
    [anon_sym_min2] = ACTIONS(283),
    [anon_sym_abs] = ACTIONS(283),
    [anon_sym_inc] = ACTIONS(283),
    [anon_sym_mod] = ACTIONS(283),
    [anon_sym_floor] = ACTIONS(283),
    [anon_sym_ceil] = ACTIONS(283),
    [anon_sym_round] = ACTIONS(283),
    [anon_sym_lines] = ACTIONS(283),
    [anon_sym_unlines] = ACTIONS(283),
    [anon_sym_unlinesCrLf] = ACTIONS(283),
    [anon_sym_split] = ACTIONS(283),
    [anon_sym_wsplit] = ACTIONS(283),
    [anon_sym_tsplit] = ACTIONS(283),
    [anon_sym_join] = ACTIONS(283),
    [anon_sym_trim] = ACTIONS(283),
    [anon_sym_trimStart] = ACTIONS(283),
    [anon_sym_trimEnd] = ACTIONS(283),
    [anon_sym_startsWith] = ACTIONS(283),
    [anon_sym_endsWith] = ACTIONS(283),
    [anon_sym_lower] = ACTIONS(283),
    [anon_sym_upper] = ACTIONS(283),
    [anon_sym_title] = ACTIONS(283),
    [anon_sym_leftPad] = ACTIONS(283),
    [anon_sym_findReplace] = ACTIONS(283),
    [anon_sym_in] = ACTIONS(283),
    [anon_sym_index] = ACTIONS(283),
    [anon_sym_lastIndexOf] = ACTIONS(283),
    [anon_sym_countSubStr] = ACTIONS(283),
    [anon_sym_parseJson] = ACTIONS(283),
    [anon_sym_parseCsv] = ACTIONS(283),
    [anon_sym_parseHtml] = ACTIONS(283),
    [anon_sym_parseExcel] = ACTIONS(283),
    [anon_sym_readFile] = ACTIONS(283),
    [anon_sym_readFileBytes] = ACTIONS(283),
    [anon_sym_readTsvFile] = ACTIONS(283),
    [anon_sym_writeFile] = ACTIONS(283),
    [anon_sym_appendFile] = ACTIONS(283),
    [anon_sym_fileExists] = ACTIONS(283),
    [anon_sym_isDir] = ACTIONS(283),
    [anon_sym_isFile] = ACTIONS(283),
    [anon_sym_fileSize] = ACTIONS(283),
    [anon_sym_cp] = ACTIONS(283),
    [anon_sym_mv] = ACTIONS(283),
    [anon_sym_rm] = ACTIONS(283),
    [anon_sym_rmf] = ACTIONS(283),
    [anon_sym_mkdir] = ACTIONS(283),
    [anon_sym_mkdirp] = ACTIONS(283),
    [anon_sym_cd] = ACTIONS(283),
    [anon_sym_pwd] = ACTIONS(283),
    [anon_sym_tempFile] = ACTIONS(283),
    [anon_sym_tempFileExt] = ACTIONS(283),
    [anon_sym_tempDir] = ACTIONS(283),
    [anon_sym_lsDir] = ACTIONS(283),
    [anon_sym_files] = ACTIONS(283),
    [anon_sym_dirs] = ACTIONS(283),
    [anon_sym_absPath] = ACTIONS(283),
    [anon_sym_dirname] = ACTIONS(283),
    [anon_sym_basename] = ACTIONS(283),
    [anon_sym_ext] = ACTIONS(283),
    [anon_sym_stem] = ACTIONS(283),
    [anon_sym_isCmd] = ACTIONS(283),
    [anon_sym_hardLink] = ACTIONS(283),
    [anon_sym_sha256sum] = ACTIONS(283),
    [anon_sym_md5] = ACTIONS(283),
    [anon_sym_now] = ACTIONS(283),
    [anon_sym_date] = ACTIONS(283),
    [anon_sym_year] = ACTIONS(283),
    [anon_sym_month] = ACTIONS(283),
    [anon_sym_day] = ACTIONS(283),
    [anon_sym_hour] = ACTIONS(283),
    [anon_sym_minute] = ACTIONS(283),
    [anon_sym_dateFmt] = ACTIONS(283),
    [anon_sym_isoDateFmt] = ACTIONS(283),
    [anon_sym_isoDateTimeFmt] = ACTIONS(283),
    [anon_sym_isWeekend] = ACTIONS(283),
    [anon_sym_isWeekday] = ACTIONS(283),
    [anon_sym_dow] = ACTIONS(283),
    [anon_sym_addDays] = ACTIONS(283),
    [anon_sym_toUnixTime] = ACTIONS(283),
    [anon_sym_toUnixTimeMilli] = ACTIONS(283),
    [anon_sym_toUnixTimeMicro] = ACTIONS(283),
    [anon_sym_toUnixTimeNano] = ACTIONS(283),
    [anon_sym_fromUnixTime] = ACTIONS(283),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(283),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(283),
    [anon_sym_fromUnixTimeNano] = ACTIONS(283),
    [anon_sym_toOleDate] = ACTIONS(283),
    [anon_sym_fromOleDate] = ACTIONS(283),
    [anon_sym_utcToCst] = ACTIONS(283),
    [anon_sym_cstToUtc] = ACTIONS(283),
    [anon_sym_reMatch] = ACTIONS(283),
    [anon_sym_reFindAll] = ACTIONS(283),
    [anon_sym_reFindAllIndex] = ACTIONS(283),
    [anon_sym_reReplace] = ACTIONS(283),
    [anon_sym_reSplit] = ACTIONS(283),
    [anon_sym_just] = ACTIONS(283),
    [anon_sym_none] = ACTIONS(283),
    [anon_sym_isNone] = ACTIONS(283),
    [anon_sym_maybe] = ACTIONS(283),
    [anon_sym_bind] = ACTIONS(283),
    [anon_sym_psub] = ACTIONS(283),
    [anon_sym_typeof] = ACTIONS(283),
    [anon_sym_runtime] = ACTIONS(283),
    [anon_sym_hostname] = ACTIONS(283),
    [anon_sym_httpGet] = ACTIONS(283),
    [anon_sym_httpPost] = ACTIONS(283),
    [anon_sym_urlEncode] = ACTIONS(283),
    [anon_sym_base64encode] = ACTIONS(283),
    [anon_sym_base64decode] = ACTIONS(283),
    [anon_sym_utf8Str] = ACTIONS(283),
    [anon_sym_utf8Bytes] = ACTIONS(283),
    [anon_sym_get] = ACTIONS(283),
    [anon_sym_getDef] = ACTIONS(283),
    [anon_sym_set] = ACTIONS(283),
    [anon_sym_setd] = ACTIONS(283),
    [anon_sym_keys] = ACTIONS(283),
    [anon_sym_values] = ACTIONS(283),
    [anon_sym_keyValues] = ACTIONS(283),
    [anon_sym_all] = ACTIONS(283),
    [anon_sym_any] = ACTIONS(283),
    [anon_sym_cartesian] = ACTIONS(283),
    [anon_sym_groupBy] = ACTIONS(283),
    [anon_sym_listToDict] = ACTIONS(283),
    [anon_sym_repeat] = ACTIONS(283),
    [anon_sym_seq] = ACTIONS(283),
    [anon_sym_tab] = ACTIONS(283),
    [anon_sym_select] = ACTIONS(283),
    [anon_sym_exclude] = ACTIONS(283),
    [anon_sym_derive] = ACTIONS(283),
    [anon_sym_updateCol] = ACTIONS(283),
    [anon_sym_gridValues] = ACTIONS(283),
    [anon_sym_leftJoin] = ACTIONS(283),
    [anon_sym_outerJoin] = ACTIONS(283),
    [anon_sym_linearSearch] = ACTIONS(283),
    [anon_sym_linearSearchIndex] = ACTIONS(283),
    [anon_sym_binPaths] = ACTIONS(283),
    [anon_sym_wt] = ACTIONS(283),
    [anon_sym_tt] = ACTIONS(283),
    [anon_sym_ttFile] = ACTIONS(283),
    [anon_sym_uw] = ACTIONS(283),
    [anon_sym_tuw] = ACTIONS(283),
    [anon_sym_strCmp] = ACTIONS(283),
    [anon_sym_floatCmp] = ACTIONS(283),
    [anon_sym_versionSortCmp] = ACTIONS(283),
    [anon_sym_id] = ACTIONS(283),
    [anon_sym_2id] = ACTIONS(283),
    [anon_sym_3id] = ACTIONS(283),
    [anon_sym_2unpack] = ACTIONS(283),
    [anon_sym_2apply] = ACTIONS(283),
    [anon_sym_2each] = ACTIONS(283),
    [anon_sym_2tuple] = ACTIONS(283),
    [anon_sym_DOTs] = ACTIONS(283),
    [anon_sym_DOTb] = ACTIONS(283),
    [anon_sym_DOTdef] = ACTIONS(283),
    [anon_sym_DOTenv] = ACTIONS(283),
    [sym_string] = ACTIONS(281),
    [sym_format_string] = ACTIONS(281),
    [sym_single_quoted_string] = ACTIONS(281),
    [sym_path] = ACTIONS(281),
    [sym_datetime] = ACTIONS(281),
    [sym_float] = ACTIONS(281),
    [sym_integer] = ACTIONS(283),
    [sym_env_store] = ACTIONS(281),
    [sym_env_check] = ACTIONS(281),
    [sym_env_retrieve] = ACTIONS(283),
    [sym_positional] = ACTIONS(281),
    [sym_var_retrieve] = ACTIONS(281),
    [sym_var_store] = ACTIONS(281),
    [sym_slice_indexer] = ACTIONS(281),
    [sym_indexer] = ACTIONS(281),
    [sym_end_indexer] = ACTIONS(283),
    [sym_start_indexer] = ACTIONS(283),
    [sym_match_arm_dup] = ACTIONS(281),
    [sym_prefix_quote] = ACTIONS(283),
    [anon_sym_GT] = ACTIONS(283),
    [anon_sym_GT_GT] = ACTIONS(281),
    [anon_sym_2_GT] = ACTIONS(283),
    [anon_sym_2_GT_GT] = ACTIONS(283),
    [anon_sym_AMP_GT] = ACTIONS(283),
    [anon_sym_AMP_GT_GT] = ACTIONS(281),
    [anon_sym_LT] = ACTIONS(283),
    [anon_sym_LT_GT] = ACTIONS(281),
    [anon_sym_STAR] = ACTIONS(283),
    [anon_sym_STARb] = ACTIONS(281),
    [anon_sym_CARET] = ACTIONS(283),
    [anon_sym_CARETb] = ACTIONS(281),
    [anon_sym_SEMI] = ACTIONS(281),
    [anon_sym_BANG] = ACTIONS(283),
    [anon_sym_QMARK] = ACTIONS(281),
    [anon_sym_BANG_EQ] = ACTIONS(281),
    [anon_sym_LT_EQ] = ACTIONS(281),
    [anon_sym_GT_EQ] = ACTIONS(281),
    [anon_sym_AMP] = ACTIONS(283),
    [anon_sym_PIPE] = ACTIONS(281),
    [anon_sym_COMMA] = ACTIONS(281),
    [anon_sym_COLON] = ACTIONS(283),
  },
  [25] = {
    [ts_builtin_sym_end] = ACTIONS(285),
    [sym_identifier] = ACTIONS(287),
    [anon_sym_LBRACK] = ACTIONS(287),
    [anon_sym_RBRACK] = ACTIONS(285),
    [anon_sym_LPAREN] = ACTIONS(285),
    [anon_sym_RPAREN] = ACTIONS(285),
    [anon_sym_LBRACE] = ACTIONS(285),
    [anon_sym_RBRACE] = ACTIONS(285),
    [anon_sym_LBRACK_PIPE] = ACTIONS(285),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(287),
    [anon_sym_false] = ACTIONS(287),
    [anon_sym_def] = ACTIONS(287),
    [anon_sym_end] = ACTIONS(287),
    [anon_sym_if] = ACTIONS(287),
    [anon_sym_iff] = ACTIONS(287),
    [anon_sym_else] = ACTIONS(287),
    [anon_sym_else_STAR] = ACTIONS(285),
    [anon_sym_STARif] = ACTIONS(285),
    [anon_sym_loop] = ACTIONS(287),
    [anon_sym_match] = ACTIONS(287),
    [anon_sym_break] = ACTIONS(287),
    [anon_sym_continue] = ACTIONS(287),
    [anon_sym_soe] = ACTIONS(287),
    [anon_sym_not] = ACTIONS(287),
    [anon_sym_and] = ACTIONS(287),
    [anon_sym_or] = ACTIONS(287),
    [anon_sym_read] = ACTIONS(287),
    [anon_sym_str] = ACTIONS(287),
    [anon_sym_as] = ACTIONS(287),
    [anon_sym_type] = ACTIONS(287),
    [anon_sym_try] = ACTIONS(287),
    [anon_sym_fail] = ACTIONS(287),
    [anon_sym_pure] = ACTIONS(287),
    [anon_sym_VER] = ACTIONS(287),
    [anon_sym_x] = ACTIONS(287),
    [anon_sym_int] = ACTIONS(287),
    [anon_sym_float] = ACTIONS(287),
    [anon_sym_bool] = ACTIONS(287),
    [anon_sym_dup] = ACTIONS(287),
    [anon_sym_swap] = ACTIONS(287),
    [anon_sym_drop] = ACTIONS(287),
    [anon_sym_over] = ACTIONS(287),
    [anon_sym_pick] = ACTIONS(287),
    [anon_sym_rot] = ACTIONS(287),
    [anon_sym_DASHrot] = ACTIONS(287),
    [anon_sym_nip] = ACTIONS(287),
    [anon_sym_w] = ACTIONS(287),
    [anon_sym_wl] = ACTIONS(287),
    [anon_sym_we] = ACTIONS(287),
    [anon_sym_wle] = ACTIONS(287),
    [anon_sym_len] = ACTIONS(287),
    [anon_sym_args] = ACTIONS(287),
    [anon_sym_glob] = ACTIONS(287),
    [anon_sym_toFloat] = ACTIONS(287),
    [anon_sym_toInt] = ACTIONS(287),
    [anon_sym_toPath] = ACTIONS(287),
    [anon_sym_toDt] = ACTIONS(287),
    [anon_sym_toGrid] = ACTIONS(287),
    [anon_sym_toCsv] = ACTIONS(287),
    [anon_sym_toCsvCell] = ACTIONS(287),
    [anon_sym_exit] = ACTIONS(287),
    [anon_sym_prompt] = ACTIONS(287),
    [anon_sym_stdin] = ACTIONS(287),
    [anon_sym_COLON_COLON] = ACTIONS(285),
    [anon_sym_foldl] = ACTIONS(287),
    [anon_sym_map] = ACTIONS(287),
    [anon_sym_each] = ACTIONS(287),
    [anon_sym_eachWhile] = ACTIONS(287),
    [anon_sym_filter] = ACTIONS(287),
    [anon_sym_append] = ACTIONS(287),
    [anon_sym_extend] = ACTIONS(287),
    [anon_sym_concat] = ACTIONS(287),
    [anon_sym_reverse] = ACTIONS(287),
    [anon_sym_sort] = ACTIONS(287),
    [anon_sym_sortV] = ACTIONS(287),
    [anon_sym_sortBy] = ACTIONS(287),
    [anon_sym_sortByCmp] = ACTIONS(287),
    [anon_sym_uniq] = ACTIONS(287),
    [anon_sym_zip] = ACTIONS(287),
    [anon_sym_enumerate] = ACTIONS(287),
    [anon_sym_enumerateN] = ACTIONS(287),
    [anon_sym_chunk] = ACTIONS(287),
    [anon_sym_pop] = ACTIONS(287),
    [anon_sym_take] = ACTIONS(287),
    [anon_sym_takeWhile] = ACTIONS(287),
    [anon_sym_skip] = ACTIONS(287),
    [anon_sym_dropWhile] = ACTIONS(287),
    [anon_sym_nth] = ACTIONS(287),
    [anon_sym_insert] = ACTIONS(287),
    [anon_sym_setAt] = ACTIONS(287),
    [anon_sym_del] = ACTIONS(287),
    [anon_sym_sum] = ACTIONS(287),
    [anon_sym_max] = ACTIONS(287),
    [anon_sym_max2] = ACTIONS(287),
    [anon_sym_min] = ACTIONS(287),
    [anon_sym_min2] = ACTIONS(287),
    [anon_sym_abs] = ACTIONS(287),
    [anon_sym_inc] = ACTIONS(287),
    [anon_sym_mod] = ACTIONS(287),
    [anon_sym_floor] = ACTIONS(287),
    [anon_sym_ceil] = ACTIONS(287),
    [anon_sym_round] = ACTIONS(287),
    [anon_sym_lines] = ACTIONS(287),
    [anon_sym_unlines] = ACTIONS(287),
    [anon_sym_unlinesCrLf] = ACTIONS(287),
    [anon_sym_split] = ACTIONS(287),
    [anon_sym_wsplit] = ACTIONS(287),
    [anon_sym_tsplit] = ACTIONS(287),
    [anon_sym_join] = ACTIONS(287),
    [anon_sym_trim] = ACTIONS(287),
    [anon_sym_trimStart] = ACTIONS(287),
    [anon_sym_trimEnd] = ACTIONS(287),
    [anon_sym_startsWith] = ACTIONS(287),
    [anon_sym_endsWith] = ACTIONS(287),
    [anon_sym_lower] = ACTIONS(287),
    [anon_sym_upper] = ACTIONS(287),
    [anon_sym_title] = ACTIONS(287),
    [anon_sym_leftPad] = ACTIONS(287),
    [anon_sym_findReplace] = ACTIONS(287),
    [anon_sym_in] = ACTIONS(287),
    [anon_sym_index] = ACTIONS(287),
    [anon_sym_lastIndexOf] = ACTIONS(287),
    [anon_sym_countSubStr] = ACTIONS(287),
    [anon_sym_parseJson] = ACTIONS(287),
    [anon_sym_parseCsv] = ACTIONS(287),
    [anon_sym_parseHtml] = ACTIONS(287),
    [anon_sym_parseExcel] = ACTIONS(287),
    [anon_sym_readFile] = ACTIONS(287),
    [anon_sym_readFileBytes] = ACTIONS(287),
    [anon_sym_readTsvFile] = ACTIONS(287),
    [anon_sym_writeFile] = ACTIONS(287),
    [anon_sym_appendFile] = ACTIONS(287),
    [anon_sym_fileExists] = ACTIONS(287),
    [anon_sym_isDir] = ACTIONS(287),
    [anon_sym_isFile] = ACTIONS(287),
    [anon_sym_fileSize] = ACTIONS(287),
    [anon_sym_cp] = ACTIONS(287),
    [anon_sym_mv] = ACTIONS(287),
    [anon_sym_rm] = ACTIONS(287),
    [anon_sym_rmf] = ACTIONS(287),
    [anon_sym_mkdir] = ACTIONS(287),
    [anon_sym_mkdirp] = ACTIONS(287),
    [anon_sym_cd] = ACTIONS(287),
    [anon_sym_pwd] = ACTIONS(287),
    [anon_sym_tempFile] = ACTIONS(287),
    [anon_sym_tempFileExt] = ACTIONS(287),
    [anon_sym_tempDir] = ACTIONS(287),
    [anon_sym_lsDir] = ACTIONS(287),
    [anon_sym_files] = ACTIONS(287),
    [anon_sym_dirs] = ACTIONS(287),
    [anon_sym_absPath] = ACTIONS(287),
    [anon_sym_dirname] = ACTIONS(287),
    [anon_sym_basename] = ACTIONS(287),
    [anon_sym_ext] = ACTIONS(287),
    [anon_sym_stem] = ACTIONS(287),
    [anon_sym_isCmd] = ACTIONS(287),
    [anon_sym_hardLink] = ACTIONS(287),
    [anon_sym_sha256sum] = ACTIONS(287),
    [anon_sym_md5] = ACTIONS(287),
    [anon_sym_now] = ACTIONS(287),
    [anon_sym_date] = ACTIONS(287),
    [anon_sym_year] = ACTIONS(287),
    [anon_sym_month] = ACTIONS(287),
    [anon_sym_day] = ACTIONS(287),
    [anon_sym_hour] = ACTIONS(287),
    [anon_sym_minute] = ACTIONS(287),
    [anon_sym_dateFmt] = ACTIONS(287),
    [anon_sym_isoDateFmt] = ACTIONS(287),
    [anon_sym_isoDateTimeFmt] = ACTIONS(287),
    [anon_sym_isWeekend] = ACTIONS(287),
    [anon_sym_isWeekday] = ACTIONS(287),
    [anon_sym_dow] = ACTIONS(287),
    [anon_sym_addDays] = ACTIONS(287),
    [anon_sym_toUnixTime] = ACTIONS(287),
    [anon_sym_toUnixTimeMilli] = ACTIONS(287),
    [anon_sym_toUnixTimeMicro] = ACTIONS(287),
    [anon_sym_toUnixTimeNano] = ACTIONS(287),
    [anon_sym_fromUnixTime] = ACTIONS(287),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(287),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(287),
    [anon_sym_fromUnixTimeNano] = ACTIONS(287),
    [anon_sym_toOleDate] = ACTIONS(287),
    [anon_sym_fromOleDate] = ACTIONS(287),
    [anon_sym_utcToCst] = ACTIONS(287),
    [anon_sym_cstToUtc] = ACTIONS(287),
    [anon_sym_reMatch] = ACTIONS(287),
    [anon_sym_reFindAll] = ACTIONS(287),
    [anon_sym_reFindAllIndex] = ACTIONS(287),
    [anon_sym_reReplace] = ACTIONS(287),
    [anon_sym_reSplit] = ACTIONS(287),
    [anon_sym_just] = ACTIONS(287),
    [anon_sym_none] = ACTIONS(287),
    [anon_sym_isNone] = ACTIONS(287),
    [anon_sym_maybe] = ACTIONS(287),
    [anon_sym_bind] = ACTIONS(287),
    [anon_sym_psub] = ACTIONS(287),
    [anon_sym_typeof] = ACTIONS(287),
    [anon_sym_runtime] = ACTIONS(287),
    [anon_sym_hostname] = ACTIONS(287),
    [anon_sym_httpGet] = ACTIONS(287),
    [anon_sym_httpPost] = ACTIONS(287),
    [anon_sym_urlEncode] = ACTIONS(287),
    [anon_sym_base64encode] = ACTIONS(287),
    [anon_sym_base64decode] = ACTIONS(287),
    [anon_sym_utf8Str] = ACTIONS(287),
    [anon_sym_utf8Bytes] = ACTIONS(287),
    [anon_sym_get] = ACTIONS(287),
    [anon_sym_getDef] = ACTIONS(287),
    [anon_sym_set] = ACTIONS(287),
    [anon_sym_setd] = ACTIONS(287),
    [anon_sym_keys] = ACTIONS(287),
    [anon_sym_values] = ACTIONS(287),
    [anon_sym_keyValues] = ACTIONS(287),
    [anon_sym_all] = ACTIONS(287),
    [anon_sym_any] = ACTIONS(287),
    [anon_sym_cartesian] = ACTIONS(287),
    [anon_sym_groupBy] = ACTIONS(287),
    [anon_sym_listToDict] = ACTIONS(287),
    [anon_sym_repeat] = ACTIONS(287),
    [anon_sym_seq] = ACTIONS(287),
    [anon_sym_tab] = ACTIONS(287),
    [anon_sym_select] = ACTIONS(287),
    [anon_sym_exclude] = ACTIONS(287),
    [anon_sym_derive] = ACTIONS(287),
    [anon_sym_updateCol] = ACTIONS(287),
    [anon_sym_gridValues] = ACTIONS(287),
    [anon_sym_leftJoin] = ACTIONS(287),
    [anon_sym_outerJoin] = ACTIONS(287),
    [anon_sym_linearSearch] = ACTIONS(287),
    [anon_sym_linearSearchIndex] = ACTIONS(287),
    [anon_sym_binPaths] = ACTIONS(287),
    [anon_sym_wt] = ACTIONS(287),
    [anon_sym_tt] = ACTIONS(287),
    [anon_sym_ttFile] = ACTIONS(287),
    [anon_sym_uw] = ACTIONS(287),
    [anon_sym_tuw] = ACTIONS(287),
    [anon_sym_strCmp] = ACTIONS(287),
    [anon_sym_floatCmp] = ACTIONS(287),
    [anon_sym_versionSortCmp] = ACTIONS(287),
    [anon_sym_id] = ACTIONS(287),
    [anon_sym_2id] = ACTIONS(287),
    [anon_sym_3id] = ACTIONS(287),
    [anon_sym_2unpack] = ACTIONS(287),
    [anon_sym_2apply] = ACTIONS(287),
    [anon_sym_2each] = ACTIONS(287),
    [anon_sym_2tuple] = ACTIONS(287),
    [anon_sym_DOTs] = ACTIONS(287),
    [anon_sym_DOTb] = ACTIONS(287),
    [anon_sym_DOTdef] = ACTIONS(287),
    [anon_sym_DOTenv] = ACTIONS(287),
    [sym_string] = ACTIONS(285),
    [sym_format_string] = ACTIONS(285),
    [sym_single_quoted_string] = ACTIONS(285),
    [sym_path] = ACTIONS(285),
    [sym_datetime] = ACTIONS(285),
    [sym_float] = ACTIONS(285),
    [sym_integer] = ACTIONS(287),
    [sym_env_store] = ACTIONS(285),
    [sym_env_check] = ACTIONS(285),
    [sym_env_retrieve] = ACTIONS(287),
    [sym_positional] = ACTIONS(285),
    [sym_var_retrieve] = ACTIONS(285),
    [sym_var_store] = ACTIONS(285),
    [sym_slice_indexer] = ACTIONS(285),
    [sym_indexer] = ACTIONS(285),
    [sym_end_indexer] = ACTIONS(287),
    [sym_start_indexer] = ACTIONS(287),
    [sym_match_arm_dup] = ACTIONS(285),
    [sym_prefix_quote] = ACTIONS(287),
    [anon_sym_GT] = ACTIONS(287),
    [anon_sym_GT_GT] = ACTIONS(285),
    [anon_sym_2_GT] = ACTIONS(287),
    [anon_sym_2_GT_GT] = ACTIONS(287),
    [anon_sym_AMP_GT] = ACTIONS(287),
    [anon_sym_AMP_GT_GT] = ACTIONS(285),
    [anon_sym_LT] = ACTIONS(287),
    [anon_sym_LT_GT] = ACTIONS(285),
    [anon_sym_STAR] = ACTIONS(287),
    [anon_sym_STARb] = ACTIONS(285),
    [anon_sym_CARET] = ACTIONS(287),
    [anon_sym_CARETb] = ACTIONS(285),
    [anon_sym_SEMI] = ACTIONS(285),
    [anon_sym_BANG] = ACTIONS(287),
    [anon_sym_QMARK] = ACTIONS(285),
    [anon_sym_BANG_EQ] = ACTIONS(285),
    [anon_sym_LT_EQ] = ACTIONS(285),
    [anon_sym_GT_EQ] = ACTIONS(285),
    [anon_sym_AMP] = ACTIONS(287),
    [anon_sym_PIPE] = ACTIONS(285),
    [anon_sym_COMMA] = ACTIONS(285),
    [anon_sym_COLON] = ACTIONS(287),
  },
  [26] = {
    [ts_builtin_sym_end] = ACTIONS(289),
    [sym_identifier] = ACTIONS(291),
    [anon_sym_LBRACK] = ACTIONS(291),
    [anon_sym_RBRACK] = ACTIONS(289),
    [anon_sym_LPAREN] = ACTIONS(289),
    [anon_sym_RPAREN] = ACTIONS(289),
    [anon_sym_LBRACE] = ACTIONS(289),
    [anon_sym_RBRACE] = ACTIONS(289),
    [anon_sym_LBRACK_PIPE] = ACTIONS(289),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(291),
    [anon_sym_false] = ACTIONS(291),
    [anon_sym_def] = ACTIONS(291),
    [anon_sym_end] = ACTIONS(291),
    [anon_sym_if] = ACTIONS(291),
    [anon_sym_iff] = ACTIONS(291),
    [anon_sym_else] = ACTIONS(291),
    [anon_sym_else_STAR] = ACTIONS(289),
    [anon_sym_STARif] = ACTIONS(289),
    [anon_sym_loop] = ACTIONS(291),
    [anon_sym_match] = ACTIONS(291),
    [anon_sym_break] = ACTIONS(291),
    [anon_sym_continue] = ACTIONS(291),
    [anon_sym_soe] = ACTIONS(291),
    [anon_sym_not] = ACTIONS(291),
    [anon_sym_and] = ACTIONS(291),
    [anon_sym_or] = ACTIONS(291),
    [anon_sym_read] = ACTIONS(291),
    [anon_sym_str] = ACTIONS(291),
    [anon_sym_as] = ACTIONS(291),
    [anon_sym_type] = ACTIONS(291),
    [anon_sym_try] = ACTIONS(291),
    [anon_sym_fail] = ACTIONS(291),
    [anon_sym_pure] = ACTIONS(291),
    [anon_sym_VER] = ACTIONS(291),
    [anon_sym_x] = ACTIONS(291),
    [anon_sym_int] = ACTIONS(291),
    [anon_sym_float] = ACTIONS(291),
    [anon_sym_bool] = ACTIONS(291),
    [anon_sym_dup] = ACTIONS(291),
    [anon_sym_swap] = ACTIONS(291),
    [anon_sym_drop] = ACTIONS(291),
    [anon_sym_over] = ACTIONS(291),
    [anon_sym_pick] = ACTIONS(291),
    [anon_sym_rot] = ACTIONS(291),
    [anon_sym_DASHrot] = ACTIONS(291),
    [anon_sym_nip] = ACTIONS(291),
    [anon_sym_w] = ACTIONS(291),
    [anon_sym_wl] = ACTIONS(291),
    [anon_sym_we] = ACTIONS(291),
    [anon_sym_wle] = ACTIONS(291),
    [anon_sym_len] = ACTIONS(291),
    [anon_sym_args] = ACTIONS(291),
    [anon_sym_glob] = ACTIONS(291),
    [anon_sym_toFloat] = ACTIONS(291),
    [anon_sym_toInt] = ACTIONS(291),
    [anon_sym_toPath] = ACTIONS(291),
    [anon_sym_toDt] = ACTIONS(291),
    [anon_sym_toGrid] = ACTIONS(291),
    [anon_sym_toCsv] = ACTIONS(291),
    [anon_sym_toCsvCell] = ACTIONS(291),
    [anon_sym_exit] = ACTIONS(291),
    [anon_sym_prompt] = ACTIONS(291),
    [anon_sym_stdin] = ACTIONS(291),
    [anon_sym_COLON_COLON] = ACTIONS(289),
    [anon_sym_foldl] = ACTIONS(291),
    [anon_sym_map] = ACTIONS(291),
    [anon_sym_each] = ACTIONS(291),
    [anon_sym_eachWhile] = ACTIONS(291),
    [anon_sym_filter] = ACTIONS(291),
    [anon_sym_append] = ACTIONS(291),
    [anon_sym_extend] = ACTIONS(291),
    [anon_sym_concat] = ACTIONS(291),
    [anon_sym_reverse] = ACTIONS(291),
    [anon_sym_sort] = ACTIONS(291),
    [anon_sym_sortV] = ACTIONS(291),
    [anon_sym_sortBy] = ACTIONS(291),
    [anon_sym_sortByCmp] = ACTIONS(291),
    [anon_sym_uniq] = ACTIONS(291),
    [anon_sym_zip] = ACTIONS(291),
    [anon_sym_enumerate] = ACTIONS(291),
    [anon_sym_enumerateN] = ACTIONS(291),
    [anon_sym_chunk] = ACTIONS(291),
    [anon_sym_pop] = ACTIONS(291),
    [anon_sym_take] = ACTIONS(291),
    [anon_sym_takeWhile] = ACTIONS(291),
    [anon_sym_skip] = ACTIONS(291),
    [anon_sym_dropWhile] = ACTIONS(291),
    [anon_sym_nth] = ACTIONS(291),
    [anon_sym_insert] = ACTIONS(291),
    [anon_sym_setAt] = ACTIONS(291),
    [anon_sym_del] = ACTIONS(291),
    [anon_sym_sum] = ACTIONS(291),
    [anon_sym_max] = ACTIONS(291),
    [anon_sym_max2] = ACTIONS(291),
    [anon_sym_min] = ACTIONS(291),
    [anon_sym_min2] = ACTIONS(291),
    [anon_sym_abs] = ACTIONS(291),
    [anon_sym_inc] = ACTIONS(291),
    [anon_sym_mod] = ACTIONS(291),
    [anon_sym_floor] = ACTIONS(291),
    [anon_sym_ceil] = ACTIONS(291),
    [anon_sym_round] = ACTIONS(291),
    [anon_sym_lines] = ACTIONS(291),
    [anon_sym_unlines] = ACTIONS(291),
    [anon_sym_unlinesCrLf] = ACTIONS(291),
    [anon_sym_split] = ACTIONS(291),
    [anon_sym_wsplit] = ACTIONS(291),
    [anon_sym_tsplit] = ACTIONS(291),
    [anon_sym_join] = ACTIONS(291),
    [anon_sym_trim] = ACTIONS(291),
    [anon_sym_trimStart] = ACTIONS(291),
    [anon_sym_trimEnd] = ACTIONS(291),
    [anon_sym_startsWith] = ACTIONS(291),
    [anon_sym_endsWith] = ACTIONS(291),
    [anon_sym_lower] = ACTIONS(291),
    [anon_sym_upper] = ACTIONS(291),
    [anon_sym_title] = ACTIONS(291),
    [anon_sym_leftPad] = ACTIONS(291),
    [anon_sym_findReplace] = ACTIONS(291),
    [anon_sym_in] = ACTIONS(291),
    [anon_sym_index] = ACTIONS(291),
    [anon_sym_lastIndexOf] = ACTIONS(291),
    [anon_sym_countSubStr] = ACTIONS(291),
    [anon_sym_parseJson] = ACTIONS(291),
    [anon_sym_parseCsv] = ACTIONS(291),
    [anon_sym_parseHtml] = ACTIONS(291),
    [anon_sym_parseExcel] = ACTIONS(291),
    [anon_sym_readFile] = ACTIONS(291),
    [anon_sym_readFileBytes] = ACTIONS(291),
    [anon_sym_readTsvFile] = ACTIONS(291),
    [anon_sym_writeFile] = ACTIONS(291),
    [anon_sym_appendFile] = ACTIONS(291),
    [anon_sym_fileExists] = ACTIONS(291),
    [anon_sym_isDir] = ACTIONS(291),
    [anon_sym_isFile] = ACTIONS(291),
    [anon_sym_fileSize] = ACTIONS(291),
    [anon_sym_cp] = ACTIONS(291),
    [anon_sym_mv] = ACTIONS(291),
    [anon_sym_rm] = ACTIONS(291),
    [anon_sym_rmf] = ACTIONS(291),
    [anon_sym_mkdir] = ACTIONS(291),
    [anon_sym_mkdirp] = ACTIONS(291),
    [anon_sym_cd] = ACTIONS(291),
    [anon_sym_pwd] = ACTIONS(291),
    [anon_sym_tempFile] = ACTIONS(291),
    [anon_sym_tempFileExt] = ACTIONS(291),
    [anon_sym_tempDir] = ACTIONS(291),
    [anon_sym_lsDir] = ACTIONS(291),
    [anon_sym_files] = ACTIONS(291),
    [anon_sym_dirs] = ACTIONS(291),
    [anon_sym_absPath] = ACTIONS(291),
    [anon_sym_dirname] = ACTIONS(291),
    [anon_sym_basename] = ACTIONS(291),
    [anon_sym_ext] = ACTIONS(291),
    [anon_sym_stem] = ACTIONS(291),
    [anon_sym_isCmd] = ACTIONS(291),
    [anon_sym_hardLink] = ACTIONS(291),
    [anon_sym_sha256sum] = ACTIONS(291),
    [anon_sym_md5] = ACTIONS(291),
    [anon_sym_now] = ACTIONS(291),
    [anon_sym_date] = ACTIONS(291),
    [anon_sym_year] = ACTIONS(291),
    [anon_sym_month] = ACTIONS(291),
    [anon_sym_day] = ACTIONS(291),
    [anon_sym_hour] = ACTIONS(291),
    [anon_sym_minute] = ACTIONS(291),
    [anon_sym_dateFmt] = ACTIONS(291),
    [anon_sym_isoDateFmt] = ACTIONS(291),
    [anon_sym_isoDateTimeFmt] = ACTIONS(291),
    [anon_sym_isWeekend] = ACTIONS(291),
    [anon_sym_isWeekday] = ACTIONS(291),
    [anon_sym_dow] = ACTIONS(291),
    [anon_sym_addDays] = ACTIONS(291),
    [anon_sym_toUnixTime] = ACTIONS(291),
    [anon_sym_toUnixTimeMilli] = ACTIONS(291),
    [anon_sym_toUnixTimeMicro] = ACTIONS(291),
    [anon_sym_toUnixTimeNano] = ACTIONS(291),
    [anon_sym_fromUnixTime] = ACTIONS(291),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(291),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(291),
    [anon_sym_fromUnixTimeNano] = ACTIONS(291),
    [anon_sym_toOleDate] = ACTIONS(291),
    [anon_sym_fromOleDate] = ACTIONS(291),
    [anon_sym_utcToCst] = ACTIONS(291),
    [anon_sym_cstToUtc] = ACTIONS(291),
    [anon_sym_reMatch] = ACTIONS(291),
    [anon_sym_reFindAll] = ACTIONS(291),
    [anon_sym_reFindAllIndex] = ACTIONS(291),
    [anon_sym_reReplace] = ACTIONS(291),
    [anon_sym_reSplit] = ACTIONS(291),
    [anon_sym_just] = ACTIONS(291),
    [anon_sym_none] = ACTIONS(291),
    [anon_sym_isNone] = ACTIONS(291),
    [anon_sym_maybe] = ACTIONS(291),
    [anon_sym_bind] = ACTIONS(291),
    [anon_sym_psub] = ACTIONS(291),
    [anon_sym_typeof] = ACTIONS(291),
    [anon_sym_runtime] = ACTIONS(291),
    [anon_sym_hostname] = ACTIONS(291),
    [anon_sym_httpGet] = ACTIONS(291),
    [anon_sym_httpPost] = ACTIONS(291),
    [anon_sym_urlEncode] = ACTIONS(291),
    [anon_sym_base64encode] = ACTIONS(291),
    [anon_sym_base64decode] = ACTIONS(291),
    [anon_sym_utf8Str] = ACTIONS(291),
    [anon_sym_utf8Bytes] = ACTIONS(291),
    [anon_sym_get] = ACTIONS(291),
    [anon_sym_getDef] = ACTIONS(291),
    [anon_sym_set] = ACTIONS(291),
    [anon_sym_setd] = ACTIONS(291),
    [anon_sym_keys] = ACTIONS(291),
    [anon_sym_values] = ACTIONS(291),
    [anon_sym_keyValues] = ACTIONS(291),
    [anon_sym_all] = ACTIONS(291),
    [anon_sym_any] = ACTIONS(291),
    [anon_sym_cartesian] = ACTIONS(291),
    [anon_sym_groupBy] = ACTIONS(291),
    [anon_sym_listToDict] = ACTIONS(291),
    [anon_sym_repeat] = ACTIONS(291),
    [anon_sym_seq] = ACTIONS(291),
    [anon_sym_tab] = ACTIONS(291),
    [anon_sym_select] = ACTIONS(291),
    [anon_sym_exclude] = ACTIONS(291),
    [anon_sym_derive] = ACTIONS(291),
    [anon_sym_updateCol] = ACTIONS(291),
    [anon_sym_gridValues] = ACTIONS(291),
    [anon_sym_leftJoin] = ACTIONS(291),
    [anon_sym_outerJoin] = ACTIONS(291),
    [anon_sym_linearSearch] = ACTIONS(291),
    [anon_sym_linearSearchIndex] = ACTIONS(291),
    [anon_sym_binPaths] = ACTIONS(291),
    [anon_sym_wt] = ACTIONS(291),
    [anon_sym_tt] = ACTIONS(291),
    [anon_sym_ttFile] = ACTIONS(291),
    [anon_sym_uw] = ACTIONS(291),
    [anon_sym_tuw] = ACTIONS(291),
    [anon_sym_strCmp] = ACTIONS(291),
    [anon_sym_floatCmp] = ACTIONS(291),
    [anon_sym_versionSortCmp] = ACTIONS(291),
    [anon_sym_id] = ACTIONS(291),
    [anon_sym_2id] = ACTIONS(291),
    [anon_sym_3id] = ACTIONS(291),
    [anon_sym_2unpack] = ACTIONS(291),
    [anon_sym_2apply] = ACTIONS(291),
    [anon_sym_2each] = ACTIONS(291),
    [anon_sym_2tuple] = ACTIONS(291),
    [anon_sym_DOTs] = ACTIONS(291),
    [anon_sym_DOTb] = ACTIONS(291),
    [anon_sym_DOTdef] = ACTIONS(291),
    [anon_sym_DOTenv] = ACTIONS(291),
    [sym_string] = ACTIONS(289),
    [sym_format_string] = ACTIONS(289),
    [sym_single_quoted_string] = ACTIONS(289),
    [sym_path] = ACTIONS(289),
    [sym_datetime] = ACTIONS(289),
    [sym_float] = ACTIONS(289),
    [sym_integer] = ACTIONS(291),
    [sym_env_store] = ACTIONS(289),
    [sym_env_check] = ACTIONS(289),
    [sym_env_retrieve] = ACTIONS(291),
    [sym_positional] = ACTIONS(289),
    [sym_var_retrieve] = ACTIONS(289),
    [sym_var_store] = ACTIONS(289),
    [sym_slice_indexer] = ACTIONS(289),
    [sym_indexer] = ACTIONS(289),
    [sym_end_indexer] = ACTIONS(291),
    [sym_start_indexer] = ACTIONS(291),
    [sym_match_arm_dup] = ACTIONS(289),
    [sym_prefix_quote] = ACTIONS(291),
    [anon_sym_GT] = ACTIONS(291),
    [anon_sym_GT_GT] = ACTIONS(289),
    [anon_sym_2_GT] = ACTIONS(291),
    [anon_sym_2_GT_GT] = ACTIONS(291),
    [anon_sym_AMP_GT] = ACTIONS(291),
    [anon_sym_AMP_GT_GT] = ACTIONS(289),
    [anon_sym_LT] = ACTIONS(291),
    [anon_sym_LT_GT] = ACTIONS(289),
    [anon_sym_STAR] = ACTIONS(291),
    [anon_sym_STARb] = ACTIONS(289),
    [anon_sym_CARET] = ACTIONS(291),
    [anon_sym_CARETb] = ACTIONS(289),
    [anon_sym_SEMI] = ACTIONS(289),
    [anon_sym_BANG] = ACTIONS(291),
    [anon_sym_QMARK] = ACTIONS(289),
    [anon_sym_BANG_EQ] = ACTIONS(289),
    [anon_sym_LT_EQ] = ACTIONS(289),
    [anon_sym_GT_EQ] = ACTIONS(289),
    [anon_sym_AMP] = ACTIONS(291),
    [anon_sym_PIPE] = ACTIONS(289),
    [anon_sym_COMMA] = ACTIONS(289),
    [anon_sym_COLON] = ACTIONS(291),
  },
  [27] = {
    [ts_builtin_sym_end] = ACTIONS(293),
    [sym_identifier] = ACTIONS(295),
    [anon_sym_LBRACK] = ACTIONS(295),
    [anon_sym_RBRACK] = ACTIONS(293),
    [anon_sym_LPAREN] = ACTIONS(293),
    [anon_sym_RPAREN] = ACTIONS(293),
    [anon_sym_LBRACE] = ACTIONS(293),
    [anon_sym_RBRACE] = ACTIONS(293),
    [anon_sym_LBRACK_PIPE] = ACTIONS(293),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(295),
    [anon_sym_false] = ACTIONS(295),
    [anon_sym_def] = ACTIONS(295),
    [anon_sym_end] = ACTIONS(295),
    [anon_sym_if] = ACTIONS(295),
    [anon_sym_iff] = ACTIONS(295),
    [anon_sym_else] = ACTIONS(295),
    [anon_sym_else_STAR] = ACTIONS(293),
    [anon_sym_STARif] = ACTIONS(293),
    [anon_sym_loop] = ACTIONS(295),
    [anon_sym_match] = ACTIONS(295),
    [anon_sym_break] = ACTIONS(295),
    [anon_sym_continue] = ACTIONS(295),
    [anon_sym_soe] = ACTIONS(295),
    [anon_sym_not] = ACTIONS(295),
    [anon_sym_and] = ACTIONS(295),
    [anon_sym_or] = ACTIONS(295),
    [anon_sym_read] = ACTIONS(295),
    [anon_sym_str] = ACTIONS(295),
    [anon_sym_as] = ACTIONS(295),
    [anon_sym_type] = ACTIONS(295),
    [anon_sym_try] = ACTIONS(295),
    [anon_sym_fail] = ACTIONS(295),
    [anon_sym_pure] = ACTIONS(295),
    [anon_sym_VER] = ACTIONS(295),
    [anon_sym_x] = ACTIONS(295),
    [anon_sym_int] = ACTIONS(295),
    [anon_sym_float] = ACTIONS(295),
    [anon_sym_bool] = ACTIONS(295),
    [anon_sym_dup] = ACTIONS(295),
    [anon_sym_swap] = ACTIONS(295),
    [anon_sym_drop] = ACTIONS(295),
    [anon_sym_over] = ACTIONS(295),
    [anon_sym_pick] = ACTIONS(295),
    [anon_sym_rot] = ACTIONS(295),
    [anon_sym_DASHrot] = ACTIONS(295),
    [anon_sym_nip] = ACTIONS(295),
    [anon_sym_w] = ACTIONS(295),
    [anon_sym_wl] = ACTIONS(295),
    [anon_sym_we] = ACTIONS(295),
    [anon_sym_wle] = ACTIONS(295),
    [anon_sym_len] = ACTIONS(295),
    [anon_sym_args] = ACTIONS(295),
    [anon_sym_glob] = ACTIONS(295),
    [anon_sym_toFloat] = ACTIONS(295),
    [anon_sym_toInt] = ACTIONS(295),
    [anon_sym_toPath] = ACTIONS(295),
    [anon_sym_toDt] = ACTIONS(295),
    [anon_sym_toGrid] = ACTIONS(295),
    [anon_sym_toCsv] = ACTIONS(295),
    [anon_sym_toCsvCell] = ACTIONS(295),
    [anon_sym_exit] = ACTIONS(295),
    [anon_sym_prompt] = ACTIONS(295),
    [anon_sym_stdin] = ACTIONS(295),
    [anon_sym_COLON_COLON] = ACTIONS(293),
    [anon_sym_foldl] = ACTIONS(295),
    [anon_sym_map] = ACTIONS(295),
    [anon_sym_each] = ACTIONS(295),
    [anon_sym_eachWhile] = ACTIONS(295),
    [anon_sym_filter] = ACTIONS(295),
    [anon_sym_append] = ACTIONS(295),
    [anon_sym_extend] = ACTIONS(295),
    [anon_sym_concat] = ACTIONS(295),
    [anon_sym_reverse] = ACTIONS(295),
    [anon_sym_sort] = ACTIONS(295),
    [anon_sym_sortV] = ACTIONS(295),
    [anon_sym_sortBy] = ACTIONS(295),
    [anon_sym_sortByCmp] = ACTIONS(295),
    [anon_sym_uniq] = ACTIONS(295),
    [anon_sym_zip] = ACTIONS(295),
    [anon_sym_enumerate] = ACTIONS(295),
    [anon_sym_enumerateN] = ACTIONS(295),
    [anon_sym_chunk] = ACTIONS(295),
    [anon_sym_pop] = ACTIONS(295),
    [anon_sym_take] = ACTIONS(295),
    [anon_sym_takeWhile] = ACTIONS(295),
    [anon_sym_skip] = ACTIONS(295),
    [anon_sym_dropWhile] = ACTIONS(295),
    [anon_sym_nth] = ACTIONS(295),
    [anon_sym_insert] = ACTIONS(295),
    [anon_sym_setAt] = ACTIONS(295),
    [anon_sym_del] = ACTIONS(295),
    [anon_sym_sum] = ACTIONS(295),
    [anon_sym_max] = ACTIONS(295),
    [anon_sym_max2] = ACTIONS(295),
    [anon_sym_min] = ACTIONS(295),
    [anon_sym_min2] = ACTIONS(295),
    [anon_sym_abs] = ACTIONS(295),
    [anon_sym_inc] = ACTIONS(295),
    [anon_sym_mod] = ACTIONS(295),
    [anon_sym_floor] = ACTIONS(295),
    [anon_sym_ceil] = ACTIONS(295),
    [anon_sym_round] = ACTIONS(295),
    [anon_sym_lines] = ACTIONS(295),
    [anon_sym_unlines] = ACTIONS(295),
    [anon_sym_unlinesCrLf] = ACTIONS(295),
    [anon_sym_split] = ACTIONS(295),
    [anon_sym_wsplit] = ACTIONS(295),
    [anon_sym_tsplit] = ACTIONS(295),
    [anon_sym_join] = ACTIONS(295),
    [anon_sym_trim] = ACTIONS(295),
    [anon_sym_trimStart] = ACTIONS(295),
    [anon_sym_trimEnd] = ACTIONS(295),
    [anon_sym_startsWith] = ACTIONS(295),
    [anon_sym_endsWith] = ACTIONS(295),
    [anon_sym_lower] = ACTIONS(295),
    [anon_sym_upper] = ACTIONS(295),
    [anon_sym_title] = ACTIONS(295),
    [anon_sym_leftPad] = ACTIONS(295),
    [anon_sym_findReplace] = ACTIONS(295),
    [anon_sym_in] = ACTIONS(295),
    [anon_sym_index] = ACTIONS(295),
    [anon_sym_lastIndexOf] = ACTIONS(295),
    [anon_sym_countSubStr] = ACTIONS(295),
    [anon_sym_parseJson] = ACTIONS(295),
    [anon_sym_parseCsv] = ACTIONS(295),
    [anon_sym_parseHtml] = ACTIONS(295),
    [anon_sym_parseExcel] = ACTIONS(295),
    [anon_sym_readFile] = ACTIONS(295),
    [anon_sym_readFileBytes] = ACTIONS(295),
    [anon_sym_readTsvFile] = ACTIONS(295),
    [anon_sym_writeFile] = ACTIONS(295),
    [anon_sym_appendFile] = ACTIONS(295),
    [anon_sym_fileExists] = ACTIONS(295),
    [anon_sym_isDir] = ACTIONS(295),
    [anon_sym_isFile] = ACTIONS(295),
    [anon_sym_fileSize] = ACTIONS(295),
    [anon_sym_cp] = ACTIONS(295),
    [anon_sym_mv] = ACTIONS(295),
    [anon_sym_rm] = ACTIONS(295),
    [anon_sym_rmf] = ACTIONS(295),
    [anon_sym_mkdir] = ACTIONS(295),
    [anon_sym_mkdirp] = ACTIONS(295),
    [anon_sym_cd] = ACTIONS(295),
    [anon_sym_pwd] = ACTIONS(295),
    [anon_sym_tempFile] = ACTIONS(295),
    [anon_sym_tempFileExt] = ACTIONS(295),
    [anon_sym_tempDir] = ACTIONS(295),
    [anon_sym_lsDir] = ACTIONS(295),
    [anon_sym_files] = ACTIONS(295),
    [anon_sym_dirs] = ACTIONS(295),
    [anon_sym_absPath] = ACTIONS(295),
    [anon_sym_dirname] = ACTIONS(295),
    [anon_sym_basename] = ACTIONS(295),
    [anon_sym_ext] = ACTIONS(295),
    [anon_sym_stem] = ACTIONS(295),
    [anon_sym_isCmd] = ACTIONS(295),
    [anon_sym_hardLink] = ACTIONS(295),
    [anon_sym_sha256sum] = ACTIONS(295),
    [anon_sym_md5] = ACTIONS(295),
    [anon_sym_now] = ACTIONS(295),
    [anon_sym_date] = ACTIONS(295),
    [anon_sym_year] = ACTIONS(295),
    [anon_sym_month] = ACTIONS(295),
    [anon_sym_day] = ACTIONS(295),
    [anon_sym_hour] = ACTIONS(295),
    [anon_sym_minute] = ACTIONS(295),
    [anon_sym_dateFmt] = ACTIONS(295),
    [anon_sym_isoDateFmt] = ACTIONS(295),
    [anon_sym_isoDateTimeFmt] = ACTIONS(295),
    [anon_sym_isWeekend] = ACTIONS(295),
    [anon_sym_isWeekday] = ACTIONS(295),
    [anon_sym_dow] = ACTIONS(295),
    [anon_sym_addDays] = ACTIONS(295),
    [anon_sym_toUnixTime] = ACTIONS(295),
    [anon_sym_toUnixTimeMilli] = ACTIONS(295),
    [anon_sym_toUnixTimeMicro] = ACTIONS(295),
    [anon_sym_toUnixTimeNano] = ACTIONS(295),
    [anon_sym_fromUnixTime] = ACTIONS(295),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(295),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(295),
    [anon_sym_fromUnixTimeNano] = ACTIONS(295),
    [anon_sym_toOleDate] = ACTIONS(295),
    [anon_sym_fromOleDate] = ACTIONS(295),
    [anon_sym_utcToCst] = ACTIONS(295),
    [anon_sym_cstToUtc] = ACTIONS(295),
    [anon_sym_reMatch] = ACTIONS(295),
    [anon_sym_reFindAll] = ACTIONS(295),
    [anon_sym_reFindAllIndex] = ACTIONS(295),
    [anon_sym_reReplace] = ACTIONS(295),
    [anon_sym_reSplit] = ACTIONS(295),
    [anon_sym_just] = ACTIONS(295),
    [anon_sym_none] = ACTIONS(295),
    [anon_sym_isNone] = ACTIONS(295),
    [anon_sym_maybe] = ACTIONS(295),
    [anon_sym_bind] = ACTIONS(295),
    [anon_sym_psub] = ACTIONS(295),
    [anon_sym_typeof] = ACTIONS(295),
    [anon_sym_runtime] = ACTIONS(295),
    [anon_sym_hostname] = ACTIONS(295),
    [anon_sym_httpGet] = ACTIONS(295),
    [anon_sym_httpPost] = ACTIONS(295),
    [anon_sym_urlEncode] = ACTIONS(295),
    [anon_sym_base64encode] = ACTIONS(295),
    [anon_sym_base64decode] = ACTIONS(295),
    [anon_sym_utf8Str] = ACTIONS(295),
    [anon_sym_utf8Bytes] = ACTIONS(295),
    [anon_sym_get] = ACTIONS(295),
    [anon_sym_getDef] = ACTIONS(295),
    [anon_sym_set] = ACTIONS(295),
    [anon_sym_setd] = ACTIONS(295),
    [anon_sym_keys] = ACTIONS(295),
    [anon_sym_values] = ACTIONS(295),
    [anon_sym_keyValues] = ACTIONS(295),
    [anon_sym_all] = ACTIONS(295),
    [anon_sym_any] = ACTIONS(295),
    [anon_sym_cartesian] = ACTIONS(295),
    [anon_sym_groupBy] = ACTIONS(295),
    [anon_sym_listToDict] = ACTIONS(295),
    [anon_sym_repeat] = ACTIONS(295),
    [anon_sym_seq] = ACTIONS(295),
    [anon_sym_tab] = ACTIONS(295),
    [anon_sym_select] = ACTIONS(295),
    [anon_sym_exclude] = ACTIONS(295),
    [anon_sym_derive] = ACTIONS(295),
    [anon_sym_updateCol] = ACTIONS(295),
    [anon_sym_gridValues] = ACTIONS(295),
    [anon_sym_leftJoin] = ACTIONS(295),
    [anon_sym_outerJoin] = ACTIONS(295),
    [anon_sym_linearSearch] = ACTIONS(295),
    [anon_sym_linearSearchIndex] = ACTIONS(295),
    [anon_sym_binPaths] = ACTIONS(295),
    [anon_sym_wt] = ACTIONS(295),
    [anon_sym_tt] = ACTIONS(295),
    [anon_sym_ttFile] = ACTIONS(295),
    [anon_sym_uw] = ACTIONS(295),
    [anon_sym_tuw] = ACTIONS(295),
    [anon_sym_strCmp] = ACTIONS(295),
    [anon_sym_floatCmp] = ACTIONS(295),
    [anon_sym_versionSortCmp] = ACTIONS(295),
    [anon_sym_id] = ACTIONS(295),
    [anon_sym_2id] = ACTIONS(295),
    [anon_sym_3id] = ACTIONS(295),
    [anon_sym_2unpack] = ACTIONS(295),
    [anon_sym_2apply] = ACTIONS(295),
    [anon_sym_2each] = ACTIONS(295),
    [anon_sym_2tuple] = ACTIONS(295),
    [anon_sym_DOTs] = ACTIONS(295),
    [anon_sym_DOTb] = ACTIONS(295),
    [anon_sym_DOTdef] = ACTIONS(295),
    [anon_sym_DOTenv] = ACTIONS(295),
    [sym_string] = ACTIONS(293),
    [sym_format_string] = ACTIONS(293),
    [sym_single_quoted_string] = ACTIONS(293),
    [sym_path] = ACTIONS(293),
    [sym_datetime] = ACTIONS(293),
    [sym_float] = ACTIONS(293),
    [sym_integer] = ACTIONS(295),
    [sym_env_store] = ACTIONS(293),
    [sym_env_check] = ACTIONS(293),
    [sym_env_retrieve] = ACTIONS(295),
    [sym_positional] = ACTIONS(293),
    [sym_var_retrieve] = ACTIONS(293),
    [sym_var_store] = ACTIONS(293),
    [sym_slice_indexer] = ACTIONS(293),
    [sym_indexer] = ACTIONS(293),
    [sym_end_indexer] = ACTIONS(295),
    [sym_start_indexer] = ACTIONS(295),
    [sym_match_arm_dup] = ACTIONS(293),
    [sym_prefix_quote] = ACTIONS(295),
    [anon_sym_GT] = ACTIONS(295),
    [anon_sym_GT_GT] = ACTIONS(293),
    [anon_sym_2_GT] = ACTIONS(295),
    [anon_sym_2_GT_GT] = ACTIONS(295),
    [anon_sym_AMP_GT] = ACTIONS(295),
    [anon_sym_AMP_GT_GT] = ACTIONS(293),
    [anon_sym_LT] = ACTIONS(295),
    [anon_sym_LT_GT] = ACTIONS(293),
    [anon_sym_STAR] = ACTIONS(295),
    [anon_sym_STARb] = ACTIONS(293),
    [anon_sym_CARET] = ACTIONS(295),
    [anon_sym_CARETb] = ACTIONS(293),
    [anon_sym_SEMI] = ACTIONS(293),
    [anon_sym_BANG] = ACTIONS(295),
    [anon_sym_QMARK] = ACTIONS(293),
    [anon_sym_BANG_EQ] = ACTIONS(293),
    [anon_sym_LT_EQ] = ACTIONS(293),
    [anon_sym_GT_EQ] = ACTIONS(293),
    [anon_sym_AMP] = ACTIONS(295),
    [anon_sym_PIPE] = ACTIONS(293),
    [anon_sym_COMMA] = ACTIONS(293),
    [anon_sym_COLON] = ACTIONS(295),
  },
  [28] = {
    [ts_builtin_sym_end] = ACTIONS(297),
    [sym_identifier] = ACTIONS(299),
    [anon_sym_LBRACK] = ACTIONS(299),
    [anon_sym_RBRACK] = ACTIONS(297),
    [anon_sym_LPAREN] = ACTIONS(297),
    [anon_sym_RPAREN] = ACTIONS(297),
    [anon_sym_LBRACE] = ACTIONS(297),
    [anon_sym_RBRACE] = ACTIONS(297),
    [anon_sym_LBRACK_PIPE] = ACTIONS(297),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(299),
    [anon_sym_false] = ACTIONS(299),
    [anon_sym_def] = ACTIONS(299),
    [anon_sym_end] = ACTIONS(299),
    [anon_sym_if] = ACTIONS(299),
    [anon_sym_iff] = ACTIONS(299),
    [anon_sym_else] = ACTIONS(299),
    [anon_sym_else_STAR] = ACTIONS(297),
    [anon_sym_STARif] = ACTIONS(297),
    [anon_sym_loop] = ACTIONS(299),
    [anon_sym_match] = ACTIONS(299),
    [anon_sym_break] = ACTIONS(299),
    [anon_sym_continue] = ACTIONS(299),
    [anon_sym_soe] = ACTIONS(299),
    [anon_sym_not] = ACTIONS(299),
    [anon_sym_and] = ACTIONS(299),
    [anon_sym_or] = ACTIONS(299),
    [anon_sym_read] = ACTIONS(299),
    [anon_sym_str] = ACTIONS(299),
    [anon_sym_as] = ACTIONS(299),
    [anon_sym_type] = ACTIONS(299),
    [anon_sym_try] = ACTIONS(299),
    [anon_sym_fail] = ACTIONS(299),
    [anon_sym_pure] = ACTIONS(299),
    [anon_sym_VER] = ACTIONS(299),
    [anon_sym_x] = ACTIONS(299),
    [anon_sym_int] = ACTIONS(299),
    [anon_sym_float] = ACTIONS(299),
    [anon_sym_bool] = ACTIONS(299),
    [anon_sym_dup] = ACTIONS(299),
    [anon_sym_swap] = ACTIONS(299),
    [anon_sym_drop] = ACTIONS(299),
    [anon_sym_over] = ACTIONS(299),
    [anon_sym_pick] = ACTIONS(299),
    [anon_sym_rot] = ACTIONS(299),
    [anon_sym_DASHrot] = ACTIONS(299),
    [anon_sym_nip] = ACTIONS(299),
    [anon_sym_w] = ACTIONS(299),
    [anon_sym_wl] = ACTIONS(299),
    [anon_sym_we] = ACTIONS(299),
    [anon_sym_wle] = ACTIONS(299),
    [anon_sym_len] = ACTIONS(299),
    [anon_sym_args] = ACTIONS(299),
    [anon_sym_glob] = ACTIONS(299),
    [anon_sym_toFloat] = ACTIONS(299),
    [anon_sym_toInt] = ACTIONS(299),
    [anon_sym_toPath] = ACTIONS(299),
    [anon_sym_toDt] = ACTIONS(299),
    [anon_sym_toGrid] = ACTIONS(299),
    [anon_sym_toCsv] = ACTIONS(299),
    [anon_sym_toCsvCell] = ACTIONS(299),
    [anon_sym_exit] = ACTIONS(299),
    [anon_sym_prompt] = ACTIONS(299),
    [anon_sym_stdin] = ACTIONS(299),
    [anon_sym_COLON_COLON] = ACTIONS(297),
    [anon_sym_foldl] = ACTIONS(299),
    [anon_sym_map] = ACTIONS(299),
    [anon_sym_each] = ACTIONS(299),
    [anon_sym_eachWhile] = ACTIONS(299),
    [anon_sym_filter] = ACTIONS(299),
    [anon_sym_append] = ACTIONS(299),
    [anon_sym_extend] = ACTIONS(299),
    [anon_sym_concat] = ACTIONS(299),
    [anon_sym_reverse] = ACTIONS(299),
    [anon_sym_sort] = ACTIONS(299),
    [anon_sym_sortV] = ACTIONS(299),
    [anon_sym_sortBy] = ACTIONS(299),
    [anon_sym_sortByCmp] = ACTIONS(299),
    [anon_sym_uniq] = ACTIONS(299),
    [anon_sym_zip] = ACTIONS(299),
    [anon_sym_enumerate] = ACTIONS(299),
    [anon_sym_enumerateN] = ACTIONS(299),
    [anon_sym_chunk] = ACTIONS(299),
    [anon_sym_pop] = ACTIONS(299),
    [anon_sym_take] = ACTIONS(299),
    [anon_sym_takeWhile] = ACTIONS(299),
    [anon_sym_skip] = ACTIONS(299),
    [anon_sym_dropWhile] = ACTIONS(299),
    [anon_sym_nth] = ACTIONS(299),
    [anon_sym_insert] = ACTIONS(299),
    [anon_sym_setAt] = ACTIONS(299),
    [anon_sym_del] = ACTIONS(299),
    [anon_sym_sum] = ACTIONS(299),
    [anon_sym_max] = ACTIONS(299),
    [anon_sym_max2] = ACTIONS(299),
    [anon_sym_min] = ACTIONS(299),
    [anon_sym_min2] = ACTIONS(299),
    [anon_sym_abs] = ACTIONS(299),
    [anon_sym_inc] = ACTIONS(299),
    [anon_sym_mod] = ACTIONS(299),
    [anon_sym_floor] = ACTIONS(299),
    [anon_sym_ceil] = ACTIONS(299),
    [anon_sym_round] = ACTIONS(299),
    [anon_sym_lines] = ACTIONS(299),
    [anon_sym_unlines] = ACTIONS(299),
    [anon_sym_unlinesCrLf] = ACTIONS(299),
    [anon_sym_split] = ACTIONS(299),
    [anon_sym_wsplit] = ACTIONS(299),
    [anon_sym_tsplit] = ACTIONS(299),
    [anon_sym_join] = ACTIONS(299),
    [anon_sym_trim] = ACTIONS(299),
    [anon_sym_trimStart] = ACTIONS(299),
    [anon_sym_trimEnd] = ACTIONS(299),
    [anon_sym_startsWith] = ACTIONS(299),
    [anon_sym_endsWith] = ACTIONS(299),
    [anon_sym_lower] = ACTIONS(299),
    [anon_sym_upper] = ACTIONS(299),
    [anon_sym_title] = ACTIONS(299),
    [anon_sym_leftPad] = ACTIONS(299),
    [anon_sym_findReplace] = ACTIONS(299),
    [anon_sym_in] = ACTIONS(299),
    [anon_sym_index] = ACTIONS(299),
    [anon_sym_lastIndexOf] = ACTIONS(299),
    [anon_sym_countSubStr] = ACTIONS(299),
    [anon_sym_parseJson] = ACTIONS(299),
    [anon_sym_parseCsv] = ACTIONS(299),
    [anon_sym_parseHtml] = ACTIONS(299),
    [anon_sym_parseExcel] = ACTIONS(299),
    [anon_sym_readFile] = ACTIONS(299),
    [anon_sym_readFileBytes] = ACTIONS(299),
    [anon_sym_readTsvFile] = ACTIONS(299),
    [anon_sym_writeFile] = ACTIONS(299),
    [anon_sym_appendFile] = ACTIONS(299),
    [anon_sym_fileExists] = ACTIONS(299),
    [anon_sym_isDir] = ACTIONS(299),
    [anon_sym_isFile] = ACTIONS(299),
    [anon_sym_fileSize] = ACTIONS(299),
    [anon_sym_cp] = ACTIONS(299),
    [anon_sym_mv] = ACTIONS(299),
    [anon_sym_rm] = ACTIONS(299),
    [anon_sym_rmf] = ACTIONS(299),
    [anon_sym_mkdir] = ACTIONS(299),
    [anon_sym_mkdirp] = ACTIONS(299),
    [anon_sym_cd] = ACTIONS(299),
    [anon_sym_pwd] = ACTIONS(299),
    [anon_sym_tempFile] = ACTIONS(299),
    [anon_sym_tempFileExt] = ACTIONS(299),
    [anon_sym_tempDir] = ACTIONS(299),
    [anon_sym_lsDir] = ACTIONS(299),
    [anon_sym_files] = ACTIONS(299),
    [anon_sym_dirs] = ACTIONS(299),
    [anon_sym_absPath] = ACTIONS(299),
    [anon_sym_dirname] = ACTIONS(299),
    [anon_sym_basename] = ACTIONS(299),
    [anon_sym_ext] = ACTIONS(299),
    [anon_sym_stem] = ACTIONS(299),
    [anon_sym_isCmd] = ACTIONS(299),
    [anon_sym_hardLink] = ACTIONS(299),
    [anon_sym_sha256sum] = ACTIONS(299),
    [anon_sym_md5] = ACTIONS(299),
    [anon_sym_now] = ACTIONS(299),
    [anon_sym_date] = ACTIONS(299),
    [anon_sym_year] = ACTIONS(299),
    [anon_sym_month] = ACTIONS(299),
    [anon_sym_day] = ACTIONS(299),
    [anon_sym_hour] = ACTIONS(299),
    [anon_sym_minute] = ACTIONS(299),
    [anon_sym_dateFmt] = ACTIONS(299),
    [anon_sym_isoDateFmt] = ACTIONS(299),
    [anon_sym_isoDateTimeFmt] = ACTIONS(299),
    [anon_sym_isWeekend] = ACTIONS(299),
    [anon_sym_isWeekday] = ACTIONS(299),
    [anon_sym_dow] = ACTIONS(299),
    [anon_sym_addDays] = ACTIONS(299),
    [anon_sym_toUnixTime] = ACTIONS(299),
    [anon_sym_toUnixTimeMilli] = ACTIONS(299),
    [anon_sym_toUnixTimeMicro] = ACTIONS(299),
    [anon_sym_toUnixTimeNano] = ACTIONS(299),
    [anon_sym_fromUnixTime] = ACTIONS(299),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(299),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(299),
    [anon_sym_fromUnixTimeNano] = ACTIONS(299),
    [anon_sym_toOleDate] = ACTIONS(299),
    [anon_sym_fromOleDate] = ACTIONS(299),
    [anon_sym_utcToCst] = ACTIONS(299),
    [anon_sym_cstToUtc] = ACTIONS(299),
    [anon_sym_reMatch] = ACTIONS(299),
    [anon_sym_reFindAll] = ACTIONS(299),
    [anon_sym_reFindAllIndex] = ACTIONS(299),
    [anon_sym_reReplace] = ACTIONS(299),
    [anon_sym_reSplit] = ACTIONS(299),
    [anon_sym_just] = ACTIONS(299),
    [anon_sym_none] = ACTIONS(299),
    [anon_sym_isNone] = ACTIONS(299),
    [anon_sym_maybe] = ACTIONS(299),
    [anon_sym_bind] = ACTIONS(299),
    [anon_sym_psub] = ACTIONS(299),
    [anon_sym_typeof] = ACTIONS(299),
    [anon_sym_runtime] = ACTIONS(299),
    [anon_sym_hostname] = ACTIONS(299),
    [anon_sym_httpGet] = ACTIONS(299),
    [anon_sym_httpPost] = ACTIONS(299),
    [anon_sym_urlEncode] = ACTIONS(299),
    [anon_sym_base64encode] = ACTIONS(299),
    [anon_sym_base64decode] = ACTIONS(299),
    [anon_sym_utf8Str] = ACTIONS(299),
    [anon_sym_utf8Bytes] = ACTIONS(299),
    [anon_sym_get] = ACTIONS(299),
    [anon_sym_getDef] = ACTIONS(299),
    [anon_sym_set] = ACTIONS(299),
    [anon_sym_setd] = ACTIONS(299),
    [anon_sym_keys] = ACTIONS(299),
    [anon_sym_values] = ACTIONS(299),
    [anon_sym_keyValues] = ACTIONS(299),
    [anon_sym_all] = ACTIONS(299),
    [anon_sym_any] = ACTIONS(299),
    [anon_sym_cartesian] = ACTIONS(299),
    [anon_sym_groupBy] = ACTIONS(299),
    [anon_sym_listToDict] = ACTIONS(299),
    [anon_sym_repeat] = ACTIONS(299),
    [anon_sym_seq] = ACTIONS(299),
    [anon_sym_tab] = ACTIONS(299),
    [anon_sym_select] = ACTIONS(299),
    [anon_sym_exclude] = ACTIONS(299),
    [anon_sym_derive] = ACTIONS(299),
    [anon_sym_updateCol] = ACTIONS(299),
    [anon_sym_gridValues] = ACTIONS(299),
    [anon_sym_leftJoin] = ACTIONS(299),
    [anon_sym_outerJoin] = ACTIONS(299),
    [anon_sym_linearSearch] = ACTIONS(299),
    [anon_sym_linearSearchIndex] = ACTIONS(299),
    [anon_sym_binPaths] = ACTIONS(299),
    [anon_sym_wt] = ACTIONS(299),
    [anon_sym_tt] = ACTIONS(299),
    [anon_sym_ttFile] = ACTIONS(299),
    [anon_sym_uw] = ACTIONS(299),
    [anon_sym_tuw] = ACTIONS(299),
    [anon_sym_strCmp] = ACTIONS(299),
    [anon_sym_floatCmp] = ACTIONS(299),
    [anon_sym_versionSortCmp] = ACTIONS(299),
    [anon_sym_id] = ACTIONS(299),
    [anon_sym_2id] = ACTIONS(299),
    [anon_sym_3id] = ACTIONS(299),
    [anon_sym_2unpack] = ACTIONS(299),
    [anon_sym_2apply] = ACTIONS(299),
    [anon_sym_2each] = ACTIONS(299),
    [anon_sym_2tuple] = ACTIONS(299),
    [anon_sym_DOTs] = ACTIONS(299),
    [anon_sym_DOTb] = ACTIONS(299),
    [anon_sym_DOTdef] = ACTIONS(299),
    [anon_sym_DOTenv] = ACTIONS(299),
    [sym_string] = ACTIONS(297),
    [sym_format_string] = ACTIONS(297),
    [sym_single_quoted_string] = ACTIONS(297),
    [sym_path] = ACTIONS(297),
    [sym_datetime] = ACTIONS(297),
    [sym_float] = ACTIONS(297),
    [sym_integer] = ACTIONS(299),
    [sym_env_store] = ACTIONS(297),
    [sym_env_check] = ACTIONS(297),
    [sym_env_retrieve] = ACTIONS(299),
    [sym_positional] = ACTIONS(297),
    [sym_var_retrieve] = ACTIONS(297),
    [sym_var_store] = ACTIONS(297),
    [sym_slice_indexer] = ACTIONS(297),
    [sym_indexer] = ACTIONS(297),
    [sym_end_indexer] = ACTIONS(299),
    [sym_start_indexer] = ACTIONS(299),
    [sym_match_arm_dup] = ACTIONS(297),
    [sym_prefix_quote] = ACTIONS(299),
    [anon_sym_GT] = ACTIONS(299),
    [anon_sym_GT_GT] = ACTIONS(297),
    [anon_sym_2_GT] = ACTIONS(299),
    [anon_sym_2_GT_GT] = ACTIONS(299),
    [anon_sym_AMP_GT] = ACTIONS(299),
    [anon_sym_AMP_GT_GT] = ACTIONS(297),
    [anon_sym_LT] = ACTIONS(299),
    [anon_sym_LT_GT] = ACTIONS(297),
    [anon_sym_STAR] = ACTIONS(299),
    [anon_sym_STARb] = ACTIONS(297),
    [anon_sym_CARET] = ACTIONS(299),
    [anon_sym_CARETb] = ACTIONS(297),
    [anon_sym_SEMI] = ACTIONS(297),
    [anon_sym_BANG] = ACTIONS(299),
    [anon_sym_QMARK] = ACTIONS(297),
    [anon_sym_BANG_EQ] = ACTIONS(297),
    [anon_sym_LT_EQ] = ACTIONS(297),
    [anon_sym_GT_EQ] = ACTIONS(297),
    [anon_sym_AMP] = ACTIONS(299),
    [anon_sym_PIPE] = ACTIONS(297),
    [anon_sym_COMMA] = ACTIONS(297),
    [anon_sym_COLON] = ACTIONS(299),
  },
  [29] = {
    [ts_builtin_sym_end] = ACTIONS(301),
    [sym_identifier] = ACTIONS(303),
    [anon_sym_LBRACK] = ACTIONS(303),
    [anon_sym_RBRACK] = ACTIONS(301),
    [anon_sym_LPAREN] = ACTIONS(301),
    [anon_sym_RPAREN] = ACTIONS(301),
    [anon_sym_LBRACE] = ACTIONS(301),
    [anon_sym_RBRACE] = ACTIONS(301),
    [anon_sym_LBRACK_PIPE] = ACTIONS(301),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(303),
    [anon_sym_false] = ACTIONS(303),
    [anon_sym_def] = ACTIONS(303),
    [anon_sym_end] = ACTIONS(303),
    [anon_sym_if] = ACTIONS(303),
    [anon_sym_iff] = ACTIONS(303),
    [anon_sym_else] = ACTIONS(303),
    [anon_sym_else_STAR] = ACTIONS(301),
    [anon_sym_STARif] = ACTIONS(301),
    [anon_sym_loop] = ACTIONS(303),
    [anon_sym_match] = ACTIONS(303),
    [anon_sym_break] = ACTIONS(303),
    [anon_sym_continue] = ACTIONS(303),
    [anon_sym_soe] = ACTIONS(303),
    [anon_sym_not] = ACTIONS(303),
    [anon_sym_and] = ACTIONS(303),
    [anon_sym_or] = ACTIONS(303),
    [anon_sym_read] = ACTIONS(303),
    [anon_sym_str] = ACTIONS(303),
    [anon_sym_as] = ACTIONS(303),
    [anon_sym_type] = ACTIONS(303),
    [anon_sym_try] = ACTIONS(303),
    [anon_sym_fail] = ACTIONS(303),
    [anon_sym_pure] = ACTIONS(303),
    [anon_sym_VER] = ACTIONS(303),
    [anon_sym_x] = ACTIONS(303),
    [anon_sym_int] = ACTIONS(303),
    [anon_sym_float] = ACTIONS(303),
    [anon_sym_bool] = ACTIONS(303),
    [anon_sym_dup] = ACTIONS(303),
    [anon_sym_swap] = ACTIONS(303),
    [anon_sym_drop] = ACTIONS(303),
    [anon_sym_over] = ACTIONS(303),
    [anon_sym_pick] = ACTIONS(303),
    [anon_sym_rot] = ACTIONS(303),
    [anon_sym_DASHrot] = ACTIONS(303),
    [anon_sym_nip] = ACTIONS(303),
    [anon_sym_w] = ACTIONS(303),
    [anon_sym_wl] = ACTIONS(303),
    [anon_sym_we] = ACTIONS(303),
    [anon_sym_wle] = ACTIONS(303),
    [anon_sym_len] = ACTIONS(303),
    [anon_sym_args] = ACTIONS(303),
    [anon_sym_glob] = ACTIONS(303),
    [anon_sym_toFloat] = ACTIONS(303),
    [anon_sym_toInt] = ACTIONS(303),
    [anon_sym_toPath] = ACTIONS(303),
    [anon_sym_toDt] = ACTIONS(303),
    [anon_sym_toGrid] = ACTIONS(303),
    [anon_sym_toCsv] = ACTIONS(303),
    [anon_sym_toCsvCell] = ACTIONS(303),
    [anon_sym_exit] = ACTIONS(303),
    [anon_sym_prompt] = ACTIONS(303),
    [anon_sym_stdin] = ACTIONS(303),
    [anon_sym_COLON_COLON] = ACTIONS(301),
    [anon_sym_foldl] = ACTIONS(303),
    [anon_sym_map] = ACTIONS(303),
    [anon_sym_each] = ACTIONS(303),
    [anon_sym_eachWhile] = ACTIONS(303),
    [anon_sym_filter] = ACTIONS(303),
    [anon_sym_append] = ACTIONS(303),
    [anon_sym_extend] = ACTIONS(303),
    [anon_sym_concat] = ACTIONS(303),
    [anon_sym_reverse] = ACTIONS(303),
    [anon_sym_sort] = ACTIONS(303),
    [anon_sym_sortV] = ACTIONS(303),
    [anon_sym_sortBy] = ACTIONS(303),
    [anon_sym_sortByCmp] = ACTIONS(303),
    [anon_sym_uniq] = ACTIONS(303),
    [anon_sym_zip] = ACTIONS(303),
    [anon_sym_enumerate] = ACTIONS(303),
    [anon_sym_enumerateN] = ACTIONS(303),
    [anon_sym_chunk] = ACTIONS(303),
    [anon_sym_pop] = ACTIONS(303),
    [anon_sym_take] = ACTIONS(303),
    [anon_sym_takeWhile] = ACTIONS(303),
    [anon_sym_skip] = ACTIONS(303),
    [anon_sym_dropWhile] = ACTIONS(303),
    [anon_sym_nth] = ACTIONS(303),
    [anon_sym_insert] = ACTIONS(303),
    [anon_sym_setAt] = ACTIONS(303),
    [anon_sym_del] = ACTIONS(303),
    [anon_sym_sum] = ACTIONS(303),
    [anon_sym_max] = ACTIONS(303),
    [anon_sym_max2] = ACTIONS(303),
    [anon_sym_min] = ACTIONS(303),
    [anon_sym_min2] = ACTIONS(303),
    [anon_sym_abs] = ACTIONS(303),
    [anon_sym_inc] = ACTIONS(303),
    [anon_sym_mod] = ACTIONS(303),
    [anon_sym_floor] = ACTIONS(303),
    [anon_sym_ceil] = ACTIONS(303),
    [anon_sym_round] = ACTIONS(303),
    [anon_sym_lines] = ACTIONS(303),
    [anon_sym_unlines] = ACTIONS(303),
    [anon_sym_unlinesCrLf] = ACTIONS(303),
    [anon_sym_split] = ACTIONS(303),
    [anon_sym_wsplit] = ACTIONS(303),
    [anon_sym_tsplit] = ACTIONS(303),
    [anon_sym_join] = ACTIONS(303),
    [anon_sym_trim] = ACTIONS(303),
    [anon_sym_trimStart] = ACTIONS(303),
    [anon_sym_trimEnd] = ACTIONS(303),
    [anon_sym_startsWith] = ACTIONS(303),
    [anon_sym_endsWith] = ACTIONS(303),
    [anon_sym_lower] = ACTIONS(303),
    [anon_sym_upper] = ACTIONS(303),
    [anon_sym_title] = ACTIONS(303),
    [anon_sym_leftPad] = ACTIONS(303),
    [anon_sym_findReplace] = ACTIONS(303),
    [anon_sym_in] = ACTIONS(303),
    [anon_sym_index] = ACTIONS(303),
    [anon_sym_lastIndexOf] = ACTIONS(303),
    [anon_sym_countSubStr] = ACTIONS(303),
    [anon_sym_parseJson] = ACTIONS(303),
    [anon_sym_parseCsv] = ACTIONS(303),
    [anon_sym_parseHtml] = ACTIONS(303),
    [anon_sym_parseExcel] = ACTIONS(303),
    [anon_sym_readFile] = ACTIONS(303),
    [anon_sym_readFileBytes] = ACTIONS(303),
    [anon_sym_readTsvFile] = ACTIONS(303),
    [anon_sym_writeFile] = ACTIONS(303),
    [anon_sym_appendFile] = ACTIONS(303),
    [anon_sym_fileExists] = ACTIONS(303),
    [anon_sym_isDir] = ACTIONS(303),
    [anon_sym_isFile] = ACTIONS(303),
    [anon_sym_fileSize] = ACTIONS(303),
    [anon_sym_cp] = ACTIONS(303),
    [anon_sym_mv] = ACTIONS(303),
    [anon_sym_rm] = ACTIONS(303),
    [anon_sym_rmf] = ACTIONS(303),
    [anon_sym_mkdir] = ACTIONS(303),
    [anon_sym_mkdirp] = ACTIONS(303),
    [anon_sym_cd] = ACTIONS(303),
    [anon_sym_pwd] = ACTIONS(303),
    [anon_sym_tempFile] = ACTIONS(303),
    [anon_sym_tempFileExt] = ACTIONS(303),
    [anon_sym_tempDir] = ACTIONS(303),
    [anon_sym_lsDir] = ACTIONS(303),
    [anon_sym_files] = ACTIONS(303),
    [anon_sym_dirs] = ACTIONS(303),
    [anon_sym_absPath] = ACTIONS(303),
    [anon_sym_dirname] = ACTIONS(303),
    [anon_sym_basename] = ACTIONS(303),
    [anon_sym_ext] = ACTIONS(303),
    [anon_sym_stem] = ACTIONS(303),
    [anon_sym_isCmd] = ACTIONS(303),
    [anon_sym_hardLink] = ACTIONS(303),
    [anon_sym_sha256sum] = ACTIONS(303),
    [anon_sym_md5] = ACTIONS(303),
    [anon_sym_now] = ACTIONS(303),
    [anon_sym_date] = ACTIONS(303),
    [anon_sym_year] = ACTIONS(303),
    [anon_sym_month] = ACTIONS(303),
    [anon_sym_day] = ACTIONS(303),
    [anon_sym_hour] = ACTIONS(303),
    [anon_sym_minute] = ACTIONS(303),
    [anon_sym_dateFmt] = ACTIONS(303),
    [anon_sym_isoDateFmt] = ACTIONS(303),
    [anon_sym_isoDateTimeFmt] = ACTIONS(303),
    [anon_sym_isWeekend] = ACTIONS(303),
    [anon_sym_isWeekday] = ACTIONS(303),
    [anon_sym_dow] = ACTIONS(303),
    [anon_sym_addDays] = ACTIONS(303),
    [anon_sym_toUnixTime] = ACTIONS(303),
    [anon_sym_toUnixTimeMilli] = ACTIONS(303),
    [anon_sym_toUnixTimeMicro] = ACTIONS(303),
    [anon_sym_toUnixTimeNano] = ACTIONS(303),
    [anon_sym_fromUnixTime] = ACTIONS(303),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(303),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(303),
    [anon_sym_fromUnixTimeNano] = ACTIONS(303),
    [anon_sym_toOleDate] = ACTIONS(303),
    [anon_sym_fromOleDate] = ACTIONS(303),
    [anon_sym_utcToCst] = ACTIONS(303),
    [anon_sym_cstToUtc] = ACTIONS(303),
    [anon_sym_reMatch] = ACTIONS(303),
    [anon_sym_reFindAll] = ACTIONS(303),
    [anon_sym_reFindAllIndex] = ACTIONS(303),
    [anon_sym_reReplace] = ACTIONS(303),
    [anon_sym_reSplit] = ACTIONS(303),
    [anon_sym_just] = ACTIONS(303),
    [anon_sym_none] = ACTIONS(303),
    [anon_sym_isNone] = ACTIONS(303),
    [anon_sym_maybe] = ACTIONS(303),
    [anon_sym_bind] = ACTIONS(303),
    [anon_sym_psub] = ACTIONS(303),
    [anon_sym_typeof] = ACTIONS(303),
    [anon_sym_runtime] = ACTIONS(303),
    [anon_sym_hostname] = ACTIONS(303),
    [anon_sym_httpGet] = ACTIONS(303),
    [anon_sym_httpPost] = ACTIONS(303),
    [anon_sym_urlEncode] = ACTIONS(303),
    [anon_sym_base64encode] = ACTIONS(303),
    [anon_sym_base64decode] = ACTIONS(303),
    [anon_sym_utf8Str] = ACTIONS(303),
    [anon_sym_utf8Bytes] = ACTIONS(303),
    [anon_sym_get] = ACTIONS(303),
    [anon_sym_getDef] = ACTIONS(303),
    [anon_sym_set] = ACTIONS(303),
    [anon_sym_setd] = ACTIONS(303),
    [anon_sym_keys] = ACTIONS(303),
    [anon_sym_values] = ACTIONS(303),
    [anon_sym_keyValues] = ACTIONS(303),
    [anon_sym_all] = ACTIONS(303),
    [anon_sym_any] = ACTIONS(303),
    [anon_sym_cartesian] = ACTIONS(303),
    [anon_sym_groupBy] = ACTIONS(303),
    [anon_sym_listToDict] = ACTIONS(303),
    [anon_sym_repeat] = ACTIONS(303),
    [anon_sym_seq] = ACTIONS(303),
    [anon_sym_tab] = ACTIONS(303),
    [anon_sym_select] = ACTIONS(303),
    [anon_sym_exclude] = ACTIONS(303),
    [anon_sym_derive] = ACTIONS(303),
    [anon_sym_updateCol] = ACTIONS(303),
    [anon_sym_gridValues] = ACTIONS(303),
    [anon_sym_leftJoin] = ACTIONS(303),
    [anon_sym_outerJoin] = ACTIONS(303),
    [anon_sym_linearSearch] = ACTIONS(303),
    [anon_sym_linearSearchIndex] = ACTIONS(303),
    [anon_sym_binPaths] = ACTIONS(303),
    [anon_sym_wt] = ACTIONS(303),
    [anon_sym_tt] = ACTIONS(303),
    [anon_sym_ttFile] = ACTIONS(303),
    [anon_sym_uw] = ACTIONS(303),
    [anon_sym_tuw] = ACTIONS(303),
    [anon_sym_strCmp] = ACTIONS(303),
    [anon_sym_floatCmp] = ACTIONS(303),
    [anon_sym_versionSortCmp] = ACTIONS(303),
    [anon_sym_id] = ACTIONS(303),
    [anon_sym_2id] = ACTIONS(303),
    [anon_sym_3id] = ACTIONS(303),
    [anon_sym_2unpack] = ACTIONS(303),
    [anon_sym_2apply] = ACTIONS(303),
    [anon_sym_2each] = ACTIONS(303),
    [anon_sym_2tuple] = ACTIONS(303),
    [anon_sym_DOTs] = ACTIONS(303),
    [anon_sym_DOTb] = ACTIONS(303),
    [anon_sym_DOTdef] = ACTIONS(303),
    [anon_sym_DOTenv] = ACTIONS(303),
    [sym_string] = ACTIONS(301),
    [sym_format_string] = ACTIONS(301),
    [sym_single_quoted_string] = ACTIONS(301),
    [sym_path] = ACTIONS(301),
    [sym_datetime] = ACTIONS(301),
    [sym_float] = ACTIONS(301),
    [sym_integer] = ACTIONS(303),
    [sym_env_store] = ACTIONS(301),
    [sym_env_check] = ACTIONS(301),
    [sym_env_retrieve] = ACTIONS(303),
    [sym_positional] = ACTIONS(301),
    [sym_var_retrieve] = ACTIONS(301),
    [sym_var_store] = ACTIONS(301),
    [sym_slice_indexer] = ACTIONS(301),
    [sym_indexer] = ACTIONS(301),
    [sym_end_indexer] = ACTIONS(303),
    [sym_start_indexer] = ACTIONS(303),
    [sym_match_arm_dup] = ACTIONS(301),
    [sym_prefix_quote] = ACTIONS(303),
    [anon_sym_GT] = ACTIONS(303),
    [anon_sym_GT_GT] = ACTIONS(301),
    [anon_sym_2_GT] = ACTIONS(303),
    [anon_sym_2_GT_GT] = ACTIONS(303),
    [anon_sym_AMP_GT] = ACTIONS(303),
    [anon_sym_AMP_GT_GT] = ACTIONS(301),
    [anon_sym_LT] = ACTIONS(303),
    [anon_sym_LT_GT] = ACTIONS(301),
    [anon_sym_STAR] = ACTIONS(303),
    [anon_sym_STARb] = ACTIONS(301),
    [anon_sym_CARET] = ACTIONS(303),
    [anon_sym_CARETb] = ACTIONS(301),
    [anon_sym_SEMI] = ACTIONS(301),
    [anon_sym_BANG] = ACTIONS(303),
    [anon_sym_QMARK] = ACTIONS(301),
    [anon_sym_BANG_EQ] = ACTIONS(301),
    [anon_sym_LT_EQ] = ACTIONS(301),
    [anon_sym_GT_EQ] = ACTIONS(301),
    [anon_sym_AMP] = ACTIONS(303),
    [anon_sym_PIPE] = ACTIONS(301),
    [anon_sym_COMMA] = ACTIONS(301),
    [anon_sym_COLON] = ACTIONS(303),
  },
  [30] = {
    [ts_builtin_sym_end] = ACTIONS(305),
    [sym_identifier] = ACTIONS(307),
    [anon_sym_LBRACK] = ACTIONS(307),
    [anon_sym_RBRACK] = ACTIONS(305),
    [anon_sym_LPAREN] = ACTIONS(305),
    [anon_sym_RPAREN] = ACTIONS(305),
    [anon_sym_LBRACE] = ACTIONS(305),
    [anon_sym_RBRACE] = ACTIONS(305),
    [anon_sym_LBRACK_PIPE] = ACTIONS(305),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(307),
    [anon_sym_false] = ACTIONS(307),
    [anon_sym_def] = ACTIONS(307),
    [anon_sym_end] = ACTIONS(307),
    [anon_sym_if] = ACTIONS(307),
    [anon_sym_iff] = ACTIONS(307),
    [anon_sym_else] = ACTIONS(307),
    [anon_sym_else_STAR] = ACTIONS(305),
    [anon_sym_STARif] = ACTIONS(305),
    [anon_sym_loop] = ACTIONS(307),
    [anon_sym_match] = ACTIONS(307),
    [anon_sym_break] = ACTIONS(307),
    [anon_sym_continue] = ACTIONS(307),
    [anon_sym_soe] = ACTIONS(307),
    [anon_sym_not] = ACTIONS(307),
    [anon_sym_and] = ACTIONS(307),
    [anon_sym_or] = ACTIONS(307),
    [anon_sym_read] = ACTIONS(307),
    [anon_sym_str] = ACTIONS(307),
    [anon_sym_as] = ACTIONS(307),
    [anon_sym_type] = ACTIONS(307),
    [anon_sym_try] = ACTIONS(307),
    [anon_sym_fail] = ACTIONS(307),
    [anon_sym_pure] = ACTIONS(307),
    [anon_sym_VER] = ACTIONS(307),
    [anon_sym_x] = ACTIONS(307),
    [anon_sym_int] = ACTIONS(307),
    [anon_sym_float] = ACTIONS(307),
    [anon_sym_bool] = ACTIONS(307),
    [anon_sym_dup] = ACTIONS(307),
    [anon_sym_swap] = ACTIONS(307),
    [anon_sym_drop] = ACTIONS(307),
    [anon_sym_over] = ACTIONS(307),
    [anon_sym_pick] = ACTIONS(307),
    [anon_sym_rot] = ACTIONS(307),
    [anon_sym_DASHrot] = ACTIONS(307),
    [anon_sym_nip] = ACTIONS(307),
    [anon_sym_w] = ACTIONS(307),
    [anon_sym_wl] = ACTIONS(307),
    [anon_sym_we] = ACTIONS(307),
    [anon_sym_wle] = ACTIONS(307),
    [anon_sym_len] = ACTIONS(307),
    [anon_sym_args] = ACTIONS(307),
    [anon_sym_glob] = ACTIONS(307),
    [anon_sym_toFloat] = ACTIONS(307),
    [anon_sym_toInt] = ACTIONS(307),
    [anon_sym_toPath] = ACTIONS(307),
    [anon_sym_toDt] = ACTIONS(307),
    [anon_sym_toGrid] = ACTIONS(307),
    [anon_sym_toCsv] = ACTIONS(307),
    [anon_sym_toCsvCell] = ACTIONS(307),
    [anon_sym_exit] = ACTIONS(307),
    [anon_sym_prompt] = ACTIONS(307),
    [anon_sym_stdin] = ACTIONS(307),
    [anon_sym_COLON_COLON] = ACTIONS(305),
    [anon_sym_foldl] = ACTIONS(307),
    [anon_sym_map] = ACTIONS(307),
    [anon_sym_each] = ACTIONS(307),
    [anon_sym_eachWhile] = ACTIONS(307),
    [anon_sym_filter] = ACTIONS(307),
    [anon_sym_append] = ACTIONS(307),
    [anon_sym_extend] = ACTIONS(307),
    [anon_sym_concat] = ACTIONS(307),
    [anon_sym_reverse] = ACTIONS(307),
    [anon_sym_sort] = ACTIONS(307),
    [anon_sym_sortV] = ACTIONS(307),
    [anon_sym_sortBy] = ACTIONS(307),
    [anon_sym_sortByCmp] = ACTIONS(307),
    [anon_sym_uniq] = ACTIONS(307),
    [anon_sym_zip] = ACTIONS(307),
    [anon_sym_enumerate] = ACTIONS(307),
    [anon_sym_enumerateN] = ACTIONS(307),
    [anon_sym_chunk] = ACTIONS(307),
    [anon_sym_pop] = ACTIONS(307),
    [anon_sym_take] = ACTIONS(307),
    [anon_sym_takeWhile] = ACTIONS(307),
    [anon_sym_skip] = ACTIONS(307),
    [anon_sym_dropWhile] = ACTIONS(307),
    [anon_sym_nth] = ACTIONS(307),
    [anon_sym_insert] = ACTIONS(307),
    [anon_sym_setAt] = ACTIONS(307),
    [anon_sym_del] = ACTIONS(307),
    [anon_sym_sum] = ACTIONS(307),
    [anon_sym_max] = ACTIONS(307),
    [anon_sym_max2] = ACTIONS(307),
    [anon_sym_min] = ACTIONS(307),
    [anon_sym_min2] = ACTIONS(307),
    [anon_sym_abs] = ACTIONS(307),
    [anon_sym_inc] = ACTIONS(307),
    [anon_sym_mod] = ACTIONS(307),
    [anon_sym_floor] = ACTIONS(307),
    [anon_sym_ceil] = ACTIONS(307),
    [anon_sym_round] = ACTIONS(307),
    [anon_sym_lines] = ACTIONS(307),
    [anon_sym_unlines] = ACTIONS(307),
    [anon_sym_unlinesCrLf] = ACTIONS(307),
    [anon_sym_split] = ACTIONS(307),
    [anon_sym_wsplit] = ACTIONS(307),
    [anon_sym_tsplit] = ACTIONS(307),
    [anon_sym_join] = ACTIONS(307),
    [anon_sym_trim] = ACTIONS(307),
    [anon_sym_trimStart] = ACTIONS(307),
    [anon_sym_trimEnd] = ACTIONS(307),
    [anon_sym_startsWith] = ACTIONS(307),
    [anon_sym_endsWith] = ACTIONS(307),
    [anon_sym_lower] = ACTIONS(307),
    [anon_sym_upper] = ACTIONS(307),
    [anon_sym_title] = ACTIONS(307),
    [anon_sym_leftPad] = ACTIONS(307),
    [anon_sym_findReplace] = ACTIONS(307),
    [anon_sym_in] = ACTIONS(307),
    [anon_sym_index] = ACTIONS(307),
    [anon_sym_lastIndexOf] = ACTIONS(307),
    [anon_sym_countSubStr] = ACTIONS(307),
    [anon_sym_parseJson] = ACTIONS(307),
    [anon_sym_parseCsv] = ACTIONS(307),
    [anon_sym_parseHtml] = ACTIONS(307),
    [anon_sym_parseExcel] = ACTIONS(307),
    [anon_sym_readFile] = ACTIONS(307),
    [anon_sym_readFileBytes] = ACTIONS(307),
    [anon_sym_readTsvFile] = ACTIONS(307),
    [anon_sym_writeFile] = ACTIONS(307),
    [anon_sym_appendFile] = ACTIONS(307),
    [anon_sym_fileExists] = ACTIONS(307),
    [anon_sym_isDir] = ACTIONS(307),
    [anon_sym_isFile] = ACTIONS(307),
    [anon_sym_fileSize] = ACTIONS(307),
    [anon_sym_cp] = ACTIONS(307),
    [anon_sym_mv] = ACTIONS(307),
    [anon_sym_rm] = ACTIONS(307),
    [anon_sym_rmf] = ACTIONS(307),
    [anon_sym_mkdir] = ACTIONS(307),
    [anon_sym_mkdirp] = ACTIONS(307),
    [anon_sym_cd] = ACTIONS(307),
    [anon_sym_pwd] = ACTIONS(307),
    [anon_sym_tempFile] = ACTIONS(307),
    [anon_sym_tempFileExt] = ACTIONS(307),
    [anon_sym_tempDir] = ACTIONS(307),
    [anon_sym_lsDir] = ACTIONS(307),
    [anon_sym_files] = ACTIONS(307),
    [anon_sym_dirs] = ACTIONS(307),
    [anon_sym_absPath] = ACTIONS(307),
    [anon_sym_dirname] = ACTIONS(307),
    [anon_sym_basename] = ACTIONS(307),
    [anon_sym_ext] = ACTIONS(307),
    [anon_sym_stem] = ACTIONS(307),
    [anon_sym_isCmd] = ACTIONS(307),
    [anon_sym_hardLink] = ACTIONS(307),
    [anon_sym_sha256sum] = ACTIONS(307),
    [anon_sym_md5] = ACTIONS(307),
    [anon_sym_now] = ACTIONS(307),
    [anon_sym_date] = ACTIONS(307),
    [anon_sym_year] = ACTIONS(307),
    [anon_sym_month] = ACTIONS(307),
    [anon_sym_day] = ACTIONS(307),
    [anon_sym_hour] = ACTIONS(307),
    [anon_sym_minute] = ACTIONS(307),
    [anon_sym_dateFmt] = ACTIONS(307),
    [anon_sym_isoDateFmt] = ACTIONS(307),
    [anon_sym_isoDateTimeFmt] = ACTIONS(307),
    [anon_sym_isWeekend] = ACTIONS(307),
    [anon_sym_isWeekday] = ACTIONS(307),
    [anon_sym_dow] = ACTIONS(307),
    [anon_sym_addDays] = ACTIONS(307),
    [anon_sym_toUnixTime] = ACTIONS(307),
    [anon_sym_toUnixTimeMilli] = ACTIONS(307),
    [anon_sym_toUnixTimeMicro] = ACTIONS(307),
    [anon_sym_toUnixTimeNano] = ACTIONS(307),
    [anon_sym_fromUnixTime] = ACTIONS(307),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(307),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(307),
    [anon_sym_fromUnixTimeNano] = ACTIONS(307),
    [anon_sym_toOleDate] = ACTIONS(307),
    [anon_sym_fromOleDate] = ACTIONS(307),
    [anon_sym_utcToCst] = ACTIONS(307),
    [anon_sym_cstToUtc] = ACTIONS(307),
    [anon_sym_reMatch] = ACTIONS(307),
    [anon_sym_reFindAll] = ACTIONS(307),
    [anon_sym_reFindAllIndex] = ACTIONS(307),
    [anon_sym_reReplace] = ACTIONS(307),
    [anon_sym_reSplit] = ACTIONS(307),
    [anon_sym_just] = ACTIONS(307),
    [anon_sym_none] = ACTIONS(307),
    [anon_sym_isNone] = ACTIONS(307),
    [anon_sym_maybe] = ACTIONS(307),
    [anon_sym_bind] = ACTIONS(307),
    [anon_sym_psub] = ACTIONS(307),
    [anon_sym_typeof] = ACTIONS(307),
    [anon_sym_runtime] = ACTIONS(307),
    [anon_sym_hostname] = ACTIONS(307),
    [anon_sym_httpGet] = ACTIONS(307),
    [anon_sym_httpPost] = ACTIONS(307),
    [anon_sym_urlEncode] = ACTIONS(307),
    [anon_sym_base64encode] = ACTIONS(307),
    [anon_sym_base64decode] = ACTIONS(307),
    [anon_sym_utf8Str] = ACTIONS(307),
    [anon_sym_utf8Bytes] = ACTIONS(307),
    [anon_sym_get] = ACTIONS(307),
    [anon_sym_getDef] = ACTIONS(307),
    [anon_sym_set] = ACTIONS(307),
    [anon_sym_setd] = ACTIONS(307),
    [anon_sym_keys] = ACTIONS(307),
    [anon_sym_values] = ACTIONS(307),
    [anon_sym_keyValues] = ACTIONS(307),
    [anon_sym_all] = ACTIONS(307),
    [anon_sym_any] = ACTIONS(307),
    [anon_sym_cartesian] = ACTIONS(307),
    [anon_sym_groupBy] = ACTIONS(307),
    [anon_sym_listToDict] = ACTIONS(307),
    [anon_sym_repeat] = ACTIONS(307),
    [anon_sym_seq] = ACTIONS(307),
    [anon_sym_tab] = ACTIONS(307),
    [anon_sym_select] = ACTIONS(307),
    [anon_sym_exclude] = ACTIONS(307),
    [anon_sym_derive] = ACTIONS(307),
    [anon_sym_updateCol] = ACTIONS(307),
    [anon_sym_gridValues] = ACTIONS(307),
    [anon_sym_leftJoin] = ACTIONS(307),
    [anon_sym_outerJoin] = ACTIONS(307),
    [anon_sym_linearSearch] = ACTIONS(307),
    [anon_sym_linearSearchIndex] = ACTIONS(307),
    [anon_sym_binPaths] = ACTIONS(307),
    [anon_sym_wt] = ACTIONS(307),
    [anon_sym_tt] = ACTIONS(307),
    [anon_sym_ttFile] = ACTIONS(307),
    [anon_sym_uw] = ACTIONS(307),
    [anon_sym_tuw] = ACTIONS(307),
    [anon_sym_strCmp] = ACTIONS(307),
    [anon_sym_floatCmp] = ACTIONS(307),
    [anon_sym_versionSortCmp] = ACTIONS(307),
    [anon_sym_id] = ACTIONS(307),
    [anon_sym_2id] = ACTIONS(307),
    [anon_sym_3id] = ACTIONS(307),
    [anon_sym_2unpack] = ACTIONS(307),
    [anon_sym_2apply] = ACTIONS(307),
    [anon_sym_2each] = ACTIONS(307),
    [anon_sym_2tuple] = ACTIONS(307),
    [anon_sym_DOTs] = ACTIONS(307),
    [anon_sym_DOTb] = ACTIONS(307),
    [anon_sym_DOTdef] = ACTIONS(307),
    [anon_sym_DOTenv] = ACTIONS(307),
    [sym_string] = ACTIONS(305),
    [sym_format_string] = ACTIONS(305),
    [sym_single_quoted_string] = ACTIONS(305),
    [sym_path] = ACTIONS(305),
    [sym_datetime] = ACTIONS(305),
    [sym_float] = ACTIONS(305),
    [sym_integer] = ACTIONS(307),
    [sym_env_store] = ACTIONS(305),
    [sym_env_check] = ACTIONS(305),
    [sym_env_retrieve] = ACTIONS(307),
    [sym_positional] = ACTIONS(305),
    [sym_var_retrieve] = ACTIONS(305),
    [sym_var_store] = ACTIONS(305),
    [sym_slice_indexer] = ACTIONS(305),
    [sym_indexer] = ACTIONS(305),
    [sym_end_indexer] = ACTIONS(307),
    [sym_start_indexer] = ACTIONS(307),
    [sym_match_arm_dup] = ACTIONS(305),
    [sym_prefix_quote] = ACTIONS(307),
    [anon_sym_GT] = ACTIONS(307),
    [anon_sym_GT_GT] = ACTIONS(305),
    [anon_sym_2_GT] = ACTIONS(307),
    [anon_sym_2_GT_GT] = ACTIONS(307),
    [anon_sym_AMP_GT] = ACTIONS(307),
    [anon_sym_AMP_GT_GT] = ACTIONS(305),
    [anon_sym_LT] = ACTIONS(307),
    [anon_sym_LT_GT] = ACTIONS(305),
    [anon_sym_STAR] = ACTIONS(307),
    [anon_sym_STARb] = ACTIONS(305),
    [anon_sym_CARET] = ACTIONS(307),
    [anon_sym_CARETb] = ACTIONS(305),
    [anon_sym_SEMI] = ACTIONS(305),
    [anon_sym_BANG] = ACTIONS(307),
    [anon_sym_QMARK] = ACTIONS(305),
    [anon_sym_BANG_EQ] = ACTIONS(305),
    [anon_sym_LT_EQ] = ACTIONS(305),
    [anon_sym_GT_EQ] = ACTIONS(305),
    [anon_sym_AMP] = ACTIONS(307),
    [anon_sym_PIPE] = ACTIONS(305),
    [anon_sym_COMMA] = ACTIONS(305),
    [anon_sym_COLON] = ACTIONS(307),
  },
  [31] = {
    [ts_builtin_sym_end] = ACTIONS(309),
    [sym_identifier] = ACTIONS(311),
    [anon_sym_LBRACK] = ACTIONS(311),
    [anon_sym_RBRACK] = ACTIONS(309),
    [anon_sym_LPAREN] = ACTIONS(309),
    [anon_sym_RPAREN] = ACTIONS(309),
    [anon_sym_LBRACE] = ACTIONS(309),
    [anon_sym_RBRACE] = ACTIONS(309),
    [anon_sym_LBRACK_PIPE] = ACTIONS(309),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(311),
    [anon_sym_false] = ACTIONS(311),
    [anon_sym_def] = ACTIONS(311),
    [anon_sym_end] = ACTIONS(311),
    [anon_sym_if] = ACTIONS(311),
    [anon_sym_iff] = ACTIONS(311),
    [anon_sym_else] = ACTIONS(311),
    [anon_sym_else_STAR] = ACTIONS(309),
    [anon_sym_STARif] = ACTIONS(309),
    [anon_sym_loop] = ACTIONS(311),
    [anon_sym_match] = ACTIONS(311),
    [anon_sym_break] = ACTIONS(311),
    [anon_sym_continue] = ACTIONS(311),
    [anon_sym_soe] = ACTIONS(311),
    [anon_sym_not] = ACTIONS(311),
    [anon_sym_and] = ACTIONS(311),
    [anon_sym_or] = ACTIONS(311),
    [anon_sym_read] = ACTIONS(311),
    [anon_sym_str] = ACTIONS(311),
    [anon_sym_as] = ACTIONS(311),
    [anon_sym_type] = ACTIONS(311),
    [anon_sym_try] = ACTIONS(311),
    [anon_sym_fail] = ACTIONS(311),
    [anon_sym_pure] = ACTIONS(311),
    [anon_sym_VER] = ACTIONS(311),
    [anon_sym_x] = ACTIONS(311),
    [anon_sym_int] = ACTIONS(311),
    [anon_sym_float] = ACTIONS(311),
    [anon_sym_bool] = ACTIONS(311),
    [anon_sym_dup] = ACTIONS(311),
    [anon_sym_swap] = ACTIONS(311),
    [anon_sym_drop] = ACTIONS(311),
    [anon_sym_over] = ACTIONS(311),
    [anon_sym_pick] = ACTIONS(311),
    [anon_sym_rot] = ACTIONS(311),
    [anon_sym_DASHrot] = ACTIONS(311),
    [anon_sym_nip] = ACTIONS(311),
    [anon_sym_w] = ACTIONS(311),
    [anon_sym_wl] = ACTIONS(311),
    [anon_sym_we] = ACTIONS(311),
    [anon_sym_wle] = ACTIONS(311),
    [anon_sym_len] = ACTIONS(311),
    [anon_sym_args] = ACTIONS(311),
    [anon_sym_glob] = ACTIONS(311),
    [anon_sym_toFloat] = ACTIONS(311),
    [anon_sym_toInt] = ACTIONS(311),
    [anon_sym_toPath] = ACTIONS(311),
    [anon_sym_toDt] = ACTIONS(311),
    [anon_sym_toGrid] = ACTIONS(311),
    [anon_sym_toCsv] = ACTIONS(311),
    [anon_sym_toCsvCell] = ACTIONS(311),
    [anon_sym_exit] = ACTIONS(311),
    [anon_sym_prompt] = ACTIONS(311),
    [anon_sym_stdin] = ACTIONS(311),
    [anon_sym_COLON_COLON] = ACTIONS(309),
    [anon_sym_foldl] = ACTIONS(311),
    [anon_sym_map] = ACTIONS(311),
    [anon_sym_each] = ACTIONS(311),
    [anon_sym_eachWhile] = ACTIONS(311),
    [anon_sym_filter] = ACTIONS(311),
    [anon_sym_append] = ACTIONS(311),
    [anon_sym_extend] = ACTIONS(311),
    [anon_sym_concat] = ACTIONS(311),
    [anon_sym_reverse] = ACTIONS(311),
    [anon_sym_sort] = ACTIONS(311),
    [anon_sym_sortV] = ACTIONS(311),
    [anon_sym_sortBy] = ACTIONS(311),
    [anon_sym_sortByCmp] = ACTIONS(311),
    [anon_sym_uniq] = ACTIONS(311),
    [anon_sym_zip] = ACTIONS(311),
    [anon_sym_enumerate] = ACTIONS(311),
    [anon_sym_enumerateN] = ACTIONS(311),
    [anon_sym_chunk] = ACTIONS(311),
    [anon_sym_pop] = ACTIONS(311),
    [anon_sym_take] = ACTIONS(311),
    [anon_sym_takeWhile] = ACTIONS(311),
    [anon_sym_skip] = ACTIONS(311),
    [anon_sym_dropWhile] = ACTIONS(311),
    [anon_sym_nth] = ACTIONS(311),
    [anon_sym_insert] = ACTIONS(311),
    [anon_sym_setAt] = ACTIONS(311),
    [anon_sym_del] = ACTIONS(311),
    [anon_sym_sum] = ACTIONS(311),
    [anon_sym_max] = ACTIONS(311),
    [anon_sym_max2] = ACTIONS(311),
    [anon_sym_min] = ACTIONS(311),
    [anon_sym_min2] = ACTIONS(311),
    [anon_sym_abs] = ACTIONS(311),
    [anon_sym_inc] = ACTIONS(311),
    [anon_sym_mod] = ACTIONS(311),
    [anon_sym_floor] = ACTIONS(311),
    [anon_sym_ceil] = ACTIONS(311),
    [anon_sym_round] = ACTIONS(311),
    [anon_sym_lines] = ACTIONS(311),
    [anon_sym_unlines] = ACTIONS(311),
    [anon_sym_unlinesCrLf] = ACTIONS(311),
    [anon_sym_split] = ACTIONS(311),
    [anon_sym_wsplit] = ACTIONS(311),
    [anon_sym_tsplit] = ACTIONS(311),
    [anon_sym_join] = ACTIONS(311),
    [anon_sym_trim] = ACTIONS(311),
    [anon_sym_trimStart] = ACTIONS(311),
    [anon_sym_trimEnd] = ACTIONS(311),
    [anon_sym_startsWith] = ACTIONS(311),
    [anon_sym_endsWith] = ACTIONS(311),
    [anon_sym_lower] = ACTIONS(311),
    [anon_sym_upper] = ACTIONS(311),
    [anon_sym_title] = ACTIONS(311),
    [anon_sym_leftPad] = ACTIONS(311),
    [anon_sym_findReplace] = ACTIONS(311),
    [anon_sym_in] = ACTIONS(311),
    [anon_sym_index] = ACTIONS(311),
    [anon_sym_lastIndexOf] = ACTIONS(311),
    [anon_sym_countSubStr] = ACTIONS(311),
    [anon_sym_parseJson] = ACTIONS(311),
    [anon_sym_parseCsv] = ACTIONS(311),
    [anon_sym_parseHtml] = ACTIONS(311),
    [anon_sym_parseExcel] = ACTIONS(311),
    [anon_sym_readFile] = ACTIONS(311),
    [anon_sym_readFileBytes] = ACTIONS(311),
    [anon_sym_readTsvFile] = ACTIONS(311),
    [anon_sym_writeFile] = ACTIONS(311),
    [anon_sym_appendFile] = ACTIONS(311),
    [anon_sym_fileExists] = ACTIONS(311),
    [anon_sym_isDir] = ACTIONS(311),
    [anon_sym_isFile] = ACTIONS(311),
    [anon_sym_fileSize] = ACTIONS(311),
    [anon_sym_cp] = ACTIONS(311),
    [anon_sym_mv] = ACTIONS(311),
    [anon_sym_rm] = ACTIONS(311),
    [anon_sym_rmf] = ACTIONS(311),
    [anon_sym_mkdir] = ACTIONS(311),
    [anon_sym_mkdirp] = ACTIONS(311),
    [anon_sym_cd] = ACTIONS(311),
    [anon_sym_pwd] = ACTIONS(311),
    [anon_sym_tempFile] = ACTIONS(311),
    [anon_sym_tempFileExt] = ACTIONS(311),
    [anon_sym_tempDir] = ACTIONS(311),
    [anon_sym_lsDir] = ACTIONS(311),
    [anon_sym_files] = ACTIONS(311),
    [anon_sym_dirs] = ACTIONS(311),
    [anon_sym_absPath] = ACTIONS(311),
    [anon_sym_dirname] = ACTIONS(311),
    [anon_sym_basename] = ACTIONS(311),
    [anon_sym_ext] = ACTIONS(311),
    [anon_sym_stem] = ACTIONS(311),
    [anon_sym_isCmd] = ACTIONS(311),
    [anon_sym_hardLink] = ACTIONS(311),
    [anon_sym_sha256sum] = ACTIONS(311),
    [anon_sym_md5] = ACTIONS(311),
    [anon_sym_now] = ACTIONS(311),
    [anon_sym_date] = ACTIONS(311),
    [anon_sym_year] = ACTIONS(311),
    [anon_sym_month] = ACTIONS(311),
    [anon_sym_day] = ACTIONS(311),
    [anon_sym_hour] = ACTIONS(311),
    [anon_sym_minute] = ACTIONS(311),
    [anon_sym_dateFmt] = ACTIONS(311),
    [anon_sym_isoDateFmt] = ACTIONS(311),
    [anon_sym_isoDateTimeFmt] = ACTIONS(311),
    [anon_sym_isWeekend] = ACTIONS(311),
    [anon_sym_isWeekday] = ACTIONS(311),
    [anon_sym_dow] = ACTIONS(311),
    [anon_sym_addDays] = ACTIONS(311),
    [anon_sym_toUnixTime] = ACTIONS(311),
    [anon_sym_toUnixTimeMilli] = ACTIONS(311),
    [anon_sym_toUnixTimeMicro] = ACTIONS(311),
    [anon_sym_toUnixTimeNano] = ACTIONS(311),
    [anon_sym_fromUnixTime] = ACTIONS(311),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(311),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(311),
    [anon_sym_fromUnixTimeNano] = ACTIONS(311),
    [anon_sym_toOleDate] = ACTIONS(311),
    [anon_sym_fromOleDate] = ACTIONS(311),
    [anon_sym_utcToCst] = ACTIONS(311),
    [anon_sym_cstToUtc] = ACTIONS(311),
    [anon_sym_reMatch] = ACTIONS(311),
    [anon_sym_reFindAll] = ACTIONS(311),
    [anon_sym_reFindAllIndex] = ACTIONS(311),
    [anon_sym_reReplace] = ACTIONS(311),
    [anon_sym_reSplit] = ACTIONS(311),
    [anon_sym_just] = ACTIONS(311),
    [anon_sym_none] = ACTIONS(311),
    [anon_sym_isNone] = ACTIONS(311),
    [anon_sym_maybe] = ACTIONS(311),
    [anon_sym_bind] = ACTIONS(311),
    [anon_sym_psub] = ACTIONS(311),
    [anon_sym_typeof] = ACTIONS(311),
    [anon_sym_runtime] = ACTIONS(311),
    [anon_sym_hostname] = ACTIONS(311),
    [anon_sym_httpGet] = ACTIONS(311),
    [anon_sym_httpPost] = ACTIONS(311),
    [anon_sym_urlEncode] = ACTIONS(311),
    [anon_sym_base64encode] = ACTIONS(311),
    [anon_sym_base64decode] = ACTIONS(311),
    [anon_sym_utf8Str] = ACTIONS(311),
    [anon_sym_utf8Bytes] = ACTIONS(311),
    [anon_sym_get] = ACTIONS(311),
    [anon_sym_getDef] = ACTIONS(311),
    [anon_sym_set] = ACTIONS(311),
    [anon_sym_setd] = ACTIONS(311),
    [anon_sym_keys] = ACTIONS(311),
    [anon_sym_values] = ACTIONS(311),
    [anon_sym_keyValues] = ACTIONS(311),
    [anon_sym_all] = ACTIONS(311),
    [anon_sym_any] = ACTIONS(311),
    [anon_sym_cartesian] = ACTIONS(311),
    [anon_sym_groupBy] = ACTIONS(311),
    [anon_sym_listToDict] = ACTIONS(311),
    [anon_sym_repeat] = ACTIONS(311),
    [anon_sym_seq] = ACTIONS(311),
    [anon_sym_tab] = ACTIONS(311),
    [anon_sym_select] = ACTIONS(311),
    [anon_sym_exclude] = ACTIONS(311),
    [anon_sym_derive] = ACTIONS(311),
    [anon_sym_updateCol] = ACTIONS(311),
    [anon_sym_gridValues] = ACTIONS(311),
    [anon_sym_leftJoin] = ACTIONS(311),
    [anon_sym_outerJoin] = ACTIONS(311),
    [anon_sym_linearSearch] = ACTIONS(311),
    [anon_sym_linearSearchIndex] = ACTIONS(311),
    [anon_sym_binPaths] = ACTIONS(311),
    [anon_sym_wt] = ACTIONS(311),
    [anon_sym_tt] = ACTIONS(311),
    [anon_sym_ttFile] = ACTIONS(311),
    [anon_sym_uw] = ACTIONS(311),
    [anon_sym_tuw] = ACTIONS(311),
    [anon_sym_strCmp] = ACTIONS(311),
    [anon_sym_floatCmp] = ACTIONS(311),
    [anon_sym_versionSortCmp] = ACTIONS(311),
    [anon_sym_id] = ACTIONS(311),
    [anon_sym_2id] = ACTIONS(311),
    [anon_sym_3id] = ACTIONS(311),
    [anon_sym_2unpack] = ACTIONS(311),
    [anon_sym_2apply] = ACTIONS(311),
    [anon_sym_2each] = ACTIONS(311),
    [anon_sym_2tuple] = ACTIONS(311),
    [anon_sym_DOTs] = ACTIONS(311),
    [anon_sym_DOTb] = ACTIONS(311),
    [anon_sym_DOTdef] = ACTIONS(311),
    [anon_sym_DOTenv] = ACTIONS(311),
    [sym_string] = ACTIONS(309),
    [sym_format_string] = ACTIONS(309),
    [sym_single_quoted_string] = ACTIONS(309),
    [sym_path] = ACTIONS(309),
    [sym_datetime] = ACTIONS(309),
    [sym_float] = ACTIONS(309),
    [sym_integer] = ACTIONS(311),
    [sym_env_store] = ACTIONS(309),
    [sym_env_check] = ACTIONS(309),
    [sym_env_retrieve] = ACTIONS(311),
    [sym_positional] = ACTIONS(309),
    [sym_var_retrieve] = ACTIONS(309),
    [sym_var_store] = ACTIONS(309),
    [sym_slice_indexer] = ACTIONS(309),
    [sym_indexer] = ACTIONS(309),
    [sym_end_indexer] = ACTIONS(311),
    [sym_start_indexer] = ACTIONS(311),
    [sym_match_arm_dup] = ACTIONS(309),
    [sym_prefix_quote] = ACTIONS(311),
    [anon_sym_GT] = ACTIONS(311),
    [anon_sym_GT_GT] = ACTIONS(309),
    [anon_sym_2_GT] = ACTIONS(311),
    [anon_sym_2_GT_GT] = ACTIONS(311),
    [anon_sym_AMP_GT] = ACTIONS(311),
    [anon_sym_AMP_GT_GT] = ACTIONS(309),
    [anon_sym_LT] = ACTIONS(311),
    [anon_sym_LT_GT] = ACTIONS(309),
    [anon_sym_STAR] = ACTIONS(311),
    [anon_sym_STARb] = ACTIONS(309),
    [anon_sym_CARET] = ACTIONS(311),
    [anon_sym_CARETb] = ACTIONS(309),
    [anon_sym_SEMI] = ACTIONS(309),
    [anon_sym_BANG] = ACTIONS(311),
    [anon_sym_QMARK] = ACTIONS(309),
    [anon_sym_BANG_EQ] = ACTIONS(309),
    [anon_sym_LT_EQ] = ACTIONS(309),
    [anon_sym_GT_EQ] = ACTIONS(309),
    [anon_sym_AMP] = ACTIONS(311),
    [anon_sym_PIPE] = ACTIONS(309),
    [anon_sym_COMMA] = ACTIONS(309),
    [anon_sym_COLON] = ACTIONS(311),
  },
  [32] = {
    [ts_builtin_sym_end] = ACTIONS(313),
    [sym_identifier] = ACTIONS(315),
    [anon_sym_LBRACK] = ACTIONS(315),
    [anon_sym_RBRACK] = ACTIONS(313),
    [anon_sym_LPAREN] = ACTIONS(313),
    [anon_sym_RPAREN] = ACTIONS(313),
    [anon_sym_LBRACE] = ACTIONS(313),
    [anon_sym_RBRACE] = ACTIONS(313),
    [anon_sym_LBRACK_PIPE] = ACTIONS(313),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(315),
    [anon_sym_false] = ACTIONS(315),
    [anon_sym_def] = ACTIONS(315),
    [anon_sym_end] = ACTIONS(315),
    [anon_sym_if] = ACTIONS(315),
    [anon_sym_iff] = ACTIONS(315),
    [anon_sym_else] = ACTIONS(315),
    [anon_sym_else_STAR] = ACTIONS(313),
    [anon_sym_STARif] = ACTIONS(313),
    [anon_sym_loop] = ACTIONS(315),
    [anon_sym_match] = ACTIONS(315),
    [anon_sym_break] = ACTIONS(315),
    [anon_sym_continue] = ACTIONS(315),
    [anon_sym_soe] = ACTIONS(315),
    [anon_sym_not] = ACTIONS(315),
    [anon_sym_and] = ACTIONS(315),
    [anon_sym_or] = ACTIONS(315),
    [anon_sym_read] = ACTIONS(315),
    [anon_sym_str] = ACTIONS(315),
    [anon_sym_as] = ACTIONS(315),
    [anon_sym_type] = ACTIONS(315),
    [anon_sym_try] = ACTIONS(315),
    [anon_sym_fail] = ACTIONS(315),
    [anon_sym_pure] = ACTIONS(315),
    [anon_sym_VER] = ACTIONS(315),
    [anon_sym_x] = ACTIONS(315),
    [anon_sym_int] = ACTIONS(315),
    [anon_sym_float] = ACTIONS(315),
    [anon_sym_bool] = ACTIONS(315),
    [anon_sym_dup] = ACTIONS(315),
    [anon_sym_swap] = ACTIONS(315),
    [anon_sym_drop] = ACTIONS(315),
    [anon_sym_over] = ACTIONS(315),
    [anon_sym_pick] = ACTIONS(315),
    [anon_sym_rot] = ACTIONS(315),
    [anon_sym_DASHrot] = ACTIONS(315),
    [anon_sym_nip] = ACTIONS(315),
    [anon_sym_w] = ACTIONS(315),
    [anon_sym_wl] = ACTIONS(315),
    [anon_sym_we] = ACTIONS(315),
    [anon_sym_wle] = ACTIONS(315),
    [anon_sym_len] = ACTIONS(315),
    [anon_sym_args] = ACTIONS(315),
    [anon_sym_glob] = ACTIONS(315),
    [anon_sym_toFloat] = ACTIONS(315),
    [anon_sym_toInt] = ACTIONS(315),
    [anon_sym_toPath] = ACTIONS(315),
    [anon_sym_toDt] = ACTIONS(315),
    [anon_sym_toGrid] = ACTIONS(315),
    [anon_sym_toCsv] = ACTIONS(315),
    [anon_sym_toCsvCell] = ACTIONS(315),
    [anon_sym_exit] = ACTIONS(315),
    [anon_sym_prompt] = ACTIONS(315),
    [anon_sym_stdin] = ACTIONS(315),
    [anon_sym_COLON_COLON] = ACTIONS(313),
    [anon_sym_foldl] = ACTIONS(315),
    [anon_sym_map] = ACTIONS(315),
    [anon_sym_each] = ACTIONS(315),
    [anon_sym_eachWhile] = ACTIONS(315),
    [anon_sym_filter] = ACTIONS(315),
    [anon_sym_append] = ACTIONS(315),
    [anon_sym_extend] = ACTIONS(315),
    [anon_sym_concat] = ACTIONS(315),
    [anon_sym_reverse] = ACTIONS(315),
    [anon_sym_sort] = ACTIONS(315),
    [anon_sym_sortV] = ACTIONS(315),
    [anon_sym_sortBy] = ACTIONS(315),
    [anon_sym_sortByCmp] = ACTIONS(315),
    [anon_sym_uniq] = ACTIONS(315),
    [anon_sym_zip] = ACTIONS(315),
    [anon_sym_enumerate] = ACTIONS(315),
    [anon_sym_enumerateN] = ACTIONS(315),
    [anon_sym_chunk] = ACTIONS(315),
    [anon_sym_pop] = ACTIONS(315),
    [anon_sym_take] = ACTIONS(315),
    [anon_sym_takeWhile] = ACTIONS(315),
    [anon_sym_skip] = ACTIONS(315),
    [anon_sym_dropWhile] = ACTIONS(315),
    [anon_sym_nth] = ACTIONS(315),
    [anon_sym_insert] = ACTIONS(315),
    [anon_sym_setAt] = ACTIONS(315),
    [anon_sym_del] = ACTIONS(315),
    [anon_sym_sum] = ACTIONS(315),
    [anon_sym_max] = ACTIONS(315),
    [anon_sym_max2] = ACTIONS(315),
    [anon_sym_min] = ACTIONS(315),
    [anon_sym_min2] = ACTIONS(315),
    [anon_sym_abs] = ACTIONS(315),
    [anon_sym_inc] = ACTIONS(315),
    [anon_sym_mod] = ACTIONS(315),
    [anon_sym_floor] = ACTIONS(315),
    [anon_sym_ceil] = ACTIONS(315),
    [anon_sym_round] = ACTIONS(315),
    [anon_sym_lines] = ACTIONS(315),
    [anon_sym_unlines] = ACTIONS(315),
    [anon_sym_unlinesCrLf] = ACTIONS(315),
    [anon_sym_split] = ACTIONS(315),
    [anon_sym_wsplit] = ACTIONS(315),
    [anon_sym_tsplit] = ACTIONS(315),
    [anon_sym_join] = ACTIONS(315),
    [anon_sym_trim] = ACTIONS(315),
    [anon_sym_trimStart] = ACTIONS(315),
    [anon_sym_trimEnd] = ACTIONS(315),
    [anon_sym_startsWith] = ACTIONS(315),
    [anon_sym_endsWith] = ACTIONS(315),
    [anon_sym_lower] = ACTIONS(315),
    [anon_sym_upper] = ACTIONS(315),
    [anon_sym_title] = ACTIONS(315),
    [anon_sym_leftPad] = ACTIONS(315),
    [anon_sym_findReplace] = ACTIONS(315),
    [anon_sym_in] = ACTIONS(315),
    [anon_sym_index] = ACTIONS(315),
    [anon_sym_lastIndexOf] = ACTIONS(315),
    [anon_sym_countSubStr] = ACTIONS(315),
    [anon_sym_parseJson] = ACTIONS(315),
    [anon_sym_parseCsv] = ACTIONS(315),
    [anon_sym_parseHtml] = ACTIONS(315),
    [anon_sym_parseExcel] = ACTIONS(315),
    [anon_sym_readFile] = ACTIONS(315),
    [anon_sym_readFileBytes] = ACTIONS(315),
    [anon_sym_readTsvFile] = ACTIONS(315),
    [anon_sym_writeFile] = ACTIONS(315),
    [anon_sym_appendFile] = ACTIONS(315),
    [anon_sym_fileExists] = ACTIONS(315),
    [anon_sym_isDir] = ACTIONS(315),
    [anon_sym_isFile] = ACTIONS(315),
    [anon_sym_fileSize] = ACTIONS(315),
    [anon_sym_cp] = ACTIONS(315),
    [anon_sym_mv] = ACTIONS(315),
    [anon_sym_rm] = ACTIONS(315),
    [anon_sym_rmf] = ACTIONS(315),
    [anon_sym_mkdir] = ACTIONS(315),
    [anon_sym_mkdirp] = ACTIONS(315),
    [anon_sym_cd] = ACTIONS(315),
    [anon_sym_pwd] = ACTIONS(315),
    [anon_sym_tempFile] = ACTIONS(315),
    [anon_sym_tempFileExt] = ACTIONS(315),
    [anon_sym_tempDir] = ACTIONS(315),
    [anon_sym_lsDir] = ACTIONS(315),
    [anon_sym_files] = ACTIONS(315),
    [anon_sym_dirs] = ACTIONS(315),
    [anon_sym_absPath] = ACTIONS(315),
    [anon_sym_dirname] = ACTIONS(315),
    [anon_sym_basename] = ACTIONS(315),
    [anon_sym_ext] = ACTIONS(315),
    [anon_sym_stem] = ACTIONS(315),
    [anon_sym_isCmd] = ACTIONS(315),
    [anon_sym_hardLink] = ACTIONS(315),
    [anon_sym_sha256sum] = ACTIONS(315),
    [anon_sym_md5] = ACTIONS(315),
    [anon_sym_now] = ACTIONS(315),
    [anon_sym_date] = ACTIONS(315),
    [anon_sym_year] = ACTIONS(315),
    [anon_sym_month] = ACTIONS(315),
    [anon_sym_day] = ACTIONS(315),
    [anon_sym_hour] = ACTIONS(315),
    [anon_sym_minute] = ACTIONS(315),
    [anon_sym_dateFmt] = ACTIONS(315),
    [anon_sym_isoDateFmt] = ACTIONS(315),
    [anon_sym_isoDateTimeFmt] = ACTIONS(315),
    [anon_sym_isWeekend] = ACTIONS(315),
    [anon_sym_isWeekday] = ACTIONS(315),
    [anon_sym_dow] = ACTIONS(315),
    [anon_sym_addDays] = ACTIONS(315),
    [anon_sym_toUnixTime] = ACTIONS(315),
    [anon_sym_toUnixTimeMilli] = ACTIONS(315),
    [anon_sym_toUnixTimeMicro] = ACTIONS(315),
    [anon_sym_toUnixTimeNano] = ACTIONS(315),
    [anon_sym_fromUnixTime] = ACTIONS(315),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(315),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(315),
    [anon_sym_fromUnixTimeNano] = ACTIONS(315),
    [anon_sym_toOleDate] = ACTIONS(315),
    [anon_sym_fromOleDate] = ACTIONS(315),
    [anon_sym_utcToCst] = ACTIONS(315),
    [anon_sym_cstToUtc] = ACTIONS(315),
    [anon_sym_reMatch] = ACTIONS(315),
    [anon_sym_reFindAll] = ACTIONS(315),
    [anon_sym_reFindAllIndex] = ACTIONS(315),
    [anon_sym_reReplace] = ACTIONS(315),
    [anon_sym_reSplit] = ACTIONS(315),
    [anon_sym_just] = ACTIONS(315),
    [anon_sym_none] = ACTIONS(315),
    [anon_sym_isNone] = ACTIONS(315),
    [anon_sym_maybe] = ACTIONS(315),
    [anon_sym_bind] = ACTIONS(315),
    [anon_sym_psub] = ACTIONS(315),
    [anon_sym_typeof] = ACTIONS(315),
    [anon_sym_runtime] = ACTIONS(315),
    [anon_sym_hostname] = ACTIONS(315),
    [anon_sym_httpGet] = ACTIONS(315),
    [anon_sym_httpPost] = ACTIONS(315),
    [anon_sym_urlEncode] = ACTIONS(315),
    [anon_sym_base64encode] = ACTIONS(315),
    [anon_sym_base64decode] = ACTIONS(315),
    [anon_sym_utf8Str] = ACTIONS(315),
    [anon_sym_utf8Bytes] = ACTIONS(315),
    [anon_sym_get] = ACTIONS(315),
    [anon_sym_getDef] = ACTIONS(315),
    [anon_sym_set] = ACTIONS(315),
    [anon_sym_setd] = ACTIONS(315),
    [anon_sym_keys] = ACTIONS(315),
    [anon_sym_values] = ACTIONS(315),
    [anon_sym_keyValues] = ACTIONS(315),
    [anon_sym_all] = ACTIONS(315),
    [anon_sym_any] = ACTIONS(315),
    [anon_sym_cartesian] = ACTIONS(315),
    [anon_sym_groupBy] = ACTIONS(315),
    [anon_sym_listToDict] = ACTIONS(315),
    [anon_sym_repeat] = ACTIONS(315),
    [anon_sym_seq] = ACTIONS(315),
    [anon_sym_tab] = ACTIONS(315),
    [anon_sym_select] = ACTIONS(315),
    [anon_sym_exclude] = ACTIONS(315),
    [anon_sym_derive] = ACTIONS(315),
    [anon_sym_updateCol] = ACTIONS(315),
    [anon_sym_gridValues] = ACTIONS(315),
    [anon_sym_leftJoin] = ACTIONS(315),
    [anon_sym_outerJoin] = ACTIONS(315),
    [anon_sym_linearSearch] = ACTIONS(315),
    [anon_sym_linearSearchIndex] = ACTIONS(315),
    [anon_sym_binPaths] = ACTIONS(315),
    [anon_sym_wt] = ACTIONS(315),
    [anon_sym_tt] = ACTIONS(315),
    [anon_sym_ttFile] = ACTIONS(315),
    [anon_sym_uw] = ACTIONS(315),
    [anon_sym_tuw] = ACTIONS(315),
    [anon_sym_strCmp] = ACTIONS(315),
    [anon_sym_floatCmp] = ACTIONS(315),
    [anon_sym_versionSortCmp] = ACTIONS(315),
    [anon_sym_id] = ACTIONS(315),
    [anon_sym_2id] = ACTIONS(315),
    [anon_sym_3id] = ACTIONS(315),
    [anon_sym_2unpack] = ACTIONS(315),
    [anon_sym_2apply] = ACTIONS(315),
    [anon_sym_2each] = ACTIONS(315),
    [anon_sym_2tuple] = ACTIONS(315),
    [anon_sym_DOTs] = ACTIONS(315),
    [anon_sym_DOTb] = ACTIONS(315),
    [anon_sym_DOTdef] = ACTIONS(315),
    [anon_sym_DOTenv] = ACTIONS(315),
    [sym_string] = ACTIONS(313),
    [sym_format_string] = ACTIONS(313),
    [sym_single_quoted_string] = ACTIONS(313),
    [sym_path] = ACTIONS(313),
    [sym_datetime] = ACTIONS(313),
    [sym_float] = ACTIONS(313),
    [sym_integer] = ACTIONS(315),
    [sym_env_store] = ACTIONS(313),
    [sym_env_check] = ACTIONS(313),
    [sym_env_retrieve] = ACTIONS(315),
    [sym_positional] = ACTIONS(313),
    [sym_var_retrieve] = ACTIONS(313),
    [sym_var_store] = ACTIONS(313),
    [sym_slice_indexer] = ACTIONS(313),
    [sym_indexer] = ACTIONS(313),
    [sym_end_indexer] = ACTIONS(315),
    [sym_start_indexer] = ACTIONS(315),
    [sym_match_arm_dup] = ACTIONS(313),
    [sym_prefix_quote] = ACTIONS(315),
    [anon_sym_GT] = ACTIONS(315),
    [anon_sym_GT_GT] = ACTIONS(313),
    [anon_sym_2_GT] = ACTIONS(315),
    [anon_sym_2_GT_GT] = ACTIONS(315),
    [anon_sym_AMP_GT] = ACTIONS(315),
    [anon_sym_AMP_GT_GT] = ACTIONS(313),
    [anon_sym_LT] = ACTIONS(315),
    [anon_sym_LT_GT] = ACTIONS(313),
    [anon_sym_STAR] = ACTIONS(315),
    [anon_sym_STARb] = ACTIONS(313),
    [anon_sym_CARET] = ACTIONS(315),
    [anon_sym_CARETb] = ACTIONS(313),
    [anon_sym_SEMI] = ACTIONS(313),
    [anon_sym_BANG] = ACTIONS(315),
    [anon_sym_QMARK] = ACTIONS(313),
    [anon_sym_BANG_EQ] = ACTIONS(313),
    [anon_sym_LT_EQ] = ACTIONS(313),
    [anon_sym_GT_EQ] = ACTIONS(313),
    [anon_sym_AMP] = ACTIONS(315),
    [anon_sym_PIPE] = ACTIONS(313),
    [anon_sym_COMMA] = ACTIONS(313),
    [anon_sym_COLON] = ACTIONS(315),
  },
  [33] = {
    [ts_builtin_sym_end] = ACTIONS(317),
    [sym_identifier] = ACTIONS(319),
    [anon_sym_LBRACK] = ACTIONS(319),
    [anon_sym_RBRACK] = ACTIONS(317),
    [anon_sym_LPAREN] = ACTIONS(317),
    [anon_sym_RPAREN] = ACTIONS(317),
    [anon_sym_LBRACE] = ACTIONS(317),
    [anon_sym_RBRACE] = ACTIONS(317),
    [anon_sym_LBRACK_PIPE] = ACTIONS(317),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(319),
    [anon_sym_false] = ACTIONS(319),
    [anon_sym_def] = ACTIONS(319),
    [anon_sym_end] = ACTIONS(319),
    [anon_sym_if] = ACTIONS(319),
    [anon_sym_iff] = ACTIONS(319),
    [anon_sym_else] = ACTIONS(319),
    [anon_sym_else_STAR] = ACTIONS(317),
    [anon_sym_STARif] = ACTIONS(317),
    [anon_sym_loop] = ACTIONS(319),
    [anon_sym_match] = ACTIONS(319),
    [anon_sym_break] = ACTIONS(319),
    [anon_sym_continue] = ACTIONS(319),
    [anon_sym_soe] = ACTIONS(319),
    [anon_sym_not] = ACTIONS(319),
    [anon_sym_and] = ACTIONS(319),
    [anon_sym_or] = ACTIONS(319),
    [anon_sym_read] = ACTIONS(319),
    [anon_sym_str] = ACTIONS(319),
    [anon_sym_as] = ACTIONS(319),
    [anon_sym_type] = ACTIONS(319),
    [anon_sym_try] = ACTIONS(319),
    [anon_sym_fail] = ACTIONS(319),
    [anon_sym_pure] = ACTIONS(319),
    [anon_sym_VER] = ACTIONS(319),
    [anon_sym_x] = ACTIONS(319),
    [anon_sym_int] = ACTIONS(319),
    [anon_sym_float] = ACTIONS(319),
    [anon_sym_bool] = ACTIONS(319),
    [anon_sym_dup] = ACTIONS(319),
    [anon_sym_swap] = ACTIONS(319),
    [anon_sym_drop] = ACTIONS(319),
    [anon_sym_over] = ACTIONS(319),
    [anon_sym_pick] = ACTIONS(319),
    [anon_sym_rot] = ACTIONS(319),
    [anon_sym_DASHrot] = ACTIONS(319),
    [anon_sym_nip] = ACTIONS(319),
    [anon_sym_w] = ACTIONS(319),
    [anon_sym_wl] = ACTIONS(319),
    [anon_sym_we] = ACTIONS(319),
    [anon_sym_wle] = ACTIONS(319),
    [anon_sym_len] = ACTIONS(319),
    [anon_sym_args] = ACTIONS(319),
    [anon_sym_glob] = ACTIONS(319),
    [anon_sym_toFloat] = ACTIONS(319),
    [anon_sym_toInt] = ACTIONS(319),
    [anon_sym_toPath] = ACTIONS(319),
    [anon_sym_toDt] = ACTIONS(319),
    [anon_sym_toGrid] = ACTIONS(319),
    [anon_sym_toCsv] = ACTIONS(319),
    [anon_sym_toCsvCell] = ACTIONS(319),
    [anon_sym_exit] = ACTIONS(319),
    [anon_sym_prompt] = ACTIONS(319),
    [anon_sym_stdin] = ACTIONS(319),
    [anon_sym_COLON_COLON] = ACTIONS(317),
    [anon_sym_foldl] = ACTIONS(319),
    [anon_sym_map] = ACTIONS(319),
    [anon_sym_each] = ACTIONS(319),
    [anon_sym_eachWhile] = ACTIONS(319),
    [anon_sym_filter] = ACTIONS(319),
    [anon_sym_append] = ACTIONS(319),
    [anon_sym_extend] = ACTIONS(319),
    [anon_sym_concat] = ACTIONS(319),
    [anon_sym_reverse] = ACTIONS(319),
    [anon_sym_sort] = ACTIONS(319),
    [anon_sym_sortV] = ACTIONS(319),
    [anon_sym_sortBy] = ACTIONS(319),
    [anon_sym_sortByCmp] = ACTIONS(319),
    [anon_sym_uniq] = ACTIONS(319),
    [anon_sym_zip] = ACTIONS(319),
    [anon_sym_enumerate] = ACTIONS(319),
    [anon_sym_enumerateN] = ACTIONS(319),
    [anon_sym_chunk] = ACTIONS(319),
    [anon_sym_pop] = ACTIONS(319),
    [anon_sym_take] = ACTIONS(319),
    [anon_sym_takeWhile] = ACTIONS(319),
    [anon_sym_skip] = ACTIONS(319),
    [anon_sym_dropWhile] = ACTIONS(319),
    [anon_sym_nth] = ACTIONS(319),
    [anon_sym_insert] = ACTIONS(319),
    [anon_sym_setAt] = ACTIONS(319),
    [anon_sym_del] = ACTIONS(319),
    [anon_sym_sum] = ACTIONS(319),
    [anon_sym_max] = ACTIONS(319),
    [anon_sym_max2] = ACTIONS(319),
    [anon_sym_min] = ACTIONS(319),
    [anon_sym_min2] = ACTIONS(319),
    [anon_sym_abs] = ACTIONS(319),
    [anon_sym_inc] = ACTIONS(319),
    [anon_sym_mod] = ACTIONS(319),
    [anon_sym_floor] = ACTIONS(319),
    [anon_sym_ceil] = ACTIONS(319),
    [anon_sym_round] = ACTIONS(319),
    [anon_sym_lines] = ACTIONS(319),
    [anon_sym_unlines] = ACTIONS(319),
    [anon_sym_unlinesCrLf] = ACTIONS(319),
    [anon_sym_split] = ACTIONS(319),
    [anon_sym_wsplit] = ACTIONS(319),
    [anon_sym_tsplit] = ACTIONS(319),
    [anon_sym_join] = ACTIONS(319),
    [anon_sym_trim] = ACTIONS(319),
    [anon_sym_trimStart] = ACTIONS(319),
    [anon_sym_trimEnd] = ACTIONS(319),
    [anon_sym_startsWith] = ACTIONS(319),
    [anon_sym_endsWith] = ACTIONS(319),
    [anon_sym_lower] = ACTIONS(319),
    [anon_sym_upper] = ACTIONS(319),
    [anon_sym_title] = ACTIONS(319),
    [anon_sym_leftPad] = ACTIONS(319),
    [anon_sym_findReplace] = ACTIONS(319),
    [anon_sym_in] = ACTIONS(319),
    [anon_sym_index] = ACTIONS(319),
    [anon_sym_lastIndexOf] = ACTIONS(319),
    [anon_sym_countSubStr] = ACTIONS(319),
    [anon_sym_parseJson] = ACTIONS(319),
    [anon_sym_parseCsv] = ACTIONS(319),
    [anon_sym_parseHtml] = ACTIONS(319),
    [anon_sym_parseExcel] = ACTIONS(319),
    [anon_sym_readFile] = ACTIONS(319),
    [anon_sym_readFileBytes] = ACTIONS(319),
    [anon_sym_readTsvFile] = ACTIONS(319),
    [anon_sym_writeFile] = ACTIONS(319),
    [anon_sym_appendFile] = ACTIONS(319),
    [anon_sym_fileExists] = ACTIONS(319),
    [anon_sym_isDir] = ACTIONS(319),
    [anon_sym_isFile] = ACTIONS(319),
    [anon_sym_fileSize] = ACTIONS(319),
    [anon_sym_cp] = ACTIONS(319),
    [anon_sym_mv] = ACTIONS(319),
    [anon_sym_rm] = ACTIONS(319),
    [anon_sym_rmf] = ACTIONS(319),
    [anon_sym_mkdir] = ACTIONS(319),
    [anon_sym_mkdirp] = ACTIONS(319),
    [anon_sym_cd] = ACTIONS(319),
    [anon_sym_pwd] = ACTIONS(319),
    [anon_sym_tempFile] = ACTIONS(319),
    [anon_sym_tempFileExt] = ACTIONS(319),
    [anon_sym_tempDir] = ACTIONS(319),
    [anon_sym_lsDir] = ACTIONS(319),
    [anon_sym_files] = ACTIONS(319),
    [anon_sym_dirs] = ACTIONS(319),
    [anon_sym_absPath] = ACTIONS(319),
    [anon_sym_dirname] = ACTIONS(319),
    [anon_sym_basename] = ACTIONS(319),
    [anon_sym_ext] = ACTIONS(319),
    [anon_sym_stem] = ACTIONS(319),
    [anon_sym_isCmd] = ACTIONS(319),
    [anon_sym_hardLink] = ACTIONS(319),
    [anon_sym_sha256sum] = ACTIONS(319),
    [anon_sym_md5] = ACTIONS(319),
    [anon_sym_now] = ACTIONS(319),
    [anon_sym_date] = ACTIONS(319),
    [anon_sym_year] = ACTIONS(319),
    [anon_sym_month] = ACTIONS(319),
    [anon_sym_day] = ACTIONS(319),
    [anon_sym_hour] = ACTIONS(319),
    [anon_sym_minute] = ACTIONS(319),
    [anon_sym_dateFmt] = ACTIONS(319),
    [anon_sym_isoDateFmt] = ACTIONS(319),
    [anon_sym_isoDateTimeFmt] = ACTIONS(319),
    [anon_sym_isWeekend] = ACTIONS(319),
    [anon_sym_isWeekday] = ACTIONS(319),
    [anon_sym_dow] = ACTIONS(319),
    [anon_sym_addDays] = ACTIONS(319),
    [anon_sym_toUnixTime] = ACTIONS(319),
    [anon_sym_toUnixTimeMilli] = ACTIONS(319),
    [anon_sym_toUnixTimeMicro] = ACTIONS(319),
    [anon_sym_toUnixTimeNano] = ACTIONS(319),
    [anon_sym_fromUnixTime] = ACTIONS(319),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(319),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(319),
    [anon_sym_fromUnixTimeNano] = ACTIONS(319),
    [anon_sym_toOleDate] = ACTIONS(319),
    [anon_sym_fromOleDate] = ACTIONS(319),
    [anon_sym_utcToCst] = ACTIONS(319),
    [anon_sym_cstToUtc] = ACTIONS(319),
    [anon_sym_reMatch] = ACTIONS(319),
    [anon_sym_reFindAll] = ACTIONS(319),
    [anon_sym_reFindAllIndex] = ACTIONS(319),
    [anon_sym_reReplace] = ACTIONS(319),
    [anon_sym_reSplit] = ACTIONS(319),
    [anon_sym_just] = ACTIONS(319),
    [anon_sym_none] = ACTIONS(319),
    [anon_sym_isNone] = ACTIONS(319),
    [anon_sym_maybe] = ACTIONS(319),
    [anon_sym_bind] = ACTIONS(319),
    [anon_sym_psub] = ACTIONS(319),
    [anon_sym_typeof] = ACTIONS(319),
    [anon_sym_runtime] = ACTIONS(319),
    [anon_sym_hostname] = ACTIONS(319),
    [anon_sym_httpGet] = ACTIONS(319),
    [anon_sym_httpPost] = ACTIONS(319),
    [anon_sym_urlEncode] = ACTIONS(319),
    [anon_sym_base64encode] = ACTIONS(319),
    [anon_sym_base64decode] = ACTIONS(319),
    [anon_sym_utf8Str] = ACTIONS(319),
    [anon_sym_utf8Bytes] = ACTIONS(319),
    [anon_sym_get] = ACTIONS(319),
    [anon_sym_getDef] = ACTIONS(319),
    [anon_sym_set] = ACTIONS(319),
    [anon_sym_setd] = ACTIONS(319),
    [anon_sym_keys] = ACTIONS(319),
    [anon_sym_values] = ACTIONS(319),
    [anon_sym_keyValues] = ACTIONS(319),
    [anon_sym_all] = ACTIONS(319),
    [anon_sym_any] = ACTIONS(319),
    [anon_sym_cartesian] = ACTIONS(319),
    [anon_sym_groupBy] = ACTIONS(319),
    [anon_sym_listToDict] = ACTIONS(319),
    [anon_sym_repeat] = ACTIONS(319),
    [anon_sym_seq] = ACTIONS(319),
    [anon_sym_tab] = ACTIONS(319),
    [anon_sym_select] = ACTIONS(319),
    [anon_sym_exclude] = ACTIONS(319),
    [anon_sym_derive] = ACTIONS(319),
    [anon_sym_updateCol] = ACTIONS(319),
    [anon_sym_gridValues] = ACTIONS(319),
    [anon_sym_leftJoin] = ACTIONS(319),
    [anon_sym_outerJoin] = ACTIONS(319),
    [anon_sym_linearSearch] = ACTIONS(319),
    [anon_sym_linearSearchIndex] = ACTIONS(319),
    [anon_sym_binPaths] = ACTIONS(319),
    [anon_sym_wt] = ACTIONS(319),
    [anon_sym_tt] = ACTIONS(319),
    [anon_sym_ttFile] = ACTIONS(319),
    [anon_sym_uw] = ACTIONS(319),
    [anon_sym_tuw] = ACTIONS(319),
    [anon_sym_strCmp] = ACTIONS(319),
    [anon_sym_floatCmp] = ACTIONS(319),
    [anon_sym_versionSortCmp] = ACTIONS(319),
    [anon_sym_id] = ACTIONS(319),
    [anon_sym_2id] = ACTIONS(319),
    [anon_sym_3id] = ACTIONS(319),
    [anon_sym_2unpack] = ACTIONS(319),
    [anon_sym_2apply] = ACTIONS(319),
    [anon_sym_2each] = ACTIONS(319),
    [anon_sym_2tuple] = ACTIONS(319),
    [anon_sym_DOTs] = ACTIONS(319),
    [anon_sym_DOTb] = ACTIONS(319),
    [anon_sym_DOTdef] = ACTIONS(319),
    [anon_sym_DOTenv] = ACTIONS(319),
    [sym_string] = ACTIONS(317),
    [sym_format_string] = ACTIONS(317),
    [sym_single_quoted_string] = ACTIONS(317),
    [sym_path] = ACTIONS(317),
    [sym_datetime] = ACTIONS(317),
    [sym_float] = ACTIONS(317),
    [sym_integer] = ACTIONS(319),
    [sym_env_store] = ACTIONS(317),
    [sym_env_check] = ACTIONS(317),
    [sym_env_retrieve] = ACTIONS(319),
    [sym_positional] = ACTIONS(317),
    [sym_var_retrieve] = ACTIONS(317),
    [sym_var_store] = ACTIONS(317),
    [sym_slice_indexer] = ACTIONS(317),
    [sym_indexer] = ACTIONS(317),
    [sym_end_indexer] = ACTIONS(319),
    [sym_start_indexer] = ACTIONS(319),
    [sym_match_arm_dup] = ACTIONS(317),
    [sym_prefix_quote] = ACTIONS(319),
    [anon_sym_GT] = ACTIONS(319),
    [anon_sym_GT_GT] = ACTIONS(317),
    [anon_sym_2_GT] = ACTIONS(319),
    [anon_sym_2_GT_GT] = ACTIONS(319),
    [anon_sym_AMP_GT] = ACTIONS(319),
    [anon_sym_AMP_GT_GT] = ACTIONS(317),
    [anon_sym_LT] = ACTIONS(319),
    [anon_sym_LT_GT] = ACTIONS(317),
    [anon_sym_STAR] = ACTIONS(319),
    [anon_sym_STARb] = ACTIONS(317),
    [anon_sym_CARET] = ACTIONS(319),
    [anon_sym_CARETb] = ACTIONS(317),
    [anon_sym_SEMI] = ACTIONS(317),
    [anon_sym_BANG] = ACTIONS(319),
    [anon_sym_QMARK] = ACTIONS(317),
    [anon_sym_BANG_EQ] = ACTIONS(317),
    [anon_sym_LT_EQ] = ACTIONS(317),
    [anon_sym_GT_EQ] = ACTIONS(317),
    [anon_sym_AMP] = ACTIONS(319),
    [anon_sym_PIPE] = ACTIONS(317),
    [anon_sym_COMMA] = ACTIONS(317),
    [anon_sym_COLON] = ACTIONS(319),
  },
  [34] = {
    [ts_builtin_sym_end] = ACTIONS(321),
    [sym_identifier] = ACTIONS(323),
    [anon_sym_LBRACK] = ACTIONS(323),
    [anon_sym_RBRACK] = ACTIONS(321),
    [anon_sym_LPAREN] = ACTIONS(321),
    [anon_sym_RPAREN] = ACTIONS(321),
    [anon_sym_LBRACE] = ACTIONS(321),
    [anon_sym_RBRACE] = ACTIONS(321),
    [anon_sym_LBRACK_PIPE] = ACTIONS(321),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(323),
    [anon_sym_false] = ACTIONS(323),
    [anon_sym_def] = ACTIONS(323),
    [anon_sym_end] = ACTIONS(323),
    [anon_sym_if] = ACTIONS(323),
    [anon_sym_iff] = ACTIONS(323),
    [anon_sym_else] = ACTIONS(323),
    [anon_sym_else_STAR] = ACTIONS(321),
    [anon_sym_STARif] = ACTIONS(321),
    [anon_sym_loop] = ACTIONS(323),
    [anon_sym_match] = ACTIONS(323),
    [anon_sym_break] = ACTIONS(323),
    [anon_sym_continue] = ACTIONS(323),
    [anon_sym_soe] = ACTIONS(323),
    [anon_sym_not] = ACTIONS(323),
    [anon_sym_and] = ACTIONS(323),
    [anon_sym_or] = ACTIONS(323),
    [anon_sym_read] = ACTIONS(323),
    [anon_sym_str] = ACTIONS(323),
    [anon_sym_as] = ACTIONS(323),
    [anon_sym_type] = ACTIONS(323),
    [anon_sym_try] = ACTIONS(323),
    [anon_sym_fail] = ACTIONS(323),
    [anon_sym_pure] = ACTIONS(323),
    [anon_sym_VER] = ACTIONS(323),
    [anon_sym_x] = ACTIONS(323),
    [anon_sym_int] = ACTIONS(323),
    [anon_sym_float] = ACTIONS(323),
    [anon_sym_bool] = ACTIONS(323),
    [anon_sym_dup] = ACTIONS(323),
    [anon_sym_swap] = ACTIONS(323),
    [anon_sym_drop] = ACTIONS(323),
    [anon_sym_over] = ACTIONS(323),
    [anon_sym_pick] = ACTIONS(323),
    [anon_sym_rot] = ACTIONS(323),
    [anon_sym_DASHrot] = ACTIONS(323),
    [anon_sym_nip] = ACTIONS(323),
    [anon_sym_w] = ACTIONS(323),
    [anon_sym_wl] = ACTIONS(323),
    [anon_sym_we] = ACTIONS(323),
    [anon_sym_wle] = ACTIONS(323),
    [anon_sym_len] = ACTIONS(323),
    [anon_sym_args] = ACTIONS(323),
    [anon_sym_glob] = ACTIONS(323),
    [anon_sym_toFloat] = ACTIONS(323),
    [anon_sym_toInt] = ACTIONS(323),
    [anon_sym_toPath] = ACTIONS(323),
    [anon_sym_toDt] = ACTIONS(323),
    [anon_sym_toGrid] = ACTIONS(323),
    [anon_sym_toCsv] = ACTIONS(323),
    [anon_sym_toCsvCell] = ACTIONS(323),
    [anon_sym_exit] = ACTIONS(323),
    [anon_sym_prompt] = ACTIONS(323),
    [anon_sym_stdin] = ACTIONS(323),
    [anon_sym_COLON_COLON] = ACTIONS(321),
    [anon_sym_foldl] = ACTIONS(323),
    [anon_sym_map] = ACTIONS(323),
    [anon_sym_each] = ACTIONS(323),
    [anon_sym_eachWhile] = ACTIONS(323),
    [anon_sym_filter] = ACTIONS(323),
    [anon_sym_append] = ACTIONS(323),
    [anon_sym_extend] = ACTIONS(323),
    [anon_sym_concat] = ACTIONS(323),
    [anon_sym_reverse] = ACTIONS(323),
    [anon_sym_sort] = ACTIONS(323),
    [anon_sym_sortV] = ACTIONS(323),
    [anon_sym_sortBy] = ACTIONS(323),
    [anon_sym_sortByCmp] = ACTIONS(323),
    [anon_sym_uniq] = ACTIONS(323),
    [anon_sym_zip] = ACTIONS(323),
    [anon_sym_enumerate] = ACTIONS(323),
    [anon_sym_enumerateN] = ACTIONS(323),
    [anon_sym_chunk] = ACTIONS(323),
    [anon_sym_pop] = ACTIONS(323),
    [anon_sym_take] = ACTIONS(323),
    [anon_sym_takeWhile] = ACTIONS(323),
    [anon_sym_skip] = ACTIONS(323),
    [anon_sym_dropWhile] = ACTIONS(323),
    [anon_sym_nth] = ACTIONS(323),
    [anon_sym_insert] = ACTIONS(323),
    [anon_sym_setAt] = ACTIONS(323),
    [anon_sym_del] = ACTIONS(323),
    [anon_sym_sum] = ACTIONS(323),
    [anon_sym_max] = ACTIONS(323),
    [anon_sym_max2] = ACTIONS(323),
    [anon_sym_min] = ACTIONS(323),
    [anon_sym_min2] = ACTIONS(323),
    [anon_sym_abs] = ACTIONS(323),
    [anon_sym_inc] = ACTIONS(323),
    [anon_sym_mod] = ACTIONS(323),
    [anon_sym_floor] = ACTIONS(323),
    [anon_sym_ceil] = ACTIONS(323),
    [anon_sym_round] = ACTIONS(323),
    [anon_sym_lines] = ACTIONS(323),
    [anon_sym_unlines] = ACTIONS(323),
    [anon_sym_unlinesCrLf] = ACTIONS(323),
    [anon_sym_split] = ACTIONS(323),
    [anon_sym_wsplit] = ACTIONS(323),
    [anon_sym_tsplit] = ACTIONS(323),
    [anon_sym_join] = ACTIONS(323),
    [anon_sym_trim] = ACTIONS(323),
    [anon_sym_trimStart] = ACTIONS(323),
    [anon_sym_trimEnd] = ACTIONS(323),
    [anon_sym_startsWith] = ACTIONS(323),
    [anon_sym_endsWith] = ACTIONS(323),
    [anon_sym_lower] = ACTIONS(323),
    [anon_sym_upper] = ACTIONS(323),
    [anon_sym_title] = ACTIONS(323),
    [anon_sym_leftPad] = ACTIONS(323),
    [anon_sym_findReplace] = ACTIONS(323),
    [anon_sym_in] = ACTIONS(323),
    [anon_sym_index] = ACTIONS(323),
    [anon_sym_lastIndexOf] = ACTIONS(323),
    [anon_sym_countSubStr] = ACTIONS(323),
    [anon_sym_parseJson] = ACTIONS(323),
    [anon_sym_parseCsv] = ACTIONS(323),
    [anon_sym_parseHtml] = ACTIONS(323),
    [anon_sym_parseExcel] = ACTIONS(323),
    [anon_sym_readFile] = ACTIONS(323),
    [anon_sym_readFileBytes] = ACTIONS(323),
    [anon_sym_readTsvFile] = ACTIONS(323),
    [anon_sym_writeFile] = ACTIONS(323),
    [anon_sym_appendFile] = ACTIONS(323),
    [anon_sym_fileExists] = ACTIONS(323),
    [anon_sym_isDir] = ACTIONS(323),
    [anon_sym_isFile] = ACTIONS(323),
    [anon_sym_fileSize] = ACTIONS(323),
    [anon_sym_cp] = ACTIONS(323),
    [anon_sym_mv] = ACTIONS(323),
    [anon_sym_rm] = ACTIONS(323),
    [anon_sym_rmf] = ACTIONS(323),
    [anon_sym_mkdir] = ACTIONS(323),
    [anon_sym_mkdirp] = ACTIONS(323),
    [anon_sym_cd] = ACTIONS(323),
    [anon_sym_pwd] = ACTIONS(323),
    [anon_sym_tempFile] = ACTIONS(323),
    [anon_sym_tempFileExt] = ACTIONS(323),
    [anon_sym_tempDir] = ACTIONS(323),
    [anon_sym_lsDir] = ACTIONS(323),
    [anon_sym_files] = ACTIONS(323),
    [anon_sym_dirs] = ACTIONS(323),
    [anon_sym_absPath] = ACTIONS(323),
    [anon_sym_dirname] = ACTIONS(323),
    [anon_sym_basename] = ACTIONS(323),
    [anon_sym_ext] = ACTIONS(323),
    [anon_sym_stem] = ACTIONS(323),
    [anon_sym_isCmd] = ACTIONS(323),
    [anon_sym_hardLink] = ACTIONS(323),
    [anon_sym_sha256sum] = ACTIONS(323),
    [anon_sym_md5] = ACTIONS(323),
    [anon_sym_now] = ACTIONS(323),
    [anon_sym_date] = ACTIONS(323),
    [anon_sym_year] = ACTIONS(323),
    [anon_sym_month] = ACTIONS(323),
    [anon_sym_day] = ACTIONS(323),
    [anon_sym_hour] = ACTIONS(323),
    [anon_sym_minute] = ACTIONS(323),
    [anon_sym_dateFmt] = ACTIONS(323),
    [anon_sym_isoDateFmt] = ACTIONS(323),
    [anon_sym_isoDateTimeFmt] = ACTIONS(323),
    [anon_sym_isWeekend] = ACTIONS(323),
    [anon_sym_isWeekday] = ACTIONS(323),
    [anon_sym_dow] = ACTIONS(323),
    [anon_sym_addDays] = ACTIONS(323),
    [anon_sym_toUnixTime] = ACTIONS(323),
    [anon_sym_toUnixTimeMilli] = ACTIONS(323),
    [anon_sym_toUnixTimeMicro] = ACTIONS(323),
    [anon_sym_toUnixTimeNano] = ACTIONS(323),
    [anon_sym_fromUnixTime] = ACTIONS(323),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(323),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(323),
    [anon_sym_fromUnixTimeNano] = ACTIONS(323),
    [anon_sym_toOleDate] = ACTIONS(323),
    [anon_sym_fromOleDate] = ACTIONS(323),
    [anon_sym_utcToCst] = ACTIONS(323),
    [anon_sym_cstToUtc] = ACTIONS(323),
    [anon_sym_reMatch] = ACTIONS(323),
    [anon_sym_reFindAll] = ACTIONS(323),
    [anon_sym_reFindAllIndex] = ACTIONS(323),
    [anon_sym_reReplace] = ACTIONS(323),
    [anon_sym_reSplit] = ACTIONS(323),
    [anon_sym_just] = ACTIONS(323),
    [anon_sym_none] = ACTIONS(323),
    [anon_sym_isNone] = ACTIONS(323),
    [anon_sym_maybe] = ACTIONS(323),
    [anon_sym_bind] = ACTIONS(323),
    [anon_sym_psub] = ACTIONS(323),
    [anon_sym_typeof] = ACTIONS(323),
    [anon_sym_runtime] = ACTIONS(323),
    [anon_sym_hostname] = ACTIONS(323),
    [anon_sym_httpGet] = ACTIONS(323),
    [anon_sym_httpPost] = ACTIONS(323),
    [anon_sym_urlEncode] = ACTIONS(323),
    [anon_sym_base64encode] = ACTIONS(323),
    [anon_sym_base64decode] = ACTIONS(323),
    [anon_sym_utf8Str] = ACTIONS(323),
    [anon_sym_utf8Bytes] = ACTIONS(323),
    [anon_sym_get] = ACTIONS(323),
    [anon_sym_getDef] = ACTIONS(323),
    [anon_sym_set] = ACTIONS(323),
    [anon_sym_setd] = ACTIONS(323),
    [anon_sym_keys] = ACTIONS(323),
    [anon_sym_values] = ACTIONS(323),
    [anon_sym_keyValues] = ACTIONS(323),
    [anon_sym_all] = ACTIONS(323),
    [anon_sym_any] = ACTIONS(323),
    [anon_sym_cartesian] = ACTIONS(323),
    [anon_sym_groupBy] = ACTIONS(323),
    [anon_sym_listToDict] = ACTIONS(323),
    [anon_sym_repeat] = ACTIONS(323),
    [anon_sym_seq] = ACTIONS(323),
    [anon_sym_tab] = ACTIONS(323),
    [anon_sym_select] = ACTIONS(323),
    [anon_sym_exclude] = ACTIONS(323),
    [anon_sym_derive] = ACTIONS(323),
    [anon_sym_updateCol] = ACTIONS(323),
    [anon_sym_gridValues] = ACTIONS(323),
    [anon_sym_leftJoin] = ACTIONS(323),
    [anon_sym_outerJoin] = ACTIONS(323),
    [anon_sym_linearSearch] = ACTIONS(323),
    [anon_sym_linearSearchIndex] = ACTIONS(323),
    [anon_sym_binPaths] = ACTIONS(323),
    [anon_sym_wt] = ACTIONS(323),
    [anon_sym_tt] = ACTIONS(323),
    [anon_sym_ttFile] = ACTIONS(323),
    [anon_sym_uw] = ACTIONS(323),
    [anon_sym_tuw] = ACTIONS(323),
    [anon_sym_strCmp] = ACTIONS(323),
    [anon_sym_floatCmp] = ACTIONS(323),
    [anon_sym_versionSortCmp] = ACTIONS(323),
    [anon_sym_id] = ACTIONS(323),
    [anon_sym_2id] = ACTIONS(323),
    [anon_sym_3id] = ACTIONS(323),
    [anon_sym_2unpack] = ACTIONS(323),
    [anon_sym_2apply] = ACTIONS(323),
    [anon_sym_2each] = ACTIONS(323),
    [anon_sym_2tuple] = ACTIONS(323),
    [anon_sym_DOTs] = ACTIONS(323),
    [anon_sym_DOTb] = ACTIONS(323),
    [anon_sym_DOTdef] = ACTIONS(323),
    [anon_sym_DOTenv] = ACTIONS(323),
    [sym_string] = ACTIONS(321),
    [sym_format_string] = ACTIONS(321),
    [sym_single_quoted_string] = ACTIONS(321),
    [sym_path] = ACTIONS(321),
    [sym_datetime] = ACTIONS(321),
    [sym_float] = ACTIONS(321),
    [sym_integer] = ACTIONS(323),
    [sym_env_store] = ACTIONS(321),
    [sym_env_check] = ACTIONS(321),
    [sym_env_retrieve] = ACTIONS(323),
    [sym_positional] = ACTIONS(321),
    [sym_var_retrieve] = ACTIONS(321),
    [sym_var_store] = ACTIONS(321),
    [sym_slice_indexer] = ACTIONS(321),
    [sym_indexer] = ACTIONS(321),
    [sym_end_indexer] = ACTIONS(323),
    [sym_start_indexer] = ACTIONS(323),
    [sym_match_arm_dup] = ACTIONS(321),
    [sym_prefix_quote] = ACTIONS(323),
    [anon_sym_GT] = ACTIONS(323),
    [anon_sym_GT_GT] = ACTIONS(321),
    [anon_sym_2_GT] = ACTIONS(323),
    [anon_sym_2_GT_GT] = ACTIONS(323),
    [anon_sym_AMP_GT] = ACTIONS(323),
    [anon_sym_AMP_GT_GT] = ACTIONS(321),
    [anon_sym_LT] = ACTIONS(323),
    [anon_sym_LT_GT] = ACTIONS(321),
    [anon_sym_STAR] = ACTIONS(323),
    [anon_sym_STARb] = ACTIONS(321),
    [anon_sym_CARET] = ACTIONS(323),
    [anon_sym_CARETb] = ACTIONS(321),
    [anon_sym_SEMI] = ACTIONS(321),
    [anon_sym_BANG] = ACTIONS(323),
    [anon_sym_QMARK] = ACTIONS(321),
    [anon_sym_BANG_EQ] = ACTIONS(321),
    [anon_sym_LT_EQ] = ACTIONS(321),
    [anon_sym_GT_EQ] = ACTIONS(321),
    [anon_sym_AMP] = ACTIONS(323),
    [anon_sym_PIPE] = ACTIONS(321),
    [anon_sym_COMMA] = ACTIONS(321),
    [anon_sym_COLON] = ACTIONS(323),
  },
  [35] = {
    [ts_builtin_sym_end] = ACTIONS(325),
    [sym_identifier] = ACTIONS(327),
    [anon_sym_LBRACK] = ACTIONS(327),
    [anon_sym_RBRACK] = ACTIONS(325),
    [anon_sym_LPAREN] = ACTIONS(325),
    [anon_sym_RPAREN] = ACTIONS(325),
    [anon_sym_LBRACE] = ACTIONS(325),
    [anon_sym_RBRACE] = ACTIONS(325),
    [anon_sym_LBRACK_PIPE] = ACTIONS(325),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(327),
    [anon_sym_false] = ACTIONS(327),
    [anon_sym_def] = ACTIONS(327),
    [anon_sym_end] = ACTIONS(327),
    [anon_sym_if] = ACTIONS(327),
    [anon_sym_iff] = ACTIONS(327),
    [anon_sym_else] = ACTIONS(327),
    [anon_sym_else_STAR] = ACTIONS(325),
    [anon_sym_STARif] = ACTIONS(325),
    [anon_sym_loop] = ACTIONS(327),
    [anon_sym_match] = ACTIONS(327),
    [anon_sym_break] = ACTIONS(327),
    [anon_sym_continue] = ACTIONS(327),
    [anon_sym_soe] = ACTIONS(327),
    [anon_sym_not] = ACTIONS(327),
    [anon_sym_and] = ACTIONS(327),
    [anon_sym_or] = ACTIONS(327),
    [anon_sym_read] = ACTIONS(327),
    [anon_sym_str] = ACTIONS(327),
    [anon_sym_as] = ACTIONS(327),
    [anon_sym_type] = ACTIONS(327),
    [anon_sym_try] = ACTIONS(327),
    [anon_sym_fail] = ACTIONS(327),
    [anon_sym_pure] = ACTIONS(327),
    [anon_sym_VER] = ACTIONS(327),
    [anon_sym_x] = ACTIONS(327),
    [anon_sym_int] = ACTIONS(327),
    [anon_sym_float] = ACTIONS(327),
    [anon_sym_bool] = ACTIONS(327),
    [anon_sym_dup] = ACTIONS(327),
    [anon_sym_swap] = ACTIONS(327),
    [anon_sym_drop] = ACTIONS(327),
    [anon_sym_over] = ACTIONS(327),
    [anon_sym_pick] = ACTIONS(327),
    [anon_sym_rot] = ACTIONS(327),
    [anon_sym_DASHrot] = ACTIONS(327),
    [anon_sym_nip] = ACTIONS(327),
    [anon_sym_w] = ACTIONS(327),
    [anon_sym_wl] = ACTIONS(327),
    [anon_sym_we] = ACTIONS(327),
    [anon_sym_wle] = ACTIONS(327),
    [anon_sym_len] = ACTIONS(327),
    [anon_sym_args] = ACTIONS(327),
    [anon_sym_glob] = ACTIONS(327),
    [anon_sym_toFloat] = ACTIONS(327),
    [anon_sym_toInt] = ACTIONS(327),
    [anon_sym_toPath] = ACTIONS(327),
    [anon_sym_toDt] = ACTIONS(327),
    [anon_sym_toGrid] = ACTIONS(327),
    [anon_sym_toCsv] = ACTIONS(327),
    [anon_sym_toCsvCell] = ACTIONS(327),
    [anon_sym_exit] = ACTIONS(327),
    [anon_sym_prompt] = ACTIONS(327),
    [anon_sym_stdin] = ACTIONS(327),
    [anon_sym_COLON_COLON] = ACTIONS(325),
    [anon_sym_foldl] = ACTIONS(327),
    [anon_sym_map] = ACTIONS(327),
    [anon_sym_each] = ACTIONS(327),
    [anon_sym_eachWhile] = ACTIONS(327),
    [anon_sym_filter] = ACTIONS(327),
    [anon_sym_append] = ACTIONS(327),
    [anon_sym_extend] = ACTIONS(327),
    [anon_sym_concat] = ACTIONS(327),
    [anon_sym_reverse] = ACTIONS(327),
    [anon_sym_sort] = ACTIONS(327),
    [anon_sym_sortV] = ACTIONS(327),
    [anon_sym_sortBy] = ACTIONS(327),
    [anon_sym_sortByCmp] = ACTIONS(327),
    [anon_sym_uniq] = ACTIONS(327),
    [anon_sym_zip] = ACTIONS(327),
    [anon_sym_enumerate] = ACTIONS(327),
    [anon_sym_enumerateN] = ACTIONS(327),
    [anon_sym_chunk] = ACTIONS(327),
    [anon_sym_pop] = ACTIONS(327),
    [anon_sym_take] = ACTIONS(327),
    [anon_sym_takeWhile] = ACTIONS(327),
    [anon_sym_skip] = ACTIONS(327),
    [anon_sym_dropWhile] = ACTIONS(327),
    [anon_sym_nth] = ACTIONS(327),
    [anon_sym_insert] = ACTIONS(327),
    [anon_sym_setAt] = ACTIONS(327),
    [anon_sym_del] = ACTIONS(327),
    [anon_sym_sum] = ACTIONS(327),
    [anon_sym_max] = ACTIONS(327),
    [anon_sym_max2] = ACTIONS(327),
    [anon_sym_min] = ACTIONS(327),
    [anon_sym_min2] = ACTIONS(327),
    [anon_sym_abs] = ACTIONS(327),
    [anon_sym_inc] = ACTIONS(327),
    [anon_sym_mod] = ACTIONS(327),
    [anon_sym_floor] = ACTIONS(327),
    [anon_sym_ceil] = ACTIONS(327),
    [anon_sym_round] = ACTIONS(327),
    [anon_sym_lines] = ACTIONS(327),
    [anon_sym_unlines] = ACTIONS(327),
    [anon_sym_unlinesCrLf] = ACTIONS(327),
    [anon_sym_split] = ACTIONS(327),
    [anon_sym_wsplit] = ACTIONS(327),
    [anon_sym_tsplit] = ACTIONS(327),
    [anon_sym_join] = ACTIONS(327),
    [anon_sym_trim] = ACTIONS(327),
    [anon_sym_trimStart] = ACTIONS(327),
    [anon_sym_trimEnd] = ACTIONS(327),
    [anon_sym_startsWith] = ACTIONS(327),
    [anon_sym_endsWith] = ACTIONS(327),
    [anon_sym_lower] = ACTIONS(327),
    [anon_sym_upper] = ACTIONS(327),
    [anon_sym_title] = ACTIONS(327),
    [anon_sym_leftPad] = ACTIONS(327),
    [anon_sym_findReplace] = ACTIONS(327),
    [anon_sym_in] = ACTIONS(327),
    [anon_sym_index] = ACTIONS(327),
    [anon_sym_lastIndexOf] = ACTIONS(327),
    [anon_sym_countSubStr] = ACTIONS(327),
    [anon_sym_parseJson] = ACTIONS(327),
    [anon_sym_parseCsv] = ACTIONS(327),
    [anon_sym_parseHtml] = ACTIONS(327),
    [anon_sym_parseExcel] = ACTIONS(327),
    [anon_sym_readFile] = ACTIONS(327),
    [anon_sym_readFileBytes] = ACTIONS(327),
    [anon_sym_readTsvFile] = ACTIONS(327),
    [anon_sym_writeFile] = ACTIONS(327),
    [anon_sym_appendFile] = ACTIONS(327),
    [anon_sym_fileExists] = ACTIONS(327),
    [anon_sym_isDir] = ACTIONS(327),
    [anon_sym_isFile] = ACTIONS(327),
    [anon_sym_fileSize] = ACTIONS(327),
    [anon_sym_cp] = ACTIONS(327),
    [anon_sym_mv] = ACTIONS(327),
    [anon_sym_rm] = ACTIONS(327),
    [anon_sym_rmf] = ACTIONS(327),
    [anon_sym_mkdir] = ACTIONS(327),
    [anon_sym_mkdirp] = ACTIONS(327),
    [anon_sym_cd] = ACTIONS(327),
    [anon_sym_pwd] = ACTIONS(327),
    [anon_sym_tempFile] = ACTIONS(327),
    [anon_sym_tempFileExt] = ACTIONS(327),
    [anon_sym_tempDir] = ACTIONS(327),
    [anon_sym_lsDir] = ACTIONS(327),
    [anon_sym_files] = ACTIONS(327),
    [anon_sym_dirs] = ACTIONS(327),
    [anon_sym_absPath] = ACTIONS(327),
    [anon_sym_dirname] = ACTIONS(327),
    [anon_sym_basename] = ACTIONS(327),
    [anon_sym_ext] = ACTIONS(327),
    [anon_sym_stem] = ACTIONS(327),
    [anon_sym_isCmd] = ACTIONS(327),
    [anon_sym_hardLink] = ACTIONS(327),
    [anon_sym_sha256sum] = ACTIONS(327),
    [anon_sym_md5] = ACTIONS(327),
    [anon_sym_now] = ACTIONS(327),
    [anon_sym_date] = ACTIONS(327),
    [anon_sym_year] = ACTIONS(327),
    [anon_sym_month] = ACTIONS(327),
    [anon_sym_day] = ACTIONS(327),
    [anon_sym_hour] = ACTIONS(327),
    [anon_sym_minute] = ACTIONS(327),
    [anon_sym_dateFmt] = ACTIONS(327),
    [anon_sym_isoDateFmt] = ACTIONS(327),
    [anon_sym_isoDateTimeFmt] = ACTIONS(327),
    [anon_sym_isWeekend] = ACTIONS(327),
    [anon_sym_isWeekday] = ACTIONS(327),
    [anon_sym_dow] = ACTIONS(327),
    [anon_sym_addDays] = ACTIONS(327),
    [anon_sym_toUnixTime] = ACTIONS(327),
    [anon_sym_toUnixTimeMilli] = ACTIONS(327),
    [anon_sym_toUnixTimeMicro] = ACTIONS(327),
    [anon_sym_toUnixTimeNano] = ACTIONS(327),
    [anon_sym_fromUnixTime] = ACTIONS(327),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(327),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(327),
    [anon_sym_fromUnixTimeNano] = ACTIONS(327),
    [anon_sym_toOleDate] = ACTIONS(327),
    [anon_sym_fromOleDate] = ACTIONS(327),
    [anon_sym_utcToCst] = ACTIONS(327),
    [anon_sym_cstToUtc] = ACTIONS(327),
    [anon_sym_reMatch] = ACTIONS(327),
    [anon_sym_reFindAll] = ACTIONS(327),
    [anon_sym_reFindAllIndex] = ACTIONS(327),
    [anon_sym_reReplace] = ACTIONS(327),
    [anon_sym_reSplit] = ACTIONS(327),
    [anon_sym_just] = ACTIONS(327),
    [anon_sym_none] = ACTIONS(327),
    [anon_sym_isNone] = ACTIONS(327),
    [anon_sym_maybe] = ACTIONS(327),
    [anon_sym_bind] = ACTIONS(327),
    [anon_sym_psub] = ACTIONS(327),
    [anon_sym_typeof] = ACTIONS(327),
    [anon_sym_runtime] = ACTIONS(327),
    [anon_sym_hostname] = ACTIONS(327),
    [anon_sym_httpGet] = ACTIONS(327),
    [anon_sym_httpPost] = ACTIONS(327),
    [anon_sym_urlEncode] = ACTIONS(327),
    [anon_sym_base64encode] = ACTIONS(327),
    [anon_sym_base64decode] = ACTIONS(327),
    [anon_sym_utf8Str] = ACTIONS(327),
    [anon_sym_utf8Bytes] = ACTIONS(327),
    [anon_sym_get] = ACTIONS(327),
    [anon_sym_getDef] = ACTIONS(327),
    [anon_sym_set] = ACTIONS(327),
    [anon_sym_setd] = ACTIONS(327),
    [anon_sym_keys] = ACTIONS(327),
    [anon_sym_values] = ACTIONS(327),
    [anon_sym_keyValues] = ACTIONS(327),
    [anon_sym_all] = ACTIONS(327),
    [anon_sym_any] = ACTIONS(327),
    [anon_sym_cartesian] = ACTIONS(327),
    [anon_sym_groupBy] = ACTIONS(327),
    [anon_sym_listToDict] = ACTIONS(327),
    [anon_sym_repeat] = ACTIONS(327),
    [anon_sym_seq] = ACTIONS(327),
    [anon_sym_tab] = ACTIONS(327),
    [anon_sym_select] = ACTIONS(327),
    [anon_sym_exclude] = ACTIONS(327),
    [anon_sym_derive] = ACTIONS(327),
    [anon_sym_updateCol] = ACTIONS(327),
    [anon_sym_gridValues] = ACTIONS(327),
    [anon_sym_leftJoin] = ACTIONS(327),
    [anon_sym_outerJoin] = ACTIONS(327),
    [anon_sym_linearSearch] = ACTIONS(327),
    [anon_sym_linearSearchIndex] = ACTIONS(327),
    [anon_sym_binPaths] = ACTIONS(327),
    [anon_sym_wt] = ACTIONS(327),
    [anon_sym_tt] = ACTIONS(327),
    [anon_sym_ttFile] = ACTIONS(327),
    [anon_sym_uw] = ACTIONS(327),
    [anon_sym_tuw] = ACTIONS(327),
    [anon_sym_strCmp] = ACTIONS(327),
    [anon_sym_floatCmp] = ACTIONS(327),
    [anon_sym_versionSortCmp] = ACTIONS(327),
    [anon_sym_id] = ACTIONS(327),
    [anon_sym_2id] = ACTIONS(327),
    [anon_sym_3id] = ACTIONS(327),
    [anon_sym_2unpack] = ACTIONS(327),
    [anon_sym_2apply] = ACTIONS(327),
    [anon_sym_2each] = ACTIONS(327),
    [anon_sym_2tuple] = ACTIONS(327),
    [anon_sym_DOTs] = ACTIONS(327),
    [anon_sym_DOTb] = ACTIONS(327),
    [anon_sym_DOTdef] = ACTIONS(327),
    [anon_sym_DOTenv] = ACTIONS(327),
    [sym_string] = ACTIONS(325),
    [sym_format_string] = ACTIONS(325),
    [sym_single_quoted_string] = ACTIONS(325),
    [sym_path] = ACTIONS(325),
    [sym_datetime] = ACTIONS(325),
    [sym_float] = ACTIONS(325),
    [sym_integer] = ACTIONS(327),
    [sym_env_store] = ACTIONS(325),
    [sym_env_check] = ACTIONS(325),
    [sym_env_retrieve] = ACTIONS(327),
    [sym_positional] = ACTIONS(325),
    [sym_var_retrieve] = ACTIONS(325),
    [sym_var_store] = ACTIONS(325),
    [sym_slice_indexer] = ACTIONS(325),
    [sym_indexer] = ACTIONS(325),
    [sym_end_indexer] = ACTIONS(327),
    [sym_start_indexer] = ACTIONS(327),
    [sym_match_arm_dup] = ACTIONS(325),
    [sym_prefix_quote] = ACTIONS(327),
    [anon_sym_GT] = ACTIONS(327),
    [anon_sym_GT_GT] = ACTIONS(325),
    [anon_sym_2_GT] = ACTIONS(327),
    [anon_sym_2_GT_GT] = ACTIONS(327),
    [anon_sym_AMP_GT] = ACTIONS(327),
    [anon_sym_AMP_GT_GT] = ACTIONS(325),
    [anon_sym_LT] = ACTIONS(327),
    [anon_sym_LT_GT] = ACTIONS(325),
    [anon_sym_STAR] = ACTIONS(327),
    [anon_sym_STARb] = ACTIONS(325),
    [anon_sym_CARET] = ACTIONS(327),
    [anon_sym_CARETb] = ACTIONS(325),
    [anon_sym_SEMI] = ACTIONS(325),
    [anon_sym_BANG] = ACTIONS(327),
    [anon_sym_QMARK] = ACTIONS(325),
    [anon_sym_BANG_EQ] = ACTIONS(325),
    [anon_sym_LT_EQ] = ACTIONS(325),
    [anon_sym_GT_EQ] = ACTIONS(325),
    [anon_sym_AMP] = ACTIONS(327),
    [anon_sym_PIPE] = ACTIONS(325),
    [anon_sym_COMMA] = ACTIONS(325),
    [anon_sym_COLON] = ACTIONS(327),
  },
  [36] = {
    [ts_builtin_sym_end] = ACTIONS(329),
    [sym_identifier] = ACTIONS(331),
    [anon_sym_LBRACK] = ACTIONS(331),
    [anon_sym_RBRACK] = ACTIONS(329),
    [anon_sym_LPAREN] = ACTIONS(329),
    [anon_sym_RPAREN] = ACTIONS(329),
    [anon_sym_LBRACE] = ACTIONS(329),
    [anon_sym_RBRACE] = ACTIONS(329),
    [anon_sym_LBRACK_PIPE] = ACTIONS(329),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(331),
    [anon_sym_false] = ACTIONS(331),
    [anon_sym_def] = ACTIONS(331),
    [anon_sym_end] = ACTIONS(331),
    [anon_sym_if] = ACTIONS(331),
    [anon_sym_iff] = ACTIONS(331),
    [anon_sym_else] = ACTIONS(331),
    [anon_sym_else_STAR] = ACTIONS(329),
    [anon_sym_STARif] = ACTIONS(329),
    [anon_sym_loop] = ACTIONS(331),
    [anon_sym_match] = ACTIONS(331),
    [anon_sym_break] = ACTIONS(331),
    [anon_sym_continue] = ACTIONS(331),
    [anon_sym_soe] = ACTIONS(331),
    [anon_sym_not] = ACTIONS(331),
    [anon_sym_and] = ACTIONS(331),
    [anon_sym_or] = ACTIONS(331),
    [anon_sym_read] = ACTIONS(331),
    [anon_sym_str] = ACTIONS(331),
    [anon_sym_as] = ACTIONS(331),
    [anon_sym_type] = ACTIONS(331),
    [anon_sym_try] = ACTIONS(331),
    [anon_sym_fail] = ACTIONS(331),
    [anon_sym_pure] = ACTIONS(331),
    [anon_sym_VER] = ACTIONS(331),
    [anon_sym_x] = ACTIONS(331),
    [anon_sym_int] = ACTIONS(331),
    [anon_sym_float] = ACTIONS(331),
    [anon_sym_bool] = ACTIONS(331),
    [anon_sym_dup] = ACTIONS(331),
    [anon_sym_swap] = ACTIONS(331),
    [anon_sym_drop] = ACTIONS(331),
    [anon_sym_over] = ACTIONS(331),
    [anon_sym_pick] = ACTIONS(331),
    [anon_sym_rot] = ACTIONS(331),
    [anon_sym_DASHrot] = ACTIONS(331),
    [anon_sym_nip] = ACTIONS(331),
    [anon_sym_w] = ACTIONS(331),
    [anon_sym_wl] = ACTIONS(331),
    [anon_sym_we] = ACTIONS(331),
    [anon_sym_wle] = ACTIONS(331),
    [anon_sym_len] = ACTIONS(331),
    [anon_sym_args] = ACTIONS(331),
    [anon_sym_glob] = ACTIONS(331),
    [anon_sym_toFloat] = ACTIONS(331),
    [anon_sym_toInt] = ACTIONS(331),
    [anon_sym_toPath] = ACTIONS(331),
    [anon_sym_toDt] = ACTIONS(331),
    [anon_sym_toGrid] = ACTIONS(331),
    [anon_sym_toCsv] = ACTIONS(331),
    [anon_sym_toCsvCell] = ACTIONS(331),
    [anon_sym_exit] = ACTIONS(331),
    [anon_sym_prompt] = ACTIONS(331),
    [anon_sym_stdin] = ACTIONS(331),
    [anon_sym_COLON_COLON] = ACTIONS(329),
    [anon_sym_foldl] = ACTIONS(331),
    [anon_sym_map] = ACTIONS(331),
    [anon_sym_each] = ACTIONS(331),
    [anon_sym_eachWhile] = ACTIONS(331),
    [anon_sym_filter] = ACTIONS(331),
    [anon_sym_append] = ACTIONS(331),
    [anon_sym_extend] = ACTIONS(331),
    [anon_sym_concat] = ACTIONS(331),
    [anon_sym_reverse] = ACTIONS(331),
    [anon_sym_sort] = ACTIONS(331),
    [anon_sym_sortV] = ACTIONS(331),
    [anon_sym_sortBy] = ACTIONS(331),
    [anon_sym_sortByCmp] = ACTIONS(331),
    [anon_sym_uniq] = ACTIONS(331),
    [anon_sym_zip] = ACTIONS(331),
    [anon_sym_enumerate] = ACTIONS(331),
    [anon_sym_enumerateN] = ACTIONS(331),
    [anon_sym_chunk] = ACTIONS(331),
    [anon_sym_pop] = ACTIONS(331),
    [anon_sym_take] = ACTIONS(331),
    [anon_sym_takeWhile] = ACTIONS(331),
    [anon_sym_skip] = ACTIONS(331),
    [anon_sym_dropWhile] = ACTIONS(331),
    [anon_sym_nth] = ACTIONS(331),
    [anon_sym_insert] = ACTIONS(331),
    [anon_sym_setAt] = ACTIONS(331),
    [anon_sym_del] = ACTIONS(331),
    [anon_sym_sum] = ACTIONS(331),
    [anon_sym_max] = ACTIONS(331),
    [anon_sym_max2] = ACTIONS(331),
    [anon_sym_min] = ACTIONS(331),
    [anon_sym_min2] = ACTIONS(331),
    [anon_sym_abs] = ACTIONS(331),
    [anon_sym_inc] = ACTIONS(331),
    [anon_sym_mod] = ACTIONS(331),
    [anon_sym_floor] = ACTIONS(331),
    [anon_sym_ceil] = ACTIONS(331),
    [anon_sym_round] = ACTIONS(331),
    [anon_sym_lines] = ACTIONS(331),
    [anon_sym_unlines] = ACTIONS(331),
    [anon_sym_unlinesCrLf] = ACTIONS(331),
    [anon_sym_split] = ACTIONS(331),
    [anon_sym_wsplit] = ACTIONS(331),
    [anon_sym_tsplit] = ACTIONS(331),
    [anon_sym_join] = ACTIONS(331),
    [anon_sym_trim] = ACTIONS(331),
    [anon_sym_trimStart] = ACTIONS(331),
    [anon_sym_trimEnd] = ACTIONS(331),
    [anon_sym_startsWith] = ACTIONS(331),
    [anon_sym_endsWith] = ACTIONS(331),
    [anon_sym_lower] = ACTIONS(331),
    [anon_sym_upper] = ACTIONS(331),
    [anon_sym_title] = ACTIONS(331),
    [anon_sym_leftPad] = ACTIONS(331),
    [anon_sym_findReplace] = ACTIONS(331),
    [anon_sym_in] = ACTIONS(331),
    [anon_sym_index] = ACTIONS(331),
    [anon_sym_lastIndexOf] = ACTIONS(331),
    [anon_sym_countSubStr] = ACTIONS(331),
    [anon_sym_parseJson] = ACTIONS(331),
    [anon_sym_parseCsv] = ACTIONS(331),
    [anon_sym_parseHtml] = ACTIONS(331),
    [anon_sym_parseExcel] = ACTIONS(331),
    [anon_sym_readFile] = ACTIONS(331),
    [anon_sym_readFileBytes] = ACTIONS(331),
    [anon_sym_readTsvFile] = ACTIONS(331),
    [anon_sym_writeFile] = ACTIONS(331),
    [anon_sym_appendFile] = ACTIONS(331),
    [anon_sym_fileExists] = ACTIONS(331),
    [anon_sym_isDir] = ACTIONS(331),
    [anon_sym_isFile] = ACTIONS(331),
    [anon_sym_fileSize] = ACTIONS(331),
    [anon_sym_cp] = ACTIONS(331),
    [anon_sym_mv] = ACTIONS(331),
    [anon_sym_rm] = ACTIONS(331),
    [anon_sym_rmf] = ACTIONS(331),
    [anon_sym_mkdir] = ACTIONS(331),
    [anon_sym_mkdirp] = ACTIONS(331),
    [anon_sym_cd] = ACTIONS(331),
    [anon_sym_pwd] = ACTIONS(331),
    [anon_sym_tempFile] = ACTIONS(331),
    [anon_sym_tempFileExt] = ACTIONS(331),
    [anon_sym_tempDir] = ACTIONS(331),
    [anon_sym_lsDir] = ACTIONS(331),
    [anon_sym_files] = ACTIONS(331),
    [anon_sym_dirs] = ACTIONS(331),
    [anon_sym_absPath] = ACTIONS(331),
    [anon_sym_dirname] = ACTIONS(331),
    [anon_sym_basename] = ACTIONS(331),
    [anon_sym_ext] = ACTIONS(331),
    [anon_sym_stem] = ACTIONS(331),
    [anon_sym_isCmd] = ACTIONS(331),
    [anon_sym_hardLink] = ACTIONS(331),
    [anon_sym_sha256sum] = ACTIONS(331),
    [anon_sym_md5] = ACTIONS(331),
    [anon_sym_now] = ACTIONS(331),
    [anon_sym_date] = ACTIONS(331),
    [anon_sym_year] = ACTIONS(331),
    [anon_sym_month] = ACTIONS(331),
    [anon_sym_day] = ACTIONS(331),
    [anon_sym_hour] = ACTIONS(331),
    [anon_sym_minute] = ACTIONS(331),
    [anon_sym_dateFmt] = ACTIONS(331),
    [anon_sym_isoDateFmt] = ACTIONS(331),
    [anon_sym_isoDateTimeFmt] = ACTIONS(331),
    [anon_sym_isWeekend] = ACTIONS(331),
    [anon_sym_isWeekday] = ACTIONS(331),
    [anon_sym_dow] = ACTIONS(331),
    [anon_sym_addDays] = ACTIONS(331),
    [anon_sym_toUnixTime] = ACTIONS(331),
    [anon_sym_toUnixTimeMilli] = ACTIONS(331),
    [anon_sym_toUnixTimeMicro] = ACTIONS(331),
    [anon_sym_toUnixTimeNano] = ACTIONS(331),
    [anon_sym_fromUnixTime] = ACTIONS(331),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(331),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(331),
    [anon_sym_fromUnixTimeNano] = ACTIONS(331),
    [anon_sym_toOleDate] = ACTIONS(331),
    [anon_sym_fromOleDate] = ACTIONS(331),
    [anon_sym_utcToCst] = ACTIONS(331),
    [anon_sym_cstToUtc] = ACTIONS(331),
    [anon_sym_reMatch] = ACTIONS(331),
    [anon_sym_reFindAll] = ACTIONS(331),
    [anon_sym_reFindAllIndex] = ACTIONS(331),
    [anon_sym_reReplace] = ACTIONS(331),
    [anon_sym_reSplit] = ACTIONS(331),
    [anon_sym_just] = ACTIONS(331),
    [anon_sym_none] = ACTIONS(331),
    [anon_sym_isNone] = ACTIONS(331),
    [anon_sym_maybe] = ACTIONS(331),
    [anon_sym_bind] = ACTIONS(331),
    [anon_sym_psub] = ACTIONS(331),
    [anon_sym_typeof] = ACTIONS(331),
    [anon_sym_runtime] = ACTIONS(331),
    [anon_sym_hostname] = ACTIONS(331),
    [anon_sym_httpGet] = ACTIONS(331),
    [anon_sym_httpPost] = ACTIONS(331),
    [anon_sym_urlEncode] = ACTIONS(331),
    [anon_sym_base64encode] = ACTIONS(331),
    [anon_sym_base64decode] = ACTIONS(331),
    [anon_sym_utf8Str] = ACTIONS(331),
    [anon_sym_utf8Bytes] = ACTIONS(331),
    [anon_sym_get] = ACTIONS(331),
    [anon_sym_getDef] = ACTIONS(331),
    [anon_sym_set] = ACTIONS(331),
    [anon_sym_setd] = ACTIONS(331),
    [anon_sym_keys] = ACTIONS(331),
    [anon_sym_values] = ACTIONS(331),
    [anon_sym_keyValues] = ACTIONS(331),
    [anon_sym_all] = ACTIONS(331),
    [anon_sym_any] = ACTIONS(331),
    [anon_sym_cartesian] = ACTIONS(331),
    [anon_sym_groupBy] = ACTIONS(331),
    [anon_sym_listToDict] = ACTIONS(331),
    [anon_sym_repeat] = ACTIONS(331),
    [anon_sym_seq] = ACTIONS(331),
    [anon_sym_tab] = ACTIONS(331),
    [anon_sym_select] = ACTIONS(331),
    [anon_sym_exclude] = ACTIONS(331),
    [anon_sym_derive] = ACTIONS(331),
    [anon_sym_updateCol] = ACTIONS(331),
    [anon_sym_gridValues] = ACTIONS(331),
    [anon_sym_leftJoin] = ACTIONS(331),
    [anon_sym_outerJoin] = ACTIONS(331),
    [anon_sym_linearSearch] = ACTIONS(331),
    [anon_sym_linearSearchIndex] = ACTIONS(331),
    [anon_sym_binPaths] = ACTIONS(331),
    [anon_sym_wt] = ACTIONS(331),
    [anon_sym_tt] = ACTIONS(331),
    [anon_sym_ttFile] = ACTIONS(331),
    [anon_sym_uw] = ACTIONS(331),
    [anon_sym_tuw] = ACTIONS(331),
    [anon_sym_strCmp] = ACTIONS(331),
    [anon_sym_floatCmp] = ACTIONS(331),
    [anon_sym_versionSortCmp] = ACTIONS(331),
    [anon_sym_id] = ACTIONS(331),
    [anon_sym_2id] = ACTIONS(331),
    [anon_sym_3id] = ACTIONS(331),
    [anon_sym_2unpack] = ACTIONS(331),
    [anon_sym_2apply] = ACTIONS(331),
    [anon_sym_2each] = ACTIONS(331),
    [anon_sym_2tuple] = ACTIONS(331),
    [anon_sym_DOTs] = ACTIONS(331),
    [anon_sym_DOTb] = ACTIONS(331),
    [anon_sym_DOTdef] = ACTIONS(331),
    [anon_sym_DOTenv] = ACTIONS(331),
    [sym_string] = ACTIONS(329),
    [sym_format_string] = ACTIONS(329),
    [sym_single_quoted_string] = ACTIONS(329),
    [sym_path] = ACTIONS(329),
    [sym_datetime] = ACTIONS(329),
    [sym_float] = ACTIONS(329),
    [sym_integer] = ACTIONS(331),
    [sym_env_store] = ACTIONS(329),
    [sym_env_check] = ACTIONS(329),
    [sym_env_retrieve] = ACTIONS(331),
    [sym_positional] = ACTIONS(329),
    [sym_var_retrieve] = ACTIONS(329),
    [sym_var_store] = ACTIONS(329),
    [sym_slice_indexer] = ACTIONS(329),
    [sym_indexer] = ACTIONS(329),
    [sym_end_indexer] = ACTIONS(331),
    [sym_start_indexer] = ACTIONS(331),
    [sym_match_arm_dup] = ACTIONS(329),
    [sym_prefix_quote] = ACTIONS(331),
    [anon_sym_GT] = ACTIONS(331),
    [anon_sym_GT_GT] = ACTIONS(329),
    [anon_sym_2_GT] = ACTIONS(331),
    [anon_sym_2_GT_GT] = ACTIONS(331),
    [anon_sym_AMP_GT] = ACTIONS(331),
    [anon_sym_AMP_GT_GT] = ACTIONS(329),
    [anon_sym_LT] = ACTIONS(331),
    [anon_sym_LT_GT] = ACTIONS(329),
    [anon_sym_STAR] = ACTIONS(331),
    [anon_sym_STARb] = ACTIONS(329),
    [anon_sym_CARET] = ACTIONS(331),
    [anon_sym_CARETb] = ACTIONS(329),
    [anon_sym_SEMI] = ACTIONS(329),
    [anon_sym_BANG] = ACTIONS(331),
    [anon_sym_QMARK] = ACTIONS(329),
    [anon_sym_BANG_EQ] = ACTIONS(329),
    [anon_sym_LT_EQ] = ACTIONS(329),
    [anon_sym_GT_EQ] = ACTIONS(329),
    [anon_sym_AMP] = ACTIONS(331),
    [anon_sym_PIPE] = ACTIONS(329),
    [anon_sym_COMMA] = ACTIONS(329),
    [anon_sym_COLON] = ACTIONS(331),
  },
  [37] = {
    [sym_identifier] = ACTIONS(311),
    [anon_sym_LBRACK] = ACTIONS(311),
    [anon_sym_LPAREN] = ACTIONS(309),
    [anon_sym_LBRACE] = ACTIONS(309),
    [anon_sym_LBRACK_PIPE] = ACTIONS(309),
    [anon_sym_PIPE_RBRACK] = ACTIONS(309),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(311),
    [anon_sym_false] = ACTIONS(311),
    [anon_sym_def] = ACTIONS(311),
    [anon_sym_end] = ACTIONS(311),
    [anon_sym_if] = ACTIONS(311),
    [anon_sym_iff] = ACTIONS(311),
    [anon_sym_else] = ACTIONS(311),
    [anon_sym_else_STAR] = ACTIONS(309),
    [anon_sym_STARif] = ACTIONS(309),
    [anon_sym_loop] = ACTIONS(311),
    [anon_sym_match] = ACTIONS(311),
    [anon_sym_break] = ACTIONS(311),
    [anon_sym_continue] = ACTIONS(311),
    [anon_sym_soe] = ACTIONS(311),
    [anon_sym_not] = ACTIONS(311),
    [anon_sym_and] = ACTIONS(311),
    [anon_sym_or] = ACTIONS(311),
    [anon_sym_read] = ACTIONS(311),
    [anon_sym_str] = ACTIONS(311),
    [anon_sym_as] = ACTIONS(311),
    [anon_sym_type] = ACTIONS(311),
    [anon_sym_try] = ACTIONS(311),
    [anon_sym_fail] = ACTIONS(311),
    [anon_sym_pure] = ACTIONS(311),
    [anon_sym_VER] = ACTIONS(311),
    [anon_sym_x] = ACTIONS(311),
    [anon_sym_int] = ACTIONS(311),
    [anon_sym_float] = ACTIONS(311),
    [anon_sym_bool] = ACTIONS(311),
    [anon_sym_dup] = ACTIONS(311),
    [anon_sym_swap] = ACTIONS(311),
    [anon_sym_drop] = ACTIONS(311),
    [anon_sym_over] = ACTIONS(311),
    [anon_sym_pick] = ACTIONS(311),
    [anon_sym_rot] = ACTIONS(311),
    [anon_sym_DASHrot] = ACTIONS(311),
    [anon_sym_nip] = ACTIONS(311),
    [anon_sym_w] = ACTIONS(311),
    [anon_sym_wl] = ACTIONS(311),
    [anon_sym_we] = ACTIONS(311),
    [anon_sym_wle] = ACTIONS(311),
    [anon_sym_len] = ACTIONS(311),
    [anon_sym_args] = ACTIONS(311),
    [anon_sym_glob] = ACTIONS(311),
    [anon_sym_toFloat] = ACTIONS(311),
    [anon_sym_toInt] = ACTIONS(311),
    [anon_sym_toPath] = ACTIONS(311),
    [anon_sym_toDt] = ACTIONS(311),
    [anon_sym_toGrid] = ACTIONS(311),
    [anon_sym_toCsv] = ACTIONS(311),
    [anon_sym_toCsvCell] = ACTIONS(311),
    [anon_sym_exit] = ACTIONS(311),
    [anon_sym_prompt] = ACTIONS(311),
    [anon_sym_stdin] = ACTIONS(311),
    [anon_sym_COLON_COLON] = ACTIONS(309),
    [anon_sym_foldl] = ACTIONS(311),
    [anon_sym_map] = ACTIONS(311),
    [anon_sym_each] = ACTIONS(311),
    [anon_sym_eachWhile] = ACTIONS(311),
    [anon_sym_filter] = ACTIONS(311),
    [anon_sym_append] = ACTIONS(311),
    [anon_sym_extend] = ACTIONS(311),
    [anon_sym_concat] = ACTIONS(311),
    [anon_sym_reverse] = ACTIONS(311),
    [anon_sym_sort] = ACTIONS(311),
    [anon_sym_sortV] = ACTIONS(311),
    [anon_sym_sortBy] = ACTIONS(311),
    [anon_sym_sortByCmp] = ACTIONS(311),
    [anon_sym_uniq] = ACTIONS(311),
    [anon_sym_zip] = ACTIONS(311),
    [anon_sym_enumerate] = ACTIONS(311),
    [anon_sym_enumerateN] = ACTIONS(311),
    [anon_sym_chunk] = ACTIONS(311),
    [anon_sym_pop] = ACTIONS(311),
    [anon_sym_take] = ACTIONS(311),
    [anon_sym_takeWhile] = ACTIONS(311),
    [anon_sym_skip] = ACTIONS(311),
    [anon_sym_dropWhile] = ACTIONS(311),
    [anon_sym_nth] = ACTIONS(311),
    [anon_sym_insert] = ACTIONS(311),
    [anon_sym_setAt] = ACTIONS(311),
    [anon_sym_del] = ACTIONS(311),
    [anon_sym_sum] = ACTIONS(311),
    [anon_sym_max] = ACTIONS(311),
    [anon_sym_max2] = ACTIONS(311),
    [anon_sym_min] = ACTIONS(311),
    [anon_sym_min2] = ACTIONS(311),
    [anon_sym_abs] = ACTIONS(311),
    [anon_sym_inc] = ACTIONS(311),
    [anon_sym_mod] = ACTIONS(311),
    [anon_sym_floor] = ACTIONS(311),
    [anon_sym_ceil] = ACTIONS(311),
    [anon_sym_round] = ACTIONS(311),
    [anon_sym_lines] = ACTIONS(311),
    [anon_sym_unlines] = ACTIONS(311),
    [anon_sym_unlinesCrLf] = ACTIONS(311),
    [anon_sym_split] = ACTIONS(311),
    [anon_sym_wsplit] = ACTIONS(311),
    [anon_sym_tsplit] = ACTIONS(311),
    [anon_sym_join] = ACTIONS(311),
    [anon_sym_trim] = ACTIONS(311),
    [anon_sym_trimStart] = ACTIONS(311),
    [anon_sym_trimEnd] = ACTIONS(311),
    [anon_sym_startsWith] = ACTIONS(311),
    [anon_sym_endsWith] = ACTIONS(311),
    [anon_sym_lower] = ACTIONS(311),
    [anon_sym_upper] = ACTIONS(311),
    [anon_sym_title] = ACTIONS(311),
    [anon_sym_leftPad] = ACTIONS(311),
    [anon_sym_findReplace] = ACTIONS(311),
    [anon_sym_in] = ACTIONS(311),
    [anon_sym_index] = ACTIONS(311),
    [anon_sym_lastIndexOf] = ACTIONS(311),
    [anon_sym_countSubStr] = ACTIONS(311),
    [anon_sym_parseJson] = ACTIONS(311),
    [anon_sym_parseCsv] = ACTIONS(311),
    [anon_sym_parseHtml] = ACTIONS(311),
    [anon_sym_parseExcel] = ACTIONS(311),
    [anon_sym_readFile] = ACTIONS(311),
    [anon_sym_readFileBytes] = ACTIONS(311),
    [anon_sym_readTsvFile] = ACTIONS(311),
    [anon_sym_writeFile] = ACTIONS(311),
    [anon_sym_appendFile] = ACTIONS(311),
    [anon_sym_fileExists] = ACTIONS(311),
    [anon_sym_isDir] = ACTIONS(311),
    [anon_sym_isFile] = ACTIONS(311),
    [anon_sym_fileSize] = ACTIONS(311),
    [anon_sym_cp] = ACTIONS(311),
    [anon_sym_mv] = ACTIONS(311),
    [anon_sym_rm] = ACTIONS(311),
    [anon_sym_rmf] = ACTIONS(311),
    [anon_sym_mkdir] = ACTIONS(311),
    [anon_sym_mkdirp] = ACTIONS(311),
    [anon_sym_cd] = ACTIONS(311),
    [anon_sym_pwd] = ACTIONS(311),
    [anon_sym_tempFile] = ACTIONS(311),
    [anon_sym_tempFileExt] = ACTIONS(311),
    [anon_sym_tempDir] = ACTIONS(311),
    [anon_sym_lsDir] = ACTIONS(311),
    [anon_sym_files] = ACTIONS(311),
    [anon_sym_dirs] = ACTIONS(311),
    [anon_sym_absPath] = ACTIONS(311),
    [anon_sym_dirname] = ACTIONS(311),
    [anon_sym_basename] = ACTIONS(311),
    [anon_sym_ext] = ACTIONS(311),
    [anon_sym_stem] = ACTIONS(311),
    [anon_sym_isCmd] = ACTIONS(311),
    [anon_sym_hardLink] = ACTIONS(311),
    [anon_sym_sha256sum] = ACTIONS(311),
    [anon_sym_md5] = ACTIONS(311),
    [anon_sym_now] = ACTIONS(311),
    [anon_sym_date] = ACTIONS(311),
    [anon_sym_year] = ACTIONS(311),
    [anon_sym_month] = ACTIONS(311),
    [anon_sym_day] = ACTIONS(311),
    [anon_sym_hour] = ACTIONS(311),
    [anon_sym_minute] = ACTIONS(311),
    [anon_sym_dateFmt] = ACTIONS(311),
    [anon_sym_isoDateFmt] = ACTIONS(311),
    [anon_sym_isoDateTimeFmt] = ACTIONS(311),
    [anon_sym_isWeekend] = ACTIONS(311),
    [anon_sym_isWeekday] = ACTIONS(311),
    [anon_sym_dow] = ACTIONS(311),
    [anon_sym_addDays] = ACTIONS(311),
    [anon_sym_toUnixTime] = ACTIONS(311),
    [anon_sym_toUnixTimeMilli] = ACTIONS(311),
    [anon_sym_toUnixTimeMicro] = ACTIONS(311),
    [anon_sym_toUnixTimeNano] = ACTIONS(311),
    [anon_sym_fromUnixTime] = ACTIONS(311),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(311),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(311),
    [anon_sym_fromUnixTimeNano] = ACTIONS(311),
    [anon_sym_toOleDate] = ACTIONS(311),
    [anon_sym_fromOleDate] = ACTIONS(311),
    [anon_sym_utcToCst] = ACTIONS(311),
    [anon_sym_cstToUtc] = ACTIONS(311),
    [anon_sym_reMatch] = ACTIONS(311),
    [anon_sym_reFindAll] = ACTIONS(311),
    [anon_sym_reFindAllIndex] = ACTIONS(311),
    [anon_sym_reReplace] = ACTIONS(311),
    [anon_sym_reSplit] = ACTIONS(311),
    [anon_sym_just] = ACTIONS(311),
    [anon_sym_none] = ACTIONS(311),
    [anon_sym_isNone] = ACTIONS(311),
    [anon_sym_maybe] = ACTIONS(311),
    [anon_sym_bind] = ACTIONS(311),
    [anon_sym_psub] = ACTIONS(311),
    [anon_sym_typeof] = ACTIONS(311),
    [anon_sym_runtime] = ACTIONS(311),
    [anon_sym_hostname] = ACTIONS(311),
    [anon_sym_httpGet] = ACTIONS(311),
    [anon_sym_httpPost] = ACTIONS(311),
    [anon_sym_urlEncode] = ACTIONS(311),
    [anon_sym_base64encode] = ACTIONS(311),
    [anon_sym_base64decode] = ACTIONS(311),
    [anon_sym_utf8Str] = ACTIONS(311),
    [anon_sym_utf8Bytes] = ACTIONS(311),
    [anon_sym_get] = ACTIONS(311),
    [anon_sym_getDef] = ACTIONS(311),
    [anon_sym_set] = ACTIONS(311),
    [anon_sym_setd] = ACTIONS(311),
    [anon_sym_keys] = ACTIONS(311),
    [anon_sym_values] = ACTIONS(311),
    [anon_sym_keyValues] = ACTIONS(311),
    [anon_sym_all] = ACTIONS(311),
    [anon_sym_any] = ACTIONS(311),
    [anon_sym_cartesian] = ACTIONS(311),
    [anon_sym_groupBy] = ACTIONS(311),
    [anon_sym_listToDict] = ACTIONS(311),
    [anon_sym_repeat] = ACTIONS(311),
    [anon_sym_seq] = ACTIONS(311),
    [anon_sym_tab] = ACTIONS(311),
    [anon_sym_select] = ACTIONS(311),
    [anon_sym_exclude] = ACTIONS(311),
    [anon_sym_derive] = ACTIONS(311),
    [anon_sym_updateCol] = ACTIONS(311),
    [anon_sym_gridValues] = ACTIONS(311),
    [anon_sym_leftJoin] = ACTIONS(311),
    [anon_sym_outerJoin] = ACTIONS(311),
    [anon_sym_linearSearch] = ACTIONS(311),
    [anon_sym_linearSearchIndex] = ACTIONS(311),
    [anon_sym_binPaths] = ACTIONS(311),
    [anon_sym_wt] = ACTIONS(311),
    [anon_sym_tt] = ACTIONS(311),
    [anon_sym_ttFile] = ACTIONS(311),
    [anon_sym_uw] = ACTIONS(311),
    [anon_sym_tuw] = ACTIONS(311),
    [anon_sym_strCmp] = ACTIONS(311),
    [anon_sym_floatCmp] = ACTIONS(311),
    [anon_sym_versionSortCmp] = ACTIONS(311),
    [anon_sym_id] = ACTIONS(311),
    [anon_sym_2id] = ACTIONS(311),
    [anon_sym_3id] = ACTIONS(311),
    [anon_sym_2unpack] = ACTIONS(311),
    [anon_sym_2apply] = ACTIONS(311),
    [anon_sym_2each] = ACTIONS(311),
    [anon_sym_2tuple] = ACTIONS(311),
    [anon_sym_DOTs] = ACTIONS(311),
    [anon_sym_DOTb] = ACTIONS(311),
    [anon_sym_DOTdef] = ACTIONS(311),
    [anon_sym_DOTenv] = ACTIONS(311),
    [sym_string] = ACTIONS(309),
    [sym_format_string] = ACTIONS(309),
    [sym_single_quoted_string] = ACTIONS(309),
    [sym_path] = ACTIONS(309),
    [sym_datetime] = ACTIONS(309),
    [sym_float] = ACTIONS(309),
    [sym_integer] = ACTIONS(311),
    [sym_env_store] = ACTIONS(309),
    [sym_env_check] = ACTIONS(309),
    [sym_env_retrieve] = ACTIONS(311),
    [sym_positional] = ACTIONS(309),
    [sym_var_retrieve] = ACTIONS(309),
    [sym_var_store] = ACTIONS(309),
    [sym_slice_indexer] = ACTIONS(309),
    [sym_indexer] = ACTIONS(309),
    [sym_end_indexer] = ACTIONS(311),
    [sym_start_indexer] = ACTIONS(311),
    [sym_match_arm_dup] = ACTIONS(309),
    [sym_prefix_quote] = ACTIONS(311),
    [anon_sym_GT] = ACTIONS(311),
    [anon_sym_GT_GT] = ACTIONS(309),
    [anon_sym_2_GT] = ACTIONS(311),
    [anon_sym_2_GT_GT] = ACTIONS(311),
    [anon_sym_AMP_GT] = ACTIONS(311),
    [anon_sym_AMP_GT_GT] = ACTIONS(309),
    [anon_sym_LT] = ACTIONS(311),
    [anon_sym_LT_GT] = ACTIONS(309),
    [anon_sym_STAR] = ACTIONS(311),
    [anon_sym_STARb] = ACTIONS(309),
    [anon_sym_CARET] = ACTIONS(311),
    [anon_sym_CARETb] = ACTIONS(309),
    [anon_sym_SEMI] = ACTIONS(309),
    [anon_sym_BANG] = ACTIONS(311),
    [anon_sym_QMARK] = ACTIONS(309),
    [anon_sym_BANG_EQ] = ACTIONS(309),
    [anon_sym_LT_EQ] = ACTIONS(309),
    [anon_sym_GT_EQ] = ACTIONS(309),
    [anon_sym_AMP] = ACTIONS(311),
    [anon_sym_PIPE] = ACTIONS(311),
    [anon_sym_COMMA] = ACTIONS(309),
    [anon_sym_COLON] = ACTIONS(311),
  },
  [38] = {
    [sym_identifier] = ACTIONS(319),
    [anon_sym_LBRACK] = ACTIONS(319),
    [anon_sym_LPAREN] = ACTIONS(317),
    [anon_sym_LBRACE] = ACTIONS(317),
    [anon_sym_LBRACK_PIPE] = ACTIONS(317),
    [anon_sym_PIPE_RBRACK] = ACTIONS(317),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(319),
    [anon_sym_false] = ACTIONS(319),
    [anon_sym_def] = ACTIONS(319),
    [anon_sym_end] = ACTIONS(319),
    [anon_sym_if] = ACTIONS(319),
    [anon_sym_iff] = ACTIONS(319),
    [anon_sym_else] = ACTIONS(319),
    [anon_sym_else_STAR] = ACTIONS(317),
    [anon_sym_STARif] = ACTIONS(317),
    [anon_sym_loop] = ACTIONS(319),
    [anon_sym_match] = ACTIONS(319),
    [anon_sym_break] = ACTIONS(319),
    [anon_sym_continue] = ACTIONS(319),
    [anon_sym_soe] = ACTIONS(319),
    [anon_sym_not] = ACTIONS(319),
    [anon_sym_and] = ACTIONS(319),
    [anon_sym_or] = ACTIONS(319),
    [anon_sym_read] = ACTIONS(319),
    [anon_sym_str] = ACTIONS(319),
    [anon_sym_as] = ACTIONS(319),
    [anon_sym_type] = ACTIONS(319),
    [anon_sym_try] = ACTIONS(319),
    [anon_sym_fail] = ACTIONS(319),
    [anon_sym_pure] = ACTIONS(319),
    [anon_sym_VER] = ACTIONS(319),
    [anon_sym_x] = ACTIONS(319),
    [anon_sym_int] = ACTIONS(319),
    [anon_sym_float] = ACTIONS(319),
    [anon_sym_bool] = ACTIONS(319),
    [anon_sym_dup] = ACTIONS(319),
    [anon_sym_swap] = ACTIONS(319),
    [anon_sym_drop] = ACTIONS(319),
    [anon_sym_over] = ACTIONS(319),
    [anon_sym_pick] = ACTIONS(319),
    [anon_sym_rot] = ACTIONS(319),
    [anon_sym_DASHrot] = ACTIONS(319),
    [anon_sym_nip] = ACTIONS(319),
    [anon_sym_w] = ACTIONS(319),
    [anon_sym_wl] = ACTIONS(319),
    [anon_sym_we] = ACTIONS(319),
    [anon_sym_wle] = ACTIONS(319),
    [anon_sym_len] = ACTIONS(319),
    [anon_sym_args] = ACTIONS(319),
    [anon_sym_glob] = ACTIONS(319),
    [anon_sym_toFloat] = ACTIONS(319),
    [anon_sym_toInt] = ACTIONS(319),
    [anon_sym_toPath] = ACTIONS(319),
    [anon_sym_toDt] = ACTIONS(319),
    [anon_sym_toGrid] = ACTIONS(319),
    [anon_sym_toCsv] = ACTIONS(319),
    [anon_sym_toCsvCell] = ACTIONS(319),
    [anon_sym_exit] = ACTIONS(319),
    [anon_sym_prompt] = ACTIONS(319),
    [anon_sym_stdin] = ACTIONS(319),
    [anon_sym_COLON_COLON] = ACTIONS(317),
    [anon_sym_foldl] = ACTIONS(319),
    [anon_sym_map] = ACTIONS(319),
    [anon_sym_each] = ACTIONS(319),
    [anon_sym_eachWhile] = ACTIONS(319),
    [anon_sym_filter] = ACTIONS(319),
    [anon_sym_append] = ACTIONS(319),
    [anon_sym_extend] = ACTIONS(319),
    [anon_sym_concat] = ACTIONS(319),
    [anon_sym_reverse] = ACTIONS(319),
    [anon_sym_sort] = ACTIONS(319),
    [anon_sym_sortV] = ACTIONS(319),
    [anon_sym_sortBy] = ACTIONS(319),
    [anon_sym_sortByCmp] = ACTIONS(319),
    [anon_sym_uniq] = ACTIONS(319),
    [anon_sym_zip] = ACTIONS(319),
    [anon_sym_enumerate] = ACTIONS(319),
    [anon_sym_enumerateN] = ACTIONS(319),
    [anon_sym_chunk] = ACTIONS(319),
    [anon_sym_pop] = ACTIONS(319),
    [anon_sym_take] = ACTIONS(319),
    [anon_sym_takeWhile] = ACTIONS(319),
    [anon_sym_skip] = ACTIONS(319),
    [anon_sym_dropWhile] = ACTIONS(319),
    [anon_sym_nth] = ACTIONS(319),
    [anon_sym_insert] = ACTIONS(319),
    [anon_sym_setAt] = ACTIONS(319),
    [anon_sym_del] = ACTIONS(319),
    [anon_sym_sum] = ACTIONS(319),
    [anon_sym_max] = ACTIONS(319),
    [anon_sym_max2] = ACTIONS(319),
    [anon_sym_min] = ACTIONS(319),
    [anon_sym_min2] = ACTIONS(319),
    [anon_sym_abs] = ACTIONS(319),
    [anon_sym_inc] = ACTIONS(319),
    [anon_sym_mod] = ACTIONS(319),
    [anon_sym_floor] = ACTIONS(319),
    [anon_sym_ceil] = ACTIONS(319),
    [anon_sym_round] = ACTIONS(319),
    [anon_sym_lines] = ACTIONS(319),
    [anon_sym_unlines] = ACTIONS(319),
    [anon_sym_unlinesCrLf] = ACTIONS(319),
    [anon_sym_split] = ACTIONS(319),
    [anon_sym_wsplit] = ACTIONS(319),
    [anon_sym_tsplit] = ACTIONS(319),
    [anon_sym_join] = ACTIONS(319),
    [anon_sym_trim] = ACTIONS(319),
    [anon_sym_trimStart] = ACTIONS(319),
    [anon_sym_trimEnd] = ACTIONS(319),
    [anon_sym_startsWith] = ACTIONS(319),
    [anon_sym_endsWith] = ACTIONS(319),
    [anon_sym_lower] = ACTIONS(319),
    [anon_sym_upper] = ACTIONS(319),
    [anon_sym_title] = ACTIONS(319),
    [anon_sym_leftPad] = ACTIONS(319),
    [anon_sym_findReplace] = ACTIONS(319),
    [anon_sym_in] = ACTIONS(319),
    [anon_sym_index] = ACTIONS(319),
    [anon_sym_lastIndexOf] = ACTIONS(319),
    [anon_sym_countSubStr] = ACTIONS(319),
    [anon_sym_parseJson] = ACTIONS(319),
    [anon_sym_parseCsv] = ACTIONS(319),
    [anon_sym_parseHtml] = ACTIONS(319),
    [anon_sym_parseExcel] = ACTIONS(319),
    [anon_sym_readFile] = ACTIONS(319),
    [anon_sym_readFileBytes] = ACTIONS(319),
    [anon_sym_readTsvFile] = ACTIONS(319),
    [anon_sym_writeFile] = ACTIONS(319),
    [anon_sym_appendFile] = ACTIONS(319),
    [anon_sym_fileExists] = ACTIONS(319),
    [anon_sym_isDir] = ACTIONS(319),
    [anon_sym_isFile] = ACTIONS(319),
    [anon_sym_fileSize] = ACTIONS(319),
    [anon_sym_cp] = ACTIONS(319),
    [anon_sym_mv] = ACTIONS(319),
    [anon_sym_rm] = ACTIONS(319),
    [anon_sym_rmf] = ACTIONS(319),
    [anon_sym_mkdir] = ACTIONS(319),
    [anon_sym_mkdirp] = ACTIONS(319),
    [anon_sym_cd] = ACTIONS(319),
    [anon_sym_pwd] = ACTIONS(319),
    [anon_sym_tempFile] = ACTIONS(319),
    [anon_sym_tempFileExt] = ACTIONS(319),
    [anon_sym_tempDir] = ACTIONS(319),
    [anon_sym_lsDir] = ACTIONS(319),
    [anon_sym_files] = ACTIONS(319),
    [anon_sym_dirs] = ACTIONS(319),
    [anon_sym_absPath] = ACTIONS(319),
    [anon_sym_dirname] = ACTIONS(319),
    [anon_sym_basename] = ACTIONS(319),
    [anon_sym_ext] = ACTIONS(319),
    [anon_sym_stem] = ACTIONS(319),
    [anon_sym_isCmd] = ACTIONS(319),
    [anon_sym_hardLink] = ACTIONS(319),
    [anon_sym_sha256sum] = ACTIONS(319),
    [anon_sym_md5] = ACTIONS(319),
    [anon_sym_now] = ACTIONS(319),
    [anon_sym_date] = ACTIONS(319),
    [anon_sym_year] = ACTIONS(319),
    [anon_sym_month] = ACTIONS(319),
    [anon_sym_day] = ACTIONS(319),
    [anon_sym_hour] = ACTIONS(319),
    [anon_sym_minute] = ACTIONS(319),
    [anon_sym_dateFmt] = ACTIONS(319),
    [anon_sym_isoDateFmt] = ACTIONS(319),
    [anon_sym_isoDateTimeFmt] = ACTIONS(319),
    [anon_sym_isWeekend] = ACTIONS(319),
    [anon_sym_isWeekday] = ACTIONS(319),
    [anon_sym_dow] = ACTIONS(319),
    [anon_sym_addDays] = ACTIONS(319),
    [anon_sym_toUnixTime] = ACTIONS(319),
    [anon_sym_toUnixTimeMilli] = ACTIONS(319),
    [anon_sym_toUnixTimeMicro] = ACTIONS(319),
    [anon_sym_toUnixTimeNano] = ACTIONS(319),
    [anon_sym_fromUnixTime] = ACTIONS(319),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(319),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(319),
    [anon_sym_fromUnixTimeNano] = ACTIONS(319),
    [anon_sym_toOleDate] = ACTIONS(319),
    [anon_sym_fromOleDate] = ACTIONS(319),
    [anon_sym_utcToCst] = ACTIONS(319),
    [anon_sym_cstToUtc] = ACTIONS(319),
    [anon_sym_reMatch] = ACTIONS(319),
    [anon_sym_reFindAll] = ACTIONS(319),
    [anon_sym_reFindAllIndex] = ACTIONS(319),
    [anon_sym_reReplace] = ACTIONS(319),
    [anon_sym_reSplit] = ACTIONS(319),
    [anon_sym_just] = ACTIONS(319),
    [anon_sym_none] = ACTIONS(319),
    [anon_sym_isNone] = ACTIONS(319),
    [anon_sym_maybe] = ACTIONS(319),
    [anon_sym_bind] = ACTIONS(319),
    [anon_sym_psub] = ACTIONS(319),
    [anon_sym_typeof] = ACTIONS(319),
    [anon_sym_runtime] = ACTIONS(319),
    [anon_sym_hostname] = ACTIONS(319),
    [anon_sym_httpGet] = ACTIONS(319),
    [anon_sym_httpPost] = ACTIONS(319),
    [anon_sym_urlEncode] = ACTIONS(319),
    [anon_sym_base64encode] = ACTIONS(319),
    [anon_sym_base64decode] = ACTIONS(319),
    [anon_sym_utf8Str] = ACTIONS(319),
    [anon_sym_utf8Bytes] = ACTIONS(319),
    [anon_sym_get] = ACTIONS(319),
    [anon_sym_getDef] = ACTIONS(319),
    [anon_sym_set] = ACTIONS(319),
    [anon_sym_setd] = ACTIONS(319),
    [anon_sym_keys] = ACTIONS(319),
    [anon_sym_values] = ACTIONS(319),
    [anon_sym_keyValues] = ACTIONS(319),
    [anon_sym_all] = ACTIONS(319),
    [anon_sym_any] = ACTIONS(319),
    [anon_sym_cartesian] = ACTIONS(319),
    [anon_sym_groupBy] = ACTIONS(319),
    [anon_sym_listToDict] = ACTIONS(319),
    [anon_sym_repeat] = ACTIONS(319),
    [anon_sym_seq] = ACTIONS(319),
    [anon_sym_tab] = ACTIONS(319),
    [anon_sym_select] = ACTIONS(319),
    [anon_sym_exclude] = ACTIONS(319),
    [anon_sym_derive] = ACTIONS(319),
    [anon_sym_updateCol] = ACTIONS(319),
    [anon_sym_gridValues] = ACTIONS(319),
    [anon_sym_leftJoin] = ACTIONS(319),
    [anon_sym_outerJoin] = ACTIONS(319),
    [anon_sym_linearSearch] = ACTIONS(319),
    [anon_sym_linearSearchIndex] = ACTIONS(319),
    [anon_sym_binPaths] = ACTIONS(319),
    [anon_sym_wt] = ACTIONS(319),
    [anon_sym_tt] = ACTIONS(319),
    [anon_sym_ttFile] = ACTIONS(319),
    [anon_sym_uw] = ACTIONS(319),
    [anon_sym_tuw] = ACTIONS(319),
    [anon_sym_strCmp] = ACTIONS(319),
    [anon_sym_floatCmp] = ACTIONS(319),
    [anon_sym_versionSortCmp] = ACTIONS(319),
    [anon_sym_id] = ACTIONS(319),
    [anon_sym_2id] = ACTIONS(319),
    [anon_sym_3id] = ACTIONS(319),
    [anon_sym_2unpack] = ACTIONS(319),
    [anon_sym_2apply] = ACTIONS(319),
    [anon_sym_2each] = ACTIONS(319),
    [anon_sym_2tuple] = ACTIONS(319),
    [anon_sym_DOTs] = ACTIONS(319),
    [anon_sym_DOTb] = ACTIONS(319),
    [anon_sym_DOTdef] = ACTIONS(319),
    [anon_sym_DOTenv] = ACTIONS(319),
    [sym_string] = ACTIONS(317),
    [sym_format_string] = ACTIONS(317),
    [sym_single_quoted_string] = ACTIONS(317),
    [sym_path] = ACTIONS(317),
    [sym_datetime] = ACTIONS(317),
    [sym_float] = ACTIONS(317),
    [sym_integer] = ACTIONS(319),
    [sym_env_store] = ACTIONS(317),
    [sym_env_check] = ACTIONS(317),
    [sym_env_retrieve] = ACTIONS(319),
    [sym_positional] = ACTIONS(317),
    [sym_var_retrieve] = ACTIONS(317),
    [sym_var_store] = ACTIONS(317),
    [sym_slice_indexer] = ACTIONS(317),
    [sym_indexer] = ACTIONS(317),
    [sym_end_indexer] = ACTIONS(319),
    [sym_start_indexer] = ACTIONS(319),
    [sym_match_arm_dup] = ACTIONS(317),
    [sym_prefix_quote] = ACTIONS(319),
    [anon_sym_GT] = ACTIONS(319),
    [anon_sym_GT_GT] = ACTIONS(317),
    [anon_sym_2_GT] = ACTIONS(319),
    [anon_sym_2_GT_GT] = ACTIONS(319),
    [anon_sym_AMP_GT] = ACTIONS(319),
    [anon_sym_AMP_GT_GT] = ACTIONS(317),
    [anon_sym_LT] = ACTIONS(319),
    [anon_sym_LT_GT] = ACTIONS(317),
    [anon_sym_STAR] = ACTIONS(319),
    [anon_sym_STARb] = ACTIONS(317),
    [anon_sym_CARET] = ACTIONS(319),
    [anon_sym_CARETb] = ACTIONS(317),
    [anon_sym_SEMI] = ACTIONS(317),
    [anon_sym_BANG] = ACTIONS(319),
    [anon_sym_QMARK] = ACTIONS(317),
    [anon_sym_BANG_EQ] = ACTIONS(317),
    [anon_sym_LT_EQ] = ACTIONS(317),
    [anon_sym_GT_EQ] = ACTIONS(317),
    [anon_sym_AMP] = ACTIONS(319),
    [anon_sym_PIPE] = ACTIONS(319),
    [anon_sym_COMMA] = ACTIONS(317),
    [anon_sym_COLON] = ACTIONS(319),
  },
  [39] = {
    [sym_identifier] = ACTIONS(323),
    [anon_sym_LBRACK] = ACTIONS(323),
    [anon_sym_LPAREN] = ACTIONS(321),
    [anon_sym_LBRACE] = ACTIONS(321),
    [anon_sym_LBRACK_PIPE] = ACTIONS(321),
    [anon_sym_PIPE_RBRACK] = ACTIONS(321),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(323),
    [anon_sym_false] = ACTIONS(323),
    [anon_sym_def] = ACTIONS(323),
    [anon_sym_end] = ACTIONS(323),
    [anon_sym_if] = ACTIONS(323),
    [anon_sym_iff] = ACTIONS(323),
    [anon_sym_else] = ACTIONS(323),
    [anon_sym_else_STAR] = ACTIONS(321),
    [anon_sym_STARif] = ACTIONS(321),
    [anon_sym_loop] = ACTIONS(323),
    [anon_sym_match] = ACTIONS(323),
    [anon_sym_break] = ACTIONS(323),
    [anon_sym_continue] = ACTIONS(323),
    [anon_sym_soe] = ACTIONS(323),
    [anon_sym_not] = ACTIONS(323),
    [anon_sym_and] = ACTIONS(323),
    [anon_sym_or] = ACTIONS(323),
    [anon_sym_read] = ACTIONS(323),
    [anon_sym_str] = ACTIONS(323),
    [anon_sym_as] = ACTIONS(323),
    [anon_sym_type] = ACTIONS(323),
    [anon_sym_try] = ACTIONS(323),
    [anon_sym_fail] = ACTIONS(323),
    [anon_sym_pure] = ACTIONS(323),
    [anon_sym_VER] = ACTIONS(323),
    [anon_sym_x] = ACTIONS(323),
    [anon_sym_int] = ACTIONS(323),
    [anon_sym_float] = ACTIONS(323),
    [anon_sym_bool] = ACTIONS(323),
    [anon_sym_dup] = ACTIONS(323),
    [anon_sym_swap] = ACTIONS(323),
    [anon_sym_drop] = ACTIONS(323),
    [anon_sym_over] = ACTIONS(323),
    [anon_sym_pick] = ACTIONS(323),
    [anon_sym_rot] = ACTIONS(323),
    [anon_sym_DASHrot] = ACTIONS(323),
    [anon_sym_nip] = ACTIONS(323),
    [anon_sym_w] = ACTIONS(323),
    [anon_sym_wl] = ACTIONS(323),
    [anon_sym_we] = ACTIONS(323),
    [anon_sym_wle] = ACTIONS(323),
    [anon_sym_len] = ACTIONS(323),
    [anon_sym_args] = ACTIONS(323),
    [anon_sym_glob] = ACTIONS(323),
    [anon_sym_toFloat] = ACTIONS(323),
    [anon_sym_toInt] = ACTIONS(323),
    [anon_sym_toPath] = ACTIONS(323),
    [anon_sym_toDt] = ACTIONS(323),
    [anon_sym_toGrid] = ACTIONS(323),
    [anon_sym_toCsv] = ACTIONS(323),
    [anon_sym_toCsvCell] = ACTIONS(323),
    [anon_sym_exit] = ACTIONS(323),
    [anon_sym_prompt] = ACTIONS(323),
    [anon_sym_stdin] = ACTIONS(323),
    [anon_sym_COLON_COLON] = ACTIONS(321),
    [anon_sym_foldl] = ACTIONS(323),
    [anon_sym_map] = ACTIONS(323),
    [anon_sym_each] = ACTIONS(323),
    [anon_sym_eachWhile] = ACTIONS(323),
    [anon_sym_filter] = ACTIONS(323),
    [anon_sym_append] = ACTIONS(323),
    [anon_sym_extend] = ACTIONS(323),
    [anon_sym_concat] = ACTIONS(323),
    [anon_sym_reverse] = ACTIONS(323),
    [anon_sym_sort] = ACTIONS(323),
    [anon_sym_sortV] = ACTIONS(323),
    [anon_sym_sortBy] = ACTIONS(323),
    [anon_sym_sortByCmp] = ACTIONS(323),
    [anon_sym_uniq] = ACTIONS(323),
    [anon_sym_zip] = ACTIONS(323),
    [anon_sym_enumerate] = ACTIONS(323),
    [anon_sym_enumerateN] = ACTIONS(323),
    [anon_sym_chunk] = ACTIONS(323),
    [anon_sym_pop] = ACTIONS(323),
    [anon_sym_take] = ACTIONS(323),
    [anon_sym_takeWhile] = ACTIONS(323),
    [anon_sym_skip] = ACTIONS(323),
    [anon_sym_dropWhile] = ACTIONS(323),
    [anon_sym_nth] = ACTIONS(323),
    [anon_sym_insert] = ACTIONS(323),
    [anon_sym_setAt] = ACTIONS(323),
    [anon_sym_del] = ACTIONS(323),
    [anon_sym_sum] = ACTIONS(323),
    [anon_sym_max] = ACTIONS(323),
    [anon_sym_max2] = ACTIONS(323),
    [anon_sym_min] = ACTIONS(323),
    [anon_sym_min2] = ACTIONS(323),
    [anon_sym_abs] = ACTIONS(323),
    [anon_sym_inc] = ACTIONS(323),
    [anon_sym_mod] = ACTIONS(323),
    [anon_sym_floor] = ACTIONS(323),
    [anon_sym_ceil] = ACTIONS(323),
    [anon_sym_round] = ACTIONS(323),
    [anon_sym_lines] = ACTIONS(323),
    [anon_sym_unlines] = ACTIONS(323),
    [anon_sym_unlinesCrLf] = ACTIONS(323),
    [anon_sym_split] = ACTIONS(323),
    [anon_sym_wsplit] = ACTIONS(323),
    [anon_sym_tsplit] = ACTIONS(323),
    [anon_sym_join] = ACTIONS(323),
    [anon_sym_trim] = ACTIONS(323),
    [anon_sym_trimStart] = ACTIONS(323),
    [anon_sym_trimEnd] = ACTIONS(323),
    [anon_sym_startsWith] = ACTIONS(323),
    [anon_sym_endsWith] = ACTIONS(323),
    [anon_sym_lower] = ACTIONS(323),
    [anon_sym_upper] = ACTIONS(323),
    [anon_sym_title] = ACTIONS(323),
    [anon_sym_leftPad] = ACTIONS(323),
    [anon_sym_findReplace] = ACTIONS(323),
    [anon_sym_in] = ACTIONS(323),
    [anon_sym_index] = ACTIONS(323),
    [anon_sym_lastIndexOf] = ACTIONS(323),
    [anon_sym_countSubStr] = ACTIONS(323),
    [anon_sym_parseJson] = ACTIONS(323),
    [anon_sym_parseCsv] = ACTIONS(323),
    [anon_sym_parseHtml] = ACTIONS(323),
    [anon_sym_parseExcel] = ACTIONS(323),
    [anon_sym_readFile] = ACTIONS(323),
    [anon_sym_readFileBytes] = ACTIONS(323),
    [anon_sym_readTsvFile] = ACTIONS(323),
    [anon_sym_writeFile] = ACTIONS(323),
    [anon_sym_appendFile] = ACTIONS(323),
    [anon_sym_fileExists] = ACTIONS(323),
    [anon_sym_isDir] = ACTIONS(323),
    [anon_sym_isFile] = ACTIONS(323),
    [anon_sym_fileSize] = ACTIONS(323),
    [anon_sym_cp] = ACTIONS(323),
    [anon_sym_mv] = ACTIONS(323),
    [anon_sym_rm] = ACTIONS(323),
    [anon_sym_rmf] = ACTIONS(323),
    [anon_sym_mkdir] = ACTIONS(323),
    [anon_sym_mkdirp] = ACTIONS(323),
    [anon_sym_cd] = ACTIONS(323),
    [anon_sym_pwd] = ACTIONS(323),
    [anon_sym_tempFile] = ACTIONS(323),
    [anon_sym_tempFileExt] = ACTIONS(323),
    [anon_sym_tempDir] = ACTIONS(323),
    [anon_sym_lsDir] = ACTIONS(323),
    [anon_sym_files] = ACTIONS(323),
    [anon_sym_dirs] = ACTIONS(323),
    [anon_sym_absPath] = ACTIONS(323),
    [anon_sym_dirname] = ACTIONS(323),
    [anon_sym_basename] = ACTIONS(323),
    [anon_sym_ext] = ACTIONS(323),
    [anon_sym_stem] = ACTIONS(323),
    [anon_sym_isCmd] = ACTIONS(323),
    [anon_sym_hardLink] = ACTIONS(323),
    [anon_sym_sha256sum] = ACTIONS(323),
    [anon_sym_md5] = ACTIONS(323),
    [anon_sym_now] = ACTIONS(323),
    [anon_sym_date] = ACTIONS(323),
    [anon_sym_year] = ACTIONS(323),
    [anon_sym_month] = ACTIONS(323),
    [anon_sym_day] = ACTIONS(323),
    [anon_sym_hour] = ACTIONS(323),
    [anon_sym_minute] = ACTIONS(323),
    [anon_sym_dateFmt] = ACTIONS(323),
    [anon_sym_isoDateFmt] = ACTIONS(323),
    [anon_sym_isoDateTimeFmt] = ACTIONS(323),
    [anon_sym_isWeekend] = ACTIONS(323),
    [anon_sym_isWeekday] = ACTIONS(323),
    [anon_sym_dow] = ACTIONS(323),
    [anon_sym_addDays] = ACTIONS(323),
    [anon_sym_toUnixTime] = ACTIONS(323),
    [anon_sym_toUnixTimeMilli] = ACTIONS(323),
    [anon_sym_toUnixTimeMicro] = ACTIONS(323),
    [anon_sym_toUnixTimeNano] = ACTIONS(323),
    [anon_sym_fromUnixTime] = ACTIONS(323),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(323),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(323),
    [anon_sym_fromUnixTimeNano] = ACTIONS(323),
    [anon_sym_toOleDate] = ACTIONS(323),
    [anon_sym_fromOleDate] = ACTIONS(323),
    [anon_sym_utcToCst] = ACTIONS(323),
    [anon_sym_cstToUtc] = ACTIONS(323),
    [anon_sym_reMatch] = ACTIONS(323),
    [anon_sym_reFindAll] = ACTIONS(323),
    [anon_sym_reFindAllIndex] = ACTIONS(323),
    [anon_sym_reReplace] = ACTIONS(323),
    [anon_sym_reSplit] = ACTIONS(323),
    [anon_sym_just] = ACTIONS(323),
    [anon_sym_none] = ACTIONS(323),
    [anon_sym_isNone] = ACTIONS(323),
    [anon_sym_maybe] = ACTIONS(323),
    [anon_sym_bind] = ACTIONS(323),
    [anon_sym_psub] = ACTIONS(323),
    [anon_sym_typeof] = ACTIONS(323),
    [anon_sym_runtime] = ACTIONS(323),
    [anon_sym_hostname] = ACTIONS(323),
    [anon_sym_httpGet] = ACTIONS(323),
    [anon_sym_httpPost] = ACTIONS(323),
    [anon_sym_urlEncode] = ACTIONS(323),
    [anon_sym_base64encode] = ACTIONS(323),
    [anon_sym_base64decode] = ACTIONS(323),
    [anon_sym_utf8Str] = ACTIONS(323),
    [anon_sym_utf8Bytes] = ACTIONS(323),
    [anon_sym_get] = ACTIONS(323),
    [anon_sym_getDef] = ACTIONS(323),
    [anon_sym_set] = ACTIONS(323),
    [anon_sym_setd] = ACTIONS(323),
    [anon_sym_keys] = ACTIONS(323),
    [anon_sym_values] = ACTIONS(323),
    [anon_sym_keyValues] = ACTIONS(323),
    [anon_sym_all] = ACTIONS(323),
    [anon_sym_any] = ACTIONS(323),
    [anon_sym_cartesian] = ACTIONS(323),
    [anon_sym_groupBy] = ACTIONS(323),
    [anon_sym_listToDict] = ACTIONS(323),
    [anon_sym_repeat] = ACTIONS(323),
    [anon_sym_seq] = ACTIONS(323),
    [anon_sym_tab] = ACTIONS(323),
    [anon_sym_select] = ACTIONS(323),
    [anon_sym_exclude] = ACTIONS(323),
    [anon_sym_derive] = ACTIONS(323),
    [anon_sym_updateCol] = ACTIONS(323),
    [anon_sym_gridValues] = ACTIONS(323),
    [anon_sym_leftJoin] = ACTIONS(323),
    [anon_sym_outerJoin] = ACTIONS(323),
    [anon_sym_linearSearch] = ACTIONS(323),
    [anon_sym_linearSearchIndex] = ACTIONS(323),
    [anon_sym_binPaths] = ACTIONS(323),
    [anon_sym_wt] = ACTIONS(323),
    [anon_sym_tt] = ACTIONS(323),
    [anon_sym_ttFile] = ACTIONS(323),
    [anon_sym_uw] = ACTIONS(323),
    [anon_sym_tuw] = ACTIONS(323),
    [anon_sym_strCmp] = ACTIONS(323),
    [anon_sym_floatCmp] = ACTIONS(323),
    [anon_sym_versionSortCmp] = ACTIONS(323),
    [anon_sym_id] = ACTIONS(323),
    [anon_sym_2id] = ACTIONS(323),
    [anon_sym_3id] = ACTIONS(323),
    [anon_sym_2unpack] = ACTIONS(323),
    [anon_sym_2apply] = ACTIONS(323),
    [anon_sym_2each] = ACTIONS(323),
    [anon_sym_2tuple] = ACTIONS(323),
    [anon_sym_DOTs] = ACTIONS(323),
    [anon_sym_DOTb] = ACTIONS(323),
    [anon_sym_DOTdef] = ACTIONS(323),
    [anon_sym_DOTenv] = ACTIONS(323),
    [sym_string] = ACTIONS(321),
    [sym_format_string] = ACTIONS(321),
    [sym_single_quoted_string] = ACTIONS(321),
    [sym_path] = ACTIONS(321),
    [sym_datetime] = ACTIONS(321),
    [sym_float] = ACTIONS(321),
    [sym_integer] = ACTIONS(323),
    [sym_env_store] = ACTIONS(321),
    [sym_env_check] = ACTIONS(321),
    [sym_env_retrieve] = ACTIONS(323),
    [sym_positional] = ACTIONS(321),
    [sym_var_retrieve] = ACTIONS(321),
    [sym_var_store] = ACTIONS(321),
    [sym_slice_indexer] = ACTIONS(321),
    [sym_indexer] = ACTIONS(321),
    [sym_end_indexer] = ACTIONS(323),
    [sym_start_indexer] = ACTIONS(323),
    [sym_match_arm_dup] = ACTIONS(321),
    [sym_prefix_quote] = ACTIONS(323),
    [anon_sym_GT] = ACTIONS(323),
    [anon_sym_GT_GT] = ACTIONS(321),
    [anon_sym_2_GT] = ACTIONS(323),
    [anon_sym_2_GT_GT] = ACTIONS(323),
    [anon_sym_AMP_GT] = ACTIONS(323),
    [anon_sym_AMP_GT_GT] = ACTIONS(321),
    [anon_sym_LT] = ACTIONS(323),
    [anon_sym_LT_GT] = ACTIONS(321),
    [anon_sym_STAR] = ACTIONS(323),
    [anon_sym_STARb] = ACTIONS(321),
    [anon_sym_CARET] = ACTIONS(323),
    [anon_sym_CARETb] = ACTIONS(321),
    [anon_sym_SEMI] = ACTIONS(321),
    [anon_sym_BANG] = ACTIONS(323),
    [anon_sym_QMARK] = ACTIONS(321),
    [anon_sym_BANG_EQ] = ACTIONS(321),
    [anon_sym_LT_EQ] = ACTIONS(321),
    [anon_sym_GT_EQ] = ACTIONS(321),
    [anon_sym_AMP] = ACTIONS(323),
    [anon_sym_PIPE] = ACTIONS(323),
    [anon_sym_COMMA] = ACTIONS(321),
    [anon_sym_COLON] = ACTIONS(323),
  },
  [40] = {
    [sym_identifier] = ACTIONS(331),
    [anon_sym_LBRACK] = ACTIONS(331),
    [anon_sym_LPAREN] = ACTIONS(329),
    [anon_sym_LBRACE] = ACTIONS(329),
    [anon_sym_LBRACK_PIPE] = ACTIONS(329),
    [anon_sym_PIPE_RBRACK] = ACTIONS(329),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(331),
    [anon_sym_false] = ACTIONS(331),
    [anon_sym_def] = ACTIONS(331),
    [anon_sym_end] = ACTIONS(331),
    [anon_sym_if] = ACTIONS(331),
    [anon_sym_iff] = ACTIONS(331),
    [anon_sym_else] = ACTIONS(331),
    [anon_sym_else_STAR] = ACTIONS(329),
    [anon_sym_STARif] = ACTIONS(329),
    [anon_sym_loop] = ACTIONS(331),
    [anon_sym_match] = ACTIONS(331),
    [anon_sym_break] = ACTIONS(331),
    [anon_sym_continue] = ACTIONS(331),
    [anon_sym_soe] = ACTIONS(331),
    [anon_sym_not] = ACTIONS(331),
    [anon_sym_and] = ACTIONS(331),
    [anon_sym_or] = ACTIONS(331),
    [anon_sym_read] = ACTIONS(331),
    [anon_sym_str] = ACTIONS(331),
    [anon_sym_as] = ACTIONS(331),
    [anon_sym_type] = ACTIONS(331),
    [anon_sym_try] = ACTIONS(331),
    [anon_sym_fail] = ACTIONS(331),
    [anon_sym_pure] = ACTIONS(331),
    [anon_sym_VER] = ACTIONS(331),
    [anon_sym_x] = ACTIONS(331),
    [anon_sym_int] = ACTIONS(331),
    [anon_sym_float] = ACTIONS(331),
    [anon_sym_bool] = ACTIONS(331),
    [anon_sym_dup] = ACTIONS(331),
    [anon_sym_swap] = ACTIONS(331),
    [anon_sym_drop] = ACTIONS(331),
    [anon_sym_over] = ACTIONS(331),
    [anon_sym_pick] = ACTIONS(331),
    [anon_sym_rot] = ACTIONS(331),
    [anon_sym_DASHrot] = ACTIONS(331),
    [anon_sym_nip] = ACTIONS(331),
    [anon_sym_w] = ACTIONS(331),
    [anon_sym_wl] = ACTIONS(331),
    [anon_sym_we] = ACTIONS(331),
    [anon_sym_wle] = ACTIONS(331),
    [anon_sym_len] = ACTIONS(331),
    [anon_sym_args] = ACTIONS(331),
    [anon_sym_glob] = ACTIONS(331),
    [anon_sym_toFloat] = ACTIONS(331),
    [anon_sym_toInt] = ACTIONS(331),
    [anon_sym_toPath] = ACTIONS(331),
    [anon_sym_toDt] = ACTIONS(331),
    [anon_sym_toGrid] = ACTIONS(331),
    [anon_sym_toCsv] = ACTIONS(331),
    [anon_sym_toCsvCell] = ACTIONS(331),
    [anon_sym_exit] = ACTIONS(331),
    [anon_sym_prompt] = ACTIONS(331),
    [anon_sym_stdin] = ACTIONS(331),
    [anon_sym_COLON_COLON] = ACTIONS(329),
    [anon_sym_foldl] = ACTIONS(331),
    [anon_sym_map] = ACTIONS(331),
    [anon_sym_each] = ACTIONS(331),
    [anon_sym_eachWhile] = ACTIONS(331),
    [anon_sym_filter] = ACTIONS(331),
    [anon_sym_append] = ACTIONS(331),
    [anon_sym_extend] = ACTIONS(331),
    [anon_sym_concat] = ACTIONS(331),
    [anon_sym_reverse] = ACTIONS(331),
    [anon_sym_sort] = ACTIONS(331),
    [anon_sym_sortV] = ACTIONS(331),
    [anon_sym_sortBy] = ACTIONS(331),
    [anon_sym_sortByCmp] = ACTIONS(331),
    [anon_sym_uniq] = ACTIONS(331),
    [anon_sym_zip] = ACTIONS(331),
    [anon_sym_enumerate] = ACTIONS(331),
    [anon_sym_enumerateN] = ACTIONS(331),
    [anon_sym_chunk] = ACTIONS(331),
    [anon_sym_pop] = ACTIONS(331),
    [anon_sym_take] = ACTIONS(331),
    [anon_sym_takeWhile] = ACTIONS(331),
    [anon_sym_skip] = ACTIONS(331),
    [anon_sym_dropWhile] = ACTIONS(331),
    [anon_sym_nth] = ACTIONS(331),
    [anon_sym_insert] = ACTIONS(331),
    [anon_sym_setAt] = ACTIONS(331),
    [anon_sym_del] = ACTIONS(331),
    [anon_sym_sum] = ACTIONS(331),
    [anon_sym_max] = ACTIONS(331),
    [anon_sym_max2] = ACTIONS(331),
    [anon_sym_min] = ACTIONS(331),
    [anon_sym_min2] = ACTIONS(331),
    [anon_sym_abs] = ACTIONS(331),
    [anon_sym_inc] = ACTIONS(331),
    [anon_sym_mod] = ACTIONS(331),
    [anon_sym_floor] = ACTIONS(331),
    [anon_sym_ceil] = ACTIONS(331),
    [anon_sym_round] = ACTIONS(331),
    [anon_sym_lines] = ACTIONS(331),
    [anon_sym_unlines] = ACTIONS(331),
    [anon_sym_unlinesCrLf] = ACTIONS(331),
    [anon_sym_split] = ACTIONS(331),
    [anon_sym_wsplit] = ACTIONS(331),
    [anon_sym_tsplit] = ACTIONS(331),
    [anon_sym_join] = ACTIONS(331),
    [anon_sym_trim] = ACTIONS(331),
    [anon_sym_trimStart] = ACTIONS(331),
    [anon_sym_trimEnd] = ACTIONS(331),
    [anon_sym_startsWith] = ACTIONS(331),
    [anon_sym_endsWith] = ACTIONS(331),
    [anon_sym_lower] = ACTIONS(331),
    [anon_sym_upper] = ACTIONS(331),
    [anon_sym_title] = ACTIONS(331),
    [anon_sym_leftPad] = ACTIONS(331),
    [anon_sym_findReplace] = ACTIONS(331),
    [anon_sym_in] = ACTIONS(331),
    [anon_sym_index] = ACTIONS(331),
    [anon_sym_lastIndexOf] = ACTIONS(331),
    [anon_sym_countSubStr] = ACTIONS(331),
    [anon_sym_parseJson] = ACTIONS(331),
    [anon_sym_parseCsv] = ACTIONS(331),
    [anon_sym_parseHtml] = ACTIONS(331),
    [anon_sym_parseExcel] = ACTIONS(331),
    [anon_sym_readFile] = ACTIONS(331),
    [anon_sym_readFileBytes] = ACTIONS(331),
    [anon_sym_readTsvFile] = ACTIONS(331),
    [anon_sym_writeFile] = ACTIONS(331),
    [anon_sym_appendFile] = ACTIONS(331),
    [anon_sym_fileExists] = ACTIONS(331),
    [anon_sym_isDir] = ACTIONS(331),
    [anon_sym_isFile] = ACTIONS(331),
    [anon_sym_fileSize] = ACTIONS(331),
    [anon_sym_cp] = ACTIONS(331),
    [anon_sym_mv] = ACTIONS(331),
    [anon_sym_rm] = ACTIONS(331),
    [anon_sym_rmf] = ACTIONS(331),
    [anon_sym_mkdir] = ACTIONS(331),
    [anon_sym_mkdirp] = ACTIONS(331),
    [anon_sym_cd] = ACTIONS(331),
    [anon_sym_pwd] = ACTIONS(331),
    [anon_sym_tempFile] = ACTIONS(331),
    [anon_sym_tempFileExt] = ACTIONS(331),
    [anon_sym_tempDir] = ACTIONS(331),
    [anon_sym_lsDir] = ACTIONS(331),
    [anon_sym_files] = ACTIONS(331),
    [anon_sym_dirs] = ACTIONS(331),
    [anon_sym_absPath] = ACTIONS(331),
    [anon_sym_dirname] = ACTIONS(331),
    [anon_sym_basename] = ACTIONS(331),
    [anon_sym_ext] = ACTIONS(331),
    [anon_sym_stem] = ACTIONS(331),
    [anon_sym_isCmd] = ACTIONS(331),
    [anon_sym_hardLink] = ACTIONS(331),
    [anon_sym_sha256sum] = ACTIONS(331),
    [anon_sym_md5] = ACTIONS(331),
    [anon_sym_now] = ACTIONS(331),
    [anon_sym_date] = ACTIONS(331),
    [anon_sym_year] = ACTIONS(331),
    [anon_sym_month] = ACTIONS(331),
    [anon_sym_day] = ACTIONS(331),
    [anon_sym_hour] = ACTIONS(331),
    [anon_sym_minute] = ACTIONS(331),
    [anon_sym_dateFmt] = ACTIONS(331),
    [anon_sym_isoDateFmt] = ACTIONS(331),
    [anon_sym_isoDateTimeFmt] = ACTIONS(331),
    [anon_sym_isWeekend] = ACTIONS(331),
    [anon_sym_isWeekday] = ACTIONS(331),
    [anon_sym_dow] = ACTIONS(331),
    [anon_sym_addDays] = ACTIONS(331),
    [anon_sym_toUnixTime] = ACTIONS(331),
    [anon_sym_toUnixTimeMilli] = ACTIONS(331),
    [anon_sym_toUnixTimeMicro] = ACTIONS(331),
    [anon_sym_toUnixTimeNano] = ACTIONS(331),
    [anon_sym_fromUnixTime] = ACTIONS(331),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(331),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(331),
    [anon_sym_fromUnixTimeNano] = ACTIONS(331),
    [anon_sym_toOleDate] = ACTIONS(331),
    [anon_sym_fromOleDate] = ACTIONS(331),
    [anon_sym_utcToCst] = ACTIONS(331),
    [anon_sym_cstToUtc] = ACTIONS(331),
    [anon_sym_reMatch] = ACTIONS(331),
    [anon_sym_reFindAll] = ACTIONS(331),
    [anon_sym_reFindAllIndex] = ACTIONS(331),
    [anon_sym_reReplace] = ACTIONS(331),
    [anon_sym_reSplit] = ACTIONS(331),
    [anon_sym_just] = ACTIONS(331),
    [anon_sym_none] = ACTIONS(331),
    [anon_sym_isNone] = ACTIONS(331),
    [anon_sym_maybe] = ACTIONS(331),
    [anon_sym_bind] = ACTIONS(331),
    [anon_sym_psub] = ACTIONS(331),
    [anon_sym_typeof] = ACTIONS(331),
    [anon_sym_runtime] = ACTIONS(331),
    [anon_sym_hostname] = ACTIONS(331),
    [anon_sym_httpGet] = ACTIONS(331),
    [anon_sym_httpPost] = ACTIONS(331),
    [anon_sym_urlEncode] = ACTIONS(331),
    [anon_sym_base64encode] = ACTIONS(331),
    [anon_sym_base64decode] = ACTIONS(331),
    [anon_sym_utf8Str] = ACTIONS(331),
    [anon_sym_utf8Bytes] = ACTIONS(331),
    [anon_sym_get] = ACTIONS(331),
    [anon_sym_getDef] = ACTIONS(331),
    [anon_sym_set] = ACTIONS(331),
    [anon_sym_setd] = ACTIONS(331),
    [anon_sym_keys] = ACTIONS(331),
    [anon_sym_values] = ACTIONS(331),
    [anon_sym_keyValues] = ACTIONS(331),
    [anon_sym_all] = ACTIONS(331),
    [anon_sym_any] = ACTIONS(331),
    [anon_sym_cartesian] = ACTIONS(331),
    [anon_sym_groupBy] = ACTIONS(331),
    [anon_sym_listToDict] = ACTIONS(331),
    [anon_sym_repeat] = ACTIONS(331),
    [anon_sym_seq] = ACTIONS(331),
    [anon_sym_tab] = ACTIONS(331),
    [anon_sym_select] = ACTIONS(331),
    [anon_sym_exclude] = ACTIONS(331),
    [anon_sym_derive] = ACTIONS(331),
    [anon_sym_updateCol] = ACTIONS(331),
    [anon_sym_gridValues] = ACTIONS(331),
    [anon_sym_leftJoin] = ACTIONS(331),
    [anon_sym_outerJoin] = ACTIONS(331),
    [anon_sym_linearSearch] = ACTIONS(331),
    [anon_sym_linearSearchIndex] = ACTIONS(331),
    [anon_sym_binPaths] = ACTIONS(331),
    [anon_sym_wt] = ACTIONS(331),
    [anon_sym_tt] = ACTIONS(331),
    [anon_sym_ttFile] = ACTIONS(331),
    [anon_sym_uw] = ACTIONS(331),
    [anon_sym_tuw] = ACTIONS(331),
    [anon_sym_strCmp] = ACTIONS(331),
    [anon_sym_floatCmp] = ACTIONS(331),
    [anon_sym_versionSortCmp] = ACTIONS(331),
    [anon_sym_id] = ACTIONS(331),
    [anon_sym_2id] = ACTIONS(331),
    [anon_sym_3id] = ACTIONS(331),
    [anon_sym_2unpack] = ACTIONS(331),
    [anon_sym_2apply] = ACTIONS(331),
    [anon_sym_2each] = ACTIONS(331),
    [anon_sym_2tuple] = ACTIONS(331),
    [anon_sym_DOTs] = ACTIONS(331),
    [anon_sym_DOTb] = ACTIONS(331),
    [anon_sym_DOTdef] = ACTIONS(331),
    [anon_sym_DOTenv] = ACTIONS(331),
    [sym_string] = ACTIONS(329),
    [sym_format_string] = ACTIONS(329),
    [sym_single_quoted_string] = ACTIONS(329),
    [sym_path] = ACTIONS(329),
    [sym_datetime] = ACTIONS(329),
    [sym_float] = ACTIONS(329),
    [sym_integer] = ACTIONS(331),
    [sym_env_store] = ACTIONS(329),
    [sym_env_check] = ACTIONS(329),
    [sym_env_retrieve] = ACTIONS(331),
    [sym_positional] = ACTIONS(329),
    [sym_var_retrieve] = ACTIONS(329),
    [sym_var_store] = ACTIONS(329),
    [sym_slice_indexer] = ACTIONS(329),
    [sym_indexer] = ACTIONS(329),
    [sym_end_indexer] = ACTIONS(331),
    [sym_start_indexer] = ACTIONS(331),
    [sym_match_arm_dup] = ACTIONS(329),
    [sym_prefix_quote] = ACTIONS(331),
    [anon_sym_GT] = ACTIONS(331),
    [anon_sym_GT_GT] = ACTIONS(329),
    [anon_sym_2_GT] = ACTIONS(331),
    [anon_sym_2_GT_GT] = ACTIONS(331),
    [anon_sym_AMP_GT] = ACTIONS(331),
    [anon_sym_AMP_GT_GT] = ACTIONS(329),
    [anon_sym_LT] = ACTIONS(331),
    [anon_sym_LT_GT] = ACTIONS(329),
    [anon_sym_STAR] = ACTIONS(331),
    [anon_sym_STARb] = ACTIONS(329),
    [anon_sym_CARET] = ACTIONS(331),
    [anon_sym_CARETb] = ACTIONS(329),
    [anon_sym_SEMI] = ACTIONS(329),
    [anon_sym_BANG] = ACTIONS(331),
    [anon_sym_QMARK] = ACTIONS(329),
    [anon_sym_BANG_EQ] = ACTIONS(329),
    [anon_sym_LT_EQ] = ACTIONS(329),
    [anon_sym_GT_EQ] = ACTIONS(329),
    [anon_sym_AMP] = ACTIONS(331),
    [anon_sym_PIPE] = ACTIONS(331),
    [anon_sym_COMMA] = ACTIONS(329),
    [anon_sym_COLON] = ACTIONS(331),
  },
  [41] = {
    [sym_identifier] = ACTIONS(279),
    [anon_sym_LBRACK] = ACTIONS(279),
    [anon_sym_LPAREN] = ACTIONS(277),
    [anon_sym_LBRACE] = ACTIONS(277),
    [anon_sym_LBRACK_PIPE] = ACTIONS(277),
    [anon_sym_PIPE_RBRACK] = ACTIONS(277),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(279),
    [anon_sym_false] = ACTIONS(279),
    [anon_sym_def] = ACTIONS(279),
    [anon_sym_end] = ACTIONS(279),
    [anon_sym_if] = ACTIONS(279),
    [anon_sym_iff] = ACTIONS(279),
    [anon_sym_else] = ACTIONS(279),
    [anon_sym_else_STAR] = ACTIONS(277),
    [anon_sym_STARif] = ACTIONS(277),
    [anon_sym_loop] = ACTIONS(279),
    [anon_sym_match] = ACTIONS(279),
    [anon_sym_break] = ACTIONS(279),
    [anon_sym_continue] = ACTIONS(279),
    [anon_sym_soe] = ACTIONS(279),
    [anon_sym_not] = ACTIONS(279),
    [anon_sym_and] = ACTIONS(279),
    [anon_sym_or] = ACTIONS(279),
    [anon_sym_read] = ACTIONS(279),
    [anon_sym_str] = ACTIONS(279),
    [anon_sym_as] = ACTIONS(279),
    [anon_sym_type] = ACTIONS(279),
    [anon_sym_try] = ACTIONS(279),
    [anon_sym_fail] = ACTIONS(279),
    [anon_sym_pure] = ACTIONS(279),
    [anon_sym_VER] = ACTIONS(279),
    [anon_sym_x] = ACTIONS(279),
    [anon_sym_int] = ACTIONS(279),
    [anon_sym_float] = ACTIONS(279),
    [anon_sym_bool] = ACTIONS(279),
    [anon_sym_dup] = ACTIONS(279),
    [anon_sym_swap] = ACTIONS(279),
    [anon_sym_drop] = ACTIONS(279),
    [anon_sym_over] = ACTIONS(279),
    [anon_sym_pick] = ACTIONS(279),
    [anon_sym_rot] = ACTIONS(279),
    [anon_sym_DASHrot] = ACTIONS(279),
    [anon_sym_nip] = ACTIONS(279),
    [anon_sym_w] = ACTIONS(279),
    [anon_sym_wl] = ACTIONS(279),
    [anon_sym_we] = ACTIONS(279),
    [anon_sym_wle] = ACTIONS(279),
    [anon_sym_len] = ACTIONS(279),
    [anon_sym_args] = ACTIONS(279),
    [anon_sym_glob] = ACTIONS(279),
    [anon_sym_toFloat] = ACTIONS(279),
    [anon_sym_toInt] = ACTIONS(279),
    [anon_sym_toPath] = ACTIONS(279),
    [anon_sym_toDt] = ACTIONS(279),
    [anon_sym_toGrid] = ACTIONS(279),
    [anon_sym_toCsv] = ACTIONS(279),
    [anon_sym_toCsvCell] = ACTIONS(279),
    [anon_sym_exit] = ACTIONS(279),
    [anon_sym_prompt] = ACTIONS(279),
    [anon_sym_stdin] = ACTIONS(279),
    [anon_sym_COLON_COLON] = ACTIONS(277),
    [anon_sym_foldl] = ACTIONS(279),
    [anon_sym_map] = ACTIONS(279),
    [anon_sym_each] = ACTIONS(279),
    [anon_sym_eachWhile] = ACTIONS(279),
    [anon_sym_filter] = ACTIONS(279),
    [anon_sym_append] = ACTIONS(279),
    [anon_sym_extend] = ACTIONS(279),
    [anon_sym_concat] = ACTIONS(279),
    [anon_sym_reverse] = ACTIONS(279),
    [anon_sym_sort] = ACTIONS(279),
    [anon_sym_sortV] = ACTIONS(279),
    [anon_sym_sortBy] = ACTIONS(279),
    [anon_sym_sortByCmp] = ACTIONS(279),
    [anon_sym_uniq] = ACTIONS(279),
    [anon_sym_zip] = ACTIONS(279),
    [anon_sym_enumerate] = ACTIONS(279),
    [anon_sym_enumerateN] = ACTIONS(279),
    [anon_sym_chunk] = ACTIONS(279),
    [anon_sym_pop] = ACTIONS(279),
    [anon_sym_take] = ACTIONS(279),
    [anon_sym_takeWhile] = ACTIONS(279),
    [anon_sym_skip] = ACTIONS(279),
    [anon_sym_dropWhile] = ACTIONS(279),
    [anon_sym_nth] = ACTIONS(279),
    [anon_sym_insert] = ACTIONS(279),
    [anon_sym_setAt] = ACTIONS(279),
    [anon_sym_del] = ACTIONS(279),
    [anon_sym_sum] = ACTIONS(279),
    [anon_sym_max] = ACTIONS(279),
    [anon_sym_max2] = ACTIONS(279),
    [anon_sym_min] = ACTIONS(279),
    [anon_sym_min2] = ACTIONS(279),
    [anon_sym_abs] = ACTIONS(279),
    [anon_sym_inc] = ACTIONS(279),
    [anon_sym_mod] = ACTIONS(279),
    [anon_sym_floor] = ACTIONS(279),
    [anon_sym_ceil] = ACTIONS(279),
    [anon_sym_round] = ACTIONS(279),
    [anon_sym_lines] = ACTIONS(279),
    [anon_sym_unlines] = ACTIONS(279),
    [anon_sym_unlinesCrLf] = ACTIONS(279),
    [anon_sym_split] = ACTIONS(279),
    [anon_sym_wsplit] = ACTIONS(279),
    [anon_sym_tsplit] = ACTIONS(279),
    [anon_sym_join] = ACTIONS(279),
    [anon_sym_trim] = ACTIONS(279),
    [anon_sym_trimStart] = ACTIONS(279),
    [anon_sym_trimEnd] = ACTIONS(279),
    [anon_sym_startsWith] = ACTIONS(279),
    [anon_sym_endsWith] = ACTIONS(279),
    [anon_sym_lower] = ACTIONS(279),
    [anon_sym_upper] = ACTIONS(279),
    [anon_sym_title] = ACTIONS(279),
    [anon_sym_leftPad] = ACTIONS(279),
    [anon_sym_findReplace] = ACTIONS(279),
    [anon_sym_in] = ACTIONS(279),
    [anon_sym_index] = ACTIONS(279),
    [anon_sym_lastIndexOf] = ACTIONS(279),
    [anon_sym_countSubStr] = ACTIONS(279),
    [anon_sym_parseJson] = ACTIONS(279),
    [anon_sym_parseCsv] = ACTIONS(279),
    [anon_sym_parseHtml] = ACTIONS(279),
    [anon_sym_parseExcel] = ACTIONS(279),
    [anon_sym_readFile] = ACTIONS(279),
    [anon_sym_readFileBytes] = ACTIONS(279),
    [anon_sym_readTsvFile] = ACTIONS(279),
    [anon_sym_writeFile] = ACTIONS(279),
    [anon_sym_appendFile] = ACTIONS(279),
    [anon_sym_fileExists] = ACTIONS(279),
    [anon_sym_isDir] = ACTIONS(279),
    [anon_sym_isFile] = ACTIONS(279),
    [anon_sym_fileSize] = ACTIONS(279),
    [anon_sym_cp] = ACTIONS(279),
    [anon_sym_mv] = ACTIONS(279),
    [anon_sym_rm] = ACTIONS(279),
    [anon_sym_rmf] = ACTIONS(279),
    [anon_sym_mkdir] = ACTIONS(279),
    [anon_sym_mkdirp] = ACTIONS(279),
    [anon_sym_cd] = ACTIONS(279),
    [anon_sym_pwd] = ACTIONS(279),
    [anon_sym_tempFile] = ACTIONS(279),
    [anon_sym_tempFileExt] = ACTIONS(279),
    [anon_sym_tempDir] = ACTIONS(279),
    [anon_sym_lsDir] = ACTIONS(279),
    [anon_sym_files] = ACTIONS(279),
    [anon_sym_dirs] = ACTIONS(279),
    [anon_sym_absPath] = ACTIONS(279),
    [anon_sym_dirname] = ACTIONS(279),
    [anon_sym_basename] = ACTIONS(279),
    [anon_sym_ext] = ACTIONS(279),
    [anon_sym_stem] = ACTIONS(279),
    [anon_sym_isCmd] = ACTIONS(279),
    [anon_sym_hardLink] = ACTIONS(279),
    [anon_sym_sha256sum] = ACTIONS(279),
    [anon_sym_md5] = ACTIONS(279),
    [anon_sym_now] = ACTIONS(279),
    [anon_sym_date] = ACTIONS(279),
    [anon_sym_year] = ACTIONS(279),
    [anon_sym_month] = ACTIONS(279),
    [anon_sym_day] = ACTIONS(279),
    [anon_sym_hour] = ACTIONS(279),
    [anon_sym_minute] = ACTIONS(279),
    [anon_sym_dateFmt] = ACTIONS(279),
    [anon_sym_isoDateFmt] = ACTIONS(279),
    [anon_sym_isoDateTimeFmt] = ACTIONS(279),
    [anon_sym_isWeekend] = ACTIONS(279),
    [anon_sym_isWeekday] = ACTIONS(279),
    [anon_sym_dow] = ACTIONS(279),
    [anon_sym_addDays] = ACTIONS(279),
    [anon_sym_toUnixTime] = ACTIONS(279),
    [anon_sym_toUnixTimeMilli] = ACTIONS(279),
    [anon_sym_toUnixTimeMicro] = ACTIONS(279),
    [anon_sym_toUnixTimeNano] = ACTIONS(279),
    [anon_sym_fromUnixTime] = ACTIONS(279),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(279),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(279),
    [anon_sym_fromUnixTimeNano] = ACTIONS(279),
    [anon_sym_toOleDate] = ACTIONS(279),
    [anon_sym_fromOleDate] = ACTIONS(279),
    [anon_sym_utcToCst] = ACTIONS(279),
    [anon_sym_cstToUtc] = ACTIONS(279),
    [anon_sym_reMatch] = ACTIONS(279),
    [anon_sym_reFindAll] = ACTIONS(279),
    [anon_sym_reFindAllIndex] = ACTIONS(279),
    [anon_sym_reReplace] = ACTIONS(279),
    [anon_sym_reSplit] = ACTIONS(279),
    [anon_sym_just] = ACTIONS(279),
    [anon_sym_none] = ACTIONS(279),
    [anon_sym_isNone] = ACTIONS(279),
    [anon_sym_maybe] = ACTIONS(279),
    [anon_sym_bind] = ACTIONS(279),
    [anon_sym_psub] = ACTIONS(279),
    [anon_sym_typeof] = ACTIONS(279),
    [anon_sym_runtime] = ACTIONS(279),
    [anon_sym_hostname] = ACTIONS(279),
    [anon_sym_httpGet] = ACTIONS(279),
    [anon_sym_httpPost] = ACTIONS(279),
    [anon_sym_urlEncode] = ACTIONS(279),
    [anon_sym_base64encode] = ACTIONS(279),
    [anon_sym_base64decode] = ACTIONS(279),
    [anon_sym_utf8Str] = ACTIONS(279),
    [anon_sym_utf8Bytes] = ACTIONS(279),
    [anon_sym_get] = ACTIONS(279),
    [anon_sym_getDef] = ACTIONS(279),
    [anon_sym_set] = ACTIONS(279),
    [anon_sym_setd] = ACTIONS(279),
    [anon_sym_keys] = ACTIONS(279),
    [anon_sym_values] = ACTIONS(279),
    [anon_sym_keyValues] = ACTIONS(279),
    [anon_sym_all] = ACTIONS(279),
    [anon_sym_any] = ACTIONS(279),
    [anon_sym_cartesian] = ACTIONS(279),
    [anon_sym_groupBy] = ACTIONS(279),
    [anon_sym_listToDict] = ACTIONS(279),
    [anon_sym_repeat] = ACTIONS(279),
    [anon_sym_seq] = ACTIONS(279),
    [anon_sym_tab] = ACTIONS(279),
    [anon_sym_select] = ACTIONS(279),
    [anon_sym_exclude] = ACTIONS(279),
    [anon_sym_derive] = ACTIONS(279),
    [anon_sym_updateCol] = ACTIONS(279),
    [anon_sym_gridValues] = ACTIONS(279),
    [anon_sym_leftJoin] = ACTIONS(279),
    [anon_sym_outerJoin] = ACTIONS(279),
    [anon_sym_linearSearch] = ACTIONS(279),
    [anon_sym_linearSearchIndex] = ACTIONS(279),
    [anon_sym_binPaths] = ACTIONS(279),
    [anon_sym_wt] = ACTIONS(279),
    [anon_sym_tt] = ACTIONS(279),
    [anon_sym_ttFile] = ACTIONS(279),
    [anon_sym_uw] = ACTIONS(279),
    [anon_sym_tuw] = ACTIONS(279),
    [anon_sym_strCmp] = ACTIONS(279),
    [anon_sym_floatCmp] = ACTIONS(279),
    [anon_sym_versionSortCmp] = ACTIONS(279),
    [anon_sym_id] = ACTIONS(279),
    [anon_sym_2id] = ACTIONS(279),
    [anon_sym_3id] = ACTIONS(279),
    [anon_sym_2unpack] = ACTIONS(279),
    [anon_sym_2apply] = ACTIONS(279),
    [anon_sym_2each] = ACTIONS(279),
    [anon_sym_2tuple] = ACTIONS(279),
    [anon_sym_DOTs] = ACTIONS(279),
    [anon_sym_DOTb] = ACTIONS(279),
    [anon_sym_DOTdef] = ACTIONS(279),
    [anon_sym_DOTenv] = ACTIONS(279),
    [sym_string] = ACTIONS(277),
    [sym_format_string] = ACTIONS(277),
    [sym_single_quoted_string] = ACTIONS(277),
    [sym_path] = ACTIONS(277),
    [sym_datetime] = ACTIONS(277),
    [sym_float] = ACTIONS(277),
    [sym_integer] = ACTIONS(279),
    [sym_env_store] = ACTIONS(277),
    [sym_env_check] = ACTIONS(277),
    [sym_env_retrieve] = ACTIONS(279),
    [sym_positional] = ACTIONS(277),
    [sym_var_retrieve] = ACTIONS(277),
    [sym_var_store] = ACTIONS(277),
    [sym_slice_indexer] = ACTIONS(277),
    [sym_indexer] = ACTIONS(277),
    [sym_end_indexer] = ACTIONS(279),
    [sym_start_indexer] = ACTIONS(279),
    [sym_match_arm_dup] = ACTIONS(277),
    [sym_prefix_quote] = ACTIONS(279),
    [anon_sym_GT] = ACTIONS(279),
    [anon_sym_GT_GT] = ACTIONS(277),
    [anon_sym_2_GT] = ACTIONS(279),
    [anon_sym_2_GT_GT] = ACTIONS(279),
    [anon_sym_AMP_GT] = ACTIONS(279),
    [anon_sym_AMP_GT_GT] = ACTIONS(277),
    [anon_sym_LT] = ACTIONS(279),
    [anon_sym_LT_GT] = ACTIONS(277),
    [anon_sym_STAR] = ACTIONS(279),
    [anon_sym_STARb] = ACTIONS(277),
    [anon_sym_CARET] = ACTIONS(279),
    [anon_sym_CARETb] = ACTIONS(277),
    [anon_sym_SEMI] = ACTIONS(277),
    [anon_sym_BANG] = ACTIONS(279),
    [anon_sym_QMARK] = ACTIONS(277),
    [anon_sym_BANG_EQ] = ACTIONS(277),
    [anon_sym_LT_EQ] = ACTIONS(277),
    [anon_sym_GT_EQ] = ACTIONS(277),
    [anon_sym_AMP] = ACTIONS(279),
    [anon_sym_PIPE] = ACTIONS(279),
    [anon_sym_COMMA] = ACTIONS(277),
    [anon_sym_COLON] = ACTIONS(279),
  },
  [42] = {
    [sym_identifier] = ACTIONS(283),
    [anon_sym_LBRACK] = ACTIONS(283),
    [anon_sym_LPAREN] = ACTIONS(281),
    [anon_sym_LBRACE] = ACTIONS(281),
    [anon_sym_LBRACK_PIPE] = ACTIONS(281),
    [anon_sym_PIPE_RBRACK] = ACTIONS(281),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(283),
    [anon_sym_false] = ACTIONS(283),
    [anon_sym_def] = ACTIONS(283),
    [anon_sym_end] = ACTIONS(283),
    [anon_sym_if] = ACTIONS(283),
    [anon_sym_iff] = ACTIONS(283),
    [anon_sym_else] = ACTIONS(283),
    [anon_sym_else_STAR] = ACTIONS(281),
    [anon_sym_STARif] = ACTIONS(281),
    [anon_sym_loop] = ACTIONS(283),
    [anon_sym_match] = ACTIONS(283),
    [anon_sym_break] = ACTIONS(283),
    [anon_sym_continue] = ACTIONS(283),
    [anon_sym_soe] = ACTIONS(283),
    [anon_sym_not] = ACTIONS(283),
    [anon_sym_and] = ACTIONS(283),
    [anon_sym_or] = ACTIONS(283),
    [anon_sym_read] = ACTIONS(283),
    [anon_sym_str] = ACTIONS(283),
    [anon_sym_as] = ACTIONS(283),
    [anon_sym_type] = ACTIONS(283),
    [anon_sym_try] = ACTIONS(283),
    [anon_sym_fail] = ACTIONS(283),
    [anon_sym_pure] = ACTIONS(283),
    [anon_sym_VER] = ACTIONS(283),
    [anon_sym_x] = ACTIONS(283),
    [anon_sym_int] = ACTIONS(283),
    [anon_sym_float] = ACTIONS(283),
    [anon_sym_bool] = ACTIONS(283),
    [anon_sym_dup] = ACTIONS(283),
    [anon_sym_swap] = ACTIONS(283),
    [anon_sym_drop] = ACTIONS(283),
    [anon_sym_over] = ACTIONS(283),
    [anon_sym_pick] = ACTIONS(283),
    [anon_sym_rot] = ACTIONS(283),
    [anon_sym_DASHrot] = ACTIONS(283),
    [anon_sym_nip] = ACTIONS(283),
    [anon_sym_w] = ACTIONS(283),
    [anon_sym_wl] = ACTIONS(283),
    [anon_sym_we] = ACTIONS(283),
    [anon_sym_wle] = ACTIONS(283),
    [anon_sym_len] = ACTIONS(283),
    [anon_sym_args] = ACTIONS(283),
    [anon_sym_glob] = ACTIONS(283),
    [anon_sym_toFloat] = ACTIONS(283),
    [anon_sym_toInt] = ACTIONS(283),
    [anon_sym_toPath] = ACTIONS(283),
    [anon_sym_toDt] = ACTIONS(283),
    [anon_sym_toGrid] = ACTIONS(283),
    [anon_sym_toCsv] = ACTIONS(283),
    [anon_sym_toCsvCell] = ACTIONS(283),
    [anon_sym_exit] = ACTIONS(283),
    [anon_sym_prompt] = ACTIONS(283),
    [anon_sym_stdin] = ACTIONS(283),
    [anon_sym_COLON_COLON] = ACTIONS(281),
    [anon_sym_foldl] = ACTIONS(283),
    [anon_sym_map] = ACTIONS(283),
    [anon_sym_each] = ACTIONS(283),
    [anon_sym_eachWhile] = ACTIONS(283),
    [anon_sym_filter] = ACTIONS(283),
    [anon_sym_append] = ACTIONS(283),
    [anon_sym_extend] = ACTIONS(283),
    [anon_sym_concat] = ACTIONS(283),
    [anon_sym_reverse] = ACTIONS(283),
    [anon_sym_sort] = ACTIONS(283),
    [anon_sym_sortV] = ACTIONS(283),
    [anon_sym_sortBy] = ACTIONS(283),
    [anon_sym_sortByCmp] = ACTIONS(283),
    [anon_sym_uniq] = ACTIONS(283),
    [anon_sym_zip] = ACTIONS(283),
    [anon_sym_enumerate] = ACTIONS(283),
    [anon_sym_enumerateN] = ACTIONS(283),
    [anon_sym_chunk] = ACTIONS(283),
    [anon_sym_pop] = ACTIONS(283),
    [anon_sym_take] = ACTIONS(283),
    [anon_sym_takeWhile] = ACTIONS(283),
    [anon_sym_skip] = ACTIONS(283),
    [anon_sym_dropWhile] = ACTIONS(283),
    [anon_sym_nth] = ACTIONS(283),
    [anon_sym_insert] = ACTIONS(283),
    [anon_sym_setAt] = ACTIONS(283),
    [anon_sym_del] = ACTIONS(283),
    [anon_sym_sum] = ACTIONS(283),
    [anon_sym_max] = ACTIONS(283),
    [anon_sym_max2] = ACTIONS(283),
    [anon_sym_min] = ACTIONS(283),
    [anon_sym_min2] = ACTIONS(283),
    [anon_sym_abs] = ACTIONS(283),
    [anon_sym_inc] = ACTIONS(283),
    [anon_sym_mod] = ACTIONS(283),
    [anon_sym_floor] = ACTIONS(283),
    [anon_sym_ceil] = ACTIONS(283),
    [anon_sym_round] = ACTIONS(283),
    [anon_sym_lines] = ACTIONS(283),
    [anon_sym_unlines] = ACTIONS(283),
    [anon_sym_unlinesCrLf] = ACTIONS(283),
    [anon_sym_split] = ACTIONS(283),
    [anon_sym_wsplit] = ACTIONS(283),
    [anon_sym_tsplit] = ACTIONS(283),
    [anon_sym_join] = ACTIONS(283),
    [anon_sym_trim] = ACTIONS(283),
    [anon_sym_trimStart] = ACTIONS(283),
    [anon_sym_trimEnd] = ACTIONS(283),
    [anon_sym_startsWith] = ACTIONS(283),
    [anon_sym_endsWith] = ACTIONS(283),
    [anon_sym_lower] = ACTIONS(283),
    [anon_sym_upper] = ACTIONS(283),
    [anon_sym_title] = ACTIONS(283),
    [anon_sym_leftPad] = ACTIONS(283),
    [anon_sym_findReplace] = ACTIONS(283),
    [anon_sym_in] = ACTIONS(283),
    [anon_sym_index] = ACTIONS(283),
    [anon_sym_lastIndexOf] = ACTIONS(283),
    [anon_sym_countSubStr] = ACTIONS(283),
    [anon_sym_parseJson] = ACTIONS(283),
    [anon_sym_parseCsv] = ACTIONS(283),
    [anon_sym_parseHtml] = ACTIONS(283),
    [anon_sym_parseExcel] = ACTIONS(283),
    [anon_sym_readFile] = ACTIONS(283),
    [anon_sym_readFileBytes] = ACTIONS(283),
    [anon_sym_readTsvFile] = ACTIONS(283),
    [anon_sym_writeFile] = ACTIONS(283),
    [anon_sym_appendFile] = ACTIONS(283),
    [anon_sym_fileExists] = ACTIONS(283),
    [anon_sym_isDir] = ACTIONS(283),
    [anon_sym_isFile] = ACTIONS(283),
    [anon_sym_fileSize] = ACTIONS(283),
    [anon_sym_cp] = ACTIONS(283),
    [anon_sym_mv] = ACTIONS(283),
    [anon_sym_rm] = ACTIONS(283),
    [anon_sym_rmf] = ACTIONS(283),
    [anon_sym_mkdir] = ACTIONS(283),
    [anon_sym_mkdirp] = ACTIONS(283),
    [anon_sym_cd] = ACTIONS(283),
    [anon_sym_pwd] = ACTIONS(283),
    [anon_sym_tempFile] = ACTIONS(283),
    [anon_sym_tempFileExt] = ACTIONS(283),
    [anon_sym_tempDir] = ACTIONS(283),
    [anon_sym_lsDir] = ACTIONS(283),
    [anon_sym_files] = ACTIONS(283),
    [anon_sym_dirs] = ACTIONS(283),
    [anon_sym_absPath] = ACTIONS(283),
    [anon_sym_dirname] = ACTIONS(283),
    [anon_sym_basename] = ACTIONS(283),
    [anon_sym_ext] = ACTIONS(283),
    [anon_sym_stem] = ACTIONS(283),
    [anon_sym_isCmd] = ACTIONS(283),
    [anon_sym_hardLink] = ACTIONS(283),
    [anon_sym_sha256sum] = ACTIONS(283),
    [anon_sym_md5] = ACTIONS(283),
    [anon_sym_now] = ACTIONS(283),
    [anon_sym_date] = ACTIONS(283),
    [anon_sym_year] = ACTIONS(283),
    [anon_sym_month] = ACTIONS(283),
    [anon_sym_day] = ACTIONS(283),
    [anon_sym_hour] = ACTIONS(283),
    [anon_sym_minute] = ACTIONS(283),
    [anon_sym_dateFmt] = ACTIONS(283),
    [anon_sym_isoDateFmt] = ACTIONS(283),
    [anon_sym_isoDateTimeFmt] = ACTIONS(283),
    [anon_sym_isWeekend] = ACTIONS(283),
    [anon_sym_isWeekday] = ACTIONS(283),
    [anon_sym_dow] = ACTIONS(283),
    [anon_sym_addDays] = ACTIONS(283),
    [anon_sym_toUnixTime] = ACTIONS(283),
    [anon_sym_toUnixTimeMilli] = ACTIONS(283),
    [anon_sym_toUnixTimeMicro] = ACTIONS(283),
    [anon_sym_toUnixTimeNano] = ACTIONS(283),
    [anon_sym_fromUnixTime] = ACTIONS(283),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(283),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(283),
    [anon_sym_fromUnixTimeNano] = ACTIONS(283),
    [anon_sym_toOleDate] = ACTIONS(283),
    [anon_sym_fromOleDate] = ACTIONS(283),
    [anon_sym_utcToCst] = ACTIONS(283),
    [anon_sym_cstToUtc] = ACTIONS(283),
    [anon_sym_reMatch] = ACTIONS(283),
    [anon_sym_reFindAll] = ACTIONS(283),
    [anon_sym_reFindAllIndex] = ACTIONS(283),
    [anon_sym_reReplace] = ACTIONS(283),
    [anon_sym_reSplit] = ACTIONS(283),
    [anon_sym_just] = ACTIONS(283),
    [anon_sym_none] = ACTIONS(283),
    [anon_sym_isNone] = ACTIONS(283),
    [anon_sym_maybe] = ACTIONS(283),
    [anon_sym_bind] = ACTIONS(283),
    [anon_sym_psub] = ACTIONS(283),
    [anon_sym_typeof] = ACTIONS(283),
    [anon_sym_runtime] = ACTIONS(283),
    [anon_sym_hostname] = ACTIONS(283),
    [anon_sym_httpGet] = ACTIONS(283),
    [anon_sym_httpPost] = ACTIONS(283),
    [anon_sym_urlEncode] = ACTIONS(283),
    [anon_sym_base64encode] = ACTIONS(283),
    [anon_sym_base64decode] = ACTIONS(283),
    [anon_sym_utf8Str] = ACTIONS(283),
    [anon_sym_utf8Bytes] = ACTIONS(283),
    [anon_sym_get] = ACTIONS(283),
    [anon_sym_getDef] = ACTIONS(283),
    [anon_sym_set] = ACTIONS(283),
    [anon_sym_setd] = ACTIONS(283),
    [anon_sym_keys] = ACTIONS(283),
    [anon_sym_values] = ACTIONS(283),
    [anon_sym_keyValues] = ACTIONS(283),
    [anon_sym_all] = ACTIONS(283),
    [anon_sym_any] = ACTIONS(283),
    [anon_sym_cartesian] = ACTIONS(283),
    [anon_sym_groupBy] = ACTIONS(283),
    [anon_sym_listToDict] = ACTIONS(283),
    [anon_sym_repeat] = ACTIONS(283),
    [anon_sym_seq] = ACTIONS(283),
    [anon_sym_tab] = ACTIONS(283),
    [anon_sym_select] = ACTIONS(283),
    [anon_sym_exclude] = ACTIONS(283),
    [anon_sym_derive] = ACTIONS(283),
    [anon_sym_updateCol] = ACTIONS(283),
    [anon_sym_gridValues] = ACTIONS(283),
    [anon_sym_leftJoin] = ACTIONS(283),
    [anon_sym_outerJoin] = ACTIONS(283),
    [anon_sym_linearSearch] = ACTIONS(283),
    [anon_sym_linearSearchIndex] = ACTIONS(283),
    [anon_sym_binPaths] = ACTIONS(283),
    [anon_sym_wt] = ACTIONS(283),
    [anon_sym_tt] = ACTIONS(283),
    [anon_sym_ttFile] = ACTIONS(283),
    [anon_sym_uw] = ACTIONS(283),
    [anon_sym_tuw] = ACTIONS(283),
    [anon_sym_strCmp] = ACTIONS(283),
    [anon_sym_floatCmp] = ACTIONS(283),
    [anon_sym_versionSortCmp] = ACTIONS(283),
    [anon_sym_id] = ACTIONS(283),
    [anon_sym_2id] = ACTIONS(283),
    [anon_sym_3id] = ACTIONS(283),
    [anon_sym_2unpack] = ACTIONS(283),
    [anon_sym_2apply] = ACTIONS(283),
    [anon_sym_2each] = ACTIONS(283),
    [anon_sym_2tuple] = ACTIONS(283),
    [anon_sym_DOTs] = ACTIONS(283),
    [anon_sym_DOTb] = ACTIONS(283),
    [anon_sym_DOTdef] = ACTIONS(283),
    [anon_sym_DOTenv] = ACTIONS(283),
    [sym_string] = ACTIONS(281),
    [sym_format_string] = ACTIONS(281),
    [sym_single_quoted_string] = ACTIONS(281),
    [sym_path] = ACTIONS(281),
    [sym_datetime] = ACTIONS(281),
    [sym_float] = ACTIONS(281),
    [sym_integer] = ACTIONS(283),
    [sym_env_store] = ACTIONS(281),
    [sym_env_check] = ACTIONS(281),
    [sym_env_retrieve] = ACTIONS(283),
    [sym_positional] = ACTIONS(281),
    [sym_var_retrieve] = ACTIONS(281),
    [sym_var_store] = ACTIONS(281),
    [sym_slice_indexer] = ACTIONS(281),
    [sym_indexer] = ACTIONS(281),
    [sym_end_indexer] = ACTIONS(283),
    [sym_start_indexer] = ACTIONS(283),
    [sym_match_arm_dup] = ACTIONS(281),
    [sym_prefix_quote] = ACTIONS(283),
    [anon_sym_GT] = ACTIONS(283),
    [anon_sym_GT_GT] = ACTIONS(281),
    [anon_sym_2_GT] = ACTIONS(283),
    [anon_sym_2_GT_GT] = ACTIONS(283),
    [anon_sym_AMP_GT] = ACTIONS(283),
    [anon_sym_AMP_GT_GT] = ACTIONS(281),
    [anon_sym_LT] = ACTIONS(283),
    [anon_sym_LT_GT] = ACTIONS(281),
    [anon_sym_STAR] = ACTIONS(283),
    [anon_sym_STARb] = ACTIONS(281),
    [anon_sym_CARET] = ACTIONS(283),
    [anon_sym_CARETb] = ACTIONS(281),
    [anon_sym_SEMI] = ACTIONS(281),
    [anon_sym_BANG] = ACTIONS(283),
    [anon_sym_QMARK] = ACTIONS(281),
    [anon_sym_BANG_EQ] = ACTIONS(281),
    [anon_sym_LT_EQ] = ACTIONS(281),
    [anon_sym_GT_EQ] = ACTIONS(281),
    [anon_sym_AMP] = ACTIONS(283),
    [anon_sym_PIPE] = ACTIONS(283),
    [anon_sym_COMMA] = ACTIONS(281),
    [anon_sym_COLON] = ACTIONS(283),
  },
  [43] = {
    [sym_identifier] = ACTIONS(295),
    [anon_sym_LBRACK] = ACTIONS(295),
    [anon_sym_LPAREN] = ACTIONS(293),
    [anon_sym_LBRACE] = ACTIONS(293),
    [anon_sym_LBRACK_PIPE] = ACTIONS(293),
    [anon_sym_PIPE_RBRACK] = ACTIONS(293),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(295),
    [anon_sym_false] = ACTIONS(295),
    [anon_sym_def] = ACTIONS(295),
    [anon_sym_end] = ACTIONS(295),
    [anon_sym_if] = ACTIONS(295),
    [anon_sym_iff] = ACTIONS(295),
    [anon_sym_else] = ACTIONS(295),
    [anon_sym_else_STAR] = ACTIONS(293),
    [anon_sym_STARif] = ACTIONS(293),
    [anon_sym_loop] = ACTIONS(295),
    [anon_sym_match] = ACTIONS(295),
    [anon_sym_break] = ACTIONS(295),
    [anon_sym_continue] = ACTIONS(295),
    [anon_sym_soe] = ACTIONS(295),
    [anon_sym_not] = ACTIONS(295),
    [anon_sym_and] = ACTIONS(295),
    [anon_sym_or] = ACTIONS(295),
    [anon_sym_read] = ACTIONS(295),
    [anon_sym_str] = ACTIONS(295),
    [anon_sym_as] = ACTIONS(295),
    [anon_sym_type] = ACTIONS(295),
    [anon_sym_try] = ACTIONS(295),
    [anon_sym_fail] = ACTIONS(295),
    [anon_sym_pure] = ACTIONS(295),
    [anon_sym_VER] = ACTIONS(295),
    [anon_sym_x] = ACTIONS(295),
    [anon_sym_int] = ACTIONS(295),
    [anon_sym_float] = ACTIONS(295),
    [anon_sym_bool] = ACTIONS(295),
    [anon_sym_dup] = ACTIONS(295),
    [anon_sym_swap] = ACTIONS(295),
    [anon_sym_drop] = ACTIONS(295),
    [anon_sym_over] = ACTIONS(295),
    [anon_sym_pick] = ACTIONS(295),
    [anon_sym_rot] = ACTIONS(295),
    [anon_sym_DASHrot] = ACTIONS(295),
    [anon_sym_nip] = ACTIONS(295),
    [anon_sym_w] = ACTIONS(295),
    [anon_sym_wl] = ACTIONS(295),
    [anon_sym_we] = ACTIONS(295),
    [anon_sym_wle] = ACTIONS(295),
    [anon_sym_len] = ACTIONS(295),
    [anon_sym_args] = ACTIONS(295),
    [anon_sym_glob] = ACTIONS(295),
    [anon_sym_toFloat] = ACTIONS(295),
    [anon_sym_toInt] = ACTIONS(295),
    [anon_sym_toPath] = ACTIONS(295),
    [anon_sym_toDt] = ACTIONS(295),
    [anon_sym_toGrid] = ACTIONS(295),
    [anon_sym_toCsv] = ACTIONS(295),
    [anon_sym_toCsvCell] = ACTIONS(295),
    [anon_sym_exit] = ACTIONS(295),
    [anon_sym_prompt] = ACTIONS(295),
    [anon_sym_stdin] = ACTIONS(295),
    [anon_sym_COLON_COLON] = ACTIONS(293),
    [anon_sym_foldl] = ACTIONS(295),
    [anon_sym_map] = ACTIONS(295),
    [anon_sym_each] = ACTIONS(295),
    [anon_sym_eachWhile] = ACTIONS(295),
    [anon_sym_filter] = ACTIONS(295),
    [anon_sym_append] = ACTIONS(295),
    [anon_sym_extend] = ACTIONS(295),
    [anon_sym_concat] = ACTIONS(295),
    [anon_sym_reverse] = ACTIONS(295),
    [anon_sym_sort] = ACTIONS(295),
    [anon_sym_sortV] = ACTIONS(295),
    [anon_sym_sortBy] = ACTIONS(295),
    [anon_sym_sortByCmp] = ACTIONS(295),
    [anon_sym_uniq] = ACTIONS(295),
    [anon_sym_zip] = ACTIONS(295),
    [anon_sym_enumerate] = ACTIONS(295),
    [anon_sym_enumerateN] = ACTIONS(295),
    [anon_sym_chunk] = ACTIONS(295),
    [anon_sym_pop] = ACTIONS(295),
    [anon_sym_take] = ACTIONS(295),
    [anon_sym_takeWhile] = ACTIONS(295),
    [anon_sym_skip] = ACTIONS(295),
    [anon_sym_dropWhile] = ACTIONS(295),
    [anon_sym_nth] = ACTIONS(295),
    [anon_sym_insert] = ACTIONS(295),
    [anon_sym_setAt] = ACTIONS(295),
    [anon_sym_del] = ACTIONS(295),
    [anon_sym_sum] = ACTIONS(295),
    [anon_sym_max] = ACTIONS(295),
    [anon_sym_max2] = ACTIONS(295),
    [anon_sym_min] = ACTIONS(295),
    [anon_sym_min2] = ACTIONS(295),
    [anon_sym_abs] = ACTIONS(295),
    [anon_sym_inc] = ACTIONS(295),
    [anon_sym_mod] = ACTIONS(295),
    [anon_sym_floor] = ACTIONS(295),
    [anon_sym_ceil] = ACTIONS(295),
    [anon_sym_round] = ACTIONS(295),
    [anon_sym_lines] = ACTIONS(295),
    [anon_sym_unlines] = ACTIONS(295),
    [anon_sym_unlinesCrLf] = ACTIONS(295),
    [anon_sym_split] = ACTIONS(295),
    [anon_sym_wsplit] = ACTIONS(295),
    [anon_sym_tsplit] = ACTIONS(295),
    [anon_sym_join] = ACTIONS(295),
    [anon_sym_trim] = ACTIONS(295),
    [anon_sym_trimStart] = ACTIONS(295),
    [anon_sym_trimEnd] = ACTIONS(295),
    [anon_sym_startsWith] = ACTIONS(295),
    [anon_sym_endsWith] = ACTIONS(295),
    [anon_sym_lower] = ACTIONS(295),
    [anon_sym_upper] = ACTIONS(295),
    [anon_sym_title] = ACTIONS(295),
    [anon_sym_leftPad] = ACTIONS(295),
    [anon_sym_findReplace] = ACTIONS(295),
    [anon_sym_in] = ACTIONS(295),
    [anon_sym_index] = ACTIONS(295),
    [anon_sym_lastIndexOf] = ACTIONS(295),
    [anon_sym_countSubStr] = ACTIONS(295),
    [anon_sym_parseJson] = ACTIONS(295),
    [anon_sym_parseCsv] = ACTIONS(295),
    [anon_sym_parseHtml] = ACTIONS(295),
    [anon_sym_parseExcel] = ACTIONS(295),
    [anon_sym_readFile] = ACTIONS(295),
    [anon_sym_readFileBytes] = ACTIONS(295),
    [anon_sym_readTsvFile] = ACTIONS(295),
    [anon_sym_writeFile] = ACTIONS(295),
    [anon_sym_appendFile] = ACTIONS(295),
    [anon_sym_fileExists] = ACTIONS(295),
    [anon_sym_isDir] = ACTIONS(295),
    [anon_sym_isFile] = ACTIONS(295),
    [anon_sym_fileSize] = ACTIONS(295),
    [anon_sym_cp] = ACTIONS(295),
    [anon_sym_mv] = ACTIONS(295),
    [anon_sym_rm] = ACTIONS(295),
    [anon_sym_rmf] = ACTIONS(295),
    [anon_sym_mkdir] = ACTIONS(295),
    [anon_sym_mkdirp] = ACTIONS(295),
    [anon_sym_cd] = ACTIONS(295),
    [anon_sym_pwd] = ACTIONS(295),
    [anon_sym_tempFile] = ACTIONS(295),
    [anon_sym_tempFileExt] = ACTIONS(295),
    [anon_sym_tempDir] = ACTIONS(295),
    [anon_sym_lsDir] = ACTIONS(295),
    [anon_sym_files] = ACTIONS(295),
    [anon_sym_dirs] = ACTIONS(295),
    [anon_sym_absPath] = ACTIONS(295),
    [anon_sym_dirname] = ACTIONS(295),
    [anon_sym_basename] = ACTIONS(295),
    [anon_sym_ext] = ACTIONS(295),
    [anon_sym_stem] = ACTIONS(295),
    [anon_sym_isCmd] = ACTIONS(295),
    [anon_sym_hardLink] = ACTIONS(295),
    [anon_sym_sha256sum] = ACTIONS(295),
    [anon_sym_md5] = ACTIONS(295),
    [anon_sym_now] = ACTIONS(295),
    [anon_sym_date] = ACTIONS(295),
    [anon_sym_year] = ACTIONS(295),
    [anon_sym_month] = ACTIONS(295),
    [anon_sym_day] = ACTIONS(295),
    [anon_sym_hour] = ACTIONS(295),
    [anon_sym_minute] = ACTIONS(295),
    [anon_sym_dateFmt] = ACTIONS(295),
    [anon_sym_isoDateFmt] = ACTIONS(295),
    [anon_sym_isoDateTimeFmt] = ACTIONS(295),
    [anon_sym_isWeekend] = ACTIONS(295),
    [anon_sym_isWeekday] = ACTIONS(295),
    [anon_sym_dow] = ACTIONS(295),
    [anon_sym_addDays] = ACTIONS(295),
    [anon_sym_toUnixTime] = ACTIONS(295),
    [anon_sym_toUnixTimeMilli] = ACTIONS(295),
    [anon_sym_toUnixTimeMicro] = ACTIONS(295),
    [anon_sym_toUnixTimeNano] = ACTIONS(295),
    [anon_sym_fromUnixTime] = ACTIONS(295),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(295),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(295),
    [anon_sym_fromUnixTimeNano] = ACTIONS(295),
    [anon_sym_toOleDate] = ACTIONS(295),
    [anon_sym_fromOleDate] = ACTIONS(295),
    [anon_sym_utcToCst] = ACTIONS(295),
    [anon_sym_cstToUtc] = ACTIONS(295),
    [anon_sym_reMatch] = ACTIONS(295),
    [anon_sym_reFindAll] = ACTIONS(295),
    [anon_sym_reFindAllIndex] = ACTIONS(295),
    [anon_sym_reReplace] = ACTIONS(295),
    [anon_sym_reSplit] = ACTIONS(295),
    [anon_sym_just] = ACTIONS(295),
    [anon_sym_none] = ACTIONS(295),
    [anon_sym_isNone] = ACTIONS(295),
    [anon_sym_maybe] = ACTIONS(295),
    [anon_sym_bind] = ACTIONS(295),
    [anon_sym_psub] = ACTIONS(295),
    [anon_sym_typeof] = ACTIONS(295),
    [anon_sym_runtime] = ACTIONS(295),
    [anon_sym_hostname] = ACTIONS(295),
    [anon_sym_httpGet] = ACTIONS(295),
    [anon_sym_httpPost] = ACTIONS(295),
    [anon_sym_urlEncode] = ACTIONS(295),
    [anon_sym_base64encode] = ACTIONS(295),
    [anon_sym_base64decode] = ACTIONS(295),
    [anon_sym_utf8Str] = ACTIONS(295),
    [anon_sym_utf8Bytes] = ACTIONS(295),
    [anon_sym_get] = ACTIONS(295),
    [anon_sym_getDef] = ACTIONS(295),
    [anon_sym_set] = ACTIONS(295),
    [anon_sym_setd] = ACTIONS(295),
    [anon_sym_keys] = ACTIONS(295),
    [anon_sym_values] = ACTIONS(295),
    [anon_sym_keyValues] = ACTIONS(295),
    [anon_sym_all] = ACTIONS(295),
    [anon_sym_any] = ACTIONS(295),
    [anon_sym_cartesian] = ACTIONS(295),
    [anon_sym_groupBy] = ACTIONS(295),
    [anon_sym_listToDict] = ACTIONS(295),
    [anon_sym_repeat] = ACTIONS(295),
    [anon_sym_seq] = ACTIONS(295),
    [anon_sym_tab] = ACTIONS(295),
    [anon_sym_select] = ACTIONS(295),
    [anon_sym_exclude] = ACTIONS(295),
    [anon_sym_derive] = ACTIONS(295),
    [anon_sym_updateCol] = ACTIONS(295),
    [anon_sym_gridValues] = ACTIONS(295),
    [anon_sym_leftJoin] = ACTIONS(295),
    [anon_sym_outerJoin] = ACTIONS(295),
    [anon_sym_linearSearch] = ACTIONS(295),
    [anon_sym_linearSearchIndex] = ACTIONS(295),
    [anon_sym_binPaths] = ACTIONS(295),
    [anon_sym_wt] = ACTIONS(295),
    [anon_sym_tt] = ACTIONS(295),
    [anon_sym_ttFile] = ACTIONS(295),
    [anon_sym_uw] = ACTIONS(295),
    [anon_sym_tuw] = ACTIONS(295),
    [anon_sym_strCmp] = ACTIONS(295),
    [anon_sym_floatCmp] = ACTIONS(295),
    [anon_sym_versionSortCmp] = ACTIONS(295),
    [anon_sym_id] = ACTIONS(295),
    [anon_sym_2id] = ACTIONS(295),
    [anon_sym_3id] = ACTIONS(295),
    [anon_sym_2unpack] = ACTIONS(295),
    [anon_sym_2apply] = ACTIONS(295),
    [anon_sym_2each] = ACTIONS(295),
    [anon_sym_2tuple] = ACTIONS(295),
    [anon_sym_DOTs] = ACTIONS(295),
    [anon_sym_DOTb] = ACTIONS(295),
    [anon_sym_DOTdef] = ACTIONS(295),
    [anon_sym_DOTenv] = ACTIONS(295),
    [sym_string] = ACTIONS(293),
    [sym_format_string] = ACTIONS(293),
    [sym_single_quoted_string] = ACTIONS(293),
    [sym_path] = ACTIONS(293),
    [sym_datetime] = ACTIONS(293),
    [sym_float] = ACTIONS(293),
    [sym_integer] = ACTIONS(295),
    [sym_env_store] = ACTIONS(293),
    [sym_env_check] = ACTIONS(293),
    [sym_env_retrieve] = ACTIONS(295),
    [sym_positional] = ACTIONS(293),
    [sym_var_retrieve] = ACTIONS(293),
    [sym_var_store] = ACTIONS(293),
    [sym_slice_indexer] = ACTIONS(293),
    [sym_indexer] = ACTIONS(293),
    [sym_end_indexer] = ACTIONS(295),
    [sym_start_indexer] = ACTIONS(295),
    [sym_match_arm_dup] = ACTIONS(293),
    [sym_prefix_quote] = ACTIONS(295),
    [anon_sym_GT] = ACTIONS(295),
    [anon_sym_GT_GT] = ACTIONS(293),
    [anon_sym_2_GT] = ACTIONS(295),
    [anon_sym_2_GT_GT] = ACTIONS(295),
    [anon_sym_AMP_GT] = ACTIONS(295),
    [anon_sym_AMP_GT_GT] = ACTIONS(293),
    [anon_sym_LT] = ACTIONS(295),
    [anon_sym_LT_GT] = ACTIONS(293),
    [anon_sym_STAR] = ACTIONS(295),
    [anon_sym_STARb] = ACTIONS(293),
    [anon_sym_CARET] = ACTIONS(295),
    [anon_sym_CARETb] = ACTIONS(293),
    [anon_sym_SEMI] = ACTIONS(293),
    [anon_sym_BANG] = ACTIONS(295),
    [anon_sym_QMARK] = ACTIONS(293),
    [anon_sym_BANG_EQ] = ACTIONS(293),
    [anon_sym_LT_EQ] = ACTIONS(293),
    [anon_sym_GT_EQ] = ACTIONS(293),
    [anon_sym_AMP] = ACTIONS(295),
    [anon_sym_PIPE] = ACTIONS(295),
    [anon_sym_COMMA] = ACTIONS(293),
    [anon_sym_COLON] = ACTIONS(295),
  },
  [44] = {
    [sym_identifier] = ACTIONS(315),
    [anon_sym_LBRACK] = ACTIONS(315),
    [anon_sym_LPAREN] = ACTIONS(313),
    [anon_sym_LBRACE] = ACTIONS(313),
    [anon_sym_LBRACK_PIPE] = ACTIONS(313),
    [anon_sym_PIPE_RBRACK] = ACTIONS(313),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(315),
    [anon_sym_false] = ACTIONS(315),
    [anon_sym_def] = ACTIONS(315),
    [anon_sym_end] = ACTIONS(315),
    [anon_sym_if] = ACTIONS(315),
    [anon_sym_iff] = ACTIONS(315),
    [anon_sym_else] = ACTIONS(315),
    [anon_sym_else_STAR] = ACTIONS(313),
    [anon_sym_STARif] = ACTIONS(313),
    [anon_sym_loop] = ACTIONS(315),
    [anon_sym_match] = ACTIONS(315),
    [anon_sym_break] = ACTIONS(315),
    [anon_sym_continue] = ACTIONS(315),
    [anon_sym_soe] = ACTIONS(315),
    [anon_sym_not] = ACTIONS(315),
    [anon_sym_and] = ACTIONS(315),
    [anon_sym_or] = ACTIONS(315),
    [anon_sym_read] = ACTIONS(315),
    [anon_sym_str] = ACTIONS(315),
    [anon_sym_as] = ACTIONS(315),
    [anon_sym_type] = ACTIONS(315),
    [anon_sym_try] = ACTIONS(315),
    [anon_sym_fail] = ACTIONS(315),
    [anon_sym_pure] = ACTIONS(315),
    [anon_sym_VER] = ACTIONS(315),
    [anon_sym_x] = ACTIONS(315),
    [anon_sym_int] = ACTIONS(315),
    [anon_sym_float] = ACTIONS(315),
    [anon_sym_bool] = ACTIONS(315),
    [anon_sym_dup] = ACTIONS(315),
    [anon_sym_swap] = ACTIONS(315),
    [anon_sym_drop] = ACTIONS(315),
    [anon_sym_over] = ACTIONS(315),
    [anon_sym_pick] = ACTIONS(315),
    [anon_sym_rot] = ACTIONS(315),
    [anon_sym_DASHrot] = ACTIONS(315),
    [anon_sym_nip] = ACTIONS(315),
    [anon_sym_w] = ACTIONS(315),
    [anon_sym_wl] = ACTIONS(315),
    [anon_sym_we] = ACTIONS(315),
    [anon_sym_wle] = ACTIONS(315),
    [anon_sym_len] = ACTIONS(315),
    [anon_sym_args] = ACTIONS(315),
    [anon_sym_glob] = ACTIONS(315),
    [anon_sym_toFloat] = ACTIONS(315),
    [anon_sym_toInt] = ACTIONS(315),
    [anon_sym_toPath] = ACTIONS(315),
    [anon_sym_toDt] = ACTIONS(315),
    [anon_sym_toGrid] = ACTIONS(315),
    [anon_sym_toCsv] = ACTIONS(315),
    [anon_sym_toCsvCell] = ACTIONS(315),
    [anon_sym_exit] = ACTIONS(315),
    [anon_sym_prompt] = ACTIONS(315),
    [anon_sym_stdin] = ACTIONS(315),
    [anon_sym_COLON_COLON] = ACTIONS(313),
    [anon_sym_foldl] = ACTIONS(315),
    [anon_sym_map] = ACTIONS(315),
    [anon_sym_each] = ACTIONS(315),
    [anon_sym_eachWhile] = ACTIONS(315),
    [anon_sym_filter] = ACTIONS(315),
    [anon_sym_append] = ACTIONS(315),
    [anon_sym_extend] = ACTIONS(315),
    [anon_sym_concat] = ACTIONS(315),
    [anon_sym_reverse] = ACTIONS(315),
    [anon_sym_sort] = ACTIONS(315),
    [anon_sym_sortV] = ACTIONS(315),
    [anon_sym_sortBy] = ACTIONS(315),
    [anon_sym_sortByCmp] = ACTIONS(315),
    [anon_sym_uniq] = ACTIONS(315),
    [anon_sym_zip] = ACTIONS(315),
    [anon_sym_enumerate] = ACTIONS(315),
    [anon_sym_enumerateN] = ACTIONS(315),
    [anon_sym_chunk] = ACTIONS(315),
    [anon_sym_pop] = ACTIONS(315),
    [anon_sym_take] = ACTIONS(315),
    [anon_sym_takeWhile] = ACTIONS(315),
    [anon_sym_skip] = ACTIONS(315),
    [anon_sym_dropWhile] = ACTIONS(315),
    [anon_sym_nth] = ACTIONS(315),
    [anon_sym_insert] = ACTIONS(315),
    [anon_sym_setAt] = ACTIONS(315),
    [anon_sym_del] = ACTIONS(315),
    [anon_sym_sum] = ACTIONS(315),
    [anon_sym_max] = ACTIONS(315),
    [anon_sym_max2] = ACTIONS(315),
    [anon_sym_min] = ACTIONS(315),
    [anon_sym_min2] = ACTIONS(315),
    [anon_sym_abs] = ACTIONS(315),
    [anon_sym_inc] = ACTIONS(315),
    [anon_sym_mod] = ACTIONS(315),
    [anon_sym_floor] = ACTIONS(315),
    [anon_sym_ceil] = ACTIONS(315),
    [anon_sym_round] = ACTIONS(315),
    [anon_sym_lines] = ACTIONS(315),
    [anon_sym_unlines] = ACTIONS(315),
    [anon_sym_unlinesCrLf] = ACTIONS(315),
    [anon_sym_split] = ACTIONS(315),
    [anon_sym_wsplit] = ACTIONS(315),
    [anon_sym_tsplit] = ACTIONS(315),
    [anon_sym_join] = ACTIONS(315),
    [anon_sym_trim] = ACTIONS(315),
    [anon_sym_trimStart] = ACTIONS(315),
    [anon_sym_trimEnd] = ACTIONS(315),
    [anon_sym_startsWith] = ACTIONS(315),
    [anon_sym_endsWith] = ACTIONS(315),
    [anon_sym_lower] = ACTIONS(315),
    [anon_sym_upper] = ACTIONS(315),
    [anon_sym_title] = ACTIONS(315),
    [anon_sym_leftPad] = ACTIONS(315),
    [anon_sym_findReplace] = ACTIONS(315),
    [anon_sym_in] = ACTIONS(315),
    [anon_sym_index] = ACTIONS(315),
    [anon_sym_lastIndexOf] = ACTIONS(315),
    [anon_sym_countSubStr] = ACTIONS(315),
    [anon_sym_parseJson] = ACTIONS(315),
    [anon_sym_parseCsv] = ACTIONS(315),
    [anon_sym_parseHtml] = ACTIONS(315),
    [anon_sym_parseExcel] = ACTIONS(315),
    [anon_sym_readFile] = ACTIONS(315),
    [anon_sym_readFileBytes] = ACTIONS(315),
    [anon_sym_readTsvFile] = ACTIONS(315),
    [anon_sym_writeFile] = ACTIONS(315),
    [anon_sym_appendFile] = ACTIONS(315),
    [anon_sym_fileExists] = ACTIONS(315),
    [anon_sym_isDir] = ACTIONS(315),
    [anon_sym_isFile] = ACTIONS(315),
    [anon_sym_fileSize] = ACTIONS(315),
    [anon_sym_cp] = ACTIONS(315),
    [anon_sym_mv] = ACTIONS(315),
    [anon_sym_rm] = ACTIONS(315),
    [anon_sym_rmf] = ACTIONS(315),
    [anon_sym_mkdir] = ACTIONS(315),
    [anon_sym_mkdirp] = ACTIONS(315),
    [anon_sym_cd] = ACTIONS(315),
    [anon_sym_pwd] = ACTIONS(315),
    [anon_sym_tempFile] = ACTIONS(315),
    [anon_sym_tempFileExt] = ACTIONS(315),
    [anon_sym_tempDir] = ACTIONS(315),
    [anon_sym_lsDir] = ACTIONS(315),
    [anon_sym_files] = ACTIONS(315),
    [anon_sym_dirs] = ACTIONS(315),
    [anon_sym_absPath] = ACTIONS(315),
    [anon_sym_dirname] = ACTIONS(315),
    [anon_sym_basename] = ACTIONS(315),
    [anon_sym_ext] = ACTIONS(315),
    [anon_sym_stem] = ACTIONS(315),
    [anon_sym_isCmd] = ACTIONS(315),
    [anon_sym_hardLink] = ACTIONS(315),
    [anon_sym_sha256sum] = ACTIONS(315),
    [anon_sym_md5] = ACTIONS(315),
    [anon_sym_now] = ACTIONS(315),
    [anon_sym_date] = ACTIONS(315),
    [anon_sym_year] = ACTIONS(315),
    [anon_sym_month] = ACTIONS(315),
    [anon_sym_day] = ACTIONS(315),
    [anon_sym_hour] = ACTIONS(315),
    [anon_sym_minute] = ACTIONS(315),
    [anon_sym_dateFmt] = ACTIONS(315),
    [anon_sym_isoDateFmt] = ACTIONS(315),
    [anon_sym_isoDateTimeFmt] = ACTIONS(315),
    [anon_sym_isWeekend] = ACTIONS(315),
    [anon_sym_isWeekday] = ACTIONS(315),
    [anon_sym_dow] = ACTIONS(315),
    [anon_sym_addDays] = ACTIONS(315),
    [anon_sym_toUnixTime] = ACTIONS(315),
    [anon_sym_toUnixTimeMilli] = ACTIONS(315),
    [anon_sym_toUnixTimeMicro] = ACTIONS(315),
    [anon_sym_toUnixTimeNano] = ACTIONS(315),
    [anon_sym_fromUnixTime] = ACTIONS(315),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(315),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(315),
    [anon_sym_fromUnixTimeNano] = ACTIONS(315),
    [anon_sym_toOleDate] = ACTIONS(315),
    [anon_sym_fromOleDate] = ACTIONS(315),
    [anon_sym_utcToCst] = ACTIONS(315),
    [anon_sym_cstToUtc] = ACTIONS(315),
    [anon_sym_reMatch] = ACTIONS(315),
    [anon_sym_reFindAll] = ACTIONS(315),
    [anon_sym_reFindAllIndex] = ACTIONS(315),
    [anon_sym_reReplace] = ACTIONS(315),
    [anon_sym_reSplit] = ACTIONS(315),
    [anon_sym_just] = ACTIONS(315),
    [anon_sym_none] = ACTIONS(315),
    [anon_sym_isNone] = ACTIONS(315),
    [anon_sym_maybe] = ACTIONS(315),
    [anon_sym_bind] = ACTIONS(315),
    [anon_sym_psub] = ACTIONS(315),
    [anon_sym_typeof] = ACTIONS(315),
    [anon_sym_runtime] = ACTIONS(315),
    [anon_sym_hostname] = ACTIONS(315),
    [anon_sym_httpGet] = ACTIONS(315),
    [anon_sym_httpPost] = ACTIONS(315),
    [anon_sym_urlEncode] = ACTIONS(315),
    [anon_sym_base64encode] = ACTIONS(315),
    [anon_sym_base64decode] = ACTIONS(315),
    [anon_sym_utf8Str] = ACTIONS(315),
    [anon_sym_utf8Bytes] = ACTIONS(315),
    [anon_sym_get] = ACTIONS(315),
    [anon_sym_getDef] = ACTIONS(315),
    [anon_sym_set] = ACTIONS(315),
    [anon_sym_setd] = ACTIONS(315),
    [anon_sym_keys] = ACTIONS(315),
    [anon_sym_values] = ACTIONS(315),
    [anon_sym_keyValues] = ACTIONS(315),
    [anon_sym_all] = ACTIONS(315),
    [anon_sym_any] = ACTIONS(315),
    [anon_sym_cartesian] = ACTIONS(315),
    [anon_sym_groupBy] = ACTIONS(315),
    [anon_sym_listToDict] = ACTIONS(315),
    [anon_sym_repeat] = ACTIONS(315),
    [anon_sym_seq] = ACTIONS(315),
    [anon_sym_tab] = ACTIONS(315),
    [anon_sym_select] = ACTIONS(315),
    [anon_sym_exclude] = ACTIONS(315),
    [anon_sym_derive] = ACTIONS(315),
    [anon_sym_updateCol] = ACTIONS(315),
    [anon_sym_gridValues] = ACTIONS(315),
    [anon_sym_leftJoin] = ACTIONS(315),
    [anon_sym_outerJoin] = ACTIONS(315),
    [anon_sym_linearSearch] = ACTIONS(315),
    [anon_sym_linearSearchIndex] = ACTIONS(315),
    [anon_sym_binPaths] = ACTIONS(315),
    [anon_sym_wt] = ACTIONS(315),
    [anon_sym_tt] = ACTIONS(315),
    [anon_sym_ttFile] = ACTIONS(315),
    [anon_sym_uw] = ACTIONS(315),
    [anon_sym_tuw] = ACTIONS(315),
    [anon_sym_strCmp] = ACTIONS(315),
    [anon_sym_floatCmp] = ACTIONS(315),
    [anon_sym_versionSortCmp] = ACTIONS(315),
    [anon_sym_id] = ACTIONS(315),
    [anon_sym_2id] = ACTIONS(315),
    [anon_sym_3id] = ACTIONS(315),
    [anon_sym_2unpack] = ACTIONS(315),
    [anon_sym_2apply] = ACTIONS(315),
    [anon_sym_2each] = ACTIONS(315),
    [anon_sym_2tuple] = ACTIONS(315),
    [anon_sym_DOTs] = ACTIONS(315),
    [anon_sym_DOTb] = ACTIONS(315),
    [anon_sym_DOTdef] = ACTIONS(315),
    [anon_sym_DOTenv] = ACTIONS(315),
    [sym_string] = ACTIONS(313),
    [sym_format_string] = ACTIONS(313),
    [sym_single_quoted_string] = ACTIONS(313),
    [sym_path] = ACTIONS(313),
    [sym_datetime] = ACTIONS(313),
    [sym_float] = ACTIONS(313),
    [sym_integer] = ACTIONS(315),
    [sym_env_store] = ACTIONS(313),
    [sym_env_check] = ACTIONS(313),
    [sym_env_retrieve] = ACTIONS(315),
    [sym_positional] = ACTIONS(313),
    [sym_var_retrieve] = ACTIONS(313),
    [sym_var_store] = ACTIONS(313),
    [sym_slice_indexer] = ACTIONS(313),
    [sym_indexer] = ACTIONS(313),
    [sym_end_indexer] = ACTIONS(315),
    [sym_start_indexer] = ACTIONS(315),
    [sym_match_arm_dup] = ACTIONS(313),
    [sym_prefix_quote] = ACTIONS(315),
    [anon_sym_GT] = ACTIONS(315),
    [anon_sym_GT_GT] = ACTIONS(313),
    [anon_sym_2_GT] = ACTIONS(315),
    [anon_sym_2_GT_GT] = ACTIONS(315),
    [anon_sym_AMP_GT] = ACTIONS(315),
    [anon_sym_AMP_GT_GT] = ACTIONS(313),
    [anon_sym_LT] = ACTIONS(315),
    [anon_sym_LT_GT] = ACTIONS(313),
    [anon_sym_STAR] = ACTIONS(315),
    [anon_sym_STARb] = ACTIONS(313),
    [anon_sym_CARET] = ACTIONS(315),
    [anon_sym_CARETb] = ACTIONS(313),
    [anon_sym_SEMI] = ACTIONS(313),
    [anon_sym_BANG] = ACTIONS(315),
    [anon_sym_QMARK] = ACTIONS(313),
    [anon_sym_BANG_EQ] = ACTIONS(313),
    [anon_sym_LT_EQ] = ACTIONS(313),
    [anon_sym_GT_EQ] = ACTIONS(313),
    [anon_sym_AMP] = ACTIONS(315),
    [anon_sym_PIPE] = ACTIONS(315),
    [anon_sym_COMMA] = ACTIONS(313),
    [anon_sym_COLON] = ACTIONS(315),
  },
  [45] = {
    [sym_identifier] = ACTIONS(307),
    [anon_sym_LBRACK] = ACTIONS(307),
    [anon_sym_LPAREN] = ACTIONS(305),
    [anon_sym_LBRACE] = ACTIONS(305),
    [anon_sym_LBRACK_PIPE] = ACTIONS(305),
    [anon_sym_PIPE_RBRACK] = ACTIONS(305),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(307),
    [anon_sym_false] = ACTIONS(307),
    [anon_sym_def] = ACTIONS(307),
    [anon_sym_end] = ACTIONS(307),
    [anon_sym_if] = ACTIONS(307),
    [anon_sym_iff] = ACTIONS(307),
    [anon_sym_else] = ACTIONS(307),
    [anon_sym_else_STAR] = ACTIONS(305),
    [anon_sym_STARif] = ACTIONS(305),
    [anon_sym_loop] = ACTIONS(307),
    [anon_sym_match] = ACTIONS(307),
    [anon_sym_break] = ACTIONS(307),
    [anon_sym_continue] = ACTIONS(307),
    [anon_sym_soe] = ACTIONS(307),
    [anon_sym_not] = ACTIONS(307),
    [anon_sym_and] = ACTIONS(307),
    [anon_sym_or] = ACTIONS(307),
    [anon_sym_read] = ACTIONS(307),
    [anon_sym_str] = ACTIONS(307),
    [anon_sym_as] = ACTIONS(307),
    [anon_sym_type] = ACTIONS(307),
    [anon_sym_try] = ACTIONS(307),
    [anon_sym_fail] = ACTIONS(307),
    [anon_sym_pure] = ACTIONS(307),
    [anon_sym_VER] = ACTIONS(307),
    [anon_sym_x] = ACTIONS(307),
    [anon_sym_int] = ACTIONS(307),
    [anon_sym_float] = ACTIONS(307),
    [anon_sym_bool] = ACTIONS(307),
    [anon_sym_dup] = ACTIONS(307),
    [anon_sym_swap] = ACTIONS(307),
    [anon_sym_drop] = ACTIONS(307),
    [anon_sym_over] = ACTIONS(307),
    [anon_sym_pick] = ACTIONS(307),
    [anon_sym_rot] = ACTIONS(307),
    [anon_sym_DASHrot] = ACTIONS(307),
    [anon_sym_nip] = ACTIONS(307),
    [anon_sym_w] = ACTIONS(307),
    [anon_sym_wl] = ACTIONS(307),
    [anon_sym_we] = ACTIONS(307),
    [anon_sym_wle] = ACTIONS(307),
    [anon_sym_len] = ACTIONS(307),
    [anon_sym_args] = ACTIONS(307),
    [anon_sym_glob] = ACTIONS(307),
    [anon_sym_toFloat] = ACTIONS(307),
    [anon_sym_toInt] = ACTIONS(307),
    [anon_sym_toPath] = ACTIONS(307),
    [anon_sym_toDt] = ACTIONS(307),
    [anon_sym_toGrid] = ACTIONS(307),
    [anon_sym_toCsv] = ACTIONS(307),
    [anon_sym_toCsvCell] = ACTIONS(307),
    [anon_sym_exit] = ACTIONS(307),
    [anon_sym_prompt] = ACTIONS(307),
    [anon_sym_stdin] = ACTIONS(307),
    [anon_sym_COLON_COLON] = ACTIONS(305),
    [anon_sym_foldl] = ACTIONS(307),
    [anon_sym_map] = ACTIONS(307),
    [anon_sym_each] = ACTIONS(307),
    [anon_sym_eachWhile] = ACTIONS(307),
    [anon_sym_filter] = ACTIONS(307),
    [anon_sym_append] = ACTIONS(307),
    [anon_sym_extend] = ACTIONS(307),
    [anon_sym_concat] = ACTIONS(307),
    [anon_sym_reverse] = ACTIONS(307),
    [anon_sym_sort] = ACTIONS(307),
    [anon_sym_sortV] = ACTIONS(307),
    [anon_sym_sortBy] = ACTIONS(307),
    [anon_sym_sortByCmp] = ACTIONS(307),
    [anon_sym_uniq] = ACTIONS(307),
    [anon_sym_zip] = ACTIONS(307),
    [anon_sym_enumerate] = ACTIONS(307),
    [anon_sym_enumerateN] = ACTIONS(307),
    [anon_sym_chunk] = ACTIONS(307),
    [anon_sym_pop] = ACTIONS(307),
    [anon_sym_take] = ACTIONS(307),
    [anon_sym_takeWhile] = ACTIONS(307),
    [anon_sym_skip] = ACTIONS(307),
    [anon_sym_dropWhile] = ACTIONS(307),
    [anon_sym_nth] = ACTIONS(307),
    [anon_sym_insert] = ACTIONS(307),
    [anon_sym_setAt] = ACTIONS(307),
    [anon_sym_del] = ACTIONS(307),
    [anon_sym_sum] = ACTIONS(307),
    [anon_sym_max] = ACTIONS(307),
    [anon_sym_max2] = ACTIONS(307),
    [anon_sym_min] = ACTIONS(307),
    [anon_sym_min2] = ACTIONS(307),
    [anon_sym_abs] = ACTIONS(307),
    [anon_sym_inc] = ACTIONS(307),
    [anon_sym_mod] = ACTIONS(307),
    [anon_sym_floor] = ACTIONS(307),
    [anon_sym_ceil] = ACTIONS(307),
    [anon_sym_round] = ACTIONS(307),
    [anon_sym_lines] = ACTIONS(307),
    [anon_sym_unlines] = ACTIONS(307),
    [anon_sym_unlinesCrLf] = ACTIONS(307),
    [anon_sym_split] = ACTIONS(307),
    [anon_sym_wsplit] = ACTIONS(307),
    [anon_sym_tsplit] = ACTIONS(307),
    [anon_sym_join] = ACTIONS(307),
    [anon_sym_trim] = ACTIONS(307),
    [anon_sym_trimStart] = ACTIONS(307),
    [anon_sym_trimEnd] = ACTIONS(307),
    [anon_sym_startsWith] = ACTIONS(307),
    [anon_sym_endsWith] = ACTIONS(307),
    [anon_sym_lower] = ACTIONS(307),
    [anon_sym_upper] = ACTIONS(307),
    [anon_sym_title] = ACTIONS(307),
    [anon_sym_leftPad] = ACTIONS(307),
    [anon_sym_findReplace] = ACTIONS(307),
    [anon_sym_in] = ACTIONS(307),
    [anon_sym_index] = ACTIONS(307),
    [anon_sym_lastIndexOf] = ACTIONS(307),
    [anon_sym_countSubStr] = ACTIONS(307),
    [anon_sym_parseJson] = ACTIONS(307),
    [anon_sym_parseCsv] = ACTIONS(307),
    [anon_sym_parseHtml] = ACTIONS(307),
    [anon_sym_parseExcel] = ACTIONS(307),
    [anon_sym_readFile] = ACTIONS(307),
    [anon_sym_readFileBytes] = ACTIONS(307),
    [anon_sym_readTsvFile] = ACTIONS(307),
    [anon_sym_writeFile] = ACTIONS(307),
    [anon_sym_appendFile] = ACTIONS(307),
    [anon_sym_fileExists] = ACTIONS(307),
    [anon_sym_isDir] = ACTIONS(307),
    [anon_sym_isFile] = ACTIONS(307),
    [anon_sym_fileSize] = ACTIONS(307),
    [anon_sym_cp] = ACTIONS(307),
    [anon_sym_mv] = ACTIONS(307),
    [anon_sym_rm] = ACTIONS(307),
    [anon_sym_rmf] = ACTIONS(307),
    [anon_sym_mkdir] = ACTIONS(307),
    [anon_sym_mkdirp] = ACTIONS(307),
    [anon_sym_cd] = ACTIONS(307),
    [anon_sym_pwd] = ACTIONS(307),
    [anon_sym_tempFile] = ACTIONS(307),
    [anon_sym_tempFileExt] = ACTIONS(307),
    [anon_sym_tempDir] = ACTIONS(307),
    [anon_sym_lsDir] = ACTIONS(307),
    [anon_sym_files] = ACTIONS(307),
    [anon_sym_dirs] = ACTIONS(307),
    [anon_sym_absPath] = ACTIONS(307),
    [anon_sym_dirname] = ACTIONS(307),
    [anon_sym_basename] = ACTIONS(307),
    [anon_sym_ext] = ACTIONS(307),
    [anon_sym_stem] = ACTIONS(307),
    [anon_sym_isCmd] = ACTIONS(307),
    [anon_sym_hardLink] = ACTIONS(307),
    [anon_sym_sha256sum] = ACTIONS(307),
    [anon_sym_md5] = ACTIONS(307),
    [anon_sym_now] = ACTIONS(307),
    [anon_sym_date] = ACTIONS(307),
    [anon_sym_year] = ACTIONS(307),
    [anon_sym_month] = ACTIONS(307),
    [anon_sym_day] = ACTIONS(307),
    [anon_sym_hour] = ACTIONS(307),
    [anon_sym_minute] = ACTIONS(307),
    [anon_sym_dateFmt] = ACTIONS(307),
    [anon_sym_isoDateFmt] = ACTIONS(307),
    [anon_sym_isoDateTimeFmt] = ACTIONS(307),
    [anon_sym_isWeekend] = ACTIONS(307),
    [anon_sym_isWeekday] = ACTIONS(307),
    [anon_sym_dow] = ACTIONS(307),
    [anon_sym_addDays] = ACTIONS(307),
    [anon_sym_toUnixTime] = ACTIONS(307),
    [anon_sym_toUnixTimeMilli] = ACTIONS(307),
    [anon_sym_toUnixTimeMicro] = ACTIONS(307),
    [anon_sym_toUnixTimeNano] = ACTIONS(307),
    [anon_sym_fromUnixTime] = ACTIONS(307),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(307),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(307),
    [anon_sym_fromUnixTimeNano] = ACTIONS(307),
    [anon_sym_toOleDate] = ACTIONS(307),
    [anon_sym_fromOleDate] = ACTIONS(307),
    [anon_sym_utcToCst] = ACTIONS(307),
    [anon_sym_cstToUtc] = ACTIONS(307),
    [anon_sym_reMatch] = ACTIONS(307),
    [anon_sym_reFindAll] = ACTIONS(307),
    [anon_sym_reFindAllIndex] = ACTIONS(307),
    [anon_sym_reReplace] = ACTIONS(307),
    [anon_sym_reSplit] = ACTIONS(307),
    [anon_sym_just] = ACTIONS(307),
    [anon_sym_none] = ACTIONS(307),
    [anon_sym_isNone] = ACTIONS(307),
    [anon_sym_maybe] = ACTIONS(307),
    [anon_sym_bind] = ACTIONS(307),
    [anon_sym_psub] = ACTIONS(307),
    [anon_sym_typeof] = ACTIONS(307),
    [anon_sym_runtime] = ACTIONS(307),
    [anon_sym_hostname] = ACTIONS(307),
    [anon_sym_httpGet] = ACTIONS(307),
    [anon_sym_httpPost] = ACTIONS(307),
    [anon_sym_urlEncode] = ACTIONS(307),
    [anon_sym_base64encode] = ACTIONS(307),
    [anon_sym_base64decode] = ACTIONS(307),
    [anon_sym_utf8Str] = ACTIONS(307),
    [anon_sym_utf8Bytes] = ACTIONS(307),
    [anon_sym_get] = ACTIONS(307),
    [anon_sym_getDef] = ACTIONS(307),
    [anon_sym_set] = ACTIONS(307),
    [anon_sym_setd] = ACTIONS(307),
    [anon_sym_keys] = ACTIONS(307),
    [anon_sym_values] = ACTIONS(307),
    [anon_sym_keyValues] = ACTIONS(307),
    [anon_sym_all] = ACTIONS(307),
    [anon_sym_any] = ACTIONS(307),
    [anon_sym_cartesian] = ACTIONS(307),
    [anon_sym_groupBy] = ACTIONS(307),
    [anon_sym_listToDict] = ACTIONS(307),
    [anon_sym_repeat] = ACTIONS(307),
    [anon_sym_seq] = ACTIONS(307),
    [anon_sym_tab] = ACTIONS(307),
    [anon_sym_select] = ACTIONS(307),
    [anon_sym_exclude] = ACTIONS(307),
    [anon_sym_derive] = ACTIONS(307),
    [anon_sym_updateCol] = ACTIONS(307),
    [anon_sym_gridValues] = ACTIONS(307),
    [anon_sym_leftJoin] = ACTIONS(307),
    [anon_sym_outerJoin] = ACTIONS(307),
    [anon_sym_linearSearch] = ACTIONS(307),
    [anon_sym_linearSearchIndex] = ACTIONS(307),
    [anon_sym_binPaths] = ACTIONS(307),
    [anon_sym_wt] = ACTIONS(307),
    [anon_sym_tt] = ACTIONS(307),
    [anon_sym_ttFile] = ACTIONS(307),
    [anon_sym_uw] = ACTIONS(307),
    [anon_sym_tuw] = ACTIONS(307),
    [anon_sym_strCmp] = ACTIONS(307),
    [anon_sym_floatCmp] = ACTIONS(307),
    [anon_sym_versionSortCmp] = ACTIONS(307),
    [anon_sym_id] = ACTIONS(307),
    [anon_sym_2id] = ACTIONS(307),
    [anon_sym_3id] = ACTIONS(307),
    [anon_sym_2unpack] = ACTIONS(307),
    [anon_sym_2apply] = ACTIONS(307),
    [anon_sym_2each] = ACTIONS(307),
    [anon_sym_2tuple] = ACTIONS(307),
    [anon_sym_DOTs] = ACTIONS(307),
    [anon_sym_DOTb] = ACTIONS(307),
    [anon_sym_DOTdef] = ACTIONS(307),
    [anon_sym_DOTenv] = ACTIONS(307),
    [sym_string] = ACTIONS(305),
    [sym_format_string] = ACTIONS(305),
    [sym_single_quoted_string] = ACTIONS(305),
    [sym_path] = ACTIONS(305),
    [sym_datetime] = ACTIONS(305),
    [sym_float] = ACTIONS(305),
    [sym_integer] = ACTIONS(307),
    [sym_env_store] = ACTIONS(305),
    [sym_env_check] = ACTIONS(305),
    [sym_env_retrieve] = ACTIONS(307),
    [sym_positional] = ACTIONS(305),
    [sym_var_retrieve] = ACTIONS(305),
    [sym_var_store] = ACTIONS(305),
    [sym_slice_indexer] = ACTIONS(305),
    [sym_indexer] = ACTIONS(305),
    [sym_end_indexer] = ACTIONS(307),
    [sym_start_indexer] = ACTIONS(307),
    [sym_match_arm_dup] = ACTIONS(305),
    [sym_prefix_quote] = ACTIONS(307),
    [anon_sym_GT] = ACTIONS(307),
    [anon_sym_GT_GT] = ACTIONS(305),
    [anon_sym_2_GT] = ACTIONS(307),
    [anon_sym_2_GT_GT] = ACTIONS(307),
    [anon_sym_AMP_GT] = ACTIONS(307),
    [anon_sym_AMP_GT_GT] = ACTIONS(305),
    [anon_sym_LT] = ACTIONS(307),
    [anon_sym_LT_GT] = ACTIONS(305),
    [anon_sym_STAR] = ACTIONS(307),
    [anon_sym_STARb] = ACTIONS(305),
    [anon_sym_CARET] = ACTIONS(307),
    [anon_sym_CARETb] = ACTIONS(305),
    [anon_sym_SEMI] = ACTIONS(305),
    [anon_sym_BANG] = ACTIONS(307),
    [anon_sym_QMARK] = ACTIONS(305),
    [anon_sym_BANG_EQ] = ACTIONS(305),
    [anon_sym_LT_EQ] = ACTIONS(305),
    [anon_sym_GT_EQ] = ACTIONS(305),
    [anon_sym_AMP] = ACTIONS(307),
    [anon_sym_PIPE] = ACTIONS(307),
    [anon_sym_COMMA] = ACTIONS(305),
    [anon_sym_COLON] = ACTIONS(307),
  },
  [46] = {
    [sym_identifier] = ACTIONS(287),
    [anon_sym_LBRACK] = ACTIONS(287),
    [anon_sym_LPAREN] = ACTIONS(285),
    [anon_sym_LBRACE] = ACTIONS(285),
    [anon_sym_LBRACK_PIPE] = ACTIONS(285),
    [anon_sym_PIPE_RBRACK] = ACTIONS(285),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(287),
    [anon_sym_false] = ACTIONS(287),
    [anon_sym_def] = ACTIONS(287),
    [anon_sym_end] = ACTIONS(287),
    [anon_sym_if] = ACTIONS(287),
    [anon_sym_iff] = ACTIONS(287),
    [anon_sym_else] = ACTIONS(287),
    [anon_sym_else_STAR] = ACTIONS(285),
    [anon_sym_STARif] = ACTIONS(285),
    [anon_sym_loop] = ACTIONS(287),
    [anon_sym_match] = ACTIONS(287),
    [anon_sym_break] = ACTIONS(287),
    [anon_sym_continue] = ACTIONS(287),
    [anon_sym_soe] = ACTIONS(287),
    [anon_sym_not] = ACTIONS(287),
    [anon_sym_and] = ACTIONS(287),
    [anon_sym_or] = ACTIONS(287),
    [anon_sym_read] = ACTIONS(287),
    [anon_sym_str] = ACTIONS(287),
    [anon_sym_as] = ACTIONS(287),
    [anon_sym_type] = ACTIONS(287),
    [anon_sym_try] = ACTIONS(287),
    [anon_sym_fail] = ACTIONS(287),
    [anon_sym_pure] = ACTIONS(287),
    [anon_sym_VER] = ACTIONS(287),
    [anon_sym_x] = ACTIONS(287),
    [anon_sym_int] = ACTIONS(287),
    [anon_sym_float] = ACTIONS(287),
    [anon_sym_bool] = ACTIONS(287),
    [anon_sym_dup] = ACTIONS(287),
    [anon_sym_swap] = ACTIONS(287),
    [anon_sym_drop] = ACTIONS(287),
    [anon_sym_over] = ACTIONS(287),
    [anon_sym_pick] = ACTIONS(287),
    [anon_sym_rot] = ACTIONS(287),
    [anon_sym_DASHrot] = ACTIONS(287),
    [anon_sym_nip] = ACTIONS(287),
    [anon_sym_w] = ACTIONS(287),
    [anon_sym_wl] = ACTIONS(287),
    [anon_sym_we] = ACTIONS(287),
    [anon_sym_wle] = ACTIONS(287),
    [anon_sym_len] = ACTIONS(287),
    [anon_sym_args] = ACTIONS(287),
    [anon_sym_glob] = ACTIONS(287),
    [anon_sym_toFloat] = ACTIONS(287),
    [anon_sym_toInt] = ACTIONS(287),
    [anon_sym_toPath] = ACTIONS(287),
    [anon_sym_toDt] = ACTIONS(287),
    [anon_sym_toGrid] = ACTIONS(287),
    [anon_sym_toCsv] = ACTIONS(287),
    [anon_sym_toCsvCell] = ACTIONS(287),
    [anon_sym_exit] = ACTIONS(287),
    [anon_sym_prompt] = ACTIONS(287),
    [anon_sym_stdin] = ACTIONS(287),
    [anon_sym_COLON_COLON] = ACTIONS(285),
    [anon_sym_foldl] = ACTIONS(287),
    [anon_sym_map] = ACTIONS(287),
    [anon_sym_each] = ACTIONS(287),
    [anon_sym_eachWhile] = ACTIONS(287),
    [anon_sym_filter] = ACTIONS(287),
    [anon_sym_append] = ACTIONS(287),
    [anon_sym_extend] = ACTIONS(287),
    [anon_sym_concat] = ACTIONS(287),
    [anon_sym_reverse] = ACTIONS(287),
    [anon_sym_sort] = ACTIONS(287),
    [anon_sym_sortV] = ACTIONS(287),
    [anon_sym_sortBy] = ACTIONS(287),
    [anon_sym_sortByCmp] = ACTIONS(287),
    [anon_sym_uniq] = ACTIONS(287),
    [anon_sym_zip] = ACTIONS(287),
    [anon_sym_enumerate] = ACTIONS(287),
    [anon_sym_enumerateN] = ACTIONS(287),
    [anon_sym_chunk] = ACTIONS(287),
    [anon_sym_pop] = ACTIONS(287),
    [anon_sym_take] = ACTIONS(287),
    [anon_sym_takeWhile] = ACTIONS(287),
    [anon_sym_skip] = ACTIONS(287),
    [anon_sym_dropWhile] = ACTIONS(287),
    [anon_sym_nth] = ACTIONS(287),
    [anon_sym_insert] = ACTIONS(287),
    [anon_sym_setAt] = ACTIONS(287),
    [anon_sym_del] = ACTIONS(287),
    [anon_sym_sum] = ACTIONS(287),
    [anon_sym_max] = ACTIONS(287),
    [anon_sym_max2] = ACTIONS(287),
    [anon_sym_min] = ACTIONS(287),
    [anon_sym_min2] = ACTIONS(287),
    [anon_sym_abs] = ACTIONS(287),
    [anon_sym_inc] = ACTIONS(287),
    [anon_sym_mod] = ACTIONS(287),
    [anon_sym_floor] = ACTIONS(287),
    [anon_sym_ceil] = ACTIONS(287),
    [anon_sym_round] = ACTIONS(287),
    [anon_sym_lines] = ACTIONS(287),
    [anon_sym_unlines] = ACTIONS(287),
    [anon_sym_unlinesCrLf] = ACTIONS(287),
    [anon_sym_split] = ACTIONS(287),
    [anon_sym_wsplit] = ACTIONS(287),
    [anon_sym_tsplit] = ACTIONS(287),
    [anon_sym_join] = ACTIONS(287),
    [anon_sym_trim] = ACTIONS(287),
    [anon_sym_trimStart] = ACTIONS(287),
    [anon_sym_trimEnd] = ACTIONS(287),
    [anon_sym_startsWith] = ACTIONS(287),
    [anon_sym_endsWith] = ACTIONS(287),
    [anon_sym_lower] = ACTIONS(287),
    [anon_sym_upper] = ACTIONS(287),
    [anon_sym_title] = ACTIONS(287),
    [anon_sym_leftPad] = ACTIONS(287),
    [anon_sym_findReplace] = ACTIONS(287),
    [anon_sym_in] = ACTIONS(287),
    [anon_sym_index] = ACTIONS(287),
    [anon_sym_lastIndexOf] = ACTIONS(287),
    [anon_sym_countSubStr] = ACTIONS(287),
    [anon_sym_parseJson] = ACTIONS(287),
    [anon_sym_parseCsv] = ACTIONS(287),
    [anon_sym_parseHtml] = ACTIONS(287),
    [anon_sym_parseExcel] = ACTIONS(287),
    [anon_sym_readFile] = ACTIONS(287),
    [anon_sym_readFileBytes] = ACTIONS(287),
    [anon_sym_readTsvFile] = ACTIONS(287),
    [anon_sym_writeFile] = ACTIONS(287),
    [anon_sym_appendFile] = ACTIONS(287),
    [anon_sym_fileExists] = ACTIONS(287),
    [anon_sym_isDir] = ACTIONS(287),
    [anon_sym_isFile] = ACTIONS(287),
    [anon_sym_fileSize] = ACTIONS(287),
    [anon_sym_cp] = ACTIONS(287),
    [anon_sym_mv] = ACTIONS(287),
    [anon_sym_rm] = ACTIONS(287),
    [anon_sym_rmf] = ACTIONS(287),
    [anon_sym_mkdir] = ACTIONS(287),
    [anon_sym_mkdirp] = ACTIONS(287),
    [anon_sym_cd] = ACTIONS(287),
    [anon_sym_pwd] = ACTIONS(287),
    [anon_sym_tempFile] = ACTIONS(287),
    [anon_sym_tempFileExt] = ACTIONS(287),
    [anon_sym_tempDir] = ACTIONS(287),
    [anon_sym_lsDir] = ACTIONS(287),
    [anon_sym_files] = ACTIONS(287),
    [anon_sym_dirs] = ACTIONS(287),
    [anon_sym_absPath] = ACTIONS(287),
    [anon_sym_dirname] = ACTIONS(287),
    [anon_sym_basename] = ACTIONS(287),
    [anon_sym_ext] = ACTIONS(287),
    [anon_sym_stem] = ACTIONS(287),
    [anon_sym_isCmd] = ACTIONS(287),
    [anon_sym_hardLink] = ACTIONS(287),
    [anon_sym_sha256sum] = ACTIONS(287),
    [anon_sym_md5] = ACTIONS(287),
    [anon_sym_now] = ACTIONS(287),
    [anon_sym_date] = ACTIONS(287),
    [anon_sym_year] = ACTIONS(287),
    [anon_sym_month] = ACTIONS(287),
    [anon_sym_day] = ACTIONS(287),
    [anon_sym_hour] = ACTIONS(287),
    [anon_sym_minute] = ACTIONS(287),
    [anon_sym_dateFmt] = ACTIONS(287),
    [anon_sym_isoDateFmt] = ACTIONS(287),
    [anon_sym_isoDateTimeFmt] = ACTIONS(287),
    [anon_sym_isWeekend] = ACTIONS(287),
    [anon_sym_isWeekday] = ACTIONS(287),
    [anon_sym_dow] = ACTIONS(287),
    [anon_sym_addDays] = ACTIONS(287),
    [anon_sym_toUnixTime] = ACTIONS(287),
    [anon_sym_toUnixTimeMilli] = ACTIONS(287),
    [anon_sym_toUnixTimeMicro] = ACTIONS(287),
    [anon_sym_toUnixTimeNano] = ACTIONS(287),
    [anon_sym_fromUnixTime] = ACTIONS(287),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(287),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(287),
    [anon_sym_fromUnixTimeNano] = ACTIONS(287),
    [anon_sym_toOleDate] = ACTIONS(287),
    [anon_sym_fromOleDate] = ACTIONS(287),
    [anon_sym_utcToCst] = ACTIONS(287),
    [anon_sym_cstToUtc] = ACTIONS(287),
    [anon_sym_reMatch] = ACTIONS(287),
    [anon_sym_reFindAll] = ACTIONS(287),
    [anon_sym_reFindAllIndex] = ACTIONS(287),
    [anon_sym_reReplace] = ACTIONS(287),
    [anon_sym_reSplit] = ACTIONS(287),
    [anon_sym_just] = ACTIONS(287),
    [anon_sym_none] = ACTIONS(287),
    [anon_sym_isNone] = ACTIONS(287),
    [anon_sym_maybe] = ACTIONS(287),
    [anon_sym_bind] = ACTIONS(287),
    [anon_sym_psub] = ACTIONS(287),
    [anon_sym_typeof] = ACTIONS(287),
    [anon_sym_runtime] = ACTIONS(287),
    [anon_sym_hostname] = ACTIONS(287),
    [anon_sym_httpGet] = ACTIONS(287),
    [anon_sym_httpPost] = ACTIONS(287),
    [anon_sym_urlEncode] = ACTIONS(287),
    [anon_sym_base64encode] = ACTIONS(287),
    [anon_sym_base64decode] = ACTIONS(287),
    [anon_sym_utf8Str] = ACTIONS(287),
    [anon_sym_utf8Bytes] = ACTIONS(287),
    [anon_sym_get] = ACTIONS(287),
    [anon_sym_getDef] = ACTIONS(287),
    [anon_sym_set] = ACTIONS(287),
    [anon_sym_setd] = ACTIONS(287),
    [anon_sym_keys] = ACTIONS(287),
    [anon_sym_values] = ACTIONS(287),
    [anon_sym_keyValues] = ACTIONS(287),
    [anon_sym_all] = ACTIONS(287),
    [anon_sym_any] = ACTIONS(287),
    [anon_sym_cartesian] = ACTIONS(287),
    [anon_sym_groupBy] = ACTIONS(287),
    [anon_sym_listToDict] = ACTIONS(287),
    [anon_sym_repeat] = ACTIONS(287),
    [anon_sym_seq] = ACTIONS(287),
    [anon_sym_tab] = ACTIONS(287),
    [anon_sym_select] = ACTIONS(287),
    [anon_sym_exclude] = ACTIONS(287),
    [anon_sym_derive] = ACTIONS(287),
    [anon_sym_updateCol] = ACTIONS(287),
    [anon_sym_gridValues] = ACTIONS(287),
    [anon_sym_leftJoin] = ACTIONS(287),
    [anon_sym_outerJoin] = ACTIONS(287),
    [anon_sym_linearSearch] = ACTIONS(287),
    [anon_sym_linearSearchIndex] = ACTIONS(287),
    [anon_sym_binPaths] = ACTIONS(287),
    [anon_sym_wt] = ACTIONS(287),
    [anon_sym_tt] = ACTIONS(287),
    [anon_sym_ttFile] = ACTIONS(287),
    [anon_sym_uw] = ACTIONS(287),
    [anon_sym_tuw] = ACTIONS(287),
    [anon_sym_strCmp] = ACTIONS(287),
    [anon_sym_floatCmp] = ACTIONS(287),
    [anon_sym_versionSortCmp] = ACTIONS(287),
    [anon_sym_id] = ACTIONS(287),
    [anon_sym_2id] = ACTIONS(287),
    [anon_sym_3id] = ACTIONS(287),
    [anon_sym_2unpack] = ACTIONS(287),
    [anon_sym_2apply] = ACTIONS(287),
    [anon_sym_2each] = ACTIONS(287),
    [anon_sym_2tuple] = ACTIONS(287),
    [anon_sym_DOTs] = ACTIONS(287),
    [anon_sym_DOTb] = ACTIONS(287),
    [anon_sym_DOTdef] = ACTIONS(287),
    [anon_sym_DOTenv] = ACTIONS(287),
    [sym_string] = ACTIONS(285),
    [sym_format_string] = ACTIONS(285),
    [sym_single_quoted_string] = ACTIONS(285),
    [sym_path] = ACTIONS(285),
    [sym_datetime] = ACTIONS(285),
    [sym_float] = ACTIONS(285),
    [sym_integer] = ACTIONS(287),
    [sym_env_store] = ACTIONS(285),
    [sym_env_check] = ACTIONS(285),
    [sym_env_retrieve] = ACTIONS(287),
    [sym_positional] = ACTIONS(285),
    [sym_var_retrieve] = ACTIONS(285),
    [sym_var_store] = ACTIONS(285),
    [sym_slice_indexer] = ACTIONS(285),
    [sym_indexer] = ACTIONS(285),
    [sym_end_indexer] = ACTIONS(287),
    [sym_start_indexer] = ACTIONS(287),
    [sym_match_arm_dup] = ACTIONS(285),
    [sym_prefix_quote] = ACTIONS(287),
    [anon_sym_GT] = ACTIONS(287),
    [anon_sym_GT_GT] = ACTIONS(285),
    [anon_sym_2_GT] = ACTIONS(287),
    [anon_sym_2_GT_GT] = ACTIONS(287),
    [anon_sym_AMP_GT] = ACTIONS(287),
    [anon_sym_AMP_GT_GT] = ACTIONS(285),
    [anon_sym_LT] = ACTIONS(287),
    [anon_sym_LT_GT] = ACTIONS(285),
    [anon_sym_STAR] = ACTIONS(287),
    [anon_sym_STARb] = ACTIONS(285),
    [anon_sym_CARET] = ACTIONS(287),
    [anon_sym_CARETb] = ACTIONS(285),
    [anon_sym_SEMI] = ACTIONS(285),
    [anon_sym_BANG] = ACTIONS(287),
    [anon_sym_QMARK] = ACTIONS(285),
    [anon_sym_BANG_EQ] = ACTIONS(285),
    [anon_sym_LT_EQ] = ACTIONS(285),
    [anon_sym_GT_EQ] = ACTIONS(285),
    [anon_sym_AMP] = ACTIONS(287),
    [anon_sym_PIPE] = ACTIONS(287),
    [anon_sym_COMMA] = ACTIONS(285),
    [anon_sym_COLON] = ACTIONS(287),
  },
  [47] = {
    [sym_identifier] = ACTIONS(271),
    [anon_sym_LBRACK] = ACTIONS(271),
    [anon_sym_LPAREN] = ACTIONS(269),
    [anon_sym_LBRACE] = ACTIONS(269),
    [anon_sym_LBRACK_PIPE] = ACTIONS(269),
    [anon_sym_PIPE_RBRACK] = ACTIONS(269),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(271),
    [anon_sym_false] = ACTIONS(271),
    [anon_sym_def] = ACTIONS(271),
    [anon_sym_end] = ACTIONS(271),
    [anon_sym_if] = ACTIONS(271),
    [anon_sym_iff] = ACTIONS(271),
    [anon_sym_else] = ACTIONS(271),
    [anon_sym_else_STAR] = ACTIONS(269),
    [anon_sym_STARif] = ACTIONS(269),
    [anon_sym_loop] = ACTIONS(271),
    [anon_sym_match] = ACTIONS(271),
    [anon_sym_break] = ACTIONS(271),
    [anon_sym_continue] = ACTIONS(271),
    [anon_sym_soe] = ACTIONS(271),
    [anon_sym_not] = ACTIONS(271),
    [anon_sym_and] = ACTIONS(271),
    [anon_sym_or] = ACTIONS(271),
    [anon_sym_read] = ACTIONS(271),
    [anon_sym_str] = ACTIONS(271),
    [anon_sym_as] = ACTIONS(271),
    [anon_sym_type] = ACTIONS(271),
    [anon_sym_try] = ACTIONS(271),
    [anon_sym_fail] = ACTIONS(271),
    [anon_sym_pure] = ACTIONS(271),
    [anon_sym_VER] = ACTIONS(271),
    [anon_sym_x] = ACTIONS(271),
    [anon_sym_int] = ACTIONS(271),
    [anon_sym_float] = ACTIONS(271),
    [anon_sym_bool] = ACTIONS(271),
    [anon_sym_dup] = ACTIONS(271),
    [anon_sym_swap] = ACTIONS(271),
    [anon_sym_drop] = ACTIONS(271),
    [anon_sym_over] = ACTIONS(271),
    [anon_sym_pick] = ACTIONS(271),
    [anon_sym_rot] = ACTIONS(271),
    [anon_sym_DASHrot] = ACTIONS(271),
    [anon_sym_nip] = ACTIONS(271),
    [anon_sym_w] = ACTIONS(271),
    [anon_sym_wl] = ACTIONS(271),
    [anon_sym_we] = ACTIONS(271),
    [anon_sym_wle] = ACTIONS(271),
    [anon_sym_len] = ACTIONS(271),
    [anon_sym_args] = ACTIONS(271),
    [anon_sym_glob] = ACTIONS(271),
    [anon_sym_toFloat] = ACTIONS(271),
    [anon_sym_toInt] = ACTIONS(271),
    [anon_sym_toPath] = ACTIONS(271),
    [anon_sym_toDt] = ACTIONS(271),
    [anon_sym_toGrid] = ACTIONS(271),
    [anon_sym_toCsv] = ACTIONS(271),
    [anon_sym_toCsvCell] = ACTIONS(271),
    [anon_sym_exit] = ACTIONS(271),
    [anon_sym_prompt] = ACTIONS(271),
    [anon_sym_stdin] = ACTIONS(271),
    [anon_sym_COLON_COLON] = ACTIONS(269),
    [anon_sym_foldl] = ACTIONS(271),
    [anon_sym_map] = ACTIONS(271),
    [anon_sym_each] = ACTIONS(271),
    [anon_sym_eachWhile] = ACTIONS(271),
    [anon_sym_filter] = ACTIONS(271),
    [anon_sym_append] = ACTIONS(271),
    [anon_sym_extend] = ACTIONS(271),
    [anon_sym_concat] = ACTIONS(271),
    [anon_sym_reverse] = ACTIONS(271),
    [anon_sym_sort] = ACTIONS(271),
    [anon_sym_sortV] = ACTIONS(271),
    [anon_sym_sortBy] = ACTIONS(271),
    [anon_sym_sortByCmp] = ACTIONS(271),
    [anon_sym_uniq] = ACTIONS(271),
    [anon_sym_zip] = ACTIONS(271),
    [anon_sym_enumerate] = ACTIONS(271),
    [anon_sym_enumerateN] = ACTIONS(271),
    [anon_sym_chunk] = ACTIONS(271),
    [anon_sym_pop] = ACTIONS(271),
    [anon_sym_take] = ACTIONS(271),
    [anon_sym_takeWhile] = ACTIONS(271),
    [anon_sym_skip] = ACTIONS(271),
    [anon_sym_dropWhile] = ACTIONS(271),
    [anon_sym_nth] = ACTIONS(271),
    [anon_sym_insert] = ACTIONS(271),
    [anon_sym_setAt] = ACTIONS(271),
    [anon_sym_del] = ACTIONS(271),
    [anon_sym_sum] = ACTIONS(271),
    [anon_sym_max] = ACTIONS(271),
    [anon_sym_max2] = ACTIONS(271),
    [anon_sym_min] = ACTIONS(271),
    [anon_sym_min2] = ACTIONS(271),
    [anon_sym_abs] = ACTIONS(271),
    [anon_sym_inc] = ACTIONS(271),
    [anon_sym_mod] = ACTIONS(271),
    [anon_sym_floor] = ACTIONS(271),
    [anon_sym_ceil] = ACTIONS(271),
    [anon_sym_round] = ACTIONS(271),
    [anon_sym_lines] = ACTIONS(271),
    [anon_sym_unlines] = ACTIONS(271),
    [anon_sym_unlinesCrLf] = ACTIONS(271),
    [anon_sym_split] = ACTIONS(271),
    [anon_sym_wsplit] = ACTIONS(271),
    [anon_sym_tsplit] = ACTIONS(271),
    [anon_sym_join] = ACTIONS(271),
    [anon_sym_trim] = ACTIONS(271),
    [anon_sym_trimStart] = ACTIONS(271),
    [anon_sym_trimEnd] = ACTIONS(271),
    [anon_sym_startsWith] = ACTIONS(271),
    [anon_sym_endsWith] = ACTIONS(271),
    [anon_sym_lower] = ACTIONS(271),
    [anon_sym_upper] = ACTIONS(271),
    [anon_sym_title] = ACTIONS(271),
    [anon_sym_leftPad] = ACTIONS(271),
    [anon_sym_findReplace] = ACTIONS(271),
    [anon_sym_in] = ACTIONS(271),
    [anon_sym_index] = ACTIONS(271),
    [anon_sym_lastIndexOf] = ACTIONS(271),
    [anon_sym_countSubStr] = ACTIONS(271),
    [anon_sym_parseJson] = ACTIONS(271),
    [anon_sym_parseCsv] = ACTIONS(271),
    [anon_sym_parseHtml] = ACTIONS(271),
    [anon_sym_parseExcel] = ACTIONS(271),
    [anon_sym_readFile] = ACTIONS(271),
    [anon_sym_readFileBytes] = ACTIONS(271),
    [anon_sym_readTsvFile] = ACTIONS(271),
    [anon_sym_writeFile] = ACTIONS(271),
    [anon_sym_appendFile] = ACTIONS(271),
    [anon_sym_fileExists] = ACTIONS(271),
    [anon_sym_isDir] = ACTIONS(271),
    [anon_sym_isFile] = ACTIONS(271),
    [anon_sym_fileSize] = ACTIONS(271),
    [anon_sym_cp] = ACTIONS(271),
    [anon_sym_mv] = ACTIONS(271),
    [anon_sym_rm] = ACTIONS(271),
    [anon_sym_rmf] = ACTIONS(271),
    [anon_sym_mkdir] = ACTIONS(271),
    [anon_sym_mkdirp] = ACTIONS(271),
    [anon_sym_cd] = ACTIONS(271),
    [anon_sym_pwd] = ACTIONS(271),
    [anon_sym_tempFile] = ACTIONS(271),
    [anon_sym_tempFileExt] = ACTIONS(271),
    [anon_sym_tempDir] = ACTIONS(271),
    [anon_sym_lsDir] = ACTIONS(271),
    [anon_sym_files] = ACTIONS(271),
    [anon_sym_dirs] = ACTIONS(271),
    [anon_sym_absPath] = ACTIONS(271),
    [anon_sym_dirname] = ACTIONS(271),
    [anon_sym_basename] = ACTIONS(271),
    [anon_sym_ext] = ACTIONS(271),
    [anon_sym_stem] = ACTIONS(271),
    [anon_sym_isCmd] = ACTIONS(271),
    [anon_sym_hardLink] = ACTIONS(271),
    [anon_sym_sha256sum] = ACTIONS(271),
    [anon_sym_md5] = ACTIONS(271),
    [anon_sym_now] = ACTIONS(271),
    [anon_sym_date] = ACTIONS(271),
    [anon_sym_year] = ACTIONS(271),
    [anon_sym_month] = ACTIONS(271),
    [anon_sym_day] = ACTIONS(271),
    [anon_sym_hour] = ACTIONS(271),
    [anon_sym_minute] = ACTIONS(271),
    [anon_sym_dateFmt] = ACTIONS(271),
    [anon_sym_isoDateFmt] = ACTIONS(271),
    [anon_sym_isoDateTimeFmt] = ACTIONS(271),
    [anon_sym_isWeekend] = ACTIONS(271),
    [anon_sym_isWeekday] = ACTIONS(271),
    [anon_sym_dow] = ACTIONS(271),
    [anon_sym_addDays] = ACTIONS(271),
    [anon_sym_toUnixTime] = ACTIONS(271),
    [anon_sym_toUnixTimeMilli] = ACTIONS(271),
    [anon_sym_toUnixTimeMicro] = ACTIONS(271),
    [anon_sym_toUnixTimeNano] = ACTIONS(271),
    [anon_sym_fromUnixTime] = ACTIONS(271),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(271),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(271),
    [anon_sym_fromUnixTimeNano] = ACTIONS(271),
    [anon_sym_toOleDate] = ACTIONS(271),
    [anon_sym_fromOleDate] = ACTIONS(271),
    [anon_sym_utcToCst] = ACTIONS(271),
    [anon_sym_cstToUtc] = ACTIONS(271),
    [anon_sym_reMatch] = ACTIONS(271),
    [anon_sym_reFindAll] = ACTIONS(271),
    [anon_sym_reFindAllIndex] = ACTIONS(271),
    [anon_sym_reReplace] = ACTIONS(271),
    [anon_sym_reSplit] = ACTIONS(271),
    [anon_sym_just] = ACTIONS(271),
    [anon_sym_none] = ACTIONS(271),
    [anon_sym_isNone] = ACTIONS(271),
    [anon_sym_maybe] = ACTIONS(271),
    [anon_sym_bind] = ACTIONS(271),
    [anon_sym_psub] = ACTIONS(271),
    [anon_sym_typeof] = ACTIONS(271),
    [anon_sym_runtime] = ACTIONS(271),
    [anon_sym_hostname] = ACTIONS(271),
    [anon_sym_httpGet] = ACTIONS(271),
    [anon_sym_httpPost] = ACTIONS(271),
    [anon_sym_urlEncode] = ACTIONS(271),
    [anon_sym_base64encode] = ACTIONS(271),
    [anon_sym_base64decode] = ACTIONS(271),
    [anon_sym_utf8Str] = ACTIONS(271),
    [anon_sym_utf8Bytes] = ACTIONS(271),
    [anon_sym_get] = ACTIONS(271),
    [anon_sym_getDef] = ACTIONS(271),
    [anon_sym_set] = ACTIONS(271),
    [anon_sym_setd] = ACTIONS(271),
    [anon_sym_keys] = ACTIONS(271),
    [anon_sym_values] = ACTIONS(271),
    [anon_sym_keyValues] = ACTIONS(271),
    [anon_sym_all] = ACTIONS(271),
    [anon_sym_any] = ACTIONS(271),
    [anon_sym_cartesian] = ACTIONS(271),
    [anon_sym_groupBy] = ACTIONS(271),
    [anon_sym_listToDict] = ACTIONS(271),
    [anon_sym_repeat] = ACTIONS(271),
    [anon_sym_seq] = ACTIONS(271),
    [anon_sym_tab] = ACTIONS(271),
    [anon_sym_select] = ACTIONS(271),
    [anon_sym_exclude] = ACTIONS(271),
    [anon_sym_derive] = ACTIONS(271),
    [anon_sym_updateCol] = ACTIONS(271),
    [anon_sym_gridValues] = ACTIONS(271),
    [anon_sym_leftJoin] = ACTIONS(271),
    [anon_sym_outerJoin] = ACTIONS(271),
    [anon_sym_linearSearch] = ACTIONS(271),
    [anon_sym_linearSearchIndex] = ACTIONS(271),
    [anon_sym_binPaths] = ACTIONS(271),
    [anon_sym_wt] = ACTIONS(271),
    [anon_sym_tt] = ACTIONS(271),
    [anon_sym_ttFile] = ACTIONS(271),
    [anon_sym_uw] = ACTIONS(271),
    [anon_sym_tuw] = ACTIONS(271),
    [anon_sym_strCmp] = ACTIONS(271),
    [anon_sym_floatCmp] = ACTIONS(271),
    [anon_sym_versionSortCmp] = ACTIONS(271),
    [anon_sym_id] = ACTIONS(271),
    [anon_sym_2id] = ACTIONS(271),
    [anon_sym_3id] = ACTIONS(271),
    [anon_sym_2unpack] = ACTIONS(271),
    [anon_sym_2apply] = ACTIONS(271),
    [anon_sym_2each] = ACTIONS(271),
    [anon_sym_2tuple] = ACTIONS(271),
    [anon_sym_DOTs] = ACTIONS(271),
    [anon_sym_DOTb] = ACTIONS(271),
    [anon_sym_DOTdef] = ACTIONS(271),
    [anon_sym_DOTenv] = ACTIONS(271),
    [sym_string] = ACTIONS(269),
    [sym_format_string] = ACTIONS(269),
    [sym_single_quoted_string] = ACTIONS(269),
    [sym_path] = ACTIONS(269),
    [sym_datetime] = ACTIONS(269),
    [sym_float] = ACTIONS(269),
    [sym_integer] = ACTIONS(271),
    [sym_env_store] = ACTIONS(269),
    [sym_env_check] = ACTIONS(269),
    [sym_env_retrieve] = ACTIONS(271),
    [sym_positional] = ACTIONS(269),
    [sym_var_retrieve] = ACTIONS(269),
    [sym_var_store] = ACTIONS(269),
    [sym_slice_indexer] = ACTIONS(269),
    [sym_indexer] = ACTIONS(269),
    [sym_end_indexer] = ACTIONS(271),
    [sym_start_indexer] = ACTIONS(271),
    [sym_match_arm_dup] = ACTIONS(269),
    [sym_prefix_quote] = ACTIONS(271),
    [anon_sym_GT] = ACTIONS(271),
    [anon_sym_GT_GT] = ACTIONS(269),
    [anon_sym_2_GT] = ACTIONS(271),
    [anon_sym_2_GT_GT] = ACTIONS(271),
    [anon_sym_AMP_GT] = ACTIONS(271),
    [anon_sym_AMP_GT_GT] = ACTIONS(269),
    [anon_sym_LT] = ACTIONS(271),
    [anon_sym_LT_GT] = ACTIONS(269),
    [anon_sym_STAR] = ACTIONS(271),
    [anon_sym_STARb] = ACTIONS(269),
    [anon_sym_CARET] = ACTIONS(271),
    [anon_sym_CARETb] = ACTIONS(269),
    [anon_sym_SEMI] = ACTIONS(269),
    [anon_sym_BANG] = ACTIONS(271),
    [anon_sym_QMARK] = ACTIONS(269),
    [anon_sym_BANG_EQ] = ACTIONS(269),
    [anon_sym_LT_EQ] = ACTIONS(269),
    [anon_sym_GT_EQ] = ACTIONS(269),
    [anon_sym_AMP] = ACTIONS(271),
    [anon_sym_PIPE] = ACTIONS(271),
    [anon_sym_COMMA] = ACTIONS(269),
    [anon_sym_COLON] = ACTIONS(271),
  },
  [48] = {
    [sym_identifier] = ACTIONS(299),
    [anon_sym_LBRACK] = ACTIONS(299),
    [anon_sym_LPAREN] = ACTIONS(297),
    [anon_sym_LBRACE] = ACTIONS(297),
    [anon_sym_LBRACK_PIPE] = ACTIONS(297),
    [anon_sym_PIPE_RBRACK] = ACTIONS(297),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(299),
    [anon_sym_false] = ACTIONS(299),
    [anon_sym_def] = ACTIONS(299),
    [anon_sym_end] = ACTIONS(299),
    [anon_sym_if] = ACTIONS(299),
    [anon_sym_iff] = ACTIONS(299),
    [anon_sym_else] = ACTIONS(299),
    [anon_sym_else_STAR] = ACTIONS(297),
    [anon_sym_STARif] = ACTIONS(297),
    [anon_sym_loop] = ACTIONS(299),
    [anon_sym_match] = ACTIONS(299),
    [anon_sym_break] = ACTIONS(299),
    [anon_sym_continue] = ACTIONS(299),
    [anon_sym_soe] = ACTIONS(299),
    [anon_sym_not] = ACTIONS(299),
    [anon_sym_and] = ACTIONS(299),
    [anon_sym_or] = ACTIONS(299),
    [anon_sym_read] = ACTIONS(299),
    [anon_sym_str] = ACTIONS(299),
    [anon_sym_as] = ACTIONS(299),
    [anon_sym_type] = ACTIONS(299),
    [anon_sym_try] = ACTIONS(299),
    [anon_sym_fail] = ACTIONS(299),
    [anon_sym_pure] = ACTIONS(299),
    [anon_sym_VER] = ACTIONS(299),
    [anon_sym_x] = ACTIONS(299),
    [anon_sym_int] = ACTIONS(299),
    [anon_sym_float] = ACTIONS(299),
    [anon_sym_bool] = ACTIONS(299),
    [anon_sym_dup] = ACTIONS(299),
    [anon_sym_swap] = ACTIONS(299),
    [anon_sym_drop] = ACTIONS(299),
    [anon_sym_over] = ACTIONS(299),
    [anon_sym_pick] = ACTIONS(299),
    [anon_sym_rot] = ACTIONS(299),
    [anon_sym_DASHrot] = ACTIONS(299),
    [anon_sym_nip] = ACTIONS(299),
    [anon_sym_w] = ACTIONS(299),
    [anon_sym_wl] = ACTIONS(299),
    [anon_sym_we] = ACTIONS(299),
    [anon_sym_wle] = ACTIONS(299),
    [anon_sym_len] = ACTIONS(299),
    [anon_sym_args] = ACTIONS(299),
    [anon_sym_glob] = ACTIONS(299),
    [anon_sym_toFloat] = ACTIONS(299),
    [anon_sym_toInt] = ACTIONS(299),
    [anon_sym_toPath] = ACTIONS(299),
    [anon_sym_toDt] = ACTIONS(299),
    [anon_sym_toGrid] = ACTIONS(299),
    [anon_sym_toCsv] = ACTIONS(299),
    [anon_sym_toCsvCell] = ACTIONS(299),
    [anon_sym_exit] = ACTIONS(299),
    [anon_sym_prompt] = ACTIONS(299),
    [anon_sym_stdin] = ACTIONS(299),
    [anon_sym_COLON_COLON] = ACTIONS(297),
    [anon_sym_foldl] = ACTIONS(299),
    [anon_sym_map] = ACTIONS(299),
    [anon_sym_each] = ACTIONS(299),
    [anon_sym_eachWhile] = ACTIONS(299),
    [anon_sym_filter] = ACTIONS(299),
    [anon_sym_append] = ACTIONS(299),
    [anon_sym_extend] = ACTIONS(299),
    [anon_sym_concat] = ACTIONS(299),
    [anon_sym_reverse] = ACTIONS(299),
    [anon_sym_sort] = ACTIONS(299),
    [anon_sym_sortV] = ACTIONS(299),
    [anon_sym_sortBy] = ACTIONS(299),
    [anon_sym_sortByCmp] = ACTIONS(299),
    [anon_sym_uniq] = ACTIONS(299),
    [anon_sym_zip] = ACTIONS(299),
    [anon_sym_enumerate] = ACTIONS(299),
    [anon_sym_enumerateN] = ACTIONS(299),
    [anon_sym_chunk] = ACTIONS(299),
    [anon_sym_pop] = ACTIONS(299),
    [anon_sym_take] = ACTIONS(299),
    [anon_sym_takeWhile] = ACTIONS(299),
    [anon_sym_skip] = ACTIONS(299),
    [anon_sym_dropWhile] = ACTIONS(299),
    [anon_sym_nth] = ACTIONS(299),
    [anon_sym_insert] = ACTIONS(299),
    [anon_sym_setAt] = ACTIONS(299),
    [anon_sym_del] = ACTIONS(299),
    [anon_sym_sum] = ACTIONS(299),
    [anon_sym_max] = ACTIONS(299),
    [anon_sym_max2] = ACTIONS(299),
    [anon_sym_min] = ACTIONS(299),
    [anon_sym_min2] = ACTIONS(299),
    [anon_sym_abs] = ACTIONS(299),
    [anon_sym_inc] = ACTIONS(299),
    [anon_sym_mod] = ACTIONS(299),
    [anon_sym_floor] = ACTIONS(299),
    [anon_sym_ceil] = ACTIONS(299),
    [anon_sym_round] = ACTIONS(299),
    [anon_sym_lines] = ACTIONS(299),
    [anon_sym_unlines] = ACTIONS(299),
    [anon_sym_unlinesCrLf] = ACTIONS(299),
    [anon_sym_split] = ACTIONS(299),
    [anon_sym_wsplit] = ACTIONS(299),
    [anon_sym_tsplit] = ACTIONS(299),
    [anon_sym_join] = ACTIONS(299),
    [anon_sym_trim] = ACTIONS(299),
    [anon_sym_trimStart] = ACTIONS(299),
    [anon_sym_trimEnd] = ACTIONS(299),
    [anon_sym_startsWith] = ACTIONS(299),
    [anon_sym_endsWith] = ACTIONS(299),
    [anon_sym_lower] = ACTIONS(299),
    [anon_sym_upper] = ACTIONS(299),
    [anon_sym_title] = ACTIONS(299),
    [anon_sym_leftPad] = ACTIONS(299),
    [anon_sym_findReplace] = ACTIONS(299),
    [anon_sym_in] = ACTIONS(299),
    [anon_sym_index] = ACTIONS(299),
    [anon_sym_lastIndexOf] = ACTIONS(299),
    [anon_sym_countSubStr] = ACTIONS(299),
    [anon_sym_parseJson] = ACTIONS(299),
    [anon_sym_parseCsv] = ACTIONS(299),
    [anon_sym_parseHtml] = ACTIONS(299),
    [anon_sym_parseExcel] = ACTIONS(299),
    [anon_sym_readFile] = ACTIONS(299),
    [anon_sym_readFileBytes] = ACTIONS(299),
    [anon_sym_readTsvFile] = ACTIONS(299),
    [anon_sym_writeFile] = ACTIONS(299),
    [anon_sym_appendFile] = ACTIONS(299),
    [anon_sym_fileExists] = ACTIONS(299),
    [anon_sym_isDir] = ACTIONS(299),
    [anon_sym_isFile] = ACTIONS(299),
    [anon_sym_fileSize] = ACTIONS(299),
    [anon_sym_cp] = ACTIONS(299),
    [anon_sym_mv] = ACTIONS(299),
    [anon_sym_rm] = ACTIONS(299),
    [anon_sym_rmf] = ACTIONS(299),
    [anon_sym_mkdir] = ACTIONS(299),
    [anon_sym_mkdirp] = ACTIONS(299),
    [anon_sym_cd] = ACTIONS(299),
    [anon_sym_pwd] = ACTIONS(299),
    [anon_sym_tempFile] = ACTIONS(299),
    [anon_sym_tempFileExt] = ACTIONS(299),
    [anon_sym_tempDir] = ACTIONS(299),
    [anon_sym_lsDir] = ACTIONS(299),
    [anon_sym_files] = ACTIONS(299),
    [anon_sym_dirs] = ACTIONS(299),
    [anon_sym_absPath] = ACTIONS(299),
    [anon_sym_dirname] = ACTIONS(299),
    [anon_sym_basename] = ACTIONS(299),
    [anon_sym_ext] = ACTIONS(299),
    [anon_sym_stem] = ACTIONS(299),
    [anon_sym_isCmd] = ACTIONS(299),
    [anon_sym_hardLink] = ACTIONS(299),
    [anon_sym_sha256sum] = ACTIONS(299),
    [anon_sym_md5] = ACTIONS(299),
    [anon_sym_now] = ACTIONS(299),
    [anon_sym_date] = ACTIONS(299),
    [anon_sym_year] = ACTIONS(299),
    [anon_sym_month] = ACTIONS(299),
    [anon_sym_day] = ACTIONS(299),
    [anon_sym_hour] = ACTIONS(299),
    [anon_sym_minute] = ACTIONS(299),
    [anon_sym_dateFmt] = ACTIONS(299),
    [anon_sym_isoDateFmt] = ACTIONS(299),
    [anon_sym_isoDateTimeFmt] = ACTIONS(299),
    [anon_sym_isWeekend] = ACTIONS(299),
    [anon_sym_isWeekday] = ACTIONS(299),
    [anon_sym_dow] = ACTIONS(299),
    [anon_sym_addDays] = ACTIONS(299),
    [anon_sym_toUnixTime] = ACTIONS(299),
    [anon_sym_toUnixTimeMilli] = ACTIONS(299),
    [anon_sym_toUnixTimeMicro] = ACTIONS(299),
    [anon_sym_toUnixTimeNano] = ACTIONS(299),
    [anon_sym_fromUnixTime] = ACTIONS(299),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(299),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(299),
    [anon_sym_fromUnixTimeNano] = ACTIONS(299),
    [anon_sym_toOleDate] = ACTIONS(299),
    [anon_sym_fromOleDate] = ACTIONS(299),
    [anon_sym_utcToCst] = ACTIONS(299),
    [anon_sym_cstToUtc] = ACTIONS(299),
    [anon_sym_reMatch] = ACTIONS(299),
    [anon_sym_reFindAll] = ACTIONS(299),
    [anon_sym_reFindAllIndex] = ACTIONS(299),
    [anon_sym_reReplace] = ACTIONS(299),
    [anon_sym_reSplit] = ACTIONS(299),
    [anon_sym_just] = ACTIONS(299),
    [anon_sym_none] = ACTIONS(299),
    [anon_sym_isNone] = ACTIONS(299),
    [anon_sym_maybe] = ACTIONS(299),
    [anon_sym_bind] = ACTIONS(299),
    [anon_sym_psub] = ACTIONS(299),
    [anon_sym_typeof] = ACTIONS(299),
    [anon_sym_runtime] = ACTIONS(299),
    [anon_sym_hostname] = ACTIONS(299),
    [anon_sym_httpGet] = ACTIONS(299),
    [anon_sym_httpPost] = ACTIONS(299),
    [anon_sym_urlEncode] = ACTIONS(299),
    [anon_sym_base64encode] = ACTIONS(299),
    [anon_sym_base64decode] = ACTIONS(299),
    [anon_sym_utf8Str] = ACTIONS(299),
    [anon_sym_utf8Bytes] = ACTIONS(299),
    [anon_sym_get] = ACTIONS(299),
    [anon_sym_getDef] = ACTIONS(299),
    [anon_sym_set] = ACTIONS(299),
    [anon_sym_setd] = ACTIONS(299),
    [anon_sym_keys] = ACTIONS(299),
    [anon_sym_values] = ACTIONS(299),
    [anon_sym_keyValues] = ACTIONS(299),
    [anon_sym_all] = ACTIONS(299),
    [anon_sym_any] = ACTIONS(299),
    [anon_sym_cartesian] = ACTIONS(299),
    [anon_sym_groupBy] = ACTIONS(299),
    [anon_sym_listToDict] = ACTIONS(299),
    [anon_sym_repeat] = ACTIONS(299),
    [anon_sym_seq] = ACTIONS(299),
    [anon_sym_tab] = ACTIONS(299),
    [anon_sym_select] = ACTIONS(299),
    [anon_sym_exclude] = ACTIONS(299),
    [anon_sym_derive] = ACTIONS(299),
    [anon_sym_updateCol] = ACTIONS(299),
    [anon_sym_gridValues] = ACTIONS(299),
    [anon_sym_leftJoin] = ACTIONS(299),
    [anon_sym_outerJoin] = ACTIONS(299),
    [anon_sym_linearSearch] = ACTIONS(299),
    [anon_sym_linearSearchIndex] = ACTIONS(299),
    [anon_sym_binPaths] = ACTIONS(299),
    [anon_sym_wt] = ACTIONS(299),
    [anon_sym_tt] = ACTIONS(299),
    [anon_sym_ttFile] = ACTIONS(299),
    [anon_sym_uw] = ACTIONS(299),
    [anon_sym_tuw] = ACTIONS(299),
    [anon_sym_strCmp] = ACTIONS(299),
    [anon_sym_floatCmp] = ACTIONS(299),
    [anon_sym_versionSortCmp] = ACTIONS(299),
    [anon_sym_id] = ACTIONS(299),
    [anon_sym_2id] = ACTIONS(299),
    [anon_sym_3id] = ACTIONS(299),
    [anon_sym_2unpack] = ACTIONS(299),
    [anon_sym_2apply] = ACTIONS(299),
    [anon_sym_2each] = ACTIONS(299),
    [anon_sym_2tuple] = ACTIONS(299),
    [anon_sym_DOTs] = ACTIONS(299),
    [anon_sym_DOTb] = ACTIONS(299),
    [anon_sym_DOTdef] = ACTIONS(299),
    [anon_sym_DOTenv] = ACTIONS(299),
    [sym_string] = ACTIONS(297),
    [sym_format_string] = ACTIONS(297),
    [sym_single_quoted_string] = ACTIONS(297),
    [sym_path] = ACTIONS(297),
    [sym_datetime] = ACTIONS(297),
    [sym_float] = ACTIONS(297),
    [sym_integer] = ACTIONS(299),
    [sym_env_store] = ACTIONS(297),
    [sym_env_check] = ACTIONS(297),
    [sym_env_retrieve] = ACTIONS(299),
    [sym_positional] = ACTIONS(297),
    [sym_var_retrieve] = ACTIONS(297),
    [sym_var_store] = ACTIONS(297),
    [sym_slice_indexer] = ACTIONS(297),
    [sym_indexer] = ACTIONS(297),
    [sym_end_indexer] = ACTIONS(299),
    [sym_start_indexer] = ACTIONS(299),
    [sym_match_arm_dup] = ACTIONS(297),
    [sym_prefix_quote] = ACTIONS(299),
    [anon_sym_GT] = ACTIONS(299),
    [anon_sym_GT_GT] = ACTIONS(297),
    [anon_sym_2_GT] = ACTIONS(299),
    [anon_sym_2_GT_GT] = ACTIONS(299),
    [anon_sym_AMP_GT] = ACTIONS(299),
    [anon_sym_AMP_GT_GT] = ACTIONS(297),
    [anon_sym_LT] = ACTIONS(299),
    [anon_sym_LT_GT] = ACTIONS(297),
    [anon_sym_STAR] = ACTIONS(299),
    [anon_sym_STARb] = ACTIONS(297),
    [anon_sym_CARET] = ACTIONS(299),
    [anon_sym_CARETb] = ACTIONS(297),
    [anon_sym_SEMI] = ACTIONS(297),
    [anon_sym_BANG] = ACTIONS(299),
    [anon_sym_QMARK] = ACTIONS(297),
    [anon_sym_BANG_EQ] = ACTIONS(297),
    [anon_sym_LT_EQ] = ACTIONS(297),
    [anon_sym_GT_EQ] = ACTIONS(297),
    [anon_sym_AMP] = ACTIONS(299),
    [anon_sym_PIPE] = ACTIONS(299),
    [anon_sym_COMMA] = ACTIONS(297),
    [anon_sym_COLON] = ACTIONS(299),
  },
  [49] = {
    [sym_identifier] = ACTIONS(327),
    [anon_sym_LBRACK] = ACTIONS(327),
    [anon_sym_LPAREN] = ACTIONS(325),
    [anon_sym_LBRACE] = ACTIONS(325),
    [anon_sym_LBRACK_PIPE] = ACTIONS(325),
    [anon_sym_PIPE_RBRACK] = ACTIONS(325),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(327),
    [anon_sym_false] = ACTIONS(327),
    [anon_sym_def] = ACTIONS(327),
    [anon_sym_end] = ACTIONS(327),
    [anon_sym_if] = ACTIONS(327),
    [anon_sym_iff] = ACTIONS(327),
    [anon_sym_else] = ACTIONS(327),
    [anon_sym_else_STAR] = ACTIONS(325),
    [anon_sym_STARif] = ACTIONS(325),
    [anon_sym_loop] = ACTIONS(327),
    [anon_sym_match] = ACTIONS(327),
    [anon_sym_break] = ACTIONS(327),
    [anon_sym_continue] = ACTIONS(327),
    [anon_sym_soe] = ACTIONS(327),
    [anon_sym_not] = ACTIONS(327),
    [anon_sym_and] = ACTIONS(327),
    [anon_sym_or] = ACTIONS(327),
    [anon_sym_read] = ACTIONS(327),
    [anon_sym_str] = ACTIONS(327),
    [anon_sym_as] = ACTIONS(327),
    [anon_sym_type] = ACTIONS(327),
    [anon_sym_try] = ACTIONS(327),
    [anon_sym_fail] = ACTIONS(327),
    [anon_sym_pure] = ACTIONS(327),
    [anon_sym_VER] = ACTIONS(327),
    [anon_sym_x] = ACTIONS(327),
    [anon_sym_int] = ACTIONS(327),
    [anon_sym_float] = ACTIONS(327),
    [anon_sym_bool] = ACTIONS(327),
    [anon_sym_dup] = ACTIONS(327),
    [anon_sym_swap] = ACTIONS(327),
    [anon_sym_drop] = ACTIONS(327),
    [anon_sym_over] = ACTIONS(327),
    [anon_sym_pick] = ACTIONS(327),
    [anon_sym_rot] = ACTIONS(327),
    [anon_sym_DASHrot] = ACTIONS(327),
    [anon_sym_nip] = ACTIONS(327),
    [anon_sym_w] = ACTIONS(327),
    [anon_sym_wl] = ACTIONS(327),
    [anon_sym_we] = ACTIONS(327),
    [anon_sym_wle] = ACTIONS(327),
    [anon_sym_len] = ACTIONS(327),
    [anon_sym_args] = ACTIONS(327),
    [anon_sym_glob] = ACTIONS(327),
    [anon_sym_toFloat] = ACTIONS(327),
    [anon_sym_toInt] = ACTIONS(327),
    [anon_sym_toPath] = ACTIONS(327),
    [anon_sym_toDt] = ACTIONS(327),
    [anon_sym_toGrid] = ACTIONS(327),
    [anon_sym_toCsv] = ACTIONS(327),
    [anon_sym_toCsvCell] = ACTIONS(327),
    [anon_sym_exit] = ACTIONS(327),
    [anon_sym_prompt] = ACTIONS(327),
    [anon_sym_stdin] = ACTIONS(327),
    [anon_sym_COLON_COLON] = ACTIONS(325),
    [anon_sym_foldl] = ACTIONS(327),
    [anon_sym_map] = ACTIONS(327),
    [anon_sym_each] = ACTIONS(327),
    [anon_sym_eachWhile] = ACTIONS(327),
    [anon_sym_filter] = ACTIONS(327),
    [anon_sym_append] = ACTIONS(327),
    [anon_sym_extend] = ACTIONS(327),
    [anon_sym_concat] = ACTIONS(327),
    [anon_sym_reverse] = ACTIONS(327),
    [anon_sym_sort] = ACTIONS(327),
    [anon_sym_sortV] = ACTIONS(327),
    [anon_sym_sortBy] = ACTIONS(327),
    [anon_sym_sortByCmp] = ACTIONS(327),
    [anon_sym_uniq] = ACTIONS(327),
    [anon_sym_zip] = ACTIONS(327),
    [anon_sym_enumerate] = ACTIONS(327),
    [anon_sym_enumerateN] = ACTIONS(327),
    [anon_sym_chunk] = ACTIONS(327),
    [anon_sym_pop] = ACTIONS(327),
    [anon_sym_take] = ACTIONS(327),
    [anon_sym_takeWhile] = ACTIONS(327),
    [anon_sym_skip] = ACTIONS(327),
    [anon_sym_dropWhile] = ACTIONS(327),
    [anon_sym_nth] = ACTIONS(327),
    [anon_sym_insert] = ACTIONS(327),
    [anon_sym_setAt] = ACTIONS(327),
    [anon_sym_del] = ACTIONS(327),
    [anon_sym_sum] = ACTIONS(327),
    [anon_sym_max] = ACTIONS(327),
    [anon_sym_max2] = ACTIONS(327),
    [anon_sym_min] = ACTIONS(327),
    [anon_sym_min2] = ACTIONS(327),
    [anon_sym_abs] = ACTIONS(327),
    [anon_sym_inc] = ACTIONS(327),
    [anon_sym_mod] = ACTIONS(327),
    [anon_sym_floor] = ACTIONS(327),
    [anon_sym_ceil] = ACTIONS(327),
    [anon_sym_round] = ACTIONS(327),
    [anon_sym_lines] = ACTIONS(327),
    [anon_sym_unlines] = ACTIONS(327),
    [anon_sym_unlinesCrLf] = ACTIONS(327),
    [anon_sym_split] = ACTIONS(327),
    [anon_sym_wsplit] = ACTIONS(327),
    [anon_sym_tsplit] = ACTIONS(327),
    [anon_sym_join] = ACTIONS(327),
    [anon_sym_trim] = ACTIONS(327),
    [anon_sym_trimStart] = ACTIONS(327),
    [anon_sym_trimEnd] = ACTIONS(327),
    [anon_sym_startsWith] = ACTIONS(327),
    [anon_sym_endsWith] = ACTIONS(327),
    [anon_sym_lower] = ACTIONS(327),
    [anon_sym_upper] = ACTIONS(327),
    [anon_sym_title] = ACTIONS(327),
    [anon_sym_leftPad] = ACTIONS(327),
    [anon_sym_findReplace] = ACTIONS(327),
    [anon_sym_in] = ACTIONS(327),
    [anon_sym_index] = ACTIONS(327),
    [anon_sym_lastIndexOf] = ACTIONS(327),
    [anon_sym_countSubStr] = ACTIONS(327),
    [anon_sym_parseJson] = ACTIONS(327),
    [anon_sym_parseCsv] = ACTIONS(327),
    [anon_sym_parseHtml] = ACTIONS(327),
    [anon_sym_parseExcel] = ACTIONS(327),
    [anon_sym_readFile] = ACTIONS(327),
    [anon_sym_readFileBytes] = ACTIONS(327),
    [anon_sym_readTsvFile] = ACTIONS(327),
    [anon_sym_writeFile] = ACTIONS(327),
    [anon_sym_appendFile] = ACTIONS(327),
    [anon_sym_fileExists] = ACTIONS(327),
    [anon_sym_isDir] = ACTIONS(327),
    [anon_sym_isFile] = ACTIONS(327),
    [anon_sym_fileSize] = ACTIONS(327),
    [anon_sym_cp] = ACTIONS(327),
    [anon_sym_mv] = ACTIONS(327),
    [anon_sym_rm] = ACTIONS(327),
    [anon_sym_rmf] = ACTIONS(327),
    [anon_sym_mkdir] = ACTIONS(327),
    [anon_sym_mkdirp] = ACTIONS(327),
    [anon_sym_cd] = ACTIONS(327),
    [anon_sym_pwd] = ACTIONS(327),
    [anon_sym_tempFile] = ACTIONS(327),
    [anon_sym_tempFileExt] = ACTIONS(327),
    [anon_sym_tempDir] = ACTIONS(327),
    [anon_sym_lsDir] = ACTIONS(327),
    [anon_sym_files] = ACTIONS(327),
    [anon_sym_dirs] = ACTIONS(327),
    [anon_sym_absPath] = ACTIONS(327),
    [anon_sym_dirname] = ACTIONS(327),
    [anon_sym_basename] = ACTIONS(327),
    [anon_sym_ext] = ACTIONS(327),
    [anon_sym_stem] = ACTIONS(327),
    [anon_sym_isCmd] = ACTIONS(327),
    [anon_sym_hardLink] = ACTIONS(327),
    [anon_sym_sha256sum] = ACTIONS(327),
    [anon_sym_md5] = ACTIONS(327),
    [anon_sym_now] = ACTIONS(327),
    [anon_sym_date] = ACTIONS(327),
    [anon_sym_year] = ACTIONS(327),
    [anon_sym_month] = ACTIONS(327),
    [anon_sym_day] = ACTIONS(327),
    [anon_sym_hour] = ACTIONS(327),
    [anon_sym_minute] = ACTIONS(327),
    [anon_sym_dateFmt] = ACTIONS(327),
    [anon_sym_isoDateFmt] = ACTIONS(327),
    [anon_sym_isoDateTimeFmt] = ACTIONS(327),
    [anon_sym_isWeekend] = ACTIONS(327),
    [anon_sym_isWeekday] = ACTIONS(327),
    [anon_sym_dow] = ACTIONS(327),
    [anon_sym_addDays] = ACTIONS(327),
    [anon_sym_toUnixTime] = ACTIONS(327),
    [anon_sym_toUnixTimeMilli] = ACTIONS(327),
    [anon_sym_toUnixTimeMicro] = ACTIONS(327),
    [anon_sym_toUnixTimeNano] = ACTIONS(327),
    [anon_sym_fromUnixTime] = ACTIONS(327),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(327),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(327),
    [anon_sym_fromUnixTimeNano] = ACTIONS(327),
    [anon_sym_toOleDate] = ACTIONS(327),
    [anon_sym_fromOleDate] = ACTIONS(327),
    [anon_sym_utcToCst] = ACTIONS(327),
    [anon_sym_cstToUtc] = ACTIONS(327),
    [anon_sym_reMatch] = ACTIONS(327),
    [anon_sym_reFindAll] = ACTIONS(327),
    [anon_sym_reFindAllIndex] = ACTIONS(327),
    [anon_sym_reReplace] = ACTIONS(327),
    [anon_sym_reSplit] = ACTIONS(327),
    [anon_sym_just] = ACTIONS(327),
    [anon_sym_none] = ACTIONS(327),
    [anon_sym_isNone] = ACTIONS(327),
    [anon_sym_maybe] = ACTIONS(327),
    [anon_sym_bind] = ACTIONS(327),
    [anon_sym_psub] = ACTIONS(327),
    [anon_sym_typeof] = ACTIONS(327),
    [anon_sym_runtime] = ACTIONS(327),
    [anon_sym_hostname] = ACTIONS(327),
    [anon_sym_httpGet] = ACTIONS(327),
    [anon_sym_httpPost] = ACTIONS(327),
    [anon_sym_urlEncode] = ACTIONS(327),
    [anon_sym_base64encode] = ACTIONS(327),
    [anon_sym_base64decode] = ACTIONS(327),
    [anon_sym_utf8Str] = ACTIONS(327),
    [anon_sym_utf8Bytes] = ACTIONS(327),
    [anon_sym_get] = ACTIONS(327),
    [anon_sym_getDef] = ACTIONS(327),
    [anon_sym_set] = ACTIONS(327),
    [anon_sym_setd] = ACTIONS(327),
    [anon_sym_keys] = ACTIONS(327),
    [anon_sym_values] = ACTIONS(327),
    [anon_sym_keyValues] = ACTIONS(327),
    [anon_sym_all] = ACTIONS(327),
    [anon_sym_any] = ACTIONS(327),
    [anon_sym_cartesian] = ACTIONS(327),
    [anon_sym_groupBy] = ACTIONS(327),
    [anon_sym_listToDict] = ACTIONS(327),
    [anon_sym_repeat] = ACTIONS(327),
    [anon_sym_seq] = ACTIONS(327),
    [anon_sym_tab] = ACTIONS(327),
    [anon_sym_select] = ACTIONS(327),
    [anon_sym_exclude] = ACTIONS(327),
    [anon_sym_derive] = ACTIONS(327),
    [anon_sym_updateCol] = ACTIONS(327),
    [anon_sym_gridValues] = ACTIONS(327),
    [anon_sym_leftJoin] = ACTIONS(327),
    [anon_sym_outerJoin] = ACTIONS(327),
    [anon_sym_linearSearch] = ACTIONS(327),
    [anon_sym_linearSearchIndex] = ACTIONS(327),
    [anon_sym_binPaths] = ACTIONS(327),
    [anon_sym_wt] = ACTIONS(327),
    [anon_sym_tt] = ACTIONS(327),
    [anon_sym_ttFile] = ACTIONS(327),
    [anon_sym_uw] = ACTIONS(327),
    [anon_sym_tuw] = ACTIONS(327),
    [anon_sym_strCmp] = ACTIONS(327),
    [anon_sym_floatCmp] = ACTIONS(327),
    [anon_sym_versionSortCmp] = ACTIONS(327),
    [anon_sym_id] = ACTIONS(327),
    [anon_sym_2id] = ACTIONS(327),
    [anon_sym_3id] = ACTIONS(327),
    [anon_sym_2unpack] = ACTIONS(327),
    [anon_sym_2apply] = ACTIONS(327),
    [anon_sym_2each] = ACTIONS(327),
    [anon_sym_2tuple] = ACTIONS(327),
    [anon_sym_DOTs] = ACTIONS(327),
    [anon_sym_DOTb] = ACTIONS(327),
    [anon_sym_DOTdef] = ACTIONS(327),
    [anon_sym_DOTenv] = ACTIONS(327),
    [sym_string] = ACTIONS(325),
    [sym_format_string] = ACTIONS(325),
    [sym_single_quoted_string] = ACTIONS(325),
    [sym_path] = ACTIONS(325),
    [sym_datetime] = ACTIONS(325),
    [sym_float] = ACTIONS(325),
    [sym_integer] = ACTIONS(327),
    [sym_env_store] = ACTIONS(325),
    [sym_env_check] = ACTIONS(325),
    [sym_env_retrieve] = ACTIONS(327),
    [sym_positional] = ACTIONS(325),
    [sym_var_retrieve] = ACTIONS(325),
    [sym_var_store] = ACTIONS(325),
    [sym_slice_indexer] = ACTIONS(325),
    [sym_indexer] = ACTIONS(325),
    [sym_end_indexer] = ACTIONS(327),
    [sym_start_indexer] = ACTIONS(327),
    [sym_match_arm_dup] = ACTIONS(325),
    [sym_prefix_quote] = ACTIONS(327),
    [anon_sym_GT] = ACTIONS(327),
    [anon_sym_GT_GT] = ACTIONS(325),
    [anon_sym_2_GT] = ACTIONS(327),
    [anon_sym_2_GT_GT] = ACTIONS(327),
    [anon_sym_AMP_GT] = ACTIONS(327),
    [anon_sym_AMP_GT_GT] = ACTIONS(325),
    [anon_sym_LT] = ACTIONS(327),
    [anon_sym_LT_GT] = ACTIONS(325),
    [anon_sym_STAR] = ACTIONS(327),
    [anon_sym_STARb] = ACTIONS(325),
    [anon_sym_CARET] = ACTIONS(327),
    [anon_sym_CARETb] = ACTIONS(325),
    [anon_sym_SEMI] = ACTIONS(325),
    [anon_sym_BANG] = ACTIONS(327),
    [anon_sym_QMARK] = ACTIONS(325),
    [anon_sym_BANG_EQ] = ACTIONS(325),
    [anon_sym_LT_EQ] = ACTIONS(325),
    [anon_sym_GT_EQ] = ACTIONS(325),
    [anon_sym_AMP] = ACTIONS(327),
    [anon_sym_PIPE] = ACTIONS(327),
    [anon_sym_COMMA] = ACTIONS(325),
    [anon_sym_COLON] = ACTIONS(327),
  },
  [50] = {
    [sym_identifier] = ACTIONS(275),
    [anon_sym_LBRACK] = ACTIONS(275),
    [anon_sym_LPAREN] = ACTIONS(273),
    [anon_sym_LBRACE] = ACTIONS(273),
    [anon_sym_LBRACK_PIPE] = ACTIONS(273),
    [anon_sym_PIPE_RBRACK] = ACTIONS(273),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(275),
    [anon_sym_false] = ACTIONS(275),
    [anon_sym_def] = ACTIONS(275),
    [anon_sym_end] = ACTIONS(275),
    [anon_sym_if] = ACTIONS(275),
    [anon_sym_iff] = ACTIONS(275),
    [anon_sym_else] = ACTIONS(275),
    [anon_sym_else_STAR] = ACTIONS(273),
    [anon_sym_STARif] = ACTIONS(273),
    [anon_sym_loop] = ACTIONS(275),
    [anon_sym_match] = ACTIONS(275),
    [anon_sym_break] = ACTIONS(275),
    [anon_sym_continue] = ACTIONS(275),
    [anon_sym_soe] = ACTIONS(275),
    [anon_sym_not] = ACTIONS(275),
    [anon_sym_and] = ACTIONS(275),
    [anon_sym_or] = ACTIONS(275),
    [anon_sym_read] = ACTIONS(275),
    [anon_sym_str] = ACTIONS(275),
    [anon_sym_as] = ACTIONS(275),
    [anon_sym_type] = ACTIONS(275),
    [anon_sym_try] = ACTIONS(275),
    [anon_sym_fail] = ACTIONS(275),
    [anon_sym_pure] = ACTIONS(275),
    [anon_sym_VER] = ACTIONS(275),
    [anon_sym_x] = ACTIONS(275),
    [anon_sym_int] = ACTIONS(275),
    [anon_sym_float] = ACTIONS(275),
    [anon_sym_bool] = ACTIONS(275),
    [anon_sym_dup] = ACTIONS(275),
    [anon_sym_swap] = ACTIONS(275),
    [anon_sym_drop] = ACTIONS(275),
    [anon_sym_over] = ACTIONS(275),
    [anon_sym_pick] = ACTIONS(275),
    [anon_sym_rot] = ACTIONS(275),
    [anon_sym_DASHrot] = ACTIONS(275),
    [anon_sym_nip] = ACTIONS(275),
    [anon_sym_w] = ACTIONS(275),
    [anon_sym_wl] = ACTIONS(275),
    [anon_sym_we] = ACTIONS(275),
    [anon_sym_wle] = ACTIONS(275),
    [anon_sym_len] = ACTIONS(275),
    [anon_sym_args] = ACTIONS(275),
    [anon_sym_glob] = ACTIONS(275),
    [anon_sym_toFloat] = ACTIONS(275),
    [anon_sym_toInt] = ACTIONS(275),
    [anon_sym_toPath] = ACTIONS(275),
    [anon_sym_toDt] = ACTIONS(275),
    [anon_sym_toGrid] = ACTIONS(275),
    [anon_sym_toCsv] = ACTIONS(275),
    [anon_sym_toCsvCell] = ACTIONS(275),
    [anon_sym_exit] = ACTIONS(275),
    [anon_sym_prompt] = ACTIONS(275),
    [anon_sym_stdin] = ACTIONS(275),
    [anon_sym_COLON_COLON] = ACTIONS(273),
    [anon_sym_foldl] = ACTIONS(275),
    [anon_sym_map] = ACTIONS(275),
    [anon_sym_each] = ACTIONS(275),
    [anon_sym_eachWhile] = ACTIONS(275),
    [anon_sym_filter] = ACTIONS(275),
    [anon_sym_append] = ACTIONS(275),
    [anon_sym_extend] = ACTIONS(275),
    [anon_sym_concat] = ACTIONS(275),
    [anon_sym_reverse] = ACTIONS(275),
    [anon_sym_sort] = ACTIONS(275),
    [anon_sym_sortV] = ACTIONS(275),
    [anon_sym_sortBy] = ACTIONS(275),
    [anon_sym_sortByCmp] = ACTIONS(275),
    [anon_sym_uniq] = ACTIONS(275),
    [anon_sym_zip] = ACTIONS(275),
    [anon_sym_enumerate] = ACTIONS(275),
    [anon_sym_enumerateN] = ACTIONS(275),
    [anon_sym_chunk] = ACTIONS(275),
    [anon_sym_pop] = ACTIONS(275),
    [anon_sym_take] = ACTIONS(275),
    [anon_sym_takeWhile] = ACTIONS(275),
    [anon_sym_skip] = ACTIONS(275),
    [anon_sym_dropWhile] = ACTIONS(275),
    [anon_sym_nth] = ACTIONS(275),
    [anon_sym_insert] = ACTIONS(275),
    [anon_sym_setAt] = ACTIONS(275),
    [anon_sym_del] = ACTIONS(275),
    [anon_sym_sum] = ACTIONS(275),
    [anon_sym_max] = ACTIONS(275),
    [anon_sym_max2] = ACTIONS(275),
    [anon_sym_min] = ACTIONS(275),
    [anon_sym_min2] = ACTIONS(275),
    [anon_sym_abs] = ACTIONS(275),
    [anon_sym_inc] = ACTIONS(275),
    [anon_sym_mod] = ACTIONS(275),
    [anon_sym_floor] = ACTIONS(275),
    [anon_sym_ceil] = ACTIONS(275),
    [anon_sym_round] = ACTIONS(275),
    [anon_sym_lines] = ACTIONS(275),
    [anon_sym_unlines] = ACTIONS(275),
    [anon_sym_unlinesCrLf] = ACTIONS(275),
    [anon_sym_split] = ACTIONS(275),
    [anon_sym_wsplit] = ACTIONS(275),
    [anon_sym_tsplit] = ACTIONS(275),
    [anon_sym_join] = ACTIONS(275),
    [anon_sym_trim] = ACTIONS(275),
    [anon_sym_trimStart] = ACTIONS(275),
    [anon_sym_trimEnd] = ACTIONS(275),
    [anon_sym_startsWith] = ACTIONS(275),
    [anon_sym_endsWith] = ACTIONS(275),
    [anon_sym_lower] = ACTIONS(275),
    [anon_sym_upper] = ACTIONS(275),
    [anon_sym_title] = ACTIONS(275),
    [anon_sym_leftPad] = ACTIONS(275),
    [anon_sym_findReplace] = ACTIONS(275),
    [anon_sym_in] = ACTIONS(275),
    [anon_sym_index] = ACTIONS(275),
    [anon_sym_lastIndexOf] = ACTIONS(275),
    [anon_sym_countSubStr] = ACTIONS(275),
    [anon_sym_parseJson] = ACTIONS(275),
    [anon_sym_parseCsv] = ACTIONS(275),
    [anon_sym_parseHtml] = ACTIONS(275),
    [anon_sym_parseExcel] = ACTIONS(275),
    [anon_sym_readFile] = ACTIONS(275),
    [anon_sym_readFileBytes] = ACTIONS(275),
    [anon_sym_readTsvFile] = ACTIONS(275),
    [anon_sym_writeFile] = ACTIONS(275),
    [anon_sym_appendFile] = ACTIONS(275),
    [anon_sym_fileExists] = ACTIONS(275),
    [anon_sym_isDir] = ACTIONS(275),
    [anon_sym_isFile] = ACTIONS(275),
    [anon_sym_fileSize] = ACTIONS(275),
    [anon_sym_cp] = ACTIONS(275),
    [anon_sym_mv] = ACTIONS(275),
    [anon_sym_rm] = ACTIONS(275),
    [anon_sym_rmf] = ACTIONS(275),
    [anon_sym_mkdir] = ACTIONS(275),
    [anon_sym_mkdirp] = ACTIONS(275),
    [anon_sym_cd] = ACTIONS(275),
    [anon_sym_pwd] = ACTIONS(275),
    [anon_sym_tempFile] = ACTIONS(275),
    [anon_sym_tempFileExt] = ACTIONS(275),
    [anon_sym_tempDir] = ACTIONS(275),
    [anon_sym_lsDir] = ACTIONS(275),
    [anon_sym_files] = ACTIONS(275),
    [anon_sym_dirs] = ACTIONS(275),
    [anon_sym_absPath] = ACTIONS(275),
    [anon_sym_dirname] = ACTIONS(275),
    [anon_sym_basename] = ACTIONS(275),
    [anon_sym_ext] = ACTIONS(275),
    [anon_sym_stem] = ACTIONS(275),
    [anon_sym_isCmd] = ACTIONS(275),
    [anon_sym_hardLink] = ACTIONS(275),
    [anon_sym_sha256sum] = ACTIONS(275),
    [anon_sym_md5] = ACTIONS(275),
    [anon_sym_now] = ACTIONS(275),
    [anon_sym_date] = ACTIONS(275),
    [anon_sym_year] = ACTIONS(275),
    [anon_sym_month] = ACTIONS(275),
    [anon_sym_day] = ACTIONS(275),
    [anon_sym_hour] = ACTIONS(275),
    [anon_sym_minute] = ACTIONS(275),
    [anon_sym_dateFmt] = ACTIONS(275),
    [anon_sym_isoDateFmt] = ACTIONS(275),
    [anon_sym_isoDateTimeFmt] = ACTIONS(275),
    [anon_sym_isWeekend] = ACTIONS(275),
    [anon_sym_isWeekday] = ACTIONS(275),
    [anon_sym_dow] = ACTIONS(275),
    [anon_sym_addDays] = ACTIONS(275),
    [anon_sym_toUnixTime] = ACTIONS(275),
    [anon_sym_toUnixTimeMilli] = ACTIONS(275),
    [anon_sym_toUnixTimeMicro] = ACTIONS(275),
    [anon_sym_toUnixTimeNano] = ACTIONS(275),
    [anon_sym_fromUnixTime] = ACTIONS(275),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(275),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(275),
    [anon_sym_fromUnixTimeNano] = ACTIONS(275),
    [anon_sym_toOleDate] = ACTIONS(275),
    [anon_sym_fromOleDate] = ACTIONS(275),
    [anon_sym_utcToCst] = ACTIONS(275),
    [anon_sym_cstToUtc] = ACTIONS(275),
    [anon_sym_reMatch] = ACTIONS(275),
    [anon_sym_reFindAll] = ACTIONS(275),
    [anon_sym_reFindAllIndex] = ACTIONS(275),
    [anon_sym_reReplace] = ACTIONS(275),
    [anon_sym_reSplit] = ACTIONS(275),
    [anon_sym_just] = ACTIONS(275),
    [anon_sym_none] = ACTIONS(275),
    [anon_sym_isNone] = ACTIONS(275),
    [anon_sym_maybe] = ACTIONS(275),
    [anon_sym_bind] = ACTIONS(275),
    [anon_sym_psub] = ACTIONS(275),
    [anon_sym_typeof] = ACTIONS(275),
    [anon_sym_runtime] = ACTIONS(275),
    [anon_sym_hostname] = ACTIONS(275),
    [anon_sym_httpGet] = ACTIONS(275),
    [anon_sym_httpPost] = ACTIONS(275),
    [anon_sym_urlEncode] = ACTIONS(275),
    [anon_sym_base64encode] = ACTIONS(275),
    [anon_sym_base64decode] = ACTIONS(275),
    [anon_sym_utf8Str] = ACTIONS(275),
    [anon_sym_utf8Bytes] = ACTIONS(275),
    [anon_sym_get] = ACTIONS(275),
    [anon_sym_getDef] = ACTIONS(275),
    [anon_sym_set] = ACTIONS(275),
    [anon_sym_setd] = ACTIONS(275),
    [anon_sym_keys] = ACTIONS(275),
    [anon_sym_values] = ACTIONS(275),
    [anon_sym_keyValues] = ACTIONS(275),
    [anon_sym_all] = ACTIONS(275),
    [anon_sym_any] = ACTIONS(275),
    [anon_sym_cartesian] = ACTIONS(275),
    [anon_sym_groupBy] = ACTIONS(275),
    [anon_sym_listToDict] = ACTIONS(275),
    [anon_sym_repeat] = ACTIONS(275),
    [anon_sym_seq] = ACTIONS(275),
    [anon_sym_tab] = ACTIONS(275),
    [anon_sym_select] = ACTIONS(275),
    [anon_sym_exclude] = ACTIONS(275),
    [anon_sym_derive] = ACTIONS(275),
    [anon_sym_updateCol] = ACTIONS(275),
    [anon_sym_gridValues] = ACTIONS(275),
    [anon_sym_leftJoin] = ACTIONS(275),
    [anon_sym_outerJoin] = ACTIONS(275),
    [anon_sym_linearSearch] = ACTIONS(275),
    [anon_sym_linearSearchIndex] = ACTIONS(275),
    [anon_sym_binPaths] = ACTIONS(275),
    [anon_sym_wt] = ACTIONS(275),
    [anon_sym_tt] = ACTIONS(275),
    [anon_sym_ttFile] = ACTIONS(275),
    [anon_sym_uw] = ACTIONS(275),
    [anon_sym_tuw] = ACTIONS(275),
    [anon_sym_strCmp] = ACTIONS(275),
    [anon_sym_floatCmp] = ACTIONS(275),
    [anon_sym_versionSortCmp] = ACTIONS(275),
    [anon_sym_id] = ACTIONS(275),
    [anon_sym_2id] = ACTIONS(275),
    [anon_sym_3id] = ACTIONS(275),
    [anon_sym_2unpack] = ACTIONS(275),
    [anon_sym_2apply] = ACTIONS(275),
    [anon_sym_2each] = ACTIONS(275),
    [anon_sym_2tuple] = ACTIONS(275),
    [anon_sym_DOTs] = ACTIONS(275),
    [anon_sym_DOTb] = ACTIONS(275),
    [anon_sym_DOTdef] = ACTIONS(275),
    [anon_sym_DOTenv] = ACTIONS(275),
    [sym_string] = ACTIONS(273),
    [sym_format_string] = ACTIONS(273),
    [sym_single_quoted_string] = ACTIONS(273),
    [sym_path] = ACTIONS(273),
    [sym_datetime] = ACTIONS(273),
    [sym_float] = ACTIONS(273),
    [sym_integer] = ACTIONS(275),
    [sym_env_store] = ACTIONS(273),
    [sym_env_check] = ACTIONS(273),
    [sym_env_retrieve] = ACTIONS(275),
    [sym_positional] = ACTIONS(273),
    [sym_var_retrieve] = ACTIONS(273),
    [sym_var_store] = ACTIONS(273),
    [sym_slice_indexer] = ACTIONS(273),
    [sym_indexer] = ACTIONS(273),
    [sym_end_indexer] = ACTIONS(275),
    [sym_start_indexer] = ACTIONS(275),
    [sym_match_arm_dup] = ACTIONS(273),
    [sym_prefix_quote] = ACTIONS(275),
    [anon_sym_GT] = ACTIONS(275),
    [anon_sym_GT_GT] = ACTIONS(273),
    [anon_sym_2_GT] = ACTIONS(275),
    [anon_sym_2_GT_GT] = ACTIONS(275),
    [anon_sym_AMP_GT] = ACTIONS(275),
    [anon_sym_AMP_GT_GT] = ACTIONS(273),
    [anon_sym_LT] = ACTIONS(275),
    [anon_sym_LT_GT] = ACTIONS(273),
    [anon_sym_STAR] = ACTIONS(275),
    [anon_sym_STARb] = ACTIONS(273),
    [anon_sym_CARET] = ACTIONS(275),
    [anon_sym_CARETb] = ACTIONS(273),
    [anon_sym_SEMI] = ACTIONS(273),
    [anon_sym_BANG] = ACTIONS(275),
    [anon_sym_QMARK] = ACTIONS(273),
    [anon_sym_BANG_EQ] = ACTIONS(273),
    [anon_sym_LT_EQ] = ACTIONS(273),
    [anon_sym_GT_EQ] = ACTIONS(273),
    [anon_sym_AMP] = ACTIONS(275),
    [anon_sym_PIPE] = ACTIONS(275),
    [anon_sym_COMMA] = ACTIONS(273),
    [anon_sym_COLON] = ACTIONS(275),
  },
  [51] = {
    [sym_identifier] = ACTIONS(303),
    [anon_sym_LBRACK] = ACTIONS(303),
    [anon_sym_LPAREN] = ACTIONS(301),
    [anon_sym_LBRACE] = ACTIONS(301),
    [anon_sym_LBRACK_PIPE] = ACTIONS(301),
    [anon_sym_PIPE_RBRACK] = ACTIONS(301),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(303),
    [anon_sym_false] = ACTIONS(303),
    [anon_sym_def] = ACTIONS(303),
    [anon_sym_end] = ACTIONS(303),
    [anon_sym_if] = ACTIONS(303),
    [anon_sym_iff] = ACTIONS(303),
    [anon_sym_else] = ACTIONS(303),
    [anon_sym_else_STAR] = ACTIONS(301),
    [anon_sym_STARif] = ACTIONS(301),
    [anon_sym_loop] = ACTIONS(303),
    [anon_sym_match] = ACTIONS(303),
    [anon_sym_break] = ACTIONS(303),
    [anon_sym_continue] = ACTIONS(303),
    [anon_sym_soe] = ACTIONS(303),
    [anon_sym_not] = ACTIONS(303),
    [anon_sym_and] = ACTIONS(303),
    [anon_sym_or] = ACTIONS(303),
    [anon_sym_read] = ACTIONS(303),
    [anon_sym_str] = ACTIONS(303),
    [anon_sym_as] = ACTIONS(303),
    [anon_sym_type] = ACTIONS(303),
    [anon_sym_try] = ACTIONS(303),
    [anon_sym_fail] = ACTIONS(303),
    [anon_sym_pure] = ACTIONS(303),
    [anon_sym_VER] = ACTIONS(303),
    [anon_sym_x] = ACTIONS(303),
    [anon_sym_int] = ACTIONS(303),
    [anon_sym_float] = ACTIONS(303),
    [anon_sym_bool] = ACTIONS(303),
    [anon_sym_dup] = ACTIONS(303),
    [anon_sym_swap] = ACTIONS(303),
    [anon_sym_drop] = ACTIONS(303),
    [anon_sym_over] = ACTIONS(303),
    [anon_sym_pick] = ACTIONS(303),
    [anon_sym_rot] = ACTIONS(303),
    [anon_sym_DASHrot] = ACTIONS(303),
    [anon_sym_nip] = ACTIONS(303),
    [anon_sym_w] = ACTIONS(303),
    [anon_sym_wl] = ACTIONS(303),
    [anon_sym_we] = ACTIONS(303),
    [anon_sym_wle] = ACTIONS(303),
    [anon_sym_len] = ACTIONS(303),
    [anon_sym_args] = ACTIONS(303),
    [anon_sym_glob] = ACTIONS(303),
    [anon_sym_toFloat] = ACTIONS(303),
    [anon_sym_toInt] = ACTIONS(303),
    [anon_sym_toPath] = ACTIONS(303),
    [anon_sym_toDt] = ACTIONS(303),
    [anon_sym_toGrid] = ACTIONS(303),
    [anon_sym_toCsv] = ACTIONS(303),
    [anon_sym_toCsvCell] = ACTIONS(303),
    [anon_sym_exit] = ACTIONS(303),
    [anon_sym_prompt] = ACTIONS(303),
    [anon_sym_stdin] = ACTIONS(303),
    [anon_sym_COLON_COLON] = ACTIONS(301),
    [anon_sym_foldl] = ACTIONS(303),
    [anon_sym_map] = ACTIONS(303),
    [anon_sym_each] = ACTIONS(303),
    [anon_sym_eachWhile] = ACTIONS(303),
    [anon_sym_filter] = ACTIONS(303),
    [anon_sym_append] = ACTIONS(303),
    [anon_sym_extend] = ACTIONS(303),
    [anon_sym_concat] = ACTIONS(303),
    [anon_sym_reverse] = ACTIONS(303),
    [anon_sym_sort] = ACTIONS(303),
    [anon_sym_sortV] = ACTIONS(303),
    [anon_sym_sortBy] = ACTIONS(303),
    [anon_sym_sortByCmp] = ACTIONS(303),
    [anon_sym_uniq] = ACTIONS(303),
    [anon_sym_zip] = ACTIONS(303),
    [anon_sym_enumerate] = ACTIONS(303),
    [anon_sym_enumerateN] = ACTIONS(303),
    [anon_sym_chunk] = ACTIONS(303),
    [anon_sym_pop] = ACTIONS(303),
    [anon_sym_take] = ACTIONS(303),
    [anon_sym_takeWhile] = ACTIONS(303),
    [anon_sym_skip] = ACTIONS(303),
    [anon_sym_dropWhile] = ACTIONS(303),
    [anon_sym_nth] = ACTIONS(303),
    [anon_sym_insert] = ACTIONS(303),
    [anon_sym_setAt] = ACTIONS(303),
    [anon_sym_del] = ACTIONS(303),
    [anon_sym_sum] = ACTIONS(303),
    [anon_sym_max] = ACTIONS(303),
    [anon_sym_max2] = ACTIONS(303),
    [anon_sym_min] = ACTIONS(303),
    [anon_sym_min2] = ACTIONS(303),
    [anon_sym_abs] = ACTIONS(303),
    [anon_sym_inc] = ACTIONS(303),
    [anon_sym_mod] = ACTIONS(303),
    [anon_sym_floor] = ACTIONS(303),
    [anon_sym_ceil] = ACTIONS(303),
    [anon_sym_round] = ACTIONS(303),
    [anon_sym_lines] = ACTIONS(303),
    [anon_sym_unlines] = ACTIONS(303),
    [anon_sym_unlinesCrLf] = ACTIONS(303),
    [anon_sym_split] = ACTIONS(303),
    [anon_sym_wsplit] = ACTIONS(303),
    [anon_sym_tsplit] = ACTIONS(303),
    [anon_sym_join] = ACTIONS(303),
    [anon_sym_trim] = ACTIONS(303),
    [anon_sym_trimStart] = ACTIONS(303),
    [anon_sym_trimEnd] = ACTIONS(303),
    [anon_sym_startsWith] = ACTIONS(303),
    [anon_sym_endsWith] = ACTIONS(303),
    [anon_sym_lower] = ACTIONS(303),
    [anon_sym_upper] = ACTIONS(303),
    [anon_sym_title] = ACTIONS(303),
    [anon_sym_leftPad] = ACTIONS(303),
    [anon_sym_findReplace] = ACTIONS(303),
    [anon_sym_in] = ACTIONS(303),
    [anon_sym_index] = ACTIONS(303),
    [anon_sym_lastIndexOf] = ACTIONS(303),
    [anon_sym_countSubStr] = ACTIONS(303),
    [anon_sym_parseJson] = ACTIONS(303),
    [anon_sym_parseCsv] = ACTIONS(303),
    [anon_sym_parseHtml] = ACTIONS(303),
    [anon_sym_parseExcel] = ACTIONS(303),
    [anon_sym_readFile] = ACTIONS(303),
    [anon_sym_readFileBytes] = ACTIONS(303),
    [anon_sym_readTsvFile] = ACTIONS(303),
    [anon_sym_writeFile] = ACTIONS(303),
    [anon_sym_appendFile] = ACTIONS(303),
    [anon_sym_fileExists] = ACTIONS(303),
    [anon_sym_isDir] = ACTIONS(303),
    [anon_sym_isFile] = ACTIONS(303),
    [anon_sym_fileSize] = ACTIONS(303),
    [anon_sym_cp] = ACTIONS(303),
    [anon_sym_mv] = ACTIONS(303),
    [anon_sym_rm] = ACTIONS(303),
    [anon_sym_rmf] = ACTIONS(303),
    [anon_sym_mkdir] = ACTIONS(303),
    [anon_sym_mkdirp] = ACTIONS(303),
    [anon_sym_cd] = ACTIONS(303),
    [anon_sym_pwd] = ACTIONS(303),
    [anon_sym_tempFile] = ACTIONS(303),
    [anon_sym_tempFileExt] = ACTIONS(303),
    [anon_sym_tempDir] = ACTIONS(303),
    [anon_sym_lsDir] = ACTIONS(303),
    [anon_sym_files] = ACTIONS(303),
    [anon_sym_dirs] = ACTIONS(303),
    [anon_sym_absPath] = ACTIONS(303),
    [anon_sym_dirname] = ACTIONS(303),
    [anon_sym_basename] = ACTIONS(303),
    [anon_sym_ext] = ACTIONS(303),
    [anon_sym_stem] = ACTIONS(303),
    [anon_sym_isCmd] = ACTIONS(303),
    [anon_sym_hardLink] = ACTIONS(303),
    [anon_sym_sha256sum] = ACTIONS(303),
    [anon_sym_md5] = ACTIONS(303),
    [anon_sym_now] = ACTIONS(303),
    [anon_sym_date] = ACTIONS(303),
    [anon_sym_year] = ACTIONS(303),
    [anon_sym_month] = ACTIONS(303),
    [anon_sym_day] = ACTIONS(303),
    [anon_sym_hour] = ACTIONS(303),
    [anon_sym_minute] = ACTIONS(303),
    [anon_sym_dateFmt] = ACTIONS(303),
    [anon_sym_isoDateFmt] = ACTIONS(303),
    [anon_sym_isoDateTimeFmt] = ACTIONS(303),
    [anon_sym_isWeekend] = ACTIONS(303),
    [anon_sym_isWeekday] = ACTIONS(303),
    [anon_sym_dow] = ACTIONS(303),
    [anon_sym_addDays] = ACTIONS(303),
    [anon_sym_toUnixTime] = ACTIONS(303),
    [anon_sym_toUnixTimeMilli] = ACTIONS(303),
    [anon_sym_toUnixTimeMicro] = ACTIONS(303),
    [anon_sym_toUnixTimeNano] = ACTIONS(303),
    [anon_sym_fromUnixTime] = ACTIONS(303),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(303),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(303),
    [anon_sym_fromUnixTimeNano] = ACTIONS(303),
    [anon_sym_toOleDate] = ACTIONS(303),
    [anon_sym_fromOleDate] = ACTIONS(303),
    [anon_sym_utcToCst] = ACTIONS(303),
    [anon_sym_cstToUtc] = ACTIONS(303),
    [anon_sym_reMatch] = ACTIONS(303),
    [anon_sym_reFindAll] = ACTIONS(303),
    [anon_sym_reFindAllIndex] = ACTIONS(303),
    [anon_sym_reReplace] = ACTIONS(303),
    [anon_sym_reSplit] = ACTIONS(303),
    [anon_sym_just] = ACTIONS(303),
    [anon_sym_none] = ACTIONS(303),
    [anon_sym_isNone] = ACTIONS(303),
    [anon_sym_maybe] = ACTIONS(303),
    [anon_sym_bind] = ACTIONS(303),
    [anon_sym_psub] = ACTIONS(303),
    [anon_sym_typeof] = ACTIONS(303),
    [anon_sym_runtime] = ACTIONS(303),
    [anon_sym_hostname] = ACTIONS(303),
    [anon_sym_httpGet] = ACTIONS(303),
    [anon_sym_httpPost] = ACTIONS(303),
    [anon_sym_urlEncode] = ACTIONS(303),
    [anon_sym_base64encode] = ACTIONS(303),
    [anon_sym_base64decode] = ACTIONS(303),
    [anon_sym_utf8Str] = ACTIONS(303),
    [anon_sym_utf8Bytes] = ACTIONS(303),
    [anon_sym_get] = ACTIONS(303),
    [anon_sym_getDef] = ACTIONS(303),
    [anon_sym_set] = ACTIONS(303),
    [anon_sym_setd] = ACTIONS(303),
    [anon_sym_keys] = ACTIONS(303),
    [anon_sym_values] = ACTIONS(303),
    [anon_sym_keyValues] = ACTIONS(303),
    [anon_sym_all] = ACTIONS(303),
    [anon_sym_any] = ACTIONS(303),
    [anon_sym_cartesian] = ACTIONS(303),
    [anon_sym_groupBy] = ACTIONS(303),
    [anon_sym_listToDict] = ACTIONS(303),
    [anon_sym_repeat] = ACTIONS(303),
    [anon_sym_seq] = ACTIONS(303),
    [anon_sym_tab] = ACTIONS(303),
    [anon_sym_select] = ACTIONS(303),
    [anon_sym_exclude] = ACTIONS(303),
    [anon_sym_derive] = ACTIONS(303),
    [anon_sym_updateCol] = ACTIONS(303),
    [anon_sym_gridValues] = ACTIONS(303),
    [anon_sym_leftJoin] = ACTIONS(303),
    [anon_sym_outerJoin] = ACTIONS(303),
    [anon_sym_linearSearch] = ACTIONS(303),
    [anon_sym_linearSearchIndex] = ACTIONS(303),
    [anon_sym_binPaths] = ACTIONS(303),
    [anon_sym_wt] = ACTIONS(303),
    [anon_sym_tt] = ACTIONS(303),
    [anon_sym_ttFile] = ACTIONS(303),
    [anon_sym_uw] = ACTIONS(303),
    [anon_sym_tuw] = ACTIONS(303),
    [anon_sym_strCmp] = ACTIONS(303),
    [anon_sym_floatCmp] = ACTIONS(303),
    [anon_sym_versionSortCmp] = ACTIONS(303),
    [anon_sym_id] = ACTIONS(303),
    [anon_sym_2id] = ACTIONS(303),
    [anon_sym_3id] = ACTIONS(303),
    [anon_sym_2unpack] = ACTIONS(303),
    [anon_sym_2apply] = ACTIONS(303),
    [anon_sym_2each] = ACTIONS(303),
    [anon_sym_2tuple] = ACTIONS(303),
    [anon_sym_DOTs] = ACTIONS(303),
    [anon_sym_DOTb] = ACTIONS(303),
    [anon_sym_DOTdef] = ACTIONS(303),
    [anon_sym_DOTenv] = ACTIONS(303),
    [sym_string] = ACTIONS(301),
    [sym_format_string] = ACTIONS(301),
    [sym_single_quoted_string] = ACTIONS(301),
    [sym_path] = ACTIONS(301),
    [sym_datetime] = ACTIONS(301),
    [sym_float] = ACTIONS(301),
    [sym_integer] = ACTIONS(303),
    [sym_env_store] = ACTIONS(301),
    [sym_env_check] = ACTIONS(301),
    [sym_env_retrieve] = ACTIONS(303),
    [sym_positional] = ACTIONS(301),
    [sym_var_retrieve] = ACTIONS(301),
    [sym_var_store] = ACTIONS(301),
    [sym_slice_indexer] = ACTIONS(301),
    [sym_indexer] = ACTIONS(301),
    [sym_end_indexer] = ACTIONS(303),
    [sym_start_indexer] = ACTIONS(303),
    [sym_match_arm_dup] = ACTIONS(301),
    [sym_prefix_quote] = ACTIONS(303),
    [anon_sym_GT] = ACTIONS(303),
    [anon_sym_GT_GT] = ACTIONS(301),
    [anon_sym_2_GT] = ACTIONS(303),
    [anon_sym_2_GT_GT] = ACTIONS(303),
    [anon_sym_AMP_GT] = ACTIONS(303),
    [anon_sym_AMP_GT_GT] = ACTIONS(301),
    [anon_sym_LT] = ACTIONS(303),
    [anon_sym_LT_GT] = ACTIONS(301),
    [anon_sym_STAR] = ACTIONS(303),
    [anon_sym_STARb] = ACTIONS(301),
    [anon_sym_CARET] = ACTIONS(303),
    [anon_sym_CARETb] = ACTIONS(301),
    [anon_sym_SEMI] = ACTIONS(301),
    [anon_sym_BANG] = ACTIONS(303),
    [anon_sym_QMARK] = ACTIONS(301),
    [anon_sym_BANG_EQ] = ACTIONS(301),
    [anon_sym_LT_EQ] = ACTIONS(301),
    [anon_sym_GT_EQ] = ACTIONS(301),
    [anon_sym_AMP] = ACTIONS(303),
    [anon_sym_PIPE] = ACTIONS(303),
    [anon_sym_COMMA] = ACTIONS(301),
    [anon_sym_COLON] = ACTIONS(303),
  },
  [52] = {
    [sym_identifier] = ACTIONS(291),
    [anon_sym_LBRACK] = ACTIONS(291),
    [anon_sym_LPAREN] = ACTIONS(289),
    [anon_sym_LBRACE] = ACTIONS(289),
    [anon_sym_LBRACK_PIPE] = ACTIONS(289),
    [anon_sym_PIPE_RBRACK] = ACTIONS(289),
    [sym_line_comment] = ACTIONS(3),
    [anon_sym_true] = ACTIONS(291),
    [anon_sym_false] = ACTIONS(291),
    [anon_sym_def] = ACTIONS(291),
    [anon_sym_end] = ACTIONS(291),
    [anon_sym_if] = ACTIONS(291),
    [anon_sym_iff] = ACTIONS(291),
    [anon_sym_else] = ACTIONS(291),
    [anon_sym_else_STAR] = ACTIONS(289),
    [anon_sym_STARif] = ACTIONS(289),
    [anon_sym_loop] = ACTIONS(291),
    [anon_sym_match] = ACTIONS(291),
    [anon_sym_break] = ACTIONS(291),
    [anon_sym_continue] = ACTIONS(291),
    [anon_sym_soe] = ACTIONS(291),
    [anon_sym_not] = ACTIONS(291),
    [anon_sym_and] = ACTIONS(291),
    [anon_sym_or] = ACTIONS(291),
    [anon_sym_read] = ACTIONS(291),
    [anon_sym_str] = ACTIONS(291),
    [anon_sym_as] = ACTIONS(291),
    [anon_sym_type] = ACTIONS(291),
    [anon_sym_try] = ACTIONS(291),
    [anon_sym_fail] = ACTIONS(291),
    [anon_sym_pure] = ACTIONS(291),
    [anon_sym_VER] = ACTIONS(291),
    [anon_sym_x] = ACTIONS(291),
    [anon_sym_int] = ACTIONS(291),
    [anon_sym_float] = ACTIONS(291),
    [anon_sym_bool] = ACTIONS(291),
    [anon_sym_dup] = ACTIONS(291),
    [anon_sym_swap] = ACTIONS(291),
    [anon_sym_drop] = ACTIONS(291),
    [anon_sym_over] = ACTIONS(291),
    [anon_sym_pick] = ACTIONS(291),
    [anon_sym_rot] = ACTIONS(291),
    [anon_sym_DASHrot] = ACTIONS(291),
    [anon_sym_nip] = ACTIONS(291),
    [anon_sym_w] = ACTIONS(291),
    [anon_sym_wl] = ACTIONS(291),
    [anon_sym_we] = ACTIONS(291),
    [anon_sym_wle] = ACTIONS(291),
    [anon_sym_len] = ACTIONS(291),
    [anon_sym_args] = ACTIONS(291),
    [anon_sym_glob] = ACTIONS(291),
    [anon_sym_toFloat] = ACTIONS(291),
    [anon_sym_toInt] = ACTIONS(291),
    [anon_sym_toPath] = ACTIONS(291),
    [anon_sym_toDt] = ACTIONS(291),
    [anon_sym_toGrid] = ACTIONS(291),
    [anon_sym_toCsv] = ACTIONS(291),
    [anon_sym_toCsvCell] = ACTIONS(291),
    [anon_sym_exit] = ACTIONS(291),
    [anon_sym_prompt] = ACTIONS(291),
    [anon_sym_stdin] = ACTIONS(291),
    [anon_sym_COLON_COLON] = ACTIONS(289),
    [anon_sym_foldl] = ACTIONS(291),
    [anon_sym_map] = ACTIONS(291),
    [anon_sym_each] = ACTIONS(291),
    [anon_sym_eachWhile] = ACTIONS(291),
    [anon_sym_filter] = ACTIONS(291),
    [anon_sym_append] = ACTIONS(291),
    [anon_sym_extend] = ACTIONS(291),
    [anon_sym_concat] = ACTIONS(291),
    [anon_sym_reverse] = ACTIONS(291),
    [anon_sym_sort] = ACTIONS(291),
    [anon_sym_sortV] = ACTIONS(291),
    [anon_sym_sortBy] = ACTIONS(291),
    [anon_sym_sortByCmp] = ACTIONS(291),
    [anon_sym_uniq] = ACTIONS(291),
    [anon_sym_zip] = ACTIONS(291),
    [anon_sym_enumerate] = ACTIONS(291),
    [anon_sym_enumerateN] = ACTIONS(291),
    [anon_sym_chunk] = ACTIONS(291),
    [anon_sym_pop] = ACTIONS(291),
    [anon_sym_take] = ACTIONS(291),
    [anon_sym_takeWhile] = ACTIONS(291),
    [anon_sym_skip] = ACTIONS(291),
    [anon_sym_dropWhile] = ACTIONS(291),
    [anon_sym_nth] = ACTIONS(291),
    [anon_sym_insert] = ACTIONS(291),
    [anon_sym_setAt] = ACTIONS(291),
    [anon_sym_del] = ACTIONS(291),
    [anon_sym_sum] = ACTIONS(291),
    [anon_sym_max] = ACTIONS(291),
    [anon_sym_max2] = ACTIONS(291),
    [anon_sym_min] = ACTIONS(291),
    [anon_sym_min2] = ACTIONS(291),
    [anon_sym_abs] = ACTIONS(291),
    [anon_sym_inc] = ACTIONS(291),
    [anon_sym_mod] = ACTIONS(291),
    [anon_sym_floor] = ACTIONS(291),
    [anon_sym_ceil] = ACTIONS(291),
    [anon_sym_round] = ACTIONS(291),
    [anon_sym_lines] = ACTIONS(291),
    [anon_sym_unlines] = ACTIONS(291),
    [anon_sym_unlinesCrLf] = ACTIONS(291),
    [anon_sym_split] = ACTIONS(291),
    [anon_sym_wsplit] = ACTIONS(291),
    [anon_sym_tsplit] = ACTIONS(291),
    [anon_sym_join] = ACTIONS(291),
    [anon_sym_trim] = ACTIONS(291),
    [anon_sym_trimStart] = ACTIONS(291),
    [anon_sym_trimEnd] = ACTIONS(291),
    [anon_sym_startsWith] = ACTIONS(291),
    [anon_sym_endsWith] = ACTIONS(291),
    [anon_sym_lower] = ACTIONS(291),
    [anon_sym_upper] = ACTIONS(291),
    [anon_sym_title] = ACTIONS(291),
    [anon_sym_leftPad] = ACTIONS(291),
    [anon_sym_findReplace] = ACTIONS(291),
    [anon_sym_in] = ACTIONS(291),
    [anon_sym_index] = ACTIONS(291),
    [anon_sym_lastIndexOf] = ACTIONS(291),
    [anon_sym_countSubStr] = ACTIONS(291),
    [anon_sym_parseJson] = ACTIONS(291),
    [anon_sym_parseCsv] = ACTIONS(291),
    [anon_sym_parseHtml] = ACTIONS(291),
    [anon_sym_parseExcel] = ACTIONS(291),
    [anon_sym_readFile] = ACTIONS(291),
    [anon_sym_readFileBytes] = ACTIONS(291),
    [anon_sym_readTsvFile] = ACTIONS(291),
    [anon_sym_writeFile] = ACTIONS(291),
    [anon_sym_appendFile] = ACTIONS(291),
    [anon_sym_fileExists] = ACTIONS(291),
    [anon_sym_isDir] = ACTIONS(291),
    [anon_sym_isFile] = ACTIONS(291),
    [anon_sym_fileSize] = ACTIONS(291),
    [anon_sym_cp] = ACTIONS(291),
    [anon_sym_mv] = ACTIONS(291),
    [anon_sym_rm] = ACTIONS(291),
    [anon_sym_rmf] = ACTIONS(291),
    [anon_sym_mkdir] = ACTIONS(291),
    [anon_sym_mkdirp] = ACTIONS(291),
    [anon_sym_cd] = ACTIONS(291),
    [anon_sym_pwd] = ACTIONS(291),
    [anon_sym_tempFile] = ACTIONS(291),
    [anon_sym_tempFileExt] = ACTIONS(291),
    [anon_sym_tempDir] = ACTIONS(291),
    [anon_sym_lsDir] = ACTIONS(291),
    [anon_sym_files] = ACTIONS(291),
    [anon_sym_dirs] = ACTIONS(291),
    [anon_sym_absPath] = ACTIONS(291),
    [anon_sym_dirname] = ACTIONS(291),
    [anon_sym_basename] = ACTIONS(291),
    [anon_sym_ext] = ACTIONS(291),
    [anon_sym_stem] = ACTIONS(291),
    [anon_sym_isCmd] = ACTIONS(291),
    [anon_sym_hardLink] = ACTIONS(291),
    [anon_sym_sha256sum] = ACTIONS(291),
    [anon_sym_md5] = ACTIONS(291),
    [anon_sym_now] = ACTIONS(291),
    [anon_sym_date] = ACTIONS(291),
    [anon_sym_year] = ACTIONS(291),
    [anon_sym_month] = ACTIONS(291),
    [anon_sym_day] = ACTIONS(291),
    [anon_sym_hour] = ACTIONS(291),
    [anon_sym_minute] = ACTIONS(291),
    [anon_sym_dateFmt] = ACTIONS(291),
    [anon_sym_isoDateFmt] = ACTIONS(291),
    [anon_sym_isoDateTimeFmt] = ACTIONS(291),
    [anon_sym_isWeekend] = ACTIONS(291),
    [anon_sym_isWeekday] = ACTIONS(291),
    [anon_sym_dow] = ACTIONS(291),
    [anon_sym_addDays] = ACTIONS(291),
    [anon_sym_toUnixTime] = ACTIONS(291),
    [anon_sym_toUnixTimeMilli] = ACTIONS(291),
    [anon_sym_toUnixTimeMicro] = ACTIONS(291),
    [anon_sym_toUnixTimeNano] = ACTIONS(291),
    [anon_sym_fromUnixTime] = ACTIONS(291),
    [anon_sym_fromUnixTimeMilli] = ACTIONS(291),
    [anon_sym_fromUnixTimeMicro] = ACTIONS(291),
    [anon_sym_fromUnixTimeNano] = ACTIONS(291),
    [anon_sym_toOleDate] = ACTIONS(291),
    [anon_sym_fromOleDate] = ACTIONS(291),
    [anon_sym_utcToCst] = ACTIONS(291),
    [anon_sym_cstToUtc] = ACTIONS(291),
    [anon_sym_reMatch] = ACTIONS(291),
    [anon_sym_reFindAll] = ACTIONS(291),
    [anon_sym_reFindAllIndex] = ACTIONS(291),
    [anon_sym_reReplace] = ACTIONS(291),
    [anon_sym_reSplit] = ACTIONS(291),
    [anon_sym_just] = ACTIONS(291),
    [anon_sym_none] = ACTIONS(291),
    [anon_sym_isNone] = ACTIONS(291),
    [anon_sym_maybe] = ACTIONS(291),
    [anon_sym_bind] = ACTIONS(291),
    [anon_sym_psub] = ACTIONS(291),
    [anon_sym_typeof] = ACTIONS(291),
    [anon_sym_runtime] = ACTIONS(291),
    [anon_sym_hostname] = ACTIONS(291),
    [anon_sym_httpGet] = ACTIONS(291),
    [anon_sym_httpPost] = ACTIONS(291),
    [anon_sym_urlEncode] = ACTIONS(291),
    [anon_sym_base64encode] = ACTIONS(291),
    [anon_sym_base64decode] = ACTIONS(291),
    [anon_sym_utf8Str] = ACTIONS(291),
    [anon_sym_utf8Bytes] = ACTIONS(291),
    [anon_sym_get] = ACTIONS(291),
    [anon_sym_getDef] = ACTIONS(291),
    [anon_sym_set] = ACTIONS(291),
    [anon_sym_setd] = ACTIONS(291),
    [anon_sym_keys] = ACTIONS(291),
    [anon_sym_values] = ACTIONS(291),
    [anon_sym_keyValues] = ACTIONS(291),
    [anon_sym_all] = ACTIONS(291),
    [anon_sym_any] = ACTIONS(291),
    [anon_sym_cartesian] = ACTIONS(291),
    [anon_sym_groupBy] = ACTIONS(291),
    [anon_sym_listToDict] = ACTIONS(291),
    [anon_sym_repeat] = ACTIONS(291),
    [anon_sym_seq] = ACTIONS(291),
    [anon_sym_tab] = ACTIONS(291),
    [anon_sym_select] = ACTIONS(291),
    [anon_sym_exclude] = ACTIONS(291),
    [anon_sym_derive] = ACTIONS(291),
    [anon_sym_updateCol] = ACTIONS(291),
    [anon_sym_gridValues] = ACTIONS(291),
    [anon_sym_leftJoin] = ACTIONS(291),
    [anon_sym_outerJoin] = ACTIONS(291),
    [anon_sym_linearSearch] = ACTIONS(291),
    [anon_sym_linearSearchIndex] = ACTIONS(291),
    [anon_sym_binPaths] = ACTIONS(291),
    [anon_sym_wt] = ACTIONS(291),
    [anon_sym_tt] = ACTIONS(291),
    [anon_sym_ttFile] = ACTIONS(291),
    [anon_sym_uw] = ACTIONS(291),
    [anon_sym_tuw] = ACTIONS(291),
    [anon_sym_strCmp] = ACTIONS(291),
    [anon_sym_floatCmp] = ACTIONS(291),
    [anon_sym_versionSortCmp] = ACTIONS(291),
    [anon_sym_id] = ACTIONS(291),
    [anon_sym_2id] = ACTIONS(291),
    [anon_sym_3id] = ACTIONS(291),
    [anon_sym_2unpack] = ACTIONS(291),
    [anon_sym_2apply] = ACTIONS(291),
    [anon_sym_2each] = ACTIONS(291),
    [anon_sym_2tuple] = ACTIONS(291),
    [anon_sym_DOTs] = ACTIONS(291),
    [anon_sym_DOTb] = ACTIONS(291),
    [anon_sym_DOTdef] = ACTIONS(291),
    [anon_sym_DOTenv] = ACTIONS(291),
    [sym_string] = ACTIONS(289),
    [sym_format_string] = ACTIONS(289),
    [sym_single_quoted_string] = ACTIONS(289),
    [sym_path] = ACTIONS(289),
    [sym_datetime] = ACTIONS(289),
    [sym_float] = ACTIONS(289),
    [sym_integer] = ACTIONS(291),
    [sym_env_store] = ACTIONS(289),
    [sym_env_check] = ACTIONS(289),
    [sym_env_retrieve] = ACTIONS(291),
    [sym_positional] = ACTIONS(289),
    [sym_var_retrieve] = ACTIONS(289),
    [sym_var_store] = ACTIONS(289),
    [sym_slice_indexer] = ACTIONS(289),
    [sym_indexer] = ACTIONS(289),
    [sym_end_indexer] = ACTIONS(291),
    [sym_start_indexer] = ACTIONS(291),
    [sym_match_arm_dup] = ACTIONS(289),
    [sym_prefix_quote] = ACTIONS(291),
    [anon_sym_GT] = ACTIONS(291),
    [anon_sym_GT_GT] = ACTIONS(289),
    [anon_sym_2_GT] = ACTIONS(291),
    [anon_sym_2_GT_GT] = ACTIONS(291),
    [anon_sym_AMP_GT] = ACTIONS(291),
    [anon_sym_AMP_GT_GT] = ACTIONS(289),
    [anon_sym_LT] = ACTIONS(291),
    [anon_sym_LT_GT] = ACTIONS(289),
    [anon_sym_STAR] = ACTIONS(291),
    [anon_sym_STARb] = ACTIONS(289),
    [anon_sym_CARET] = ACTIONS(291),
    [anon_sym_CARETb] = ACTIONS(289),
    [anon_sym_SEMI] = ACTIONS(289),
    [anon_sym_BANG] = ACTIONS(291),
    [anon_sym_QMARK] = ACTIONS(289),
    [anon_sym_BANG_EQ] = ACTIONS(289),
    [anon_sym_LT_EQ] = ACTIONS(289),
    [anon_sym_GT_EQ] = ACTIONS(289),
    [anon_sym_AMP] = ACTIONS(291),
    [anon_sym_PIPE] = ACTIONS(291),
    [anon_sym_COMMA] = ACTIONS(289),
    [anon_sym_COLON] = ACTIONS(291),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(333), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(53)] = 0,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [41] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [47] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [50] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(10),
  [53] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(11),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(3),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(4),
  [62] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(31),
  [65] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(33),
  [68] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(33),
  [71] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(34),
  [74] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [83] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(23),
  [86] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(23),
  [89] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(24),
  [92] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(24),
  [95] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(27),
  [98] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(32),
  [101] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(32),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [110] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [122] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [124] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [128] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [130] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [152] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [174] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [180] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(12),
  [183] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(13),
  [186] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(14),
  [189] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [192] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [195] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(37),
  [198] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(38),
  [201] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(38),
  [204] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(39),
  [207] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(40),
  [210] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(40),
  [213] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(12),
  [216] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [219] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [222] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [225] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [228] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [231] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [234] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [237] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [239] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [243] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [247] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [249] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [253] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [255] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dict, 3, 0, 0),
  [271] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dict, 3, 0, 0),
  [273] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grid, 2, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_grid, 2, 0, 0),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_redirect_operator, 1, 0, 0),
  [279] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_redirect_operator, 1, 0, 0),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_execute_operator, 1, 0, 0),
  [283] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_execute_operator, 1, 0, 0),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 3, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 3, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quotation, 3, 0, 0),
  [291] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_quotation, 3, 0, 0),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison_operator, 1, 0, 0),
  [295] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison_operator, 1, 0, 0),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grid, 3, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_grid, 3, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quotation, 2, 0, 0),
  [303] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_quotation, 2, 0, 0),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 2, 0, 0),
  [307] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 2, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1, 0, 0),
  [311] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean, 1, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_punctuation, 1, 0, 0),
  [315] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_punctuation, 1, 0, 0),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_keyword, 1, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_keyword, 1, 0, 0),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_keyword, 1, 0, 0),
  [323] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_keyword, 1, 0, 0),
  [325] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dict, 2, 0, 0),
  [327] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dict, 2, 0, 0),
  [329] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin, 1, 0, 0),
  [331] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin, 1, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_mshell(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
