#ifndef TETRIS_TFIGUREUNIT_H
#define TETRIS_TFIGUREUNIT_H

#if _MSC_VER > 1200
  #pragma once
#endif

#include "Tetris/Common/THeader.h"

SDL_TETRIS_BEGIN

class TFigureUnit final {
public:

    TFigureUnit();
    TFigureUnit(const sdleasygui::TPoint point, const t_age age, const sdleasygui::ColorCode color, const UnitType type);
    ~TFigureUnit();

    bool operator!=(const TFigureUnit &unit);

    inline const sdleasygui::TPoint &getPoint() const noexcept {
        return m_point;
    }
    inline t_age getAge() const noexcept {
        return m_age;
    }
    inline const sdleasygui::TColor &getColor() const noexcept {
        return m_color;
    }
    inline const UnitType getType() const noexcept {
        return m_type;
    }

    inline void set(const sdleasygui::TPoint &m_point) {
        this->m_point = m_point;
    }
    inline void set(sdleasygui::TPoint &&m_point) {
        this->m_point = m_point;
    }
    inline void set(const t_age age) noexcept {
        this->m_age = age;
    }
    inline void set(const sdleasygui::TColor &color) noexcept {
        this->m_color = color;
    }
    inline void set(sdleasygui::TColor &&color) noexcept {
        this->m_color = color;
    }

    inline void set(const UnitType &m_type) noexcept {
        this->m_type = m_type;
    }

    static TFigureUnit &getDefaultUnit() {
        static TFigureUnit unit(sdleasygui::TPoint(0, 0), 0, sdleasygui::ColorCode::none, UnitType::Empty);
        return unit;
    }

private:
    sdleasygui::TPoint m_point;
    t_age m_age;
    sdleasygui::TColor m_color;
    UnitType m_type;
};

SDL_TETRIS_END

#endif
