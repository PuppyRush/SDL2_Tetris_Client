//
// Created by chaed on 18. 12. 26.
//

#include "Control.h"

#include "sdl2gfx/SDL2_gfxPrimitives.h"

#include "GameInterface/include/Logger.h"
#include "include/SEG_TypeTraits.h"
#include "include/SEG_Event.h"

using namespace seg;

Control::Control(const Control* ctl)
        : GraphicInterface(ctl->getBasic()), m_isBounded(false)
{
    _initializeInCtor();
    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

Control::Control(const ControlBuilder& bld)
        : m_positionRect({ static_cast<int>(bld.getBasic().point.x), static_cast<int>(bld.getBasic().point.y),
                          static_cast<int>(bld.getBasic().width), static_cast<int>(bld.getBasic().height) }),
          GraphicInterface(std::make_shared<ControlBasic>(bld.getBasic()))
{
    _initializeInCtor();
    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

void Control::release()
{
    auto renderer =  getSDLRenderer();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Control::_initializeInCtor()
{
    setPosition({ static_cast<int>(getPoint().x), static_cast<int>(getPoint().y), static_cast<int>(getWidth()), static_cast<int>(getHeight()) });
    setMidPoint({getPoint().x + getWidth() / 2, getPoint().y + getHeight() / 2});
}

void Control::initialize()
{
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
    auto renderer = getWindow()->getSDLRenderer();

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
            filledEllipseRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, m_textWidth / 2, m_textHeight / 2,
                              backColor.r, backColor.g, backColor.b, backColor.a);
            break;

        case BorderBoundaryType::round: {
            filledCircleRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2,
                             std::max(m_textWidth / 2, m_textHeight / 2),
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
    event::EventPusher event{this->getWindow()->getWindowID(), SEG_DRAW, SEG_DRAW_CONTROLLER};
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

    event::EventPusher event{this->getWindow()->getWindowID(), SEG_CONTROLLER, SEG_CLICKED_CONTROLLER};
    event.setTargetId(this->getId());
    event.setUserData(new event::SEG_Click{point, this->getId(), isSelected()});
    event.pushEvent();

    event::EventPusher event_ {this->getWindow()->getWindowID(), SEG_CONTROLLER, SEG_ATTACH_FOCUS};
    event_.setTargetId(this->getId());
    event_.pushEvent();
}

bool Control::isHit(const t_coord x, const t_coord y, const t_coord z) const
{
    return isHit({x, y, z});
}

bool Control::isHit(SEG_Point&& point) const
{
    return isHit(static_cast<const SEG_Point>(std::move(point)));
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
    bool bounded = isHit(event.motion.x, event.motion.y);
    if (bounded)
    {
        event::EventPusher event {getWindow()->getWindowID(), SEG_CONTROLLER, SEG_BOUND};
        event.setTargetId(getId());
        event.pushEvent();
    }
    else
    {
        event::EventPusher event {getWindow()->getWindowID(), SEG_CONTROLLER, SEG_UNBOUND};
        event.setTargetId(getId());
        event.pushEvent();
    }
    return m_isBounded = bounded;
}

bool Control::focus(const SDL_Event& event)
{
    bool bounded = isHit(event.motion.x, event.motion.y);
    if (bounded)
    {
        event::EventPusher event {getWindow()->getWindowID(), SEG_CONTROLLER, SEG_ATTACH_FOCUS};
        event.setTargetId(getId());
        event.pushEvent();
    }
    else
    {
        event::EventPusher event {getWindow()->getWindowID(), SEG_CONTROLLER, SEG_DETACH_FOCUS};
        event.setTargetId(getId());
        event.pushEvent();
    }
    return m_isBounded = bounded;
}


void Control::onDraw()
{
}

void Control::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    onHit({ static_cast<t_coord>(button->x), static_cast<t_coord>(button->y) }, !isSelected());
}