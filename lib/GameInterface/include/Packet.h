//
// Created by chaed on 19. 2. 19.
//

#ifndef GAMEINTERFACE_PACKET_H
#define GAMEINTERFACE_PACKET_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <iostream>
#include <chrono>
#include <type_traits>
#include <string>

#include <json/json.h> // or jsoncpp/json.h , or json/json.h etc.

#include "EasyTimer/Times.h"

#include "Constant.h"
#include "TypeTraits.h"
#include "Type.h"
#include "Object.h"
#include "MessageType.h"

namespace game_interface::packet {

typedef struct Header
{

    Header() = default;

    Header(const t_unique _destId, const t_unique _senderId, const messageInfo _message)
            : destId(_destId), senderId(_senderId), message(_message)
    {}

    t_unique destId = NULL_ID;
    t_unique senderId = NULL_ID;
    messageDirection where = messageDirection::UNKOWN;
    messageInfo message = messageInfo::UNKWON;
    t_time timestamp = 0;
} Header;


class Packet final
{
public:
    static constexpr const size_t BUF_MAX_SIZE = 1024;
    static constexpr const size_t header_size = sizeof(Header);

    using buffer_type   = unsigned char;
    using buffer_ptr    = buffer_type*;
    using size_type     = t_ssize;
    using packet_type   = std::pair<buffer_type[BUF_MAX_SIZE], size_type>;

    Packet(const Header& _header);

    Packet(const Header& _header, const Json::Value& _payload);

    Packet(Header&& _header, Json::Value&& _payload);

    Packet(const buffer_ptr& buf, const size_type size);

    Packet(const packet_type& _packet);

    Packet(const char*, const size_type);

    friend std::ostream& operator<<(std::ostream& os, const Packet& packet)
    {
        os << "[" << g_modulename ;
        if(packet.m_isRecv)
            os << "RECV]";
        else
            os << "SEND]";
        os << " destid :" << packet.getHeader().destId
            << " / message : " << std::to_string(toUType(packet.getHeader().message))
             << " / timestamp : " << easytimer::get_time_string(packet.getHeader().timestamp) << std::endl;
        return os;
    }

    const std::pair<buffer_type*,long>
    toByte() const;

    void appendObject(const game_interface::Object*);

    inline void setDestId(const t_unique destId)
    {
        m_header.destId = destId;
    }

    inline void setSenderId(const t_unique senderId)
    {
        m_header.senderId = senderId;
    }

    inline void setMessage(const messageInfo message)
    {
        m_header.message = message;
    }

    inline void updateLocale() const
    {
        m_header.timestamp = easytimer::now_to_time();
        m_header.where = g_isServer ? messageDirection::SERVER : messageDirection::CLIENT;
    }

    inline const Header& getHeader() const noexcept
    {
        return m_header;
    };

    inline const Json::Value getPayload() const
    {
        return m_payload;
    }

    static Packet& getNullPacket()
    {
        static Packet p{Header{}};
        return p;
    }

private:

    inline const bool validObjectLeastOne(const Json::Value& json)
    {
        return json.isMember("unique") || json.isMember("maketime");
    }

    inline const bool validObjectAll(const Json::Value& json)
    {
        return json.isMember("unique") && json.isMember("maketime");
    }

    void toPacket();

    mutable Header m_header;
    Json::Value m_payload;

    mutable buffer_type m_buf[BUF_MAX_SIZE];
    mutable size_type   m_bufSize;
    mutable bool        m_validPacket = true;
    const bool          m_isRecv = false;
};

}

#endif //SDL2EASYGUI_PACKET_H
