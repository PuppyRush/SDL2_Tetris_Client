//
// Created by chaed on 19. 2. 19.
//

#ifndef TETRIS_FIGURE_CLASS_MESSAGETYPE_H
#define TETRIS_FIGURE_CLASS_MESSAGETYPE_H

#if _MSC_VER >= 1200
#pragma once
#endif

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
    DUMMY_SIGNAL,
    PLAYER_INIT_INFO,

    WAITINGROOMS_GAMEROOM_INFO,
    WAITINGROOMS_REQUEST_INIT_INFO,
    WAITINGROOMS_RESPONSE_INIT_INFO,
    WAITINGROOMS_REQUEST_ENTER,
    WAITINGROOMS_RESPONSE_ENTER,
    WAITINGROOMS_REQUEST_CREATE,
    WAITINGROOMS_RESPONSE_CREATE,
    WAITINGROOMS_SEND_CHAT,
    WAITINGROOMS_RECV_CHAT,
    GAME_REQUEST_BOARDINFO,
    GAME_RESPONSE_BOARDINFO,

    DISCONNECT,
};

}

#endif //TETRIS_FIGURE_CLASS_MESSAGETYPE_H
