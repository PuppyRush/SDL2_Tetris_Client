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
    m_visibleMenuCnt = 3;
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
            m_selectedMenuIdx = calcIndexOf(button->y);

            setHeight(m_defaultHeight);

            EventPusher event{getWindow()->getWindowID(), getResourceId(), SEG_DECORATOR_DETACH};
            event.setUserData(this);
            event.pushEvent();

        } else {
            size_t menuMax = m_items.size() < m_visibleMenuCnt ? m_visibleMenuCnt : m_items.size();
            setHeight(getHeight() * menuMax);

            if (m_visibleMenuCnt < m_items.size()) {
                auto dec = new ScrollrableDecorator(this);
                EventPusher event{getWindow()->getWindowID(), getResourceId(), SEG_DECORATOR_ATTACH};
                event.setUserData(dec);
                event.pushEvent();
            }
        }

    }
}

void ComboBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    if (!m_items.empty()) {

        m_selectedMenuIdx = m_selectedMenuIdx >= m_items.size() ? m_items.size() - 1 : m_selectedMenuIdx;

        if (isFolded()) {

            auto& item = *m_items.at(m_selectedMenuIdx);
            auto point = getPoint();
            point.x += 5;

            TextDrawer textDrawer{renderer, getFont(), point, item.getString()};
            textDrawer.drawText();

        } else {

            auto point = getPoint();
            point.x += 5;

            TextDrawer textDrawer{renderer, getFont(), point, m_items.at(m_selectedMenuIdx)->getString()};
            textDrawer.drawText();

            point.y += textDrawer.getTextHeight() + MENU_GAP;

            const int endIdx =
                    (m_menuStartIdx + m_visibleMenuCnt) > m_items.size() ? m_items.size() : m_menuStartIdx + m_visibleMenuCnt;
            for (int i = m_menuStartIdx; i < endIdx; i++) {
                TextDrawer textDrawer{renderer, getFont(), point, m_items.at(i)->getString()};
                textDrawer.drawText();

                point.y += textDrawer.getTextHeight() + MENU_GAP;

                m_menuHeight = textDrawer.getTextHeight();
            }
        }
    }

    BoxBasic::onDraw();
}

void ComboBox::onDrawBackground()
{
    BoxBasic::onDrawBackground();
}