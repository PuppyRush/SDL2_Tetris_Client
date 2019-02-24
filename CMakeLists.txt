cmake_minimum_required(VERSION 3.12)
project(tetris_figure_class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)
find_package(PkgConfig REQUIRED)

#add_library(boost::serialization INTERFACE IMPORTED)

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

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()

add_executable(tetris_figure_class
        src/Main.cpp
        src/Tetris/Common/TProperty.h
        src/Tetris/Common/TDefine.h
        src/Tetris/Common/THeader.h
        src/Tetris/Common/TResource.h
        src/Tetris/TFiguers/TFigureL.h
        src/Tetris/TFiguers/TFigureUnit.h
        src/Tetris/TFiguers/TFigureUnit.cpp
        src/Tetris/TFiguers/TFigureL.cpp
        src/Tetris/TFiguers/TFigureL.h
        src/Tetris/TFiguers/TFigureBuilder.h
        src/Tetris/TFiguers/TFigure.cpp
        src/Tetris/TFiguers/TFigureBoard.h
        src/Tetris/TFiguers/TFigureBuilder.cpp
        src/Tetris/TFiguers/TFigureBoardBuilder.cpp
        src/Tetris/TFiguers/TFigureBoardBuilder.h
        src/Tetris/TFiguers/TFigureZ.cpp
        src/Tetris/TFiguers/TFigureZ.h
        src/Tetris/TFiguers/TFigureI.cpp
        src/Tetris/TFiguers/TFigureI.h
        src/Tetris/TFiguers/TFigureO.cpp
        src/Tetris/TFiguers/TFigureO.h
        src/Tetris/TFiguers/TFigureT.cpp
        src/Tetris/TFiguers/TFigureT.h
        src/Tetris/TFiguers/TFigureController.cpp
        src/Tetris/TFiguers/TFigureController.h
        src/Tetris/TObject/TScore.cpp
        src/Tetris/TObject/TScore.h
        src/Tetris/TObject/TPlayer.h
        src/Tetris/TObject/TPlayer.cpp
        src/Tetris/TDisplay/Game/TSingleGameDisplay.cpp
        src/Tetris/TDisplay/Game/TSingleGameDisplay.h
        src/Tetris/TDisplay/Game/TGameDisplay.cpp
        src/Tetris/TDisplay/Game/TGameDisplay.h
        src/Tetris/TDisplay/Main/TLocalMainDisplay.h
        src/Tetris/TDisplay/Main/TLocalMainDisplay.cpp
        src/Tetris/TDisplay/Main/TMainDisplay.h
        src/Tetris/TDisplay/Main/TMainDisplay.cpp
        src/Tetris/TDisplay/Main/TMultiMainDisplay.h
        src/Tetris/TDisplay/Main/TMultiMainDisplay.cpp
        src/Tetris/TDisplay/TOptionDisplay.cpp
        src/Tetris/TDisplay/TOptionDisplay.h
        src/Tetris/TDisplay/Game/TMultiGameRoomDisplay.cpp
        src/Tetris/TDisplay/Game/TMultiGameRoomDisplay.h
        src/Tetris/TDisplay/Waiting/TWaitingRoomCard.cpp
        src/Tetris/TDisplay/Waiting/TWaitingRoomCard.h
        src/Tetris/TDisplay/Waiting/TWaitingRoomDisplay.cpp
        src/Tetris/TDisplay/Waiting/TWaitingRoomDisplay.h
        src/Tetris/TDisplay/Main/TEnterServerDisplay.cpp
        src/Tetris/TDisplay/Main/TEnterServerDisplay.h
        src/Tetris/TOption/TOptionManager.cpp
        src/Tetris/TOption/TOptionManager.h
        src/Tetris/TClient/TClientController.h
        src/Tetris/TClient/TClientController.cpp
        src/SDLEasyGUI/SEG_Event.h
        src/SDLEasyGUI/Windows/DisplayInterface.h
        src/SDLEasyGUI/Windows/DisplayInterface.cpp
        src/SDLEasyGUI/Windows/DisplayController.cpp
        src/SDLEasyGUI/Windows/DisplayInterface.h
        src/SDLEasyGUI/Windows/Window.cpp
        src/SDLEasyGUI/Windows/Window.h
        src/SDLEasyGUI/Windows/GraphicInterface.h
        src/SDLEasyGUI/Controller/ControllBuilder.cpp
        src/SDLEasyGUI/Controller/ControllBuilder.h
        src/SDLEasyGUI/Controller/Controll.cpp
        src/SDLEasyGUI/Controller/Controll.h
        src/SDLEasyGUI/Controller/StaticLabel.cpp
        src/SDLEasyGUI/Controller/StaticLabel.h
        src/SDLEasyGUI/Controller/Button.cpp
        src/SDLEasyGUI/Controller/Button.h
        src/SDLEasyGUI/Controller/ButtonBasic.cpp
        src/SDLEasyGUI/Controller/ButtonBasic.h
        src/SDLEasyGUI/Controller/RadioButton.cpp
        src/SDLEasyGUI/Controller/RadioButton.h
        src/SDLEasyGUI/Controller/EditLabel.cpp
        src/SDLEasyGUI/Controller/EditLabel.h
        src/SDLEasyGUI/Controller/GroupControllManager.cpp
        src/SDLEasyGUI/Controller/GroupControllManager.h
        src/SDLEasyGUI/Controller/Border.cpp
        src/SDLEasyGUI/Controller/Border.h
        src/SDLEasyGUI/Controller/ListBox.cpp
        src/SDLEasyGUI/Controller/ListBox.h
        src/SDLEasyGUI/Windows/EventListener.h
        src/SDLEasyGUI/SEG_Initiator.h
        src/SDLEasyGUI/SEG_Constant.h
        src/SDLEasyGUI/SEG_Quit.h
        src/SDLEasyGUI/Windows/EventQueue.cpp
        src/SDLEasyGUI/Windows/EventQueue.h
        src/SDLEasyGUI/Windows/EventDelivery.h
        src/SDLEasyGUI/Command/Commander.h
        src/SDLEasyGUI/Command/EventCommand.h
        src/SDLEasyGUI/SEG_Event.cpp
        src/GameInterface/Online/JsonHelper.cpp
        src/GameInterface/Online/JsonHelper.h
        src/GameInterface/Object/Player.cpp
        src/GameInterface/Object/Player.h
        src/GameInterface/Object/Room.cpp
        src/GameInterface/Object/Room.h
        src/GameInterface/Object/Atomic.h
        src/GameInterface/Object/Object.cpp
        src/GameInterface/Object/Object.h
        src/GameInterface/Object/GameRoom.cpp
        src/GameInterface/Object/GameRoom.h
        src/GameInterface/Object/WaitingRoom.cpp
        src/GameInterface/Object/WaitingRoom.h
        src/GameInterface/Online/ClientConnector.cpp
        src/GameInterface/Online/ClientConnector.h
        src/GameInterface/Online/ClientService.cpp
        src/GameInterface/Online/ClientService.h
        src/GameInterface/Event.h
        src/GameInterface/TStruct.h
        src/GameInterface/Observer/Observer.h
        src/GameInterface/Online/MessageType.h
        src/GameInterface/Online/Packet.cpp
        src/GameInterface/Online/Packet.h
        src/GameInterface/Online/PacketQueue.h
        src/GameInterface/Online/PacketQueue.cpp
        src/GameInterface/Define.h src/Tetris/Common/TStruct.h)


include_directories(
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/GameInterface
        ${PROJECT_SOURCE_DIR}/src/SDLEasyGUI
        ${PROJECT_SOURCE_DIR}/src/Tetris
        ${ACE_INCLUDE_DIR})

target_link_libraries(
        tetris_figure_class
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY}
        ${ACE_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        Threads::Threads)



