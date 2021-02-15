cmake_minimum_required(VERSION 3.12)
project(SDL2EasyGUI)

message("----------------SDL2EasyGUI START----------------")


find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Boost 1.17.0)
find_path(BOOST_INCLUDE_DIR boost)

set(BOOST_INCLUDE_DIR "C:\\Users\\goodd\\source\\repos\\vcpkg-master\\vcpkg-master\\installed\\x64-windows\\include")


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
        ${BOOST_INCLUDE_DIR}
)


ADD_LIBRARY(SDL2EasyGUI STATIC
        src/Command/Commander.h
        src/Command/EventCommand.h
        src/Control/Border.cpp
        src/Control/Border.h
        src/Control/Button/Button.cpp
        src/Control/Button/ButtonBasic.cpp
        src/Control/Button/ButtonBasic.h
        src/Control/Box/ComboBox.cpp
        src/Control/Control.cpp
        src/Control/Control.h
        "src/Control/ControlBuilderBase.cpp"
        src/Control/Label/EditLabel.cpp
        src/Control/GroupControlManager.cpp
        src/Control/Box/ListBox.cpp
        src/Control/Button/RadioButton.cpp
        src/Control/Label/StaticLabel.cpp
        src/Control/ImageStatic.cpp
        src/Control/ImageStatic.h
        src/Control/Label/LabelBasic.cpp
        src/Control/Label/LabelBasic.h
        src/Control/Box/BoxBasic.cpp
        src/Control/Box/BoxBasic.h
        src/Control/Button/CheckBox.cpp
        src/Display/InputDialog.cpp
        src/Display/MessageDialog.cpp
        src/Windows/DisplayController.cpp
        src/Windows/DisplayInterface.cpp
        src/Windows/EventQueue.cpp
        src/Windows/GraphicInterface.h
        src/Windows/SEG_Window.cpp
        src/Windows/SEG_Event.cpp
        src/Windows/GraphicInterface.cpp
        src/Windows/EventListener.h
        src/Decorator/Decorator.h
        src/Decorator/ScrollbarDecorator.cpp
        src/Decorator/ScrollbarDecorator.h
        src/Decorator/BorderDecorator.h
        src/Decorator/BorderDecorator.cpp
        src/Decorator/ScrollrableDecorator.h
        src/Decorator/ScrollrableDecorator.cpp
        include/Button.h
        include/ComboBox.h
        "include/ControlBuilderBase.h"
        include/EditLabel.h
        include/GroupControlManager.h
        include/ListBox.h
        include/RadioButton.h
        include/StaticLabel.h
        include/InputDialog.h
        include/MessageDialog.h
        include/DisplayController.h
        include/DisplayInterface.h
        
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
         "src/Decorator/DecoratorInterface.h" "include/SEG_Atomic.h")

add_subdirectory(sdl2gfx)


target_link_libraries(
        ${PROJECT_NAME} PRIVATE  
		SDL2::SDL2
		SDL2::SDL2main
		SDL2::SDL2_image
		SDL2::SDL2_ttf
        SDL2_gfx
 )

 
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

message("----------------SDL2EasyGUI END----------------")
