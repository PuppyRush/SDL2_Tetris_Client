//
// Created by chaed on 19. 1. 22.
//

#ifndef CONTROLLER_BORDER_H
#define CONTROLLER_BORDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Controll.h"
#include "SDLEasyGUI/Windows/GraphicInterface.h"
#include "ControllBuilder.h"

enum class BorderBoundaryType : char
{
    angle,
    ellipse,
    round
};

enum class BorderBoundaryLineType : char
{
    straight,
    single_dashed,
    double_dashed,
};

typedef struct BorderBasic
{
    BorderBoundaryLineType lineType = BorderBoundaryLineType::straight;
    BorderBoundaryType type = BorderBoundaryType::angle;
    int angle = 0;
};



class BorderBuilder;
class Border : public Controll {

public:
    Border(const BorderBuilder& basic);

    virtual void onDraw() override;


private:

    BorderBasic m_borderBasic;
};

class BorderBuilder : public ControllBuilder
{
public:

    BorderBuilder(const GraphicInterface::window_ptr window, const TPoint& point, const std::string& str)
        :ControllBuilder(window,point,str)
    {
    }

    BorderBuilder(const GraphicInterface::window_ptr window, TPoint&& point, std::string&& str)
        :ControllBuilder(window,point,str)
    {
    }

    virtual std::shared_ptr<Controll> build() final
    {
        return make_shared<Border>(*this);
    }

    BorderBasic m_borderBasic;

};



#endif //TETRIS_FIGURE_CLASS_TBORDER_H
