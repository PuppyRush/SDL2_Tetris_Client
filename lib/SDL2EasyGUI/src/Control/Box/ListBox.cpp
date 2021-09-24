//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"
#include "include/SEG_Drawer.h"

using namespace seg;

ListBox::ListBox(ListBoxBuilder& bld)
        : BoxBasic(bld)
{
    setScrollHorizenActivating(bld.getScrollHorizen());
    setScrollVerticalActivating(bld.getScrollVertical());
    
    bld.kind(ControlKind::ListBox);

    size_t choosenCount = 1;
    if (getItemCount() > countComponent())
    {
        choosenCount = countComponent();
    }
    else
    {
        choosenCount = getItemCount();
    }

    Base::setControlText("");
}

void ListBox::setControlText(const char* ch)
{
    //nothing to do, dont call base fn
}


void ListBox::setControlText(std::string&& str)
{
    //nothing to do, dont call base fn
}


void ListBox::setControlText(const std::string& str)
{
    //nothing to do, dont call base fn
}


void ListBox::initialize()
{
    /*auto mng = _getBoxItemManager();
    const auto end = mng.end();
    int i = 0;
    for(auto it = mng.begin() ; it != end ; it++)
    {
        (*it)->setPosition(mng.calculatePosition(i));
        i++;
    }*/

    Base::initialize();
}


void ListBox::onDraw()
{
    Base::onDraw();
}


void ListBox::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    setBoundedMenuIndex( _calcIndexOf(motion->y));
    Base::onMouseMotionEvent(motion);
}


t_size ListBox::_calcIndexOf(const t_coord y)
{
    const size_t menuHeight = getMenuHeight() + MENU_GAP;

    int test_idx = (y - getPoint().y ) / (menuHeight);
    if (test_idx >= getVisibleMenuCount())
    {
        return INVALID_SIZE;
    }

    if ((test_idx + getBoxStartIndex()) < countComponent()) {
        return test_idx + getBoxStartIndex();
    }

    return INVALID_SIZE;

}

