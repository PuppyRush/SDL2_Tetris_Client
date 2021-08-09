//
// Created by chaed on 19. 1. 22.
//

#ifndef SDL2EASYGUI_GRAPHICINTERFACE_H
#define SDL2EASYGUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "../../include/SEG_Event.h"
#include "../../include/SEG_Window.h"
#include "../../include/EventQueue.h"



#include "SDL2EasyGUI/src/Windows/EventListener.h"

namespace seg {

class GraphicInterface : public EventListener
{

public:
    using window_type = SEG_Window*;
    using unique_type = SEG_Window::unique_type;

    virtual ~GraphicInterface();

    inline void setWindowTitle(const std::string& str)
    { m_window->setTitle(str); }

    inline void setWindowWidth(t_size width) noexcept
    {
        m_window->setWidth(width);
    }

    inline void setWindowHeight(t_size height) noexcept
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

    inline void setWindow(window_type window)
    { m_window = window; }

    inline window_type getSEGWindow() const noexcept
    { return m_window; }

    inline SEG_Window::window_type getWindow() const noexcept
    {
        return getSEGWindow()->getWindow();
    }

    inline SEG_Window::renderer_type getRenderer() const noexcept
    {
        return getSEGWindow()->getRenderer();
    }

    inline unique_type getId() const noexcept
    {
        return m_data->resourceId;
    }

    inline SEG_Point getPoint() const noexcept
    {
        return make_segpoint(m_data->position.x, m_data->position.y);
    }

    inline void setPoint(SEG_Point& point) noexcept
    {
        m_data->position.x = point.x;
        m_data->position.y = point.y;
        m_data->midPoint = SEG_Point{point.x + m_data->width / 2, point.y + m_data->height / 2};
    }

    inline SEG_Point getMidPoint() const noexcept
    {
        return m_data->midPoint;
    }
	
    inline void setMidPoint(SEG_Point&& point) noexcept
    {
        m_data->midPoint = point;
    }

    inline void setMidPoint(const SEG_Point& point) noexcept
    {
        m_data->midPoint = point;
    }

    inline t_size getWidth() const noexcept
    {
        return m_data->width;
    }

    virtual inline void setWidth(t_size width) noexcept
    {
        m_data->width = width;
        m_data->position.w = width;
        m_data->midPoint = SEG_Point{m_data->position.x + width / 2, m_data->midPoint.y};
    }

    inline t_size getHeight() const noexcept
    {
        return m_data->height;
    }

    virtual void setHeight(t_size height) noexcept
    {
        m_data->height = height;
        m_data->position.h = height;
        m_data->midPoint = SEG_Point{m_data->width, m_data->position.y + height / 2};
    }

    inline SEG_TFont getFont() const noexcept
    {
        return m_data->font;
    }

    inline void setFont(SEG_TFont&& font) noexcept
    {
        m_data->font = font;
    }

    inline void setFont(const SEG_TFont& font) noexcept
    {
        m_data->font = font;
    }

    inline std::string getName() const noexcept
    {
        return m_data->name;
    }

    inline void setName(std::string&& name)
    {
        m_data->name = name;
    }

    inline void setName(const std::string& name)
    {
        m_data->name = name;
    }

    inline bool isEnabled() const noexcept
    {
        return m_data->enabled;
    }

    inline void setEnabled(bool enabled) noexcept
    {
        m_data->enabled = enabled;
    }

    inline ControlKind getKind() const noexcept
    {
        return m_data->kind;
    }

    inline int getGroup() const noexcept
    {
        return m_data->group;
    }

    inline void setGroup(int group) noexcept
    {
        m_data->group = group;
    }

    inline bool isCarot() const noexcept
    {
        return m_data->carot;
    }

    inline void setCarot(bool carot) noexcept
    {
        m_data->carot = carot;
    }

    inline t_display getDisplay() const noexcept
    {
        return m_data->display;
    }

    inline void setDisplay(t_display display) noexcept
    {
        m_data->display = display;
    }

    inline bool getAutoSize() const noexcept
    {
        return m_data->autoSize;
    }

    inline BorderBoundaryLineType getBorderBoundaryLineType() const noexcept
    {
        return m_data->borderLineType;
    }

    inline BorderBoundaryType getBorderBoundaryType() const noexcept
    {
        return m_data->borderType;
    }

    inline SEG_Color getBorderLineColor() const noexcept
    {
        return m_data->borderColor;
    }

    inline int getBorderAngle() const noexcept
    {
        return m_data->borderAngle;
    }

    inline int getBorderThick() const noexcept
    {
        return m_data->borderThick;
    }

    inline bool isSelected() const noexcept
    {
        return m_data->selected;
    }

    inline const bool isMultiselected() const noexcept
    {
        return m_data->multiselected;
    }

    inline void setMultiselected(bool multiselected) noexcept
    {
        m_data->multiselected = multiselected;
    }

    inline virtual void setPosition(SDL_Rect rect) noexcept
    {
        m_data->position = rect;
    }

    inline virtual SDL_Rect getPosition() const noexcept
    {
        return m_data->position;
    }

    inline virtual void setVisible(bool b) noexcept
    {
        m_data->visible = b;
    }

    inline virtual bool isVisible() const noexcept
    {
        return m_data->visible;
    }

    inline virtual const SDL_Rect& getConstPosition() const noexcept
    {
        return m_data->position;
    }


    virtual void initialize() = 0;

    virtual void onDraw();

    virtual void onDrawBackground() = 0;

    virtual void resize() = 0;

    virtual void refresh() = 0;

    virtual bool bound(const SDL_Event& event) = 0;

    virtual bool focus(const SDL_Event& event) = 0;

protected:


    explicit GraphicInterface(window_type window);

    explicit GraphicInterface(const std::shared_ptr<ControlData>& ctl);

    inline const std::shared_ptr<ControlData> getData() const noexcept
    {
        return m_data;
    }

    inline void setId(const t_id id) const noexcept
    {
        m_data->resourceId = id;
    }

    virtual void _drawBackground(const SDL_Rect rect);

private:

    void _release();

private:

    window_type m_window = nullptr;
    std::shared_ptr<ControlData> m_data;
    SEG_Color m_backgroundColor;
};

}

#endif //SDL2EASYGUI_TGRAPHICINTERFACE_H
