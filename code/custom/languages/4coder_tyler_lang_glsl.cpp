
internal void
F4_GLSL_ParseMacroDefinition(F4_Index_ParseCtx *ctx)
{
    Token *name = 0;
    if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Identifier, &name))
    {
        F4_Index_Note *last_parent = F4_Index_PushParent(ctx, 0);
        F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Macro, 0);
        F4_Index_PopParent(ctx, last_parent);
        F4_Index_SkipSoftTokens(ctx, 1);
    }
}

internal b32
F4_GLSL_SkipParseBody(F4_Index_ParseCtx *ctx)
{
    b32 body_found = 0;
    int nest = 0;
    
    for(;!ctx->done;)
    {
        Token *name = 0;
        
        if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Comment, &name))
        {
            F4_Index_ParseComment(ctx, name);
        }
        else if(F4_Index_ParsePattern(ctx, "%b", TokenGLSLKind_PPDefine, &name))
        {
            F4_GLSL_ParseMacroDefinition(ctx);
        }
        else if(F4_Index_ParsePattern(ctx, "%t", "{"))
        {
            nest += 1;
            body_found = 1;
        }
        else if(F4_Index_ParsePattern(ctx, "%t", "}"))
        {
            nest -= 1;
            if(nest == 0)
            {
                break;
            }
        }
        else if(body_found == 0)
        {
            break;
        }
        else
        {
            F4_Index_ParseCtx_Inc(ctx, F4_Index_TokenSkipFlag_SkipWhitespace);
        }
    }
    return body_found;
}

function b32
F4_GLSL_ParseDecl(F4_Index_ParseCtx *ctx, Token **name)
{
    Token *base_type = 0;
    return (F4_Index_ParsePattern(ctx, "%k%o%k%o%t",
                                  TokenBaseKind_Identifier, &base_type,
                                  TokenBaseKind_Identifier, name,
                                  ";") ||
            F4_Index_ParsePattern(ctx, "%k%o%k%t",
                                  TokenBaseKind_Identifier, &base_type,
                                  TokenBaseKind_Identifier, name,
                                  "="));
}

function b32
T4_GLSL_ParseMaybeDecl(F4_Index_ParseCtx *ctx, Token **base_type, Token **name)
{
    return (F4_Index_ParsePattern(ctx, "%k%o%k%o%t",
                                  TokenBaseKind_Keyword, &base_type,
                                  TokenBaseKind_Identifier, name,
                                  ";") ||
            F4_Index_ParsePattern(ctx, "%k%o%k%t",
                                  TokenBaseKind_Keyword, &base_type,
                                  TokenBaseKind_Identifier, name,
                                  "="));
}

function void
F4_GLSL_ParseStructOrUnionBodyIFuckingHateCPlusPlus(F4_Index_ParseCtx *ctx, F4_Index_NoteFlags note_flags)
{
    Token *name = 0;
    b32 valid = 0;
    b32 need_end_name = 0;
    
    if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Identifier, &name))
    {
        valid = 1;
    }
    else
    {
        need_end_name = 1;
    }
    
    if(F4_GLSL_SkipParseBody(ctx))
    {
    }
    else
    {
        note_flags |= F4_Index_NoteFlag_Prototype;
    }
    
    if(need_end_name)
    {
        if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Identifier, &name))
        {
            valid = 1;
        }
    }
    
    if(valid)
    {
        F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Type, note_flags);
    }
}

function b32
F4_GLSL_ParseFunctionBodyIFuckingHateCPlusPlus(F4_Index_ParseCtx *ctx, b32 *prototype_ptr)
{
    b32 valid = 0;
    b32 prototype = 0;
    
    for(;!ctx->done;)
    {
        Token *token = token_it_read(&ctx->it);
        if(token == 0) { break; }
        
        if(token->sub_kind == TokenGLSLKind_Semicolon)
        {
            valid = 1;
            prototype = 1;
            break;
        }
        else if(token->sub_kind == TokenGLSLKind_ParenCl)
        {
        }
        else if(token->kind == TokenBaseKind_ScopeOpen)
        {
            valid = 1;
            break;
        }
        
#if 0        
        //~ NOTE(Tyler): Labels
        else if(F4_Index_ParsePattern(ctx, "%k%t", TokenBaseKind_Identifier, &name, ":"))
        {
            //handled = 1;
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Label, F4_Index_NoteFlag_DontList);
        }
#endif
        
        F4_Index_ParseCtx_Inc(ctx, 0);
    }
    
    if(valid)
    {
        if(prototype == 0)
        {
            F4_GLSL_SkipParseBody(ctx);
        }
    }
    
    *prototype_ptr = prototype;
    
    return valid;
}

