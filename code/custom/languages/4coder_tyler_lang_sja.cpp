internal F4_LANGUAGE_INDEXFILE(SJA_IndexFile){
    while(!ctx->done){
        b32 Handled = false;
        Token *token = token_it_read(&ctx->it);
        if(!token) break;
        
        Token *base_type = 0;
        Token *name = 0;
        if(F4_Index_ParsePattern(ctx, "%k%k",
                                 TokenBaseKind_Keyword, &base_type,
                                 TokenBaseKind_LiteralString, &name)){
            Handled = true;
            String_Const_u8 asset_type = F4_Index_StringFromToken(ctx, base_type);
            if(string_match(asset_type, S8Lit(": Ignore "))) continue;
            F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Asset, 0);
            
        }else if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Comment, &name)){
            Handled = true;
            F4_Index_ParseComment(ctx, name);
        }
        
        if(!Handled){
            F4_Index_ParseCtx_Inc(ctx, 0);
        }
    }
}

internal F4_LANGUAGE_POSCONTEXT(SJA_PosContext){
    return 0;
}

internal F4_LANGUAGE_HIGHLIGHT(SJA_Highlight){
    Token_Iterator_Array it = token_iterator_pos(0, array, 0);
    
    while(true){
        Token *token = token_it_read(&it);
        if(!token) break;
        
        if(token->kind == TokenBaseKind_Identifier){
            if(!token_it_inc_non_whitespace(&it)) break;
            if(token_it_read(&it)->kind != TokenBaseKind_ParentheticalOpen) continue;
            
            paint_text_color(app, text_layout_id, Ii64(token), F4_ARGBFromID(color_table, tyler_color_index_built_in_function));
        }
        
        if(!token_it_inc_non_whitespace(&it)) break;
    }
    
}

internal T4_LANGUAGE_INDENT(SJA_Indent){
    
}
