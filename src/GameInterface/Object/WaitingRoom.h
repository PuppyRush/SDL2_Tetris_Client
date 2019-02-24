//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_WAITINGROOM_H
#define TETRIS_FIGURE_CLASS_WAITINGROOM_H

#include "Room.h"

namespace game_interface {

class WaitingRoom : public Room {

    virtual void updateObserver(const Observer &, const Packet ) override;

    virtual void enter(player_ptr ply) override;
    virtual void exit(player_ptr ply) override;

};

}

#endif //TETRIS_FIGURE_CLASS_WAITINGROOM_H
