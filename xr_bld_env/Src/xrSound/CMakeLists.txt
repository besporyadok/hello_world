project(xrSound)

add_dir("${PROJECT_SOURCE_DIR}")
exclude_from_build("${PROJECT_SOURCE_DIR}/MusicStream.cpp")
exclude_from_build("${PROJECT_SOURCE_DIR}/xr_cda.cpp")
exclude_from_build("${PROJECT_SOURCE_DIR}/xr_streamsnd.cpp")
exclude_from_build("${PROJECT_SOURCE_DIR}/xrCDB_Collector.cpp")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE XRSOUND_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)

target_link_libraries(${PROJECT_NAME} dxguid.lib vorbisfile_static.lib ogg_static.lib OpenAL32.lib)