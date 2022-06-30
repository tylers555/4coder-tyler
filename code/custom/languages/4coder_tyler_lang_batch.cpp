internal F4_LANGUAGE_INDEXFILE(Batch_IndexFile){
    while(!ctx->done){
        b32 handled = false;
        Token *token = token_it_read(&ctx->it);
        if(!token) break;
        
        Token *dummy = 0;
        Token *base_type = 0;
        Token *name = 0;
        if(F4_Index_ParsePattern(ctx, "%k%k%k",
                                 TokenBaseKind_StatementClose, &dummy,
                                 TokenBaseKind_Operator, &base_type,
                                 TokenBaseKind_Identifier, &name)){
            handled = true;
            if(base_type->sub_kind == TokenBatchKind_Colon){
                F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Label, 0);
            }
        }else if(F4_Index_ParsePattern(ctx, "%k%k",
                                       TokenBaseKind_Keyword, &base_type,
                                       TokenBaseKind_Identifier, &name)){
            handled = true;
            if(base_type->sub_kind == TokenBatchKind_Set){
                F4_Index_MakeNote(ctx, Ii64(name), F4_Index_NoteKind_Decl, 0);
            }
        }else if(F4_Index_ParsePattern(ctx, "%k", TokenBaseKind_Comment, &name)){
            handled = true;
            F4_Index_ParseComment(ctx, name);
        }
        
        if(!handled){
            F4_Index_ParseCtx_Inc(ctx, 0);
        }
    }
}

internal F4_LANGUAGE_POSCONTEXT(Batch_PosContext){
    return 0;
}

internal F4_LANGUAGE_HIGHLIGHT(Batch_Highlight){
    Token_Iterator_Array it = token_iterator_pos(0, array, 0);
    
    while(true){
        Token *token = token_it_read(&it);
        if(!token) break;
        
        if(token->sub_kind == TokenBatchKind_Variable){
            paint_text_color(app, text_layout_id, Ii64(token), F4_ARGBFromID(color_table, fleury_color_index_decl));
        }
        
        if(!token_it_inc_non_whitespace(&it)) break;
    }
}

internal T4_LANGUAGE_INDENT(Batch_Indent){
    
}
