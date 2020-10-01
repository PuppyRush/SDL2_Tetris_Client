//
// Created by chaed on 19. 2. 21.
//

#include "PacketQueue.h"
#include "ManagerController.h"
#include "Constant.h"

using namespace game_interface;
using namespace game_interface::packet;

PacketQueue::PacketQueue()
{
}

PacketQueue::~PacketQueue()
{
    end();
    m_cond.notify_one();
    m_thread.join();
}

void PacketQueue::run()
{
    m_isServer = g_isServer;
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
    m_cond.wait(lock, [=]() { return !m_packetQ.empty() || !m_isContinue; });

    if (!m_isContinue) {
        return Packet::getNullPacket();
    }

    const auto msg = m_packetQ.front();
    m_packetQ.pop();
    return msg;
}

void PacketQueue::notify()
{
    auto& mngCtl = game_interface::ManagerController::getInstance();

    if (m_isServer) {
        while (m_isContinue) {
            const auto packet = popEvent();

            std::cout << packet;

            mngCtl.updateObserver(packet);
        }
    } else {
        while (m_isContinue) {
            auto packet = popEvent();

            std::cout << packet;

            if (packet.getHeader().where == messageDirection::CLIENT) {
                continue;
            }

            for (auto& obj : m_objects) {
                obj->updateObserver(packet);
            }
        }
    }
}
