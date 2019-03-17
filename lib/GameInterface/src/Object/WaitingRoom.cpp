//
// Created by chaed on 19. 2. 8.
//
#include <string>

#include "WaitingRoom.h"

using namespace game_interface;


void WaitingRoom::updateObserver(const Packet& )
{}

void WaitingRoom::addGameRoom(room_ptr room)
{
    std::unique_lock<std::mutex>(m_roomMutex);

    auto it = std::find_if(begin(m_rooms), end(m_rooms), [room](const room_ptr element)
    {
      return room->compareUnique(element->getUnique());
    });

    if(it == m_rooms.end())
    {
        m_rooms.push_back(room);
        postAddedGameRoom(room);
    }
    else
    {
        assert(0);
    }
}

void WaitingRoom::removeGameRoom(const unique_type unique)
{
    std::unique_lock<std::mutex>(m_roomMutex);

    auto it = std::remove_if(begin(m_rooms), end(m_rooms), [unique](const room_ptr element)
    {
      return element->compareUnique(unique);
    });

    if(it != m_rooms.end())
    {
        assert(0);
    }
    else
    {
        postRemovedGameRoom(unique);
    }
}

Json::Value WaitingRoom::toJson() const
{
    auto root = Room::toJson();

    auto roomContainer = getGameRoomContiner();
    auto playerContainer = getPlayerContainer();

    size_t i = 0;
    Json::Value room,player;

    room["gameroom_count"] = static_cast<Json::UInt >(roomContainer.size());
    for (const auto &groom : roomContainer) {

        Json::Value jsonroom;
        jsonroom.append(groom->toJson());

        std::string name = groom->getUniqueName().data();
        name += std::to_string(i);
        room[name.c_str()] = jsonroom;
        i++;
    }
    root["room"] = room;


    room["player_count"] = static_cast<Json::UInt >(playerContainer.size());
    for (const auto &ply : playerContainer) {

        Json::Value jsonroom;
        jsonroom.append(ply->toJson());

        std::string name = ply->getUniqueName().data();
        name += std::to_string(i);
        room[name.c_str()] = jsonroom;
        i++;
    }

    return root;
}

