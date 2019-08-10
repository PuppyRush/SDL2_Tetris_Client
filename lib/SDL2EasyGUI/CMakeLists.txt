cmake_minimum_required(VERSION 3.12)
project(SDL2EasyGUI)

SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

#set(SDL2_PATH "${PROJECT_SOURCE_DIR}/S9DL")

set(Boost_INCLUDE_DIR /usr/include)
set(BOOST_SOURCE /usr/include)
set(Boost_LIBRARIES /usr/lib/x86_64-linux-gnu/)
set(sdl2gfx /usr/local/lib)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem serialization)
find_package(PkgConfig REQUIRED)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message("-- OK.")
else ()
    message(FATAL_ERROR "Threads not found.")
endif ()


include_directories(.)
include_directories(src)
include_directories(src/Command)
include_directories(src/Controller)
include_directories(src/Display)
include_directories(src/Subjector)
include_directories(src/Windows)

include_directories(
        ../
        include
        src
        lib
        SYSTEM ${Boost_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)

#configure_file("src/" "../SDL2_Tetris_Client/lib/SDL2EasyGUI" COPYONLY)


file(COPY DIRECTORY "src/"
        DESTINATION "include"
        FILES_MATCHING PATTERN "*.h"
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
        src/Decorator/ScrollrableDecorator.h src/Decorator/ScrollrableDecorator.cpp include/SEG_Debug.h)

target_link_libraries(
        SDL2EasyGUI
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY}
        /usr/local/lib/libSDL2_gfx.a
        Threads::Threads)
