//
// Created by chaed on 18. 11. 25.
//

#include "TFigureBuilder.h"
#include "TypeTraits.h"

using namespace tetris;

TFigureBuilder::TFigureBuilder(const TPoint &point)
    : m_point(point),
      m_width(0),
      m_height(0),
      m_color(EnumHelper<TColor>::getRandomly ()),
      m_age(1),
      m_figureType(TFigureType::None)
  {
  }
