Hello World #1
Author: K4R (besporyadok)

----------------
|I| What is it?
----------------
My hello world (round one) for probe programming on C++ and 
WinAPI, Direct3D. This program draw into display
simple 3D box and lighting his, screenshot implementation. 
Additional present debug functional (logging, asserts), experimental 
class for string's work, experimental file reader for binary files in 
EA IFF format.

-----------------------
|II| How build this?
-----------------------
Generally this program build without installed Visual Studio or 
Windows SDK and Directx SDK.

Requirements:
- Windows SDK 7.1 or Visual Studio 2013
- DirectX SDK June 2010

NOTE:
Your compiler directory must satisfy several requirements:
1) Binaries (compiler, linker, pdbserver) placed in '<YOUR_COMPILER_DIR>\Bin'.
2) Include files placed in '<YOUR_COMPILER_DIR>\Inc'
2.1) 'Inc\sal' - Source Annotations Language headers
2.2) 'Inc\crt' - C Run-Time library headers
2.3) 'Inc\stl' - C++ Standart Template Library headers
2.4) 'Inc\nt' -  Native API headers
2.5) 'Inc\w32' - Windows API headers
2.6) 'Inc\d3d' - DirectX headers.
3) Library files placed in '<YOUR_COMPILER_DIR>\Lib'.
4) '<YOUR_COMPILER_DIR>\Docs' various documentation
4.1) Compiler.txt - Compiler documentation
4.2) Linker.txt - Linker documentation
4.3) Dump.txt - DumpBin documentation
4.4) Resource.txt - Resource compiler documentation
4.5) Manifest.txt - Manifest compiler documentation
4.6) Make.txt - NMake documentation
4.7) windows_graphics.chm - DirectX documentation extracted from DX SDK
Or edit variables 'INC' and 'LNKFLAGS' in 'Makefil0' file.
Or install Visual Studio (Windows SDK) and DirectX SDK and configure need's 
global variables in your system.

NOTE:
For generated debug information in PDB format previosly define global variable
'DBG' in '1' value.

With Windows SDK:
1) Go to 'Build.bat' script and change '<YOUR_COMPILER_DIR>' in 
'TOOL' variable on your compiler directory from Windows SDK.
2) Run 'Build.bat' without paremeters.
3) Build result printed in 'Build.log' file. 

NOTE:
For cleanup execute 'Build.bat' with 'clean' parameter.

With Visual Studio:
Variant One:

1) Create solution and add C++ Win32 App project in created solution
2) Add in created project *.cpp & *.h files 
3) Configure include and libraries directory for DirectX SDK in project
settings page
4) Execute Build->Build...

Varian two:
1) Create Makefile project from existing source files
3) Configure include and libraries directory for DirectX SDK in project
settings page
4) Execute Build->Build...

------------------
|III| Source tree
------------------
EP.cpp - Entry point this program, create instance main application class.
Engine.cpp - Implementation main application class (create main 
window, work with DirectX, handling input, message cycle).
Engine_msg.cpp - Implementation application message cycle.
Reader.cpp - Implementation experimental IFF binary files reader.
Lab.cpp - Implementation test's for reader and string classes.
Str.h - Implementation experimental string class.