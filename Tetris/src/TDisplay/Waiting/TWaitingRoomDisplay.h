//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H

#include <list>

#include "SDL2EasyGUI/src/Controller/ListBox.h"
#include "TDisplay/TDisplayInterface.h"
#include "TWaitingRoomCard.h"
#include "../../TObject/TWaitingRoom.h"

SDL_TETRIS_BEGIN

typedef struct UserInfo : sdleasygui::ListItem
{
    std::string username;
    game_interface::t_time maketime;
    sdleasygui::t_unique  unique;

    UserInfo(const std::string& name, game_interface::t_time time,  sdleasygui::t_unique  unique)
        :username(name), unique(unique), maketime(time)
    {
    }

    virtual ~UserInfo() = default;

    virtual const std::string& getString()  const noexcept override
    {
        return username;
    }
}UserInfo;

typedef struct ChatInfo : sdleasygui::ListItem
{
    std::string username;
    std::string chat;
    game_interface::t_time maketime;

    ChatInfo(const std::string& name, const std::string& chat, game_interface::t_time time)
        :username(name), chat(chat), maketime(time)
    {
    }

    virtual ~ChatInfo() = default;

    virtual const std::string& getString()  const noexcept override
    {
        return chat;
    }
}ChatInfo;


class TWaitingRoomDisplay : public TDisplayInterface
{
public:
    virtual ~TWaitingRoomDisplay() = default;

    virtual void updateObserver(const game_interface::Packet& ) override;

    virtual void registerEvent() override;
    virtual void onInitialize() override;
    virtual void onDraw() override;

protected:
    virtual void postCreate(TDisplayInterface::display_ptr) override;

private:

    void onClickCreateGameRoom(const void *);
    void sendChat(const void *);
    void recvChat(const game_interface::Packet &packet);
    void createGameroom(const game_interface::Packet &packet);
    void recvGameRoomInfo(const game_interface::Packet &packet);

    virtual Json::Value toJson() const override {}
    virtual const std::string_view& getUniqueName() const override {}

    const sdleasygui::TPoint m_controllBeginPoint = sdleasygui::TPoint{ 50, 50 };

    const sdleasygui::t_size m_userBoxWidth = sdleasygui::WINDOW_WIDTH /5;
    const sdleasygui::t_size m_userBoxHeight = sdleasygui::WINDOW_HEIGHT - 350;
    const sdleasygui::TPoint m_userBoxBeginPoint = sdleasygui::TPoint{sdleasygui::WINDOW_WIDTH-m_userBoxWidth-20, 50};

    const sdleasygui::t_size m_chatBoxWidth = sdleasygui::WINDOW_WIDTH - 100 - m_userBoxWidth;
    const sdleasygui::t_size m_chatBoxHeight = sdleasygui::WINDOW_HEIGHT / 7;
    const sdleasygui::TPoint m_chatBoxBeginPoint = sdleasygui::TPoint{m_controllBeginPoint.x,
                                                                      sdleasygui::WINDOW_HEIGHT-m_chatBoxHeight-200};

    const sdleasygui::t_size m_btnWidth =  m_userBoxWidth;
    const sdleasygui::t_size m_btnHeight = 50;
    const sdleasygui::TPoint m_createBtnBeginPoint = sdleasygui::TPoint{m_userBoxBeginPoint.x, m_chatBoxBeginPoint.y+50};

    TWaitingRoom m_waitingRoom;
    std::vector<TWaitingRoomCard> m_gamerooms;
    std::unordered_map<sdleasygui::t_unique, std::function<void()>> m_roomClickedFn;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
