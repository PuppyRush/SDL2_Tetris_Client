//
// Created by chaed on 19. 2. 19.
//

#ifndef TETRIS_FIGURE_CLASS_MESSAGETYPE_H
#define TETRIS_FIGURE_CLASS_MESSAGETYPE_H

#include "Type.h"

namespace game_interface {

enum class messageDirection : t_type
{
    UNKOWN,
    CLIENT,
    SERVER,
};

enum class messgaeType : t_type
{
    Request,
    Response,
};

enum class messageInfo : t_type
{
    UNKWON,
    PLAYER_INIT_INFO,
    WAITING_ROOMS_INFO,
    GAME_TETRISBOARD_INFO,
};

}


#endif //TETRIS_FIGURE_CLASS_MESSAGETYPE_H
