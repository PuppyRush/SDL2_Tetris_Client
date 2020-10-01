//
// Created by chaed on 19. 2. 17.
//

#include "SEG_Event.h"
#include "SEG_Property.h"

namespace seg {
namespace event {

Uint32 timerCallback(Uint32 interval, void* param)
{

    SDL_UserEvent* myevent = reinterpret_cast<SDL_UserEvent*>(param);

    SDL_UserEvent userevent;
    userevent = *myevent;
    userevent.type = SEG_TIMER_EVENT;

    SDL_Event event;
    event.type = SEG_TIMER_EVENT;
    event.user = userevent;
    
    SDL_PushEvent(&event);
    return (interval);
}

}

}