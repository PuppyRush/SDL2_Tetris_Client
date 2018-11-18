cmake_minimum_required(VERSION 3.12)
project(SDL2_draw_example)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

find_package(SDL2 REQUIRED)

add_executable(SDL2_draw_example main.cpp)


include_directories(SDL2_draw_example
        ${SDL2_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(SDL2_draw_example
        ${SDL2_LIBRARY})