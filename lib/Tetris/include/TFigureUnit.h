#ifndef TETRISMODULE_TFIGUREUNIT_H
#define TETRISMODULE_TFIGUREUNIT_H

#if _MSC_VER > 1200
#pragma once
#endif

#include "GameInterface/include/TypeTraits.h"
#include "GameInterface/include/Type.h"
#include "GameInterface/include/TStruct.h"
#include "SDL2EasyGUI/include/SEG_Type.h"
#include "SDL2EasyGUI/include/SEG_Struct.h"
#include "TProperty.h"

namespace tetris_module {

class TFigureUnit final
{
public:

    TFigureUnit();

    TFigureUnit(const seg::SEG_Point point, const game_interface::t_age age, const seg::ColorCode color,
                const tetris_module::UnitType type);

    ~TFigureUnit();

    bool operator!=(const TFigureUnit& unit);

    inline seg::SEG_Point getPoint() const noexcept
    {
        return m_point;
    }

    inline game_interface::t_age getAge() const noexcept
    {
        return m_age;
    }

    inline seg::SEG_Color getColor() const noexcept
    {
        return m_color;
    }

    inline UnitType getType() const noexcept
    {
        return m_type;
    }

    inline void set(const seg::SEG_Point& m_point)
    {
        this->m_point = m_point;
    }

    inline void set(seg::SEG_Point&& m_point)
    {
        this->m_point = m_point;
    }

    inline void set(const game_interface::t_age age) noexcept
    {
        this->m_age = age;
    }

    inline void set(const seg::SEG_Color& color) noexcept
    {
        this->m_color = color;
    }

    inline void set(seg::SEG_Color&& color) noexcept
    {
        this->m_color = color;
    }

    inline void set(const UnitType& m_type) noexcept
    {
        this->m_type = m_type;
    }

    static TFigureUnit& getDefaultUnit()
    {
        static TFigureUnit unit(seg::SEG_Point(0, 0), 0, seg::ColorCode::none, UnitType::Empty);
        return unit;
    }

private:
    seg::SEG_Point m_point;
    seg::SEG_Color m_color;
    game_interface::t_age m_age;
    UnitType m_type;
};

}

#endif
