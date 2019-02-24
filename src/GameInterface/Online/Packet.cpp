//
// Created by chaed on 19. 2. 19.
//

#include <algorithm>

#include "Packet.h"

using namespace game_interface;

Packet::Packet(const Header& header)
    :m_header(header)
{
}


Packet::Packet(const Header& _header, const Json::Value& _payload)
    :m_header(_header), m_payload(_payload)
{
    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(Header&& _header, Json::Value&& _payload)
    :m_header(_header), m_payload(_payload)
{
    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(buffer_ptr buf, const size_type size)
    :m_bufSize(size)
{
    assert(size<BUF_MAX_SIZE);
    memcpy(m_buf,buf,size);
    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(const packet_type _packet)
    :m_bufSize(_packet.second)
{
    assert(_packet.second <= 1024);
    memcpy(m_buf,_packet.first, _packet.second);

    this->m_header.timestamp = std::time(nullptr);
}

Packet::Packet(const char* buf, const size_type len)
{
     char* b = const_cast<char*>(buf);
     memcpy(m_buf,b,len);
}



std::pair<std::__decay_and_strip<unsigned char (&)[1024]>::__type, long>
Packet::toByte()
{
    memset(m_buf,0,m_bufSize);

    assert(m_header.message != messageInfo::UNKWON and m_header.where != messageDirection::UNKOWN);

    Json::StyledWriter styledWriter;
    const auto plyloadbuf = styledWriter.write(m_payload);

    buffer_type headerBuf[header_size];
    memcpy(headerBuf,&m_header,header_size);

    memcpy(m_buf,headerBuf,header_size);
    memcpy(m_buf+header_size,plyloadbuf.c_str(), plyloadbuf.size());

    return std::make_pair(m_buf, m_bufSize);
}

Packet* Packet::toPacket()
{
    assert(m_bufSize>0);

    Header header;
    memcpy(&header,m_buf,header_size);

    Json::Reader reader;
    reader.parse(reinterpret_cast< char*>(m_buf+header_size), m_payload);

    return this;
}