function void
F4_GLSL_ParseEnumBodyIFuckingHateCPlusPlus(F4_Index_ParseCtx *ctx)
{
    if(F4_Index_ParsePattern(ctx, "%t", "{"))
    {
        for(;!ctx->done;)
        {
            Token *constant = 0;
            if(F4_Index_ParsePattern(ctx, "%k%t", TokenBaseKind_Identifier, &constant, ","))
            {
                F4_Index_MakeNote(ctx, Ii64(constant), F4_Index_NoteKind_Constant, 0);
            }
            else if(F4_Index_ParsePattern(ctx, "%k%t", TokenBaseKind_Identifier, &constant, "="))
            {
                F4_Index_MakeNote(ctx, Ii64(constant), F4_Index_NoteKind_Constant, 0);
                
                for(;!ctx->done;)
                {
                    Token *token = token_it_read(&ctx->it);
                    if(token->kind == TokenBaseKind_StatementClose)
                    {
                        F4_Index_ParseCtx_Inc(ctx, 0);
                        break;
                    }
                    else if(token->kind == TokenBaseKind_ScopeClose ||
                            token->kind == TokenBaseKind_ScopeOpen)
                    {
                        break;
                    }
                    F4_Index_ParseCtx_Inc(ctx, 0);
                }
            }
            else if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Identifier, &constant))
            {
                F4_Index_MakeNote(ctx, Ii64(constant), F4_Index_NoteKind_Constant, 0);
            }
            else if(F4_Index_ParsePattern(ctx, "%t", "}"))
            {
                break;
            }
            else
            {
                F4_Index_ParseCtx_Inc(ctx, 0);
            }
        }
    }
}

internal F4_LANGUAGE_INDEXFILE(GLSL_IndexFile){
    int scope_nest = 0;
    for(b32 handled = 0; !ctx->done;)
    {
        handled = 0;
        
        Token *name = 0;
        Token *base_type = 0;
        F4_Index_Note *note = 0;
        
        if(0){}
        
        //~ NOTE(rjf): Scope Nest Changes
        else if(F4_Index_ParsePattern(ctx, "%t", "{"))
        {
            handled = 1;
            scope_nest += 1;
        }
        else if(F4_Index_ParsePattern(ctx, "%t", "}"))
        {
            handled = 1;
            scope_nest -= 1;
            if(scope_nest < 0)
            {
                scope_nest = 0;
            }
        }
        
        //~ NOTE(rjf): Structs
        else if(F4_Index_ParsePattern(ctx, "%t", "struct"))
        {
            handled = 1;
            F4_GLSL_ParseStructOrUnionBodyIFuckingHateCPlusPlus(ctx, F4_Index_NoteFlag_ProductType);
        }
        
        //~ NOTE(rjf): Functions
        else if(scope_nest == 0 &&
                (F4_Index_ParsePattern(ctx, "%k%o%k%t",
                                       TokenBaseKind_Identifier, &base_type,
                                       TokenBaseKind_Identifier, &name,
                                       "(") ||
                 F4_Index_ParsePattern(ctx, "%k%o%k%t",
                                       TokenBaseKind_Keyword, &base_type,
                                       TokenBaseKind_Identifier, &name,
                                       "(")))
        {
            handled = 1;
            b32 prototype = 0;
            if(F4_GLSL_ParseFunctionBodyIFuckingHateCPlusPlus(ctx, &prototype))
            {
                F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Function, prototype ? F4_Index_NoteFlag_Prototype : 0);
            }
        }
        
        //~ NOTE(Tyler): Uniform declarations
        else if(scope_nest == 0 &&
                F4_Index_ParsePattern(ctx, "%t%k%o%k%o%t","uniform",
                                      TokenBaseKind_Keyword, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      ";") || 
                F4_Index_ParsePattern(ctx, "%t%k%o%k%t", "uniform",
                                      TokenBaseKind_Keyword, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      "=") ||
                F4_Index_ParsePattern(ctx, "%t%k%o%k%o%t", "uniform",
                                      TokenBaseKind_Identifier, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      ";") ||
                F4_Index_ParsePattern(ctx, "%t%k%o%k%t", "uniform",
                                      TokenBaseKind_Identifier, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      "=")){
            handled = 1;
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_GLSL_Uniform, 0);
        }
        
        //~ NOTE(Tyler): In declarations
        else if(scope_nest == 0 &&
                F4_Index_ParsePattern(ctx, "%t%k%o%k%o%t","in",
                                      TokenBaseKind_Keyword, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      ";") || 
                F4_Index_ParsePattern(ctx, "%t%k%o%k%t","in",
                                      TokenBaseKind_Keyword, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      "=") ||
                F4_Index_ParsePattern(ctx, "%t%k%o%k%o%t","in",
                                      TokenBaseKind_Identifier, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      ";") ||
                F4_Index_ParsePattern(ctx, "%t%k%o%k%t","in",
                                      TokenBaseKind_Identifier, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      "=")){
            handled = 1;
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_GLSL_In, 0);
        }
        
        //~ NOTE(Tyler): Out declarations
        else if(scope_nest == 0 &&
                F4_Index_ParsePattern(ctx, "%t%k%o%k%o%t","out",
                                      TokenBaseKind_Keyword, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      ";") || 
                F4_Index_ParsePattern(ctx, "%t%k%o%k%t","out",
                                      TokenBaseKind_Keyword, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      "=") ||
                F4_Index_ParsePattern(ctx, "%t%k%o%k%o%t","out",
                                      TokenBaseKind_Identifier, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      ";") ||
                F4_Index_ParsePattern(ctx, "%t%k%o%k%t","out",
                                      TokenBaseKind_Identifier, &base_type,
                                      TokenBaseKind_Identifier, &name,
                                      "=")){
            handled = 1;
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_GLSL_Out, 0);
        }
        
        //~ NOTE(rjf): Declarations
        else if(scope_nest == 0 && 
                (F4_GLSL_ParseDecl(ctx, &name) || T4_GLSL_ParseMaybeDecl(ctx, &base_type, &name)))
        {
            handled = 1;
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Decl, 0);
        }
        
        //~ NOTE(rjf): Macro Functions
        else if(0 && F4_Index_ParsePattern(ctx, "%n%t%k",
                                           F4_Index_NoteKind_Macro, &note,
                                           "(",
                                           TokenBaseKind_Identifier, &name))
        {
            b32 valid = 0;
            b32 prototype = 0;
            
            for(;!ctx->done;)
            {
                Token *token = token_it_read(&ctx->it);
                if(token == 0) { break; }
                if(token->sub_kind == TokenGLSLKind_Semicolon)
                {
                    prototype = 1;
                    valid = 1;
                    break;
                }
                else if(token->sub_kind == TokenGLSLKind_ParenCl)
                {
                }
                else if(token->kind == TokenBaseKind_ScopeOpen)
                {
                    valid = 1;
                    break;
                }
                F4_Index_ParseCtx_Inc(ctx, 0);
            }
            
            if(valid)
            {
                handled = 1;
                F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Function, prototype ? F4_Index_NoteFlag_ProductType : 0);
                F4_GLSL_SkipParseBody(ctx);
            }
        }
        
        //~ NOTE(rjf): Comment Tags
        else if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Comment, &name))
        {
            handled = 1;
            F4_Index_ParseComment(ctx, name);
        }
        
        //~ NOTE(rjf): Macros
        else if(F4_Index_ParsePattern(ctx, "%b", TokenGLSLKind_PPDefine, &name))
        {
            handled = 1;
            F4_GLSL_ParseMacroDefinition(ctx);
        }
        
        if(handled == 0)
        {
            F4_Index_ParseCtx_Inc(ctx, 0);
        }
    }
}

