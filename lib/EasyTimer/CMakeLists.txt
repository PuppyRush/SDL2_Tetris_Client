# CMakeList.txt : 최상위 CMake 프로젝트 파일, 전역 구성을 수행하고
# 여기에 하위 프로젝트를 포함합니다.
#
cmake_minimum_required (VERSION 3.8)

project ("EasyTimer")

message("----------------EasyTimer START----------------")

message("Boost_LIBRARY_DIRS" ${Boost_LIBRARY_DIRS} )
message("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})

cmake_policy(SET CMP0079 NEW)

ADD_LIBRARY (EasyTimer STATIC
                EasyTimer.cpp 
                Countdown.h
                Date.h
                ElapsedTimer.h
                Scheduling.h
                ScopeTimer.h
                Stopwatch.h
                Times.h
                )



target_link_libraries(
        ${PROJECT_NAME}
        ${BOOST_LIBRARIES}
		)


message("----------------EasyTimer END----------------")