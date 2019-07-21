//
// Created by chaed on 19. 3. 13.
//

#include "TWaitingRoom.h"

SDL_TETRIS
using namespace game_interface;
using namespace game_interface::packet;

void TWaitingRoom::updateObserver(const Packet& packet)
{

}

void TWaitingRoom::postEnter(const WaitingRoom::player_ptr&)
{

}

void TWaitingRoom::postExit(const WaitingRoom::player_ptr&)
{

}

void TWaitingRoom::postAddedGameRoom(const room_ptr& room)
{

}

void TWaitingRoom::postRemovedGameRoom(const unique_type unique)
{

}

void TWaitingRoom::initialize()
{
    WaitingRoom::initialize();
}

void TWaitingRoom::destory()
{
    WaitingRoom::destory();
}