//
// Created by chaed on 18. 12. 28.
//

#include "EditLabel.h"
#include "GameInterface/include/Logger.h"

#include <SEG_Drawer.h>

#include "SDL2EasyGUI/include/SEG_Event.h"
#include "SDL2EasyGUI/include/SEG_TypeTraits.h"

using namespace std;
using namespace seg;

EditLabel::EditLabel(EditLabelBuilder& bld)
        : LabelBasic(bld), m_drawTextCursor(false)
{
    bld.kind(ControlKind::EditLabel);

    m_cursorTimer = make_shared<event::SEG_Timer>(this->getWindow()->getWindowID(), 800);
    m_cursorTimer->userEventData({false,this->getId() });
}

void EditLabel::onDraw()
{
    auto rdr = getSDLRenderer();
    drawer::TextDrawer drawer{ rdr, getFont(), getPoint(), getLabelString() };

    setTextWidth(drawer.getTextWidth());
    setTextHeight(drawer.getTextHeight());

    const auto point = getPoint();
    SDL_Point points[]
        = { {static_cast<int>(point.x + getTextWidth() + 7), point.y + 5},
            {static_cast<int>(point.x + getTextWidth() + 7), point.y + static_cast<int>(getHeight()) - 5},
            {static_cast<int>(point.x + getTextWidth() + 7), point.y + 5} };

    SEG_Color lineColor;
    if (m_drawTextCursor) {
        lineColor = drawer::getInvertedColor(this->getBackgroundColor());
    }
    else {
        lineColor = this->getBackgroundColor();
    }

    SDL_SetRenderDrawColor(rdr, lineColor.r, lineColor.g, lineColor.b, 255);
    SDL_RenderDrawLines(rdr, points, SDL_arraysize(points));

    using namespace game_interface::logger;
    Logger::getInstance().printLog("EditLabel::onTimerEvent", Logger::logger_level::Debug);


    Base::onDraw();
}

void EditLabel::onTimerEvent(const SDL_UserEvent* user)
{
    using namespace event;

    auto userdata = static_cast<SEG_UserEventData*>(user->data1);
    if (userdata == nullptr)
    {
        assert(0);
        return;
    }

    if(m_cursorTimer->isStarted())
    {
        m_drawTextCursor = !m_drawTextCursor;
    }

    refresh();

    Base::onTimerEvent(user);
}

void EditLabel::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{

}

void EditLabel::onAttachFocus(const SDL_UserEvent* user)
{
    if (!m_cursorTimer->isStarted())
    {
        m_cursorTimer->start();
    }

    setSelected(true);

    Base::onAttachFocus(user);
}

void EditLabel::onDetachFocus(const SDL_UserEvent* user)
{
    m_cursorTimer->stop();
    m_drawTextCursor = false;
    setSelected(false);

    Base::onDetachFocus(user);
}

void EditLabel::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    if (!isSelected()) {
        return;
    }

    if (key->type == SDL_KEYDOWN) {
        if (key->keysym.sym == SDLK_BACKSPACE && !isEmpty()) {
            getLabelString().pop_back();
        }
    }

    event::EventPusher event{this->getWindow()->getWindowID(), SEG_CONTROLLER, SEG_ENTER_CONTROLLER};
    event.setTargetId(this->getId());
    event.setUserData(const_cast<SDL_KeyboardEvent*>(key));
    event.pushEvent();

    Base::onKeyboardEvent(key);
}

void EditLabel::onTextInputEvent(const SDL_TextInputEvent* text)
{
    if (!isSelected()) {
        return;
    }

    getLabelString() += (text->text);
    Base::onTextInputEvent(text);
}

void EditLabel::onDrawBackground()
{
    Base::onDrawBackground();
}

void EditLabel::initialize()
{
    Base::initialize();
}

