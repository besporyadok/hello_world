project(xrParticles)

add_dir("${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE XR_PARTICLES_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)