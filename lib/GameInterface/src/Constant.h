//
// Created by chaed on 19. 2. 8.
//

#ifndef GAMEINTERFACE_CONSTATNT_H
#define GAMEINTERFACE_CONSTATNT_H

#include <string_view>
#include <limits>

#include "Type.h"

namespace game_interface {

constexpr const t_id NULL_ID = std::numeric_limits<t_id>::max();
constexpr const std::uint8_t CLIENT_ATOMIC_BITCOUNT = 3;
constexpr const t_id SERVER_ATOMIC_START = 1 << 3;

constexpr const std::string_view NAME_PLAYER = std::string_view("player");
constexpr const std::string_view NAME_GAMEROOM = std::string_view("game_room");
constexpr const std::string_view NAME_WAITINGROOM = std::string_view("waiting_room");

}

#endif //TETRIS_FIGURE_CLASS_SEG_CONSTANT_H


