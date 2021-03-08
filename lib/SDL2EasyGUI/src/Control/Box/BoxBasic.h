//
// Created by chaed on 19. 4. 21.
//

#ifndef SDL2EASYGUI_BOXBASIC_H
#define SDL2EASYGUI_BOXBASIC_H

#include <vector>

#include "SDL2EasyGUI/include/ControlBuilderBase.h"
#include "SDL2EasyGUI/include/SEG_Drawer.h"
#include "../Border.h"

namespace seg {



class BoxBasicItemBuilder;
class BoxItem : public Control
{
public:

    using Base = Control;
    using string_type = std::string;

    BoxItem(const BoxBasicItemBuilder& bld);

    BoxItem(BoxBasicItemBuilder&& bld);

    virtual ~BoxItem() = default;

    size_t getIndex() const noexcept
    {
        return m_idx;
    }

    void setIndex(size_t i)
    {
        //caching = false;
        this->m_idx = i;
    }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    // virtual void setOriginString(std::string& _origin) = 0;

protected:
    //bool caching = false;

private:

    BoxItem() = delete;

    std::size_t m_idx;
};

class BoxBasicItemBuilder : public ControlBuilderBase
{
public:

    virtual ~BoxBasicItemBuilder() = default;

    BoxBasicItemBuilder(const GraphicInterface::window_type window, const std::string& str)
        : ControlBuilderBase(window)
    {
        text(str);
        id(atomic::getUniqueId());
    }

    BoxBasicItemBuilder(const GraphicInterface::window_type window, std::string&& str)
        : ControlBuilderBase(window)
    {
        text(str);
        id(atomic::getUniqueId());
    }

    virtual inline BoxBasicItemBuilder* text(std::string&& str) noexcept override
    {
        m_basic.text = str;
        return this;
    }

    virtual inline BoxBasicItemBuilder* text(const std::string& str) noexcept override
    {
        m_basic.text = str;
        return this;
    }

    virtual inline BoxBasicItemBuilder* font(const SEG_TFont& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline BoxBasicItemBuilder* font(SEG_TFont&& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline BoxBasicItemBuilder* fontSize(t_size size) noexcept
    {
        m_basic.font.size = size;
        return this;
    }

    virtual inline BoxBasicItemBuilder* fontColor(SEG_Color color) noexcept
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

    virtual inline BoxBasicItemBuilder* id(t_id id) noexcept override
    {
        m_id = atomic::getUniqueId();
        return this;
    }

private:

    virtual inline BoxBasicItemBuilder* point(SDL_Point pt) noexcept override
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* position(SDL_Rect rect) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* width(t_size size) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* height(t_size size) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* grouping(size_t idx) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* selected() noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* borderLineType(BorderBoundaryLineType lineType) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* borderBoundaryType(BorderBoundaryType type) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* borderColor(SEG_Color lineColor) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* borderAngle(int borderAngle) noexcept
    {
        return this;
    }

    virtual inline BoxBasicItemBuilder* borderThick(int borderThick) noexcept
    {
        return this;
    }



};
/////


class BoxBasicBuilder;
class BoxBasic : public Border
{
public:

    using Base = Border;
    using item_type = BoxItem;
    using string_type = std::string;
    using item_ptr = std::shared_ptr<item_type>;
    using item_ary = std::vector<item_ptr>;

    void recalculateBoxesPosition();

    std::pair<t_size, t_size> getvisibleMenuIndexRange();

    inline void setVisibleMenuCount(size_t mVisibleMenuCnt)
    {
        m_visibleMenuCnt = mVisibleMenuCnt;
    }

    inline size_t getVisibleMenuCount() const noexcept
    {
        return m_visibleMenuCnt;
    }

    inline size_t getBoxStartIndex() const noexcept
    {
        return m_boxStartIndex;
    }

    inline void setBoxStartIndex(int mMenuStartIdx)
    {
        if (mMenuStartIdx < 0)
        {
            mMenuStartIdx = 0;
        }
        else if (mMenuStartIdx > (m_items.size() - m_visibleMenuCnt))
        {
            mMenuStartIdx = m_items.size() - m_visibleMenuCnt;
        }
        m_boxStartIndex = mMenuStartIdx;
        recalculateBoxesPosition();
    }

    void addItem(const item_ptr item);

    virtual void addItem(const item_type::string_type& str);

    virtual void addItem(const item_type::string_type&& str);

    virtual item_ptr popItem();

    virtual item_ptr removeItem(t_size idx);

    inline item_ary& getItems()
    {
        return m_items;
    }

    inline void setItems(const item_ary& mItems)
    {
        m_items = mItems;
    }

    item_ptr getItem(const size_t idx)
    {
        return m_items.at(idx);
    }

    item_ptr at(const size_t index)
    {
        assert(m_items.size() > index);
        return m_items.at(index);
    }

    inline t_size getBoxCount() const noexcept
    {
        return m_items.size();
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

    inline void setBoundedMenuIndex(int mBoundedMenuIndx)
    {
        m_boundedMenuIndex = mBoundedMenuIndx;
    }

    virtual void onEvent(const SDL_Event& event);

    virtual void onDraw() override;

    virtual void initialize() override;

protected:

    item_ary m_items;
    t_size m_boundedMenuIndex = INVALID_SIZE;

    BoxBasic(BoxBasicBuilder& bld);

    virtual ~BoxBasic() = default;

    void autoFitBox(const size_t idx);

    bool _isBoundInMenues();

private:
    t_size m_visibleMenuCnt = 3;
    t_size m_boxStartIndex = 0;
    t_size m_menuHeight = 0;
    t_size m_visibleMenuWidth = 0;
};

class BoxBasicBuilder : public BorderBuilder
{
public:

    using item_type = BoxItem;
    using item_ptr = std::shared_ptr<item_type>;
    using item_ary = std::vector<item_ptr>;


    BoxBasicBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
        : BorderBuilder(window, point, str)
    {
    }

    BoxBasicBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
        : BorderBuilder(window, point, str)
    {
    }

    virtual ~BoxBasicBuilder() = default;

    BoxBasicBuilder* addItem(const std::string& str)
    {
        m_items.emplace_back(std::make_shared<item_type>(BoxBasicItemBuilder{ m_basic.window, str }));
        return this;
    }

    BoxBasicBuilder* addItem(std::string&& str)
    {
        m_items.emplace_back(std::make_shared<item_type>(BoxBasicItemBuilder{ m_basic.window, str }));
        return this;
    }

    BoxBasicBuilder* addItem(const BoxBasicItemBuilder& item)
    {
        m_items.emplace_back(std::make_shared<item_type>(const_cast<BoxBasicItemBuilder&>(item)));
        return this;
    }

    BoxBasicBuilder* addItem(BoxBasicItemBuilder&& item)
    {
        m_items.emplace_back(std::make_shared<item_type>(item));
        return this;
    }

    const item_ary& getItems() const noexcept
    {
        return m_items;


    }
    virtual Control::control_ptr build() = 0;

private:

    item_ary m_items;

};

}

#endif //UICLASSEXAMPLE_BOXBASIC_H
