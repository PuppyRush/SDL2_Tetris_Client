//
// Created by chaed on 19. 2. 7.
//

#include "JsonHelper.h"

#include <iostream>
#include <fstream>

using namespace std;

std::bitset<35> JsonHelper::toGameboardBitset(int tetrimino, int direction, int x, int y) {

    std::bitset<3>tetriminoBit(tetrimino);
    std::bitset<2>directionBit(direction);
    std::bitset<10>xBit(x);
    std::bitset<20>yBit(y);
    std::string concator = tetriminoBit.to_string() + directionBit.to_string() + xBit.to_string() + yBit.to_string();

    return std::bitset<35>(concator);
}


void JsonHelper::ref(std::string in, int &tetrimino, int &direction, int &x, int &y){
    tetrimino = (int)std::bitset<3>(in.substr(0,3)).to_ulong(),
    direction = (int)std::bitset<2>(in.substr(3,2)).to_ulong(),
    x = (int)std::bitset<10>(in.substr(5,10)).to_ulong(),
    y = (int)std::bitset<20>(in.substr(15,20)).to_ulong();
}


Json::Value JsonHelper::toJson(std::string id, std::string ip, std::string time, std::string gameBoard){
    Json::Value json;
    json["id"] = id;
    json["ip"] = ip;
    json["time"] = time;
    json["gameBoard"] = gameBoard;

    return json;
}

void JsonHelper::jsonRef(Json::Value json, std::string &id, std::string &ip, std::string &time, std::string &gameBoard){
    id = json["id"].asString();
    ip = json["ip"].asString();
    time = json["time"].asString();
    gameBoard = json["gameBoard"].asString();
}
