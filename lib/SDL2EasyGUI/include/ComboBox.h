//
// Created by chaed on 19. 3. 8.
//

#ifndef SDL2EASYGUI_COMBOBOX_H
#define SDL2EASYGUI_COMBOBOX_H

#include "SDL2EasyGUI/src/Control/Box/BoxBasic.h"

namespace seg {

class BoxItemBuilder : public BoxBasicItemBuilder
{
public:

    virtual ~BoxItemBuilder() = default;

    BoxItemBuilder(const GraphicInterface::window_type window, const std::string& str)
        : BoxBasicItemBuilder(window, str)
    {
        text(str);
        id(atomic::getUniqueId());
    }

    BoxItemBuilder(const GraphicInterface::window_type window, std::string&& str)
        : BoxBasicItemBuilder(window, str)
    {
        text(str);
        id(atomic::getUniqueId());
    }

    virtual inline BoxItemBuilder* backgroundColor(ColorCode color) noexcept
    {
        m_basic.backgroundColor = color;
        return this;
    }

    virtual inline BoxItemBuilder* enabled(bool enable) noexcept
    {
        m_basic.enabled = enable;
        return this;
    }


    virtual Control::control_ptr build()
    {
        return new BoxItem(*this);
    }

};
/////



class ComboBoxBuilder;
class ComboBox : public BoxBasic
{
public:
    using Base = BoxBasic;
    using item_type = BoxItem;
    using string_type = std::string;
    using item_ptr = std::shared_ptr<item_type>;
    using item_ary = std::vector<item_ptr>;

    ComboBox(ComboBoxBuilder& bld);

    virtual ~ComboBox() = default;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onDraw() override;

    void onDrawBackground();

    virtual void initialize() override;

    virtual void onDetachFocus(const SDL_UserEvent* user) override;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;


    inline t_size getSelectedMenuIndex() const noexcept
    {
        return m_selectedMenuIndex;
    }

    inline void setSelectedMenuIndex(t_size mSelectedMenuIdx)
    {
        m_selectedMenuIndex = mSelectedMenuIdx;
    }

    inline int getBoundedMenuIndex() const noexcept
    {
        return m_boundedMenuIndex;
    }

    inline void setBoundedMenuIndex(int mBoundedMenuIndx)
    {
        m_boundedMenuIndex = mBoundedMenuIndx;
    }



    void removeAll() noexcept;

    t_size calcIndexOf(const t_coord y);

    std::string getSelectedText();

    bool isFolded() const noexcept
    {
        return m_folded;
    }

    void setFolded(const bool fold) noexcept
    {
        m_folded = fold;
    }

    inline const t_size getMenuGap() const noexcept
    {
        return MENU_GAP;
    }


    t_size getFittedTextSize(const size_t idx);

protected:

    virtual void foldBox();

    virtual void unfoldBox();



private:

    

    bool isBoundInMenues();

private:
    t_size m_selectedMenuIndex = 0;
    t_size m_boundedMenuIndex = INVALID_SIZE;
    t_size m_defaultHeight;

    bool m_folded = true;
    const t_size MENU_GAP = 3;

};

class ComboBoxBuilder : public BoxBasicBuilder
{
public:


    virtual ~ComboBoxBuilder() = default;

    ComboBoxBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    ComboBoxBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    virtual Control::control_ptr build() final
    {
        return new ComboBox(*this);
    }
    
private:

};

}

#endif //SDL2EASYGUI_COMBOBOX_H
