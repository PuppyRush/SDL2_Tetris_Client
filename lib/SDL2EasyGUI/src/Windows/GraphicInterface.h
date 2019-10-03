//
// Created by chaed on 19. 1. 22.
//

#ifndef GUI_GRAPHICINTERFACE_H
#define GUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/include/SEG_Window.h"
#include "../../include/EventQueue.h"

namespace seg {

class GraphicInterface
{

public:
    using window_type = SEG_Window*;
    using unique_type = SEG_Window::unique_type;

    virtual ~GraphicInterface();

    inline void setWindowTitle(const std::string& str)
    { m_window->setTitle(str); }

    inline void setWindowWidth(const t_size width) noexcept
    {
        m_window->setWidth(width);
    }

    inline void setWindowHeight(const t_size height) noexcept
    {
        m_window->setHeight(height);
    }

    inline const t_size getWindowWidth() const noexcept
    { return m_window->getWidth(); }

    inline const t_size getWindowHeight() const noexcept
    { return m_window->getHeight(); }

    inline SEG_Color getBackgroundColor() const noexcept
    {
        return m_backgroundColor;
    }

    inline void setBackgroundColor(const SEG_Color& background_color) noexcept
    {
        m_backgroundColor = background_color;
    }

    inline void setBackgroundColor(SEG_Color&& background_color) noexcept
    {
        m_backgroundColor = background_color;
    }

    inline void setWindow(const window_type window)
    { m_window = window; }

    inline window_type getWindow() const noexcept
    { return m_window; }

    inline t_id getId() const _GLIBCXX_NOEXCEPT
    {
        return m_data->resourceId;
    }

    inline SEG_Point& getPoint() const _GLIBCXX_NOEXCEPT
    {
        return m_data->point;
    }

    inline void setPoint(const SEG_Point& point) _GLIBCXX_NOEXCEPT
    {
        m_data->point = point;
        m_data->positionRect.x = point.x;
        m_data->positionRect.y = point.y;

        m_data->midPoint = SEG_Point{point.x + m_data->width / 2, point.y + m_data->height / 2};
    }

    inline SEG_Point& getMidPoint() const _GLIBCXX_NOEXCEPT
    {
        return m_data->midPoint;
    }

    inline void setMidPoint(const SEG_Point& point) _GLIBCXX_NOEXCEPT
    {
        /* if (m_data->point.x > point.x) {
             m_data->point.x -= (m_data->point.x - point.x);
         } else {
             m_data->point.x += (point.x - m_data->point.x);
         }

         if (m_data->point.y > point.y) {
             m_data->point.y -= (m_data->point.y - point.y);
         } else {
             m_data->point.y += (point.y - m_data->point.y);
         }*/

        m_data->midPoint = point;
    }

    inline t_size getWidth() const _GLIBCXX_NOEXCEPT
    {
        return m_data->width;
    }

    inline void setWidth(const t_size width) _GLIBCXX_NOEXCEPT
    {
        m_data->width = width;
        m_data->positionRect.w = width;
        m_data->midPoint = SEG_Point{m_data->point.x + width / 2, m_data->midPoint.y};
    }

    inline t_size getHeight() const _GLIBCXX_NOEXCEPT
    {
        return m_data->height;
    }

    void setHeight(const t_size height) _GLIBCXX_NOEXCEPT
    {
        m_data->height = height;
        m_data->positionRect.h = height;
        m_data->midPoint = SEG_Point{m_data->width, m_data->point.y + height / 2};
    }

    inline SEG_TFont& getFont() const _GLIBCXX_NOEXCEPT
    {
        return m_data->font;
    }

    inline void setFont(const SEG_TFont& font) _GLIBCXX_NOEXCEPT
    {
        m_data->font = font;
    }

    inline std::string getName() const _GLIBCXX_NOEXCEPT
    {
        return m_data->name;
    }

    inline void setName(const std::string& name) _GLIBCXX_NOEXCEPT
    {
        m_data->name = name;
    }

    inline bool isEnabled() const _GLIBCXX_NOEXCEPT
    {
        return m_data->enabled;
    }

    inline void setEnabled(const bool enabled) _GLIBCXX_NOEXCEPT
    {
        m_data->enabled = enabled;
    }

    inline ControlKind getKind() const _GLIBCXX_NOEXCEPT
    {
        return m_data->kind;
    }

    inline int getGroup() const _GLIBCXX_NOEXCEPT
    {
        return m_data->group;
    }

    inline void setGroup(const int group) _GLIBCXX_NOEXCEPT
    {
        m_data->group = group;
    }

    inline bool isCarot() const _GLIBCXX_NOEXCEPT
    {
        return m_data->carot;
    }

    inline void setCarot(const bool carot) _GLIBCXX_NOEXCEPT
    {
        m_data->carot = carot;
    }

    inline t_display getDisplay() const _GLIBCXX_NOEXCEPT
    {
        return m_data->display;
    }

    inline void setDisplay(const t_display display) _GLIBCXX_NOEXCEPT
    {
        m_data->display = display;
    }

    inline bool getAutoSize() const _GLIBCXX_NOEXCEPT
    {
        return m_data->autoSize;
    }

    inline BorderBoundaryLineType getBorderBoundaryLineType() const _GLIBCXX_NOEXCEPT
    {
        return m_data->borderLineType;
    }

    inline BorderBoundaryType getBorderBoundaryType() const _GLIBCXX_NOEXCEPT
    {
        return m_data->borderType;
    }

    inline SEG_Color& getBorderLineColor() const _GLIBCXX_NOEXCEPT
    {
        return m_data->borderColor;
    }

    inline int getBorderAngle() const _GLIBCXX_NOEXCEPT
    {
        return m_data->borderAngle;
    }

    inline int getBorderThick() const _GLIBCXX_NOEXCEPT
    {
        return m_data->borderThick;
    }

    inline bool isSelected() const _GLIBCXX_NOEXCEPT
    {
        return m_data->selected;
    }

    inline const bool isMultiselected() const _GLIBCXX_NOEXCEPT
    {
        return m_data->multiselected;
    }

    inline void setMultiselected(bool multiselected) _GLIBCXX_NOEXCEPT
    {
        m_data->multiselected = multiselected;
    }

    inline virtual void setPosition(const SDL_Rect rect) _GLIBCXX_NOEXCEPT
    {
        m_data->positionRect = rect;
    }

    inline virtual SDL_Rect getPosition() const _GLIBCXX_NOEXCEPT
    {
        return m_data->positionRect;
    }

    virtual void initialize() = 0;

    virtual void onDraw() = 0;

    virtual void onDrawBackground() = 0;

    virtual void resize() = 0;

    virtual void refresh() = 0;

protected:

    window_type m_window = nullptr;

    explicit GraphicInterface();

    explicit GraphicInterface(std::shared_ptr<ControlBasic>);

    inline std::shared_ptr<ControlBasic> getBasic() const _GLIBCXX_NOEXCEPT
    {
        return m_data;
    }

    virtual void _drawBackground(const SDL_Rect rect);

    bool _hitTest(const SDL_Rect&, const t_coord& , const t_coord& ) const _GLIBCXX_NOEXCEPT;

    bool _hitTest(const SDL_Rect&, const SEG_Point&) const _GLIBCXX_NOEXCEPT;

    std::shared_ptr<ControlBasic> m_data;

    SEG_Color m_backgroundColor;
};

}

#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
