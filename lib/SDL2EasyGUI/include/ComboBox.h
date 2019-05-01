//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_FIGURE_CLASS_COMBOBOX_H
#define TETRIS_FIGURE_CLASS_COMBOBOX_H

#include "SDL2EasyGUI/src/Controller/Box/BoxBasic.h"

namespace sdleasygui {

typedef struct ComboBoxItem : sdleasygui::BoxItem
{

public:

    ComboBoxItem() = default;

    ComboBoxItem(const std::string& name)
            : m_str(name)
    {
    }

    virtual ~ComboBoxItem() = default;

    virtual void setOriginString(std::string& _origin) override
    {
    }

private:
    std::string m_str;

} ComboBoxItem;

class ComoboBoxBuilder;

class ComboBox : public BoxBasic
{

public:
    ComboBox(ComoboBoxBuilder& bld);

    virtual ~ComboBox() = default;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void initialize() override
    {
        BoxBasic::initialize();
    }

private:
    bool m_folded = true;
};

class ComoboBoxBuilder : public BorderBuilder
{
public:

    virtual ~ComoboBoxBuilder() = default;

    ComoboBoxBuilder(const GraphicInterface::window_type window, const TPoint& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
    }

    ComoboBoxBuilder(const GraphicInterface::window_type window, TPoint&& point, std::string&& str)
            : BorderBuilder(window, point, str)
    {
    }

    virtual Controller::controll_ptr build() final
    {
        return new ComboBox(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_COMBOBOX_H
