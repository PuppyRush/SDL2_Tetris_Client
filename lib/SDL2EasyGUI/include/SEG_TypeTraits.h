//
// Created by chaed on 18. 11. 25.
//

#ifndef SDL2EASYGUI_TYPE_TRAITS_H
#define SDL2EASYGUI_TYPE_TRAITS_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <cstdlib>
#include <random>
#include <ctime>
#include <memory>
#include <cassert>

#include "SEG_Struct.h"
#include "SEG_Atomic.h"

namespace seg {

    template<class T>
    inline const constexpr auto toUType(T enuml) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(enuml);
    }

    inline auto make_segpoint(SDL_Point pt) noexcept
    {
        return SEG_Point{ static_cast<decltype(SEG_Point::x)>(pt.x), static_cast<decltype(SEG_Point::y)>(pt.y), static_cast<decltype(SEG_Point::z)>(0) };
    }

    template<class P1, class P2, class P3 = decltype(SEG_Point::z)>
    inline auto make_segpoint(P1 x, P2 y, P3 z = 0) noexcept
    {
        return SEG_Point{ static_cast<decltype(SEG_Point::x)>(x), static_cast<decltype(SEG_Point::y)>(y), static_cast<decltype(SEG_Point::z)>(z) };
    }

    template<class P1, class P2>
    inline auto make_sdlpoint(P1 x, P2 y) noexcept
    {
        return SDL_Point{ static_cast<decltype(SDL_Point::x)>(x), static_cast<decltype(SDL_Point::y)>(y) };
    }

    inline auto make_sdlpoint(SEG_Point pt) noexcept
    {
        return SDL_Point{ static_cast<decltype(SDL_Point::x)>(pt.x), static_cast<decltype(SDL_Point::y)>(pt.y) };
    }


    inline auto make_sdlrect(SEG_Rect rect) noexcept
    {
        return SDL_Rect{ static_cast<decltype(SDL_Rect::x)>(rect.point.x), static_cast<decltype(SDL_Rect::y)>(rect.point.y), static_cast<decltype(SDL_Rect::w)>(rect.w), static_cast<decltype(SDL_Rect::h)>(rect.h) };
    }

    inline auto make_segrect(SDL_Rect rect) noexcept
    {
        return SEG_Rect{ { static_cast<decltype(SEG_Rect::point.x)>(rect.x), static_cast<decltype(SEG_Rect::point.y)>(rect.y), static_cast<decltype(SEG_Rect::point.z)>(0) },
            static_cast<decltype(SEG_Rect::w)>(rect.w), static_cast<decltype(SEG_Rect::h)>(rect.h) };
    }


    template<class P1, class P2, class P3, class P4>
    inline auto make_segrect(P1 x, P2 y, P3 w, P4 h) noexcept
    {
        return SEG_Rect{ { static_cast<decltype(SEG_Rect::point::x)>(x), static_cast<decltype(SDL_Rect::point::y)>(y),static_cast<decltype(SDL_Rect::point::z)>(0) },
            static_cast<decltype(SEG_Rect::w)>(w), static_cast<decltype(SEG_Rect::h)>(h) };
    }


    template<class P1, class P2, class P3, class P4>
    inline auto make_sdlrect(P1 x, P2 y, P3 w, P4 h) noexcept
    {
        return SDL_Rect{ static_cast<decltype(SDL_Rect::x)>(x), static_cast<decltype(SDL_Rect::y)>(y), static_cast<decltype(SDL_Rect::w)>(w), static_cast<decltype(SDL_Rect::h)>(h) };
    }


    template<class _Tp, class... _Args>
    inline std::shared_ptr<_Tp>
        make_display(_Args&& ... __args)
    {
        typedef typename std::remove_const<_Tp>::type _Tp_nc;
        return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(), std::forward<_Args>(__args)...);
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
            value = static_cast<T>(toUType(value) << 1);
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
