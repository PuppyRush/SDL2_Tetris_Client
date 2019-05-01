cmake_minimum_required(VERSION 3.12)
project(sdl2_tetris_client)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_REQUIRED_FLAGS -std=c++2a)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

# You can tweak some common (for all subprojects) stuff here. For example:

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(BUILD_SHARED_LIBS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

set(CMAKE_BUILD_TYPE=Debug /home/chaed/projects/SDL2_Tetris_Client/cmake-build-debug)
SET(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries")

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

include_directories(lib)
# When done tweaking common stuff, configure the components (subprojects).
# NOTE: The order matters! The most independent ones should go first.
add_subdirectory(lib/GameInterface) # C is a shared library (depends on B and external XXX)
add_subdirectory(lib/SDL2EasyGUI)
add_subdirectory(lib/Tetris)
add_subdirectory(lib/magic_enum)


add_subdirectory(Tetris) # Executable (depends on A and C)