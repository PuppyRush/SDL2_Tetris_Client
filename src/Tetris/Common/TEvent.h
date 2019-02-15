//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_EVENT_H
#define TETRIS_FIGURE_CLASS_EVENT_H

#include "THeader.h"

SDL_TETRIS

Uint32 my_callbackfunc(Uint32 interval, void *param) {

    SDL_UserEvent userevent;
    userevent.type = TETRIS_EVENT_FIGURETIMER;
    userevent.code = 0;

    SDL_Event event;
    event.type = TETRIS_EVENT_FIGURETIMER;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

#endif //TETRIS_FIGURE_CLASS_EVENT_H
