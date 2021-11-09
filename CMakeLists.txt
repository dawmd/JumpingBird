cmake_minimum_required(VERSION 3.0)


# the project's name
project(JumpingBird VERSION 1.0)


# no information about compilation status
set_property(GLOBAL PROPERTY RULE_MESSAGE OFF)


# displaying information about making the project
set(CMAKE_VERBOSE_MAKEFILE ON)


# required third-party packages
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW 2.0 REQUIRED)
find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# flags for compiling the files
set(CMAKE_CXX_FLAGS "-DGLEW_NO_GLU -Wall -Wextra -O3")


# source files
# set(PROJECT_SOURCE_DIR src)


# add the executable
add_executable(JumpingBird main.cpp Window.cpp Matrix4f.cpp Rectangle.cpp Bird.cpp Shader.cpp Game.cpp Pipe.cpp)


# linking the libraries
target_link_libraries(JumpingBird OpenGL::GL GLEW::GLEW glfw)
