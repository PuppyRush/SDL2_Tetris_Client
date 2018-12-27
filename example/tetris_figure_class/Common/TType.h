#pragma once

#include <cstddef>
#include <atomic>

#include <SDL2/SDL_stdinc.h>

#include "TDefine.h"

SDL_TETRIS_BEGIN

using t_id = std::uint32_t ;
using t_id_atomic = std::atomic<t_id>;
using t_type = std::uint8_t ;
using t_age = std::uint16_t ;
using t_coord = int;         //unify this type with SDL2
using t_size = int;         //unify this type with SDL2
using t_color = Uint8;      //unify this type with SDL2


SDL_TETRIS_END