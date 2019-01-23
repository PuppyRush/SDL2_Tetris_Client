//
// Created by chaed on 18. 12. 27.
//

#ifndef TETRIS_FIGURE_CLASS_TBUTTONBASIC_H
#define TETRIS_FIGURE_CLASS_TBUTTONBASIC_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TControll.h"

SDL_TETRIS_BEGIN

class TButtonBasic : public TControll{
public:

    inline const bool isMultiselected() const noexcept{
        TControll::isMultiselected();
    }
    inline void setMultiselected(bool multiselected) noexcept{
        TControll::setMultiselected(multiselected);
    }

protected:
    TButtonBasic(const TControllBuilder& bld, const TControllKind kind);

private:

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TBUTTONBASIC_H
