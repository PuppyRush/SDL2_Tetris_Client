//
// Created by chaed on 19. 1. 13.
//

#include "Player.h"


using namespace game_interface;

Json::Value Player::toJson() const
{
    Json::Value json = Object::toJson();
    json["player_name"] = getUserName();

    return json;
}