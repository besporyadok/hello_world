macro(add_dir dirs)
	foreach(dir in ${dirs})
		file(GLOB ${dir}_cs ${dir} "${dir}/*.c")
		file(GLOB ${dir}_cpps ${dir} "${dir}/*.cpp")
		file(GLOB ${dir}_cxxs ${dir} "${dir}/*.cxx")
		list(APPEND ${PROJECT_NAME}__SOURCES ${${dir}_cs} ${${dir}_cpps} ${${dir}_cxxs})
	endforeach()
endmacro()

macro(exclude_from_build fn)
	list(REMOVE_ITEM ${PROJECT_NAME}__SOURCES "${fn}")
endmacro()