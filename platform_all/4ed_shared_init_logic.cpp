/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 18.07.2017
 *
 * Shared logic for 4coder initialization.
 *
 */

// TOP

internal void
memory_init(Arena *scratch){
#if defined(FRED_INTERNAL)
# if ARCH_64BIT
    void *bases[] = { (void*)TB(1), (void*)TB(2), };
# else
    void *bases[] = { (void*)MB(96), (void*)MB(512), };
# endif
#else
    void *bases[] = { (void*)0, (void*)0, };
#endif
    
    memory_vars.vars_memory_size = MB(128);
    memory_vars.vars_memory = system_memory_allocate_extended(bases[0], memory_vars.vars_memory_size);
    memory_vars.target_memory_size = MB(512);
    memory_vars.target_memory = system_memory_allocate_extended(bases[1], memory_vars.target_memory_size);
    memory_vars.user_memory_size = MB(32);
    memory_vars.user_memory = system_memory_allocate_extended(0, memory_vars.user_memory_size);
    memory_vars.debug_memory_size = MB(512);
    memory_vars.debug_memory = system_memory_allocate_extended(0, memory_vars.debug_memory_size);
    
    i32 render_memsize = MB(1);
    target.arena = make_arena_system(&sysfunc);
    
    b32 alloc_success = true;
    if (memory_vars.vars_memory == 0 || memory_vars.target_memory == 0 || memory_vars.user_memory == 0){
        alloc_success = false;
    }
    
    if (!alloc_success){
        char msg[] = "Could not allocate sufficient memory. Please make sure you have atleast 512Mb of RAM free. (This requirement will be relaxed in the future).";
        system_error_box(scratch, msg);
    }
}

internal void
load_app_code(Arena *scratch){
    App_Get_Functions *get_funcs = 0;
    
    if (system_load_library(scratch, &libraries.app_code, "4ed_app", LoadLibrary_BinaryDirectory)){
        get_funcs = (App_Get_Functions*)system_get_proc(&libraries.app_code, "app_get_functions");
    }
    else{
        char msg[] = "Could not load '4ed_app." DLL "'. This file should be in the same directory as the main '4ed' executable.";
        system_error_box(scratch, msg);
    }
    
    if (get_funcs != 0){
        app = get_funcs();
    }
    else{
        char msg[] = "Failed to get application code from '4ed_app." DLL "'.";
        system_error_box(scratch, msg);
    }
}

global char custom_fail_version_msg[] = "Failed to load custom code due to missing version information or a version mismatch.  Try rebuilding with buildsuper.";

global char custom_fail_missing_get_bindings_msg[] = "Failed to load custom code due to missing 'get_bindings' symbol.  Try rebuilding with buildsuper.";

internal void
load_custom_code(Arena *scratch){
    local_persist char *default_file = "custom_4coder";
    local_persist Load_Library_Location locations[] = {
        LoadLibrary_CurrentDirectory,
        LoadLibrary_BinaryDirectory,
    };
    
    char *custom_files[3] = {};
    if (plat_settings.custom_dll != 0){
        custom_files[0] = plat_settings.custom_dll;
        if (!plat_settings.custom_dll_is_strict){
            custom_files[1] = default_file;
        }
    }
    else{
        custom_files[0] = default_file;
    }
    
    char success_file[4096];
    b32 has_library = false;
    for (u32 i = 0; custom_files[i] != 0 && !has_library; ++i){
        char *file = custom_files[i];
        for (u32 j = 0; j < ArrayCount(locations) && !has_library; ++j){
            if (system_load_library(scratch, &libraries.custom, file, locations[j], success_file, sizeof(success_file))){
                has_library = true;
                success_file[sizeof(success_file) - 1] = 0;
            }
        }
    }
    
    if (!has_library){
        system_error_box(scratch, "Did not find a library for the custom layer.");
    }
    
    custom_api.get_alpha_4coder_version = (_Get_Version_Function*)
        system_get_proc(&libraries.custom, "get_alpha_4coder_version");
    
    if (custom_api.get_alpha_4coder_version == 0 || custom_api.get_alpha_4coder_version(MAJOR, MINOR, PATCH) == 0){
        system_error_box(scratch, custom_fail_version_msg);
    }
    
    custom_api.get_bindings = (Get_Binding_Data_Function*)
        system_get_proc(&libraries.custom, "get_bindings");
    
    if (custom_api.get_bindings == 0){
        system_error_box(scratch, custom_fail_missing_get_bindings_msg);
    }
    
    //LOGF("Loaded custom file: %s\n", success_file);
}

internal void
read_command_line(Arena *scratch, i32 argc, char **argv){
    Temp_Memory temp = begin_temp(scratch);
    String_Const_u8 curdir = sysfunc.get_current_path(scratch);
    curdir = string_mod_replace_character(curdir, '\\', '/');
    
    char **files = 0;
    i32 *file_count = 0;
    app.read_command_line(&sysfunc, &memory_vars, curdir, &plat_settings, &files, &file_count, argc, argv);
    sysshared_filter_real_files(scratch, files, file_count);
    end_temp(temp);
}

// BOTTOM

