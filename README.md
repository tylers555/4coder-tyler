# 4coder-tyler

This fork of the 4coder code base contains some bug fixes, as well as the code for my customizaiton layer. 
This repository also contains 4coder-non-source, which was originally needed to build the program. 
As such, this would be the only repository needed to be downloaded in order to be built.

## Customization Layer
The customization layer is based upon [Ryan Fleury's custom layer](https://github.com/Dion-Systems/4coder_fleury)

- Contains multiple languages. Some languages introduce additional syntax highlighting, and use the code index.
    - C/C++, this also includes syntax highlighing for similar languages. From 4coder_fleury.
    - Metadesk, Ryan Fleury's language for metaprogramming. From 4coder_fleury.
    - JAI, Jonathan Blow's new programming language. From 4coder_fleury.
    - GLSL, this includes syntax highlighting for keywords, as well as uniform ins and outs.
    - SJA, my own custom format for defining assets
    - Batch, batch files are now syntax highlighted
- The lister for searching the code index now has color depending on the code index note. The entire line is now also displayed for each note.
- The lister now only updates and renders the visible items, this is a significant performance gain for very large code bases.
- Different modes for listing, based on file type, current file, and only definitions(useful).
- Text fade in and out for copy/paste/ctrl+delete

## Bug Fixes
- Fixed copy/paste bug

## Build Instructions
The build currently is only configured for Windows.  These instructions will end up building both the customization layer and the core layer. It is also configured to use 4coder_fleury. Debug builds are fine for testing, but do not perform near well enough for large code bases (like this one).

1. Download/clone the repository.
2. On windows setup the visual studio command line magic sauce so that "cl" works
3. There are two modes for building:
   - On windows run "bin\build.bat" this will make an unoptimized build
   - On Windows run "bin\build_optimized.bat" this will make an optimized build

## Future Plans
1. Remove the differentiation between 4coder_fleury and original/default 4coder customization layer.
    - Remove significant amounts of duplicated code!!!
2. Simplify and remove/rework several features for simplification
3. Simplify and robustify the build system for both the core and customization layers.
    - Linux and Mac build configurations, perhaps?
4. Customization layer - Support other languages with different auto indentation rules.
5. Perhaps merge the core and customization layers into one codebase? 
    - Now that 4coder is open sourced, there should be no problem or downside for doing so. This will also help significantly to simplify the build systems and codebase.
6. Perhaps remove the number of files and directories needed to run/install 4coder? - Low priority.

## Notes on Major Issues

1. The build system and organization of files is extremely complicated. There is a 4ed_build.cpp that defines how builds run, and the build scripts have to build and run this C++ file. The file is pretty chaotic since it cannot rely on the codebase's usual helpers. On top of that there is a totally separate build system for the custom layer which is also a big gigantic mess of its own. It involves several stages of compilation, and a number of metaprograms.

2. The documentation system is over complicated & the documentation is incomplete. There is very little documentation for the internals or the complicated layers of helpers.

3. The lexer generator is way too complicated, and the built-in support for language features is not fully developed. The background threaded parsing is not very carefully organized and is not very flexible, so it's hard to add new languages at any level of the system.
    - This is somewhat made easier by Ryan Fleury's language parsing code in the customization layer.

4. There are a few layers of overcomplicated configuration parsers.

5. Mac and Linux are not being tested or supported in this build. Although, they should be able to build if configured properly, however those bugs likely won't be fixed.

6. The codebase has a very weak base layer with key features that were added very late, so lots of code was written in the absence of useful features to bind things together. To make matters worse the base layer is split by the distinction of custom layer & core layer, leading to some double definitions and some incosistencies.

## Credits (from Allen Webster)
This codebase was authored by Allen Webster from 2014-2022, with help from a number of contributors:

Casey Muratori
"insofaras" Alex Baines
Yuval Dolev
Ryan Fleury

Also thanks to all those who supported the project, financially and/or through all your detailed feedback.

## License (from Allen Webster)

Copyright (c) 2022 Allen Webster

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


