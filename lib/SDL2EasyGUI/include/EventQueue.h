//
// Created by chaed on 19. 2. 13.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTQUEUE_H
#define TETRIS_FIGURE_CLASS_EVENTQUEUE_H

#include <queue>
#include <condition_variable>
#include <atomic>

#include <SDL2/SDL.h>

#include "SDL2EasyGUI/include/SEG_Type.h"

namespace seg {

struct event_mover
{
    const event_type event = nullptr;

    explicit event_mover(const event_type event)
            : event(event)
    {};

    ~event_mover()
    {
        if (event->type >= 0x8000) {
            /*if(event->user.data1 != nullptr)
                delete event->user.data1;
            if(event->user.data2 != nullptr)
                delete event->user.data2;*/
        }
        if (event) {
            delete event;
        }
    }
};

template<class _Data>
class EventQueue
{

public:

    using data_ref = _Data&;
    using data_ptr = _Data*;

    const data_ptr const MUTABLE_VALUE = nullptr;

    EventQueue()
        : m_isContinue(true), MUTABLE_VALUE(new  _Data)
    {

    }

    ~EventQueue()
    {
        m_isContinue = false;

        std::lock_guard<std::mutex> lock(m_mutex);
        while (!m_eventQ.empty()) {
            auto e = m_eventQ.front();
            m_eventQ.pop();
        }

        if (MUTABLE_VALUE != nullptr)
            delete MUTABLE_VALUE;
    }

    void pushEvent(const data_ptr event)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_eventQ.push(event);
       // printf("push seq : %lu\n", m_seq);
        m_cond.notify_one();
    }

    const data_ptr popEvent()
    {
        /*if (m_eventQ.empty())
            return MUTABLE_VALUE;*/

        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [=]() { return !m_eventQ.empty() || !m_isContinue; });

        if (m_eventQ.empty() || !m_isContinue) {
            return MUTABLE_VALUE;
        }

        const auto msg = m_eventQ.front();
        m_eventQ.pop();
       // printf("pop seq : %lu\n", m_seq++);
        return msg;
    }

    static std::uint64_t m_seq;

private:
    std::queue<data_ptr> m_eventQ;
    std::condition_variable m_cond;
    std::mutex m_mutex;
    std::atomic_bool m_isContinue;
};

template<class _Data>
std::uint64_t EventQueue<_Data>::m_seq = 0;

}

#endif //TETRIS_FIGURE_CLASS_EVENTQUEUE_H
