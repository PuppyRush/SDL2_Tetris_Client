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
    enum class UIResource : t_type
    {
        OnlineStart,
        LocalStart,
        Option,
        End
    };

    virtual bool clickedEnterServer() override {}
    virtual bool clickedStartLocalGame() override {}
    virtual bool clickedBack() override {}
    virtual void _setDisplay() override{}
    static std::shared_ptr<TMainDisplay> getInstance();

private:
    TMainOnlineDisplay(){}

};



SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
