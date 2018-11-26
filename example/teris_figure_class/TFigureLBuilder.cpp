//
// Created by chaed on 18. 11. 25.
//

#include <random>

#include "TypeTraits.h"
#include "TFigureLBuilder.h"
#include "TFigureL.h"

using namespace tetris;

TFigureLBuilder::TFigureLBuilder(const TPoint& point)
        :TFigureBuilder(point)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution
        (static_cast<int>(TFigureClass::Begin), static_cast<int>(TFigureClass::End));
    
    TFigureClass somethingFigure = TFigureClass(distribution(generator));
}

TFigureLBuilder::~TFigureLBuilder()
{}

TFigureLBuilder* TFigureLBuilder::color(const TColor& color)
{
    this->m_color = color;
    return this;
}

TFigureLBuilder* TFigureLBuilder::type(const TFigureType& type)
{
    this->m_figureType = type;
    return this;
}

TFigureLBuilder* TFigureLBuilder::age(const t_age& age)
{
    this->m_age = age;
    return this;
}

std::shared_ptr<TFigure> TFigureLBuilder::build() const
{
    return TFigureL::get(this);
}

