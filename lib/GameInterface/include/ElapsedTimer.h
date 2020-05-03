#pragma once
#ifndef SDL2_TETRIS_SERVER_TOOL_ELAPSEDTIMER_H
#define SDL2_TETRIS_SERVER_TOOL_ELAPSEDTIMER_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include "../src/Tool/Time/TimerBasic.h"

namespace game_interface::time {

template <typename _Rep, typename _Rn = long long>
class ElapsedTimer : public TimerBasic<_Rep, _Rn>
{
public:

	ElapsedTimer() = default;
	virtual ~ElapsedTimer() = default;

};

}


#endif
