
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

	using unique_type = t_unique;

	virtual ~Object() = default;

	inline const bool compareUnique(const unique_type unique) const noexcept { return m_unique == unique; }

	inline void setUnique(const unique_type unique) { m_unique = unique; }
	inline const unique_type getUnique() const noexcept { return m_unique; }

	inline const t_time getMaketime() { return m_maketime;}

protected:
	Object();

private:
	unique_type m_unique;
	t_time m_maketime;
};

}

#endif