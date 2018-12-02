cmake_minimum_required(VERSION 3.12)
project(teris_figure_class)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

find_package(SDL2 REQUIRED)


add_executable(teris_figure_class
        TMain.cpp
        TType.h
        TFigureL.h
        TFigureUnit.h
        TFigureUnit.cpp
        TFigureL.cpp
        TFigureL.h
        TFigureBuilder.h
        TFigure.cpp
        TBoardController.cpp
        TBoardController.h
        TFigureBoard.cpp
        TFigureBoard.h
        TProperty.h
        TypeTraits.h
        TFigureBuilder.cpp
        TFigureBoardBuilder.cpp
        TFigureBoardBuilder.h
        TFigureZ.cpp
        TFigureZ.h DevLib/RandomGenerator.cpp DevLib/RandomGenerator.h TDefine.h TFigureI.cpp TFigureI.h TFigureO.cpp TFigureO.h TFigureT.cpp TFigureT.h)

include_directories(teris_figure_class
        ${SDL2_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(teris_figure_class
        ${SDL2_LIBRARY})