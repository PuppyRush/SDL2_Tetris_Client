//
// Created by chaed on 19. 4. 21.
//

#ifndef UICLASSEXAMPLE_BOXBASIC_H
#define UICLASSEXAMPLE_BOXBASIC_H

#include <vector>

#include "../Border.h"

namespace seg {

struct BoxItem
{
    using string_type = std::string;

    BoxItem() = default;

    BoxItem(const string_type& str)
        :string(str)
    {

    }


    BoxItem(const BoxItem& item)
    {
        if (this == &item) {
            return;
        }
        this->string = item.string;
        this->color = item.color;
        this->idx = item.idx;
        this->font = item.font;
    }

    virtual ~BoxItem() = default;

    /*virtual const std::string& getLabelString()
    {
        if (!caching) {
            setOriginString(origin);
            caching = true;
        }
        return origin;
    }*/

    void setString(const string_type& str)
    {
        string = str;
    }

    void setString(string_type&& str)
    {
        string = str;
    }

    string_type getString()
    {
        return string;
    }

    size_t getIdx() const
    {
        return idx;
    }

    void setIdx(size_t idx)
    {
        //caching = false;
        BoxItem::idx = idx;
    }

    const SEG_Color& getColor() const
    {
        return color;
    }

    void setColor(const SEG_Color& color)
    {
       // caching = false;
        this->color = color;
    }

    const SEG_TFont& getFont() const
    {
        return font;
    }

    void setFont(const SEG_TFont& font)
    {
       // caching = false;
        this->font = font;
    }

   // virtual void setOriginString(std::string& _origin) = 0;

protected:
    //bool caching = false;

private:
    mutable string_type string{50};
    std::size_t idx;
    SEG_Color color = {ColorCode::black};
    SEG_TFont font;

};

class BoxBasicBuilder;
class BoxBasic : public Border
{
public:

    using Base = Border;
    using item_type = BoxItem;
    using string_type = item_type::string_type;
    using item_ptr = std::shared_ptr<item_type>;
    using item_ary = std::vector<item_ptr>;

    void appendItem(item_ptr item)
    {
        m_items.emplace_back(item);
    }
    
    void appendItem(const string_type& str)
    {
        m_items.push_back(std::make_shared<item_type>(str));
    }


    item_ptr at(const size_t index)
    {
        assert(m_items.size() > index);
        return m_items.at(index);
    }

    inline t_size getMenuCount() const noexcept
    { return m_items.size(); }

    void removeAll() noexcept;

    int calcIndexOf(const t_coord y);

    std::string getSelectedText();

    bool isFolded() const noexcept
    { return m_folded; }

    void setFolded(const bool fold) noexcept
    { m_folded = fold; }

    inline const t_size getMenuGap() const noexcept
    {
        return MENU_GAP;
    }

    inline size_t getVisibleMenuCount() const noexcept
    {
        return m_visibleMenuCnt;
    }

    inline void setVisibleMenuCount(size_t mVisibleMenuCnt)
    {
        m_visibleMenuCnt = mVisibleMenuCnt;
    }

    inline item_ary& getItems()
    {
        return m_items;
    }

    inline void setItems(const item_ary& mItems)
    {
        m_items = mItems;
    }

    inline t_size getMenuHeight() const noexcept
    {
        return m_menuHeight;
    }

    inline void setMenuHeight(t_size mMenuHeight)
    {
        m_menuHeight = mMenuHeight;
    }

    inline size_t getMenuStartIndex() const noexcept
    {
        return m_menuStartIdx;
    }

    inline void setMenuStartIndex(int mMenuStartIdx)
    {
        if(mMenuStartIdx < 0)
        {
            mMenuStartIdx = 0;
        }
        else if(mMenuStartIdx > (m_items.size() - m_visibleMenuCnt) )
        {
            mMenuStartIdx = m_items.size() - m_visibleMenuCnt;
        }
        m_menuStartIdx = mMenuStartIdx;
    }

    inline int getSelectedMenuIndex() const noexcept
    {
        return m_selectedMenuIdx;
    }

    inline void setSelectedMenuIndex(int mSelectedMenuIdx)
    {
        m_selectedMenuIdx = mSelectedMenuIdx;
    }

    inline int getBoundedMenuIndex() const noexcept
    {
        return m_boundedMenuIndx;
    }

    inline void setBoundedMenuIndex(int mBoundedMenuIndx)
    {
        m_boundedMenuIndx = mBoundedMenuIndx;
    }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    void onDrawBackground();

    virtual void onDraw() override;

    virtual bool bound(const SDL_Event& event) override
    {
        return Base::bound(event);
    }

    virtual bool focus(const SDL_Event& event) override
    {
        return Base::focus(event);
    }

    virtual void onDetachFocus(const SDL_UserEvent* user) override;


protected:

    BoxBasic(BoxBasicBuilder& bld);

    virtual ~BoxBasic();

    virtual void initialize() override;

    std::pair<t_size, t_size> getVisibleRangeIndex() const;

    virtual void foldBox()
    {}
    
    virtual void unfoldBox()
    {}

private:
    const t_size MENU_GAP = 3;

    t_size m_visibleMenuCnt = 3;
    std::vector<item_ptr> m_items;
    t_size m_menuHeight = 0;
    t_size m_menuStartIdx = 0;
    t_size m_selectedMenuIdx = INVALID_VALUE;
    t_size m_boundedMenuIndx = INVALID_VALUE;
    bool m_folded = true;
    
};

class BoxBasicBuilder : public BorderBuilder
{
public:

    using item_type = BoxBasic::item_type;
    using string_type = item_type::string_type;
    using item_ptr = std::shared_ptr<item_type>;
    using item_ary = std::vector<item_ptr>;

    virtual ~BoxBasicBuilder() = default;

    BoxBasicBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
        : BorderBuilder(window, point, str)
    {
    }

    BoxBasicBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
        : BorderBuilder(window, point, str)
    {
    }

    BoxBasicBuilder* appendItem(string_type&& str)
    {
        m_items.push_back(std::make_shared<item_type>(str));
        return this;
    }

    BoxBasicBuilder* appendItem(const string_type& str)
    {
        m_items.push_back(std::make_shared<item_type>(str));
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
