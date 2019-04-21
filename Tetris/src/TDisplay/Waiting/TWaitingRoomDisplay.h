//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H

#include <list>

#include "SDL2EasyGUI/src/Controller/Box/ListBox.h"
#include "TDisplay/TDisplayInterface.h"
#include "TWaitingRoomCard.h"
#include "../../TObject/TWaitingRoom.h"
#include "GameInterface/include/JsonPackage.h"

SDL_TETRIS_BEGIN

typedef struct UserInfo : sdleasygui::BoxItem
{
    std::string username;
    game_interface::t_time maketime;
    sdleasygui::t_unique  unique;

    UserInfo() = default;

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

typedef struct ChatInfo : sdleasygui::BoxItem, game_interface::JsonPackage
{
    std::string username;
    std::string chat;
    game_interface::t_time maketime;

    ChatInfo() = default;

    ChatInfo(const std::string& name, const std::string& chat, game_interface::t_time time)
        :username(name), chat(chat), maketime(time)
    {
    }

    virtual ~ChatInfo() = default;

    void appendUserNameFromChat()
    {
        std::string newchat;
        newchat.reserve(username.size() + chat.size() + 5);
        newchat += username;
        newchat += " : ";
        newchat += chat;

        chat = newchat;
    }

    virtual const std::string& getString()  const noexcept override
    {
        return chat;
    }

    virtual Json::Value toJson() const
    {
        Json::Value json;
        json["username"] = username;
        json["chat"] = chat;
        json["maketime"] = static_cast<Json::UInt64>(maketime);

        return json;
    }

    virtual void fromJson(const Json::Value &json) override
    {
        username = json["username"].asString();
        chat = json["chat"].asString();
        maketime = json["maketime"].asUInt64();
    }

    virtual const std::string_view &getUniqueName() const override
    {
        return game_interface::NAME_CHATINFO;
    }


}ChatInfo;


class TWaitingRoomDisplay : public TDisplayInterface
{
public:

    explicit TWaitingRoomDisplay(const sdleasygui::t_id displayId);
    virtual ~TWaitingRoomDisplay() = default;

    virtual void updateObserver(const game_interface::Packet& ) override;

    virtual void registerEvent() override;
    virtual void onInitialize() override;
    virtual void onDraw() override;

    auto& getWaitingRoom(){return m_waitingRoom;}

protected:
    virtual void postCreate(TDisplayInterface::display_ptr) override;

private:

    void onClickCreateGameRoom(const void *);
    void sendChat(const void *);
    void recvChat(const game_interface::Packet &packet);
    void createGameroom(const game_interface::Packet &packet);
    void recvWaitingRoomInitInfo(const game_interface::Packet &packet);

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