internal F4_LANGUAGE_POSCONTEXT(GLSL_PosContext){
    int count = 0;
    F4_Language_PosContextData *first = 0;
    F4_Language_PosContextData *last = 0;
    
    Token_Array tokens = get_token_array_from_buffer(app, buffer);
    Token_Iterator_Array it = token_iterator_pos(0, &tokens, pos);
    
    // NOTE(rjf): Search for left parentheses (function call or macro invocation).
    {
        int paren_nest = 0;
        int arg_idx = 0;
        for(int i = 0; count < 4; i += 1)
        {
            Token *token = token_it_read(&it);
            if(token)
            {
                if(paren_nest == 0 &&
                   token->sub_kind == TokenCppKind_ParenOp &&
                   token_it_dec_non_whitespace(&it))
                {
                    Token *name = token_it_read(&it);
                    if(name && name->kind == TokenBaseKind_Identifier)
                    {
                        F4_Language_PosContext_PushData_Call(arena, &first, &last, push_buffer_range(app, arena, buffer, Ii64(name)), arg_idx);
                        count += 1;
                        arg_idx = 0;
                    }
                }
                else if(token->sub_kind == TokenCppKind_ParenOp)
                {
                    paren_nest -= 1;
                }
                else if(token->sub_kind == TokenCppKind_ParenCl && i > 0)
                {
                    paren_nest += 1;
                }
                else if(token->sub_kind == TokenCppKind_Comma && i > 0 && paren_nest == 0)
                {
                    arg_idx += 1;
                }
            }
            else { break; }
            if(!token_it_dec_non_whitespace(&it))
            {
                break;
            }
        }
    }
    
    return first;
}

internal F4_LANGUAGE_HIGHLIGHT(GLSL_Highlight){
    Scratch_Block scratch(app);
    
    Token_Iterator_Array it = token_iterator_pos(0, array, 0);
    
    while(true){
        Token *token = token_it_read(&it);
        if(!token) break;
        
        if(token->kind == TokenBaseKind_Identifier){
            //String_Const_u8 string = push_buffer_range(app, scratch, buffer, Ii64(token));
        }
        
        if(!token_it_inc_non_whitespace(&it)) break;
    }
}

internal T4_LANGUAGE_INDENT(GLSL_Indent){
}
