@echo off
@cls

@setlocal

@set TL=K:\Tool\Dev
@path %TL%\kw\bin;%TL%\dd\Bin;%PATH%

@set INCLUDE=%TL%\dd\Inc\sal;%TL%\dd\Inc\crt;%TL%\dd\Inc\stl;%TL%\dd\Inc\w32;%TL%\dd\Inc\d3d
@set LIB=%TL%\dd\Lib

@if /I "%1" EQU "/g" goto gen

@pushd build
@nmake /errorreport:none /nologo
@popd
@echo [INF] Done!

@goto end

:clean
@goto end

:gen
@cmake -S src -B build -G "NMake Makefiles"

:end
@endlocal
@pause > nul