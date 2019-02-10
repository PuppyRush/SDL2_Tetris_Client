//
// Created by chaed on 18. 12. 15.
//

#ifndef GUI_GAMECONTROLLER_H
#define GUI_GAMECONTROLLER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <unordered_map>
#include <queue>

#include "DisplayInterface.h"
#include "Tetris/Common/Resource.h"
/*

namespace std
{
template<>
struct hash<DisplayInfo>
{
    size_t operator()(const DisplayInfo& obj) const
    {
        using modeType = underlying_type_t <TLocalMode>;
        using dpType = underlying_type_t <TDisplay >;
        using dpModeType = underlying_type_t <TDisplayMode >;
        const auto mode = static_cast<modeType>(obj.mode);
        const auto dp = static_cast<dpType>(obj.display);
        const auto dpMode = static_cast<dpType>(obj.displayMode);
        return hash<modeType>()(mode)*13 + hash<modeType>()(dp)*21 * hash<dpModeType>()(dpMode)*37 * obj.id*53;
    }
};
}

struct KeyHash {
    std::size_t operator()(const DisplayInfo& obj) const
    {
        using modeType = underlying_type_t <TLocalMode>;
        using dpType = underlying_type_t <TDisplay >;
        using dpModeType = underlying_type_t <TDisplayMode >;
        const auto mode = static_cast<modeType>(obj.mode);
        const auto dp = static_cast<dpType>(obj.display);
        const auto dpMode = static_cast<dpType>(obj.displayMode);
        return hash<modeType>()(mode)*13 + hash<modeType>()(dp)*21 * hash<dpModeType>()(dpMode)*37 * obj.id*53;
    }
};


struct KeyEqual {
    bool operator()(const DisplayInfo& lhs, const DisplayInfo& rhs) const
    {
        return rhs.display == lhs.display &&
            rhs.mode == lhs.mode &&
            rhs.displayMode == lhs.displayMode &&
            rhs.id == lhs.id;
    }
};
*/


SDL_TETRIS_BEGIN

class DisplayController final{

public:
    using display_ptr = std::shared_ptr<DisplayInterface>;
    using modal_ary = std::deque<display_ptr>;
    using modaless_ary =  std::vector<display_ptr>;
    using modaless_ary_iterator = modaless_ary::const_iterator;

    void run();
    resource modal(display_ptr);
    void modaless(display_ptr);
    void close(const t_winid id);
    display_ptr findFromId(const t_winid id);

    static std::shared_ptr<DisplayController> getInstance();

private:

    DisplayController();

    Uint32 getActivatedWindowID(const SDL_Event* event);

    void _release();

    template <class T>
    display_ptr _find(const T& ary, const t_winid id);

    modaless_ary m_modalessAry;
    modal_ary m_modalStack;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
