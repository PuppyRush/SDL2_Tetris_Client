//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "TGameDisplay.h"
#include "../../TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TSingleGameDisplay final : public TGameDisplay
{

public:

    explicit TSingleGameDisplay(const seg::t_id displayId);

    virtual ~TSingleGameDisplay() = default;

private:
    virtual void onClickedStart(const void* click) override final;

    virtual void onClickedSuspend(const void* click) override final;

    virtual void onDraw() override final;

    virtual void onInitialize() override final;

    virtual void onClose() override final;

    virtual void onCreate() override final;

    virtual void registerEvent() override final;

};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
