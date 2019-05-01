//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_LIST_H
#define TETRIS_FIGURE_CLASS_LIST_H

#include <vector>

#include "SDL2EasyGUI/src/Controller/Box/BoxBasic.h"

namespace sdleasygui {

enum class ListBoxTypes : t_type
{
    multiclicked,
    editable,
    clickable,
};

enum class ListBoxScrollType : t_type
{
    vertical,
    horizen,
    both
};

class ListBoxBuilder;

class ListBox : public BoxBasic
{
public:

    explicit ListBox(ListBoxBuilder& bld);

    virtual ~ListBox() = default;

    virtual void onDraw() override;

    virtual void initialize() override
    {
        BoxBasic::initialize();
    }

};

class ListBoxBuilder : public BorderBuilder
{
public:

    virtual ~ListBoxBuilder() = default;

    ListBoxBuilder(const GraphicInterface::window_type window, const TPoint& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
    }

    ListBoxBuilder(const GraphicInterface::window_type window, TPoint&& point, std::string&& str)
            : BorderBuilder(window, point, str)
    {
    }

    virtual Controller::controll_ptr build() final
    {
        return new ListBox(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_LIST_H
