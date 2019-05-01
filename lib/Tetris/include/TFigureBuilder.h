#ifndef TETRIS_TFIGUREBUILDER_H
#define TETRIS_TFIGUREBUILDER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "GameInterface/include/Type.h"
#include "TFigureInterface.h"
#include "TFigures.h"

namespace tetris_module {

class TFigureBuilder final
{
public:

    TFigureBuilder(const sdleasygui::TPoint& point);

    virtual ~TFigureBuilder()
    {}

    inline TFigureBuilder* color(const sdleasygui::ColorCode& color)
    {
        this->m_color = color;
        return this;
    }

    inline TFigureBuilder* type(const TFigureType& type)
    {
        this->m_figureType = type;
        return this;
    }

    inline TFigureBuilder* age(const game_interface::t_age& age)
    {
        this->m_age = age;
        return this;
    }

    inline TFigureBuilder* unitType(const UnitType& type)
    {
        this->m_unitType = type;
        return this;
    }

    inline TFigureBuilder* figure(const TFigureClass& figure)
    {
        this->m_figureClass = figure;
        return this;
    }

    inline const sdleasygui::TPoint getPoint() const noexcept
    { return m_point; }

    inline const sdleasygui::ColorCode getColor() const noexcept
    { return m_color; }

    inline const TFigureType getType() const noexcept
    { return m_figureType; }

    inline const game_interface::t_age getAge() const noexcept
    { return m_age; }

    inline const sdleasygui::t_size getHeight() const noexcept
    { return m_height; }

    inline const sdleasygui::t_size getWidth() const noexcept
    { return m_width; }

    inline const UnitType getUnitType() const noexcept
    { return m_unitType; }

    inline constexpr const TFigureClass getClass() const noexcept
    { return m_figureClass; }

    std::shared_ptr<TFigureInterface> build();

private:
    inline void width(const sdleasygui::t_size width)
    { m_width = width; }

    inline void height(const sdleasygui::t_size height)
    { m_height = height; }

    sdleasygui::t_size m_width;
    sdleasygui::t_size m_height;
    sdleasygui::ColorCode m_color;
    sdleasygui::TPoint m_point;
    TFigureType m_figureType;
    TFigureClass m_figureClass = TFigureClass::L;
    game_interface::t_age m_age;
    UnitType m_unitType;

};

}

#endif