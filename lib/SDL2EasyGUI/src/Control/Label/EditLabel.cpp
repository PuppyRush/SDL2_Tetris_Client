//
// Created by chaed on 18. 12. 28.
//

#include "EditLabel.h"
#include "GameInterface/include/Logger.h"

#include "SEG_Drawer.h"

#include "include/SEG_Event.h"
#include "include/SEG_TypeTraits.h"

using namespace std;
using namespace seg;

EditLabel::EditLabel(EditLabelBuilder& bld)
    : LabelBasic(bld), m_drawTextCursor(false), m_textWidth(new int), m_textHeight(new int)
{
    bld.kind(ControlKind::EditLabel);

    m_cursorTimer = make_shared<event::SEG_Timer>(this->getSEGWindow()->getWindowID(), 800);
    m_cursorTimer->userEventData({false,this->getId() });
}

EditLabel::~EditLabel()
{
    if (m_textWidth)
        delete m_textWidth;
    if (m_textHeight)
        delete m_textHeight;
}

void EditLabel::onDraw()
{
    const auto point = getPoint();
    SDL_Point points[]
        = { make_sdlpoint(point.x + getControlTextWidth() + 7, point.y + 5),
            make_sdlpoint(point.x + getControlTextWidth() + 7, point.y + getHeight() - 5),
            make_sdlpoint(point.x + getControlTextWidth() + 7, point.y + 5) };

    SEG_Color lineColor;
    if (m_drawTextCursor) {
        lineColor = drawer::getInvertedColor(this->getBackgroundColor());
    }
    else {
        lineColor = this->getBackgroundColor();
    }

    SDL_SetRenderDrawColor(getRenderer(), lineColor.r, lineColor.g, lineColor.b, 255);
    SDL_RenderDrawLines(getRenderer(), points, SDL_arraysize(points));

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
           getControlText().pop_back();
        }
    }

    event::EventPusher event{getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_ENTER_CONTROLLER};
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

    getControlText() += (text->text);


    TTF_Font* font = TTF_OpenFont(getFont().fontName.c_str(), getFont().size);
    TTF_SizeText(font, getControlText().c_str(), m_textWidth, m_textHeight);
    setControlTextWidth(*m_textWidth);
    setControlTextHeight(*m_textHeight);

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

