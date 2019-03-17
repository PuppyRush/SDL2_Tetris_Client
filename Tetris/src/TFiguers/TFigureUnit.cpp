#include "TFigureUnit.h"

SDL_TETRIS

using namespace sdleasygui;

TFigureUnit::TFigureUnit()
    :m_type(UnitType::Empty),
     m_point(sdleasygui::TPoint(0,0)),
     m_color(sdleasygui::ColorCode::none),
     m_age(0)
{

}

TFigureUnit::TFigureUnit(const TPoint point, const t_age age, const ColorCode color, const UnitType type)
    :m_type(type),
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
    return (this->getPoint ().x != unit.getPoint ().x || this->getPoint ().y != unit.getPoint ().y);
}