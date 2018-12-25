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
    virtual bool clickedBack(const TDisplay disply) override {}
    static std::shared_ptr<TMainDisplay> getInstance();

private:
    TMainOnlineDisplay(){}

    virtual void _preInitialize() override;
    virtual void _event(const SDL_Event* event) override;
    virtual void _timer() override;
    virtual void _draw() override;

};



SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
