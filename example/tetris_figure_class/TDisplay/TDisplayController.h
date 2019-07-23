//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
#define TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

#include "unordered_map"

#include "TDisplayInterface.h"


namespace std
{
template<>
struct hash<std::pair<TETRIS::TMode, TETRIS::TDisplay>>
{
    size_t operator()(const std::pair<TETRIS::TMode, TETRIS::TDisplay>& obj) const
    {
        using modeType = underlying_type_t <TETRIS::TMode>;
        using dpType = underlying_type_t <TETRIS::TDisplay >;
        const auto mode = static_cast<modeType>(obj.first);
        const auto dp = static_cast<dpType>(obj.second);
        return hash<modeType>()(mode)*13 + hash<modeType>()(dp)*21;
    }
};
}


SDL_TETRIS_BEGIN

class TDisplayController final{

public:
    void operateGame();

    inline const TMode getMode() { return m_mode;}
    inline void setMode(const TMode mode) { m_mode = mode;}
    inline void setDisplay(const TDisplay dp) { m_currentDisplay = dp;}
    inline const bool getProgramEnd() const noexcept{ return m_programEnd;}
    inline void setProgramEnd(const bool end) { m_programEnd = end;}

    inline const TDisplay getDisplay() { return m_currentDisplay ;}

    static std::shared_ptr<TDisplayController> getInstance();

private:
    TDisplayController();
    void _release();

    std::unordered_map< std::pair<TMode,TDisplay>,std::shared_ptr<TDisplayInterface>> m_displayMap;
    std::shared_ptr<TDisplayInterface> m_display;


    bool m_programEnd;
    TMode m_mode;
    TDisplay m_currentDisplay;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
