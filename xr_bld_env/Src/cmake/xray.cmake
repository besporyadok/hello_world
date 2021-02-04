set(CMAKE_CONFIGURATION_TYPES Debug DebugNoExceptions Mixed Release)
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Create XRay build config's" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin" CACHE STRING "Binary output dir" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib" CACHE STRING "Library output dir" FORCE)
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin" CACHE STRING "PDB output dir" FORCE)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../Game" CACHE PATH "Installation directory" FORCE)
endif()

set(CL_COMM_FLAGS
		/DWIN32
		/D_WINDOWS
		/Zc:forScope-
		/nologo
		)

string(REPLACE ";" " " CL_COMM_FLAGS "${CL_COMM_FLAGS}")

set(CMAKE_CXX_FLAGS "${CL_COMM_FLAGS}" CACHE STRING "MSVC++ common flags" FORCE)

# Debug
set(CMAKE_C_FLAGS_DEBUG "/Zi" CACHE STRING "MSVC flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "/Zi" CACHE STRING "MSVC++ flags" FORCE)
# DebugNoExceptions
# Mixed
set(CMAKE_C_FLAGS_MIXED "/Ox /Ob2 /Oi /Ot /Oy- /GT /GF /GS /Gy- /GR /GL- /DMIXED /DNDEBUG /Zi" CACHE STRING "MSVC flags" FORCE)
set(CMAKE_CXX_FLAGS_MIXED "/Ox /Ob2 /Oi /Ot /Oy- /GT /GF /GS /Gy- /GR /GL- /EHs /DMIXED /DNDEBUG /Zi" CACHE STRING "MSVC++ flags" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_MIXED "/DEBUG /INCREMENTAL /SUBSYSTEM:windows /LIBPATH:${XRAY_DIR}/ThirdParty/lib /LIBPATH:${CMAKE_BINARY_DIR}/Lib" CACHE STRING "Linker flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_MIXED "/DEBUG /INCREMENTAL /SUBSYSTEM:windows /LIBPATH:${XRAY_DIR}/ThirdParty/lib /LIBPATH:${CMAKE_BINARY_DIR}/Lib" CACHE STRING "Linker flags" FORCE)
# Release

list(APPEND CL_INCL "${XRAY_DIR}/ThirdParty/inc"
					"${XRAY_DIR}/ThirdParty/inc/lua" 
					"${XRAY_DIR}/ThirdParty/inc/oal"
					"${XRAY_DIR}/ThirdParty/inc/eax" 
					"${XRAY_DIR}/xrCore")

include_directories("${CL_INCL}")
