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
#include "GameInterface/Object/Observer.h"

namespace game_interface {

class Observer;

template <class _Unique, class _Object, class _Container>
class SubjectInterface : private boost::noncopyable{
public:

    using object_type = std::shared_ptr<_Object>;
    using unique_type = _Unique;
    using container_type = _Container;

    virtual ~SubjectInterface() {}

    void attach(object_type obs)
    {
        assert(!exist(obs->getUnique()));

        std::lock_guard<std::mutex> lock(m_objMutex);

        insert(obs);

        m_objCond.notify_one();

        postAttach(obs);
    }

    void detach(const unique_type unique) {
        assert(!exist(unique));

        std::unique_lock<std::mutex> lock(m_objMutex);
        m_objCond.wait(lock, [=]() { return !exist(unique); });

        remove(unique);
        postDetach(unique);
    }



protected:
    SubjectInterface() {}

    virtual void postAttach(object_type ) = 0;
    virtual void postDetach(unique_type) = 0;
    virtual void insert(object_type obs) = 0 ;
    virtual void remove(const unique_type unique) = 0 ;
    virtual bool exist(const unique_type unique) const = 0;
    virtual object_type at(const unique_type unique) = 0;

    container_type m_objects;
private:

    std::condition_variable m_objCond;
    std::mutex m_objMutex;
};

}

#endif //SDL2_TETRIS_SERVER_SUBJECTINTERFACE_H
