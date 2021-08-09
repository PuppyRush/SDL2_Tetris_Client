//
// Created by chaed on 19. 2. 16.
//

#ifndef SDL2EASYGUI_LIST_H
#define SDL2EASYGUI_LIST_H

#include <vector>

#include "SDL2EasyGUI/src/Control/Box/BoxBasic.h"

namespace seg {

enum class ListBoxTypes : t_type
{
    multiclicked,
    editable,
    clickable,
};

enum class ListBoxScrollType : t_type
{
    vertical,
    horizen,
    both
};

class ListBoxBuilder;



class ListBox : public BoxBasic
{
public:

    using Base = BoxBasic;

    explicit ListBox(ListBoxBuilder& bld);

    virtual ~ListBox() = default;



    inline bool isScrollHorizenActivating() const noexcept
    {
        return m_scrollHorizen;
    }

    inline void setScrollHorizenActivating(bool b) noexcept
    {
        m_scrollHorizen = b;
    }

    inline bool isScrollVerticalActivating() const noexcept
    {
        return m_scrollVertical;
    }

    inline void setScrollVerticalActivating(bool b) noexcept
    {
        m_scrollVertical = b;
    }

    void setItemCount(size_t count)
    {
        m_itemCount = count;
    }

    size_t getItemCount() const noexcept
    {
        return m_itemCount;
    }

    virtual void setControlText(const char* ch);

    virtual void setControlText(std::string&& str);

    virtual void setControlText(const std::string& str);

    virtual void initialize();

    virtual void onDraw() override;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

protected:

    virtual t_size _calcIndexOf(const t_coord y) override;

private:
    bool m_scrollVertical = true;
    bool m_scrollHorizen = false;
    size_t m_itemCount = 3;
};

class ListBoxBuilder : public BoxBasicBuilder
{
public:

    friend class ListBox;

    virtual ~ListBoxBuilder() = default;

    ListBoxBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    ListBoxBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BoxBasicBuilder(window, point, str)
    {
    }

    ListBoxBuilder* scrollHorizen(bool b)
    {
        m_scrollHorizen = b;
        return this;
    }

    ListBoxBuilder* scrollVertical(bool b)
    {
        m_scrollVertical = b;
        return this;
    }

    virtual Control::control_ptr build() final
    {
        return new ListBox(*this);
    }

private:
    bool m_scrollHorizen = false;
    bool m_scrollVertical = true;
};

}

#endif //SDL2EASYGUI_LIST_H
