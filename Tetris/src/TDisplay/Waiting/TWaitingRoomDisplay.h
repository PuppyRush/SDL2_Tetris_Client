//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H

#include <array>
#include <list>

#include "SDL2EasyGUI/include/ListBox.h"
#include "TDisplayInterface.h"
#include "TWaitingRoomCard.h"
#include "../../TObject/TWaitingRoom.h"
#include "GameInterface/include/JsonPackage.h"

SDL_TETRIS_BEGIN

typedef struct RoomInfo : sdleasygui::BoxItem
{
public:

    const std::string& getRoomname() const
    {
        return roomname;
    }

    void setRoomname(const std::string& roomname)
    {
        caching = false;
        RoomInfo::roomname = roomname;
    }

    game_interface::t_time getMaketime() const
    {
        return maketime;
    }

    void setMaketime(game_interface::t_time maketime)
    {
        caching = false;
        RoomInfo::maketime = maketime;
    }

    sdleasygui::t_unique getUnique() const
    {
        return unique;
    }

    void setUnique(sdleasygui::t_unique unique)
    {
        caching = false;
        RoomInfo::unique = unique;
    }

    size_t getUserCount() const
    {
        return userCount;
    }

    void setUserCount(size_t userCount)
    {
        caching = false;
        RoomInfo::userCount = userCount;
    }

    size_t getFullCount() const
    {
        return fullCount;
    }

    void setFullCount(size_t fullCount)
    {
        caching = false;
        RoomInfo::fullCount = fullCount;
    }

    size_t getRoomnumber() const
    {
        return roomnumber;
    }

    void setRoomnumber(size_t roomnumber)
    {
        caching = false;
        RoomInfo::roomnumber = roomnumber;
    }

    RoomInfo() = default;

    RoomInfo(size_t _roomnumber, const std::string& name, game_interface::t_time time, sdleasygui::t_unique unique,
             size_t _userCount, size_t _fullCount)
            : roomname(name), unique(unique), maketime(time), userCount(_userCount), fullCount(_fullCount),
              roomnumber(_roomnumber)
    {
    }

    virtual ~RoomInfo() = default;

    virtual void setOriginString(std::string& _origin) override
    {
        _origin.resize(roomname.size() + 10);
        _origin.clear();
        _origin += std::to_string(roomnumber) + " / " + roomname + " / (" + std::to_string(userCount) +
                   "/" + std::to_string(fullCount) + ")";
    }

private:

    std::string roomname;
    game_interface::t_time maketime;
    sdleasygui::t_unique unique;
    size_t userCount;
    size_t fullCount;
    size_t roomnumber;

} RoomInfo;

typedef struct UserInfo : sdleasygui::BoxItem
{

    UserInfo() = default;

    UserInfo(const std::string& name, game_interface::t_time time, sdleasygui::t_unique unique)
            : username(name), unique(unique), maketime(time)
    {
    }

    virtual ~UserInfo() = default;

    virtual void setOriginString(std::string& _origin) override
    {
        _origin.resize(username.size());
        _origin.clear();
        _origin += username;
    }

    const std::string& getUsername() const
    {
        return username;
    }

    void setUsername(const std::string& username)
    {
        caching = false;
        UserInfo::username = username;
    }

    game_interface::t_time getMaketime() const
    {
        return maketime;
    }

    void setMaketime(game_interface::t_time maketime)
    {
        caching = false;
        UserInfo::maketime = maketime;
    }

    sdleasygui::t_unique getUnique() const
    {
        return unique;
    }

    void setUnique(sdleasygui::t_unique unique)
    {
        caching = false;
        UserInfo::unique = unique;
    }

private:
    std::string username;
    game_interface::t_time maketime;
    sdleasygui::t_unique unique;

} UserInfo;

