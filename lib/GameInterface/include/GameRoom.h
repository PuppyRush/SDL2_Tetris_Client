//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_GAMEROOM_H
#define TETRIS_FIGURE_CLASS_GAMEROOM_H

#include "Room.h"

namespace game_interface {

class GameRoom : public Room
{
public:
    using unique_type = Room::unique_type;
    using room_ptr = Room::room_ptr;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json);

    virtual void updateObserver(const Packet&) = 0;

protected:

    virtual void postEnter(const player_ptr&) = 0;

    virtual void postExit(const player_ptr&) = 0;

};

}
#endif //TETRIS_FIGURE_CLASS_GAMEROOM_H
