@echo off

@setlocal
@set TL=%~dp0tools
@set PATH=%TL%\dd\Bin;%PATH%
@set INCLUDE=%TL%\dd\Inc\sal;%TL%\dd\Inc\crt;%TL%\dd\Inc\stl;%TL%\dd\Inc\w32;%TL%\dd\Inc\mfc;%TL%\dd\Inc\d3d
@set LIB=%TL%\dd\Lib

@set TARGET=all

@if /I "%1" EQU "/g" goto gen
@if /I "%1" EQU "/b" goto build
@if /I "%1" EQU "/i" goto install
goto usage

:gen
%TL%\kw\bin\cmake -S Src -B Build -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Mixed
goto :eof

:build
shift
@if /I "%1" NEQ "" set TARGET=%1
cd Build
nmake /nologo %TARGET%
goto :eof

:install
shift
@copy /Y Build\Bin\*.exe Game\Bin\*.exe
@copy /Y Build\Bin\*.dll Game\Bin\*.dll
@if /I "%1" EQU "/dbg" copy /Y Build\Bin\*.pdb Game\Bin\*.pdb 
goto :eof

:usage
@cls
@echo X-Ray Engine builder
@echo Usage: Build.cmd [/g] [/b] (target) [/i] (/dbg)
@echo Parameters:
@echo 	/g - Generate CMake files
@echo 	/b - Build X-Ray
@echo 	/i - Copy compiled binaries in work dir
@echo Options:
@echo 	(target) - target for build (default %TARGET%)
@echo 	(/nodbg) - copy debug information in work dir
@echo Target's:
@echo 	- xrCore
@echo 	- xr_3da
@echo 	- xrGame
@pause > nul