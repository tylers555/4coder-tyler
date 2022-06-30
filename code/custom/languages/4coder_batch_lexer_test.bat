
set location=%cd%
set me=%~dp0
cd %me%
cd ..
set custom_root=%cd%
set custom_bin=%custom_root%\bin
cd %location%

 if NOT "%Platform%" == "X64" IF NOT "%Platform%" == "x64" (call "%custom_bin%\setup_cl_x64.bat")

set target=%1
if "%target%" == "" set target=%custom_root%\4coder_default_bindings.cpp

set debug=/Zi
set release=/O2 /Zi
set mode=%debug%
if "%2" == "release" (set mode=%release%)

set binname=%3
if "%binname%" == "" set binname="custom_4coder"
