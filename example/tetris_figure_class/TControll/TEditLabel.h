//
// Created by chaed on 18. 12. 28.
//

#ifndef TETRIS_FIGURE_CLASS_TEDIT_H
#define TETRIS_FIGURE_CLASS_TEDIT_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TControll.h"

SDL_TETRIS_BEGIN

class TEditLabel final : public TControll{

public:
    static std::shared_ptr<TControll> getInstance(const TControllBuilder& bld);

private:
    TEditLabel(const TControllBuilder& bld);

    bool m_canWritable = true;
    bool m_canReadable = true;
    bool m_isOnlyNumber = false;
    bool m_isOnlyString = false;
    t_size m_maxlen = 20;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TEDIT_H
