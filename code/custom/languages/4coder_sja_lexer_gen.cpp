// TOP

#define LANG_NAME_LOWER sja
#define LANG_NAME_CAMEL SJA

#include "lexer_generator/4coder_lex_gen_main.cpp"

internal void
build_language_model(void){
    u8 utf8[129];
    smh_utf8_fill(utf8);
    
    smh_set_base_character_names();
    smh_typical_tokens();
    
    // SJA Direct Token Kinds
    sm_select_base_kind(TokenBaseKind_Comment);
    sm_direct_token_kind("BlockComment");
    sm_direct_token_kind("LineComment");
    
    sm_select_base_kind(TokenBaseKind_Whitespace);
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_direct_token_kind("LiteralInteger");
    sm_direct_token_kind("LiteralIntegerHex");
    
    sm_select_base_kind(TokenBaseKind_LiteralFloat);
    sm_direct_token_kind("LiteralFloat");
    
    sm_select_base_kind(TokenBaseKind_LiteralString);
    sm_direct_token_kind("LiteralString");
    
    Operator_Set *main_ops = sm_begin_op_set();
    
    sm_select_base_kind(TokenBaseKind_ParentheticalOpen);
    sm_op("(");
    sm_select_base_kind(TokenBaseKind_ParentheticalClose);
    sm_op(")");
    
    sm_select_base_kind(TokenBaseKind_Operator);
    sm_char_name(':', "BeginCommand");
    
    // SJA Keywords
    Keyword_Set *main_keys = sm_begin_key_set("main_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_direct_token_kind("KeywordGeneric");
    sm_direct_token_kind("Command");
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_key("LiteralTrue", "true");
    sm_key("LiteralFalse", "false");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key_fallback("Identifier");
    
    // State Machine
    State *root = sm_begin_state_machine();
    
    Flag *is_hex = sm_add_flag(FlagResetRule_AutoZero);
    
#define AddState(N) State *N = sm_add_state(#N)
    
    AddState(identifier);
    AddState(whitespace);
    
    AddState(pre_number);
    AddState(number);
    AddState(fnumber_decimal);
    AddState(number_hex_first);
    AddState(number_hex);
    
    AddState(string);
    AddState(string_esc);
    
    AddState(comment_line);
    
    AddState(command_begin);
    AddState(command_whitespace);
    AddState(command_end);
    
    //~ Root
    sm_select_state(root);
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("EOF");
        sm_case_eof(emit);
    }
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_",
            identifier);
    sm_case(" \n\r\t\f\v", whitespace);
    sm_case("#", comment_line);
    sm_case(":", command_begin);
    sm_case("\"", string);
    sm_case("123456789", number);
    sm_case("0", pre_number);
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops);
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback(emit);
    }
    
    //~ Identifier
    sm_select_state(identifier);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "_",
            identifier);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(main_keys);
        sm_fallback_peek(emit);
    }
    
    //~ Whitespace
    sm_select_state(whitespace);
    sm_case(" \n\r\t\f\v", whitespace);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Whitespace");
        sm_fallback_peek(emit);
    }
    
    //~ Pre number
    sm_select_state(pre_number);
    sm_case("0123456789", number);
    sm_case(".", fnumber_decimal);
    sm_case("xX", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    
    //~ Integer
    sm_select_state(number);
    sm_case("0123456789", number);
    sm_case(".", fnumber_decimal);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    //~ Float
    sm_select_state(fnumber_decimal);
    sm_select_state(fnumber_decimal);
    sm_case("0123456789", fnumber_decimal);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat");
        sm_fallback_peek(emit);
    }
    
    //~ Hex number first
    sm_select_state(number_hex_first);
    sm_set_flag(is_hex, true);
    sm_case("0123456789abcdefABCDEF", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    //~ Hex number
    sm_select_state(number_hex);
    sm_case("0123456789abcdefABCDEF", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerHex");
        sm_fallback_peek(emit);
    }
    
    //~ String
    sm_select_state(string);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralString");
        sm_case("\"", emit);
    }
    sm_case("\\", string_esc);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_case("\"", string);
    sm_fallback(string);
    
    //~ String escape
    sm_select_state(string_esc);
    sm_case("\\n", string);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(string);
    
    //~ Comment
    sm_select_state(comment_line);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LineComment");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LineComment");
        sm_case_eof_peek(emit);
    }
    sm_fallback(comment_line);
    
    //~ Command
    sm_select_state(command_begin);
    sm_case(" \n\r\t\f\v", command_whitespace);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "_",
            command_end);
    sm_fallback_peek(root);
    
    ////
    sm_select_state(command_whitespace);
    sm_case(" \n\r\t\f\v", command_whitespace);
    sm_fallback_peek(command_begin);
    
    ////
    sm_select_state(command_end);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "_",
            command_end);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Command");
        sm_fallback(emit);
    }
    
}

// BOTTOM

