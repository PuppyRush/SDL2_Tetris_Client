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

template <class _Observer>
class MapSubject : public SubjectInterface<_Observer, std::unordered_map<typename _Observer::unique_type, std::shared_ptr<_Observer>>>
{
public:

    using _Base = SubjectInterface<_Observer, std::unordered_map<t_unique, std::shared_ptr<_Observer>>>;
    using object_type = typename _Base::object_type ;
    using unique_type = typename _Base::unique_type;

    virtual ~MapSubject() {}
    virtual void notify() = 0;

protected:
    MapSubject() {}

    virtual void insert(object_type obs) override {
        _Base::m_objects.insert(std::make_pair(obs->getUnique(), obs));
    }

    virtual void remove(const unique_type unique){
        _Base::m_objects.erase(unique);
    }

    virtual bool exist(const unique_type unique) const {
        return _Base::m_objects.count(unique);
    }

    virtual object_type at(const unique_type unique) {
        if(exist(unique))
            return _Base::m_objects.at(unique);
        else
            return nullptr;
    }

};

}

#endif //TETRIS_FIGURE_CLASS_OBJECTOR_H
