//
// Created by chaed on 19. 2. 14.
//

#ifndef TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
#define TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H

#include "SDLEasyGUI/Controller/EditLabel.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "SDLEasyGUI/Windows/DisplayInterface.h"

#include "../../Common/THeader.h"

SDL_TETRIS_BEGIN

class TEnterServerDisplay : public sdleasygui::DisplayInterface
{

public:

    TEnterServerDisplay() = default;
    virtual ~TEnterServerDisplay() = default;

    void registerEvent();
    void onPreInitialize() ;
    void onClickedEnterServer();
    void onClickedBack();

private:

    //EditLabel m_idLabel;
    //Button m_enterBtn;
    //Button m_backBtn;

    virtual void updateObserver(const game_interface::Packet& ) override final {}
};



SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
