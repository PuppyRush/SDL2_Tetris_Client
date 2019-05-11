//
// Created by chaed on 19. 5. 4.
//

#ifndef SDL2_TETIRS_CLIENT_INITIATOR_H
#define SDL2_TETIRS_CLIENT_INITIATOR_H

#include "Constant.h"
#include "PacketQueue.h"

namespace game_interface {

static void GameInterface_Init(bool isServer)
{
    g_isServer = isServer;

    if (isServer) {
        g_modulename = NAME_SERVER;
    } else {
        g_modulename = NAME_CLIENT;
    }

    PacketQueue::getInstance().run();
}

}

#endif //SDL2_TETIRS_CLIENT_INITIATOR_H