typedef struct ChatInfo : sdleasygui::BoxItem, game_interface::JsonPackage
{

public:

    ChatInfo() = default;

    ChatInfo(const std::string& name, const std::string& chat, game_interface::t_time time)
            : username(name), chat(chat), maketime(time)
    {
    }

    virtual ~ChatInfo() = default;

    virtual void setOriginString(std::string& _origin) override
    {
        std::string newchat;
        newchat.reserve(username.size() + chat.size() + 5);
        newchat += username;
        newchat += " : ";
        newchat += chat;

        _origin.resize(newchat.size());
        _origin.clear();
        _origin += newchat;
    }

    virtual Json::Value toJson() const
    {
        Json::Value json;
        json["username"] = username;
        json["contents"] = chat;
        json["maketime"] = static_cast<Json::UInt64>(maketime);

        return json;
    }

    virtual void fromJson(const Json::Value& json) override
    {
        username = json["username"].asString();
        chat = json["contents"].asString();
        maketime = json["maketime"].asUInt64();
    }

    virtual const std::string_view& getUniqueName() const override
    {
        return game_interface::NAME_CHATINFO;
    }

    const std::string& getUsername() const
    {
        return username;
    }

    void setUsername(const std::string& username)
    {
        caching = false;
        ChatInfo::username = username;
    }

    const std::string& getChat() const
    {
        return chat;
    }

    void setChat(const std::string& chat)
    {
        caching = false;
        ChatInfo::chat = chat;
    }

    game_interface::t_time getMaketime() const
    {
        return maketime;
    }

    void setMaketime(game_interface::t_time maketime)
    {
        caching = false;
        ChatInfo::maketime = maketime;
    }

private:
    game_interface::t_time maketime;
    std::string username;
    std::string chat;

} ChatInfo;

class TWaitingRoomDisplay : public TDisplayInterface
{
public:

    explicit TWaitingRoomDisplay(const sdleasygui::t_id displayId);

    virtual ~TWaitingRoomDisplay() = default;

    virtual void updateObserver(const game_interface::packet::Packet&) override;

    virtual void registerEvent() override;

    virtual void onInitialize() override;

    virtual void onDraw() override;

    auto& getWaitingRoom()
    { return m_waitingRoom; }

protected:
    virtual void postCreate(TDisplayInterface::display_ptr) override;

private:

    void onClickCreateGameRoom(const void*);

    void sendChat(const void*);

    void recvChat(const game_interface::packet::Packet& packet);

    void createGameroom(const game_interface::packet::Packet& packet);

    void recvWaitingRoomInitInfo(const game_interface::packet::Packet& packet);

    const sdleasygui::SEG_Point m_controllBeginPoint = sdleasygui::SEG_Point{50, 50};

    const sdleasygui::t_size m_userBoxWidth = sdleasygui::WINDOW_WIDTH / 5;
    const sdleasygui::t_size m_userBoxHeight = sdleasygui::WINDOW_HEIGHT - 350;
    const sdleasygui::SEG_Point m_userBoxBeginPoint = sdleasygui::SEG_Point{sdleasygui::WINDOW_WIDTH - m_userBoxWidth - 20,
                                                                      50};

    const sdleasygui::t_size m_chatBoxWidth = sdleasygui::WINDOW_WIDTH - 100 - m_userBoxWidth;
    const sdleasygui::t_size m_chatBoxHeight = sdleasygui::WINDOW_HEIGHT / 7;
    const sdleasygui::SEG_Point m_chatBoxBeginPoint = sdleasygui::SEG_Point{m_controllBeginPoint.x,
                                                                      sdleasygui::WINDOW_HEIGHT - m_chatBoxHeight -
                                                                      300};

    const sdleasygui::t_size m_gameroomBoxWidth = m_chatBoxWidth;
    const sdleasygui::t_size m_gameroomBoxHeight = m_userBoxHeight - 300;
    const sdleasygui::SEG_Point m_gameroomBoxBeginPoint = m_controllBeginPoint;

    const sdleasygui::t_size m_btnWidth = m_userBoxWidth;
    const sdleasygui::t_size m_btnHeight = 50;
    const sdleasygui::SEG_Point m_createBtnBeginPoint = sdleasygui::SEG_Point{m_userBoxBeginPoint.x,
                                                                        m_chatBoxBeginPoint.y + 50};

    TWaitingRoom m_waitingRoom;

    std::vector<TWaitingRoomCard> m_gamerooms;
    std::unordered_map<sdleasygui::t_unique, std::function<void()>> m_roomClickedFn;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
