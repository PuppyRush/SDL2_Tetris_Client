//
// Created by chaed on 19. 2. 19.
//

#include <algorithm>

#include "Packet.h"

using namespace game_interface;

Packet::Packet(const Header& header)
        : m_header(header)
{
    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(const Header& _header, const Json::Value& _payload)
        : m_header(_header), m_payload(_payload)
{
    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(Header&& _header, Json::Value&& _payload)
        : m_header(_header), m_payload(_payload)
{
    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(buffer_ptr buf, const size_type size)
        : m_bufSize(size)
{
    if (size >= BUF_MAX_SIZE) {
        validPacket = false;
        m_bufSize = BUF_MAX_SIZE;
    }

    memcpy(m_buf, buf, size);
}

Packet::Packet(const packet_type _packet)
        : m_bufSize(_packet.second)
{
    if (_packet.second > BUF_MAX_SIZE) {
        validPacket = false;
        m_bufSize = BUF_MAX_SIZE;
    }
    memcpy(m_buf, _packet.first, _packet.second);

}

Packet::Packet(const char* buf, const size_type len)
        : m_bufSize(len)
{
    memcpy(m_buf, buf, len);
}

std::pair<std::__decay_and_strip<unsigned char (&)[1024]>::__type, long>
Packet::toByte()
{
    memset(m_buf, 0, BUF_MAX_SIZE);

    if (m_header.where == messageDirection::UNKOWN or
        m_header.message == messageInfo::UNKWON or
        m_header.timestamp == 0) {
        validPacket = false;
        return std::make_pair(m_buf, 0);
    }

    Json::StyledWriter styledWriter;
    const auto plyloadbuf = styledWriter.write(m_payload);

    memcpy(m_buf, &m_header, header_size);
    memcpy(m_buf + header_size, plyloadbuf.c_str(), plyloadbuf.size());

    m_bufSize = header_size + plyloadbuf.size();

    return std::make_pair(m_buf, m_bufSize);
}

Packet* Packet::toPacket()
{
    if (m_bufSize <= 0) {
        validPacket = false;
        return this;
    }

    memcpy(&m_header, m_buf, header_size);

    auto bufstr = reinterpret_cast< char*>(m_buf + header_size);

    Json::Reader reader;
    reader.parse(bufstr, m_payload);

    return this;
}

void Packet::appendObject(const game_interface::Object* obj)
{
    if (validPacket = validObjectAll(obj)) {
        assert(0);
        return;
    }

    m_payload["unique"] = static_cast<Json::Value::UInt64>(obj->getUnique());
    m_payload["maketime"] = static_cast<Json::Value::UInt64>(obj->getMaketime());
}
