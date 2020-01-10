cmake_minimum_required(VERSION 3.12)
project(GameInterface)

message("----------------GameInterface START----------------")

find_package(jsoncpp CONFIG REQUIRED)
find_package(Boost 1.17.0)


include_directories(
        src
        SYSTEM
        ../../src
        .
		)


ADD_LIBRARY(GameInterface STATIC
        src/Online/JsonHelper.cpp
        src/Online/JsonHelper.h
        src/Online/PlayerConnector.cpp
        src/Online/PlayerService.cpp
        src/Online/PacketQueue.cpp
        src/Online/Packet.cpp
        src/Object/Player.cpp
        src/Object/Object.cpp
        src/Object/Room.cpp
        src/Object/GameRoom.cpp
        src/Object/WaitingRoom.cpp
        src/SubScription/ManagerController.cpp
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
		jsoncpp_lib
        #Threads::Threads
		)
