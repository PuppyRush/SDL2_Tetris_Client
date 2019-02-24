//
// Created by chaed on 19. 1. 16.
//

#include "Room.h"

using namespace game_interface;

Room::Room()
: m_roomnumber(Atomic::newWaitingRoomNumber())
{}

void Room::setRoomname(const std::string& name)
{
    m_roomname = name;
}
