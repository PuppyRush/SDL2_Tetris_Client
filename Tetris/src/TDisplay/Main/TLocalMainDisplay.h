#ifndef TETRIS_TMAIN_TMAINLOCALDISPLAY_H
#define TETRIS_TMAIN_TMAINLOCALDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TLocalMainDisplay final : public TMainDisplay
{
public:

	TLocalMainDisplay();
    virtual ~TLocalMainDisplay() = default;

private:

	[[deprecated("dont call this function in TLocalMainDisplay")]]
	virtual void onClickedEnterServer() {assert(0);};

	virtual void onClickedStartLocalGame() override final;
	virtual void onClickedOption() override final;
	virtual void onClickedBack()  override {}
	virtual void registerEvent() override final;
	virtual void onInitialize() override final;
	virtual void onTimerEvent() override final;
    virtual void onDraw() override final;

	virtual Json::Value toJson() const override {}
	virtual const std::string_view& getUniqueName() const override {}

};

SDL_TETRIS_END

#endif