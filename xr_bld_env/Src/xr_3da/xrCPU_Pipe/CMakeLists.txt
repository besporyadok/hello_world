project(xrCPU_Pipe)

add_dir("${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE XRCPU_PIPE_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE StdAfx.h)

target_link_libraries(${PROJECT_NAME} xr_3da.lib)