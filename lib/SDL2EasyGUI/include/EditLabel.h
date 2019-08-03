//
// Created by chaed on 18. 12. 28.
//

#ifndef CONTROLLER_EDITLABEL_H
#define CONTROLLER_EDITLABEL_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/src/Controller/Label/LabelBasic.h"
#include "SDL2EasyGUI/include/SEG_Event.h"

namespace seg {

typedef struct EditLabelBasic
{
    bool canWritable = true;
    bool canReadable = true;
    bool isOnlyNumber = false;
    bool isOnlyString = false;
    t_size maxlen = 20;
    std::string editstring;
} EditLabelBasic;

class EditLabelBuilder;

class EditLabel : public LabelBasic
{

public:
    virtual ~EditLabel() = default;

    explicit EditLabel(EditLabelBuilder& bld);

    inline void clearString() _GLIBCXX_NOEXCEPT
    {
        m_labelString.clear();
        onDraw();
    }

    inline const std::string& getString() const _GLIBCXX_NOEXCEPT
    { return m_labelString; }

protected:
    virtual void onUserEvent(const SDL_UserEvent* user) override;

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key);

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) override;

    virtual void initialize() override;

    virtual void onDraw();

    virtual void onDrawBackground() override;

    virtual void onTimerEvent(const SDL_UserEvent* user) override;

private:
    virtual void onAttachFocus();

    virtual void onDetachFocus();

    bool m_textCursor;
    t_timer m_textCursorTimer = NULL_TIMER_ID;
    EditLabelBasic m_labelBasic;
    std::shared_ptr<TimerAdder> m_textCursorTimerAdder;
};

class EditLabelBuilder : public BorderBuilder
{
public:

    EditLabelBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
    }

    EditLabelBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BorderBuilder(window, point, str)
    {
    }

    virtual ~EditLabelBuilder() = default;

    virtual Control::control_ptr build()
    {
        return new EditLabel(*this);
    }

    EditLabelBasic m_editBasic;

};

}

#endif //TETRIS_FIGURE_CLASS_TEDIT_H
