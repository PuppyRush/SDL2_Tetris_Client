//
// Created by chaed on 18. 12. 15.
//

#ifndef GUI_GAMECONTROLLER_H
#define GUI_GAMECONTROLLER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <unordered_map>
#include <stack>

#include "DisplayInterface.h"
#include "Tetris/Common/Resource.h"

namespace std
{
template<>
struct hash<TETRIS::DisplayInfo>
{
    size_t operator()(const TETRIS::DisplayInfo& obj) const
    {
        using modeType = underlying_type_t <TETRIS::TLocalMode>;
        using dpType = underlying_type_t <TETRIS::TDisplay >;
        using dpModeType = underlying_type_t <TETRIS::TDisplayMode >;
        const auto mode = static_cast<modeType>(obj.mode);
        const auto dp = static_cast<dpType>(obj.display);
        const auto dpMode = static_cast<dpType>(obj.displayMode);
        return hash<modeType>()(mode)*13 + hash<modeType>()(dp)*21 * hash<dpModeType>()(dpMode)*37 * obj.id*53;
    }
};
}

struct KeyHash {
    std::size_t operator()(const TETRIS::DisplayInfo& obj) const
    {
        using modeType = underlying_type_t <TETRIS::TLocalMode>;
        using dpType = underlying_type_t <TETRIS::TDisplay >;
        using dpModeType = underlying_type_t <TETRIS::TDisplayMode >;
        const auto mode = static_cast<modeType>(obj.mode);
        const auto dp = static_cast<dpType>(obj.display);
        const auto dpMode = static_cast<dpType>(obj.displayMode);
        return hash<modeType>()(mode)*13 + hash<modeType>()(dp)*21 * hash<dpModeType>()(dpMode)*37 * obj.id*53;
    }
};


struct KeyEqual {
    bool operator()(const TETRIS::DisplayInfo& lhs, const TETRIS::DisplayInfo& rhs) const
    {
        return rhs.display == lhs.display &&
            rhs.mode == lhs.mode &&
            rhs.displayMode == lhs.displayMode &&
            rhs.id == lhs.id;
    }
};


SDL_TETRIS_BEGIN

class DisplayController final{

public:
    using display_ptr = std::shared_ptr<DisplayInterface>;

    resource modal(display_ptr);
    void modaless(display_ptr);

    static std::shared_ptr<DisplayController> getInstance();

private:

    DisplayController();
    void _release();

    std::unordered_map< DisplayInfo, display_ptr, KeyHash, KeyEqual> m_modalessMap;
    std::stack<display_ptr> m_modalStack;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
