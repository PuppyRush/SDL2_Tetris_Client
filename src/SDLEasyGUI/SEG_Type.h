
#ifndef SDLEASYGUIDE_TTYPE_H
#define SDLEASYGUIDE_TTYPE_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include <cstddef>
#include <atomic>

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>


using t_type = std::uint8_t ;
using t_age = std::uint16_t ;
using t_unique = std::uint_fast16_t ;
using t_uniqueAtomic = std::atomic<t_unique>;
using t_eventType = unsigned int;
using t_port = unsigned short;
using t_res = unsigned int;
using t_cmd = unsigned int;
using t_display = unsigned short;

//unify typies with SDL2
using event_type = SDL_Event*;
using t_id = Uint32 ;
using t_id_atomic = std::atomic<t_id>;

using t_coord = int;
using t_size = int;
using t_color = Uint8;

#endif