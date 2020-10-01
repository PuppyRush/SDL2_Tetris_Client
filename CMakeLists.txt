cmake_minimum_required(VERSION 3.12)
project(sdl2_tetris_client)

message("----------------sdl2_tetris_client START----------------")

#pre out cmake var
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )
message("CMAKE_SYSTEM_NAME : " ${CMAKE_SYSTEM_NAME})
message("VCPKG_ROOT " $ENV{VCPKG_ROOT})


#set enviroment var
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)")
	if(CMAKE_SYSTEM_NAME MATCHES "Windows")
		set(PLATFORM "x86-windows")
	endif()
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "(amd64)|(AMD64)")
	if(CMAKE_SYSTEM_NAME MATCHES "Windows")
		set(PLATFORM "x64-windows")
	endif()
endif()

set(VCPKG_PLATFORM $ENV{VCPKG_ROOT}\\installed\\${PLATFORM})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BOOST_LIBRARY_DIRS ${VCPKG_PLATFORM}\\lib)
set(BOOST_INCLUDE_DIR ${VCPKG_PLATFORM}\\include)

#post out cmake var
message("VCPKG_PLATFORM : " ${VCPKG_PLATFORM})
message("PLATFORM : " ${PLATFORM})
message("MSVC_VERSION : " ${MSVC_VERSION})


if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
        message("CMAKE_CXX_COMPILER_VERSION :" ${CMAKE_CXX_COMPILER_VERSION} )
    endif()
endif()


# You can tweak some common (for all subprojects) stuff here. For example:

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message("In-source builds are not allowed.")
endif ()

#set(BUILD_SHARED_LIBS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

set(CMAKE_BUILD_TYPE=Debug ./cmake-build-debug)
#set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "postfix applied to debug build of libraries")

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_RepEFIX "")
endif ()

# When done tweaking common stuff, configure the components (subprojects).
# NOTE: The order matters! The most independent ones should go first.
include_directories(lib)
add_subdirectory(lib/GameInterface) # C is a shared library (depends on B and external XXX)
add_subdirectory(lib/SDL2EasyGUI)
add_subdirectory(lib/Tetris)
add_subdirectory(lib/magic_enum)

add_subdirectory(Tetris) # Executable (depends on A and C)