cmake_minimum_required(VERSION 3.12)
project(GameInterface)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)
find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})

########################################################################
##  general find

find_path(ACE_INCLUDE_DIR ace/ACE.h ${CMAKE_SOURCE_DIR}/../ACE_wrappers/ /usr/include /usr/local/include $ENV{ACE_ROOT} $ENV{ACE_ROOT}/include DOC "directory containing ace/*.h for ACE library")

find_library(ACE_LIBRARY NAMES ACE ace PATHS ${CMAKE_SOURCE_DIR}/../ACE_wrappers/lib/ /usr/lib /usr/local/lib $ENV{ACE_ROOT}/lib $ENV{ACE_ROOT} DOC "ACE library file")

########################################################################
## finished - now just set up flags and complain to user if necessary

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


# TSS: backwards compatibility
set(ACE_LIBRARIES ${ACE_LIBRARY})

include_directories(
        src
        SYSTEM ${Boost_INCLUDE_DIR}
        ../../src
        .
        ${PROJECT_SOURCE_DIR}/src/SDLEasyGUI
        ${PROJECT_SOURCE_DIR}/src/Tetris
        ${ACE_INCLUDE_DIR})


ADD_LIBRARY(GameInterface STATIC
        src/Online/JsonHelper.cpp
        src/Online/JsonHelper.h
        src/Online/PlayerConnector.cpp
        src/Online/PlayerService.cpp
        src/Online/PacketQueue.cpp
        src/Online/Packet.cpp
        src/Object/Player.cpp
        src/Object/Object.cpp
        src/Object/Room.cpp
        src/Object/GameRoom.cpp
        src/Object/WaitingRoom.cpp
        src/SubScription/ManagerController.cpp
        include/Subject.h
        include/Player.h
        include/Object.h
        include/Room.h
        include/Atomic.h
        include/GameRoom.h
        include/WaitingRoom.h
        include/Event.h
        include/TStruct.h
        include/Quit.h
        include/JsonPackage.h
        include/PlayerConnector.h
        include/PlayerService.h
        include/Observer.h
        include/VectorSubject.h
        include/ManagerController.h
        include/MapSubject.h
        include/MessageType.h
        include/Packet.h
        include/PacketQueue.h
        )


target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${ACE_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        Threads::Threads)

