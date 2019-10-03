//
// Created by chaed on 19. 8. 23..
//

#ifndef SDL2_TETRIS_CLIENT_SEG_TIME_H
#define SDL2_TETRIS_CLIENT_SEG_TIME_H

#include <string>
#include <chrono>

namespace seg::time{

using time_type = std::chrono::high_resolution_clock;

static std::string current(const time_type::time_point& t)
{

    using namespace std::chrono;

    const milliseconds ms = duration_cast<milliseconds>(t.time_since_epoch());
    const seconds s = duration_cast<seconds>(ms);
    const std::time_t cur = s.count();
    const std::size_t fractional_seconds = ms.count() % 1000;

    std::string timestr{};
    timestr.reserve(50);
    timestr += std::ctime(&cur);
    timestr.pop_back();
    timestr += "(milli : " + std::to_string(fractional_seconds) + ")";

    return timestr;
}


static std::string current(const time_t t)
{
    return current(std::chrono::high_resolution_clock::from_time_t(t));
}

static std::time_t now_to_time()
{
    return std::time(nullptr);
}

static std::string now_to_string()
{
    return current(time_type::now());
}

}

#endif //SDL2_TETRIS_CLIENT_SEG_TIME_H
