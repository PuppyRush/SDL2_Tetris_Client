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
        Main.cpp
        Common/TType.h
        Common/TProperty.h
        Common/TypeTraits.h
        Common/TDefine.h
        Common/THeader.h
        Common/TStruct.h
        TGame/TFigureL.h
        TGame/TFigureUnit.h
        TGame/TFigureUnit.cpp
        TGame/TFigureL.cpp
        TGame/TFigureL.h
        TGame/TFigureBuilder.h
        TGame/TFigure.cpp
        TGame/TFigureBoard.cpp
        TGame/TFigureBoard.h
        TGame/TFigureBuilder.cpp
        TGame/TFigureBoardBuilder.cpp
        TGame/TFigureBoardBuilder.h
        TGame/TFigureZ.cpp
        TGame/TFigureZ.h
        TGame/TFigureI.cpp
        TGame/TFigureI.h
        TGame/TFigureO.cpp
        TGame/TFigureO.h
        TGame/TFigureT.cpp
        TGame/TFigureT.h
        TGame/TScore.cpp
        TGame/TScore.h
        TDisplay/TGameLocalDisplay.cpp
        TDisplay/TGameLocalDisplay.h
        TDisplay/TGameDisplay.cpp
        TDisplay/TGameDisplay.h
        Interface/Controller/ControllBuilder.cpp
        Interface/Controller/ControllBuilder.h
        Interface/GUI/DisplayInterface.h
        Interface/GUI/DisplayInterface.cpp
        Interface/GUI/DisplayController.cpp
        Interface/GUI/DisplayInterface.h
        Interface/GUI/Window.cpp
        Interface/GUI/Window.h
        TMain/TMainLocalDisplay.h
        TMain/TMainLocalDisplay.cpp
        TMain/TMainDisplay.h
        TMain/TMainDisplay.cpp
        TMain/TMainOnlineDisplay.h
        TMain/TMainOnlineDisplay.cpp
        TDisplay/TOptionDisplay.cpp
        TDisplay/TOptionDisplay.h
        TOption/TOptionManager.cpp
        TOption/TOptionManager.h
        Interface/Controller/Controll.cpp
        Interface/Controller/Controll.h
        Interface/Controller/StaticLabel.cpp
        Interface/Controller/StaticLabel.h
        Interface/Controller/Button.cpp
        Interface/Controller/Button.h
        Interface/Controller/ButtonBasic.cpp
        Interface/Controller/ButtonBasic.h
        Interface/Controller/RadioButton.cpp
        Interface/Controller/RadioButton.h
        Interface/Controller/EditLabel.cpp
        Interface/Controller/EditLabel.h
        Interface/Controller/GroupControllManager.cpp
        Interface/Controller/GroupControllManager.h
        Interface/Object/Player.cpp
        Interface/Object/Player.h
        Interface/Object/Room.cpp
        Interface/Object/Room.h
        Interface/Object/Atomic.h
        Interface/Object/Object.cpp
        Interface/Object/Object.h
        TClient/TClientConnector.cpp
        TClient/TClientConnector.h
        TClient/TClientService.cpp
        TClient/TClientService.h
        Interface/Controller/Border.cpp
        Interface/Controller/Border.h
        Interface/GUI/GraphicInterface.h
        TObject/TPlayer.h
        TObject/TPlayer.cpp)

include_directories(tetris_figure_class
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/TDisplay
        ${PROJECT_SOURCE_DIR}/TGame
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

