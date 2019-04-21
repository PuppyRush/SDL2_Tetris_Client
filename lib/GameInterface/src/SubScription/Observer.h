//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_SUBJECT_H
#define TETRIS_FIGURE_CLASS_SUBJECT_H

#include "GameInterface/include/Type.h"
#include "GameInterface/src/Online/Packet.h"
#include "GameInterface/include/Object.h"

namespace game_interface {

//pre-declarcation
class Observer : public Object {
public:

    using unique_type = Object::unique_type ;

    Observer() = default;
    virtual ~Observer() = default;

    virtual void updateObserver(const Packet& ) = 0;
    virtual Json::Value toJson() const = 0;
};

}

#endif //TETRIS_FIGURE_CLASS_SUBJECT_H
