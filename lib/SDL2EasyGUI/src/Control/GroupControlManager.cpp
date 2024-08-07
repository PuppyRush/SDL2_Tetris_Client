//
// Created by chaed on 18. 12. 28.
//

#include <cassert>

#include "include/GroupControlManager.h"

using namespace std;
using namespace seg;

GroupControlManager::group& GroupControlManager::get(const group_id grpId)
{
    if (isGroup(grpId)) {
        return m_group.at(grpId);
    } else {
        assert(0);
    }
}

void GroupControlManager::add(const group_id grpId, const t_id ctlId)
{
    if (!isGroup(grpId)) {
        group grp;
        grp.add(ctlId);
        m_group.insert(make_pair(grpId, grp));
    }
}

void GroupControlManager::remove(const group_id grpId)
{
    if (isGroup(grpId)) {
        m_group.erase(grpId);
    } else
        assert(0);

}

void GroupControlManager::remove(const group_id grpId, const t_id ctlId)
{
    if (isGroup(grpId) && get(grpId).count(ctlId) > 0) {

    } else
        assert(0);
}

void GroupControlManager::setMultiselect(const group_id grpId)
{
    if (isGroup(grpId)) {
        get(grpId).setMultiSelected();
    }
}

const std::vector<t_id> GroupControlManager::getSelectedId(const group_id grpId)
{
    if (isGroup(grpId)) {
        const auto& grp = get(grpId);
        vector<t_id> ids;

        if (grp.m_selectedIds.empty()) {
            return ids;
        }

        for (const auto& id : grp.m_selectedIds) {
            ids.emplace_back(id);
        }

        return ids;
    } else
        assert(0);

}

bool GroupControlManager::isGroup(const group_id grpId)
{
    return m_group.count(grpId);
}

void GroupControlManager::select(const group_id grpId, const t_id ctlId)
{
    if (isGroup(grpId)) {
        get(grpId).select(ctlId);
    }
}

void GroupControlManager::unselecte(const group_id grpId, const t_id ctlId)
{
    if (isGroup(grpId)) {
        get(grpId).unselect(grpId);
    }
}

bool GroupControlManager::isSelected(const group_id grpId, const t_id ctlId)
{
    if (isGroup(grpId)) {
        return get(grpId).isSelected(ctlId);
    } else {
        return false;
    }
}