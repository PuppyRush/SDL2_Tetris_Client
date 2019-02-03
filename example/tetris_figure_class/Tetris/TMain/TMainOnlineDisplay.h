//
// Created by chaed on 18. 11. 18.
//

#ifndef UICLASSEXAMPLE_MAINONLINEDISPLAY_H
#define UICLASSEXAMPLE_MAINONLINEDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainOnlineDisplay final : public TMainDisplay
{
public:
    enum class UIResource : t_type
    {
        OnlineStart,
        LocalStart,
        Option,
        End
    };

    virtual bool clickedEnterServer() final {}
    virtual bool clickedStartLocalGame() final {}
    virtual bool clickedBack(const TDisplay disply) final {}
    static std::shared_ptr<TMainDisplay> getInstance();

private:
    TMainOnlineDisplay(){}

    virtual void _preInitialize() final;
    virtual void _event(const SDL_Event* event) final;
    virtual void _timer() final;
    virtual void _draw() final;

};



SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
