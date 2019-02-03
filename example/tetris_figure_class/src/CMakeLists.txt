cmake_minimum_required(VERSION 3.12)
project(tetris_figure_class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../CMakeModules;${CMAKE_MODULE_PATH}")

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
        Main.cpp
        Common/TType.h
        Common/TProperty.h
        Common/TypeTraits.h
        Common/TDefine.h
        Common/THeader.h
        Common/TStruct.h
        Tetris/TFiguers/TFigureL.h
        Tetris/TFiguers/TFigureUnit.h
        Tetris/TFiguers/TFigureUnit.cpp
        Tetris/TFiguers/TFigureL.cpp
        Tetris/TFiguers/TFigureL.h
        Tetris/TFiguers/TFigureBuilder.h
        Tetris/TFiguers/TFigure.cpp
        Tetris/TFiguers/TFigureBoard.cpp
        Tetris/TFiguers/TFigureBoard.h
        Tetris/TFiguers/TFigureBuilder.cpp
        Tetris/TFiguers/TFigureBoardBuilder.cpp
        Tetris/TFiguers/TFigureBoardBuilder.h
        Tetris/TFiguers/TFigureZ.cpp
        Tetris/TFiguers/TFigureZ.h
        Tetris/TFiguers/TFigureI.cpp
        Tetris/TFiguers/TFigureI.h
        Tetris/TFiguers/TFigureO.cpp
        Tetris/TFiguers/TFigureO.h
        Tetris/TFiguers/TFigureT.cpp
        Tetris/TFiguers/TFigureT.h
        Tetris/TObject/TScore.cpp
        Tetris/TObject/TScore.h
        Tetris/TDisplay/TGameLocalDisplay.cpp
        Tetris/TDisplay/TGameLocalDisplay.h
        Tetris/TDisplay/TGameDisplay.cpp
        Tetris/TDisplay/TGameDisplay.h
        SDLEasyGUI/Controller/ControllBuilder.cpp
        SDLEasyGUI/Controller/ControllBuilder.h
        SDLEasyGUI/Windows/DisplayInterface.h
        SDLEasyGUI/Windows/DisplayInterface.cpp
        SDLEasyGUI/Windows/DisplayController.cpp
        SDLEasyGUI/Windows/DisplayInterface.h
        SDLEasyGUI/Windows/Window.cpp
        SDLEasyGUI/Windows/Window.h
        Tetris/TMain/TMainLocalDisplay.h
        Tetris/TMain/TMainLocalDisplay.cpp
        Tetris/TMain/TMainDisplay.h
        Tetris/TMain/TMainDisplay.cpp
        Tetris/TMain/TMainOnlineDisplay.h
        Tetris/TMain/TMainOnlineDisplay.cpp
        Tetris/TDisplay/TOptionDisplay.cpp
        Tetris/TDisplay/TOptionDisplay.h
        Tetris/TOption/TOptionManager.cpp
        Tetris/TOption/TOptionManager.h
        SDLEasyGUI/Controller/Controll.cpp
        SDLEasyGUI/Controller/Controll.h
        SDLEasyGUI/Controller/StaticLabel.cpp
        SDLEasyGUI/Controller/StaticLabel.h
        SDLEasyGUI/Controller/Button.cpp
        SDLEasyGUI/Controller/Button.h
        SDLEasyGUI/Controller/ButtonBasic.cpp
        SDLEasyGUI/Controller/ButtonBasic.h
        SDLEasyGUI/Controller/RadioButton.cpp
        SDLEasyGUI/Controller/RadioButton.h
        SDLEasyGUI/Controller/EditLabel.cpp
        SDLEasyGUI/Controller/EditLabel.h
        SDLEasyGUI/Controller/GroupControllManager.cpp
        SDLEasyGUI/Controller/GroupControllManager.h
        GameInterface/Object/Player.cpp
        GameInterface/Object/Player.h
        GameInterface/Object/Room.cpp
        GameInterface/Object/Room.h
        GameInterface/Object/Atomic.h
        GameInterface/Object/Object.cpp
        GameInterface/Object/Object.h
        Tetris/TClient/TClientConnector.cpp
        Tetris/TClient/TClientConnector.h
        Tetris/TClient/TClientService.cpp
        Tetris/TClient/TClientService.h
        SDLEasyGUI/Controller/Border.cpp
        SDLEasyGUI/Controller/Border.h
        SDLEasyGUI/Windows/GraphicInterface.h
        Tetris/TObject/TPlayer.h
        Tetris/TObject/TPlayer.cpp Tetris/TFiguers/TFigureController.cpp Tetris/TFiguers/TFigureController.h)

include_directories(tetris_figure_class
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}
        Tetris/TDisplay
        Tetris/TFiguers
        ${PROJECT_SOURCE_DIR}/Common
        ${ACE_INCLUDE_DIR})

target_link_libraries(tetris_figure_class
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY}
        ${ACE_LIBRARIES}
        Threads::Threads)

