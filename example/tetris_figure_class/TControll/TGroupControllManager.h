//
// Created by chaed on 18. 12. 28.
//

#ifndef TETRIS_FIGURE_CLASS_TGROUPCONTROLLMANAGER_H
#define TETRIS_FIGURE_CLASS_TGROUPCONTROLLMANAGER_H

#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "TControll.h"

SDL_TETRIS_BEGIN

class TGroupControllManager final {
public:

    static std::shared_ptr<TGroupControllManager> getInstance();

private:

    typedef struct group
    {
        std::unordered_set<t_id>  unselectedIds;
        std::unordered_set<t_id>  selectedIds;

        void add(const t_id id)
        {
            if(unselectedIds.count(id)==0)
                unselectedIds.insert(id);
            else
                assert(0);
        }

        void toSelected(const t_id id)
        {
            if(unselectedIds.count(id)==0)
                assert(0);
            if(selectedIds.count(id))
                assert(0);
            unselectedIds.erase(id);
            selectedIds.insert(id);
        }

        void toUnSelected(const t_id id)
        {
            if(selectedIds.count(id)==0)
                assert(0);
            if(unselectedIds.count(id))
                assert(0);
            selectedIds.erase(id);
            unselectedIds.insert(id);
        }
    };


    TGroupControllManager() = default;
    std::unordered_map<int,group> m_group;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TGROUPCONTROLLMANAGER_H
