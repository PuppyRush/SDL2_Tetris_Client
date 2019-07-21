//
// Created by chaed on 19. 1. 13.
//

#include "GameInterface/include/Player.h"

using namespace game_interface;

Json::Value Player::toJson() const
{
    Json::Value json = Object::toJson();
    json["name"] = getUserName();

    return json;
}

void Player::fromJson(const Json::Value& json)
{
    setUserName(json["name"].asString());
    Object::fromJson(json);
}
