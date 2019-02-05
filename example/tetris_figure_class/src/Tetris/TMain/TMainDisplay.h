#ifndef TETRIS_TMAIN_TMAINDISPLAY_H
#define TETRIS_TMAIN_TMAINDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDLEasyGUI/Windows/DisplayInterface.h"

SDL_TETRIS_BEGIN

class TMainDisplay : public DisplayInterface
{
public:

	bool clickedOption();
	bool clickedDown();
	bool clickedUp();

	virtual ~TMainDisplay() {}


	virtual bool onClickedEnterServer() =0;
	virtual bool onClickedStartLocalGame() =0;
	virtual bool onClickedBack(const TDisplay disply) = 0;


protected:
    TMainDisplay();

	virtual void onPreInitialize() = 0;
	virtual void _event(const SDL_Event* event) =0;
	virtual void _timer() =0;
    virtual void onDraw() =0;
};

SDL_TETRIS_END

#endif