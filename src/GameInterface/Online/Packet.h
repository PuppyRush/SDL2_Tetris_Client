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
#include "MessageType.h"

namespace game_interface {

class Packet {
public:

    typedef struct {
        t_unique objectId = NULL_ID;
        messageDirection where = messageDirection::UNKOWN;
        messageInfo message = messageInfo::UNKWON;
    } Header;

    static constexpr const size_t BUF_MAX_SIZE = 1024;
    static constexpr const size_t header_size = sizeof(Header);

    using buffer_type = unsigned char;
    using buffer_ptr = buffer_type *;
    using size_type = ssize_t;
    using packet_type = std::pair<buffer_type[BUF_MAX_SIZE], size_type>;

    Packet(const Header &_header, const Json::Value &_payload);
    Packet(Header &&_header, Json::Value &&_payload);
    Packet(buffer_ptr buf, const size_type size);
    Packet(const packet_type _packet);

    std::pair<std::__decay_and_strip<unsigned char (&)[1024]>::__type, long> toByte();
    Packet *toPacket();

    inline const Header &getHeader() const noexcept {
        assert(m_header.objectId != NULL_ID and
            m_header.where != messageDirection::UNKOWN and
            m_header.message != messageInfo::UNKWON);

        return m_header;
    };

private:

    Header m_header;
    Json::Value m_payload;

    buffer_type m_buf[BUF_MAX_SIZE];
    size_type m_bufSize;
};

}

#endif //TETRIS_FIGURE_CLASS_PACKET_H
