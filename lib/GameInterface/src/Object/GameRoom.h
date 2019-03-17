//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_GAMEROOM_H
#define TETRIS_FIGURE_CLASS_GAMEROOM_H

#include "Room.h"

namespace game_interface {

class GameRoom : public Room{
public:
    using unique_type = Room::unique_type ;
    using room_ptr = Room::room_ptr ;

    virtual void updateObserver(const Packet& ) =0;
    virtual Json::Value toJson() const override;

protected:
    virtual void postEnter(player_ptr ply) =0;
    virtual void postExit(const unique_type unique) =0;

};

}
#endif //TETRIS_FIGURE_CLASS_GAMEROOM_H
