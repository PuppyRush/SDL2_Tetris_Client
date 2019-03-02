//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_WAITINGROOM_H
#define TETRIS_FIGURE_CLASS_WAITINGROOM_H

#include "Room.h"
#include "GameRoom.h"

namespace game_interface {

class WaitingRoom : public Room {

public:
    using room_ptr = GameRoom::room_ptr ;
    using unique_type = GameRoom::unique_type ;

    virtual void updateObserver(const Packet& ) =0;
    virtual void addGameRoom(room_ptr room);
    virtual void removeGameRoom(const unique_type unique);

private:
    std::vector<room_ptr> m_rooms;
    std::mutex m_roomMutex;
};

}

#endif //TETRIS_FIGURE_CLASS_WAITINGROOM_H
