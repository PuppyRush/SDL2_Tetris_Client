//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H

#include "TGameDisplay.h"

SDL_TETRIS_BEGIN

class TGameLocalDisplay : public TGameDisplay{

public:
    enum class UIResource : t_type
    {
        Suspend,
        End
    };


    virtual bool clickedStart() override;
    virtual bool clickedSuspend() override;
    virtual bool clickedBack()  override;

    virtual ~TGameLocalDisplay(){}

    static std::shared_ptr<TGameDisplay> getInstance();

private:

    TGameLocalDisplay():TGameDisplay(){}
    virtual void _setDisplay() override;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
