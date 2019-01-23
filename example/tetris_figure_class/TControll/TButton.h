//
// Created by chaed on 18. 12. 27.
//

#ifndef TETRIS_FIGURE_CLASS_TBUTTON_H
#define TETRIS_FIGURE_CLASS_TBUTTON_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TButtonBasic.h"

SDL_TETRIS_BEGIN

class TButton final : public TButtonBasic{

public:

    static std::shared_ptr<TButtonBasic> getInstance(const TControllBuilder& bld);

private:
    TButton(const TControllBuilder& bld);
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TBUTTON_H
