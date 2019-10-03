cmake_minimum_required(VERSION 3.12)
project(sdl2_tetris_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

# You can tweak some common (for all subprojects) stuff here. For example:

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(BUILD_SHARED_LIBS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

set(CMAKE_BUILD_TYPE=Debug ./cmake-build-debug)
set(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries")

find_package(PkgConfig REQUIRED)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)


set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# When done tweaking common stuff, configure the components (subprojects).
# NOTE: The order matters! The most independent ones should go first.
#include_directories(SDL2-2.0.9)
add_subdirectory(SDL2-2.0.9)
add_subdirectory(SDL2_ttf-2.0.15)
include_directories(lib)
add_subdirectory(lib/GameInterface) # C is a shared library (depends on B and external XXX)
add_subdirectory(lib/SDL2EasyGUI)
add_subdirectory(lib/Tetris)
add_subdirectory(lib/magic_enum)

add_subdirectory(Tetris) # Executable (depends on A and C)