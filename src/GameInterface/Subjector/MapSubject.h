//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_OBJECTOR_H
#define TETRIS_FIGURE_CLASS_OBJECTOR_H

#include <unordered_map>

#include "SubjectInterface.h"
#include "../Object/Object.h"
#include "GameInterface/Object/Observer.h"

namespace game_interface {

class Observer;
class MapSubject : public SubjectInterface<t_unique, Observer, std::unordered_map<t_unique, std::shared_ptr<Observer>>>
{
public:

    virtual ~MapSubject() {}

    virtual void notify() = 0;

protected:
    MapSubject() {}

    virtual void insert(object_type obs) {
        m_objects.insert(std::make_pair(obs->getUnique(), obs));
    }

    virtual void remove(const unique_type unique){
        m_objects.erase(unique);
    }

    virtual bool exist(const unique_type unique) const {
        return m_objects.count(unique);
    }

    virtual object_type at(const unique_type unique) {
        if(exist(unique))
            return m_objects.at(unique);
        else
            return nullptr;
    }

private:

    std::condition_variable m_objCond;
    std::mutex m_objMutex;
};

}

#endif //TETRIS_FIGURE_CLASS_OBJECTOR_H
