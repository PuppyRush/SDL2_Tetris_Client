//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
#define TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

#include "../TController.h"

SDL_TETRIS_BEGIN

class TGameController : public TControllerInterface{

public:

    static auto getInstance();

private:
    TGameController(){}

    virtual void _setDisplay() override;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
