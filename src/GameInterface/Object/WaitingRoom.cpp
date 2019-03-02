//
// Created by chaed on 19. 2. 8.
//

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
}
