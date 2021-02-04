project(xrLUA_JIT)

list(APPEND DIRS "${PROJECT_SOURCE_DIR}" "src" "luabind")
add_dir("${DIRS}")
exclude_from_build("${PROJECT_SOURCE_DIR}/src/lua.c")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE _USRDLL LUA_BUILD_AS_DLL LUABIND_BUILDING)

target_include_directories(${PROJECT_NAME} PRIVATE "dynasm")
# target_precompile_headers(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:StdAfx.h>)

string(REPLACE "/INCREMENTAL" "/INCREMENTAL:NO" CMAKE_SHARED_LINKER_FLAGS_MIXED "${CMAKE_SHARED_LINKER_FLAGS_MIXED}")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/OPT:REF")