//
// Created by chaed on 19. 2. 15.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H

#include "SDLEasyGUI/Controller/Border.h"
#include "SDLEasyGUI/Controller/StaticLabel.h"
#include "../Game/TMultiGameRoomDisplay.h"

SDL_TETRIS_BEGIN

class TWaitingRoomCardBuilder;
class TWaitingRoomCard final : public sdleasygui::Border
{
public:

    TWaitingRoomCard(TWaitingRoomCardBuilder& bld);
    virtual void onDraw() override final;
    virtual void initialize() override final;

private:

    std::unique_ptr<TMultiGameRoomDisplay> m_gameroom;
    std::unique_ptr<sdleasygui::StaticLabel> m_name;
    std::unique_ptr<sdleasygui::StaticLabel> m_partyNumber;
    std::unique_ptr<sdleasygui::StaticLabel> m_state;
};


class TWaitingRoomCardBuilder : public sdleasygui::BorderBuilder
{
public:

    TWaitingRoomCardBuilder(const sdleasygui::GraphicInterface::window_ptr window, const sdleasygui::Point& point, const std::string& str)
        :BorderBuilder(window,point,str)
    {
    }

    TWaitingRoomCardBuilder(const sdleasygui::GraphicInterface::window_ptr window, sdleasygui::Point&& point, std::string&& str)
        :BorderBuilder(window,point,str)
    {
    }

    virtual std::shared_ptr<sdleasygui::Controll> build() final
    {
        return std::make_shared<TWaitingRoomCard>(*this );
    }

};



SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H
