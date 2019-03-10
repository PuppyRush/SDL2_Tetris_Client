//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_FIGURE_CLASS_CREATEWINDOW_H
#define TETRIS_FIGURE_CLASS_CREATEWINDOW_H

#include <string>

#include "SDLEasyGUI/Windows/DisplayInterface.h"

class CreateGameroomWindow : public sdleasygui::DisplayInterface
{
public:

    std::string m_roomname;
    virtual ~CreateGameroomWindow(){}

protected:
    virtual void updateObserver(const game_interface::Packet& ) {}

    virtual void registerEvent() override;
    virtual void onInitialize() override;
    virtual void onDraw() override;
    virtual void onClose() override;
    virtual void onOK() override;
    virtual void onCancel() override;

private:

};

#endif //TETRIS_FIGURE_CLASS_CREATEWINDOW_H
