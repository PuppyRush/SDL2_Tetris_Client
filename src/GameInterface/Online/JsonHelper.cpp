//
// Created by chaed on 19. 2. 7.
//

#include "JsonHelper.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace game_interface;

bitset<35> JsonHelper::toGameboardBitset(int tetrimino, int direction, int x, int y) {

    bitset<3>tetriminoBit(tetrimino);
    bitset<2>directionBit(direction);
    bitset<10>xBit(x);
    bitset<20>yBit(y);
    string concator = tetriminoBit.to_string() + directionBit.to_string() + xBit.to_string() + yBit.to_string();

    return bitset<35>(concator);
}


void JsonHelper::ref(string in, int &tetrimino, int &direction, int &x, int &y){
    tetrimino = (int)bitset<3>(in.substr(0,3)).to_ulong(),
    direction = (int)bitset<2>(in.substr(3,2)).to_ulong(),
    x = (int)bitset<10>(in.substr(5,10)).to_ulong(),
    y = (int)bitset<20>(in.substr(15,20)).to_ulong();
}


Json::Value JsonHelper::toJson(string id, string ip, string time, string gameBoard){
    Json::Value json;
    json["id"] = id;
    json["ip"] = ip;
    json["time"] = time;
    json["gameBoard"] = gameBoard;

    return json;
}

void JsonHelper::jsonRef(Json::Value json, string &id, string &ip, string &time, string &gameBoard){
    id = json["id"].asString();
    ip = json["ip"].asString();
    time = json["time"].asString();
    gameBoard = json["gameBoard"].asString();
}


template <class T>
Json::Value JsonHelper::toJson(std::initializer_list<KeyValue<T>> va)
{
}
