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


	virtual bool clickedEnterServer() final;
	virtual bool clickedStartLocalGame() final;
	virtual bool clickedBack(const TDisplay disply) final;

    static std::shared_ptr<TMainDisplay> getInstance();



protected:


private:
	TMainLocalDisplay();

	virtual void _preInitialize() final;
	virtual void _event(const SDL_Event* event) final;
	virtual void _timer() final;
    virtual void _draw() final;
};

SDL_TETRIS_END

#endif