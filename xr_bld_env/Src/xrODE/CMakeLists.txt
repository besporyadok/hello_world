project(ode)

list(APPEND DIRS "${PROJECT_SOURCE_DIR}/contrib/msvc7/ode_default"
				 "${PROJECT_SOURCE_DIR}/ode/src")
add_dir("${DIRS}")

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}__SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE /Wd4100 /Wd4505) # ?!
target_compile_definitions(${PROJECT_NAME} PRIVATE dSINGLE MSVC dNODEBUG)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/DEF:${PROJECT_SOURCE_DIR}/config/msvcdefs.def")