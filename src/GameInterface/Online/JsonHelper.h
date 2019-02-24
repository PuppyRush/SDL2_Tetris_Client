// Created by chaed on 19. 2. 7.
//

#ifndef TETRIS_FIGURE_CLASS_JSONHELPER_H
#define TETRIS_FIGURE_CLASS_JSONHELPER_H

#include <bitset>
#include <string>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.

namespace game_interface {

template <class T>
struct KeyValue{

    std::string key;
    T value;
};

class JsonHelper {
public:

    static std::bitset<35> toGameboardBitset(int tetrimino, int direction, int x, int y);
    static void ref(std::string in, int &tetrimino, int &direction, int &x, int &y);
    static Json::Value toJson(std::string id, std::string ip, std::string time, std::string gameBoard);
    static void jsonRef(Json::Value json, std::string &id, std::string &ip, std::string &time, std::string &gameBoard);

    template <class T>
    static Json::Value toJson(std::initializer_list<KeyValue<T>>);

private:
    JsonHelper() = default;
};

}

#endif //TETRIS_FIGURE_CLASS_JSONHELPER_H
