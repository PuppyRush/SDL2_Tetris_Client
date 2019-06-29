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

    virtual const std::string& getString()
    {
        if (!caching) {
            setOriginString(m_str);
            caching = true;
        }
        return m_str;
    }


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

    virtual void initialize() override;

private:
    const size_t MENU_MAX = 5;


    t_size m_defaultHeight;
};

class ComoboBoxBuilder : public BorderBuilder
{
public:

    virtual ~ComoboBoxBuilder() = default;

    ComoboBoxBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
    }

    ComoboBoxBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
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
