#ifndef OBJECT_ATOMIC_H
#define OBJECT_ATOMIC_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>

#include "Type.h"
#include "Constant.h"

namespace game_interface::atomic {

template <class _Ty>
class Atomic : public boost::serialization::singleton<Atomic<_Ty>>
{
public:

    friend class boost::serialization::singleton<Atomic>;

    Atomic()
    {

    }
    ~Atomic()
    = default;

    t_id setFirstUnique(t_id id) noexcept
    {
        return (m_firstAtomic = id);
    }

    t_unique newUnique() noexcept
    {
        static t_uniqueAtomic _atomic{ m_firstAtomic };
        return _atomic.fetch_add(1);
    }

    /*static const t_unique newWaitingRoomNumber() noexcept
    {
        static t_uniqueAtomic _atomic{0};
        return _atomic.fetch_add(1);
    }*/

    static Atomic& getInstance()
    {
        return boost::serialization::singleton<Atomic<_Ty>>::get_mutable_instance();
    }

    t_id m_firstAtomic = 0;
};

}

#endif