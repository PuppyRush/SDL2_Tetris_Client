cmake_minimum_required(VERSION 3.8)
project(GameInterface)

message("----------------GameInterface START----------------")
message("Boost_LIBRARY_DIRS" ${Boost_LIBRARY_DIRS} )
message("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})


SET(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(jsoncpp CONFIG REQUIRED)
find_package(Boost 1.17.0)
find_path(BOOST_INCLUDE_DIR boost)

if (WIN32)
	set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/boost_system-vc140-mt.lib)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)
        set(BOOST_LIBRARIES ${Boost_LIBRARY_DIRS}/../debug/lib/boost_date_time-vc140-mt-gd.lib)
	endif()
endif()

#set(CMAKE_CXX_STANDARD 20)

#FILE(WRITE ${CMAKE_BINARY_DIR}/src/Tool/Timer "")

include_directories(
${BOOST_INCLUDE_DIR}
        .
        src
        SYSTEM
        include
		)


ADD_LIBRARY(GameInterface STATIC
        src/Online/PlayerConnector.cpp
        src/Online/PlayerService.cpp
        src/Online/PacketQueue.cpp
        src/Online/Packet.cpp
        src/Online/PacketCommander.h
        src/Object/Player.cpp
        src/Object/Object.cpp
        src/Object/Room.cpp
        src/Object/GameRoom.cpp
        src/Object/WaitingRoom.cpp
        src/SubScription/ManagerController.cpp
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/TimerBasic.h
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/TimerBasic.cpp
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/Countdown.cpp
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/ElapsedTimer.cpp
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/Scheduling.cpp
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/ScopeTimer.cpp
        ${PROJECT_SOURCE_DIR}/src/Tool/Time/Stopwatch.cpp
        include/Countdown.h
        include/ElapsedTimer.h
        include/Scheduling.h
        include/ScopeTimer.h
        include/Stopwatch.h
        include/Logger.h
        include/Subject.h
        include/Player.h
        include/Object.h
        include/Room.h
        include/Atomic.h
        include/GameRoom.h
        include/WaitingRoom.h
        include/Event.h
        include/TStruct.h
        include/Quit.h
        include/JsonPackage.h
        include/PlayerConnector.h
        include/PlayerService.h
        include/Observer.h
        include/VectorSubject.h
        include/ManagerController.h
        include/MapSubject.h
        include/MessageType.h
        include/Packet.h
        include/PacketQueue.h
        include/Times.h
        include/Date.h
        )


target_link_libraries(
        ${PROJECT_NAME}
		jsoncpp_lib
        ${BOOST_LIBRARIES}
        #Threads::Threads
		)
