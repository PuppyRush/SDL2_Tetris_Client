#pragma once

#include "MainDisplay.h"

class MainLocalDisplay : public MainDisplay
{
public:

	bool clickedEnterServer() {}
	bool clickedStartLocalGame() {}

	virtual bool clickedBack() override {}
};
