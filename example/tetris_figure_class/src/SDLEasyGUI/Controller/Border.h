//
// Created by chaed on 19. 1. 22.
//

#ifndef CONTROLLER_BORDER_H
#define CONTROLLER_BORDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Common/TStruct.h"
#include "SDLEasyGUI/Windows/GraphicInterface.h"

SDL_TETRIS_BEGIN

class Border final : public GraphicInterface {

    Border(const TPoint& beginPoint,const t_size width, const t_size height);
    Border(const t_coord x, const t_coord y ,const t_size width, const t_size height);

    virtual void onDraw() override;

private:
    TColorCode m_backgounrdColor = TColorCode::none;
    TPoint m_beginPoint = {0,0};
    t_size m_width = 0;
    t_size m_height = 0;
    t_size m_weight = 1;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TBORDER_H
