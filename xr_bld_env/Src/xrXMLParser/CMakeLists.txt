project(xrXMLParser)

list(APPEND DIRS "${PROJECT_SOURCE_DIR}")
add_dir("${DIRS}")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE XRXMLPARSER_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)