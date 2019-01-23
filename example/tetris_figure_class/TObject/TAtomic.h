#ifndef TETRIS_TOBJECT_TATOMIC_H
#define TETRIS_TOBJECT_TATOMIC_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Common/TDefine.h"
#include "TType.h"

SDL_TETRIS_BEGIN

class TAtomic
{
public:
	~TAtomic()
	{}

	static const tetris::t_unique newUnique() noexcept
	{
		static tetris::t_uniqueAtomic _atomic;
		return _atomic.fetch_add(1);
	}

	static const tetris::t_unique newWaitingRoomNumber() noexcept
	{
		static tetris::t_uniqueAtomic _atomic;
		return _atomic.fetch_add(1);
	}


private:
	TAtomic()	{}
};

SDL_TETRIS_END

#endif