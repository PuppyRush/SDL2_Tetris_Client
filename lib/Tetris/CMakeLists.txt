cmake_minimum_required(VERSION 3.12)
project(TetrisModule)

message("----------------TetrisModule START----------------")

find_package(Boost 1.71.0)
find_path(BOOST_INCLUDE_DIR boost)

include_directories(
        src
        GameInterface
        SDL2EasyGUI
        SYSTEM
        ${BOOST_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src/SDLEasyGUI
        ${PROJECT_SOURCE_DIR}/src/Tetris
        )


ADD_LIBRARY(TetrisModule STATIC
        include/TFigureBoard.h
        include/TFigureBoardBuilder.h
        include/TFigureBuilder.h
        include/TFigureController.h
        include/TFigureInterface.h
        include/TFigures.h
        src/TFigures.cpp
        src/TFigureBoardBuilder.cpp
        src/TFigureBuilder.cpp
        src/TFigureController.cpp
        src/TFigureInterface.cpp
        src/TFigureUnit.cpp
        include/TFigureUnit.h
        )


target_link_libraries(	
		${PROJECT_NAME} PRIVATE
        ${BOOST_LIBRARIES}
)

