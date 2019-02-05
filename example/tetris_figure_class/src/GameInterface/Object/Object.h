
#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <memory>

#include "Atomic.h"
#include "Common/TType.h"

class Object
{
public:
	virtual ~Object() {}

	inline const bool operator==(const Object& object) const noexcept
	{	return m_unique == object.getUnique(); }

	inline const bool operator!=(const Object& object) const noexcept
	{	return m_unique != object.getUnique(); }

	inline const tetris::t_unique getUnique() const noexcept
	{ return m_unique;	}

protected:
	Object();

private:
	tetris::t_unique m_unique;
};

#endif