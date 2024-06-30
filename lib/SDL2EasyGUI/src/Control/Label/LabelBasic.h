//
// Created by chaed on 19. 3. 31.
//

#ifndef SDL2EASYGUI_LABELBASIC_H
#define SDL2EASYGUI_LABELBASIC_H

#include <string>

#include "../Border.h"

namespace seg {


class LabelBasicBuilder;

class LabelBasic : public Border
{

public:
    LabelBasic(LabelBasicBuilder& bld);

    virtual ~LabelBasic()
    {}

    bool isEmpty() noexcept
    {
        return getControlText().empty();
    }

protected:

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void initialize() override;

};

class LabelBasicBuilder : public BorderBuilder
{
public:

    LabelBasicBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
        : BorderBuilder(window, point, str)
    {
    }

    LabelBasicBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
        : BorderBuilder(window, point, str)
    {
    }

    virtual ~LabelBasicBuilder() = default;

    virtual Control::control_ptr build() = 0;

};

}

#endif //PROJECT_LABELBASIC_H
