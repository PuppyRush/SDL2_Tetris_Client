cmake_minimum_required(VERSION 3.12)
project(SDL2EasyGUI)

message("----------------SDL2EasyGUI START----------------")


SET(CMAKE_EXE_LINKER_FLAGS "-static")
#set(ACE_DIR "C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\share\\ace")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
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


set(CMAKE_CXX_STANDARD 17)

#find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)

include_directories(.)
include_directories(lib)
include_directories(src)
include_directories(src/Command)
include_directories(src/Controller)
include_directories(src/Display)
include_directories(src/Subjector)
include_directories(src/Windows)


include_directories(
		.
		src
        include
        lib
        SYSTEM
		sdl2gfx
)


ADD_LIBRARY(SDL2EasyGUI STATIC
        src/Command/Commander.h
        src/Command/EventCommand.h
        src/Controller/Border.cpp
        src/Controller/Border.h
        src/Controller/Button/Button.cpp
        src/Controller/Button/ButtonBasic.cpp
        src/Controller/Button/ButtonBasic.h
        src/Controller/Box/ComboBox.cpp
        src/Controller/Control.cpp
        src/Controller/Control.h
        src/Controller/ControlBuilder.cpp
        src/Controller/Label/EditLabel.cpp
        src/Controller/GroupControlManager.cpp
        src/Controller/Box/ListBox.cpp
        src/Controller/Button/RadioButton.cpp
        src/Controller/Label/StaticLabel.cpp
        src/Controller/ImageStatic.cpp
        src/Controller/ImageStatic.h
        src/Controller/Label/LabelBasic.cpp
        src/Controller/Label/LabelBasic.h
        src/Controller/Box/BoxBasic.cpp
        src/Controller/Box/BoxBasic.h
        src/Controller/Button/CheckBox.cpp
        src/Display/InputDialog.cpp
        src/Display/MessageDialog.cpp
        src/Windows/DisplayController.cpp
        src/Windows/DisplayInterface.cpp
        src/Windows/EventQueue.cpp
        src/Windows/GraphicInterface.h
        src/Windows/SEG_Window.cpp
        src/Windows/SEG_Event.cpp
        src/Windows/GraphicInterface.cpp
        src/Decorator/Decorator.h
        src/Decorator/ScrollbarDecorator.cpp
        src/Decorator/ScrollbarDecorator.h
        src/Decorator/BorderDecorator.h
        src/Decorator/BorderDecorator.cpp
        include/Button.h
        include/ComboBox.h
        include/ControlBuilder.h
        include/EditLabel.h
        include/GroupControlManager.h
        include/ListBox.h
        include/RadioButton.h
        include/StaticLabel.h
        include/InputDialog.h
        include/MessageDialog.h
        include/DisplayController.h
        include/DisplayInterface.h
        include/EventListener.h
        include/EventQueue.h
        include/SEG_Window.h
        include/SEG_Constant.h
        include/SEG_Event.h
        include/SEG_Initiator.h
        include/SEG_Property.h
        include/SEG_Quit.h
        include/SEG_Resource.h
        include/SEG_Struct.h
        include/SEG_Type.h
        include/SEG_TypeTraits.h
        include/SEG_Define.h
        include/CheckBox.h
        include/SEG_Drawer.h
        src/Decorator/ScrollrableDecorator.h
        src/Decorator/ScrollrableDecorator.cpp
        include/SEG_Logger.h
        include/SEG_Time.h)

target_link_libraries(
        ${PROJECT_NAME}
		
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2d.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2maind.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2_image.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2_ttf.lib"
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\SDL2_gfx.lib"
		#PRIVATE SDL2::SDL2 
		#SDL2::SDL2main
		#SDL2::SDL2_image
		#SDL2::SDL2_ttf
		"C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\ACEd.lib"
		${BOOST_LIBRARIES}
        #/usr/local/lib/libSDL2_gfx.a
 
 Threads::Threads)