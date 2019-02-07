//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TSTRUCT_H
#define TETRIS_FIGURE_CLASS_TSTRUCT_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <cassert>
#include <string>
#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "TType.h"
#include "Tetris/Common/TProperty.h"

SDL_TETRIS_BEGIN

typedef struct TIPString
{
    TIPString()
    :TIPString({192,168,0,1})
    {

    }

    TIPString(std::initializer_list<size_t> fields)
    {
        assert(fields.size() == 4);
        ip.reserve(16);
        for (size_t b : fields)
        {
            ip.append(std::to_string(static_cast<long>(b)));
            ip.append(".");
        }
        ip.pop_back();
    }

    const char* str() const
    {
        return ip.c_str();
    }

    std::string ip;
}TIPString;


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H
