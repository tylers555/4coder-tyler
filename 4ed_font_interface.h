/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 11.03.2017
 *
 * Font system interface.
 *
 */

// TOP

#if !defined(FCODER_FONT_INTERFACE_H)
#define FCODER_FONT_INTERFACE_H

typedef i32 Texture_Kind;
enum{
    TextureKind_Error,
    TextureKind_Mono,
};

typedef u32 Graphics_Get_Texture_Function(Vec3_i32 dim, Texture_Kind texture_kind);
typedef b32 Graphics_Fill_Texture_Function(Texture_Kind texture_kind, u32 texture,
                                           Vec3_i32 p, Vec3_i32 dim, void *data);

////////////////////////////////

struct Glyph_Bounds{
    Rect_f32 uv;
    f32 w;
    Rect_f32 xy_off;
};

struct Codepoint_Index_Map{
    b32 has_zero_index;
    u16 zero_index;
    u16 max_index;
    Table_u32_u16 table;
};

struct Face{
    Face_Description description;
    Face_ID id;
    i32 version_number;
    
    // NOTE(allen): Metrics
    f32 text_height;
    f32 line_height;
    f32 ascent;
    f32 descent;
    f32 line_skip;
    f32 max_advance;
    
    f32 underline_yoff1;
    f32 underline_yoff2;
    
    f32 space_advance;
    f32 digit_advance;
    f32 hex_advance;
    f32 byte_advance;
    f32 byte_sub_advances[3];
    f32 typical_lowercase_advance;
    f32 typical_uppercase_advance;
    f32 typical_advance;
    
    // NOTE(allen): Glyph data
    Codepoint_Index_Map codepoint_to_index_map;
    u16 index_count;
    Glyph_Bounds *bounds;
    f32 *advance;
    Glyph_Bounds white;
    
    Texture_Kind texture_kind;
    u32 texture;
    Vec3_f32 texture_dim;
};

////////////////////////////////

// NOTE(allen): Platform layer calls - implemented in a "font provider"
typedef Face *Font_Make_Face_Function(Arena *arena, Face_Description *description, f32 scale_factor);

#endif

// BOTTOM


