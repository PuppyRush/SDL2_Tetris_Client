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
class TWaitingRoomCard final : public Border
{
public:

    TWaitingRoomCard(TWaitingRoomCardBuilder& bld);
    virtual void onDraw() override final;
    virtual void initialize() override final;

private:

    std::unique_ptr<TMultiGameRoomDisplay> m_gameroom;
    std::unique_ptr<StaticLabel> m_name;
    std::unique_ptr<StaticLabel> m_partyNumber;
    std::unique_ptr<StaticLabel> m_state;
};


class TWaitingRoomCardBuilder : public BorderBuilder
{
public:

    TWaitingRoomCardBuilder(const GraphicInterface::window_ptr window, const Point& point, const std::string& str)
        :BorderBuilder(window,point,str)
    {
    }

    TWaitingRoomCardBuilder(const GraphicInterface::window_ptr window, Point&& point, std::string&& str)
        :BorderBuilder(window,point,str)
    {
    }

    virtual std::shared_ptr<Controll> build() final
    {
        return std::make_shared<TWaitingRoomCard>(*this );
    }

};



SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H
