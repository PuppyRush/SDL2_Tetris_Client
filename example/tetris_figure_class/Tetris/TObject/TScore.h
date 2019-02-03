//
// Created by chaed on 19. 1. 13.
//

#ifndef TETRIS_FIGURE_CLASS_TSCORE_H
#define TETRIS_FIGURE_CLASS_TSCORE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Common/TDefine.h"
#include "Common/TStruct.h"

SDL_TETRIS_BEGIN

class TScore final
{
public:
    TScore(/*const TPoint& boardBegin, const TColor& backColor, const TFont& font*/);


    inline const int get()
    { return m_score; }

    inline void zero()
    { m_score =0; }

    inline void add(const int score)
    { m_score+= score; }

    inline void subtract(const int score)
    { m_score-= score; }

private:

    int m_score = 0;
    TPoint m_boardBegin;
    TColor m_backColor;
    TFont m_font;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSCORE_H
