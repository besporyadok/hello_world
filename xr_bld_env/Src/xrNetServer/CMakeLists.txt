project(xrNetServer)

add_dir("${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE XR_NETSERVER_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)

target_link_libraries(${PROJECT_NAME} ws2_32.lib dxerr9.lib dxguid8.lib)