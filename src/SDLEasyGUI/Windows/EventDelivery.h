//
// Created by chaed on 19. 2. 13.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTDELIVERY_H
#define TETRIS_FIGURE_CLASS_EVENTDELIVERY_H

#include "GameInterface/Type.h"
#include "../SEG_Constant.h"
#include "EventQueue.h"
#include "EventListener.h"

class EventDelivery : public EventQueue
{
public:

    bool receiveEvent(const game_interface::t_id id, event_type event)
    {
        if(id == NULL_WINDOW_ID || validId(id)) {
            pushEvent(event);
            return true;
        }
        else
            return false;
    }

private:

    virtual bool validId(const game_interface::t_id id) = 0;

};

#endif //TETRIS_FIGURE_CLASS_EVENTDELIVERY_H
