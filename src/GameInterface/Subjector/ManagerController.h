//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_MANAGERSUBJECT_H
#define SDL2_TETRIS_SERVER_MANAGERSUBJECT_H

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "VectorSubject.h"
#include "../Object/Observer.h"
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

    static std::shared_ptr<ManagerController> getInstance() {

        static auto inst = std::shared_ptr<ManagerController>
            (&boost::serialization::singleton<ManagerController>::get_mutable_instance());
        return inst;
    }

protected:

    virtual void postDetach(_Base::unique_type) override;
    virtual void postAttach(object_type ) override {}

};

}

#endif //SDL2_TETRIS_SERVER_MANAGERSUBJECT_H
