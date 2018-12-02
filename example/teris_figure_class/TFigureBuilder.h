#pragma once


#include "TFigure.h"
#include "TFigureL.h"
#include "TFigureZ.h"
#include "TFigureI.h"
#include "TFigureT.h"
#include "TFigureO.h"
#include "TType.h"

namespace tetris
{

class TFigureBuilder {
public:

    TFigureBuilder(const TPoint &point);
    virtual ~TFigureBuilder() {}

    TFigureBuilder *color(const TColor &color);
    TFigureBuilder *type(const TFigureType &type);
    TFigureBuilder *age(const t_age &age);
    TFigureBuilder *figure(const TFigureClass& figure);

    inline const TPoint getPoint() const noexcept { return m_point; }
    inline const TColor getColor() const noexcept { return m_color; }
    inline const TFigureType getType() const noexcept { return m_figureType; }
    inline const t_age getAge() const noexcept { return m_age; }
    inline const t_size getHeight() const noexcept { return m_height; }
    inline const t_size getWidth() const noexcept { return m_width; }
    inline constexpr const TFigureClass getClass() const noexcept { return m_figureClass; }

    std::shared_ptr<TFigure> build();

private:
    inline void width(const t_size width)
    { m_width = width;}

    inline void height(const t_size height)
    { m_height = height;}

    t_size m_width;
    t_size m_height;
    TColor m_color;
    TPoint m_point;
    TFigureType m_figureType;
    TFigureClass  m_figureClass;
    t_age m_age;
    
};

}
