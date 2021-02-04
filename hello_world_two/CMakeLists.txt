project(cw)

add_dir("${PROJECT_SOURCE_DIR}")
# exclude_from_build("${PROJECT_SOURCE_DIR}/Application_linkage.cpp")

add_executable(${PROJECT_NAME} WIN32 ${${PROJECT_NAME}__SOURCES} "${PROJECT_SOURCE_DIR}/CourseWork.rc")

add_custom_target(ui
				  COMMAND uicc ${PROJECT_SOURCE_DIR}/ui/MainMenu.ribbon
							   ${PROJECT_SOURCE_DIR}/ui/MainMenu.bin
							   /header:${PROJECT_SOURCE_DIR}/ui/MainMenu.h
							   /res:${PROJECT_SOURCE_DIR}/ui/MainMenu.rc
				  COMMENT "Compiling UI...")
add_dependencies(${PROJECT_NAME} ui)

# target_link_libraries(${PROJECT_NAME} d3d9.lib xrCore.lib)

install(TARGETS ${PROJECT_NAME} 
		CONFIGURATIONS Mixed 
		RUNTIME DESTINATION Bin/)

install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION Bin/)