#include "TFigureUnit.h"

SDL_TETRIS

TFigureUnit::TFigureUnit()
    :m_type(UnitType::Empty),
     m_point(TPoint(0,0)),
     m_color(TColorCode::none),
     m_age(0)
{

}

TFigureUnit::TFigureUnit(const TPoint point, const t_age age, const TColorCode color, const UnitType type)
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