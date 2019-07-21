#include "Tetris/include/TFigureUnit.h"

using namespace tetris_module;
using namespace sdleasygui;

TFigureUnit::TFigureUnit()
        : m_type(UnitType::Empty),
          m_point(sdleasygui::SEG_Point(0, 0)),
          m_color(sdleasygui::ColorCode::none),
          m_age(0)
{

}

TFigureUnit::TFigureUnit(const SEG_Point point, const game_interface::t_age age, const ColorCode color, const UnitType type)
        : m_type(type),
          m_point(point),
          m_color(color),
          m_age(age)
{
}

TFigureUnit::~TFigureUnit()
{
}

bool TFigureUnit::operator!=(const TFigureUnit& unit)
{
    return (this->getPoint().x != unit.getPoint().x || this->getPoint().y != unit.getPoint().y);
}