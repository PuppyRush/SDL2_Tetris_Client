//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
#define TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H

#include "TGameDisplay.h"
#include "../../TObject/TGameRoom.h"
SDL_TETRIS_BEGIN

class TMultiGameRoomDisplay : public TGameDisplay
{
public:
    TMultiGameRoomDisplay();
    virtual ~TMultiGameRoomDisplay() = default;

private:

    virtual void onClickedStart(const void* click) override final;
    virtual void onClickedSuspend(const void* click) override final;

    virtual void onDraw() override final;
    virtual void onInitialize() override final;
    virtual void onClose() override final;
    virtual void onCreate() override final;
    virtual void registerEvent() override final;
    virtual void onUserEvent(const SDL_UserEvent* event) override final;

    TGameRoom m_gameroom;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
