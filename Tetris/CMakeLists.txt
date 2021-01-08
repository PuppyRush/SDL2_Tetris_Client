cmake_minimum_required(VERSION 3.12)
project(tetris)

message("----------------tetris START----------------")

find_package(Boost 1.68.0)
find_package(jsoncpp REQUIRED)
find_path(BOOST_INCLUDE_DIR boost)

#find_library(
#        #SDL2EasyGUI
#        #GameInterface
#        #TetrisModule
#        #NAMES libSDL2EasyGUI.a
#        #NAMES libGameInterface.a
#        #HINTS ${PROJECT_SOURCE_DIR}/lib/SDL2EasyGUI/cmake-build-debug
#        #HINTS ${PROJECT_SOURCE_DIR}/lib/GameInterface/src
#        #REQUIRED
#        )

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
        ${BOOST_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/GameInterface
        ${PROJECT_SOURCE_DIR}/src/SDLEasyGUI
        ${PROJECT_SOURCE_DIR}/src/Tetris
		)


target_link_libraries(
        tetris PRIVATE
        SDL2EasyGUI
        TetrisModule 
        GameInterface
        jsoncpp_lib
		${SDL2_gfx_LIBRARY}
		${BOOST_LIBRARIES}

		)