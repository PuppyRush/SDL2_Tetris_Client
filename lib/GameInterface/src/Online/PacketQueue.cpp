//
// Created by chaed on 19. 2. 21.
//

#include "PacketQueue.h"
#include "../SubScription/ManagerController.h"

using namespace game_interface;

PacketQueue::PacketQueue()
{
}

void PacketQueue::initialize()
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

Packet PacketQueue::popEvent()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond.wait(lock, [=](){return !m_packetQ.empty() || !m_isContinue;});

    const auto msg = m_packetQ.front();
    m_packetQ.pop();
    return msg;
}

void PacketQueue::notify()
{
    auto& mngCtl = *game_interface::ManagerController::getInstance();

    if(m_isServer)
    {
        while (m_isContinue) {
            auto packet = popEvent();


            printf("client recv : %d %d %ld\n", packet.getHeader().destId, toUType(packet.getHeader().message),
                   packet.getHeader().timestamp);

            mngCtl.updateObserver(packet);
        }
    }
    else
    {
        while (m_isContinue) {
            auto packet = popEvent();
            packet.toPacket();

            printf("client recv : %d %d %ld\n", packet.getHeader().destId, toUType(packet.getHeader().message),
                   packet.getHeader().timestamp);

            if(packet.getHeader().where == messageDirection::CLIENT)
                continue;

            for(auto& obj : m_objects)
            {
                obj->updateObserver(packet);
            }
        }
    }
}
