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

class Room final : public Object
{

public:
    Room();

private:
    std::string m_roomname;
    tetris::t_id_atomic m_roomnumber;
};

#endif //TETRIS_FIGURE_CLASS_TROOM_H
