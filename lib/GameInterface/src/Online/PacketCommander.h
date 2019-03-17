//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_PACKETPROCESSOR_H
#define SDL2_TETRIS_SERVER_PACKETPROCESSOR_H

#include "PacketQueue.h"

namespace game_interface {

class PacketCommander
{
public:
    void requestInfo();
    void recvInitInfo(const Packet packet);

protected:



private:

    messageInfo  m_msgInfo;
    messageDirection  m_dir;

};

}

#endif //SDL2_TETRIS_SERVER_PACKETPROCESSOR_H
