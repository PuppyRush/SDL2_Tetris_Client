cmake_minimum_required(VERSION 3.12)
project(tetris_figure_class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)

add_library(boost::serialization INTERFACE IMPORTED)



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
        src/Common/TType.h
        src/Common/TProperty.h
        src/Common/TypeTraits.h
        src/Common/TDefine.h
        src/Common/THeader.h
        src/Common/TStruct.h
        src/Tetris/TFiguers/TFigureL.h
        src/Tetris/TFiguers/TFigureUnit.h
        src/Tetris/TFiguers/TFigureUnit.cpp
        src/Tetris/TFiguers/TFigureL.cpp
        src/Tetris/TFiguers/TFigureL.h
        src/Tetris/TFiguers/TFigureBuilder.h
        src/Tetris/TFiguers/TFigure.cpp
        src/Tetris/TFiguers/TFigureBoard.cpp
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
        src/Tetris/TObject/TScore.cpp
        src/Tetris/TObject/TScore.h
        src/Tetris/TDisplay/TGameLocalDisplay.cpp
        src/Tetris/TDisplay/TGameLocalDisplay.h
        src/Tetris/TDisplay/TGameDisplay.cpp
        src/Tetris/TDisplay/TGameDisplay.h
        src/SDLEasyGUI/Controller/ControllBuilder.cpp
        src/SDLEasyGUI/Controller/ControllBuilder.h
        src/SDLEasyGUI/Windows/DisplayInterface.h
        src/SDLEasyGUI/Windows/DisplayInterface.cpp
        src/SDLEasyGUI/Windows/DisplayController.cpp
        src/SDLEasyGUI/Windows/DisplayInterface.h
        src/SDLEasyGUI/Windows/Window.cpp
        src/SDLEasyGUI/Windows/Window.h
        src/Tetris/TMain/TMainLocalDisplay.h
        src/Tetris/TMain/TMainLocalDisplay.cpp
        src/Tetris/TMain/TMainDisplay.h
        src/Tetris/TMain/TMainDisplay.cpp
        src/Tetris/TMain/TMainOnlineDisplay.h
        src/Tetris/TMain/TMainOnlineDisplay.cpp
        src/Tetris/TDisplay/TOptionDisplay.cpp
        src/Tetris/TDisplay/TOptionDisplay.h
        src/Tetris/TOption/TOptionManager.cpp
        src/Tetris/TOption/TOptionManager.h
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
        src/GameInterface/Object/Player.cpp
        src/GameInterface/Object/Player.h
        src/GameInterface/Object/Room.cpp
        src/GameInterface/Object/Room.h
        src/GameInterface/Object/Atomic.h
        src/GameInterface/Object/Object.cpp
        src/GameInterface/Object/Object.h
        src/GameInterface/Online/TClientConnector.cpp
        src/GameInterface/Online/TClientConnector.h
        src/GameInterface/Online/TClientService.cpp
        src/GameInterface/Online/TClientService.h
        src/SDLEasyGUI/Controller/Border.cpp
        src/SDLEasyGUI/Controller/Border.h
        src/SDLEasyGUI/Windows/GraphicInterface.h
        src/Tetris/TObject/TPlayer.h
        src/Tetris/TObject/TPlayer.cpp
        src/Tetris/TFiguers/TFigureController.cpp
        src/Tetris/TFiguers/TFigureController.h
        src/Tetris/TClient/TClientController.h
        src/GameInterface/Online/ClientController.cpp
        src/GameInterface/Online/ClientController.h)

include_directories(
        tetris_figure_class/src
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${ACE_INCLUDE_DIR})

target_link_libraries(
        tetris_figure_class
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY}
        ${ACE_LIBRARIES}
        Threads::Threads)

