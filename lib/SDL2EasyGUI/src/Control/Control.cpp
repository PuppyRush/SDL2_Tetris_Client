//
// Created by chaed on 18. 12. 26.
//

#include <stdexcept>

#include <SDL2/SDL2_gfxPrimitives.h>

#include "Control.h"
#include "GameInterface/include/Logger.h"
#include "include/SEG_TypeTraits.h"
#include "include/SEG_Event.h"

using namespace seg;


ControlBuilder::ControlBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
    :ControlBuilderBase(window)
{
    m_basic.position.x = point.x;
    m_basic.position.y = point.y;
    m_basic.text = str;
}

ControlBuilder::ControlBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
    : ControlBuilderBase(window)
{
    m_basic.position.x = point.x;
    m_basic.position.y = point.y;
    m_basic.text = str;
}


Control::Control(Control* ctl)
        : GraphicInterface(ctl->getData()), m_isBounded(false), m_textDrawer(getRenderer(), ctl->getFont(), ctl->getPoint(), ctl->getControlText()),
          GraphicComponent(ctl)
{
    _initializeInCtor();
}

Control::Control(const ControlBuilder& bld)
        : m_textDrawer(getRenderer(), bld.getBasic().font, make_segpoint(bld.getBasic().position.x, bld.getBasic().position.y), bld.getBasic().text),
          GraphicInterface(std::make_shared<ControlData>(bld.getBasic())),
          GraphicComponent(this)
{
    setPosition(make_sdlrect(bld.getBasic().position.x, bld.getBasic().position.y, bld.getBasic().width, bld.getBasic().height));

    _initializeInCtor();
}

Control::Control(const ControlBuilderBase& bld)
    : m_textDrawer(getRenderer(), bld.getBasic().font, make_segpoint(bld.getBasic().position.x, bld.getBasic().position.y), bld.getBasic().text),
    GraphicInterface(std::make_shared<ControlData>(bld.getBasic())), 
    GraphicComponent(this)

{
    _initializeInCtor();
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
    setBackgroundColor(getData()->backgroundColor);
    setPosition( make_sdlrect( getPoint().x, getPoint().y, getWidth(), getHeight()));
    setMidPoint({ getPoint().x + getWidth() / 2, getPoint().y + getHeight() / 2 });

    setControlText(getData()->text);

    auto wh = drawer::getTextSize(getFont().getTTF_Font(), getControlText());
    auto width = wh.first > getWidth() ? getWidth() : wh.first;
    auto height = wh.second > getHeight() ? getHeight() : wh.second;
    setControlTextWidth(width);
    setControlTextHeight(height);


    SEG_Point point = make_segpoint( getPoint().x + (getWidth() - getControlTextWidth()) / 2,
                                    getPoint().y + (getHeight() - getControlTextHeight()) / 2) ;

    setControlTextPositionX(point.x);
    setControlTextPositionY(point.y);


#ifdef SEG_DEBUG
    m_positionDrawer.setPoint(getPoint());
    m_positionDrawer.setRenderer(getRenderer());
    m_positionDrawer.setSize(14);
    m_positionDrawer.setColor(ColorCode::green);
#endif
}

void Control::initialize()
{
    m_isInitailize = true;
    setSelected(isSelected());

    if (getGroup() != GroupControlManager::NONE) {
        GroupControlManager::getInstance().add( getData()->group, getData()->resourceId);
        if (isMultiselected()) {
            GroupControlManager::getInstance().setMultiselect(getData()->group);
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

void Control::refresh()
{
    event::EventPusher event{this->getSEGWindow()->getWindowID(), SEG_DRAW, SEG_DRAW_CONTROLLER};
    event.setTargetId(this->getId());
    event.pushEvent();
}

void Control::setSelected(bool selected)
{
    getData()->selected = selected;
    if (selected) {
        GroupControlManager::getInstance().select(getGroup(), getId());
    }
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

void Control::onEvent(const SDL_Event& event)
{
    GraphicInterface::onEvent(event);

    const auto end = endComponent();
    for (auto it = beginComponent(); it != end; it++)
    {
        (*it)->onEvent(event);
    }

}


void Control::onDraw()
{
    m_textDrawer.drawText();

    const auto end = endComponent();
    for (auto it = beginComponent(); it != end; it++)
    {
        (*it)->onDraw();
    }
}

void Control::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
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

const std::string& Control::getControlText() const noexcept
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