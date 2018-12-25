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
    virtual bool clickedBack(const TDisplay disply)  = 0;



protected:

    TGameDisplay();

	virtual void _preInitialize() = 0;
    virtual void _event(const SDL_Event* event) =0;
	virtual void _timer() =0;
	virtual void _draw() =0;
};

SDL_TETRIS_END