//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_SUBJECT_H
#define TETRIS_FIGURE_CLASS_SUBJECT_H

#include "GameInterface/Type.h"
#include "GameInterface/Online/Packet.h"
#include "Object.h"

namespace game_interface {

//pre-declarcation
class Observer : public Object {
public:

    using unique_type = Object::unique_type ;

    Observer() = default;
    virtual ~Observer() = default;

    virtual void updateObserver(const Packet& ) = 0;

};

}

#endif //TETRIS_FIGURE_CLASS_SUBJECT_H
