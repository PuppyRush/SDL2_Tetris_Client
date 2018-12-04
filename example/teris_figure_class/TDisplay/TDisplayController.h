//
// Created by chaed on 18. 12. 4.
//

#ifndef UICLASSEXAMPLE_TDISPLAYCONTROLLER_H
#define UICLASSEXAMPLE_TDISPLAYCONTROLLER_H

#include "../Common/TType.h"
#include "MainOnlineDisplay.h"
#include "MainLocalDisplay.h"

SDL_TETRIS_BEGIN

class TDisplayController
{
public:




private:

    MainOnlineDisplay m_onlineDisplay;
    MainLocalDisplay m_localDisplay;
};

SDL_TETRIS_END

#endif //UICLASSEXAMPLE_TDISPLAYCONTROLLER_H

