

#ifndef TERIS_FIGURE_CLASS_TGAMEDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMEDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDLEasyGUI/Windows/DisplayInterface.h"
#include "Tetris/TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TGameDisplay : public sdleasygui::DisplayInterface
{
public:

	enum class UIResource : sdleasygui::t_type
	{};

	virtual ~TGameDisplay() {}
	virtual void onClickedStart() =0;
	virtual void onClickedSuspend() =0;

protected:

    TGameDisplay();

	virtual void onClose() override;
	virtual void onCreate() override;
	virtual void onDraw() override;

	virtual void onPreInitialize() = 0;
	virtual void onKeyboardEvent (const SDL_KeyboardEvent* key);
	virtual void onUserEvent(const SDL_UserEvent* event);

	void _drawFigure(TFigureController::board_ptr board, TFigureController::figure_ptr figure);
	void _drawNextFigure();

    std::vector<std::shared_ptr<TPlayer>> m_players;
	bool m_gamestart = false;
	bool m_drawLine;
    SDL_TimerID m_figureTimer;
};

SDL_TETRIS_END

#endif