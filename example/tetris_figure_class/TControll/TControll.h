//
// Created by chaed on 18. 12. 26.
//

#ifndef TETRIS_FIGURE_CLASS_TCONTROLL_H
#define TETRIS_FIGURE_CLASS_TCONTROLL_H

#include <atomic>

#include "THeader.h"
#include "TControll/TControllBuilder.h"

SDL_TETRIS_BEGIN

class TControll {

public:

    inline const TPoint &getPoint() const noexcept{
        return m_basic->point;
    }

    inline void setPoint(const TPoint &point) noexcept{
        m_basic->point = point;
    }
    inline const t_size getWidth() const noexcept{
        return  m_basic->width;
    }
    inline void setWidth(t_size width) noexcept{
        m_basic->width = width;
    }
    inline const t_size getHeight() const noexcept{
        return m_basic->height;
    }
    inline void setHeight(t_size height) noexcept{
        m_basic->height = height;
    }
    inline const TFont& getFont() const noexcept{
        return  m_basic->font;
    }
    inline void setFont(const TFont &font) noexcept{
        m_basic->font = font;
    }
    inline const TColor getBackground_color() const noexcept{
        return  m_basic->background_color;
    }
    inline void setBackground_color(const TColor &background_color) noexcept{
        m_basic->background_color = background_color;
    }
    inline const std::string getName() const noexcept{
        return   m_basic->name;
    }
    inline void setName(const std::string &name) noexcept{
        m_basic->name = name;
    }
    inline const bool isEnabled() const noexcept{
        return  m_basic->enabled;
    }
    inline void setEnabled(bool enabled) noexcept{
        m_basic->enabled = enabled;
    }
    inline const TControllKind getKind() const noexcept{
        return  m_basic->kind;
    }
    inline const int getGroup() const noexcept{
        return m_basic->group;
    }
    inline void setGroup(int group) noexcept{
        m_basic->group = group;
    }
    inline const bool isCarot() const noexcept{
        return  m_basic->carot;
    }
    inline void setCarot(bool carot) noexcept{
        m_basic->carot = carot;
    }
    inline const TDisplay getDisplay() const noexcept{
        return m_basic->display;
    }
    inline void setDisplay(TDisplay display) noexcept{
        m_basic->display = display;
    }

protected:

    TControll(const TControllBuilder& bld, const TControllKind kind);

    inline const bool isMultiselected() const noexcept{
        m_basic->multiselected;
    }
    inline void setMultiselected(bool multiselected) noexcept{
        m_basic->multiselected = multiselected;
    }
    inline const bool isClicked() const noexcept{
        m_basic->clicked;
    }
    inline void setClicked(bool clicked) noexcept{
        m_basic->clicked = clicked;
    }

    virtual void lButtonClicked(){}


private:

    std::shared_ptr<TControllBasic> m_basic;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H
