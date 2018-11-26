//
// Created by chaed on 18. 11. 25.
//

#ifndef TERIS_FIGURE_CLASS_TTYPETRAITS_H
#define TERIS_FIGURE_CLASS_TTYPETRAITS_H

#include <random>

namespace tetris
{

template<class T>
constexpr const auto toUType(T enuml) noexcept
{
    return static_cast<std::underlying_type_t<T>>(enuml);
}

template <class T>
struct EnumIterator
{
    T value;
    
    EnumIterator()
        :value(T::Begin)
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
    
    bool operator!=(const EnumIterator *other)
    {
        return toUType(value) != toUType(other->value);
    }
};

template <class T>
class EnumHelper
{
public:
    static const T getRandomly()
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(toUType(T::Begin), toUType(T::End));
        return T(distribution(generator));
    }
    
    static const T getRandomly(const T begin, const T end)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(toUType(begin), toUType(end));
        return T(distribution(generator));
    }
};

}
#endif //TERIS_FIGURE_CLASS_TTYPETRAITS_H
