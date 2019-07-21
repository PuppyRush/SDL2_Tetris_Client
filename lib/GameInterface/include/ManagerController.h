//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_MANAGERSUBJECT_H
#define SDL2_TETRIS_SERVER_MANAGERSUBJECT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "VectorSubject.h"
#include "Observer.h"
#include "ManagerInterface.h"

namespace game_interface {

class ManagerController : public Observer,
                          public VectorSubject<ManagerInterface>,
                          public boost::serialization::singleton<ManagerController>
{

public:

    using _Base = game_interface::VectorSubject<ManagerInterface>;
    using element_type = typename _Base::element_type;
    using unique_type = typename _Base::unique_type;

    friend class boost::serialization::singleton<ManagerController>;

    ManagerController()
    {}

    virtual ~ManagerController()
    {}

    virtual void updateObserver(const packet::Packet& packet);

    virtual void notify() override
    {}

    static ManagerController& getInstance()
    {
        return boost::serialization::singleton<ManagerController>::get_mutable_instance();
    }

    virtual const std::string_view& getUniqueName() const override final
    {
        assert(0);
        return NAME_NULL;
    }

    virtual Json::Value toJson() const override
    {
        assert(0);
        return Json::Value{};
    }

protected:

    virtual void postDetach(const unique_type unique) override;

    virtual void postAttach(const element_type&) override
    {}

};
}

#endif //SDL2_TETRIS_SERVER_MANAGERSUBJECT_H
