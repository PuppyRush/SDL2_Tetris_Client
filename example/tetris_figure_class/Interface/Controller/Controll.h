//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_CONTROLL_H
#define CONTROLLER_CONTROLL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <atomic>

#include "THeader.h"
#include "Interface/GUI/Window.h"
#include "ControllBuilder.h"
#include "GroupControllManager.h"
#include "Interface/GUI/GraphicInterface.h"

SDL_TETRIS_BEGIN

class Controll : public GraphicInterface{

public:

    inline const t_id getId() const noexcept{
        return m_basic->id;
    }
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
    inline const bool getAutoSize() const noexcept{
        return  m_basic->autoSize;
    }
    inline auto getCallbackAry() const noexcept{
        return  m_basic->callbackAry;
    }
    inline const bool isSelected() const noexcept{
        return m_basic->selected;
    }

    void setSelected(bool selected);
    const bool isHit(const TPoint& point);
    virtual void draw() override;
    virtual void clicked();
    virtual void initialize();
protected:

    Controll(const ControllBuilder& bld, const TControllKind kind);

    inline const bool isMultiselected() const noexcept{
        m_basic->multiselected;
    }
    inline void setMultiselected(bool multiselected) noexcept{
        m_basic->multiselected = multiselected;
    }

    virtual void lButtonClicked(){}


private:

    std::shared_ptr<TControllBasic> m_basic;
    const Window* m_window;

    void _drawCarot();
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H
