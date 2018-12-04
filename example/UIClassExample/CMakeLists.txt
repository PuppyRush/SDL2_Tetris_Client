# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project ("UIClassExample")


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

add_executable(UIClassExample
                DisplayInterface.h
                MainDisplay.h
                MainLocalDisplay.h
                TType.h
                main.cpp
                MainOnlineDisplay.h TDisplayController.cpp TDisplayController.h)

include_directories(UIClassExample
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(UIClassExample
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_LIBRARY})