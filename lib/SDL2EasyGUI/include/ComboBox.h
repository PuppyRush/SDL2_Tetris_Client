//
// Created by chaed on 19. 3. 8.
//

#ifndef SDL2EASYGUI_COMBOBOX_H
#define SDL2EASYGUI_COMBOBOX_H

#include "SDL2EasyGUI/src/Control/Box/BoxBasic.h"

namespace seg {

class ComoboBoxBuilder;

class ComboBox : public BoxBasic
{
public:
    using Base = BoxBasic;
    
    ComboBox(ComoboBoxBuilder& bld);

    virtual ~ComboBox() = default;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void initialize() override;

    virtual void onDetachFocus(const SDL_UserEvent* user) override;

protected:

    virtual void foldBox() override;

    virtual void unfoldBox() override;

private:

    t_size m_defaultHeight;
};

class ComoboBoxBuilder : public BoxBasicBuilder
{
public:

    virtual ~ComoboBoxBuilder() = default;

    ComoboBoxBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    ComoboBoxBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    virtual Control::control_ptr build() final
    {
        return new ComboBox(*this);
    }

};

}

#endif //SDL2EASYGUI_COMBOBOX_H
