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
    BoxItem() = default;

    BoxItem(const BoxItem& item)
    {
        if (this == &item) {
            return;
        }
        this->color = item.color;
        this->idx = item.idx;
        this->font = item.font;
    }

    virtual ~BoxItem() = default;

    virtual const std::string& getString()
    {
        if (!caching) {
            setOriginString(origin);
            caching = true;
        }
        return origin;
    }

    size_t getIdx() const
    {
        return idx;
    }

    void setIdx(size_t idx)
    {
        caching = false;
        BoxItem::idx = idx;
    }

    const SEG_Color& getColor() const
    {
        return color;
    }

    void setColor(const SEG_Color& color)
    {
        caching = false;
        BoxItem::color = color;
    }

    const SEG_TFont& getFont() const
    {
        return font;
    }

    void setFont(const SEG_TFont& font)
    {
        caching = false;
        BoxItem::font = font;
    }

    virtual void setOriginString(std::string& _origin) = 0;

protected:
    bool caching = false;

private:
    mutable std::string origin{100};
    std::size_t idx;
    SEG_Color color = {ColorCode::black};
    SEG_TFont font;

};

class BoxBasic : public Border
{
public:
    using item_type = BoxItem;
    using item_ptr = std::shared_ptr<item_type>;

    void appendItem(const item_ptr item)
    {
        m_items.push_back(item);
    }

    item_ptr at(const size_t index)
    {
        assert(m_items.size() > index);
        return m_items.at(index);
    }

    inline t_size getMenuCount() const noexcept
    { return m_items.size(); }

    inline size_t getVisibleMenuMax() const noexcept
    { return m_visibleMenuCnt; }

    inline void setVisibleMenuMax(const size_t cnt)
    { m_visibleMenuCnt = cnt; }

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

    inline std::vector<item_ptr>& getItems()
    {
        return m_items;
    }

    inline void setItems(const std::vector<item_ptr>& mItems)
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

protected:

    BoxBasic(ControlBuilder& bld);

    virtual ~BoxBasic();

    virtual void initialize() override;


private:
    const t_size MENU_GAP = 3;

    size_t m_visibleMenuCnt = 3;
    std::vector<item_ptr> m_items;
    t_size m_menuHeight = 0;
    size_t m_menuStartIdx = 0;
    int m_selectedMenuIdx = -1;
    int m_boundedMenuIndx = -1;
    bool m_folded = true;

};

}

#endif //UICLASSEXAMPLE_BOXBASIC_H
