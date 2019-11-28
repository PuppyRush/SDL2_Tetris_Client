cmake_minimum_required(VERSION 3.12)
project(TetrisModule)

message("----------------TetrisModule START----------------")

set(ACE_DIR "C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\share\\ace")


find_package(Boost 1.17.0)
#find_package(ACE)

find_path(BOOST_INCLUDE_DIR boost)

include_directories(${BOOST_INCLUDE_DIR})
if (WIN32)
	set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/boost_system-vc140-mt.lib)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)
	endif()
endif()


include_directories(
        src
        GameInterface
        SDL2EasyGUI
        SYSTEM
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

		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2d.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2maind.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2_image.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2_ttf.lib"

		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2_gfx.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\ACEd.lib"		
)

