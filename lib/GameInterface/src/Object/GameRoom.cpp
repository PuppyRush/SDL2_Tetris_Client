//
// Created by chaed on 19. 2. 8.
//

#include <string>
#include "GameInterface/include/GameRoom.h"

using namespace game_interface;
using namespace game_interface::packet;
using namespace std;

void GameRoom::updateObserver(const Packet&)
{}


Json::Value GameRoom::toJson() const
{

    auto json = Room::toJson();

    const auto& container = getPlayerContainer();
    Json::Value playerJs{Json::arrayValue};
    json["player_count"] = static_cast<Json::UInt >(container.size());

    for (const auto& player : container) {
        playerJs.append(player->toJson());
    }

    json[NAME_PLAYER.data()] = playerJs;
    return json;
}

void GameRoom::fromJson(const Json::Value& json)
{
    Room::fromJson(json);
}