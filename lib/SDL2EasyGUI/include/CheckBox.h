//
// Created by chaed on 19. 4. 27.
//

#ifndef SDL2_TETIRS_CLIENT_CHECKBOX_H
#define SDL2_TETIRS_CLIENT_CHECKBOX_H

#include "SDL2EasyGUI/src/Controller/Button/ButtonBasic.h"

namespace sdleasygui {

enum class CheckBoxType
{
    xType,
    oType,
    vType,
};

class CheckBoxBuilder;

class CheckBox : public ButtonBasic
{
public:
    explicit CheckBox(CheckBoxBuilder& bld);

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    void setSelected(const bool chk)
    {
        Control::setSelected(chk);
        _drawCheck(chk);
    }

private:

    t_size m_lineThick{2};

    CheckBoxType m_type{CheckBoxType::vType};

    const SEG_Color m_lineColor{ColorCode::black};

    void _drawCheck(const bool chk);
};

class CheckBoxBuilder : public BorderBuilder
{
public:

    t_size m_lineThick{2};
    CheckBoxType m_type{CheckBoxType::vType};
    
    CheckBoxBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
        width(20);
        height(20);
        borderColor(ColorCode::black);
    }

    CheckBoxBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BorderBuilder(window, point, str)
    {
        width(20);
        height(20);
        borderColor(ColorCode::black);
    }

    virtual ~CheckBoxBuilder() = default;

    CheckBoxBuilder* checkBoxType(const CheckBoxType type)
    {
        m_type = type;
        return this;
    }

    CheckBoxBuilder* lineThick(const size_t thick)
    {
        m_lineThick = thick;
        return this;
    }

    virtual Control::control_ptr build() final
    {
        return new CheckBox(*this);
    }

private:

};

}

#endif //SDL2_TETIRS_CLIENT_CHECKBOX_H
