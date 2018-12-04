#pragma once

#include "MainDisplay.h"

SDL_TETRIS_BEGIN

class MainLocalDisplay : public MainDisplay
{
public:


	virtual bool clickedEnterServer() override {}
	virtual bool clickedStartLocalGame() override {}
	virtual bool clickedBack() override {}

private:
	MainLocalDisplay(const std::vector<Menu> menus)
			:MainDisplay(menus)
	{}
	//메뉴 초기화하기.
	virtual void Initialize(){}
};

SDL_TETRIS_END
