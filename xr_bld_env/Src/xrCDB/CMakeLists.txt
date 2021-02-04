project(xrCDB)

list(APPEND DIRS "${PROJECT_SOURCE_DIR}")
add_dir("${DIRS}")
exclude_from_build("${PROJECT_SOURCE_DIR}/cl_raypick.cpp")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE XRCDB_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE StdAfx.h)