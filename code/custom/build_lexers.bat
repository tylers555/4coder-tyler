REM @echo off
call .\bin\build_one_time .\languages\4coder_sja_lexer_gen.cpp .\generated\one_time
.\generated\one_time\one_time.exe 

call .\bin\build_one_time .\languages\4coder_batch_lexer_gen.cpp .\generated\one_time
.\generated\one_time\one_time.exe 

call .\bin\build_one_time .\languages\4coder_glsl_lexer_gen.cpp .\generated\one_time
.\generated\one_time\one_time.exe 
