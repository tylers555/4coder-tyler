#if !defined(FCODER_LEX_GEN_HAND_WRITTEN)
#define FCODER_LEX_GEN_HAND_WRITTEN

internal u64
lexeme_hash(u64 seed, u8 *ptr, u64 size){
    u64 result = 0;
    for (u64 i = 0; i < size; i += 1, ptr += 1){
        result ^= ((*ptr) ^ result*59) + seed;
    }
    return(result);
}

internal Lexeme_Table_Lookup
lexeme_table_lookup(u64 *hash_array, String_Const_u8 *key_array, 
                    Lexeme_Table_Value *value_array, i32 slot_count, u64 seed,
                    u8 *ptr, u64 size){
    Lexeme_Table_Lookup result = {};
    u64 hash = lexeme_hash(seed, ptr, size);
    u64 comparison_hash = hash | 1;
    i32 first_index = (hash % slot_count);
    i32 index = first_index;
    for (;;){
        if (hash_array[index] == comparison_hash){
            if (string_match(SCu8(ptr, size), key_array[index])){
                result.found_match = true;
                result.base_kind = value_array[index].base_kind;
                result.sub_kind = value_array[index].sub_kind;
                break;
            }
        }
        else if (hash_array[index] == 0){
            break;
        }
        index += 1;
        if (index == slot_count){
            index = 0;
        }
        if (index == first_index){
            break;
        }
    }
    return(result);
}

