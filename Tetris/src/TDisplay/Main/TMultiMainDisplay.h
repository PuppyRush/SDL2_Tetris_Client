//
// Created by chaed on 18. 11. 18.
//

#ifndef UICLASSEXAMPLE_MAINONLINEDISPLAY_H
#define UICLASSEXAMPLE_MAINONLINEDISPLAY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "TMainDisplay.h"
#include "../TOptionDisplay.h"
#include "TEnterServerDisplay.h"

SDL_TETRIS_BEGIN

class TMultiMainDisplay final : public TMainDisplay
{
public:

    TMultiMainDisplay();

    virtual ~TMultiMainDisplay() = default;

    virtual const seg::t_id getDisplayId() const noexcept override final
    {
        return seg::toUType(TETRIS::resource::MAIN_MULTI_DISPLAY);
    }

private:
    virtual void onClickedBack(const void* click) override final;

    virtual void onClickedOption(const void* click) override final;

    virtual void onClickedEnterServer(const void* click) override final;

    virtual void registerEvent() override final;

    virtual void onDraw() override final;

    virtual void onInitialize() override final;

    [[deprecated("dont call this function in TMultiMainDisplay")]]
    virtual void onClickedStartLocalGame(const void* click) override final
    {}

};

SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
