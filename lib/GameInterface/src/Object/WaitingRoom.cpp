//
// Created by chaed on 19. 2. 8.
//
#include <string>

#include "WaitingRoom.h"

using namespace game_interface;
using namespace std;

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

    if(it == m_rooms.end())
    {
    }
    else
    {
        m_rooms.erase(it);
        postRemovedGameRoom(unique);
    }
}

const bool WaitingRoom::existGameRoom(const unique_type unique) const noexcept
{
    std::unique_lock<std::mutex>(m_roomMutex);

    auto it = std::find_if(begin(m_rooms), end(m_rooms), [unique](const room_ptr element)
    {
      return element->compareUnique(unique);
    });

    if(it != m_rooms.end())
    {
        return true;
    }
    else
    {
    }
}

Json::Value WaitingRoom::toJson() const
{
    auto root = Room::toJson();

    size_t i = 0;
    Json::Value room{Json::arrayValue}, player{Json::arrayValue};

    auto roomContainer = getGameRoomContiner();
    root["gameroom_count"] = static_cast<Json::UInt >(roomContainer.size());
    for (const auto &groom : roomContainer) {
        room.append(groom->toJson());
    }
    root[game_interface::NAME_GAMEROOM.data()] = room;


    auto playerContainer = getPlayerContainer();
    root["player_count"] = static_cast<Json::UInt >(playerContainer.size());
    for (const auto &ply : playerContainer) {
        player.append(ply->toJson());
    }
    root[game_interface::NAME_PLAYER.data()] = player;

    return root;
}

void WaitingRoom::fromJson(const Json::Value& json)
{
    Room::fromJson(json);
}
