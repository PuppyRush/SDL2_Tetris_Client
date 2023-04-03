cmake_minimum_required(VERSION 3.20)
project(SDL2EasyGUI)

message("----------------SDL2EasyGUI START----------------")

#set(CMAKE_FIND_DEBUG_MODE 1)

#set(SDL2_DIR "D:\\sources\\vcpkg\\installed\\x64-windows\\share\\sdl2")
#set(sdl2-image_DIR "D:\\sources\\vcpkg\\installed\\x64-windows\\share\\SDL2_image")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2_image CONFIG REQUIRED)
find_package(sdl2_ttf CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

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
        src/Control/Control.cpp
        src/Control/Control.h
        src/Control/Button/Button.cpp
        src/Control/Button/ButtonBasic.cpp
        src/Control/Button/ButtonBasic.h
        src/Control/Button/RadioButton.cpp
        src/Control/Button/CheckBox.cpp
        src/Control/ControlBuilderBase.cpp
        src/Control/GroupControlManager.cpp
        src/Control/ImageStatic.cpp
        src/Control/ImageStatic.h
        src/Control/Label/EditLabel.cpp
        src/Control/Label/StaticLabel.cpp
        src/Control/Label/LabelBasic.cpp
        src/Control/Label/LabelBasic.h
        src/Control/Box/ComboBox.cpp
        src/Control/Box/ListBox.cpp
        src/Control/Box/BoxItem.cpp
        src/Control/Box/BoxBasic.cpp
        src/Control/Box/BoxBasic.h
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
        src/Decorator/DecoratorInterface.h
        src/SEG_Tree.cpp
        src/GraphicComponent.h
        src/GraphicComponent.cpp
        include/Button.h
        include/ComboBox.h
        include/ControlBuilderBase.h
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
        include/SEG_Atomic.h
        include/SEG_Tree.h
        include/BoxItem.h
        )

target_link_libraries(
        ${PROJECT_NAME} PRIVATE  
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
		$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
		$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        SDL2::SDL2_gfx
 )

 
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

message("----------------SDL2EasyGUI END----------------")
