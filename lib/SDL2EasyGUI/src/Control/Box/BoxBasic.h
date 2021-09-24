//
// Created by chaed on 19. 4. 21.
//

#ifndef SDL2EASYGUI_BOXBASIC_H
#define SDL2EASYGUI_BOXBASIC_H

#include <vector>
#include <list>

#include "SDL2EasyGUI/include/ControlBuilderBase.h"
#include "SDL2EasyGUI/include/SEG_Drawer.h"
#include "../Border.h"
#include "SDL2EasyGUI/include/BoxItem.h"

namespace seg {


class BoxBasicBuilder;
class BoxBasic : public Border
{
public:

    using Base = Border;
    using item_type = BoxItem;
    using item_ptr = item_type*;
    using item_ary = std::vector<item_ptr>;
    using string_type = std::string;


    inline void setVisibleMenuCount(t_size mVisibleMenuCnt)
    {
        m_visibleMenuCnt = mVisibleMenuCnt;
    }

    inline t_size getVisibleMenuCount() const noexcept
    {
        return m_visibleMenuCnt;
    }


    inline t_size getVisibleMenuWidth() const noexcept
    {
        return m_visibleMenuWidth;
    }

    inline void setVisibleMenuWidth(t_size w)
    {
        m_visibleMenuWidth = w;
    }
   
    inline t_size getMenuHeight() const noexcept
    {
        return m_menuHeight;
    }

    inline void setMenuHeight(t_size mMenuHeight)
    {
        m_menuHeight = mMenuHeight;
    }
    
    inline int getBoundedMenuIndex() const noexcept
    {
        return m_boundedMenuIndex;
    }

    inline void setBoundedMenuIndex(size_t mBoundedMenuIndx)
    {
        m_boundedMenuIndex = mBoundedMenuIndx;
    }

    inline t_size getBoxStartIndex() const noexcept
    {
        return m_boxItemManager.getStartIndex();
    }

    inline t_size getBoxEndIndex() const noexcept
    {
        return m_boxItemManager.getEndIndex();
    }

    inline void setBoxStartIndex(int mMenuStartIdx)
    {
        m_boxItemManager.setStartIndex(mMenuStartIdx);
    }

    inline t_size getScrollMoveUnit() const noexcept
    {
        return m_scrollmovingUnitCount;
    }

    inline void setScrollMoveUnit(t_size unit) noexcept
    {
        m_scrollmovingUnitCount = unit;
    }

    inline t_size getScrollMoveUnitSize() const noexcept
    {
        return m_scrollmovingUnitSize;
    }

    inline void setScrollMoveUnitSize(t_size size) noexcept
    {
        m_scrollmovingUnitSize = size;
    }

    inline bool hasTitleBox() const noexcept
    {
        return m_hasTitleBox;
    }

    inline void setHasTitleBox(bool hasTitleBox) noexcept
    {
        m_hasTitleBox = hasTitleBox;
    }

    void calculateVisibleMenuIndexRange();

    virtual void addItem(const item_ptr item);

    virtual void addItem(const item_type::string_type& str);

    virtual void addItem(item_type::string_type&& str);

    virtual item_ptr popItem();

    virtual item_ptr removeItem(t_size idx);

    virtual void onEvent(const SDL_Event& event) override;

    virtual void onDraw() override;

    virtual void initialize() override;

    virtual iterator removeComponent(component_type::unique_type resId) override;

    virtual iterator removeComponent(iterator& it) override;

    virtual iterator removeComponentFromIndex(t_size idx) override;

    virtual void popComponent() noexcept override;

    virtual void goUpScrollByUnit();

    virtual void goDownScrollByUnit();

protected:
    
    const t_size MENU_GAP = 3;
    t_size m_boundedMenuIndex = INVALID_SIZE;

    BoxBasic(BoxBasicBuilder& bld);

    virtual ~BoxBasic() = default;

    void _autoFitBox(const t_size idx);

    bool _isBoundInMenues();
 
