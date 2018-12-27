//
// Created by chaed on 18. 12. 27.
//

#ifndef TETRIS_FIGURE_CLASS_TRADIOBUTTON_H
#define TETRIS_FIGURE_CLASS_TRADIOBUTTON_H

#include "TButtonBasic.h"

SDL_TETRIS_BEGIN

class TRadioButton final : public TButtonBasic{
public:


    inline const bool isClicked() const noexcept{
        TButtonBasic::isClicked();
    }
    inline void setClicked(bool clicked) noexcept{
        TButtonBasic::setClicked(clicked);
    }

    static std::shared_ptr<TButtonBasic> getInstance(const TControllBuilder& bld);

private:
    TRadioButton(const TControllBuilder& bld);
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TRADIOBUTTON_H
