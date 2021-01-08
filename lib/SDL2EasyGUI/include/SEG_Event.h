//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_EVENT_H
#define TETRIS_FIGURE_CLASS_EVENT_H

#include <cassert>
#include <type_traits>

#include <SDL2/SDL.h>

#include "SEG_Constant.h"
#include "SEG_Struct.h"
#include "SEG_TypeTraits.h"
#include "SEG_Resource.h"

namespace seg {
namespace event {

typedef struct SEG_Click
{
    SEG_Point point = { INVALID_COORD, INVALID_COORD };
    t_id resourceId = toUType(resource::NONE);
    bool selected = false;

    SEG_Click(const SEG_Point& point, const t_id& res, const bool sel)
            : point(point), resourceId(res), selected(sel)
    {}

} SEG_Click;

//must call by TimerAdder
Uint32 timerCallback(Uint32 interval, void* param);

typedef struct SEG_UserEventData
{
    bool isDisplay = true; // display or control
    t_id controlId = seg::NULL_WINDOW_ID;
    t_timer timerId = seg::NULL_TIMER_ID;
}SEG_UserEventData;

class SEG_Timer final
{
public:

    SEG_Timer(const t_id id, const Uint32 interval)
            : m_interval(interval), m_id(id), m_userData(new SEG_UserEventData{})
    {
        m_userEvent.data1 = static_cast<void*>(m_userData);
        m_userEvent.data2 = nullptr;
    }

    ~SEG_Timer()
    {
        if(m_userData)
            delete m_userData;

        SDL_RemoveTimer(m_timerId);
    }

    inline SEG_Timer* timestamp(const Uint32 time)
    {
        this->m_userEvent.timestamp = time;
        return this;
    }

    
    inline SEG_Timer* userEventData(SEG_UserEventData data)
    {
        *static_cast<SEG_UserEventData*>(this->m_userEvent.data1) = data;
        return this;
    }

    template <typename T>
    inline SEG_Timer* data(T* data)
    {
        this->m_userEvent.data2 = static_cast<void*>(data);
        return this;
    }

    bool isStarted() const noexcept
    {
        return m_isStarted;
    }

    t_id getTimerId() const noexcept
    {
        return m_timerId;
    }

    t_timer start()
    {
        if (m_isStarted)
        {
            return NULL_TIMER_ID;
        }

        m_userEvent.timestamp = SDL_GetTicks();
        m_userEvent.windowID = m_id;
        m_timerId = SDL_AddTimer(m_interval, timerCallback, &m_userEvent);
        m_userData->timerId = m_timerId;
        if (m_timerId != 0)
        {
            m_isStarted = true;
        }
        return m_timerId;
    }

    void stop()
    {
        SDL_RemoveTimer(m_timerId);
        m_isStarted = false;
        m_timerId = NULL_TIMER_ID;
    }



private:

    const Uint32 m_interval;
    SDL_UserEvent m_userEvent;
    SEG_UserEventData* m_userData;
    t_timer m_timerId;
    t_id m_id = NULL_TIMER_ID;
    bool m_isStarted = false;
};



class EventPusher
{
public:

    EventPusher(const t_id winid, const t_eventType type, const t_eventType event)
        :m_userData(new SEG_UserEventData{})
    {
        m_user.data1 = static_cast<void*>(m_userData);
        m_user.type = type;
        m_user.windowID = winid;
        m_user.code = event;
        m_event.type = type;
    }

    ~EventPusher()
    {
        //data1 ¾î¶»°Ô delete?
    }

    void setIsControl(bool b)
    {
        m_userData->isDisplay = b;
    }

    void setTargetId(t_eventType tid)
    {
        m_userData->controlId = tid;
    }


    template<class T>
    void setUserData(T* data)
    {
        m_user.data2 = static_cast<void*>(data);
    }

    void pushEvent()
    {
        m_user.timestamp = SDL_GetTicks();
        m_event.user = m_user;
        SDL_PushEvent(&m_event);
    }

private:

    EventPusher()
    {
        m_user.data1 = nullptr;
        m_user.data2 = nullptr;
    }

    SDL_Event m_event;
    SDL_UserEvent m_user;
    SEG_UserEventData* m_userData;
};

}

}

#endif //TETRIS_FIGURE_CLASS_EVENT_H
