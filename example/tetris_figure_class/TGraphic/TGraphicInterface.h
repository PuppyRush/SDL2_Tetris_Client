//
// Created by chaed on 19. 1. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
#define TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Common/TDefine.h"
#include "TDisplay/TWindow.h"

SDL_TETRIS_BEGIN

class TGraphicInterface {

public:
    virtual void draw() = 0;

protected:

    TGraphicInterface(){}
    virtual ~TGraphicInterface(){}

private:
    TWindow m_window;
};


SDL_TETRIS_END


#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