    virtual t_size _calcIndexOf(const t_coord y);

private:
    /////전체 박스 아이템중 화면에 보이게 될 박스들만 관리한다.
    ////필요한 변수. 
    //콤보박스의 시작 위치
    //보여질 ItemBox의 포인터
    //보여질 갯수
    ////필요한 기능
    //위로,아래로 n칸
    //n칸 움질일때 마다 ItemBox의 위치 조정 및 보일 ItemBox 조정
    //

    class BoxItemManager
    {
    public:

        using AryType = std::list<Control*>;

        friend class BoxBasic;

        BoxItemManager(BoxBasic& boxBasic);

        ~BoxItemManager() = default;


        void insert(Control* box);

        void remove(t_size idx);

        void repositionItems();

        void moveDownOf(t_size n);

        void moveUpOf(t_size n);

        void visibleAll();

        void divisibleAll();

        void setStartIndex(t_size mMenuStartIdx);

        inline t_size getStartIndex() const noexcept
        {
            return m_visibleMenuIndexRange.first;
        }

        inline t_size getEndIndex() const noexcept
        {
            return m_visibleMenuIndexRange.second;
        }

        inline t_size getSize() const noexcept
        {
            return m_boxItemAry.size();
        }

        AryType::iterator begin()
        {
            return m_boxItemAry.begin();
        }

        AryType::iterator end()
        {
            return m_boxItemAry.end();
        }

        SDL_Rect calculatePosition(int i);

    private:

        void push_back(Control* box);

        void pop_back();

        void push_front(Control* box);

        void pop_front();

        void calculateVisibleMenuIndexRange();

    private:

        bool m_isChanged = false;
        BoxBasic& m_boxbasic;
        AryType m_boxItemAry;
        std::pair<t_size, t_size> m_visibleMenuIndexRange;
    };

protected:
    inline BoxItemManager& _getBoxItemManager() noexcept
    {
        return m_boxItemManager;
    }

    virtual void addComponent(const component_ptr& component) override;

private:
    t_size m_visibleMenuCnt = 3;
    t_size m_menuHeight = 0;
    t_size m_visibleMenuWidth = 0;
    t_size m_scrollmovingUnitCount = 1;
    t_size m_scrollmovingUnitSize = 10;
    bool   m_hasTitleBox = false;
    BoxItemManager m_boxItemManager;
};


class BoxBasicBuilder : public BorderBuilder
{
public:

    using item_type = Control;
    using item_ptr = item_type*;
    using item_ary = std::vector<item_ptr>;


    BoxBasicBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
        : BorderBuilder(window, point, str)
    {
        addItem(str);
    }

    BoxBasicBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
        : BorderBuilder(window, point, str)
    {
        addItem(str);
    }

    virtual ~BoxBasicBuilder() = default;

    virtual inline ControlBuilder* width(t_size size) noexcept override
    {
        BorderBuilder::width(size);
        for (auto& items : getItems())
        {
            items->setWidth(size);
        }
        return this;
    }

    BoxBasicBuilder* addItem(const std::string& str)
    {
        auto bld = BoxItemBuilder{ m_basic.window, str }.build();
        bld->setWidth(this->getBasic().width);
        m_items.emplace_back(bld);
        return this;
    }

    BoxBasicBuilder* addItem(std::string&& str)
    {
        auto bld = BoxItemBuilder{ m_basic.window, str }.build();
        bld->setWidth(this->getBasic().width);
        m_items.emplace_back(std::move(bld));
        return this;
    }

    BoxBasicBuilder* addItem(const BoxItemBuilder& item)
    {
        auto bld = const_cast<BoxItemBuilder&>(item).build();
        bld->setWidth(this->getBasic().width);
        m_items.emplace_back(bld);
        return this;
    }

    BoxBasicBuilder* addItem(BoxItemBuilder&& item)
    {
        auto bld = item.build();
        bld->setWidth(this->getBasic().width);
        m_items.emplace_back(bld);
        return this;
    }

    const item_ary& getItems() const noexcept
    {
        return m_items;
    }

    t_size count() const noexcept
    {
        return m_items.size();
    }

    virtual Control::control_ptr build() = 0;

private:

    item_ary m_items;
};
}

#endif //UICLASSEXAMPLE_BOXBASIC_H
