#pragma once

#include "../TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TMainDisplay : public TDisplayInterface
{
public:

	bool clickedOption();
	bool clickedDown();
	bool clickedUp();

	virtual ~TMainDisplay() {}


	virtual bool clickedEnterServer() =0;
	virtual bool clickedStartLocalGame() =0;
	virtual bool clickedBack() = 0;


protected:
    TMainDisplay(const std::vector<Menu>& menus);
    TMainDisplay(std::vector<Menu>&& menus);


};

SDL_TETRIS_END