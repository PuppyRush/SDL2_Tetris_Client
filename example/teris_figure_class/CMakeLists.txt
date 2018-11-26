cmake_minimum_required(VERSION 3.12)
project(teris_figure_class)

set(CMAKE_CXX_STANDARD 17)


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
        TProperty.h TFigureLBuilder.cpp TFigureLBuilder.h TypeTraits.h TFigureBuilder.cpp TFigureBoardBuilder.cpp TFigureBoardBuilder.h)

