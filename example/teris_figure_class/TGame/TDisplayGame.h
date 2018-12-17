//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
#define TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

#include "../TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TDisplayController : public TDisplayInterface{

public:

private:
    TDisplayController();

    virtual void _setDisplay() override;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
