# CMakeList.txt : CMake project for Nene_quest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (APP_TARGET nenequest)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# OpenGL
find_package (OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIRS})

# GLFW3
find_package (glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries (${GLFW_LIBRARY_DIRS})

# GLEW
find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})

# GLM
find_package (glm REQUIRED)

# OpenAl-soft
find_package (OpenAL CONFIG REQUIRED)

# FreeType
find_package (Freetype REQUIRED)

# libpng
find_package (PNG REQUIRED)

# tinyobjloader
find_package (tinyobjloader CONFIG REQUIRED)

# Add source to this project's executable.
file (GLOB_RECURSE cpp_files ./*.cpp)
file (GLOB_RECURSE h_files ./*.h)

add_executable (${APP_TARGET}
	${cpp_files}
	${h_files}
)

target_link_libraries (${APP_TARGET}
	${OPENGL_LIBRARIES}
	glfw
	${GLEW_LIBRARIES}
	glm
	OpenAL::OpenAL
	Freetype::Freetype
	PNG::PNG
	tinyobjloader
)

# Scan through resource folder for updated files and copy if none existing or changed
file (GLOB_RECURSE resources "resources/*.*")
foreach(resource ${resources})
	get_filename_component(filename ${resource} NAME)
	get_filename_component(dir ${resource} DIRECTORY)
	get_filename_component(dirname ${dir} NAME)
 
	set (output "")
 
	while(NOT ${dirname} STREQUAL resources)
		get_filename_component(path_component ${dir} NAME)
		set (output "${path_component}/${output}")
		get_filename_component(dir ${dir} DIRECTORY)
		get_filename_component(dirname ${dir} NAME)
	endwhile()
 
	set(output "${CMAKE_CURRENT_BINARY_DIR}/resources/${output}/${filename}")
 
	add_custom_command(
		COMMENT "Moving updated resource-file '${filename}'"
		OUTPUT ${output}
		DEPENDS ${resource}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${resource}
		${output}
	)
	add_custom_target(${filename} ALL DEPENDS ${resource} ${output})
 
endforeach()

# TODO: Add tests and install targets if needed.
