# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("UIClassExample")


set(CMAKE_CXX_STANDARD 11)
include_directories(UIClassExample)
add_executable(UIClassExamples
                UIClassExample/DisplayInterface.h
                UIClassExample/MainDisplay.h
                UIClassExample/MainLocalDisplay.h
                UIClassExample/TType.h UIClassExample/main.cpp UIClassExample/MainOnlineDisplay.h)