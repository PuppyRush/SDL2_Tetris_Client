//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_CLIENT_TWAITINGROOMDISPLAY_H
#define TETRIS_CLIENT_TWAITINGROOMDISPLAY_H

#include <array>
#include <list>

#include "SDL2EasyGUI/include/ListBox.h"
#include "SDL2EasyGUI/include/SEG_Constant.h"
#include "TDisplayInterface.h"
#include "TWaitingRoomCard.h"
#include "../../TObject/TWaitingRoom.h"
#include "GameInterface/include/JsonPackage.h"

SDL_TETRIS_BEGIN

typedef struct RoomInfo
{
public:

    RoomInfo() = default;

    RoomInfo(size_t _roomnumber, const std::string& name, game_interface::t_time time, seg::t_unique unique,
        size_t _userCount, size_t _fullCount)
        : roomname(name), unique(unique), maketime(time), userCount(_userCount), fullCount(_fullCount),
        roomnumber(_roomnumber)
    {
    }

    const std::string& getRoomname() const
    {
        return roomname;
    }

    void setRoomname(const std::string& roomname)
    {
        //caching = false;
        RoomInfo::roomname = roomname;
    }

    game_interface::t_time getMaketime() const
    {
        return maketime;
    }

    void setMaketime(game_interface::t_time maketime)
    {
        //caching = false;
        RoomInfo::maketime = maketime;
    }

    seg::t_unique getUnique() const
    {
        return unique;
    }

    void setUnique(seg::t_unique unique)
    {
        //caching = false;
        RoomInfo::unique = unique;
    }

    size_t getUserCount() const
    {
        return userCount;
    }

    void setUserCount(size_t userCount)
    {
        //caching = false;
        RoomInfo::userCount = userCount;
    }

    size_t getFullCount() const
    {
        return fullCount;
    }

    void setFullCount(size_t fullCount)
    {
        //caching = false;
        RoomInfo::fullCount = fullCount;
    }

    size_t getRoomnumber() const
    {
        return roomnumber;
    }

    void setRoomnumber(size_t roomnumber)
    {
        //caching = false;
        RoomInfo::roomnumber = roomnumber;
    }

    ~RoomInfo() = default;

    //virtual void setOriginString(std::string& _origin) override
    //{
    //    _origin.resize(roomname.size() + 10);
    //    _origin.clear();
    //    _origin += std::to_string(roomnumber) + " / " + roomname + " / (" + std::to_string(userCount) +
    //               "/" + std::to_string(fullCount) + ")";
    //}

private:

    std::string roomname;
    game_interface::t_time maketime;
    seg::t_unique unique;
    size_t userCount;
    size_t fullCount;
    size_t roomnumber;

} RoomInfo;

typedef struct UserInfo
{

    UserInfo() = default;

    UserInfo(const std::string& name, game_interface::t_time time, seg::t_unique unique)
            : username(name), unique(unique), maketime(time)
    {
    }

    virtual ~UserInfo() = default;

    //virtual void setOriginString(std::string& _origin) override
    //{
    //    _origin.resize(username.size());
    //    _origin.clear();
    //    _origin += username;
    //}

    const std::string& getUsername() const
    {
        return username;
    }

    void setUsername(const std::string& username)
    {
        //caching = false;
        UserInfo::username = username;
    }

    game_interface::t_time getMaketime() const
    {
        return maketime;
    }

    void setMaketime(game_interface::t_time maketime)
    {
        //caching = false;
        UserInfo::maketime = maketime;
    }

    seg::t_unique getUnique() const
    {
        return unique;
    }

    void setUnique(seg::t_unique unique)
    {
        //caching = false;
        UserInfo::unique = unique;
    }

private:
    std::string username;
    game_interface::t_time maketime;
    seg::t_unique unique;

} UserInfo;

typedef struct ChatInfo : game_interface::JsonPackage
{

public:

    ChatInfo() = default;

    ChatInfo(const std::string& name, const std::string& chat, game_interface::t_time time)
            : username(name), chat(chat), maketime(time)
    {
    }

    virtual ~ChatInfo() = default;

    //virtual void setOriginString(std::string& _origin) override
    //{
    //    std::string newchat;
    //    newchat.reserve(username.size() + chat.size() + 5);
    //    newchat += username;
    //    newchat += " : ";
    //    newchat += chat;

    //    _origin.resize(newchat.size());
    //    _origin.clear();
    //    _origin += newchat;
    //}

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
        //caching = false;
        ChatInfo::username = username;
    }

    const std::string& getChat() const
    {
        return chat;
    }

    void setChat(const std::string& chat)
    {
        //caching = false;
        ChatInfo::chat = chat;
    }

    game_interface::t_time getMaketime() const
    {
        return maketime;
    }

    void setMaketime(game_interface::t_time maketime)
    {
        //caching = false;
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

    explicit TWaitingRoomDisplay();

    virtual ~TWaitingRoomDisplay() = default;

    virtual const seg::t_id getDisplayId() const noexcept override final
    {
        return seg::toUType(resource::WAITINGROOM_DISPLAY);
    }

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

    void onClickExit(const void*);

    void sendChat(const void*);

    void recvChat(const game_interface::packet::Packet& packet);

    void createGameroom(const game_interface::packet::Packet& packet);

    void recvWaitingRoomInitInfo(const game_interface::packet::Packet& packet);

    const seg::SEG_Point m_controllBeginPoint = seg::SEG_Point{50, 50};

    const seg::t_size m_userBoxWidth = seg::WINDOW_WIDTH / 5;
    const seg::t_size m_userBoxHeight = seg::WINDOW_HEIGHT - 350;
    const seg::SEG_Point m_userBoxBeginPoint = seg::SEG_Point{seg::WINDOW_WIDTH - m_userBoxWidth - 20,
                                                              50};

    const seg::t_size m_chatBoxWidth = seg::WINDOW_WIDTH - 100 - m_userBoxWidth;
    const seg::t_size m_chatBoxHeight = seg::WINDOW_HEIGHT / 7;
    const seg::SEG_Point m_chatBoxBeginPoint = seg::SEG_Point{m_controllBeginPoint.x,
                                                              seg::WINDOW_HEIGHT - m_chatBoxHeight -
                                                              200};

    const seg::t_size m_gameroomBoxWidth = m_chatBoxWidth;
    const seg::t_size m_gameroomBoxHeight = m_userBoxHeight - 300;
    const seg::SEG_Point m_gameroomBoxBeginPoint = m_controllBeginPoint;

    const seg::t_size m_btnWidth = m_userBoxWidth;
    const seg::t_size m_btnHeight = 50;
    const seg::SEG_Point m_createBtnBeginPoint = seg::SEG_Point{m_userBoxBeginPoint.x,
                                                                        m_chatBoxBeginPoint.y + 50};

    TWaitingRoom m_waitingRoom;

    std::vector<TWaitingRoomCard> m_gamerooms;
    std::unordered_map<seg::t_unique, std::function<void()>> m_roomClickedFn;
};

SDL_TETRIS_END

#endif //TETRIS_CLIENT_TWAITINGROOMDISPLAY_H
