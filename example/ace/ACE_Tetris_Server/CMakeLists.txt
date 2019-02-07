cmake_minimum_required(VERSION 3.10)
project(ACE_Tetris_Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

# Add Include Source File & Header File
add_executable(${PROJECT_NAME}
    src/quit.cpp
    src/service.cpp
    src/quit.h
    src/server.cpp
    src/generalacceptor.h
    src/service.h
    src/cpplint.py
    src/generalacceptor.cpp
)

# Find the ACE client includes and library
set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_path(
    ACE_INCLUDE_DIR ace/ACE.h
    ${CMAKE_SOURCE_DIR}/../ACE_wrappers/ /usr/include /usr/local/include
    $ENV{ACE_ROOT} $ENV{ACE_ROOT}/include DOC
    "directory containing ace/*.h for ACE library"
)

find_library(
    ACE_LIBRARY NAMES ACE ace PATHS
    ${CMAKE_SOURCE_DIR}/../ACE_wrappers/lib/ /usr/lib /usr/local/lib
    $ENV{ACE_ROOT}/lib $ENV{ACE_ROOT} DOC "ACE library file"
)

if (ACE_INCLUDE_DIR AND ACE_LIBRARY)
    set(ACE_FOUND TRUE)
else ()
    set(ACE_FOUND FALSE)
endif ()

if (ACE_DEBUG_LIBRARY)
    set(ACE_DEBUG_FOUND TRUE)
else ()
    set(ACE_DEBUG_LIBRARY ${ACE_LIBRARY})
endif ()

if (ACE_FOUND)
    if (NOT Ace_FIND_QUIETLY)
	message(STATUS "Found ACE library: ${ACE_LIBRARY}")
	message(STATUS "Found ACE include: ${ACE_INCLUDE_DIR}")
    endif ()
else ()
    if (Ace_FIND_REQUIRED)
	message(FATAL_ERROR "Could not find ACE")
    endif ()
endif ()

set(ACE_LIBRARIES ${ACE_LIBRARY})
include_directories(${ACE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${ACE_LIBRARIES} )


set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()

# Find the Boost Thread
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.67.0 COMPONENTS)
find_package(Boost COMPONENTS thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Boost::thread)
endif()
