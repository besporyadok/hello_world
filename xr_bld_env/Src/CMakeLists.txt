cmake_minimum_required(VERSION 3.19)

if(NOT DEFINED XRAY_DIR)
	set(XRAY_DIR "${CMAKE_SOURCE_DIR}")
endif()

project(XRay)

include("${XRAY_DIR}/cmake/xray.cmake")
include("${XRAY_DIR}/cmake/utils.cmake")

option(XR_BUILD "Build X-Ray Engine" OFF)
unset(XR_BUILD CACHE)

if(${XR_BUILD})
	add_subdirectory(xrCore)
	add_subdirectory(xrXMLParser)
	add_subdirectory(xrLUA_JIT)
	add_subdirectory(xrCDB)
	add_subdirectory(xrSound)
	add_subdirectory(xrParticles)
	add_subdirectory(xr_3da)
	add_subdirectory(xr_3da/xrCPU_Pipe)
	add_subdirectory(xr_3da/xrRender_R1)
	add_subdirectory(xrNetServer)
	add_subdirectory(xrODE)
	add_subdirectory(xr_3da/xrGame)
else()
	add_subdirectory(editors/coursework) # For personal need's
endif()