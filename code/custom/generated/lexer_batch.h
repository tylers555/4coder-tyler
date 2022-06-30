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
typedef u16 Token_Batch_Kind;
enum{
TokenBatchKind_EOF = 0,
TokenBatchKind_Whitespace = 1,
TokenBatchKind_LexError = 2,
TokenBatchKind_LineComment = 3,
TokenBatchKind_LiteralInteger = 4,
TokenBatchKind_LiteralFloat = 5,
TokenBatchKind_LiteralString = 6,
TokenBatchKind_ParenOp = 7,
TokenBatchKind_ParenCl = 8,
TokenBatchKind_EndWhitespace = 9,
TokenBatchKind_NoEcho = 10,
TokenBatchKind_Eq = 11,
TokenBatchKind_Colon = 12,
TokenBatchKind_BackSlash = 13,
TokenBatchKind_ForwardSlash = 14,
TokenBatchKind_ParentDir = 15,
TokenBatchKind_CurrentDir = 16,
TokenBatchKind_KeywordGeneric = 17,
TokenBatchKind_Set = 18,
TokenBatchKind_SetLocal = 19,
TokenBatchKind_EndLocal = 20,
TokenBatchKind_PushDir = 21,
TokenBatchKind_PopDir = 22,
TokenBatchKind_CD = 23,
TokenBatchKind_Echo = 24,
TokenBatchKind_Del = 25,
TokenBatchKind_Goto = 26,
TokenBatchKind_If = 27,
TokenBatchKind_IfCaps = 28,
TokenBatchKind_Else = 29,
TokenBatchKind_ElseCaps = 30,
TokenBatchKind_Not = 31,
TokenBatchKind_NotCaps = 32,
TokenBatchKind_Call = 33,
TokenBatchKind_Identifier = 34,
TokenBatchKind_Variable = 35,
TokenBatchKind_COUNT = 36,
};
char *token_batch_kind_names[] = {
"EOF",
"Whitespace",
"LexError",
"LineComment",
"LiteralInteger",
"LiteralFloat",
"LiteralString",
"ParenOp",
"ParenCl",
"EndWhitespace",
"NoEcho",
"Eq",
"Colon",
"BackSlash",
"ForwardSlash",
"ParentDir",
"CurrentDir",
"KeywordGeneric",
"Set",
"SetLocal",
"EndLocal",
"PushDir",
"PopDir",
"CD",
"Echo",
"Del",
"Goto",
"If",
"IfCaps",
"Else",
"ElseCaps",
"Not",
"NotCaps",
"Call",
"Identifier",
"Variable",
};
