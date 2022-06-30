// TOP

#define LANG_NAME_LOWER batch
#define LANG_NAME_CAMEL Batch

#include "lexer_generator/4coder_lex_gen_main.cpp"

internal void
build_language_model(void){
    u8 utf8[129];
    smh_utf8_fill(utf8);
    
    smh_set_base_character_names();
    smh_typical_tokens();
    
    // SJA Direct Token Kinds
    sm_select_base_kind(TokenBaseKind_Comment);
    sm_direct_token_kind("LineComment");
    
    sm_select_base_kind(TokenBaseKind_Whitespace);
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_direct_token_kind("LiteralInteger");
    
    sm_select_base_kind(TokenBaseKind_LiteralFloat);
    sm_direct_token_kind("LiteralFloat");
    
    sm_select_base_kind(TokenBaseKind_LiteralString);
    sm_direct_token_kind("LiteralString");
    
    Operator_Set *main_ops = sm_begin_op_set();
    
    sm_select_base_kind(TokenBaseKind_ScopeOpen);
    sm_op("(");
    sm_select_base_kind(TokenBaseKind_ScopeClose);
    sm_op(")");
    
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_direct_token_kind("EndWhitespace");
    
    sm_select_base_kind(TokenBaseKind_Operator);
    sm_char_name('@', "NoEcho");
    sm_op("@");
    sm_op("=");
    sm_op(":");
    sm_char_name('\\', "BackSlash");
    sm_op("\\");
    sm_char_name('/', "ForwardSlash");
    sm_op("/");
    sm_op("..", "ParentDir");
    sm_op(".", "CurrentDir");
    
    // SJA Keywords
    Keyword_Set *main_keys = sm_begin_key_set("main_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_direct_token_kind("KeywordGeneric");
    sm_key("Set",      "set");
    sm_key("SetLocal", "setlocal");
    sm_key("EndLocal", "endlocal");
    sm_key("PushDir",  "pushd");
    sm_key("PopDir",   "popd");
    sm_key("CD",       "cd");
    sm_key("Echo",     "echo");
    sm_key("Del",      "del");
    sm_key("Goto",     "goto");
    sm_key("If");
    sm_key("IfCaps", "IF");
    sm_key("Else");
    sm_key("ElseCaps", "ELSE");
    sm_key("Not");
    sm_key("NotCaps", "NOT");
    sm_key("Call");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key_fallback("Identifier");
    //sm_direct_token_kind("Label");
    sm_direct_token_kind("Variable");
    
    // State Machine
    State *root = sm_begin_state_machine();
    
    Flag *is_string = sm_add_flag(FlagResetRule_KeepState);
    //Flag *last_was_whitespace = sm_add_flag(FlagResetRule_KeepState);
    
#define AddState(N) State *N = sm_add_state(#N)
    
    AddState(identifier);
    AddState(whitespace);
    AddState(end_whitespace);
    
    AddState(number);
    
    AddState(string);
    
    AddState(variable_start);
    AddState(variable_argument);
    AddState(variable_general);
    
    AddState(comment_e);
    AddState(comment_m);
    AddState(comment_line);
    
    //~ Root
    sm_select_state(root);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("EOF");
        sm_case_eof(emit);
    }
    sm_case("abcdefghijklmnopqstuvwxyz"
            "ABCDEFGHIJKLMNOPQSTUVWXYZ"
            "_",
            identifier);
    sm_case("rR", comment_e);
    sm_case(" \r\t\f\v", whitespace);
    sm_case("\n", end_whitespace);
    //sm_case("#", comment_line);
    sm_case("\"", string);
    sm_case("%", variable_start);
    sm_case("0123456789", number);
    //sm_case_flagged(last_was_whitespace, true, ":", label_begin);
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
            "_-"
            "0123456789",
            identifier);
    //sm_set_flag(last_was_whitespace, false);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(main_keys);
        sm_fallback_peek(emit);
    }
    
    //~ Whitespace
    sm_select_state(whitespace);
    sm_case(" \r\t\f\v", whitespace);
    sm_case("\n", end_whitespace);
    //sm_set_flag(last_was_whitespace, true);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Whitespace");
        sm_fallback_peek(emit);
    }
    
    sm_select_state(end_whitespace);
    //sm_set_flag(last_was_whitespace, true);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("EndWhitespace");
        sm_fallback_peek(emit);
    }
    
    
    //~ Integer
    sm_select_state(number);
    sm_case("0123456789", number);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_", identifier);
    //sm_set_flag(last_was_whitespace, false);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    //~ String
    sm_select_state(string);
    sm_set_flag(is_string, true);
    //sm_set_flag(last_was_whitespace, false);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralString");
        sm_case_peek("%", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralString");
        sm_case("\"", emit);
        sm_on_transition_set_flag(is_string, false);
    }
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
    
    //~ Variable
    sm_select_state(variable_start);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_",
            variable_general);
    sm_case("0123456789", variable_argument);
    
    sm_select_state(variable_general);
    //sm_set_flag(last_was_whitespace, false);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Variable");
        sm_case(SCu8("%"), is_string,  true, string, Transition_Consume, emit);
        sm_case(SCu8("%"), is_string, false,   root, Transition_Consume, emit);
    }
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
    sm_case("%", variable_general);
    sm_fallback(variable_general);
    
    sm_select_state(variable_argument);
    sm_case("0123456789", variable_argument);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Variable");
        sm_case(TransitionCaseKind_Fallback, is_string,  true, string, Transition_NoConsume, emit);
        sm_case(TransitionCaseKind_Fallback, is_string, false,   root, Transition_NoConsume, emit);
    }
    
    //~ Comment
    sm_select_state(comment_e);
    //sm_set_flag(last_was_whitespace, false);
    sm_case("eE", comment_m);
    sm_fallback_peek(identifier);
    
    sm_select_state(comment_m);
    sm_case("mM", comment_line);
    sm_fallback_peek(identifier);
    
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
    
    //~ Label
#if 0
    sm_select_state(label_begin);
    //sm_set_flag(last_was_whitespace, false);
    sm_case(" \n\r\t\f\v", label_whitespace);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "_",
            label_end);
    sm_fallback_peek(root);
    
    ////
    sm_select_state(label_whitespace);
    sm_case(" \n\r\t\f\v", label_whitespace);
    sm_fallback_peek(label_begin);
    
    ////
    sm_select_state(label_end);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "_",
            label_end);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Label");
        sm_fallback(emit);
    }
#endif
}

// BOTTOM

