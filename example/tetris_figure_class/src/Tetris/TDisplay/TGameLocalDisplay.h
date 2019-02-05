//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "TGameDisplay.h"
#include "Tetris/TObject/TPlayer.h"

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
    virtual bool onClickedBack(const TDisplay disply) final;

    virtual ~TGameLocalDisplay(){}

    static std::shared_ptr<TGameDisplay> getInstance();
    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void onClose() override final;
    virtual void onCreate() override final;

private:

    TGameLocalDisplay() = default;

    virtual void _event(const SDL_Event* event) final;
    virtual void _timer() final;

    void _drawFigure(TFigureController::board_ptr board, TFigureController::figure_ptr figure);
    void _drawNextFigure();

    bool m_drawLine;
    SDL_TimerID m_figureTimer;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
