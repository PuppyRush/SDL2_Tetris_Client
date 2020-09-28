//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_LIST_H
#define TETRIS_FIGURE_CLASS_LIST_H

#include <vector>

#include "SDL2EasyGUI/src/Controller/Box/BoxBasic.h"

namespace seg {

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

class ListBoxBuilder : public BoxBasicBuilder
{
public:

    virtual ~ListBoxBuilder() = default;

    ListBoxBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    ListBoxBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    virtual Control::control_ptr build() final
    {
        return new ListBox(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_LIST_H
