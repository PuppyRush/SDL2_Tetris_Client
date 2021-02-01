//
// Created by chaed on 18. 12. 28.
//

#ifndef SDL2EASYGUI_EDITLABEL_H
#define SDL2EASYGUI_EDITLABEL_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/src/Control/Label/LabelBasic.h"
#include "SEG_Event.h"

namespace seg {


class EditLabelBuilder;

class EditLabel : public LabelBasic
{

public:
    using Base = LabelBasic;

    virtual ~EditLabel();

    explicit EditLabel(EditLabelBuilder& bld);

protected:
    
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override;

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) override;

    virtual void initialize() override;

    virtual void onDraw();

    virtual void onDrawBackground() override;

    virtual void onTimerEvent(const SDL_UserEvent* user) override;

private:
    virtual void onAttachFocus(const SDL_UserEvent* user) override;

    virtual void onDetachFocus(const SDL_UserEvent* user) override;

    int* m_textWidth = nullptr;
    int* m_textHeight = nullptr;
    bool m_drawTextCursor = false;
    std::shared_ptr<seg::event::SEG_Timer> m_cursorTimer;
};

class EditLabelBuilder : public LabelBasicBuilder
{
public:

    EditLabelBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : LabelBasicBuilder(window, point, str)
    {
    }

    EditLabelBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : LabelBasicBuilder(window, point, str)
    {
    }

    virtual ~EditLabelBuilder() = default;

    virtual Control::control_ptr build()
    {
        return new EditLabel(*this);
    }

};

}

#endif //SDL2EASYGUI_TEDIT_H
