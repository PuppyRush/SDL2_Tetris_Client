//
// Created by chaed on 19. 4. 21.
//

#ifndef SDL2EASYGUI_BOXBASIC_H
#define SDL2EASYGUI_BOXBASIC_H

#include <vector>

#include "SDL2EasyGUI/include/SEG_Drawer.h"
#include "../Border.h"

namespace seg {

struct BoxItem
{
    using string_type = std::string;
    using textDrawer_type = std::shared_ptr<drawer::TextDrawer>;

    //BoxItem() = default;

    BoxItem(const string_type& str)
    {   
        setBoxString(str);
    }

    BoxItem(const BoxItem& item)
    {
        if (this == &item) {
            return;
        }
        this->setBoxString(item.getBoxString());
        this->setFont(item.getFont());
        this->setIndex(item.getIndex());
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

    void setBoxString(const string_type& str)
    {
        m_textDrawer->setText(str);
    }

    void setBoxString(string_type&& str)
    {
        m_textDrawer->setText(str);
    }

    string_type getBoxString() const noexcept
    {
        return m_textDrawer->getText();
    }

    size_t getIndex() const noexcept
    {
        return m_idx;
    }

    void setIndex(size_t i)
    {
        //caching = false;
        this->m_idx = i;
    }

    const SEG_Color& getColor() const noexcept
    {
        return m_textDrawer->getColor();
    }

    void setColor(const SEG_Color& color)
    {
       // caching = false;
        m_textDrawer->setColor(color);
    }

    const std::string getFontName() const noexcept
    {
        return m_textDrawer->getFontName();
    }

    void setFontName(const std::string& str)
    {
        m_textDrawer->setFontName(str);
    }

    SEG_TFont getFont() const noexcept
    {
        m_textDrawer->getFont();
    }

    void setFont(SEG_TFont font)
    {
       // caching = false;
        m_textDrawer->setFont(font);
    }

    void setTextPosition(const SDL_Rect rect)
    {
        m_textDrawer->setPosition(rect);
    }

    inline SDL_Rect getTextPosition() const noexcept
    {
        return m_textDrawer->getPosition();
    }

    void setPosition(const SDL_Rect rect)
    {
        m_position = rect;
    }

    inline SDL_Rect getPosition() const noexcept
    {
        return m_position;
    }

    void setTextDrawer(textDrawer_type drawerPtr)
    {
        m_textDrawer = drawerPtr;
    }

    auto getTextDrawer()
    {
        return m_textDrawer;
    }

   // virtual void setOriginString(std::string& _origin) = 0;

protected:
    //bool caching = false;

private:
    //mutable string_type string{50};
    std::size_t m_idx;
    SDL_Rect m_position;
    textDrawer_type m_textDrawer;
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

    virtual void appendItem(item_ptr item);
    
    virtual void appendItem(const string_type& str);


    item_ptr at(const size_t index)
    {
        assert(m_items.size() > index);
        return m_items.at(index);
    }

    inline t_size getMenuCount() const noexcept
    { return m_items.size(); }

    void removeAll() noexcept;

    t_size calcIndexOf(const t_coord y);

    std::string getSelectedText();

    bool isFolded() const noexcept
    { return m_folded; }

    void setFolded(const bool fold) noexcept
    { m_folded = fold; }

    inline const t_size getMenuGap() const noexcept
    {
        return MENU_GAP;
    }

    inline t_size getVisibleMenuWidth() const noexcept
    {
        return m_visibleMenuWidth;
    }

    inline void setVisibleMenuWidth(t_size w)
    {
        m_visibleMenuWidth = w;

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

    item_ptr getItem(const size_t idx)
    {
        return m_items.at(idx);
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

    inline t_size getSelectedMenuIndex() const noexcept
    {
        return m_selectedMenuIdx;
    }

    inline void setSelectedMenuIndex(t_size mSelectedMenuIdx)
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

    virtual void initialize() override;

    t_size getFittedTextSize(const size_t idx);

protected:

    BoxBasic(BoxBasicBuilder& bld);

    virtual ~BoxBasic();


    virtual void foldBox()
    {}
    
    virtual void unfoldBox()
    {}

    void autoFitBox(const size_t idx);

    std::pair<t_size, t_size> getvisibleMenuIndexRange();

private:

    void recalculateBoxesPosition();

private:
    const t_size MENU_GAP = 3;

    t_size m_visibleMenuCnt = 3;
    std::vector<item_ptr> m_items;
    t_size m_menuHeight = 0;
    t_size m_menuStartIdx = 0;
    t_size m_selectedMenuIdx = 0;
    t_size m_boundedMenuIndx = INVALID_SIZE;
    t_size m_visibleMenuWidth = 0;
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
