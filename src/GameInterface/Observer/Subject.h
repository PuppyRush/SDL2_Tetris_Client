//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_OBJECTOR_H
#define TETRIS_FIGURE_CLASS_OBJECTOR_H

#include <unordered_map>
#include "../Object/Object.h"
#include "Observer.h"

namespace game_interface {

class Observer;
class Subject {
public:

    using container_type = std::unordered_map<t_unique, Observer *>;

    virtual ~Subject() {}

    virtual void attach(Observer *obs) {
        assert(m_objects.count(obs->getUnique()) == 0);

        std::lock_guard<std::mutex> lock(m_objMutex);

        m_objects.insert(std::make_pair(obs->getUnique(), obs));

        m_objCond.notify_one();
    }

    virtual void detach(Observer *obs) {
        assert(m_objects.count(obs->getUnique()) > 0);

        std::unique_lock<std::mutex> lock(m_objMutex);
        m_objCond.wait(lock, [=]() { return !m_objects.empty(); });

        m_objects.erase(obs->getUnique());
    }

    virtual void notify() = 0;

    inline const container_type &getContainer() {
        return m_objects;
    }

protected:
    Subject() {}

private:

    container_type m_objects;
    std::condition_variable m_objCond;
    std::mutex m_objMutex;
};

}

#endif //TETRIS_FIGURE_CLASS_OBJECTOR_H
