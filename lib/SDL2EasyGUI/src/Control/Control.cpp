//
// Created by chaed on 18. 12. 26.
//

#include <stdexcept>

#include "Control.h"

#include "sdl2gfx/SDL2_gfxPrimitives.h"

#include "GameInterface/include/Logger.h"
#include "include/SEG_TypeTraits.h"
#include "include/SEG_Event.h"

using namespace seg;

Control::Control(Control* ctl)
        : GraphicInterface(ctl->_getData()), m_isBounded(false), m_textDrawer(getRenderer(), ctl->getFont(), ctl->getPoint(), ctl->getControlText())
{
    _initializeInCtor();
    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

Control::Control(const ControlBuilder& bld)
        : m_positionRect( make_sdlrect(bld.getBasic().point.x, bld.getBasic().point.y,
                          bld.getBasic().width, bld.getBasic().height) ),
    m_textDrawer(getRenderer(), bld.getBasic().font, bld.getBasic().point, bld.getBasic().text),
          GraphicInterface(std::make_shared<ControlData>(bld.getBasic()))
{
    _initializeInCtor();
    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

void Control::release()
{
    auto renderer = getRenderer();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Control::_initializeInCtor()
{
    setPosition( make_sdlrect( getPoint().x, getPoint().y, getWidth(), getHeight()));
    setMidPoint({ getPoint().x + getWidth() / 2, getPoint().y + getHeight() / 2 });

    setControlText(_getData()->text);

    auto wh = drawer::getTextSize(getFont().getTTF_Font(), getControlText());
    auto width = wh.first > getWidth() ? getWidth() : wh.first;
    auto height = wh.second > getHeight() ? getHeight() : wh.second;
    setControlTextWidth(width);
    setControlTextHeight(height);


    SEG_Point point = make_segpoint( getPoint().x + (getWidth() - getControlTextWidth()) / 2,
                                    getPoint().y + (getHeight() - getControlTextHeight()) / 2) ;

    setControlTextPositionX(point.x);
    setControlTextPositionY(point.y);
}

void Control::initialize()
{
    m_isInitailize = true;
    setSelected(isSelected());

    if (getGroup() != GroupControlManager::NONE) {
        GroupControlManager::getInstance().add(m_data->group, m_data->resourceId);
        if (isMultiselected()) {
            GroupControlManager::getInstance().setMultiselect(m_data->group);
        }
    }

}

void Control::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    switch (key->keysym.sym) {
        case SDLK_RETURN:
            if (isActivated()) {
                onHit(getMidPoint(), true);
            }
            break;
    }

    refresh();
}

void Control::onTextInputEvent(const SDL_TextInputEvent* text)
{
    refresh();
}

void Control::onDrawBackground()
{
    const auto backColor = getBackgroundColor();
    auto renderer = getRenderer();

    SDL_Rect rect{getPosition()};
    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick() * 2) + 1;
    rect.w = (rect.w - getBorderThick() * 2) + 1;

    switch (getBorderBoundaryType()) {
        case BorderBoundaryType::angle:
            SDL_SetRenderDrawColor(renderer, backColor.r, backColor.g, backColor.b, backColor.a);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderDrawRect(renderer, &rect);
            break;

        case BorderBoundaryType::roundedAngle:
            roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, 10,
                           backColor.r, backColor.g, backColor.b, backColor.a);
            break;
        case BorderBoundaryType::ellipse:
            filledEllipseRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, getControlTextWidth() / 2, getControlTextHeight() / 2,
                              backColor.r, backColor.g, backColor.b, backColor.a);
            break;

        case BorderBoundaryType::round: {
            filledCircleRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2,
                             std::max(getControlTextWidth() / 2, getControlTextHeight() / 2),
                             backColor.r, backColor.g, backColor.b, backColor.a);

            break;
        }
    }

}

void Control::onVirtualDraw()
{
    onDrawBackground();
    onDraw();
}

#include <tuple>
void Control::refresh()
{
    event::EventPusher event{this->getSEGWindow()->getWindowID(), SEG_DRAW, SEG_DRAW_CONTROLLER};
    event.setTargetId(this->getId());
    event.pushEvent();
}

void Control::setSelected(bool selected)
{
    m_data->selected = selected;
    if (selected) {
        GroupControlManager::getInstance().select(getGroup(), getId());
    }
    // refresh();
}

void Control::onHit(const SEG_Point& point, const bool hit)
{
    setSelected(hit);

    setActivating(true);

    event::EventPusher event{this->getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_CLICKED_CONTROLLER};
    event.setTargetId(this->getId());
    event.setUserData(new event::SEG_Click{point, this->getId(), isSelected()});
    event.pushEvent();

    event::EventPusher event_ {this->getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_ATTACH_FOCUS};
    event_.setTargetId(this->getId());
    event_.pushEvent();
}

bool Control::isHit(const SEG_Point& point) const
{
    const auto& pos = GraphicInterface::getPosition();
    if ((pos.x <= point.x && point.x <= pos.x + pos.w) && (pos.y <= point.y && point.y <= pos.y + pos.h)) {
        return true;
    } else {
        return false;
    }
}

bool Control::bound(const SDL_Event& event)
{
    bool bounded = isHit( make_segpoint(event.motion.x, event.motion.y));
    if (bounded)
    {
        event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_BOUND};
        event.setTargetId(getId());
        event.pushEvent();
    }
    else
    {
        event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_UNBOUND};
        event.setTargetId(getId());
        event.pushEvent();
    }
    return m_isBounded = bounded;
}

bool Control::focus(const SDL_Event& event)
{
    bool bounded = isHit( make_segpoint(event.motion.x, event.motion.y));
    if (bounded)
    {
        event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_ATTACH_FOCUS};
        event.setTargetId(getId());
        event.pushEvent();
    }
    else
    {
        event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_DETACH_FOCUS};
        event.setTargetId(getId());
        event.pushEvent();
    }
    return m_isBounded = bounded;
}


void Control::onDraw()
{
    m_textDrawer.drawText();
}

void Control::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    onHit( make_segpoint(button->x, button->y), !isSelected());
}

void Control::setControlText(const char* ch)
{
    m_textDrawer.setText(ch);
}

void Control::setControlText(std::string&& str)
{
    m_textDrawer.setText(str);
}

void Control::setControlText(const std::string& str)
{
    m_textDrawer.setText(str);
}

std::string& Control::getControlText() noexcept
{
    return m_textDrawer.getText();
}

void Control::setControlTextPostion(const SDL_Rect rect)
{
    m_textDrawer.setPosition(rect);
}

SDL_Rect Control::getControlTextPostion(const SDL_Rect rect) const noexcept
{
    return m_textDrawer.getPosition();
}

void Control::setControlTextPositionX(const t_coord coord)
{
    m_textDrawer.setPositionX(coord);
}

t_coord Control::getControlTextPositionX() const noexcept
{
    return m_textDrawer.getPositionX();
}

void Control::setControlTextPositionY(const t_coord coord)
{
    m_textDrawer.setPositionY(coord);
}

t_coord Control::getControlTextPositionY() const noexcept
{
    return m_textDrawer.getPositionY();
}