//
// Created by chaed on 19. 2. 15.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H

#include "SDL2EasyGUI/src/Control/Control.h"
#include "SDL2EasyGUI/src/Control/Border.h"
#include "SDL2EasyGUI/include/StaticLabel.h"
#include "../Game/TMultiGameRoomDisplay.h"

SDL_TETRIS_BEGIN

typedef struct WaitingroomCardBasic
{
    std::string name;
    int partyNumber;
    int roomnumber;
    bool state;
} WaitingroomCardBasic;

class TWaitingRoomCardBuilder;

class TWaitingRoomCard final : public seg::Border
{
public:

    TWaitingRoomCard(TWaitingRoomCardBuilder& bld);

    virtual ~TWaitingRoomCard() = default;

    virtual void onDraw() override final;

    virtual void initialize() override final;

private:
    WaitingroomCardBasic m_cardBasic;
    std::unique_ptr<TMultiGameRoomDisplay> m_gameroom;
    std::unique_ptr<seg::StaticLabel> m_name;
    std::unique_ptr<seg::StaticLabel> m_partyNumber;
    std::unique_ptr<seg::StaticLabel> m_state;
};

class TWaitingRoomCardBuilder : public seg::BorderBuilder
{
public:

    TWaitingRoomCardBuilder(const seg::GraphicInterface::window_type window, const seg::SEG_Point& point,
                            const std::string& str)
            : BorderBuilder(window, point, str)
    {
    }

    TWaitingRoomCardBuilder(const seg::GraphicInterface::window_type window, seg::SEG_Point&& point,
                            std::string&& str)
            : BorderBuilder(window, point, str)
    {
    }

    inline TWaitingRoomCardBuilder* roomname(const std::string roomname) noexcept
    {
        m_cardBasic.name = roomname;
        return this;
    }

    inline TWaitingRoomCardBuilder* roomnumber(const int number) noexcept
    {
        m_cardBasic.roomnumber = number;
        return this;
    }

    inline TWaitingRoomCardBuilder* partyNumber(const int number) noexcept
    {
        m_cardBasic.partyNumber = number;
        return this;
    }

    inline TWaitingRoomCardBuilder* state(const bool state) noexcept
    {
        m_cardBasic.state = state;
        return this;
    }

    virtual seg::Control* build() final
    {
        return new TWaitingRoomCard(*this);
    }

    WaitingroomCardBasic m_cardBasic;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H
