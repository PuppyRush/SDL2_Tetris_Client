//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_MANAGERSUBJECT_H
#define SDL2_TETRIS_SERVER_MANAGERSUBJECT_H

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "VectorSubject.h"
#include "Observer.h"
#include "ManagerInterface.h"

namespace game_interface
{

class ManagerController : public Observer ,
                          public VectorSubject<ManagerInterface>,
                          public boost::serialization::singleton<ManagerController>
{

public:

    using _Base = game_interface::VectorSubject<game_interface::Observer>;

    friend class boost::serialization::singleton<ManagerController>;

    ManagerController(){}
    virtual ~ManagerController(){}

    virtual void updateObserver(const game_interface::Packet& packet);
    virtual void notify() override {}

    static ManagerController& getInstance() {
        return boost::serialization::singleton<ManagerController>::get_mutable_instance();
    }

    virtual const std::string_view& getUniqueName() const override {}
    virtual Json::Value toJson() const override {};

protected:

    virtual void postDetach(_Base::unique_type) override;
    virtual void postAttach(object_type ) override {}

};
}

#endif //SDL2_TETRIS_SERVER_MANAGERSUBJECT_H
