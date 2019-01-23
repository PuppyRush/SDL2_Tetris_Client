//
// Created by chaed on 19. 1. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TBORDER_H
#define TETRIS_FIGURE_CLASS_TBORDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Common/TStruct.h"
#include "TGraphicInterface.h"

SDL_TETRIS_BEGIN

class TBorder final : public TGraphicInterface {

    TBorder(const TPoint& beginPoint,const t_size width, const t_size height);
    TBorder(const t_coord x, const t_coord y ,const t_size width, const t_size height);

    virtual void draw() override;

private:
    TColorCode m_backgounrdColor = TColorCode::none;
    TPoint m_beginPoint = {0,0};
    t_size m_width = 0;
    t_size m_height = 0;
    t_size m_weight = 1;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TBORDER_H
