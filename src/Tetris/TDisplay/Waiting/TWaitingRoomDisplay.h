//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H

#include <list>

#include "TWaitingRoomCard.h"
#include "SDLEasyGUI/Windows/DisplayInterface.h"

SDL_TETRIS_BEGIN

class TWaitingRoomDisplay : public sdleasygui::DisplayInterface
{

public:
    virtual void updateObserver(const game_interface::Packet& ) override;
    void recvInitRoomInfo(const game_interface::Packet &);
    void recvInitPlayerInfo(const game_interface::Packet &);

    virtual void registerEvent() override;
    virtual void onPreInitialize() override;
    virtual void onDraw() override;

private:

    const sdleasygui::t_size m_userBoxBeginWidth = sdleasygui::WINDOW_WIDTH /5;
    const sdleasygui::t_size m_userBoxBeginHeight = sdleasygui::WINDOW_HEIGHT - 350;
    const sdleasygui::TPoint m_userBoxBeginPoint = sdleasygui::TPoint{sdleasygui::WINDOW_WIDTH-m_userBoxBeginWidth-20, 50};

    const sdleasygui::t_size m_chatBoxBeginWidth = sdleasygui::WINDOW_WIDTH - 100 - m_userBoxBeginWidth;
    const sdleasygui::t_size m_chatBoxBeginHeight = sdleasygui::WINDOW_HEIGHT / 7;
    const sdleasygui::TPoint m_chatBoxBeginPoint = sdleasygui::TPoint{50, sdleasygui::WINDOW_HEIGHT-m_chatBoxBeginHeight-200};

    const sdleasygui::t_size m_createBtnBeginWidth =  m_userBoxBeginWidth;
    const sdleasygui::t_size m_createBtnBeginHeight = 50;
    const sdleasygui::TPoint m_createBtnBeginPoint = sdleasygui::TPoint{m_userBoxBeginPoint.x, m_chatBoxBeginPoint.y+50};

    std::vector<TWaitingRoomCard> m_gamerooms;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
