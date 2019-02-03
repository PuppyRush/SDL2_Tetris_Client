//
// Created by chaed on 19. 1. 16.
//

#ifndef OBJECT_ROOM_H
#define OBJECT_ROOM_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <string>

#include "Object.h"

SDL_TETRIS_BEGIN

class Room final : public Object{


private:
    std::string m_roomname;
    t_id_atomic m_roomnumber;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TROOM_H
