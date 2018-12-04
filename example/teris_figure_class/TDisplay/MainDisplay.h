#pragma once

#include "DisplayInterface.h"

SDL_TETRIS_BEGIN

class MainDisplay : public DisplayInterface
{
public:

	bool clickedOption();
	bool clickedDown();
	bool clickedUp();

	virtual ~MainDisplay() {}

	virtual bool clickedEnterServer() =0;
	virtual bool clickedStartLocalGame() =0;
	virtual bool clickedBack() = 0;

protected:
    MainDisplay(const std::vector<Menu> menus)
            :DisplayInterface(menus) {}
};

SDL_TETRIS_END