cmake_minimum_required(VERSION 3.12)
project(SDL2_draw_example)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/SDL")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(SDL2_draw_3d main.cpp)


include_directories(SDL2_draw_3d
        ${SDL2_INCLUDE_DIR}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(SDL2_draw_3d
        ${SDL2_LIBRARY})