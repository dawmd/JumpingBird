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
set(SOURCE_FILES
    src/main.cpp
    src/Window.cpp
    src/Matrix4f.cpp
    src/Rectangle.cpp
    src/Bird.cpp
    src/Pipe.cpp
    src/Shader.cpp
    src/Game.cpp
)


# add the executable
add_executable(JumpingBird ${SOURCE_FILES})


# linking the libraries
target_link_libraries(JumpingBird OpenGL::GL GLEW::GLEW glfw)
