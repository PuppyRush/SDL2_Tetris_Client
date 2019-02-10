//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_RADIOBUTTON_H
#define CONTROLLER_RADIOBUTTON_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "ButtonBasic.h"

SDL_TETRIS_BEGIN

class RadioButton : public ButtonBasic{
public:


    inline const bool isSelected() const noexcept{
        ButtonBasic::isSelected();
    }
    inline void setSelected(bool clicked) noexcept{
        ButtonBasic::setSelected(clicked);
    }

    virtual void initialize() override;
    virtual void onDraw() override final;

    static std::shared_ptr<ButtonBasic> getInstance(const ControllBuilder& bld);

private:
    RadioButton(const ControllBuilder& bld);
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TRADIOBUTTON_H
