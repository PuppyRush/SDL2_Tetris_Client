//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
#define TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

#include "../TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TGameLocalDisplay : public TDisplayInterface{

public:
    enum class UIResource : t_type
    {
        Suspend,
        End
    };

    virtual bool clickedBack() override;
    static std::shared_ptr<TDisplayInterface> getInstance();

private:
    TGameLocalDisplay();

    virtual void _setDisplay() override;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
