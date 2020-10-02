# CMakeList.txt : 최상위 CMake 프로젝트 파일, 전역 구성을 수행하고
# 여기에 하위 프로젝트를 포함합니다.
#
cmake_minimum_required (VERSION 3.8)

project ("EasyTimer")

message("----------------GameInterface START----------------")
message("Boost_LIBRARY_DIRS" ${Boost_LIBRARY_DIRS} )
message("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})

cmake_policy(SET CMP0079 NEW)

find_package(Boost 1.17.0)
find_path(BOOST_INCLUDE_DIR boost)


if (WIN32)
	set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/boost_system-vc140-mt.lib)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)
        set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/../debug/lib/boost_date_time-vc140-mt-gd.lib)
	endif()
endif()


include_directories(
${BOOST_INCLUDE_DIR}
		)

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
