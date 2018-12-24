cmake_minimum_required(VERSION 3.12)
project(tetris_figure_class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")
set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)

add_library(boost::serialization INTERFACE IMPORTED)


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
        TGame/TBoardController.cpp
        TGame/TBoardController.h
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
        TGame/TGameLocalDisplay.cpp
        TGame/TGameLocalDisplay.h
        TGame/TGameDisplay.cpp
        TGame/TGameDisplay.h
        TDisplay/TDisplayInterface.h
        TDisplay/TDisplayInterface.cpp
        TDisplay/TMenuBuilder.cpp
        TDisplay/TMenuBuilder.h
        TDisplay/TDisplayController.cpp
        TDisplay/TDisplayInterface.h
        TMain/TMainLocalDisplay.h
        TMain/TMainLocalDisplay.cpp
        TMain/TMainDisplay.h
        TMain/TMainDisplay.cpp
        TMain/TMainOnlineDisplay.h
        TMain/TMainOnlineDisplay.cpp
        TOption/TOptionDisplay.cpp
        TOption/TOptionDisplay.h TDisplay/TWindow.cpp TDisplay/TWindow.h)

include_directories(tetris_figure_class
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/TDisplay
        ${PROJECT_SOURCE_DIR}/TGame
        ${PROJECT_SOURCE_DIR}/Common)

target_link_libraries(tetris_figure_class
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY})

