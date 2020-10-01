cmake_minimum_required(VERSION 3.12)
project(SDL2EasyGUI)

message("----------------SDL2EasyGUI START----------------")

SET(CMAKE_EXE_LINKER_FLAGS "-static")
SET(SDL2_LIBRARY ${VCPKG_PLATFORM}/lib)
SET(SDL2_INCLUDE_DIR ${VCPKG_PLATFORM}/include)
SET(SDL2_IMAGE_LIBRARY ${VCPKG_PLATFORM}/lib)
SET(SDL2_IMAGE_INCLUDE_DIR ${VCPKG_PLATFORM}/include)
SET(SDL2_TTF_LIBRARY ${VCPKG_PLATFORM}/lib)
SET(SDL2_TTF_INCLUDE_DIR ${VCPKG_PLATFORM}/include)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_gfx_LIBRARY ${VCPKG_PLATFORM}/lib)
set(ACE_LIBRARY ${VCPKG_PLATFORM}/lib)

message(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})

find_package(SDL2  REQUIRED)
find_package(sdl2-image  REQUIRED)
find_package(sdl2-ttf  REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Boost 1.68.0)
find_library(ace ACE_x64-windows-static REQUIRED)
#find_path(BOOST_INCLUDE_DIR boost)

include_directories(${BOOST_INCLUDE_DIR})
if (WIN32)
	set(BOOST_LIBRARIES ${BOOST_LIBRARY_DIRS}/boost_system-vc140-mt.lib)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(BOOST_LIBRARIES ${BOOST_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)
	endif()
endif()


include_directories(
		.
		src
        include
        lib
        SYSTEM
		sdl2gfx
        src/Command 
        src/Controller
        src/Display
        src/Subjector
        src/Windows
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
        src/Decorator/ScrollrableDecorator.h
        src/Decorator/ScrollrableDecorator.cpp
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
        )

target_link_libraries(
        ${PROJECT_NAME}
		PRIVATE SDL2::SDL2_gfx
		SDL2::SDL2
		SDL2::SDL2main
		SDL2::SDL2_image
		SDL2::SDL2_ttf
        "D:\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\debug\\lib\\ACEd.lib"
		#${SDL2_gfx_LIBRARY}
		${BOOST_LIBRARIES}
 )
