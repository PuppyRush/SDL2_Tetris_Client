//
// Created by chaed on 19. 3. 23.
//

#include "TPlayer.h"
#include "GameInterface/include/Constant.h"
#include "TGameRoom.h"

SDL_TETRIS
using namespace std;

void TGameRoom::postEnter(player_ptr ply)
{

}

void TGameRoom::postExit(const unique_type unique)
{

}

void TGameRoom::updateObserver(const game_interface::Packet& packet)
{
    switch(packet.getHeader().message)
    {
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
    for(int i=0 ; i < player_count ; i++)
    {
        auto dummyPlayer = make_shared<TPlayer>();
        dummyPlayer->fromJson(roomJs[i]);
        if(!exist(dummyPlayer->getUnique()))
            enter(dummyPlayer);
    }
}