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

namespace seg {



class BoxItemBuilder;
class BoxItem : public Control
{
public:

    using Base = Control;
    using string_type = std::string;

    BoxItem(const BoxItemBuilder& bld);

    BoxItem(BoxItemBuilder&& bld);

    virtual ~BoxItem() = default;

    t_size getIndex() const noexcept
    {
        return m_idx;
    }

    void setIndex(t_size i)
    {
        //caching = false;
        this->m_idx = i;
    }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onDraw() override;

    // virtual void setOriginString(std::string& _origin) = 0;

protected:
    //bool caching = false;

private:

    BoxItem() = delete;

    t_size m_idx;
};

class BoxItemBuilder : public ControlBuilderBase
{
public:

    BoxItemBuilder() = delete;

    virtual ~BoxItemBuilder() = default;

    BoxItemBuilder(const GraphicInterface::window_type window, const std::string& str)
        : ControlBuilderBase(window)
    {
        m_basic.visible = false;
        text(str);
        id(atomic::getUniqueId());
    }

    BoxItemBuilder(const GraphicInterface::window_type window, std::string&& str)
        : ControlBuilderBase(window)
    {
        m_basic.visible = false;
        text(str);
        id(atomic::getUniqueId());
    }

    virtual inline BoxItemBuilder* text(std::string&& str) noexcept override
    {
        m_basic.text = str;
        return this;
    }

    virtual inline BoxItemBuilder* text(const std::string& str) noexcept override
    {
        m_basic.text = str;
        return this;
    }

    virtual inline BoxItemBuilder* font(const SEG_TFont& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline BoxItemBuilder* font(SEG_TFont&& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline BoxItemBuilder* fontSize(t_size size) noexcept
    {
        m_basic.font.size = size;
        return this;
    }

    virtual inline BoxItemBuilder* fontColor(SEG_Color color) noexcept
    {
        m_basic.font.color = color;
        return this;
    }

    virtual Control::control_ptr build()
    {
             return new BoxItem(*this);
    }

protected:
    t_id m_id;

    virtual inline BoxItemBuilder* id(t_id id) noexcept override
    {
        m_id = atomic::getUniqueId();
        return this;
    }

private:

    virtual inline BoxItemBuilder* point(SDL_Point pt) noexcept override
    {
        return this;
    }

    virtual inline BoxItemBuilder* position(SDL_Rect rect) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* width(t_size size) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* height(t_size size) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* grouping(t_size idx) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* selected() noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderLineType(BorderBoundaryLineType lineType) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderBoundaryType(BorderBoundaryType type) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderColor(SEG_Color lineColor) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderAngle(int borderAngle) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderThick(int borderThick) noexcept
    {
        return this;
    }



};

class BoxBasicBuilder;
class BoxBasic : public Border
{
public:

    using Base = Border;
    using item_type = BoxItem;
    using string_type = std::string;
    using item_ptr = item_type*;
    using item_ary = std::vector<item_ptr>;

    void calculateVisibleMenuIndexRange();

    inline void setVisibleMenuCount(t_size mVisibleMenuCnt)
    {
        m_visibleMenuCnt = mVisibleMenuCnt;
    }

    inline t_size getVisibleMenuCount() const noexcept
    {
        return m_visibleMenuCnt;
    }

    virtual void addItem(const item_ptr item);

    virtual void addItem(const item_type::string_type& str);

    virtual void addItem(item_type::string_type&& str);

    virtual item_ptr popItem();

    virtual item_ptr removeItem(t_size idx);

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
