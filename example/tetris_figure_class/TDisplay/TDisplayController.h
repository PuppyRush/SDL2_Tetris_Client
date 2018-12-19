//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
#define TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

#include <unordered_map>

#include "TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TDisplayController{

public:

    static std::shared_ptr<TDisplayController> getInstance();

private:

    std::unordered_map<TDisplayInterface*, std::shared_ptr<TDisplayInterface>> m_map;

    TDisplayController(){}

};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
