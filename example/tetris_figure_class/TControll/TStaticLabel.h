//
// Created by chaed on 18. 12. 26.
//

#ifndef TETRIS_FIGURE_CLASS_TSTATICLABEL_H
#define TETRIS_FIGURE_CLASS_TSTATICLABEL_H

#include "TButtonBasic.h"

SDL_TETRIS_BEGIN

class TStaticLabel final : public TButtonBasic {

public:

    static std::shared_ptr<TButtonBasic> getInstance(const TControllBuilder& bld);

private:
    TStaticLabel(const TControllBuilder& bld);

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSTATICLABEL_H
