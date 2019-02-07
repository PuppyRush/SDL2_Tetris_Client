cmake_minimum_required(VERSION 3.13)
project(jsoncpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include_directories("${JSONCPP_INCLUDE_DIRS}")
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

add_executable(jsoncpp main.cpp)
