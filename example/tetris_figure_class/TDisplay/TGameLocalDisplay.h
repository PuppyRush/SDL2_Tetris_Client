//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "TGameDisplay.h"
#include "TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TGameLocalDisplay final : public TGameDisplay{

public:
    enum class UIResource : t_type
    {
        Suspend,
        End
    };


    virtual bool clickedStart() final;
    virtual bool clickedSuspend() final;
    virtual bool clickedBack(const TDisplay disply) final;

    virtual ~TGameLocalDisplay(){}

    static std::shared_ptr<TGameDisplay> getInstance();

private:

    TGameLocalDisplay():TGameDisplay(){}

    virtual void _preInitialize() final;
    virtual void _event(const SDL_Event* event) final;
    virtual void _timer() final;
    virtual void _draw() final;


    bool m_drawLine;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
