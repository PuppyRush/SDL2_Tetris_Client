//
// Created by chaed on 19. 3. 8.
//

#include "ComboBox.h"
#include "include/SEG_Drawer.h"
#include "Decorator/ScrollrableDecorator.h"
#include "GameInterface/include/Logger.h"
#include "SEG_Helper.h"

using namespace seg;





ComboBox::ComboBox(ComboBoxBuilder& bld)
        : BoxBasic(bld)
{

    bld.kind(ControlKind::ComboBox);
    setVisibleMenuCount(3);
}

void ComboBox::initialize()
{
    if (getItems().empty())
    {
        setControlTextHeight(getMenuHeight());
        setControlTextWidth(getWidth());
    }

    m_defaultHeight = getHeight();
    recalculateBoxesPosition();
    Base::initialize();
}

void ComboBox::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (!isFolded()) {

        m_boundedMenuIndex = calcIndexOf(motion->y);
    }
    Base::onMouseMotionEvent(motion);
}

void ComboBox::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
    if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT && isHit({ static_cast<t_coord>( button->x),static_cast<t_coord>(button->y) })) {

        setFolded(isFolded() ? false : true );

        if (isFolded()) {
            //펼쳐진 상태에서 최 상단 메뉴는 선택된 메뉴만 보여줘야 한다.
            if (auto idx = calcIndexOf(button->y) ;
                idx != INVALID_SIZE)
            {
                setSelectedMenuIndex(idx);
            }
            setControlText(getSelectedText());
            setControlTextWidth(getFittedTextSize(getSelectedMenuIndex()));
            foldBox();
        } else {
            unfoldBox();
        }

    }

    Base::onMouseButtonDownEvent(button);
}


void ComboBox::onDraw()
{
    auto renderer = getRenderer();

    if (!getItems().empty()) {

        if (isFolded() == false) {
            auto idxfair = getvisibleMenuIndexRange();
            for (t_size i = idxfair.first; i < idxfair.second ; i++) 
            {
                getItem(i)->onDraw();
            }

            //Draw Chosed focus
            drawer::drawThickLine(renderer, {getPoint().x, getPoint().y + getMenuHeight()},
                                       {getPoint().x + getWidth(), getPoint().y + getMenuHeight()}, ColorCode::lightgray, 3);
        }
    }

    Base::onDraw();
}

void ComboBox::onDrawBackground()
{
    Base::onDrawBackground();
}

void ComboBox::onDetachFocus(const SDL_UserEvent* user)
{
    if (isFolded() == false)
    {
        setFolded(true);
        foldBox();
    }
    Base::onDetachFocus(user);
}

void ComboBox::foldBox()
{
    setHeight(m_defaultHeight);

    event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_DECORATOR_DETACH};
    event.setTargetId(getId());
    event.setUserData(this);
    event.pushEvent();
}

void ComboBox::unfoldBox()
{
    size_t menuMax = getItems().size() > getVisibleMenuCount() ? getVisibleMenuCount() : getItems().size();
    setHeight( getHeight() + (getMenuHeight()* menuMax) + 5 );

    if (getVisibleMenuCount() < getItems().size()) {
        auto dec = DecoratorMap<ScrollrableDecorator, ComboBox>::get_decorator(this);
        event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_DECORATOR_ATTACH};
        event.setTargetId(getId());
        event.setUserData(dec);
        event.pushEvent();
    }
}


void ComboBox::removeAll() noexcept
{
    m_items.clear();
}

std::string ComboBox::getSelectedText()
{
    if (m_items.size() <= m_selectedMenuIndex) {
        throw std::out_of_range{ "" };
    }

    return m_items.at(m_selectedMenuIndex)->getControlText();
}

t_size ComboBox::calcIndexOf(const t_coord y)
{
    const size_t menuHeight = getMenuHeight() + MENU_GAP;

    int test_idx = (y - getPoint().y - menuHeight) / (menuHeight);
    if (test_idx >= getVisibleMenuCount())
    {
        return INVALID_SIZE;
    }

    if ((test_idx + getBoxStartIndex()) < m_items.size()) {
        return test_idx + getBoxStartIndex();
    }

    return INVALID_SIZE;
}


//박스에 표시될 글씨의 적절한 크기를 반환한다.
t_size ComboBox::getFittedTextSize(const size_t idx)
{
    if (getBoxCount() <= idx)
    {
        throw std::out_of_range{ "" };
        return 0;
    }

    if (getControlTextWidth() < getVisibleMenuWidth())
    {
        return getControlTextWidth();
    }
    else
    {
        return getVisibleMenuWidth();
    }

}
