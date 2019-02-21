#ifndef OBJECT_ATOMIC_H
#define OBJECT_ATOMIC_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "GameInterface/Type.h"

namespace game_interface {

class Atomic
{
public:
	~Atomic()
	{}

	static const t_unique newUnique() noexcept
	{
		static t_uniqueAtomic _atomic;
		return _atomic.fetch_add(1);
	}

	static const t_unique newWaitingRoomNumber() noexcept
	{
		static t_uniqueAtomic _atomic;
		return _atomic.fetch_add(1);
	}


private:
	Atomic()	{}
};

}

#endif