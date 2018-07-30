# CMakeList.txt : CMake project for Nene_quest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (APP_TARGET nenequest)

# opengl
find_package (OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIRS})

# glfw
find_package (glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries (${GLFW_LIBRARY_DIRS})

# glew
find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})

# glm
find_package (glm REQUIRED)

# openal
find_package (OpenAL CONFIG REQUIRED)

# Add source to this project's executable.
file (GLOB_RECURSE src_files ./*)

add_executable (${APP_TARGET}
	${src_files}
)

target_link_libraries (${APP_TARGET}
	${OPENGL_LIBRARIES}
	glfw
	${GLEW_LIBRARIES}
	glm
	OpenAL::OpenAL
)

# TODO: Add tests and install targets if needed.
