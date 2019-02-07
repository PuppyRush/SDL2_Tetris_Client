//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
#define TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H

#include "TGameDisplay.h"

SDL_TETRIS_BEGIN

class TGameOnlineDisplay : public TGameDisplay
{
public:
    TGameOnlineDisplay();
    virtual ~TGameOnlineDisplay(){}

private:

    virtual void onClickedStart() override final;
    virtual void onClickedSuspend() override final;

    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void onClose() override final;
    virtual void onCreate() override final;
    virtual void registerEvent() override final;


    virtual void event(const SDL_Event *event) override final;
    virtual void timer() override final;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
