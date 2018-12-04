#pragma once

#include "../Common/TType.h"

SDL_TETRIS_BEGIN

class TFigureUnit {
public:
    
    enum class UnitType : tetris::t_type
    {
        Fill,
        Empty
    };
    
    TFigureUnit();
    TFigureUnit(const TPoint point, const t_age age, const TColor color, const UnitType type);
    ~TFigureUnit();
    
    bool operator!=(const TFigureUnit& unit);
    
    const TPoint getPoint () const;
    void setPoint (const TPoint &m_point);
    
    const t_age getAge () const;
    void setAge (t_age m_age);
    
    const TColor getColor () const;
    void setColor (TColor m_color);
    
    UnitType getType () const;
    void setType (UnitType m_type);
    
    static TFigureUnit& getDefaultUnit()
    {
        static TFigureUnit unit(TPoint(0,0), 0,TColor::none, UnitType::Empty);
        return unit;
    }

private:
    TPoint m_point;
    t_age m_age;
    TColor m_color;
    UnitType m_type;
    
};

SDL_TETRIS_END