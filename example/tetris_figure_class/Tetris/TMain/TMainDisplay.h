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


	virtual bool clickedEnterServer() =0;
	virtual bool clickedStartLocalGame() =0;
	virtual bool clickedBack(const TDisplay disply) = 0;


protected:
    TMainDisplay();

	virtual void _preInitialize() = 0;
	virtual void _event(const SDL_Event* event) =0;
	virtual void _timer() =0;
    virtual void _draw() =0;
};

SDL_TETRIS_END

#endif