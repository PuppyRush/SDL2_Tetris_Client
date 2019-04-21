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

    explicit TMultiMainDisplay(const sdleasygui::t_id displayId);
    virtual ~TMultiMainDisplay() = default;


private:
    virtual void onClickedBack(const void* click) override final;
    virtual void onClickedOption(const void* click) override final;
    virtual void onClickedEnterServer(const void* click) override final;
    virtual void registerEvent() override final;
    virtual void onDraw() override final;
    virtual void onInitialize() override final;

    [[deprecated("dont call this function in TMultiMainDisplay")]]
    virtual void onClickedStartLocalGame(const void* click) override final {}

};

SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H
