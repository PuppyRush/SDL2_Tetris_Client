//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_EVENT_H
#define TETRIS_FIGURE_CLASS_EVENT_H

#include <cassert>
#include <type_traits>

#include <SDL2/SDL.h>

#include "SEG_Type.h"

//must call by TimerAdder
Uint32 timerCallback(Uint32 interval, void *param) ;

class TimerAdder
{
public:

    TimerAdder(const Uint32 interval, const t_eventType event)
    :m_interval(interval), m_eventType(event)
    {
        m_userEvent.type = event;
    }

    inline TimerAdder* windowsId(const t_id id)
    {
        this->m_userEvent.windowID = id;
        return this;
    }

    inline TimerAdder* timestamp(const Uint32 time)
    {
        this->m_userEvent.timestamp = time;
        return this;
    }

    inline TimerAdder* data1(void* data)
    {
        this->m_userEvent.data1 = data;
        return this;
    }

    inline TimerAdder* data2(void* data)
    {
        this->m_userEvent.data2 = data;
        return this;
    }

    const t_timer addTimer() {
        return SDL_AddTimer(m_interval, timerCallback, &m_userEvent);
    }

private:

    const t_eventType m_eventType;
    const Uint32 m_interval;
    SDL_UserEvent m_userEvent;
};


#endif //TETRIS_FIGURE_CLASS_EVENT_H
