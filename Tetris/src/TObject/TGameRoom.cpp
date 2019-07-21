//
// Created by chaed on 19. 3. 23.
//

#include "TPlayer.h"
#include "GameInterface/include/Constant.h"
#include "TGameRoom.h"

SDL_TETRIS
using namespace std;
using namespace game_interface::packet;

void TGameRoom::postEnter(const GameRoom::player_ptr& ply)
{
    const auto tply = std::dynamic_pointer_cast<TPlayer>(ply);

    tply->initialize();
}

void TGameRoom::postExit(const GameRoom::player_ptr& ply)
{
    std::dynamic_pointer_cast<TPlayer>(ply)->endGame();
}

void TGameRoom::initialize()
{
    GameRoom::initialize();
}

void TGameRoom::destory()
{

    GameRoom::destory();
}

void TGameRoom::updateObserver(const Packet& packet)
{
    switch (packet.getHeader().message) {
        case game_interface::messageInfo::WAITINGROOMS_RESPONSE_CREATE:
            this->fromJson(packet.getPayload());
            break;
    }

}

void TGameRoom::fromJson(const Json::Value& json)
{
    GameRoom::fromJson(json);

    const size_t player_count = json["player_count"].asUInt();
    const auto roomJs = json[game_interface::NAME_GAMEROOM.data()];
    for (int i = 0; i < player_count; i++) {
        auto dummyPlayer = make_shared<TPlayer>();
        dummyPlayer->fromJson(roomJs[i]);
        if (!exist(dummyPlayer->getUnique())) {
            enter(dummyPlayer);
        }
    }
}