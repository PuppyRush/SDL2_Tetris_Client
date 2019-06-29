cmake_minimum_required(VERSION 3.12)
project(tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(PkgConfig REQUIRED)

#add_library(boost::serialization INTERFACE IMPORTED)

pkg_check_modules(JSONCPP jsoncpp)

link_libraries(${JSONCPP_LIBRARIES})


set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()


#add_definitions(${A_DEFINITIONS})
find_library(
        SDL2EasyGUI
        GameInterface
        TetrisModule
        NAMES libSDL2EasyGUI.a
        NAMES libGameInterface.a
        HINTS ${PROJECT_SOURCE_DIR}/lib/SDL2EasyGUI/cmake-build-debug
        HINTS ${PROJECT_SOURCE_DIR}/lib/GameInterface/src
        REQUIRED)

add_executable(tetris
        include/TProperty.h
        include/TDefine.h
        include/THeader.h
        include/TResource.h
        include/ClientService.h
        include/TDisplayInterface.h
        src/Main.cpp
        src/TObject/TScore.cpp
        src/TObject/TScore.h
        src/TObject/TPlayer.h
        src/TObject/TPlayer.cpp
        src/TDisplay/Game/TSingleGameDisplay.cpp
        src/TDisplay/Game/TSingleGameDisplay.h
        src/TDisplay/Game/TGameDisplay.cpp
        src/TDisplay/Game/TGameDisplay.h
        src/TDisplay/Main/TLocalMainDisplay.h
        src/TDisplay/Main/TLocalMainDisplay.cpp
        src/TDisplay/Main/TMainDisplay.h
        src/TDisplay/Main/TMainDisplay.cpp
        src/TDisplay/Main/TMultiMainDisplay.h
        src/TDisplay/Main/TMultiMainDisplay.cpp
        src/TDisplay/TOptionDisplay.cpp
        src/TDisplay/TOptionDisplay.h
        src/TDisplay/Game/TMultiGameRoomDisplay.cpp
        src/TDisplay/Game/TMultiGameRoomDisplay.h
        src/TDisplay/Waiting/TWaitingRoomCard.cpp
        src/TDisplay/Waiting/TWaitingRoomCard.h
        src/TDisplay/Waiting/TWaitingRoomDisplay.cpp
        src/TDisplay/Waiting/TWaitingRoomDisplay.h
        src/TDisplay/Main/TEnterServerDisplay.cpp
        src/TDisplay/Main/TEnterServerDisplay.h
        src/TOption/TOptionManager.cpp
        src/TOption/TOptionManager.h
        src/TClient/ClientService.cpp
        src/TDisplay/Waiting/TCreateGameroomDisplay.cpp
        src/TDisplay/Waiting/TCreateGameroomDisplay.h
        src/TObject/TWaitingRoom.cpp
        src/TObject/TWaitingRoom.h
        src/TObject/TGameRoom.cpp
        src/TObject/TGameRoom.h
        )


include_directories(
        include
        SYSTEM
        ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/GameInterface
        ${PROJECT_SOURCE_DIR}/src/SDLEasyGUI
        ${PROJECT_SOURCE_DIR}/src/Tetris
        ${ACE_INCLUDE_DIR})


target_link_libraries(
        tetris
        SDL2EasyGUI
        TetrisModule
        GameInterface
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY}
        ${ACE_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        Threads::Threads)



