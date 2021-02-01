//
// Created by chaed on 19. 3. 8.
//

#include "ComboBox.h"
#include "include/SEG_Drawer.h"
#include "Decorator/ScrollrableDecorator.h"
#include "GameInterface/include/Logger.h"
#include "SEG_Helper.h"

using namespace seg;

ComboBox::ComboBox(ComoboBoxBuilder& bld)
        : BoxBasic(bld)
{
    bld.kind(ControlKind::ComboBox);
    setVisibleMenuCount(3);
}

void ComboBox::initialize()
{
    m_defaultHeight = getHeight();
    Base::initialize();
}

void ComboBox::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
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

    Base::onMouseButtonEvent(button);
}

void ComboBox::onDraw()
{
    auto renderer = getRenderer();

    if (!getItems().empty()) {

        //const auto idx = getSelectedMenuIndex() >= getItems().size() ? getItems().size() - 1 : getSelectedMenuIndex();
        //setSelectedMenuIndex(idx);

        if (isFolded() == false) {
            auto idxfair = getvisibleMenuIndexRange();
            for (t_size i = idxfair.first; i < idxfair.second ; i++) 
            {
                getItem(i)->getTextDrawer()->drawText();
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

    Base::foldBox();
}

void ComboBox::unfoldBox()
{
    size_t menuMax = getItems().size() < getVisibleMenuCount() ? getVisibleMenuCount() : getItems().size();
    setHeight(getHeight() * menuMax);

    if (getVisibleMenuCount() < getItems().size()) {
        auto dec = DecoratorMap<ScrollrableDecorator, ComboBox>::get_decorator(this);
        event::EventPusher event {getSEGWindow()->getWindowID(), SEG_CONTROLLER, SEG_DECORATOR_ATTACH};
        event.setTargetId(getId());
        event.setUserData(dec);
        event.pushEvent();
    }

    Base::unfoldBox();
}

