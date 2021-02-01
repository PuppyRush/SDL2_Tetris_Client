//
// Created by chaed on 19. 2. 20.
//

#ifndef GAMEINTERFACE_PACKETQUEUE_H
#define GAMEINTERFACE_PACKETQUEUE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <thread>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <boost/core/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "Packet.h"
#include "VectorSubject.h"

namespace game_interface {

class PacketQueue : public VectorSubject<game_interface::Observer>,
                    public boost::serialization::singleton<PacketQueue>
{
public:

    using _Base = game_interface::VectorSubject<game_interface::Observer>;
    using element_type = typename _Base::element_type;
    using unique_type = typename _Base::unique_type;

    friend class boost::serialization::singleton<PacketQueue>;

    PacketQueue();

    virtual ~PacketQueue();

    virtual void notify() override;

    void run();

    void pushEvent(packet::Packet&& event);

    void pushEvent(const packet::Packet& event);

    const packet::Packet popEvent();

    bool isEmpty();

    inline void end()
    { m_isContinue.exchange(false); }

    static PacketQueue& getInstance()
    {
        return boost::serialization::singleton<PacketQueue>::get_mutable_instance();
    }

protected:

    virtual void postAttach(const element_type&) override
    {}

    virtual void postDetach(const unique_type) override
    {}

private:

    std::queue<packet::Packet> m_packetQ;
    std::condition_variable m_cond;
    std::mutex m_mutex;
    std::atomic_bool m_isContinue = true;
    std::thread m_thread;
    bool m_isServer = true;
};

}
#endif //SDL2EASYGUI_PACKETQUEUE_H
