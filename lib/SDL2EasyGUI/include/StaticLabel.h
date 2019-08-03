//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_STATICLABEL_H
#define CONTROLLER_STATICLABEL_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/src/Controller/Label/LabelBasic.h"

namespace seg {

typedef struct StaticLabelBasic : public ControlBasic
{
} StaticLabelBasic;

class StaticLabelBuilder;

class StaticLabel : public LabelBasic
{

public:
    virtual ~StaticLabel() = default;

    explicit StaticLabel(StaticLabelBuilder& bld);

protected:
    virtual void onDrawBackground() override;

    virtual void onDraw() override final;

    virtual void initialize() override final;
};

class StaticLabelBuilder : public ControlBuilder
{
public:

    StaticLabelBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : ControlBuilder(window, point, str)
    {
    }

    StaticLabelBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : ControlBuilder(window, point, str)
    {
    }

    virtual ~StaticLabelBuilder() = default;

    virtual Control::control_ptr build() final
    {
        return new StaticLabel(*this);
    }

    StaticLabelBasic m_borderBasic;

};

}

#endif //TETRIS_FIGURE_CLASS_TSTATICLABEL_H
