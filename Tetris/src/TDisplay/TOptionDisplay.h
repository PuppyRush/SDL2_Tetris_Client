//
// Created by chaed on 18. 12. 18.
//

#ifndef TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
#define TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TOptionDisplay final: public TDisplayInterface
{
public:

    TOptionDisplay();
    virtual ~TOptionDisplay(){}

private:

    virtual void registerEvent() override final;
    virtual void onInitialize() override final;
    virtual void onDraw() override final;
    void onClickedBack(const void*);

};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
