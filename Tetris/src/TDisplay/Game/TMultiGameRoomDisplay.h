//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_CLIENT_TGAMEONLINEDISPLAY_H
#define TETRIS_CLIENT_TGAMEONLINEDISPLAY_H

#include "TGameDisplay.h"

SDL_TETRIS_BEGIN

class TMultiGameRoomDisplay : public TGameDisplay
{
public:

    TMultiGameRoomDisplay();

    virtual ~TMultiGameRoomDisplay() = default;

    virtual const seg::t_id getDisplayId() const noexcept override final
    {
        return seg::toUType(resource::MULTIGAME_DISPLAY);
    }


    inline auto& getGameRoom() noexcept
    { return m_gameroom; }

protected:
    virtual void updateObserver(const game_interface::packet::Packet&) override;

    virtual void onTimerEvent(const SDL_UserEvent* user);

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key);

private:

    virtual void onClickedStart(const void* click) override final;

    virtual void onClickedSuspend(const void* click) override final;

    virtual void onDraw() override final;

    virtual void onInitialize() override final;

    virtual void onClose() override final;

    virtual void onCreate() override final;

    virtual void registerEvent() override final;

    virtual void onUserEvent(const SDL_UserEvent* event) override final;

};

SDL_TETRIS_END

#endif //TETRIS_CLIENT_TGAMEONLINEDISPLAY_H
