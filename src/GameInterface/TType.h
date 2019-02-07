

#if _MSC_VER >= 1200
  #pragma once
#endif


#include <cstddef>
#include <atomic>

#include <SDL2/SDL_stdinc.h>

#include "Tetris/Common/TDefine.h"
using namespace std;

SDL_TETRIS_BEGIN

using t_id = uint32_t ;
using t_id_atomic = std::atomic<t_id>;
using t_type = uint8_t ;
using t_age = uint16_t ;
using t_coord = int;         //unify this type with SDL2
using t_size = int;         //unify this type with SDL2
using t_color = Uint8;      //unify this type with SDL2
using t_unique = uint_fast16_t ;
using t_uniqueAtomic = atomic<t_unique>;
using t_eventType = unsigned int;
using t_port = unsigned short;
using t_res = unsigned int;

SDL_TETRIS_END