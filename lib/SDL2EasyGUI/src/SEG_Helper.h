

#ifndef SDL2EASYGUI_HELPER_H
#define SDL2EASYGUI_HELPER_H

#if _MSC_VER >= 1200
#pragma once
#endif


#include "../../include/SEG_Struct.h"

namespace seg::helper {

    inline static bool hitTest(const SDL_Rect rect, const SEG_Point point) noexcept
    {
        if ((rect.x <= point.x && point.x <= rect.x + rect.w) && (rect.y <= point.y && point.y <= rect.y + rect.h)) {
            return true;
        }
        else {
            return false;
        }
    }

    inline static bool hitTest(const SDL_Rect rect, const t_coord x, const t_coord y) noexcept
    {
        if ((rect.x <= x && x <= rect.x + rect.w) && (rect.y <= y && y <= rect.y + rect.h)) {
            return true;
        }
        else {
            return false;
        }
    }


}

#endif