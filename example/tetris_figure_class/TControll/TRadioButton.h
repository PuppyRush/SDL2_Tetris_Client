//
// Created by chaed on 18. 12. 27.
//

#ifndef TETRIS_FIGURE_CLASS_TRADIOBUTTON_H
#define TETRIS_FIGURE_CLASS_TRADIOBUTTON_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TButtonBasic.h"

SDL_TETRIS_BEGIN

class TRadioButton final : public TButtonBasic{
public:


    inline const bool isSelected() const noexcept{
        TButtonBasic::isSelected();
    }
    inline void setSelected(bool clicked) noexcept{
        TButtonBasic::setSelected(clicked);
    }

    static std::shared_ptr<TButtonBasic> getInstance(const TControllBuilder& bld);

private:
    TRadioButton(const TControllBuilder& bld);
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TRADIOBUTTON_H
