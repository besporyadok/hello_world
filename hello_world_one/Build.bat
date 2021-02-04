@echo off

@if /I "%1" equ "clean" goto clean

@set TOOL=<YOUR_COMPILER_DIR>
goto new_style

:old_style
@%TOOL%\Bin\cl /DUNICODE /Zc:sizedDealloc- /I%TOOL%\Inc\sal /I%TOOL%\Inc\crt /I%TOOL%\Inc\w32 /I%TOOL%\Inc\d3d /c /nologo /Wv:18 Debug.cpp > Build.log
@%TOOL%\Bin\cl /DUNICODE /Zc:sizedDealloc- /I%TOOL%\Inc\sal /I%TOOL%\Inc\crt /I%TOOL%\Inc\w32 /I%TOOL%\Inc\d3d /c /nologo /Wv:18 Engine.cpp >> Build.log
@%TOOL%\Bin\cl /DUNICODE /Zc:sizedDealloc- /I%TOOL%\Inc\sal /I%TOOL%\Inc\crt /I%TOOL%\Inc\w32 /I%TOOL%\Inc\d3d /c /nologo /Wv:18 Engine_msg.cpp >> Build.log
@%TOOL%\Bin\cl /DUNICODE /Zc:sizedDealloc- /I%TOOL%\Inc\sal /I%TOOL%\Inc\crt /I%TOOL%\Inc\w32 /I%TOOL%\Inc\d3d /c /nologo /Wv:18 EP.cpp >> Build.log
@%TOOL%\Bin\link /LIBPATH:%TOOL%\Lib /NOLOGO EP.obj Engine.obj Engine_msg.obj >> Build.log

goto exit

:new_style
@%TOOL%\Bin\nmake /f Makefil0 /nologo > Build.log
goto exit

:clean
@del *.exe 2> nul
@del *.obj 2> nul
@del *.pdb 2> nul
@del *.ilk 2> nul
@del *.log 2> nul
@del *.jpg 2> nul

:exit
