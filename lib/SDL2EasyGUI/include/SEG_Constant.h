//
// Created by chaed on 19. 2. 8.
//

#ifndef SDLEASYGUIDE_CONSTATNT_H
#define SDLEASYGUIDE_CONSTATNT_H

#include <limits>

#include "SEG_Type.h"

namespace seg {

constexpr const t_id NULL_WINDOW_ID = std::numeric_limits<t_id>::max();
constexpr const SDL_Event EMPTY_EVENT = {};
constexpr const t_timer NULL_TIMER_ID = 0;
constexpr const t_coord NULL_COORD = std::numeric_limits<t_coord>::max();;
const constexpr SDL_Point NULL_POINT = { NULL_COORD,NULL_COORD };

}

#endif //TETRIS_FIGURE_CLASS_SEG_CONSTANT_H
