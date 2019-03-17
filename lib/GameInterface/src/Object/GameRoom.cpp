//
// Created by chaed on 19. 2. 8.
//

#include <string>

#include "GameRoom.h"

using namespace game_interface;


void GameRoom::updateObserver(const Packet& )
{}

Json::Value GameRoom::toJson() const {

    auto json = Room::toJson();

    const auto& container = getPlayerContainer();
    Json::Value root;
    root["player_count"] = static_cast<Json::UInt >(container.size());

    size_t i=0;
    for(const auto& player : container)
    {
        Json::Value jsonPlayer;
        jsonPlayer.append(player->toJson());

        std::string name = player->getUniqueName().data();
        name += std::to_string(i);
        root[name.c_str()] = jsonPlayer;
        i++;

    }

    json.append(root);
    return root;
}