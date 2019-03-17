//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_SUBJECTINTERFACE_H
#define SDL2_TETRIS_SERVER_SUBJECTINTERFACE_H

//
// Created by chaed on 19. 2. 16.
//

#include <condition_variable>
#include <mutex>
#include <memory>

#include "../Object/Object.h"
#include "Observer.h"

namespace game_interface {

class Observer;

template <class _Object, class _Container>
class Subject {
public:

    using element_type = _Object*;
    using container_type = _Container;
    using unique_type = typename _Object::unique_type;

    virtual ~Subject() {}

    void attach(element_type obs)
    {
        assert(!exist(obs->getUnique()));

        std::lock_guard<std::mutex> lock(m_objMutex);

        insert(obs);

        m_objCond.notify_one();

        postAttach(obs);
    }

    void detach(const unique_type unique) {
        assert(exist(unique));

        std::lock_guard<std::mutex> lock(m_objMutex);

        remove(unique);
        postDetach(unique);
    }

    inline container_type& getContainer() { return m_objects;}

    virtual bool exist(const unique_type unique) const = 0;
    virtual element_type at(const unique_type unique) = 0;

protected:

    Subject() {}

    inline const bool compare(const element_type& lhs, const element_type& rhs)
    {
        return lhs->getUnique() == rhs->getUnique();
    }

    virtual void postAttach(element_type ) = 0;
    virtual void postDetach(unique_type) = 0;
    virtual void insert(element_type obs) = 0 ;
    virtual void remove(const unique_type unique) = 0 ;

    container_type m_objects;
    std::condition_variable m_objCond;
    std::mutex m_objMutex;
};

}

#endif //SDL2_TETRIS_SERVER_SUBJECTINTERFACE_H
