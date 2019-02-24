//
// Created by chaed on 19. 2. 20.
//

#ifndef TETRIS_FIGURE_CLASS_PACKETQUEUE_H
#define TETRIS_FIGURE_CLASS_PACKETQUEUE_H

#include <thread>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <boost/core/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "Packet.h"
#include "../Subjector/MapSubject.h"

namespace game_interface {

class PacketQueue : public MapSubject, public boost::serialization::singleton<PacketQueue> {
public:

    friend class boost::serialization::singleton<PacketQueue>;

    PacketQueue();
    ~PacketQueue() = default;

    virtual void notify() override;

    void pushEvent(Packet &&event);
    void pushEvent(const Packet &event);
    Packet popEvent();

    static PacketQueue &getInstance() {

        return boost::serialization::singleton<PacketQueue>::get_mutable_instance();
    }

protected:

    virtual void postDetach(unique_type ) override {}
    virtual void postAttach(object_type) override {};

private:

    std::queue<Packet> m_packetQ;
    std::condition_variable m_cond;
    std::mutex m_mutex;
    std::atomic_bool m_isContinue = true;
    std::thread m_thread;

};

}

#endif //TETRIS_FIGURE_CLASS_PACKETQUEUE_H
