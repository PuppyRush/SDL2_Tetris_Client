//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_GAMEROOM_H
#define TETRIS_FIGURE_CLASS_GAMEROOM_H

#include "Room.h"

namespace game_interface {

class GameRoom : public Room{

    virtual void updateObserver(const Observer &, const Packet ) override;

    virtual void enter(player_ptr ply) override;
    virtual void exit(player_ptr ply) override;
};

}
#endif //TETRIS_FIGURE_CLASS_GAMEROOM_H
