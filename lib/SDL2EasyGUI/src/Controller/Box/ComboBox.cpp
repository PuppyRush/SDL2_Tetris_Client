//
// Created by chaed on 19. 3. 8.
//

#include "ComboBox.h"
#include "include/SEG_Drawer.h"
#include "SDL2EasyGUI/src/Decorator/ScrollrableDecorator.h"

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
    BoxBasic::initialize();
}

void ComboBox::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT && isHit(button->x, button->y)) {

        setFolded(!isFolded());

        if (isFolded()) {

            //펼쳐진 상태에서 최 상단 메뉴는 선택된 메뉴만 보여줘야 한다.
            setSelectedMenuIndex(calcIndexOf(button->y));

            setHeight(m_defaultHeight);

            event::EventPusher event{getWindow()->getWindowID(), getId(), SEG_DECORATOR_DETACH};
            event.setUserData(this);
            event.pushEvent();

        } else {
            size_t menuMax = getItems().size() < getVisibleMenuCount() ? getVisibleMenuCount() : getItems().size();
            setHeight(getHeight() * menuMax);

            if (getVisibleMenuCount() < getItems().size()) {
                auto dec = new ScrollrableDecorator(this);
                event::EventPusher event{getWindow()->getWindowID(), getId(), SEG_DECORATOR_ATTACH};
                event.setUserData(dec);
                event.pushEvent();
            }
        }

    }
}

void ComboBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    if (!getItems().empty()) {

        const auto idx = getSelectedMenuIndex() >= getItems().size() ? getItems().size() - 1 : getSelectedMenuIndex();
        setSelectedMenuIndex(idx);

        if (isFolded()) {

            auto& item = *getItems().at(getSelectedMenuIndex());
            auto point = getPoint();
            point.x += 5;

            drawer::TextDrawer textDrawer{renderer, getFont(), point, item.getString()};
            textDrawer.drawText();

        } else {

            auto point = getPoint();
            point.x += 5;

            drawer::TextDrawer textDrawer{renderer, getFont(), point, getItems().at(getSelectedMenuIndex())->getString()};
            textDrawer.drawText();

            point.y += textDrawer.getTextHeight() + getMenuGap();

            const int endIdx =
                    (getMenuStartIndex() + getVisibleMenuCount()) > getItems().size() ? getItems().size() :
                    getMenuStartIndex() +
                    getVisibleMenuCount();
            for (int i = getMenuStartIndex(); i < endIdx; i++) {
                drawer::TextDrawer textDrawer{renderer, getFont(), point, getItems().at(i)->getString()};
                textDrawer.drawText();

                point.y += textDrawer.getTextHeight() + getMenuGap();

                setMenuHeight(textDrawer.getTextHeight());
            }

            //Draw Chosed focus
            drawer::drawThickLine(renderer, {getPoint().x, getPoint().y + getMenuHeight()},
                                       {getPoint().x + getWidth(), getPoint().y + getMenuHeight()}, ColorCode::cyan, 4);

        }
    }

    BoxBasic::onDraw();
}

void ComboBox::onDrawBackground()
{
    BoxBasic::onDrawBackground();
}