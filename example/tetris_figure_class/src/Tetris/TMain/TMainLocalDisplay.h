#ifndef TETRIS_TMAIN_TMAINLOCALDISPLAY_H
#define TETRIS_TMAIN_TMAINLOCALDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainLocalDisplay final : public TMainDisplay, public boost::serialization::singleton<TMainLocalDisplay>
{
public:
  //  friend class boost::serialization::singleton<TMainLocalDisplay>;
    enum class UIResource : t_type
	{
		Start,
		Option,
		End
	};


	virtual bool onClickedEnterServer() final;
	virtual bool onClickedStartLocalGame() final;
	virtual bool onClickedBack(const TDisplay disply) final;

    static std::shared_ptr<TMainDisplay> getInstance();

private:
	TMainLocalDisplay();

	virtual void onPreInitialize() final;
	virtual void _event(const SDL_Event* event) final;
	virtual void _timer() final;
    virtual void onDraw() final;
};

SDL_TETRIS_END

#endif