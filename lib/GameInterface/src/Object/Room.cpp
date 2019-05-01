//
// Created by chaed on 19. 1. 16.
//

#include <algorithm>
#include <cassert>

#include "GameInterface/include/Room.h"

using namespace game_interface;

Room::Room()
        : m_roomnumber(Atomic::newWaitingRoomNumber())
{}

void Room::initialize()
{

}

void Room::destory()
{

}

void Room::setRoomName(const std::string& name)
{
    m_roomname = name;
}

void Room::enter(player_ptr ply)
{
    if (!m_players.empty() && (m_players.size() - 1 >= m_fullCount)) {
        assert(0);
        return;
    }

    std::unique_lock<std::mutex>(m_mutex);

    auto it = std::find_if(begin(m_players), end(m_players), [ply](const player_ptr element) {
        return ply->compareUnique(element->getUnique());
    });

    if (it == m_players.end()) {
        m_players.push_back(ply);
        postEnter(ply);
    } else {
        assert(0);
    }
}

void Room::exit(const unique_type unique)
{
    std::unique_lock<std::mutex>(m_mutex);

    auto it = std::find_if(begin(m_players), end(m_players), [unique](const player_ptr element) {
        return element->compareUnique(unique);
    });

    if (it == m_players.end()) {
    } else {
        postExit(*it);
        m_players.erase(it);
    }

    if (m_players.empty()) {
        destory();
    }
}

bool Room::exist(const unique_type unique) const noexcept
{
    std::unique_lock<std::mutex>(m_mutex);

    auto it = std::find_if(begin(m_players), end(m_players), [unique](const player_ptr element) {
        return element->compareUnique(unique);
    });

    if (it == m_players.end()) {
    } else {
        return true;
    }
}

Json::Value Room::toJson() const
{
    auto json = Object::toJson();
    json["name"] = getRoomName();
    json["number"] = getRoomNumber();

    return json;
}

void Room::fromJson(const Json::Value& json)
{
    setRoomName(json["name"].asString());
    setRoomNumber(json["number"].asUInt64());
    Object::fromJson(json);
}