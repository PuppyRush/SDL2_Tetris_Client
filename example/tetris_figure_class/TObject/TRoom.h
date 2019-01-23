//
// Created by chaed on 19. 1. 16.
//

#ifndef TETRIS_FIGURE_CLASS_TROOM_H
#define TETRIS_FIGURE_CLASS_TROOM_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <string>

#include "TObject.h"

SDL_TETRIS_BEGIN

class TRoom final : public TObject{


private:
    std::string m_roomname;
    t_id_atomic m_roomnumber;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TROOM_H
