//
// Created by chaed on 18. 12. 28.
//

#ifndef CONTROLLER_EDITLABEL_H
#define CONTROLLER_EDITLABEL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Controll.h"

SDL_TETRIS_BEGIN

class EditLabel : public Controll{

public:
    virtual void initialize() override;
    static std::shared_ptr<Controll> getInstance(const ControllBuilder& bld);

private:
    EditLabel(const ControllBuilder& bld);

    bool m_canWritable = true;
    bool m_canReadable = true;
    bool m_isOnlyNumber = false;
    bool m_isOnlyString = false;
    t_size m_maxlen = 20;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TEDIT_H
