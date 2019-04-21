
#ifndef GAMEINTERFACE_TTYPE_H
#define GAMEINTERFACE_TTYPE_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <cstddef>
#include <atomic>
#include <ctime>

namespace game_interface {
using t_type = uint8_t;
using t_unique = uint_fast16_t;
using t_uniqueAtomic = std::atomic<t_unique>;
using t_res = unsigned int;
using t_cmd = unsigned int;
using t_display = unsigned short;

using t_id = uint32_t;
using t_id_atomic = std::atomic<t_id>;

using t_time = std::time_t;
using t_coord = int;
using t_size = int;
using t_color = uint8_t;
using t_age = uint16_t;
using t_port = unsigned short;

}
#endif