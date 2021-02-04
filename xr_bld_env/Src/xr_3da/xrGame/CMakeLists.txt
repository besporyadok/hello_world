project(xrGame)

file(GLOB_RECURSE AI_SRC "${PROJECT_SOURCE_DIR}" "ai/*.cpp")

list(APPEND DIRS "${PROJECT_SOURCE_DIR}"
#				 "${PROJECT_SOURCE_DIR}/ai"
				 "${PROJECT_SOURCE_DIR}/dcylinder"
				 "${PROJECT_SOURCE_DIR}/gamespy"
				 "${PROJECT_SOURCE_DIR}/ik"
				 "${PROJECT_SOURCE_DIR}/tri-colliderknoopc"
				 "${PROJECT_SOURCE_DIR}/ui"
				 "${AI_SRC}")

add_dir("${DIRS}")
exclude_from_build("${PROJECT_SOURCE_DIR}/tri-colliderknoopc/dcTriListCollider.cpp")
# include("CMakeLists_exclude.txt")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE /wd4812)
target_include_directories(${PROJECT_NAME} PRIVATE "${XRAY_DIR}/ThirdParty/inc/loki"
								"${XRAY_DIR}/xrODE/include" "${XRAY_DIR}/xr_3da" "${PROJECT_SOURCE_DIR}")
target_compile_definitions(${PROJECT_NAME} PRIVATE XRGAME_EXPORTS dSINGLE MSVC)
target_precompile_headers(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:StdAfx.h>)

target_link_libraries(${PROJECT_NAME} xr_3da.lib)