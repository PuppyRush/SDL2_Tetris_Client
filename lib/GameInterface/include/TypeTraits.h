//
// Created by chaed on 18. 11. 25.
//

#ifndef GAMEINTERFACE_TYPETRAITS_H
#define GAMEINTERFACE_TYPETRAITS_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <cstdlib>
#include <random>
#include <ctime>
#include <memory>
#include <cassert>
#include <type_traits>

#include "Type.h"
#include "TStruct.h"

namespace game_interface {



template<class T>
constexpr const auto toUType(T enuml) noexcept
{
    return static_cast<std::underlying_type_t<T>>(enuml);
}

template<class T>
struct EnumIterator
{
    T value;

    EnumIterator()
            : value(T::Begin)
    {}

    inline const T begin() noexcept
    {
        value = static_cast<T>( toUType(value) << 1);
        return value;
    }

    inline const bool end() const noexcept
    {
        return toUType(value) != toUType(T::End);
    }

    EnumIterator operator++()
    {
        value = (T)(toUType(value) << 1);
        return *this;
    }

    bool operator!=(const EnumIterator* other)
    {
        return toUType(value) != toUType(other->value);
    }
};

template<class T>
class EnumHelper
{
public:

    static const T getRandomly()
    {
        const auto rnd = rand() % (toUType(T::End) - toUType(T::Begin) + 1);
        return T(rnd);
    }

    static const T getRandomly(const T begin, const T end)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(toUType(begin), toUType(end));
        return T(distribution(generator));
    }

private:

    EnumHelper()
    {

    }

};

}

#endif //TERIS_FIGURE_CLASS_TTYPETRAITS_H