#endif
u64 batch_main_keys_hash_array[27] = {
0x2f6fc7f7786bc06f,0xa1bb404f2c963f4b,0x0000000000000000,0x0000000000000000,
0x2f6f3ca87e9cf86f,0x0000000000000000,0xa347acd02fee3e2f,0x0000000000000000,
0x0624aaac112e114b,0xb95ddecdff57477f,0xb95ddecdff574599,0xa347acd02fee208f,
0x0000000000000000,0xa1bb404f2caaaba3,0x0000000000000000,0x0000000000000000,
0xa1bb404f2c418d83,0xb95ddecdff574d39,0xa1bb404f2c753fbd,0x0000000000000000,
0xa1bb404f2cc1af5d,0x0000000000000000,0xa347acd02fec6e2f,0xa347acd02fee8e17,
0xa1bb404f2c75b0d3,0x0000000000000000,0x0000000000000000,
};
u8 batch_main_keys_key_array_0[] = {0x73,0x65,0x74,0x6c,0x6f,0x63,0x61,0x6c,};
u8 batch_main_keys_key_array_1[] = {0x70,0x6f,0x70,0x64,};
u8 batch_main_keys_key_array_4[] = {0x65,0x6e,0x64,0x6c,0x6f,0x63,0x61,0x6c,};
u8 batch_main_keys_key_array_6[] = {0x73,0x65,0x74,};
u8 batch_main_keys_key_array_8[] = {0x70,0x75,0x73,0x68,0x64,};
u8 batch_main_keys_key_array_9[] = {0x63,0x64,};
u8 batch_main_keys_key_array_10[] = {0x69,0x66,};
u8 batch_main_keys_key_array_11[] = {0x6e,0x6f,0x74,};
u8 batch_main_keys_key_array_13[] = {0x63,0x61,0x6c,0x6c,};
u8 batch_main_keys_key_array_16[] = {0x67,0x6f,0x74,0x6f,};
u8 batch_main_keys_key_array_17[] = {0x49,0x46,};
u8 batch_main_keys_key_array_18[] = {0x65,0x6c,0x73,0x65,};
u8 batch_main_keys_key_array_20[] = {0x45,0x4c,0x53,0x45,};
u8 batch_main_keys_key_array_22[] = {0x4e,0x4f,0x54,};
u8 batch_main_keys_key_array_23[] = {0x64,0x65,0x6c,};
u8 batch_main_keys_key_array_24[] = {0x65,0x63,0x68,0x6f,};
String_Const_u8 batch_main_keys_key_array[27] = {
{batch_main_keys_key_array_0, 8},
{batch_main_keys_key_array_1, 4},
{0, 0},
{0, 0},
{batch_main_keys_key_array_4, 8},
{0, 0},
{batch_main_keys_key_array_6, 3},
{0, 0},
{batch_main_keys_key_array_8, 5},
{batch_main_keys_key_array_9, 2},
{batch_main_keys_key_array_10, 2},
{batch_main_keys_key_array_11, 3},
{0, 0},
{batch_main_keys_key_array_13, 4},
{0, 0},
{0, 0},
{batch_main_keys_key_array_16, 4},
{batch_main_keys_key_array_17, 2},
{batch_main_keys_key_array_18, 4},
{0, 0},
{batch_main_keys_key_array_20, 4},
{0, 0},
{batch_main_keys_key_array_22, 3},
{batch_main_keys_key_array_23, 3},
{batch_main_keys_key_array_24, 4},
{0, 0},
{0, 0},
};
Lexeme_Table_Value batch_main_keys_value_array[27] = {
{4, TokenBatchKind_SetLocal},
{4, TokenBatchKind_PopDir},
{0, 0},
{0, 0},
{4, TokenBatchKind_EndLocal},
{0, 0},
{4, TokenBatchKind_Set},
{0, 0},
{4, TokenBatchKind_PushDir},
{4, TokenBatchKind_CD},
{4, TokenBatchKind_If},
{4, TokenBatchKind_Not},
{0, 0},
{4, TokenBatchKind_Call},
{0, 0},
{0, 0},
{4, TokenBatchKind_Goto},
{4, TokenBatchKind_IfCaps},
{4, TokenBatchKind_Else},
{0, 0},
{4, TokenBatchKind_ElseCaps},
{0, 0},
{4, TokenBatchKind_NotCaps},
{4, TokenBatchKind_Del},
{4, TokenBatchKind_Echo},
{0, 0},
{0, 0},
};
i32 batch_main_keys_slot_count = 27;
u64 batch_main_keys_seed = 0x617818a3f79cfe73;
struct Lex_State_Batch{
u32 flags_KF0;
u8 *base;
u8 *delim_first;
u8 *delim_one_past_last;
u8 *emit_ptr;
u8 *ptr;
u8 *opl_ptr;
};
internal void
lex_full_input_batch_init(Lex_State_Batch *state_ptr, String_Const_u8 input){
state_ptr->flags_KF0 = 0;
state_ptr->base = input.str;
state_ptr->delim_first = input.str;
state_ptr->delim_one_past_last = input.str;
state_ptr->emit_ptr = input.str;
state_ptr->ptr = input.str;
state_ptr->opl_ptr = input.str + input.size;
}
internal b32
lex_full_input_batch_breaks(Arena *arena, Token_List *list, Lex_State_Batch *state_ptr, u64 max){
b32 result = false;
u64 emit_counter = 0;
Lex_State_Batch state;
block_copy_struct(&state, state_ptr);
{
state_label_1: // root
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x09:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
case 0x0a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_EndWhitespace;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x22:
{
state.ptr += 1;
state.flags_KF0 |= 0x1;
goto state_label_5; // string
}break;
case 0x25:
{
state.ptr += 1;
goto state_label_6; // variable_start
}break;
case 0x28:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_ParenOp;
token.kind = 11;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x29:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_ParenCl;
token.kind = 12;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_12; // op stage
}break;
case 0x2f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_ForwardSlash;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_4; // number
}break;
case 0x3a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Colon;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Eq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x40:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_NoEcho;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x41:case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:
case 0x48:case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:
case 0x4f:case 0x50:case 0x51:case 0x53:case 0x54:case 0x55:case 0x56:
case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5f:case 0x61:case 0x62:
case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:case 0x69:
case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:case 0x70:
case 0x71:case 0x73:case 0x74:case 0x75:case 0x76:case 0x77:case 0x78:
case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
case 0x52:case 0x72:
{
state.ptr += 1;
goto state_label_9; // comment_e
}break;
case 0x5c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_BackSlash;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
}
}
{
state_label_2: // identifier
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(batch_main_keys_hash_array, batch_main_keys_key_array, batch_main_keys_value_array, batch_main_keys_slot_count, batch_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenBatchKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(batch_main_keys_hash_array, batch_main_keys_key_array, batch_main_keys_value_array, batch_main_keys_slot_count, batch_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenBatchKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x2d:case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:
case 0x36:case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:
case 0x44:case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:
case 0x4b:case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:
case 0x52:case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:
case 0x59:case 0x5a:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:
case 0x65:case 0x66:case 0x67:case 0x68:case 0x69:case 0x6a:case 0x6b:
case 0x6c:case 0x6d:case 0x6e:case 0x6f:case 0x70:case 0x71:case 0x72:
case 0x73:case 0x74:case 0x75:case 0x76:case 0x77:case 0x78:case 0x79:
case 0x7a:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
}
}
{
state_label_3: // whitespace
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x09:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
case 0x0a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_EndWhitespace;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
}
}
{
state_label_4: // number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_4; // number
}break;
case 0x41:case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:
case 0x48:case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:
case 0x4f:case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:
case 0x56:case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5f:case 0x61:
case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
}
}
{
state_label_5: // string
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
state.flags_KF0 |= 0x1;
goto state_label_5; // string
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x22:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LiteralString;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 &= ~(0x1);
goto state_label_1; // root
}break;
case 0x25:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LiteralString;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.ptr += 1;
goto state_label_6; // variable_start
}break;
}
}
{
state_label_6: // variable_start
if (state.ptr == state.opl_ptr){
}
switch (*state.ptr){
default:
{
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_7; // variable_argument
}break;
case 0x41:case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:
case 0x48:case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:
case 0x4f:case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:
case 0x56:case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5f:case 0x61:
case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_8; // variable_general
}break;
}
}
{
state_label_7: // variable_argument
if (state.ptr == state.opl_ptr){
if ((!HasFlag(state.flags_KF0, 0x1))){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Variable;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
if ((HasFlag(state.flags_KF0, 0x1))){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Variable;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
goto state_label_5; // string
}
}
switch (*state.ptr){
default:
{
if ((HasFlag(state.flags_KF0, 0x1))){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Variable;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
goto state_label_5; // string
}
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Variable;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_7; // variable_argument
}break;
}
}
{
state_label_8: // variable_general
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_8; // variable_general
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x25:
{
if ((HasFlag(state.flags_KF0, 0x1))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Variable;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
goto state_label_5; // string
}
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_Variable;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
}
}
{
state_label_9: // comment_e
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_10; // comment_m
}break;
}
}
{
state_label_10: // comment_m
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_2; // identifier
}
}
switch (*state.ptr){
default:
{
goto state_label_2; // identifier
}break;
case 0x4d:case 0x6d:
{
state.ptr += 1;
goto state_label_11; // comment_line
}break;
}
}
{
state_label_11: // comment_line
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_11; // comment_line
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
}
}
{
state_label_12: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_CurrentDir;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_CurrentDir;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
do{
token.sub_kind = TokenBatchKind_ParentDir;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
goto state_label_1; // root
}break;
}
}
end:;
block_copy_struct(state_ptr, &state);
return(result);
}
internal Token_List
lex_full_input_batch(Arena *arena, String_Const_u8 input){
Lex_State_Batch state = {};
lex_full_input_batch_init(&state, input);
Token_List list = {};
lex_full_input_batch_breaks(arena, &list, &state, max_u64);
return(list);
}
