
// TOP

#define LANG_NAME_LOWER glsl
#define LANG_NAME_CAMEL GLSL

#include "lexer_generator/4coder_lex_gen_main.cpp"

internal void
build_language_model(void){
    u8 utf8[129];
    smh_utf8_fill(utf8);
    
    smh_set_base_character_names();
    smh_typical_tokens();
    
    // CPP Names
    sm_char_name('!', "Not");
    sm_char_name('&', "And");
    sm_char_name('|', "Or");
    sm_char_name('%', "Mod");
    sm_char_name('^', "Xor");
    sm_char_name('?', "Ternary");
    sm_char_name('/', "Div");
    
    // CPP Direct Toke Kinds
    sm_select_base_kind(TokenBaseKind_Comment);
    sm_direct_token_kind("BlockComment");
    sm_direct_token_kind("LineComment");
    
    sm_select_base_kind(TokenBaseKind_Whitespace);
    sm_direct_token_kind("Backslash");
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_direct_token_kind("LiteralInteger");
    sm_direct_token_kind("LiteralIntegerU");
    sm_direct_token_kind("LiteralIntegerL");
    sm_direct_token_kind("LiteralIntegerUL");
    sm_direct_token_kind("LiteralIntegerLL");
    sm_direct_token_kind("LiteralIntegerULL");
    sm_direct_token_kind("LiteralIntegerHex");
    sm_direct_token_kind("LiteralIntegerHexU");
    sm_direct_token_kind("LiteralIntegerHexL");
    sm_direct_token_kind("LiteralIntegerHexUL");
    sm_direct_token_kind("LiteralIntegerHexLL");
    sm_direct_token_kind("LiteralIntegerHexULL");
    sm_direct_token_kind("LiteralIntegerOct");
    sm_direct_token_kind("LiteralIntegerOctU");
    sm_direct_token_kind("LiteralIntegerOctL");
    sm_direct_token_kind("LiteralIntegerOctUL");
    sm_direct_token_kind("LiteralIntegerOctLL");
    sm_direct_token_kind("LiteralIntegerOctULL");
    
    sm_select_base_kind(TokenBaseKind_LiteralFloat);
    sm_direct_token_kind("LiteralFloat32");
    sm_direct_token_kind("LiteralFloat64");
    
    sm_select_base_kind(TokenBaseKind_LiteralString);
    sm_direct_token_kind("LiteralString");
    sm_direct_token_kind("LiteralStringWide");
    sm_direct_token_kind("LiteralStringUTF8");
    sm_direct_token_kind("LiteralStringUTF16");
    sm_direct_token_kind("LiteralStringUTF32");
    sm_direct_token_kind("LiteralStringRaw");
    sm_direct_token_kind("LiteralStringWideRaw");
    sm_direct_token_kind("LiteralStringUTF8Raw");
    sm_direct_token_kind("LiteralStringUTF16Raw");
    sm_direct_token_kind("LiteralStringUTF32Raw");
    sm_direct_token_kind("LiteralCharacter");
    sm_direct_token_kind("LiteralCharacterWide");
    sm_direct_token_kind("LiteralCharacterUTF8");
    sm_direct_token_kind("LiteralCharacterUTF16");
    sm_direct_token_kind("LiteralCharacterUTF32");
    sm_direct_token_kind("PPErrorMessage");
    sm_direct_token_kind("PPVersionMessage");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_direct_token_kind("KeywordGeneric");
    
    // CPP Operators
    Operator_Set *main_ops = sm_begin_op_set();
    
    sm_select_base_kind(TokenBaseKind_ScopeOpen);
    sm_op("{");
    sm_select_base_kind(TokenBaseKind_ScopeClose);
    sm_op("}");
    sm_select_base_kind(TokenBaseKind_ParentheticalOpen);
    sm_op("(");
    sm_op("[");
    sm_select_base_kind(TokenBaseKind_ParentheticalClose);
    sm_op(")");
    sm_op("]");
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_op(";");
    sm_op(":");
    sm_select_base_kind(TokenBaseKind_Operator);
    sm_op("...");
    
    sm_op("::");
    sm_op("++");
    sm_op("--");
    sm_op(".");
    sm_op("->", "Arrow");
    sm_op("+");
    sm_op("-");
    sm_op("!");
    sm_op("~");
    sm_op("*");
    sm_op("&");
    sm_op(".*");
    sm_op("->*", "ArrowStar");
    sm_op("/");
    sm_op("%");
    
    sm_char_name('<', "Left");
    sm_char_name('>', "Right");
    sm_op("<<");
    sm_op(">>");
    
    sm_op("<=>", "Compare");
    
    sm_char_name('<', "Less");
    sm_char_name('>', "Grtr");
    sm_op("<");
    sm_op("<=");
    sm_op(">");
    sm_op(">=");
    sm_op("==");
    sm_op("!=");
    
    sm_op("^");
    sm_op("|");
    sm_op("&&");
    sm_op("||");
    sm_op("?");
    sm_op("=");
    sm_op("+=");
    sm_op("-=");
    sm_op("*=");
    sm_op("/=");
    sm_op("%=");
    
    sm_char_name('<', "Left");
    sm_char_name('>', "Right");
    sm_op("<<=");
    sm_op(">>=");
    
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_op(",");
    
    // CPP Preprocess Operators
    Operator_Set *pp_ops = sm_begin_op_set();
    
    sm_op("#", "PPStringify");
    sm_op("##", "PPConcat");
    
    // CPP Keywords
    Keyword_Set *main_keys = sm_begin_key_set("main_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_key("attribute", "attribute");
    sm_key("const", "const");
    sm_key("uniform", "uniform");
    sm_key("varying", "varying");
    sm_key("layout", "layout");
    sm_key("Basics", "Basics");
    sm_key("centroid", "centroid");
    sm_key("flat", "flat");
    sm_key("smooth", "smooth");
    sm_key("noperspective", "noperspective");
    sm_key("patch", "patch");
    sm_key("sample", "sample");
    sm_key("break", "break");
    sm_key("continue", "continue");
    sm_key("do", "do");
    sm_key("for", "for");
    sm_key("while", "while");
    sm_key("switch", "switch");
    sm_key("case", "case");
    sm_key("default", "default");
    sm_key("if", "if");
    sm_key("else", "else");
    sm_key("subroutine", "subroutine");
    sm_key("in", "in");
    sm_key("out", "out");
    sm_key("inout", "inout");
    sm_key("float", "float");
    sm_key("double", "double");
    sm_key("int", "int");
    sm_key("void", "void");
    sm_key("bool", "bool");
    sm_key("invariant", "invariant");
    sm_key("discard", "discard");
    sm_key("return", "return");
    sm_key("mat2", "mat2");
    sm_key("mat3", "mat3");
    sm_key("mat4", "mat4");
    sm_key("dmat2", "dmat2");
    sm_key("dmat3", "dmat3");
    sm_key("dmat4", "dmat4");
    sm_key("mat2x2", "mat2x2");
    sm_key("mat2x3", "mat2x3");
    sm_key("mat2x4", "mat2x4");
    sm_key("dmat2x2", "dmat2x2");
    sm_key("dmat2x3", "dmat2x3");
    sm_key("dmat2x4", "dmat2x4");
    sm_key("mat3x2", "mat3x2");
    sm_key("mat3x3", "mat3x3");
    sm_key("mat3x4", "mat3x4");
    sm_key("dmat3x2", "dmat3x2");
    sm_key("dmat3x3", "dmat3x3");
    sm_key("dmat3x4", "dmat3x4");
    sm_key("mat4x2", "mat4x2");
    sm_key("mat4x3", "mat4x3");
    sm_key("mat4x4", "mat4x4");
    sm_key("dmat4x2", "dmat4x2");
    sm_key("dmat4x3", "dmat4x3");
    sm_key("dmat4x4", "dmat4x4");
    sm_key("vec2", "vec2");
    sm_key("vec3", "vec3");
    sm_key("vec4", "vec4");
    sm_key("ivec2", "ivec2");
    sm_key("ivec3", "ivec3");
    sm_key("ivec4", "ivec4");
    sm_key("bvec2", "bvec2");
    sm_key("bvec3", "bvec3");
    sm_key("bvec4", "bvec4");
    sm_key("dvec2", "dvec2");
    sm_key("dvec3", "dvec3");
    sm_key("dvec4", "dvec4");
    sm_key("uint", "uint");
    sm_key("uvec2", "uvec2");
    sm_key("uvec3", "uvec3");
    sm_key("uvec4", "uvec4");
    sm_key("lowp", "lowp");
    sm_key("mediump", "mediump");
    sm_key("highp", "highp");
    sm_key("precision", "precision");
    sm_key("sampler1D", "sampler1D");
    sm_key("sampler2D", "sampler2D");
    sm_key("sampler3D", "sampler3D");
    sm_key("samplerCube", "samplerCube");
    sm_key("sampler1DShadow", "sampler1DShadow");
    sm_key("sampler2DShadow", "sampler2DShadow");
    sm_key("samplerCubeShadow", "samplerCubeShadow");
    sm_key("sampler1DArray", "sampler1DArray");
    sm_key("sampler2DArray", "sampler2DArray");
    sm_key("sampler1DArrayShadow", "sampler1DArrayShadow");
    sm_key("sampler2DArrayShadow", "sampler2DArrayShadow");
    sm_key("isampler1D", "isampler1D");
    sm_key("isampler2D", "isampler2D");
    sm_key("isampler3D", "isampler3D");
    sm_key("isamplerCube", "isamplerCube");
    sm_key("isampler1DArray", "isampler1DArray");
    sm_key("isampler2DArray", "isampler2DArray");
    sm_key("usampler1D", "usampler1D");
    sm_key("usampler2D", "usampler2D");
    sm_key("usampler3D", "usampler3D");
    sm_key("usamplerCube", "usamplerCube");
    sm_key("usampler1DArray", "usampler1DArray");
    sm_key("usampler2DArray", "usampler2DArray");
    sm_key("sampler2DRect", "sampler2DRect");
    sm_key("sampler2DRectShadow", "sampler2DRectShadow");
    sm_key("isampler2DRect", "isampler2DRect");
    sm_key("usampler2DRect", "usampler2DRect");
    sm_key("samplerBuffer", "samplerBuffer");
    sm_key("isamplerBuffer", "isamplerBuffer");
    sm_key("usamplerBuffer", "usamplerBuffer");
    sm_key("sampler2DMS", "sampler2DMS");
    sm_key("isampler2DMS", "isampler2DMS");
    sm_key("usampler2DMS", "usampler2DMS");
    sm_key("sampler2DMSArray", "sampler2DMSArray");
    sm_key("isampler2DMSArray", "isampler2DMSArray");
    sm_key("usampler2DMSArray", "usampler2DMSArray");
    sm_key("samplerCubeArray", "samplerCubeArray");
    sm_key("samplerCubeArrayShadow", "samplerCubeArrayShadow");
    sm_key("isamplerCubeArray", "isamplerCubeArray");
    sm_key("usamplerCubeArray", "usamplerCubeArray");
    sm_key("struct", "struct");
    
    sm_select_base_kind(TokenBaseKind_BuiltInFunction);
    sm_key("radians", "radians");
    sm_key("degrees", "degrees");
    sm_key("sin", "sin");
    sm_key("cos", "cos");
    sm_key("tan", "tan");
    sm_key("asin", "asin");
    sm_key("acos", "acos");
    sm_key("atan", "atan");
    sm_key("pow", "pow");
    sm_key("exp", "exp");
    sm_key("log", "log");
    sm_key("exp2", "exp2");
    sm_key("log2", "log2");
    sm_key("sqrt", "sqrt");
    sm_key("inversesqrt", "inversesqrt");
    sm_key("abs", "abs");
    sm_key("sign", "sign");
    sm_key("floor", "floor");
    sm_key("ceil", "ceil");
    sm_key("fract", "fract");
    sm_key("mod", "mod");
    sm_key("min", "min");
    sm_key("max", "max");
    sm_key("clamp", "clamp");
    sm_key("mix", "mix");
    sm_key("step", "step");
    sm_key("smoothstep", "smoothstep");
    sm_key("length", "length");
    sm_key("distance", "distance");
    sm_key("dot", "dot");
    sm_key("cross", "cross");
    sm_key("normalize", "normalize");
    sm_key("faceforward", "faceforward");
    sm_key("reflect", "reflect");
    sm_key("refract", "refract");
    sm_key("matrixCompMult", "matrixCompMult");
    sm_key("lessThan", "lessThan");
    sm_key("lessThenEqual", "lessThenEqual");
    sm_key("greaterThan", "greaterThan");
    sm_key("greaterThanEqual", "greaterThanEqual");
    sm_key("equal", "equal");
    sm_key("notEqual", "notEqual");
    sm_key("any", "any");
    sm_key("all", "all");
    sm_key("not", "not");
    sm_key("dFdx", "dFdx");
    sm_key("dFdy", "dFdy");
    sm_key("fwidth", "fwidth");
    sm_key("noise1", "noise1");
    sm_key("noise2", "noise2");
    sm_key("noise3", "noise3");
    sm_key("noise4", "noise4");
    sm_key("outerProduct", "outerProduct");
    sm_key("transpose", "transpose");
    sm_key("trunc", "trunc");
    sm_key("round", "round");
    sm_key("roundEven", "roundEven");
    sm_key("modf", "modf");
    sm_key("isnan", "isnan");
    sm_key("isinf", "isinf");
    sm_key("sinh", "sinh");
    sm_key("cosh", "cosh");
    sm_key("tanh", "tanh");
    sm_key("asinh", "asinh");
    sm_key("acosh", "acosh");
    sm_key("atanh", "atanh");
    sm_key("textureSize", "textureSize");
    sm_key("texture", "texture");
    sm_key("textureProj", "textureProj");
    sm_key("textureLod", "textureLod");
    sm_key("textureOffset", "textureOffset");
    sm_key("texelFetch", "texelFetch");
    sm_key("texelFetchOffset", "texelFetchOffset");
    sm_key("textureProjOffset", "textureProjOffset");
    sm_key("textureLodOffset", "textureLodOffset");
    sm_key("textureProjLod", "textureProjLod");
    sm_key("textureProjLodOffset", "textureProjLodOffset");
    sm_key("textureGrad", "textureGrad");
    sm_key("textureGradOffset", "textureGradOffset");
    sm_key("textureProjGrad", "textureProjGrad");
    sm_key("textureProjGradOffset", "textureProjGradOffset");
    sm_key("determinant", "determinant");
    sm_key("inverse", "inverse");
    sm_key("EmitVertex", "EmitVertex");
    sm_key("EndPrimitive", "EndPrimitive");
    sm_key("packSnorm2x16", "packSnorm2x16");
    sm_key("unpackUnorm2x16", "unpackUnorm2x16");
    sm_key("packUnorm2x16", "packUnorm2x16");
    sm_key("unpackUnorm2x16", "unpackUnorm2x16");
    sm_key("packHalf2x16", "packHalf2x16");
    sm_key("unpackHalf2x16", "unpackHalf2x16");
    sm_key("floatBitsToInt", "floatBitsToInt");
    sm_key("floatBitsToUint", "floatBitsToUint");
    sm_key("intBitsToFloat", "intBitsToFloat");
    sm_key("uintBitsToFloat", "uintBitsToFloat");
    sm_key("fma", "fma");
    sm_key("barrier", "barrier");
    sm_key("interpolateAtCentroid", "interpolateAtCentroid");
    sm_key("interpolateAtSample", "interpolateAtSample");
    sm_key("interpolateAtOffset", "interpolateAtOffset");
    sm_key("frexp", "frexp");
    sm_key("ldexp", "ldexp");
    sm_key("packUnorm2x16", "packUnorm2x16");
    sm_key("packUnorm4x8", "packUnorm4x8");
    sm_key("packSnorm4x8", "packSnorm4x8");
    sm_key("unpackUnorm2x16", "unpackUnorm2x16");
    sm_key("unpackSnorm2x16", "unpackSnorm2x16");
    sm_key("unpackUnorm4x8", "unpackUnorm4x8");
    sm_key("unpackSnorm4x8", "unpackSnorm4x8");
    sm_key("packDouble2x32", "packDouble2x32");
    sm_key("unpackDouble2x32", "unpackDouble2x32");
    sm_key("uaddCarry", "uaddCarry");
    sm_key("usubBorrow", "usubBorrow");
    sm_key("umulExtended", "umulExtended");
    sm_key("imulExtended", "imulExtended");
    sm_key("bitfieldExtract", "bitfieldExtract");
    sm_key("bitfieldInsert", "bitfieldInsert");
    sm_key("bitfieldReverse", "bitfieldReverse");
    sm_key("bitCount", "bitCount");
    sm_key("findLSB", "findLSB");
    sm_key("findMSB", "findMSB");
    sm_key("textureQueryLod", "textureQueryLod");
    sm_key("textureGather", "textureGather");
    sm_key("textureGatherOffset", "textureGatherOffset");
    sm_key("textureGatherOffsets", "textureGatherOffsets");
    sm_key("EmitStreamVertex", "EmitStreamVertex");
    sm_key("EndStreamPrimitive", "EndStreamPrimitive");
    sm_key("packSnorm2x16", "packSnorm2x16");
    sm_key("unpackSnorm2x16", "unpackSnorm2x16");
    sm_key("packHalf2x16", "packHalf2x16");
    sm_key("unpackHalf2x16", "unpackHalf2x16");
    sm_key("atomicCounterIncrement", "atomicCounterIncrement");
    sm_key("atomicCounterDecrement", "atomicCounterDecrement");
    sm_key("atomicCounter", "atomicCounter");
    sm_key("memoryBarrier", "memoryBarrier");
    sm_key("imageLoad", "imageLoad");
    sm_key("imageStore", "imageStore");
    sm_key("imageAtomicAdd", "imageAtomicAdd");
    sm_key("imageAtomicMin", "imageAtomicMin");
    sm_key("imageAtomicMax", "imageAtomicMax");
    sm_key("imageAtomicAnd", "imageAtomicAnd");
    sm_key("imageAtomicOr", "imageAtomicOr");
    sm_key("imageAtomicXor", "imageAtomicXor");
    sm_key("imageAtomicExchange", "imageAtomicExchange");
    sm_key("imageAtomicCompSwap", "imageAtomicCompSwap");
    sm_key("textureQueryLevels", "textureQueryLevels");
    sm_key("atomicAdd", "atomicAdd");
    sm_key("atomicMin", "atomicMin");
    sm_key("atomicMax", "atomicMax");
    sm_key("atomicAnd", "atomicAnd");
    sm_key("atomicOr", "atomicOr");
    sm_key("atomicXor", "atomicXor");
    sm_key("atomicExchange", "atomicExchange");
    sm_key("atomicCompSwap", "atomicCompSwap");
    sm_key("imageSize", "imageSize");
    sm_key("memoryBarrierAtomicCounter", "memoryBarrierAtomicCounter");
    sm_key("memoryBarrierBuffer", "memoryBarrierBuffer");
    sm_key("memoryBarrierShared", "memoryBarrierShared");
    sm_key("memoryBarrierImage", "memoryBarrierImage");
    sm_key("groupMemoryBarrier", "groupMemoryBarrier");
    
    sm_select_base_kind(TokenBaseKind_BuiltInVariable);
    sm_key("gl_FragColor", "gl_FragColor");
    sm_key("gl_FragData", "gl_FragData");
    sm_key("gl_Position", "gl_Position");
    sm_key("gl_PointSize", "gl_PointSize");
    sm_key("gl_FragCoord", "gl_FragCoord");
    sm_key("gl_FrontFacing", "gl_FrontFacing");
    sm_key("gl_PointCoord", "gl_PointCoord");
    sm_key("gl_FragColor", "gl_FragColor");
    sm_key("gl_FragData", "gl_FragData");
    sm_key("gl_DepthRangeParameters", "gl_DepthRangeParameters");
    sm_key("gl_DepthRange", "gl_DepthRange");
    sm_key("gl_FragColor", "gl_FragColor");
    sm_key("gl_FragData", "gl_FragData");
    sm_key("gl_Vertex", "gl_Vertex");
    sm_key("gl_MultiTexCoord0", "gl_MultiTexCoord0");
    sm_key("gl_MultiTexCoord1", "gl_MultiTexCoord1");
    sm_key("gl_MultiTexCoord2", "gl_MultiTexCoord2");
    sm_key("gl_MultiTexCoord3", "gl_MultiTexCoord3");
    sm_key("gl_MultiTexCoord4", "gl_MultiTexCoord4");
    sm_key("gl_MultiTexCoord5", "gl_MultiTexCoord5");
    sm_key("gl_MultiTexCoord6", "gl_MultiTexCoord6");
    sm_key("gl_MultiTexCoord7", "gl_MultiTexCoord7");
    sm_key("gl_FogCoord", "gl_FogCoord");
    sm_key("gl_ModelViewMatrix", "gl_ModelViewMatrix");
    sm_key("gl_ProjectionMatrix", "gl_ProjectionMatrix");
    sm_key("gl_ModelViewProjectionMatrix", "gl_ModelViewProjectionMatrix");
    sm_key("gl_TextureMatrix", "gl_TextureMatrix");
    sm_key("gl_NormalMatrix", "gl_NormalMatrix");
    sm_key("gl_ModelViewMatrixInverse", "gl_ModelViewMatrixInverse");
    sm_key("gl_ProjectionMatrixInverse", "gl_ProjectionMatrixInverse");
    sm_key("gl_ModelViewProjectionMatrixInverse", "gl_ModelViewProjectionMatrixInverse");
    sm_key("gl_TextureMatrixInverse", "gl_TextureMatrixInverse");
    sm_key("gl_ModelViewMatrixTranspose", "gl_ModelViewMatrixTranspose");
    sm_key("gl_ProjectionMatrixTranspose", "gl_ProjectionMatrixTranspose");
    sm_key("gl_ModelViewProjectionMatrixTranspose", "gl_ModelViewProjectionMatrixTranspose");
    sm_key("gl_TextureMatrixTranspose", "gl_TextureMatrixTranspose");
    sm_key("gl_ModelViewMatrixInverseTranspose", "gl_ModelViewMatrixInverseTranspose");
    sm_key("gl_ProjectionMatrixInverseTranspose", "gl_ProjectionMatrixInverseTranspose");
    sm_key("gl_ModelViewProjectionMatrixInverseTranspose", "gl_ModelViewProjectionMatrixInverseTranspose");
    sm_key("gl_TextureMatrixInverseTranspose", "gl_TextureMatrixInverseTranspose");
    sm_key("gl_NormalScale", "gl_NormalScale");
    sm_key("gl_DepthRangeParameters", "gl_DepthRangeParameters");
    sm_key("gl_DepthRangeParameters", "gl_DepthRangeParameters");
    sm_key("gl_DepthRange", "gl_DepthRange");
    sm_key("gl_ClipPlane", "gl_ClipPlane");
    sm_key("gl_PointParameters", "gl_PointParameters");
    sm_key("gl_Point", "gl_Point");
    sm_key("gl_MaterialParameters", "gl_MaterialParameters");
    sm_key("gl_FrontMaterial", "gl_FrontMaterial");
    sm_key("gl_BackMaterial", "gl_BackMaterial");
    sm_key("gl_LightSourceParameters", "gl_LightSourceParameters");
    sm_key("gl_LightSourceParameters", "gl_LightSourceParameters");
    sm_key("gl_LightSource", "gl_LightSource");
    sm_key("gl_LightModelParameters", "gl_LightModelParameters");
    sm_key("gl_LightModel", "gl_LightModel");
    sm_key("gl_LightModelProducts", "gl_LightModelProducts");
    sm_key("gl_FrontLightModelProduct", "gl_FrontLightModelProduct");
    sm_key("gl_LightModelProducts", "gl_LightModelProducts");
    sm_key("gl_BackLightModelProduct", "gl_BackLightModelProduct");
    sm_key("gl_LightProducts", "gl_LightProducts");
    sm_key("gl_FrontLightProduct", "gl_FrontLightProduct");
    sm_key("gl_LightProducts", "gl_LightProducts");
    sm_key("gl_BackLightProduct", "gl_BackLightProduct");
    sm_key("gl_TextureEnvColor", "gl_TextureEnvColor");
    sm_key("gl_EyePlaneS", "gl_EyePlaneS");
    sm_key("gl_EyePlaneT", "gl_EyePlaneT");
    sm_key("gl_EyePlaneR", "gl_EyePlaneR");
    sm_key("gl_EyePlaneQ", "gl_EyePlaneQ");
    sm_key("gl_ObjectPlaneS", "gl_ObjectPlaneS");
    sm_key("gl_ObjectPlaneT", "gl_ObjectPlaneT");
    sm_key("gl_ObjectPlaneR", "gl_ObjectPlaneR");
    sm_key("gl_ObjectPlaneQ", "gl_ObjectPlaneQ");
    sm_key("gl_FogParameters", "gl_FogParameters");
    sm_key("gl_FrontColor", "gl_FrontColor");
    sm_key("gl_BackColor", "gl_BackColor");
    sm_key("gl_FrontSecondaryColor", "gl_FrontSecondaryColor");
    sm_key("gl_BackSecondaryColor", "gl_BackSecondaryColor");
    sm_key("gl_TexCoord", "gl_TexCoord");
    sm_key("gl_Color", "gl_Color");
    sm_key("gl_SecondaryColor", "gl_SecondaryColor");
    sm_key("gl_TexCoord", "gl_TexCoord");
    sm_key("gl_Position", "gl_Position");
    sm_key("gl_PointSize", "gl_PointSize");
    sm_key("gl_ClipDistance", "gl_ClipDistance");
    sm_key("gl_VertexID", "gl_VertexID");
    sm_key("gl_FragCoord", "gl_FragCoord");
    sm_key("gl_FragDepth", "gl_FragDepth");
    sm_key("gl_FrontFacing", "gl_FrontFacing");
    sm_key("gl_PointCoord", "gl_PointCoord");
    sm_key("gl_InstanceID", "gl_InstanceID");
    sm_key("gl_in", "gl_in");
    sm_key("gl_PrimitiveIDIn", "gl_PrimitiveIDIn");
    sm_key("gl_InvocationID", "gl_InvocationID");
    sm_key("gl_PrimitiveID", "gl_PrimitiveID");
    sm_key("gl_Layer", "gl_Layer");
    sm_key("gl_PerVertex", "gl_PerVertex");
    sm_key("gl_MaxPatchVertices", "gl_MaxPatchVertices");
    sm_key("gl_PatchVerticesIn", "gl_PatchVerticesIn");
    sm_key("gl_out", "gl_out");
    sm_key("gl_TessLevelOuter", "gl_TessLevelOuter");
    sm_key("gl_TessLevelInner", "gl_TessLevelInner");
    sm_key("gl_TessCoord", "gl_TessCoord");
    sm_key("gl_SampleID", "gl_SampleID");
    sm_key("gl_SamplePosition", "gl_SamplePosition");
    sm_key("gl_SampleMaskIn", "gl_SampleMaskIn");
    sm_key("gl_SampleMask", "gl_SampleMask");
    sm_key("gl_ViewportIndex", "gl_ViewportIndex");
    sm_key("gl_NumWorkGroups", "gl_NumWorkGroups");
    sm_key("gl_WorkGroupSize", "gl_WorkGroupSize");
    sm_key("gl_WorkGroupID", "gl_WorkGroupID");
    sm_key("gl_LocalInvocationID", "gl_LocalInvocationID");
    sm_key("gl_GlobalInvocationID", "gl_GlobalInvocationID");
    sm_key("gl_LocalInvocationIndex", "gl_LocalInvocationIndex");
    
    sm_select_base_kind(TokenBaseKind_BuiltInConstant);
    
    sm_key("gl_MaxVertexAttribs", "gl_MaxVertexAttribs");
    sm_key("gl_MaxVertexUniformVectors", "gl_MaxVertexUniformVectors");
    sm_key("gl_MaxVaryingVector", "gl_MaxVaryingVector");
    sm_key("gl_MaxVertexTextureImageUnits", "gl_MaxVertexTextureImageUnits");
    sm_key("gl_MaxCombinedTextureImageUnits", "gl_MaxCombinedTextureImageUnits");
    sm_key("gl_MaxTextureImageUnits", "gl_MaxTextureImageUnits");
    sm_key("gl_MaxFragmentUniformVectors", "gl_MaxFragmentUniformVectors");
    sm_key("gl_MaxDrawBuffers", "gl_MaxDrawBuffers");
    sm_key("gl_DepthRangeParameters", "gl_DepthRangeParameters");
    sm_key("gl_DepthRange", "gl_DepthRange");
    sm_key("gl_NumSamples", "gl_NumSamples");
    sm_key("gl_MaxLights", "gl_MaxLights");
    sm_key("gl_MaxClipPlanes", "gl_MaxClipPlanes");
    sm_key("gl_MaxTextureUnits", "gl_MaxTextureUnits");
    sm_key("gl_MaxTextureCoords", "gl_MaxTextureCoords");
    sm_key("gl_MaxVertexAttribs", "gl_MaxVertexAttribs");
    sm_key("gl_MaxVertexUniformComponents", "gl_MaxVertexUniformComponents");
    sm_key("gl_MaxVaryingFloats", "gl_MaxVaryingFloats");
    sm_key("gl_MaxVertexTextureImageUnits", "gl_MaxVertexTextureImageUnits");
    sm_key("gl_MaxCombinedTextureImageUnits", "gl_MaxCombinedTextureImageUnits");
    sm_key("gl_MaxTextureImageUnits", "gl_MaxTextureImageUnits");
    sm_key("gl_MaxFragmentUniformComponents", "gl_MaxFragmentUniformComponents");
    sm_key("gl_MaxDrawBuffers", "gl_MaxDrawBuffers");
    sm_key("gl_DepthRangeParameters", "gl_DepthRangeParameters");
    sm_key("gl_DepthRange", "gl_DepthRange");
    sm_key("gl_NumSamples", "gl_NumSamples");
    sm_key("gl_MaxVaryingComponents", "gl_MaxVaryingComponents");
    sm_key("gl_MaxClipDistances", "gl_MaxClipDistances");
    sm_key("gl_MaxVertexOutputComponents", "gl_MaxVertexOutputComponents");
    sm_key("gl_MaxGeometryInputComponents", "gl_MaxGeometryInputComponents");
    sm_key("gl_MaxGeometryOutputComponents", "gl_MaxGeometryOutputComponents");
    sm_key("gl_MaxFragmentInputComponents", "gl_MaxFragmentInputComponents");
    sm_key("gl_MaxGeometryTextureImageUnits", "gl_MaxGeometryTextureImageUnits");
    sm_key("gl_MaxGeometryOutputVertices", "gl_MaxGeometryOutputVertices");
    sm_key("gl_MaxGeometryTotalOutputComponents", "gl_MaxGeometryTotalOutputComponents");
    sm_key("gl_MaxGeometryUniformComponents", "gl_MaxGeometryUniformComponents");
    sm_key("gl_MaxGeometryVaryingComponents", "gl_MaxGeometryVaryingComponents");
    sm_key("gl_MaxVertexAttribs", "gl_MaxVertexAttribs");
    sm_key("gl_MaxVertexUniformVectors", "gl_MaxVertexUniformVectors");
    sm_key("gl_MaxVertexOutputVectors", "gl_MaxVertexOutputVectors");
    sm_key("gl_MaxFragmentInputVectors", "gl_MaxFragmentInputVectors");
    sm_key("gl_MaxVertexTextureImageUnits", "gl_MaxVertexTextureImageUnits");
    sm_key("gl_MaxCombinedTextureImageUnits", "gl_MaxCombinedTextureImageUnits");
    sm_key("gl_MaxTextureImageUnits", "gl_MaxTextureImageUnits");
    sm_key("gl_MaxFragmentUniformVectors", "gl_MaxFragmentUniformVectors");
    sm_key("gl_MaxDrawBuffers", "gl_MaxDrawBuffers");
    sm_key("gl_MinProgramTexelOffset", "gl_MinProgramTexelOffset");
    sm_key("gl_MaxProgramTexelOffset", "gl_MaxProgramTexelOffset");
    sm_key("gl_DepthRangeParameters", "gl_DepthRangeParameters");
    sm_key("gl_DepthRange", "gl_DepthRange");
    sm_key("gl_NumSamples", "gl_NumSamples");
    sm_key("gl_MaxTessControlInputComponents", "gl_MaxTessControlInputComponents");
    sm_key("gl_MaxTessControlOutputComponents", "gl_MaxTessControlOutputComponents");
    sm_key("gl_MaxTessControlTextureImageUnits", "gl_MaxTessControlTextureImageUnits");
    sm_key("gl_MaxTessControlUniformComponents", "gl_MaxTessControlUniformComponents");
    sm_key("gl_MaxTessControlTotalOutputComponents", "gl_MaxTessControlTotalOutputComponents");
    sm_key("gl_MaxTessEvaluationInputComponents", "gl_MaxTessEvaluationInputComponents");
    sm_key("gl_MaxTessEvaluationOutputComponents", "gl_MaxTessEvaluationOutputComponents");
    sm_key("gl_MaxTessEvaluationTextureImageUnits", "gl_MaxTessEvaluationTextureImageUnits");
    sm_key("gl_MaxTessEvaluationUniformComponents", "gl_MaxTessEvaluationUniformComponents");
    sm_key("gl_MaxTessPatchComponents", "gl_MaxTessPatchComponents");
    sm_key("gl_MaxPatchVertices", "gl_MaxPatchVertices");
    sm_key("gl_MaxTessGenLevel", "gl_MaxTessGenLevel");
    sm_key("gl_MaxViewports", "gl_MaxViewports");
    sm_key("gl_MaxVertexUniformVectors", "gl_MaxVertexUniformVectors");
    sm_key("gl_MaxFragmentUniformVectors", "gl_MaxFragmentUniformVectors");
    sm_key("gl_MaxVaryingVectors", "gl_MaxVaryingVectors");
    sm_key("gl_MaxImageUnits", "gl_MaxImageUnits");
    sm_key("gl_MaxCombinedImageUnitsAndFragmentOutputs", "gl_MaxCombinedImageUnitsAndFragmentOutputs");
    sm_key("gl_MaxImageSamples", "gl_MaxImageSamples");
    sm_key("gl_MaxVertexImageUniforms", "gl_MaxVertexImageUniforms");
    sm_key("gl_MaxTessControlImageUniforms", "gl_MaxTessControlImageUniforms");
    sm_key("gl_MaxTessEvaluationImageUniforms", "gl_MaxTessEvaluationImageUniforms");
    sm_key("gl_MaxGeometryImageUniforms", "gl_MaxGeometryImageUniforms");
    sm_key("gl_MaxFragmentImageUniforms", "gl_MaxFragmentImageUniforms");
    sm_key("gl_MaxCombinedImageUniforms", "gl_MaxCombinedImageUniforms");
    sm_key("gl_MaxVertexAtomicCounters", "gl_MaxVertexAtomicCounters");
    sm_key("gl_MaxTessControlAtomicCounters", "gl_MaxTessControlAtomicCounters");
    sm_key("gl_MaxTessEvaluationAtomicCounters", "gl_MaxTessEvaluationAtomicCounters");
    sm_key("gl_MaxGeometryAtomicCounters", "gl_MaxGeometryAtomicCounters");
    sm_key("gl_MaxFragmentAtomicCounters", "gl_MaxFragmentAtomicCounters");
    sm_key("gl_MaxCombinedAtomicCounters", "gl_MaxCombinedAtomicCounters");
    sm_key("gl_MaxAtomicCounterBindings", "gl_MaxAtomicCounterBindings");
    sm_key("gl_MaxVertexAtomicCounterBuffers", "gl_MaxVertexAtomicCounterBuffers");
    sm_key("gl_MaxTessControlAtomicCounterBuffers", "gl_MaxTessControlAtomicCounterBuffers");
    sm_key("gl_MaxTessEvaluationAtomicCounterBuffers", "gl_MaxTessEvaluationAtomicCounterBuffers");
    sm_key("gl_MaxGeometryAtomicCounterBuffers", "gl_MaxGeometryAtomicCounterBuffers");
    sm_key("gl_MaxFragmentAtomicCounterBuffers", "gl_MaxFragmentAtomicCounterBuffers");
    sm_key("gl_MaxCombinedAtomicCounterBuffers", "gl_MaxCombinedAtomicCounterBuffers");
    sm_key("gl_MaxAtomicCounterBufferSize", "gl_MaxAtomicCounterBufferSize");
    sm_key("gl_MinProgramTexelOffset", "gl_MinProgramTexelOffset");
    sm_key("gl_MaxProgramTexelOffset", "gl_MaxProgramTexelOffset");
    sm_key("gl_MaxComputeWorkGroupCount", "gl_MaxComputeWorkGroupCount");
    sm_key("gl_MaxComputeWorkGroupSize", "gl_MaxComputeWorkGroupSize");
    sm_key("gl_MaxComputeUniformComponents", "gl_MaxComputeUniformComponents");
    sm_key("gl_MaxComputeTextureImageUnits", "gl_MaxComputeTextureImageUnits");
    sm_key("gl_MaxComputeImageUniforms", "gl_MaxComputeImageUniforms");
    sm_key("gl_MaxComputeAtomicCounters", "gl_MaxComputeAtomicCounters");
    sm_key("gl_MaxComputeAtomicCounterBuffers", "gl_MaxComputeAtomicCounterBuffers");
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_key("LiteralTrue", "true");
    sm_key("LiteralFalse", "false");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key_fallback("Identifier");
    
    // CPP Preprocess Directives
    Keyword_Set *pp_directive_set = sm_begin_key_set("pp_directives");
    
    sm_select_base_kind(TokenBaseKind_Preprocessor);
    sm_key("PPDefine",    "define");
    sm_key("PPUndef",     "undef");
    sm_key("PPIf",        "if");
    sm_key("PPIfDef",     "ifdef");
    sm_key("PPIfNDef",    "ifndef");
    sm_key("PPElse",      "else");
    sm_key("PPElIf",      "elif");
    sm_key("PPEndIf",     "endif");
    sm_key("PPError",     "error");
    sm_key("PPPragma",    "pragma");
    sm_key("PPExtension", "extension");
    sm_key("PPVersion",   "version");
    sm_key("PPLine",      "line");
    
    // NOTE(Tyler): Custom ones for a combined glsl
    sm_key("PPVertexShader", "vertex_shader");
    sm_key("PPPixelShader",  "pixel_shader");
    
    sm_select_base_kind(TokenBaseKind_LexError);
    sm_key_fallback("PPUnknown");
    
    // CPP Preprocess Keywords
    Keyword_Set *pp_keys = sm_begin_key_set("pp_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_key("PPDefined", "defined");
    
    // State Machine
    State *root = sm_begin_state_machine();
    
    Flag *is_hex = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_oct = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_wide  = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_utf8  = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_utf16 = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_utf32 = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_char  = sm_add_flag(FlagResetRule_AutoZero);
    
    Flag *is_pp_body      = sm_add_flag(FlagResetRule_KeepState);
    Flag *is_error_body   = sm_add_flag(FlagResetRule_KeepState);
    Flag *is_version_body = sm_add_flag(FlagResetRule_KeepState);
    
    sm_flag_bind(is_pp_body, TokenBaseFlag_PreprocessorBody);
    
#define AddState(N) State *N = sm_add_state(#N)
    
    AddState(identifier);
    AddState(whitespace);
    AddState(whitespace_end_pp);
    AddState(error_body);
    AddState(version_body);
    AddState(backslash);
    
    AddState(operator_or_fnumber_dot);
    AddState(operator_or_comment_slash);
    
    AddState(number);
    AddState(znumber);
    
    AddState(fnumber_decimal);
    AddState(fnumber_exponent);
    AddState(fnumber_exponent_sign);
    AddState(fnumber_exponent_digits);
    
    AddState(number_hex_first);
    AddState(number_hex);
    AddState(number_oct);
    
    AddState(U_number);
    AddState(L_number);
    AddState(UL_number);
    AddState(LU_number);
    AddState(l_number);
    AddState(Ul_number);
    AddState(lU_number);
    AddState(LL_number);
    AddState(ULL_number);
    
    AddState(pp_directive_whitespace);
    AddState(pp_directive_first);
    AddState(pp_directive);
    AddState(pp_directive_emit);
    
    AddState(pre_L);
    AddState(pre_u);
    AddState(pre_U);
    AddState(pre_u8);
    AddState(pre_R);
    
    AddState(character);
    AddState(string);
    AddState(string_esc);
    AddState(string_esc_oct2);
    AddState(string_esc_oct1);
    AddState(string_esc_hex);
    AddState(string_esc_universal_8);
    AddState(string_esc_universal_7);
    AddState(string_esc_universal_6);
    AddState(string_esc_universal_5);
    AddState(string_esc_universal_4);
    AddState(string_esc_universal_3);
    AddState(string_esc_universal_2);
    AddState(string_esc_universal_1);
    
    AddState(raw_string);
    AddState(raw_string_get_delim);
    AddState(raw_string_finish_delim);
    AddState(raw_string_find_close);
    AddState(raw_string_try_delim);
    AddState(raw_string_try_quote);
    
    AddState(comment_block);
    AddState(comment_block_try_close);
    AddState(comment_block_newline);
    AddState(comment_line);
    AddState(comment_line_backslashing);
    
    Operator_Set *main_ops_without_dot_or_slash = smo_copy_op_set(main_ops);
    smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, ".");
    smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, "/");
    
    Operator_Set *main_ops_with_dot = smo_copy_op_set(main_ops);
    smo_remove_ops_without_prefix(main_ops_with_dot, ".");
    smo_ops_string_skip(main_ops_with_dot, 1);
    
    ////
    
    sm_select_state(root);
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("EOF");
        sm_case_eof(emit);
    }
    
    sm_case("abcdefghijklmnopqrstvwxyz"
            "ABCDEFGHIJKMNOPQSTVWXYZ"
            "_$",
            identifier);
    sm_case(utf8, identifier);
    sm_case("L", pre_L);
    sm_case("u", pre_u);
    sm_case("U", pre_U);
    sm_case("R", pre_R);
    
    sm_case_flagged(is_error_body,   true, " \r\t\f\v", error_body);
    sm_case_flagged(is_version_body, true, " \r\t\f\v", version_body);
    sm_case_flagged(is_error_body,  false, " \r\t\f\v", whitespace);
    sm_case("\n", whitespace_end_pp);
    sm_case("\\", backslash);
    
    sm_case(".", operator_or_fnumber_dot);
    sm_case("/", operator_or_comment_slash);
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops_without_dot_or_slash);
        smo_char_set_remove(char_set, "./");
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops_without_dot_or_slash, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
    }
    
    sm_case("123456789", number);
    sm_case("0", znumber);
    
    sm_case("\'", character);
    sm_case_flagged(is_pp_body, false, "#", pp_directive_whitespace);
    {
        State *operator_state = smo_op_set_lexer_root(pp_ops, root, "LexError");
        sm_case_peek_flagged(is_pp_body, true, "#", operator_state);
    }
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback(emit);
    }
    
    ////
    
    sm_select_state(identifier);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_$"
            "0123456789",
            identifier);
    sm_case(utf8, identifier);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(is_pp_body, pp_keys);
        sm_emit_handler_keys(main_keys);
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(whitespace);
    sm_case(" \t\r\f\v", whitespace);
    sm_case("\n", whitespace_end_pp);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Whitespace");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(whitespace_end_pp);
    sm_set_flag(is_pp_body, false);
    sm_set_flag(is_error_body, false);
    sm_set_flag(is_version_body, false);
    sm_fallback_peek(whitespace);
    
    ////
    
    sm_select_state(error_body);
    sm_case("\r", error_body);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("PPErrorMessage");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("PPErrorMessage");
        sm_case_eof_peek(emit);
    }
    sm_fallback(error_body);
    
    ////
    
    sm_select_state(version_body);
    sm_case("\r", version_body);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("PPVersionMessage");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("PPVersionMessage");
        sm_case_eof_peek(emit);
    }
    sm_fallback(version_body);
    
    ////
    
    sm_select_state(backslash);
    sm_case("\r", backslash);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Backslash");
        sm_case("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Backslash");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(operator_or_comment_slash);
    sm_case("*", comment_block);
    sm_case("/", comment_line);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("DivEq");
        sm_case("=", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Div");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(operator_or_fnumber_dot);
    sm_case("0123456789", fnumber_decimal);
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops_with_dot);
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops_with_dot, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Dot");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number);
    sm_case("0123456789", number);
    sm_case(".", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    sm_case("Uu", U_number);
    sm_case("L", L_number);
    sm_case("l", l_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(znumber);
    sm_case(".", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    sm_case("Uu", U_number);
    sm_case("L", L_number);
    sm_case("l", l_number);
    sm_case("Xx", number_hex_first);
    sm_case("01234567", number_oct);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_decimal);
    sm_case("0123456789", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent);
    sm_case("+-", fnumber_exponent_sign);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent_sign);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent_digits);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat32");
        sm_case("Ff", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_hex_first);
    sm_set_flag(is_hex, true);
    sm_case("0123456789abcdefABCDEF", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_hex);
    sm_case("0123456789abcdefABCDEF", number_hex);
    sm_case("Uu", U_number);
    sm_case("L", L_number);
    sm_case("l", l_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerHex");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_oct);
    sm_set_flag(is_oct, true);
    sm_case("01234567", number_oct);
    sm_case("Uu", U_number);
    sm_case("L", L_number);
    sm_case("l", l_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerOct");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(U_number);
    sm_case("L", UL_number);
    sm_case("l", Ul_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexU");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctU");
        sm_emit_handler_direct("LiteralIntegerU");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(L_number);
    sm_case("L", LL_number);
    sm_case("Uu", LU_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctL");
        sm_emit_handler_direct("LiteralIntegerL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(l_number);
    sm_case("l", LL_number);
    sm_case("Uu", lU_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctL");
        sm_emit_handler_direct("LiteralIntegerL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(LL_number);
    sm_case("Uu", ULL_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexLL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctLL");
        sm_emit_handler_direct("LiteralIntegerLL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(UL_number);
    sm_case("L", ULL_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        sm_emit_handler_direct("LiteralIntegerUL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(Ul_number);
    sm_case("l", ULL_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        sm_emit_handler_direct("LiteralIntegerUL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(LU_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        sm_emit_handler_direct("LiteralIntegerUL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(lU_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        sm_emit_handler_direct("LiteralIntegerUL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(ULL_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_hex, "LiteralIntegerHexULL");
        sm_emit_handler_direct(is_oct, "LiteralIntegerOctULL");
        sm_emit_handler_direct("LiteralIntegerULL");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(pp_directive_whitespace);
    sm_case(" \t\f\v", pp_directive_whitespace);
    sm_case_peek("abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "_"
                 "0123456789",
                 pp_directive_first);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(pp_directive_first);
    sm_delim_mark_first();
    sm_set_flag(is_pp_body, true);
    sm_fallback_peek(pp_directive);
    
    ////
    
    sm_select_state(pp_directive);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_"
            "0123456789",
            pp_directive);
    sm_fallback_peek(pp_directive_emit);
    
    ////
    
    sm_select_state(pp_directive_emit);
    sm_delim_mark_one_past_last();
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_check_set_flag("PPError",  is_error_body, true);
        sm_emit_check_set_flag("PPVersion", is_version_body, true);
        sm_emit_handler_keys_delim(pp_directive_set);
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(pre_L);
    sm_set_flag(is_wide, true);
    sm_case("\"", string);
    sm_case("R", pre_R);
    sm_fallback_peek(identifier);
    
    ////
    
    sm_select_state(pre_u);
    sm_set_flag(is_utf16, true);
    sm_case("\"", string);
    sm_case("8", pre_u8);
    sm_case("R", pre_R);
    sm_fallback_peek(identifier);
    
    ////
    
    sm_select_state(pre_U);
    sm_set_flag(is_utf32, true);
    sm_case("\"", string);
    sm_case("R", pre_R);
    sm_fallback_peek(identifier);
    
    ////
    
    sm_select_state(pre_u8);
    sm_set_flag(is_utf8, true);
    sm_case("\"", string);
    sm_case("R", pre_R);
    sm_fallback_peek(identifier);
    
    ////
    
    sm_select_state(pre_R);
    sm_case("\"", raw_string);
    sm_fallback_peek(identifier);
    
    ////
    
    sm_select_state(character);
    sm_set_flag(is_char, true);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_wide, "LiteralStringWide");
        sm_emit_handler_direct(is_utf8 , "LiteralStringUTF8");
        sm_emit_handler_direct(is_utf16, "LiteralStringUTF16");
        sm_emit_handler_direct(is_utf32, "LiteralStringUTF32");
        sm_emit_handler_direct("LiteralString");
        sm_case_flagged(is_char, false, "\"", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_wide, "LiteralCharacterWide");
        sm_emit_handler_direct(is_utf8 , "LiteralCharacterUTF8");
        sm_emit_handler_direct(is_utf16, "LiteralCharacterUTF16");
        sm_emit_handler_direct(is_utf32, "LiteralCharacterUTF32");
        sm_emit_handler_direct("LiteralCharacter");
        sm_case_flagged(is_char, true, "\'", emit);
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
    sm_case_flagged(is_char, true, "\"", string);
    sm_case_flagged(is_char, false, "\'", string);
    sm_fallback(string);
    
    ////
    
    sm_select_state(string_esc);
    sm_case("\n'\"?\\abfnrtv", string);
    sm_case("01234567", string_esc_oct2);
    sm_case("x", string_esc_hex);
    sm_case("u", string_esc_universal_4);
    sm_case("U", string_esc_universal_8);
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
    
    ////
    
    sm_select_state(string_esc_oct2);
    sm_case("01234567", string_esc_oct1);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_oct1);
    sm_case("01234567", string);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_hex);
    sm_case("0123456789abcdefABCDEF", string_esc_hex);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_8);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_7);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_7);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_6);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_6);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_5);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_5);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_4);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_4);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_3);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_3);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_2);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_2);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_1);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_1);
    sm_case("0123456789abcdefABCDEF", string);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(raw_string);
    sm_delim_mark_first();
    sm_fallback_peek(raw_string_get_delim);
    
    ////
    
    sm_select_state(raw_string_get_delim);
    sm_case_peek("(", raw_string_finish_delim);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case(" \\)", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(raw_string_get_delim);
    
    ////
    
    sm_select_state(raw_string_finish_delim);
    sm_delim_mark_one_past_last();
    sm_fallback_peek(raw_string_find_close);
    
    ////
    
    sm_select_state(raw_string_find_close);
    sm_case(")", raw_string_try_delim);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(raw_string_find_close);
    
    ////
    
    sm_select_state(raw_string_try_delim);
    sm_match_delim(raw_string_try_quote, raw_string_find_close);
    
    ////
    
    sm_select_state(raw_string_try_quote);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct(is_wide, "LiteralStringWideRaw");
        sm_emit_handler_direct(is_utf8 , "LiteralStringUTF8Raw");
        sm_emit_handler_direct(is_utf16, "LiteralStringUTF16Raw");
        sm_emit_handler_direct(is_utf32, "LiteralStringUTF32Raw");
        sm_emit_handler_direct("LiteralStringRaw");
        sm_case("\"", emit);
    }
    sm_fallback_peek(raw_string_find_close);
    
    ////
    
    sm_select_state(comment_block);
    sm_case("*", comment_block_try_close);
    sm_case("\n", comment_block_newline);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("BlockComment");
        sm_case_eof_peek(emit);
    }
    sm_fallback(comment_block);
    
    ////
    
    sm_select_state(comment_block_try_close);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("BlockComment");
        sm_case("/", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("BlockComment");
        sm_case_eof_peek(emit);
    }
    sm_case("*", comment_block_try_close);
    sm_fallback(comment_block);
    
    ////
    
    sm_select_state(comment_block_newline);
    sm_set_flag(is_pp_body, false);
    sm_fallback_peek(comment_block);
    
    ////
    
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
    sm_case("\\", comment_line_backslashing);
    sm_fallback(comment_line);
    
    sm_select_state(comment_line_backslashing);
    sm_case("\r", comment_line_backslashing);
    sm_fallback(comment_line);
}

// BOTTOM

