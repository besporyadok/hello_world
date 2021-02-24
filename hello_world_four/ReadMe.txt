Hello World #4
Author: K4R (besporyadok)

----------------
|I| What is it?
----------------
My hello world (round four) for probe programming on C++ and 
WinAPI, Direct3D. 
This program draw into display simple 3D box and lighting his, 
texturing box, very simple camera (forward & backward).
Additional implimentation experimental input handle based on
Observer pattern.
This program variant Hello World #1 program.

-----------------------
|II| How build this?
-----------------------
Generally this program build without installed Visual Studio or 
Windows SDK and Directx SDK.

Requirements:
- Windows SDK 7.1 or Visual Studio 2013
- DirectX SDK June 2010
- CMake 3.19

Build process analogous making Hello World #1.

------------------
|III| Source tree
------------------
ht_entry_point.cpp - Entry point this program, create instance main application class.
Camera.cpp - Simple camera implimentation
input.cpp - Input handle
render.cpp - Drawning
timer.cpp - Simple timer based on high-resolution perfomance counter
