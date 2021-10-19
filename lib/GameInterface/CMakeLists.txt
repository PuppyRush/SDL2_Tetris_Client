cmake_minimum_required(VERSION 3.12)
project(GameInterface)



message("----------------GameInterface START----------------")
message("BOOST_LIBRARY_DIRS" ${BOOST_LIBRARY_DIRS} )
message("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})

message("BOOST_INCLUDE_DIR:" ${BOOST_INCLUDE_DIR})


SET(CMAKE_EXE_LINKER_FLAGS "-static")
SET(ACE_LIBRARY  $ENV{VCPKG_ROOT}\\installed\\${PLATFORM}\\${CMAKE_BUILD_TYPE}\\lib\\ACEd.lib)
SET(ACE_INCLUDE_DIR ${VCPKG_PLATFORM}/include)

message("ACE_LIBRARY : " ${ACE_LIBRARY})

find_package(jsoncpp CONFIG REQUIRED)
find_package(Boost 1.17.0 REQUIRED)
find_path(BOOST_INCLUDE_DIR boost)
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")

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
        )

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE ${SIMPLEINI_INCLUDE_DIRS}
		PRIVATE jsoncpp_lib
        ${BOOST_LIBRARIES}
        ${ACE_LIBRARY}
		)



get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

message("----------------GameInterface END----------------")