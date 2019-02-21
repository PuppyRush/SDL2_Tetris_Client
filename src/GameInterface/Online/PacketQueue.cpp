//
// Created by chaed on 19. 2. 21.
//

#include "PacketQueue.h"

using namespace game_interface;

PacketQueue::PacketQueue()
{
    this->m_thread = std::thread(&PacketQueue::notify, this);
}


void PacketQueue::pushEvent(Packet&& event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_packetQ.push(std::move(event));
    m_cond.notify_one();
}

void PacketQueue::pushEvent(const Packet& event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_packetQ.push(event);
    m_cond.notify_one();
}

const Packet PacketQueue::popEvent()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond.wait(lock, [=](){return !m_packetQ.empty() || !m_isContinue;});

    const auto msg = m_packetQ.front();
    m_packetQ.pop();

}

void PacketQueue::notify()
{
    while(m_isContinue)
    {
        auto& packet = popEvent();
        if(getContainer().count(packet.getHeader().objectId)) {
            const auto& obj = getContainer().at(packet.getHeader().objectId);
            getContainer().at(packet.getHeader().objectId)->updateObserver(*obj, packet);
        }
    }
}
