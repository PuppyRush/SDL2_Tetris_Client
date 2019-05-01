cmake_minimum_required(VERSION 3.12)
project(TetrisModule)

set(CMAKE_CXX_STANDARD 17)

set(ACE_LINK_FLAGS "${ACE_LINK_FLAGS}" CACHE INTERNAL "ace link flags")

find_package(PkgConfig REQUIRED)

file(GLOB CPP_FILES source/*.cpp
        CPP_HEADERS include/*.h)

#add_library(boost::serialization INTERFACE IMPORTED)

pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

########################################################################
##  general find

find_path(ACE_INCLUDE_DIR ace/ACE.h ${CMAKE_SOURCE_DIR}/../ACE_wrappers/ /usr/include /usr/local/include $ENV{ACE_ROOT} $ENV{ACE_ROOT}/include DOC "directory containing ace/*.h for ACE library")

find_library(ACE_LIBRARY NAMES ACE ace PATHS ${CMAKE_SOURCE_DIR}/../ACE_wrappers/lib/ /usr/lib /usr/local/lib $ENV{ACE_ROOT}/lib $ENV{ACE_ROOT} DOC "ACE library file"
        GameInterface
        SDL2EasyGUI)

########################################################################
## finished - now just set up flags and complain to user if necessary

include_directories(
        src
        GameInterface
        SDL2EasyGUI
        SYSTEM ${Boost_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src/SDLEasyGUI
        ${PROJECT_SOURCE_DIR}/src/Tetris
        ${ACE_INCLUDE_DIR})


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
        ${PROJECT_NAME}
        ${JSONCPP_LIBRARIES}
)

