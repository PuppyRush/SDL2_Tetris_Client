//
// Created by chaed on 18. 12. 28.
//

#include <cassert>

#include "TGroupControllManager.h"

SDL_TETRIS
using namespace std;

TGroupControllManager::group& TGroupControllManager::get(const group_id grpId)
{
    if(isGroup(grpId))
        return m_group.at(grpId);
    else
    {
        assert(0);
    }
}

void TGroupControllManager::add(const group_id grpId, const t_id ctlId)
{
    if(!isGroup(grpId))
    {
         group grp;
         grp.add(ctlId);
         m_group.insert(make_pair(grpId, grp));
    }
}

void TGroupControllManager::remove(const group_id grpId)
{
    if(isGroup(grpId))
    {
        m_group.erase(grpId);
    } else
        assert(0);

}

void TGroupControllManager::remove(const group_id grpId, const t_id ctlId)
{
    if(isGroup(grpId) && get(grpId).count(ctlId)>0)
    {

    } else
        assert(0);
}

void TGroupControllManager::setMultiselect(const group_id grpId)
{
    if(isGroup(grpId))
        get(grpId).setMultiSelected();
}

const std::vector<t_id> TGroupControllManager::getSelectedId(const group_id grpId)
{
    if(isGroup(grpId))
    {
        const auto& grp = get(grpId);
        vector<t_id> ids;

        if(grp.m_selectedIds.empty())
            return ids;

        for(const auto& id : grp.m_selectedIds)
            ids.emplace_back(id);

        return ids;
    } else
        assert(0);

}

bool TGroupControllManager::isGroup(const group_id grpId)
{
    return m_group.count(grpId);
}

void TGroupControllManager::select(const group_id grpId, const t_id ctlId)
{
    if(isGroup(grpId))
    {
        get(grpId).toSelected(grpId);
    }
}

void TGroupControllManager::unselecte(const group_id grpId, const t_id ctlId)
{
    if(isGroup(grpId))
    {
        get(grpId).toUnSelected(grpId);
    }
}

std::shared_ptr<TGroupControllManager> TGroupControllManager::getInstance()
{
    static auto inst = std::shared_ptr<TGroupControllManager>(new TGroupControllManager());
    return inst;
}