
#include <cstddef>
#include <atomic>

#include <SDL2/SDL_stdinc.h>

#include "TDefine.h"
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

SDL_TETRIS_END