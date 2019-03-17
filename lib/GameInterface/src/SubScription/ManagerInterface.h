//
// Created by chaed on 19. 3. 1.
//

#ifndef SDL2_TETRIS_SERVER_MANAGERINTERFACE_H
#define SDL2_TETRIS_SERVER_MANAGERINTERFACE_H

#include "Observer.h"

namespace game_interface {

class ManagerInterface : public Observer {

public:

    using unique_type = Observer::unique_type ;

    virtual void boradcast(game_interface::Packet &packet) =0;
    virtual void detach(unique_type obs) = 0;

};
}

#endif //SDL2_TETRIS_SERVER_MANAGERINTERFACE_H
