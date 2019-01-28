//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_BUTTON_H
#define CONTROLLER_BUTTON_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "ButtonBasic.h"

SDL_TETRIS_BEGIN

class Button : public ButtonBasic
{

public:

    static std::shared_ptr<ButtonBasic> getInstance(const ControllBuilder& bld);

private:
    Button(const ControllBuilder& bld);

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TBUTTON_H
