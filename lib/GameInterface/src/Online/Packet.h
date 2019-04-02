//
// Created by chaed on 19. 2. 19.
//

#ifndef TETRIS_FIGURE_CLASS_PACKET_H
#define TETRIS_FIGURE_CLASS_PACKET_H

#include <type_traits>
#include <string>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.

#include "../Constant.h"
#include "../TypeTraits.h"
#include "../Type.h"
#include "../Object/Object.h"
#include "MessageType.h"

namespace game_interface {

class Packet final{
public:

    typedef struct Header{

        Header() = default;
        Header(const t_unique _destId ,const t_unique _senderId, const messageInfo _message )
            :destId(_destId), senderId(_senderId), message(_message)
        {}

        t_unique destId = NULL_ID;
        t_unique senderId = NULL_ID;
        messageDirection where = messageDirection::UNKOWN;
        messageInfo message = messageInfo::UNKWON;
        t_time timestamp = 0;
    } Header;

    static constexpr const size_t BUF_MAX_SIZE = 1024;
    static constexpr const size_t header_size = sizeof(Header);

    using buffer_type = unsigned char;
    using buffer_ptr = buffer_type *;
    using size_type = ssize_t;
    using packet_type = std::pair<buffer_type[BUF_MAX_SIZE], size_type>;

    Packet(const Header& _header);
    Packet(const Header& _header, const Json::Value& _payload);
    Packet(Header &&_header, Json::Value &&_payload);
    Packet(buffer_ptr buf, const size_type size);
    Packet(const packet_type _packet);
    Packet(const char*, const size_type);

    std::pair<std::__decay_and_strip<unsigned char (&)[1024]>::__type, long>
    toByte();

    Packet *toPacket();

    void appendObject(const game_interface::Object*);

    inline void setTimestamp(const t_time time) { m_header.timestamp = time;}
    inline void setUnique(const t_unique id){m_header.destId = id;}

    inline Header& setHeader() noexcept {
        return m_header;
    }

    inline const Header& getHeader() const noexcept {
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
        return json.isMember("unique") or json.isMember("maketime");
    }

    inline const bool validObjectAll(const Json::Value& json)
    {
        return json.isMember("unique") and json.isMember("maketime");
    }

    Header m_header;
    Json::Value m_payload;

    buffer_type m_buf[BUF_MAX_SIZE];
    size_type m_bufSize;

    bool validPacket = true;
};

}

#endif //TETRIS_FIGURE_CLASS_PACKET_H
