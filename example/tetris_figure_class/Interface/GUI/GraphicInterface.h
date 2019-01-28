//
// Created by chaed on 19. 1. 22.
//

#ifndef GUI_GRAPHICINTERFACE_H
#define GUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Common/TDefine.h"
#include "Window.h"

SDL_TETRIS_BEGIN

class GraphicInterface {

public:
    virtual void draw() = 0;

protected:

    GraphicInterface() = default;
    virtual ~GraphicInterface() = default;


private:
};


SDL_TETRIS_END


#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
