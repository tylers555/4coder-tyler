/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 19.05.2017
 *
 * Parse contexts allocation and locking.
 *
 */

// TOP

struct Parser_String_And_Type{
    char *str;
    u32 length;
    u32 type;
};

struct Stored_Parse_Context{
    umem memsize;
    u64 *kw_keywords;
    u64 *pp_keywords;
    u32 kw_max;
    u32 pp_max;
};

struct Stored_Parse_Context_Slot{
    union{
        Stored_Parse_Context_Slot *next;
        Stored_Parse_Context *context;
    };
    b32 freed;
};

struct Parse_Context_Memory{
    Stored_Parse_Context_Slot *parse_context_array;
    u32 parse_context_counter;
    u32 parse_context_max;
    
    Stored_Parse_Context_Slot free_sentinel;
};

internal void
parse_context_init_memory(Parse_Context_Memory *parse_mem, void *mem, umem memsize){
    sll_init_sentinel(&parse_mem->free_sentinel);
    
    parse_mem->parse_context_array = (Stored_Parse_Context_Slot*)mem;
    parse_mem->parse_context_counter = 0;
    parse_mem->parse_context_max = (u32)(memsize / sizeof(*parse_mem->parse_context_array));
}

internal u32
parse_context_add(Parse_Context_Memory *parse_mem, General_Memory *general, Parser_String_And_Type *kw_sats, u32 kw_count, Parser_String_And_Type *pp_sats, u32 pp_count){
    Stored_Parse_Context_Slot *slot = 0;
    if (parse_mem->free_sentinel.next != &parse_mem->free_sentinel){
        slot = parse_mem->free_sentinel.next;
        sll_remove(&parse_mem->free_sentinel, slot);
    }
    else if (parse_mem->parse_context_counter < parse_mem->parse_context_max){
        slot = &parse_mem->parse_context_array[parse_mem->parse_context_counter++];
    }
    
    u32 result = 0;
    if (slot != 0){
        u32 stride = sizeof(*kw_sats);
        umem kw_memsize = cpp_get_table_memory_size_string_lengths(&kw_sats->length, stride, kw_count);
        umem pp_memsize = cpp_get_table_memory_size_string_lengths(&pp_sats->length, stride, pp_count);
        
        umem memsize = kw_memsize + pp_memsize + sizeof(Stored_Parse_Context);
        void *mem = general_memory_allocate(general, (i32)memsize);
        
        Stored_Parse_Context *parse_context = (Stored_Parse_Context*)mem;
        u8 *kw_mem = (u8*)(parse_context+1);
        u8 *pp_mem = kw_mem + kw_memsize;
        
        Cpp_Keyword_Table kw_table = cpp_make_table(&kw_sats->str, stride, &kw_sats->length, stride, &kw_sats->type, stride, kw_count, kw_mem, kw_memsize);
        
        Cpp_Keyword_Table pp_table = cpp_make_table(&pp_sats->str, stride, &pp_sats->length, stride, &pp_sats->type, stride, pp_count, pp_mem, pp_memsize);
        
        parse_context->memsize = memsize;
        parse_context->kw_keywords = kw_table.keywords;
        parse_context->pp_keywords = pp_table.keywords;
        parse_context->kw_max = kw_table.max;
        parse_context->pp_max = pp_table.max;
        slot->context = parse_context;
        slot->freed = false;
        
        result = (u32)(slot - parse_mem->parse_context_array) + parse_mem->parse_context_max;
    }
    
    return(result);
}

internal u32
parse_context_add_default(Parse_Context_Memory *parse_mem, General_Memory *general){
    Stored_Parse_Context_Slot *slot = 0;
    if (parse_mem->free_sentinel.next != &parse_mem->free_sentinel){
        slot = parse_mem->free_sentinel.next;
        sll_remove(&parse_mem->free_sentinel, slot);
    }
    else if (parse_mem->parse_context_counter < parse_mem->parse_context_max){
        slot = &parse_mem->parse_context_array[parse_mem->parse_context_counter++];
    }
    
    u32 result = 0;
    if (slot != 0){
        umem kw_memsize = cpp_get_table_memory_size_default(CPP_TABLE_KEYWORDS);
        umem pp_memsize = cpp_get_table_memory_size_default(CPP_TABLE_PREPROCESSOR_DIRECTIVES);
        
        umem memsize = kw_memsize + pp_memsize + sizeof(Stored_Parse_Context);
        void *mem = general_memory_allocate(general, (i32)(memsize));
        
        Stored_Parse_Context *parse_context = (Stored_Parse_Context*)mem;
        u8 *kw_mem = (u8*)(parse_context+1);
        u8 *pp_mem = kw_mem + kw_memsize;
        
        Cpp_Keyword_Table kw_table = cpp_make_table_default(CPP_TABLE_KEYWORDS, kw_mem, kw_memsize);
        Cpp_Keyword_Table pp_table = cpp_make_table_default(CPP_TABLE_PREPROCESSOR_DIRECTIVES, pp_mem, pp_memsize);
        
        parse_context->memsize = memsize;
        parse_context->kw_keywords = kw_table.keywords;
        parse_context->pp_keywords = pp_table.keywords;
        parse_context->kw_max = kw_table.max;
        parse_context->pp_max = pp_table.max;
        slot->context = parse_context;
        slot->freed = false;
        
        result = (u32)(slot - parse_mem->parse_context_array) + parse_mem->parse_context_max;
    }
    
    return(result);
}

struct Parse_Context{
    b32 valid;
    Cpp_Keyword_Table kw_table;
    Cpp_Keyword_Table pp_table;
    umem memory_size;
};

internal Parse_Context
parse_context_get(Parse_Context_Memory *parse_mem, u32 id, void *mem, umem memsize){
    Parse_Context result = {0};
    
    Stored_Parse_Context_Slot *slot = 0;
    if (id == 0){
        // do nothing
    }
    else{
        id -= parse_mem->parse_context_max;
    }
    
    if (id < parse_mem->parse_context_counter){
        slot = &parse_mem->parse_context_array[id];
        if (slot->freed){
            slot = 0;
        }
    }
    
    if (slot != 0){
        Stored_Parse_Context *context = slot->context;
        if (context->memsize < memsize){
            u8 *base_ptr = (u8*)context;
            u8 *kw_keywords = (u8*)mem + (((u8*)context->kw_keywords) - base_ptr);
            u8 *pp_keywords = (u8*)mem + (((u8*)context->pp_keywords) - base_ptr);
            result.valid = true;
            result.kw_table.keywords = (u64*)kw_keywords;
            result.pp_table.keywords = (u64*)pp_keywords;
            result.kw_table.max = context->kw_max;
            result.pp_table.max = context->pp_max;
            result.memory_size = context->memsize;
            memcpy(mem, context, context->memsize);
        }
    }
    
    return(result);
}

// BOTTOM

