

#ifndef TERIS_FIGURE_CLASS_TGAMEDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMEDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TDisplay/TDisplayInterface.h"
#include "../../TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TGameDisplay : public TDisplayInterface
{
public:

	enum class UIResource : sdleasygui::t_type
	{};

	virtual ~TGameDisplay() = default;
	virtual void onClickedStart(const void* click);
	virtual void onClickedSuspend(const void* click) =0;

protected:

    explicit TGameDisplay(const sdleasygui::t_id displayId);

	virtual void onClose() override;
	virtual void onCreate() override;
	virtual void onDraw() override;

	virtual void onInitialize() { TDisplayInterface::onInitialize(); }
	virtual void onKeyboardEvent (const SDL_KeyboardEvent* key) override;
	virtual void onUserEvent(const SDL_UserEvent* event) override;
    virtual void onTimerEvent(const SDL_UserEvent *user) override;

	void _drawFigure(TFigureController::board_ptr board, TFigureController::figure_ptr figure);
	void _drawNextFigure();

    std::vector<std::shared_ptr<TPlayer>> m_players;
	bool m_gamestart = false;
	bool m_drawLine;
    SDL_TimerID m_figureTimer;
};

SDL_TETRIS_END

#endif