//
// Created by chaed on 18. 12. 28.
//

#ifndef SDL2EASYGUI_GROUPCONTROLLMANAGER_H
#define SDL2EASYGUI_GROUPCONTROLLMANAGER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>
#include <memory>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "SEG_Type.h"

namespace seg {
	
class GroupControlManager : public boost::serialization::singleton<GroupControlManager>
{
private:
    friend class boost::serialization::singleton<GroupControlManager>;

	
    typedef struct group
    {
    public:

        void setMultiSelected()
        {
            m_isMultiselection = true;
        }

        void add(const t_id id)
        {
            if (m_unselectedIds.count(id) == 0) {
                m_unselectedIds.insert(id);
            } else
                assert(0);
        }

        void erase(const t_id id)
        {
            if (count(id)) {
                m_unselectedIds.erase((id));
            }
            if (count(id)) {
                m_selectedIds.erase((id));
            }
        }

        bool count(const t_id id)
        {
            if (m_unselectedIds.count(id)) {
                return true;
            }
            if (m_selectedIds.count(id)) {
                return true;
            }
            return false;
        }

        void select(const t_id id)
        {
            if (m_isMultiselection) {
                m_unselectedIds.erase(id);
                m_selectedIds.insert(id);
            } else {
                m_selectedId = id;
                m_unselectedIds.erase(id);
            }
        }

        void unselect(const t_id id)
        {
            if (m_isMultiselection) {
                m_selectedIds.erase(id);
                m_unselectedIds.insert(id);
            } else {
                m_selectedId = -1;
                m_unselectedIds.insert(id);
            }
        }

        const bool isSelected(const t_id id)
        {
            if (m_isMultiselection) {
                return m_selectedIds.count(id);
            } else {
                return m_selectedId == id;
            }

        }

        bool m_isMultiselection = false;

        t_id m_selectedId = -1;
        std::unordered_set<t_id> m_unselectedIds;
        std::unordered_set<t_id> m_selectedIds;
    } group;

public:
	GroupControlManager() = default;

    using group_id = int;

    static const t_id NONE = -1;

    group& get(const group_id grpId);

    const std::vector<t_id> getSelectedId(const group_id grpId);

    void select(const group_id grpId, const t_id ctlId);

    void unselecte(const group_id grpId, const t_id ctlId);

    void add(const group_id grpId, const t_id ctlId);

    void remove(const group_id grpId);

    void remove(const group_id grpId, const t_id ctlId);

    void setMultiselect(const group_id grpId);

    bool isGroup(const group_id grpId);

    bool isSelected(const group_id grpId, const t_id ctlId);

    static GroupControlManager& getInstance()
    {

        return boost::serialization::singleton<GroupControlManager>::get_mutable_instance();
    }

private:

	
  

    std::unordered_map<int, group> m_group;

};

}

#endif //SDL2EASYGUI_TGROUPCONTROLLMANAGER_H
