//
// Created by chaed on 18. 11. 18.
//

#ifndef UICLASSEXAMPLE_MAINONLINEDISPLAY_H
#define UICLASSEXAMPLE_MAINONLINEDISPLAY_H

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainOnlineDisplay : public TMainDisplay
{
public:
    virtual bool clickedEnterServer() override {}
    virtual bool clickedStartLocalGame() override {}
    virtual bool clickedBack() override {}

private:
    TMainOnlineDisplay(const std::vector<Menu> menus)
            :TMainDisplay(menus) {}

};



SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
