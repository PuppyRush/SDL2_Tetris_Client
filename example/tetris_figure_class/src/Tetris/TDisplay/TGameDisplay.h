

#ifndef TERIS_FIGURE_CLASS_TGAMEDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMEDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDLEasyGUI/Windows/DisplayInterface.h"
#include "Tetris/TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TGameDisplay : public DisplayInterface
{
public:

	enum class UIResource : t_type
	{};

	virtual ~TGameDisplay() {}
	virtual bool clickedStart() =0;
	virtual bool clickedSuspend() =0;
    virtual bool onClickedBack(const TDisplay disply)  = 0;

protected:

    TGameDisplay();

	virtual void onPreInitialize() = 0;
	virtual void onDraw() =0;
    virtual void _event(const SDL_Event* event) =0;
	virtual void _timer() =0;

	std::vector<std::shared_ptr<TPlayer>> m_player;

};

SDL_TETRIS_END

#endif