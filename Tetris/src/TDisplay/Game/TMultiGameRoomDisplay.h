//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
#define TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H

#include "TGameDisplay.h"
#include "../../TObject/TGameRoom.h"
SDL_TETRIS_BEGIN

class TMultiGameRoomDisplay : public TGameDisplay
{
public:
    explicit TMultiGameRoomDisplay(const sdleasygui::t_id displayId);
    virtual ~TMultiGameRoomDisplay() = default;

    inline auto& getGameRoom() noexcept { return m_gameroom;}

protected:
    virtual void updateObserver(const game_interface::Packet& ) override;
    virtual void onTimerEvent(const SDL_UserEvent *user);
    virtual void onKeyboardEvent (const SDL_KeyboardEvent* key);
private:

    virtual void onClickedStart(const void* click) override final;
    virtual void onClickedSuspend(const void* click) override final;
    virtual void onDraw() override final;
    virtual void onInitialize() override final;
    virtual void onClose() override final;
    virtual void onCreate() override final;
    virtual void registerEvent() override final;
    virtual void onUserEvent(const SDL_UserEvent* event) override final;

    std::shared_ptr<TGameRoom> m_gameroom = TGameRoom::getInstance();
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TGAMEONLINEDISPLAY_H
