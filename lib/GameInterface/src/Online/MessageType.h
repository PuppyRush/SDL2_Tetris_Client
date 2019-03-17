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

    WAITINGROOMS_INIT,

    WAITINGROOMS_REQUEST_INIT_INFO,
    WAITINGROOMS_INIT_INFO_ROOMS_PLAYERS,
    WAITINGROOMS_REQUEST_ENTER,
    WAITINGROOMS_REQUEST_CREATE,
    WAITINGROOMS_SEND_CHAT,
    WAITINGROOMS_RECV_CHAT,
    GAME_TETRISBOARD_INFO,

};

}


#endif //TETRIS_FIGURE_CLASS_MESSAGETYPE_H
