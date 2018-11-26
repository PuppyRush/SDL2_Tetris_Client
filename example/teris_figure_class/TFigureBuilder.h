#pragma once

#include "TFigure.h"

namespace tetris
{

class TFigureBuilder {
public:
    
    virtual ~TFigureBuilder() {}

    virtual TFigureBuilder *color(const TColor &color) = 0;
    virtual TFigureBuilder *type(const TFigureType &type) = 0;
    virtual TFigureBuilder *age(const t_age &age) = 0;
    virtual std::shared_ptr<tetris::TFigure> build() const = 0;
    
    
    
    inline const TPoint getPoint() const noexcept { return m_point; }
    inline const TColor getColor() const noexcept { return m_color; }
    inline const TFigureType getType() const noexcept { return m_figureType; }
    inline const t_age getAge() const noexcept { return m_age; }
    inline const t_size getHeight() const noexcept { return m_height; }
    inline const t_size getWidth() const noexcept { return m_width; }

protected:
    
    TFigureBuilder(const TPoint &point);
    
    t_size m_width;
    t_size m_height;
    TColor m_color;
    TPoint m_point;
    TFigureType m_figureType;
    t_age m_age;

private:
    inline void width(const t_size width)
    { m_width = width;}

    inline void height(const t_size height)
    { m_height = height;}
    
    
};

}