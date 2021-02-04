project(xrCore)

list(APPEND DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/blackbox")

add_dir("${DIRS}")
exclude_from_build("${PROJECT_SOURCE_DIR}/xrDebugNew.cpp")
exclude_from_build("${PROJECT_SOURCE_DIR}/LocatorAPI_Notifications.cpp")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES} "${PROJECT_SOURCE_DIR}/xrCore.rc")

target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE  _USRDLL XRCORE_EXPORTS)