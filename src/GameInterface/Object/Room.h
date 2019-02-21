//
// Created by chaed on 19. 1. 16.
//

#ifndef OBJECT_ROOM_H
#define OBJECT_ROOM_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <string>
#include <vector>

#include "Object.h"
#include "Player.h"

namespace game_interface {

class Room final : public Object {
public:
    using player_ptr = std::shared_ptr<Player>;

    Room();

    virtual void enter(player_ptr ply) = 0;
    virtual void exit(player_ptr ply) = 0;

private:
    std::string m_roomname;
    t_id_atomic m_roomnumber;
    std::vector<player_ptr> m_players;
};

}

#endif //TETRIS_FIGURE_CLASS_TROOM_H
