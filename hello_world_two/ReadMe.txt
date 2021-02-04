Hello World #2
Author: K4R (besporyadok)

----------------
|I| What is it?
----------------
My hello world (round two) for probe programming on C++, 
WinAPI, Direct3D, CMake and also probe join with real components
(On example core game engine named X-Ray). 
This program initialize Direct3D and paint window in gray color.
Additional program create simple Fluent (aka Ribbon) menu and 
initializing X-Ray Engine core.

-----------------------
|II| How build this?
-----------------------
Generally this program build without installed Visual Studio or 
Windows SDK and Directx SDK.

Requirements:
- Windows SDK 7.1 or Visual Studio 2010
- DirectX SDK June 2010
- CMake 3.19
- X-Ray build environment from '..\xr_bld_env'
- xrCore.lib from X-Ray Engine

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

1) Execute 'Build.cmd' with '/b' parameter from 'xr_bld_env'.

------------------
|III| Source tree
------------------
<root>
+-- \ui
|   +-- MainMenu.ribbon 	; XML source (XAML) for menu
+-- \xray 					; Need X-Ray Engine headers (after small refactoring)
+-- CMakeLists.txt 			; Config file for CMake
+-- EP.cpp 					; Entry point for this application
+-- Application.cpp 		; Implementation main application class (message cycle, create main window)
+-- Application_linkage.cpp ; For linker
+-- CourseWork.rc 			; Resource file for this application
+-- Global.cpp 				; Implementation store global objects (such RenderDevice, ResourceManager)
+-- Window.cpp 				; Implementation base window class (This class mostrousle monster!)
+-- Window_WndProc.cpp 		; Implementation window procedure for application windows
+-- MainWindow.cpp 			; Implementation application main window class
+-- MainWindow_About.cpp 	; Implementation window procedure for 'About' dialog
+-- MainWindow_About.h 		; Define's need for programming dialog box without resource
+-- MainMenu.cpp 			; Implementation application menu (class and fluent style)
+-- RenderWindow.cpp 		; Implementation experimental child window class for rendering
