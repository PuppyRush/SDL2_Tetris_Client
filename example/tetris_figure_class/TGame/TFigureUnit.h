#pragma once

#include "THeader.h"

SDL_TETRIS_BEGIN

class TFigureUnit {
public:
    
    TFigureUnit();
    TFigureUnit(const TPoint point, const t_age age, const TColorCode color, const UnitType type);
    ~TFigureUnit();
    
    bool operator!=(const TFigureUnit& unit);
    
    const TPoint getPoint () const;
    void setPoint (const TPoint &m_point);
    
    const t_age getAge () const;
    void setAge (t_age m_age);
    
    const TColorCode getColor () const;
    void setColor (TColorCode m_color);

    UnitType getType () const;
    void setType (UnitType m_type);
    
    static TFigureUnit& getDefaultUnit()
    {
        static TFigureUnit unit(TPoint(0,0), 0, TColorCode::none, UnitType::Empty);
        return unit;
    }

private:
    TPoint m_point;
    t_age m_age;
    TColorCode m_color;
    UnitType m_type;
    
};

SDL_TETRIS_END