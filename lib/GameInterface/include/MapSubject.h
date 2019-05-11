//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_OBJECTOR_H
#define TETRIS_FIGURE_CLASS_OBJECTOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <unordered_map>

#include "Subject.h"
#include "Object.h"
#include "Observer.h"

namespace game_interface {

class Observer;

template<class _Observer>
class MapSubject : public Subject<_Observer, std::unordered_map<typename _Observer::unique_type, std::shared_ptr<_Observer>>>
{
public:

    using _Base = Subject<_Observer, std::unordered_map<typename _Observer::unique_type, std::shared_ptr<_Observer>>>;
    using element_type = typename _Base::element_type;
    using unique_type = typename _Base::unique_type;

    virtual ~MapSubject()
    {}

    virtual void notify() = 0;

    virtual bool exist(const unique_type unique) const override
    {
        return _Base::m_objects.count(unique) != 0;
    }

    virtual element_type at(const unique_type unique) override
    {
        if (exist(unique)) {
            return _Base::m_objects.at(unique);
        } else {
            return nullptr;
        }
    }

protected:
    MapSubject()
    {}

    virtual void insert(const element_type& obs) override
    {
        _Base::m_objects.insert(std::make_pair(obs->getUnique(), obs));
    }

    virtual void remove(const unique_type unique)
    {
        _Base::m_objects.erase(unique);
    }

    virtual void postAttach(const element_type&) = 0;

    virtual void postDetach(const unique_type unique) = 0;

};

}

#endif //TETRIS_FIGURE_CLASS_OBJECTOR_H
