//
// Created by chaed on 19. 2. 8.
//

#ifndef SDL2EASYGUI_CONSTATNT_H
#define SDL2EASYGUI_CONSTATNT_H

#include <limits>

#include "SEG_Type.h"

namespace seg {

constexpr const char DEFAULT_FONT_NAME[] = "../resources/fonts/OpenSans-Bold.ttf";
constexpr const t_id NULL_WINDOW_ID = std::numeric_limits<t_id>::max();
constexpr const t_id NULL_ID = std::numeric_limits<t_id>::max();
constexpr const SDL_Event EMPTY_EVENT = {};
constexpr const t_timer NULL_TIMER_ID = 0;
constexpr const t_coord INVALID_COORD = std::numeric_limits<t_coord>::max();
constexpr const t_size INVALID_SIZE = std::numeric_limits<t_size>::max();
constexpr const  SDL_Point NULL_POINT = { std::numeric_limits<decltype(SDL_Point::x)>::max(), std::numeric_limits<decltype(SDL_Point::x)>::max() };

constexpr const t_size WINDOW_HEIGHT = 900;
constexpr const t_size WINDOW_WIDTH = 1000;
constexpr const t_id SUPER_WINDOWS_ID = 0;
constexpr const t_id START_DISPLAY_ID = 1;

}

#endif //SDL2EASYGUI_SEG_CONSTANT_H
