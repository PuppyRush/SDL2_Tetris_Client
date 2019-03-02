//
// Created by chaed on 19. 2. 19.
//

#ifndef TETRIS_FIGURE_CLASS_MESSAGETYPE_H
#define TETRIS_FIGURE_CLASS_MESSAGETYPE_H

#include "../Type.h"

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
    DUMMY_SIGNAL,
    PLAYER_INIT_INFO,
    WAITINGROOMS_INIT_INFO_ROOMS,
    WAITINGROOMS_INIT_INFO_PLAYERS,
    GAME_TETRISBOARD_INFO,
};

}


#endif //TETRIS_FIGURE_CLASS_MESSAGETYPE_H
