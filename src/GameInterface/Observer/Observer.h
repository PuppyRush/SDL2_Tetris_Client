//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_SUBJECT_H
#define TETRIS_FIGURE_CLASS_SUBJECT_H

#include "../Type.h"
#include "../Online/Packet.h"
#include "../Object/Object.h"

namespace game_interface {

//pre-declarcation
class Subject;
class Observer : public Object {
public:
    Observer() = default;
    virtual ~Observer() {}

    virtual void updateObserver(const Observer &, const Packet &) = 0;

private:
    virtual void _update(const Observer &obs, const Packet &packet) {
        if (obs.compareUnique(this->getUnique()))
            updateObserver(obs, packet);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_SUBJECT_H
