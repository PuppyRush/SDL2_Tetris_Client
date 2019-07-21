

#ifndef TERIS_FIGURE_CLASS_TGAMEDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMEDISPLAY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/include/SEG_Event.h"
#include "TDisplayInterface.h"
#include "../../TObject/TPlayer.h"
#include "Tetris/include/TFigureController.h"
#include "../../TObject/TGameRoom.h"

SDL_TETRIS_BEGIN

class TGameDisplay : public TDisplayInterface
{
public:

    enum class UIResource : sdleasygui::t_type
    {
    };

    virtual ~TGameDisplay() = default;

    virtual void onClickedStart(const void* click);

    virtual void onClickedSuspend(const void* click) = 0;

protected:

    explicit TGameDisplay(const sdleasygui::t_id displayId);

    virtual void onClose() override;

    virtual void onCreate() override;

    virtual void onDraw() override;

    virtual void onInitialize() override;

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override;

    virtual void onUserEvent(const SDL_UserEvent* event) override;

    virtual void onTimerEvent(const SDL_UserEvent* user) override;

    void _drawFigure(tetris_module::TFigureController::board_ptr board, tetris_module::TFigureController::figure_ptr figure);

    void _drawNextFigure();

    std::shared_ptr<sdleasygui::TimerAdder> m_gameTimer;
    std::vector<std::shared_ptr<TPlayer>> m_players;
    bool m_gamestart = false;
    bool m_drawLine;
    SDL_TimerID m_timerId;
    std::shared_ptr<TGameRoom> m_gameroom = TGameRoom::getInstance();
};

SDL_TETRIS_END

#endif