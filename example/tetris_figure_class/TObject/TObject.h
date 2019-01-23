
#ifndef TETRIS_TOBJECT_TOBJECT_H
#define TETRIS_TOBJECT_TOBJECT_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <memory>

#include "TAtomic.h"
#include "../Common/TDefine.h"
#include "../Common/TType.h"

SDL_TETRIS_BEGIN

class TObject
{
public:
	virtual ~TObject() {}

	inline const bool operator==(const TObject& object) const noexcept
	{	return this->getUnique() == object.getUnique();}

	inline const bool operator!=(const TObject& object) const noexcept
	{	return this->getUnique() != object.getUnique();}

	inline const tetris::t_unique getUnique() const noexcept
	{ return m_unique;	}


protected:
	TObject();

private:
	tetris::t_unique m_unique;
};

SDL_TETRIS_END

#endif