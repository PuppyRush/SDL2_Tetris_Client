//
// Created by chaed on 19. 2. 8.
//

#ifndef GAMEINTERFACE_CONSTATNT_H
#define GAMEINTERFACE_CONSTATNT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <string_view>
#include <limits>
#include <boost/chrono/ceil.hpp>

#include "Configcpp.h"
#include "Type.h"
#include <string_view>

#undef max

namespace game_interface {

#ifdef _CONSTANCE_VERSION_V1_
inline
#endif
namespace _V1 {

__inline__ bool g_isServer = false;
__inline__ std::string_view g_modulename;

constexpr const size_t ROOM_FULLCOUNT = 7;
constexpr const t_id NULL_ID = std::numeric_limits<t_id>::max();
constexpr const std::uint8_t CLIENT_ATOMIC_BITCOUNT = 3;
constexpr const t_id SERVER_ATOMIC_START = 1 << 3;

constexpr const std::string_view NAME_SERVER = std::string_view("server");
constexpr const std::string_view NAME_CLIENT = std::string_view("client");

constexpr const std::string_view NAME_PLAYER = std::string_view("player");
constexpr const std::string_view NAME_GAMEROOM = std::string_view("game_room");
constexpr const std::string_view NAME_WAITINGROOM = std::string_view("waiting_room");
constexpr const std::string_view NAME_FIGURE = std::string_view("figure");
constexpr const std::string_view NAME_CHATINFO = std::string_view("chatinfo");

constexpr const std::string_view NAME_NULL = std::string_view("");

}
}

#endif //TETRIS_FIGURE_CLASS_SEG_CONSTANT_H


