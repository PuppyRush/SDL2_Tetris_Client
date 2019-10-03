//
// Created by chaed on 18. 12. 28.
//

#include "EditLabel.h"
#include "SDL2EasyGUI/include/SEG_Event.h"
#include "SDL2EasyGUI/include/SEG_TypeTraits.h"
#include <SEG_Drawer.h>


using namespace std;
using namespace seg;

EditLabel::EditLabel(EditLabelBuilder& bld)
        : LabelBasic(bld), m_labelBasic(bld.m_editBasic)
{
    bld.kind(ControlKind::EditLabel);

    m_textCursorTimerAdder = make_shared<event::TimerAdder>(this->getId(), 700);
}

void EditLabel::onDraw()
{

    LabelBasic::onDraw();
}

void EditLabel::onTimerEvent(const SDL_UserEvent* user)
{
    t_timer id = *static_cast<t_timer*>(user->data1);
    if(id == m_textCursorTimer)
    {
        m_textCursor = !m_textCursor;
        if (!m_labelString.empty()) {

            drawer::TextDrawer drawer{getSDLRenderer(), getFont(), getPoint(), getName()};

            setTextWidth(drawer.getTextWidth());
            setTextHeight(drawer.getTextHeight());

            const auto point = getPoint();
            SDL_Point points[]
                    = {{static_cast<int>(point.x + getTextWidth() + 7), point.y + 5},
                       {static_cast<int>(point.x + getTextWidth() + 7), point.y + static_cast<int>(getHeight()) - 5},
                       {static_cast<int>(point.x + getTextWidth() + 7), point.y + 5}};

            SEG_Color lineColor;
            if (m_textCursor) {
                lineColor = drawer::getInvertedColor(this->getBackgroundColor());
            } else {
                lineColor = this->getBackgroundColor();
            }

            SDL_SetRenderDrawColor(getWindow()->getSDLRenderer(), lineColor.r, lineColor.g, lineColor.b, 255);
            SDL_RenderDrawLines(getWindow()->getSDLRenderer(), points, SDL_arraysize(points));

            refresh();
        }
    }
}

void EditLabel::onUserEvent(const SDL_UserEvent* user)
{
    LabelBasic::onUserEvent(user);
}

void EditLabel::onAttachFocus()
{
    if (m_textCursorTimer == NULL_TIMER_ID) {
        m_textCursorTimer = m_textCursorTimerAdder->addTimer();
        m_textCursor = true;
        setSelected(true);
    }
}

void EditLabel::onDetachFocus()
{
    SDL_RemoveTimer(m_textCursorTimer);
    m_textCursor = false;
    m_textCursorTimer = NULL_TIMER_ID;
    setSelected(false);
}

void EditLabel::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    if (!isSelected()) {
        return;
    }

    if (key->type == SDL_KEYDOWN) {
        if (key->keysym.sym == SDLK_BACKSPACE && !m_labelString.empty()) {
            m_labelString.pop_back();
        }
    }

    event::EventPusher event{this->getWindow()->getWindowID(), this->getId(), SEG_ENTER_CONTROLLER};
    event.setUserData(const_cast<SDL_KeyboardEvent*>(key));
    event.pushEvent();

    LabelBasic::onKeyboardEvent(key);
}

void EditLabel::onTextInputEvent(const SDL_TextInputEvent* text)
{
    if (!isSelected()) {
        return;
    }

    m_labelString.append(text->text);
    LabelBasic::onTextInputEvent(text);
}

void EditLabel::onDrawBackground()
{
    LabelBasic::onDrawBackground();
}

void EditLabel::initialize()
{
    LabelBasic::initialize();
}

