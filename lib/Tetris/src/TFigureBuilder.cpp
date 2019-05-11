//
// Created by chaed on 18. 11. 25.
//

#include "Tetris/include/TFigureBuilder.h"
#include "GameInterface/include/TypeTraits.h"

using namespace sdleasygui;
using namespace tetris_module;

TFigureBuilder::TFigureBuilder(const SEG_Point& point)
        : m_point(point),
          m_width(0),
          m_height(0),
          m_color(game_interface::EnumHelper<ColorCode>::getRandomly()),
          m_age(1),
          m_figureType(TFigureType::A),
          m_figureClass(game_interface::EnumHelper<TFigureClass>::getRandomly())
{
}

std::shared_ptr<TFigureInterface> TFigureBuilder::build()
{
    // assert(m_figureClass != TFigureClass::End);

    switch (getClass()) {
        case TFigureClass::L:
            this->color(ColorCode::green);
            return TFigureL::get(this);
        case TFigureClass::Z:
            this->color(ColorCode::red);
            return TFigureZ::get(this);
        case TFigureClass::I:
            this->color(ColorCode::yellow);
            return TFigureI::get(this);
        case TFigureClass::O:
            this->color(ColorCode::orange);
            return TFigureO::get(this);
        case TFigureClass::T:
            this->color(ColorCode::blue);
            return TFigureT::get(this);
        default:
            assert(0);
    }
}

