//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_VECTORSUBJECT_H
#define SDL2_TETRIS_SERVER_VECTORSUBJECT_H

//
// Created by chaed on 19. 2. 16.
//

#include <vector>
#include <algorithm>

#include "SubjectInterface.h"
#include "../Object/Object.h"
#include "GameInterface/Object/Observer.h"

namespace game_interface {

template <class _Observer>
class VectorSubject : public SubjectInterface<_Observer, std::vector<std::shared_ptr<_Observer>>>
{
public:

    using _Base = SubjectInterface<_Observer, std::vector<std::shared_ptr<_Observer>>>;
    using object_type = typename _Base::object_type ;
    using unique_type = typename _Base::unique_type;

    virtual ~VectorSubject() {}

    virtual void notify() = 0;

protected:
    VectorSubject() {}

    virtual void insert(object_type obs) override {
        _Base::m_objects.emplace_back(obs);
    }

    virtual void remove(const unique_type unique) override {
        const auto it = std::remove_if(begin(_Base::m_objects), end(_Base::m_objects), [unique]( object_type element)
        {
          return element->compareUnique(unique);
        });

        if(it != _Base::m_objects.end())
            _Base::m_objects.erase(it);
    }

    virtual bool exist(const unique_type unique) const
    {
        const auto cnt = std::count_if(begin(_Base::m_objects), end(_Base::m_objects), [unique]( object_type element)
        {
          return element->compareUnique(unique);
        });

        return cnt>0;
    }

    virtual object_type at(const  unique_type unique) override {
        const auto it = std::find_if(begin(_Base::m_objects), end(_Base::m_objects), [unique]( object_type element)
        {
          return element->compareUnique(unique);
        });

        if(it != _Base::m_objects.end())
            return *it;
        else
            nullptr;
    }
};

}


#endif //SDL2_TETRIS_SERVER_VECTORSUBJECT_H
