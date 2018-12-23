#pragma once

#include "../TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TGameDisplay : public TDisplayInterface
{
public:

	enum class UIResource : t_type
	{};

	virtual ~TGameDisplay() {}

	virtual bool clickedStart() =0;
	virtual bool clickedSuspend() =0;
    virtual bool clickedBack()  = 0;



protected:

    TGameDisplay();
	virtual void _setDisplay() =0;
};

SDL_TETRIS_END