//
// Created by chaed on 18. 11. 25.
//

#include "TFigureBuilder.h"
#include "Common/TypeTraits.h"

using namespace tetris;

TFigureBuilder::TFigureBuilder(const TPoint &point)
    : m_point(point),
      m_width(0),
      m_height(0),
      m_color(EnumHelper<TColorCode>::getRandomly ()),
      m_age(1),
      m_figureType(TFigureType::A),
      m_figureClass(EnumHelper<TFigureClass>::getRandomly())
  {
  }
TFigureBuilder *TFigureBuilder::figure(const TFigureClass& figure)
{
    this->m_figureClass = figure;
    return this;
}

std::shared_ptr<TFigure> TFigureBuilder::build()
{
    switch(getClass())
    {
        case TFigureClass::L:
            this->color(TColorCode::green);
            return TFigureL::get(this);
        case TFigureClass::Z:
            this->color(TColorCode::red);
            return TFigureZ::get(this);
        case TFigureClass ::I:
            this->color(TColorCode::yellow);
            return TFigureI::get(this);
        case TFigureClass ::O:
            this->color(TColorCode::orange);
            return TFigureO::get(this);
        case TFigureClass ::T:
            this->color(TColorCode::blue);
            return TFigureT::get(this);
        default:
            assert(0);
    }
}

