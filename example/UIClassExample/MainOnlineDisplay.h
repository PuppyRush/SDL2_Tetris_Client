//
// Created by chaed on 18. 11. 18.
//

#ifndef UICLASSEXAMPLE_MAINONLINEDISPLAY_H
#define UICLASSEXAMPLE_MAINONLINEDISPLAY_H

#include "MainDisplay.h"

SDL_TETRIS_BEGIN

class MainOnlineDisplay : public MainDisplay
{
public:
    virtual bool clickedEnterServer() override {}
    virtual bool clickedStartLocalGame() override {}
    virtual bool clickedBack() override {}

private:
    MainOnlineDisplay(const std::vector<Menu> menus)
            :MainDisplay(menus) {}

};



SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
