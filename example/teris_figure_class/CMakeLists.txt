cmake_minimum_required(VERSION 3.12)
project(teris_figure_class)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

add_executable(teris_figure_class
        Common/TType.h
        Common/TProperty.h
        Common/TypeTraits.h
        Common/TDefine.h
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
        TDisplay/MainLocalDisplay.h
        TDisplay/MainDisplay.h
        TDisplay/DisplayInterface.h
        TDisplay/TDisplayMain.h
        TDisplay/MainOnlineDisplay.h
        TDisplay/TDisplayController.cpp
        TDisplay/TDisplayController.h
        Main.cpp TGame/TGameMain.h TController.cpp TController.h TGame/TGameController.cpp TGame/TGameController.h)

include_directories(teris_figure_class
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/TDisplay
        ${PROJECT_SOURCE_DIR}/TGame
        ${PROJECT_SOURCE_DIR}/Common)

target_link_libraries(teris_figure_class
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY})