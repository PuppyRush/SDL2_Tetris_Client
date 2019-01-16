//
// Created by chaed on 18. 12. 28.
//

#ifndef TETRIS_FIGURE_CLASS_TGROUPCONTROLLMANAGER_H
#define TETRIS_FIGURE_CLASS_TGROUPCONTROLLMANAGER_H

#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "THeader.h"

SDL_TETRIS_BEGIN

class TGroupControllManager final {
//pre-declareation
private:
    typedef struct group;

public:

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

    static std::shared_ptr<TGroupControllManager> getInstance();

private:

    typedef struct group
    {
    public:

        void setMultiSelected()
        {
            m_isMultiselection = true;
        }

        void add(const t_id id)
        {
            if(m_unselectedIds.count(id)==0)
                m_unselectedIds.insert(id);
            else
                assert(0);
        }

        void erase(const t_id id)
        {
            if(count(id))
                m_unselectedIds.erase((id));
            if(count(id))
                m_selectedIds.erase((id));
        }

        bool count(const t_id id)
        {
            if(m_unselectedIds.count(id))
                return true;
            if(m_selectedIds.count(id))
                return true;
            return false;
        }

        void toSelected(const t_id id)
        {
            if(m_isMultiselection)
            {
                m_unselectedIds.erase(id);
                m_selectedIds.insert(id);
            }
            else
            {
                m_selectedId = TGroupControllManager::NONE;
                m_unselectedIds.erase(id);
            }
        }

        void toUnSelected(const t_id id)
        {
            if(m_isMultiselection)
            {
                m_selectedIds.erase(id);
                m_unselectedIds.insert(id);
            }
            else
            {
                m_selectedId = -1;
                m_unselectedIds.insert(id);
            }

        }

        bool m_isMultiselection = false;

        t_id m_selectedId = -1;
        std::unordered_set<t_id>  m_unselectedIds;
        std::unordered_set<t_id>  m_selectedIds;
    }group;

    TGroupControllManager() = default;
    std::unordered_map<int,group> m_group;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TGROUPCONTROLLMANAGER_H
