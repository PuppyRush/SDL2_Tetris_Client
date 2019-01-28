//
// Created by chaed on 18. 12. 18.
//

#ifndef TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
#define TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Interface/GUI/DisplayInterface.h"

SDL_TETRIS_BEGIN

class TOptionDisplay final: public DisplayInterface
{
public:
    enum class UIResource : t_type
    {
        Suspend,
        End
    };

    virtual bool clickedBack(const TDisplay disply) override {}

    static std::shared_ptr<DisplayInterface> getInstance();

private:

    virtual void _preInitialize() final;
    virtual void _event(const SDL_Event* event) final;
    virtual void _timer() final;
    virtual void _draw() final;

};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
