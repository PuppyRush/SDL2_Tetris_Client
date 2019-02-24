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

class VectorSubject : public SubjectInterface<t_unique, Observer, std::vector<std::shared_ptr<Observer>>>
{
public:

    virtual ~VectorSubject() {}

    virtual void notify() = 0;

protected:
    VectorSubject() {}

    virtual void insert(object_type obs) {
        m_objects.emplace_back(obs);
    }

    virtual void remove(const unique_type unique) {
        const auto it = std::remove_if(begin(m_objects), end(m_objects), [unique](object_type element)
        {
          return unique == element->getUnique();
        });

        if(it != m_objects.end())
            m_objects.erase(it);
    }

    virtual bool exist(const unique_type unique) const
    {
        const auto cnt = std::count_if(begin(m_objects), end(m_objects), [unique](object_type element)
        {
          return unique == element->getUnique();
        });

        return cnt>0;
    }

    virtual object_type at(const unique_type unique) {
        const auto it = std::find_if(begin(m_objects), end(m_objects), [unique](object_type element)
        {
          return unique == element->getUnique();
        });

        if(it != m_objects.end())
            return *it;
        else
            nullptr;
    }


private:

    std::condition_variable m_objCond;
    std::mutex m_objMutex;
};

}


#endif //SDL2_TETRIS_SERVER_VECTORSUBJECT_H
