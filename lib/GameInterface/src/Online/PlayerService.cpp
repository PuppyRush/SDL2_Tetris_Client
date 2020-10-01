//
// Created by kim on 19. 1. 10.
//

#include  <iostream>
#include  <ace/OS.h>

#include "Event.h"
#include "PlayerService.h"
#include "PacketQueue.h"

using namespace game_interface;
using namespace game_interface::packet;

PlayerService::PlayerService(ACE_Reactor* reactor)
        : ACE_Event_Handler(reactor), m_peer(ACE_INVALID_HANDLE), m_state(C_INIT), m_reactor(reactor)
{
}

PlayerService::PlayerService(ACE_SOCK_Acceptor& acceptor, ACE_Reactor* reactor)
        : ACE_Event_Handler(reactor), m_peer(ACE_INVALID_HANDLE), m_state(C_INIT), m_reactor(reactor),
          m_acceptor(m_acceptor)
{
    if (-1 == acceptor.accept(m_peer, &m_addr)) {
        delete this;
        return;
    }

    char addr_string[256];
    m_addr.addr_to_string(addr_string, 256);
    std::cout << std::endl << "Enter Client:" << addr_string << std::endl;

    this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
}

PlayerService::~PlayerService(void)
{
}

void
PlayerService::state(CSTATE state)
{
    this->m_state = state;
    if (C_SUCCESS != this->m_state) { return; }
    this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
}

ACE_HANDLE
PlayerService::get_handle(void) const
{
    return this->m_peer.get_handle();
}

void PlayerService::sendPacket(const Packet& packet) const
{
    //if (C_SUCCESS != this->m_state) { return; }

    packet.updateLocale();

    std::cout << packet;
    const auto&[bytes, len] = packet.toByte();

    ACE_Message_Block* mb = new ACE_Message_Block(len);
    ACE_OS::memcpy(mb->wr_ptr(), bytes, len);
    mb->wr_ptr(len);

    this->m_sendDatas.enqueue_tail(mb);
    m_reactor->register_handler((ACE_Event_Handler*)this, ACE_Event_Handler::WRITE_MASK);
    m_reactor->register_handler((ACE_Event_Handler*)this, ACE_Event_Handler::READ_MASK);
}

int
PlayerService::handle_input(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    const int BUF = 1024;
    unsigned char* in = new unsigned char[BUF];

    ACE_Time_Value rt(0, 0);

    ssize_t len = this->m_peer.recv(in, BUF - 1, &rt);
    if (len <= 0) {// 서버  종료  또는  통신  에러
        return -1;
    }

    in[len] = 0;

    Packet p{in, len};
    PacketQueue::getInstance().pushEvent(p);

    return 0;
}

int
PlayerService::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
    std::cout << "Disconntected" << std::endl;
    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);

    this->m_peer.close();
    this->m_peer.set_handle(ACE_INVALID_HANDLE);
    this->state(C_INIT);
    this->m_sendDatas.flush();
    return 0;
}

int
PlayerService::handle_output(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    ACE_Message_Block* mb(NULL);
    ACE_Time_Value rt(0, 0);

    do {
        this->m_sendDatas.dequeue_head(mb, &rt);

        ssize_t len = this->m_peer.send(mb->rd_ptr(), mb->length(), &rt);
        if (len < 0) {//통신  에러  발생
            mb->release();
            return handle_input(fd);
        }

        mb->rd_ptr(len);
        if (mb->length() > 0) {
            this->m_sendDatas.enqueue_head(mb);
            break;
        }

        mb->release();

    } while (false);

    if (this->m_sendDatas.is_empty()) {
        ACE_Reactor_Mask m = ACE_Event_Handler::WRITE_MASK | ACE_Event_Handler::DONT_CALL;
        this->reactor()->remove_handler(this, m);
    }

    return 0;
}