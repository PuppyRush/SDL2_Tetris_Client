//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_STATICLABEL_H
#define CONTROLLER_STATICLABEL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "ButtonBasic.h"

SDL_TETRIS_BEGIN

class StaticLabel : public ButtonBasic {

public:

    virtual void initialize() override;
    static std::shared_ptr<ButtonBasic> getInstance(const ControllBuilder& bld);

private:
    StaticLabel(const ControllBuilder& bld);

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSTATICLABEL_H
