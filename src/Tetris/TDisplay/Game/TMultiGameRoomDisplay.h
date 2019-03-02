//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
#define TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H

#include "TGameDisplay.h"

SDL_TETRIS_BEGIN

class TMultiGameRoomDisplay : public TGameDisplay
{
public:
    TMultiGameRoomDisplay();
    virtual ~TMultiGameRoomDisplay(){}

private:

    virtual void onClickedStart() override final;
    virtual void onClickedSuspend() override final;

    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void onClose() override final;
    virtual void onCreate() override final;
    virtual void registerEvent() override final;
    virtual void onUserEvent(const SDL_UserEvent* event) override final;

    virtual void updateObserver(const game_interface::Packet& ) override final {}
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
