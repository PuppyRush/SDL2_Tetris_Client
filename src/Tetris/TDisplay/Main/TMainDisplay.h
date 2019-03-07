#ifndef TETRIS_TMAIN_TMAINDISPLAY_H
#define TETRIS_TMAIN_TMAINDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDLEasyGUI/Windows/DisplayInterface.h"

SDL_TETRIS_BEGIN

class TMainDisplay : public sdleasygui::DisplayInterface
{
public:

	virtual ~TMainDisplay() = default;

	bool clickedOption();
	bool clickedDown();
	bool clickedUp();

	virtual void onClickedEnterServer() =0;
	virtual void onClickedStartLocalGame() =0;
	virtual void onClickedOption() =0;
	virtual void onClickedBack() =0;


protected:
    TMainDisplay();

	virtual void onPreInitialize() = 0;
	virtual void onTimerEvent() =0;
    virtual void onDraw();
};

SDL_TETRIS_END

#endif