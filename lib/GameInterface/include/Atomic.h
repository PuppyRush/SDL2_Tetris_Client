#ifndef OBJECT_ATOMIC_H
#define OBJECT_ATOMIC_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>

#include "Type.h"
#include "Constant.h"

namespace game_interface {

class Atomic : public boost::serialization::singleton<Atomic>
{
public:

    friend class boost::serialization::singleton<Atomic>;

    ~Atomic()
    = default;

    static const t_unique newUnique() noexcept
    {
        static t_uniqueAtomic _atomic{SERVER_ATOMIC_START};
        return _atomic.fetch_add(1);
    }

    static const t_unique newWaitingRoomNumber() noexcept
    {
        static t_uniqueAtomic _atomic{0};
        return _atomic.fetch_add(1);
    }

    static Atomic& getInstance()
    {
        return boost::serialization::singleton<Atomic>::get_mutable_instance();
    }

private:
    Atomic()
    {}

};

}

#endif