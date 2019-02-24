
#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <memory>

#include "Atomic.h"
#include "GameInterface/Type.h"

namespace game_interface {

class Object {
public:
	virtual ~Object() {}

	inline const bool compareUnique(const t_unique unique) const noexcept { return m_unique == unique; }

	inline const t_unique getUnique() const noexcept { return m_unique; }

	inline void setUnique(const t_unique unique) {
	    m_unique = unique;
	}

protected:
	Object();

private:
	t_unique m_unique;
};

}

#endif