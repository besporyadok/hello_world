xr_bld_env
Author: K4R (besporyadok)

----------------
|I| What is it?
----------------
CMake build environment for X-Ray Engine.
Create for educational purposes: probe use CMake on example 
build real project and probe programming on script language
Python.
Based on X-Ray Engine 10 January 2007 snapshot (yes, very old this for 
increasing the difficulty and just for fun :-)).
Make only minimal components need for startup engine without engine SDK.

-----------------------
|II| How build this?
-----------------------
Requirements:
- Windows SDK 7.1 or Visual Studio 2013
- DirectX SDK June 2010
- CMake 3.19
- Boost 1.30.0
- EAX 2.0
- Loki
- Lua 5.1 (need headers placed in xrLUA_JIT)
- LuaJIT 1.0.3
- LiaBind 1.19.2.21
- OpenAL 1.1
- Xiph OggVorbis 1.20
- Xiph OggTheora 1.17
- Optional: Python 2.7

1) Execute 'Build.cmd' with '/b' parameter.
2) Execute 'Build.cmd' with '/i' parameter.
Builded binaries and debug information placed in 'Game\Bin'.

------------------
|III| Tree
------------------
<root>
+--- Build.cmd ; Script for build engine & generate CMake files & cleanup
+--- /Src ; Source code of X-Ray Engine
|	 +--- /cmake ; Directory for shared CMake files
|	 |	  +--- DirChk.py ; Python script for check source directory
|	 |	  +--- utils.cmake ; Shared macros
|	 |	  +--- xray.cmake ; Global CMake settings
|	 +--- /ThirdParty ; Directory for 3rd party components headers & libraries
|	 |	  +--- /inc ; Includes
|	 |	  +--- /lib ; Libraries
|	 +--- /xr_bak ; Various backup's
|	 |	  +--- /Docs ; Backup docs from X-Ray source tree
|	 |	  +--- /VCProj ; Backup original project files (VS 7.1) for projects builded on CMake
|	 |	  +--- /[project_name] ; Backup excluded or duplicated files for [project_name]
|	 +--- CMakeLists.txt ; Root CMake file
+--- /Build ; Output directory for CMake files, temporary build files (such object files), bin & dbg
+--- /Game ; Game directory
|	 +--- /Bin ; Compiled binaries and debug information
|	 +--- /Data ; Game resources directory
|	 |	  +--- /Cfg  ; Configuration engine files
|	 |	  |	   +--- system.ltx ; X-Ray main configuration file with minimal requiriments parameter's
|	 +--- Run.cmd ; Script for run engine
|	 +--- fsgame.ltx ; X-Ray filesystem configuration file
|	 +--- user.ltx ; X-Ray user settings
+--- /tools ; Instruments for build and other
|	 +--- /dd ; Visual C++ 16.0 compiler (aka Visual Studio 2010). Structure this catalog description in
 'ReadMe.txt' files in 'hello_world_one'.
|	 +--- /kw ; CMake 3.19
|	 +--- /vcs ; Git client 2.30
<end>