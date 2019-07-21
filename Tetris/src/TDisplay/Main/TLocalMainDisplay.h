#ifndef TETRIS_TMAIN_TMAINLOCALDISPLAY_H
#define TETRIS_TMAIN_TMAINLOCALDISPLAY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TLocalMainDisplay final : public TMainDisplay
{
public:

    explicit TLocalMainDisplay(const sdleasygui::t_id displayId);

    virtual ~TLocalMainDisplay() = default;

private:

    [[deprecated("dont call this function in TLocalMainDisplay")]]
    virtual void onClickedEnterServer(const void* click)
    { assert(0); };

    virtual void onClickedStartLocalGame(const void* click) override final;

    virtual void onClickedOption(const void* click) override final;

    virtual void onClickedBack(const void* click) override
    {}

    virtual void registerEvent() override final;

    virtual void onInitialize() override final;

    virtual void onDraw() override final;

};

SDL_TETRIS_END

#endif