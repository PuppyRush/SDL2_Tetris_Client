#pragma once

#include "DisplayInterface.h"

class MainDisplay : public DisplayInterface
{
public:
	bool clickedOption();

	virtual ~MainDisplay() {}

	virtual bool clickedBack() = 0;
};