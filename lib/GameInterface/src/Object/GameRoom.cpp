//
// Created by chaed on 19. 2. 8.
//

#include <string>

#include "GameRoom.h"

using namespace game_interface;
using namespace std;

void GameRoom::updateObserver(const Packet& )
{}

Json::Value GameRoom::toJson() const {

    auto json = Room::toJson();

    const auto& container = getPlayerContainer();
    Json::Value root, playerJs{Json::arrayValue};
    root["player_count"] = static_cast<Json::UInt >(container.size());

    for(const auto& player : container)
    {
        playerJs.append(player->toJson());
    }

    json[NAME_PLAYER.data()] = playerJs;
    return root;
}

void GameRoom::fromJson(const Json::Value& json)
{
    const size_t player_count = json["player_count"].asUInt();
    const auto roomJs = json[NAME_GAMEROOM.data()];
    for(int i=0 ; i < player_count ; i++)
    {
        Room::fromJson(roomJs[i]);
    }
}