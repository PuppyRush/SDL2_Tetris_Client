cmake_minimum_required(VERSION 3.11)


project(tetris_figure_class) 


MESSAGE ("====================Go CMake Info===============")
MESSAGE ( CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME} )
MESSAGE ( PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR} )
MESSAGE ( SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR} )
MESSAGE ( SDL2_IMAGE_INCLUDE_DIR: ${SDL2_IMAGE_INCLUDE_DIR} )
MESSAGE ( SDL2_TTF_INCLUDE_DIR: ${SDL2_TTF_INCLUDE_DIR} )
MESSAGE ( SDL2_DIR: ${SDL2_DIR} )
MESSAGE ( CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR} )
MESSAGE ("====================End CMake Info===============")



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

set(SDL2_PATH ${PROJECT_SOURCE_DIR}/SDL2)
set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SDL2)
set(SDL2_TTF_PATH ${PROJECT_SOURCE_DIR}/SDL2)
set(SDL2_IMAGE_PATH ${PROJECT_SOURCE_DIR}/SDL2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)



#find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)

#add_library(boost::serialization INTERFACE IMPORTED)



########################################################################
##  general find


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
        TGame/TGameLocalDisplay.cpp
        TGame/TGameLocalDisplay.h
        TGame/TGameDisplay.cpp
        TGame/TGameDisplay.h
        TDisplay/TDisplayInterface.h
        TDisplay/TDisplayInterface.cpp
        TDisplay/TDisplayController.cpp
        TDisplay/TDisplayInterface.h
        TDisplay/TWindow.cpp
        TDisplay/TWindow.h
        TMain/TMainLocalDisplay.h
        TMain/TMainLocalDisplay.cpp
        TMain/TMainDisplay.h
        TMain/TMainDisplay.cpp
        TMain/TMainOnlineDisplay.h
        TMain/TMainOnlineDisplay.cpp
        TOption/TOptionDisplay.cpp
        TOption/TOptionDisplay.h
        TOption/TOptionManager.cpp
        TOption/TOptionManager.h
        TControll/TControll.cpp
        TControll/TControll.h
        TControll/TStaticLabel.cpp
        TControll/TStaticLabel.h
        TControll/TButton.cpp
        TControll/TButton.h
        TControll/TButtonBasic.cpp
        TControll/TButtonBasic.h
        TControll/TRadioButton.cpp
        TControll/TRadioButton.h
        TControll/TEditLabel.cpp
        TControll/TEditLabel.h
        TControll/TGroupControllManager.cpp
        TControll/TGroupControllManager.h
		TControll/TControllBuilder.cpp
        TControll/TControllBuilder.h
        TObject/TPlayer.cpp
        TObject/TPlayer.h
        TObject/TRoom.cpp
        TObject/TRoom.h
        #TClient/TClientConnector.cpp
        #TClient/TClientConnector.h
        #TClient/TClientService.cpp
        #TClient/TClientService.h
		)

include_directories(tetris_figure_class
        SYSTEM
		#${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/TDisplay
        ${PROJECT_SOURCE_DIR}/TGame
        ${PROJECT_SOURCE_DIR}/Common
       )

target_link_libraries(tetris_figure_class
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
		${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        
        Threads::Threads)

