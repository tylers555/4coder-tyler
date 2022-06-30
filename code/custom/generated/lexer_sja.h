#if !defined(FCODER_LEX_GEN_HAND_WRITTEN_TYPES)
#define FCODER_LEX_GEN_HAND_WRITTEN_TYPES

struct Lexeme_Table_Value{
    Token_Base_Kind base_kind;
    u16 sub_kind;
};

struct Lexeme_Table_Lookup{
    b32 found_match;
    Token_Base_Kind base_kind;
    u16 sub_kind;
};

#endif
typedef u16 Token_SJA_Kind;
enum{
TokenSJAKind_EOF = 0,
TokenSJAKind_Whitespace = 1,
TokenSJAKind_LexError = 2,
TokenSJAKind_BlockComment = 3,
TokenSJAKind_LineComment = 4,
TokenSJAKind_LiteralInteger = 5,
TokenSJAKind_LiteralIntegerHex = 6,
TokenSJAKind_LiteralFloat = 7,
TokenSJAKind_LiteralString = 8,
TokenSJAKind_ParenOp = 9,
TokenSJAKind_ParenCl = 10,
TokenSJAKind_KeywordGeneric = 11,
TokenSJAKind_Command = 12,
TokenSJAKind_LiteralTrue = 13,
TokenSJAKind_LiteralFalse = 14,
TokenSJAKind_Identifier = 15,
TokenSJAKind_COUNT = 16,
};
char *token_sja_kind_names[] = {
"EOF",
"Whitespace",
"LexError",
"BlockComment",
"LineComment",
"LiteralInteger",
"LiteralIntegerHex",
"LiteralFloat",
"LiteralString",
"ParenOp",
"ParenCl",
"KeywordGeneric",
"Command",
"LiteralTrue",
"LiteralFalse",
"Identifier",
};
