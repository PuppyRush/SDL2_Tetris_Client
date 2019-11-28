//
// Created by chaed on 18. 12. 26.
//

#include "Control.h"

#include "SDL2EasyGUI/include/SEG_TypeTraits.h"
#include "SDL2EasyGUI/include/SEG_Event.h"

using namespace seg;

Control::Control(const Control* ctl)
        : GraphicInterface(ctl->getBasic())
{
    _initializeInCtor();
    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

Control::Control(const ControlBuilder& bld)
        : m_positionRect({bld.getBasic().point.x, bld.getBasic().point.y,
                          bld.getBasic().width, bld.getBasic().height}),
          GraphicInterface(std::make_shared<ControlBasic>(bld.getBasic()))
{
    _initializeInCtor();
    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

void Control::_initializeInCtor()
{
    setPosition({getPoint().x, getPoint().y, getWidth(), getHeight()});
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
            if (isHitting()) {
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

void Control::refresh()
{
    event::EventPusher event{this->getWindow()->getWindowID(), this->getId(), SEG_DRAW_CONTROLLER};
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

    event::EventPusher event{this->getWindow()->getWindowID(), this->getId(), SEG_CLICKED_CONTROLLER};
    event.setUserData(new event::SEG_Click{point, this->getId(), isSelected()});
    event.pushEvent();
}

bool Control::isHit(const t_coord x, const t_coord y, const t_coord z) const
{
    return isHit({x, y, z});
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

//event에 대한 bound 검사만 수행한다.
bool Control::isBounded(const SDL_Event& event)
{
    bool bounded{false};
    switch (event.type) {
        case SDL_MOUSEMOTION   :
            bounded = isHit(event.motion.x, event.motion.y);
            break;
        default:
            return false;
    }

    if (m_isBounded != bounded) {

        if (bounded) {
            event::EventPusher event{getWindow()->getWindowID(), getId(), ATTACH_FOCUS};
            event.pushEvent();
        } else {
            event::EventPusher event{getWindow()->getWindowID(), getId(), DETACH_FOCUS};
            event.pushEvent();
        }
    }

    return m_isBounded = bounded;
}

bool Control::isHitting(const SDL_Event& event) noexcept
{
    if (m_isHitting) {
        return true;
    }

    bool hit = false;
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN   :
        case SDL_MOUSEBUTTONUP   :
            if (hit = isHit(event.motion.x, event.motion.y)) {
                onHit({event.motion.x, event.motion.y}, !isSelected());
            }
            break;
        case SDL_KEYDOWN:
            hit = true;
            onHit(getMidPoint(), hit);
            break;
        default:;
    }
    return m_isHitting = hit;
}

void Control::drawBackground(const SDL_Rect rect, const SEG_Color color)
{
    auto renderer = getWindow()->getSDLRenderer();

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

}

void Control::onDraw()
{
}
