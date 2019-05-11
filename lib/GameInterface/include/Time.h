//
// Created by chaed on 19. 5. 5.
//

#ifndef SDL2_TETIRS_CLIENT_TIME_H
#define SDL2_TETIRS_CLIENT_TIME_H

#include <ctime>
#include <chrono>
#include <string>

#include "Configcpp.h"

namespace game_interface::time
{



#ifndef GI_TIME
#   if (__cplusplus >= 201103L)
#       define GI_TIME
#   endif
#endif


#ifdef GI_TIME
using time_type = std::chrono::high_resolution_clock;

#endif



#ifdef GI_TIME

GI_FORCE_INLINE

std::time_t now()
{
    return time_type::to_time_t(
            time_type::now());
}

#else

std::time_t now()
{
    return std::time(nullptr);
}

#endif



#ifdef GI_TIME

GI_FORCE_INLINE
std::string current(const time_type::time_point& t)
{
    using namespace std::chrono;

    const milliseconds ms = duration_cast<milliseconds>(t.time_since_epoch());
    const seconds s = duration_cast<seconds>(ms);
    const std::time_t cur = s.count();
    const std::size_t fractional_seconds = ms.count() % 1000;

    std::string timestr{};
    timestr.reserve(50);
    timestr += std::ctime(&cur);
    timestr += "(milli : " + std::to_string(fractional_seconds ) + ")";

    return timestr;
}
#endif


GI_FORCE_INLINE
std::string current(const time_t t)
{

#ifdef GI_TIME
    return current(std::chrono::high_resolution_clock::from_time_t(t));
#endif
    return std::string( std::ctime(&t));
}


}

#endif //SDL2_TETIRS_CLIENT_TIME_H
