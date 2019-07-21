//
// Created by chaed on 19. 3. 8.
//

#include "ComboBox.h"

using namespace sdleasygui;

ComboBox::ComboBox(ComoboBoxBuilder& bld)
        : BoxBasic(bld)
{
    bld.kind(ControllerKind::ComboBox);
}

void ComboBox::initialize()
{
    m_defaultHeight = m_data->height;
    BoxBasic::initialize();
}

void ComboBox::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->button == SDL_BUTTON_LEFT && isHit(button->x, button->y)) {

        m_folded = !m_folded;

        if (m_folded) {

            int test_idx = (button->y - m_data->point.y) / (m_menuHeight + MENU_GAP);
            if ((test_idx + m_menuStartIdx) < m_items.size()) {
                m_selectedMenuIdx = test_idx;
            }

            m_data->height = m_defaultHeight;
        } else {
            size_t menuMax = m_items.size() < MENU_MAX ? MENU_MAX : m_items.size();
            m_data->height *= menuMax;
        }

    }
}

void ComboBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    if (!m_items.empty()) {

        m_selectedMenuIdx = m_selectedMenuIdx >= m_items.size() ? m_items.size() - 1 : m_selectedMenuIdx;

        if (m_folded) {

            auto& item = *m_items.at(m_selectedMenuIdx);
            auto point = getPoint();
            point.x += 5;

            TextDrawer textDrawer{renderer, getFont(), point, item.getString()};
            textDrawer.drawText();

        } else {
            int idx = m_items.size() < m_menuStartIdx ? m_items.size() - 1 : m_menuStartIdx;
            idx -= MENU_MAX;
            idx = idx < 0 ? 0 : idx;

            auto point = getPoint();
            point.x += 5;

            for (; idx < m_items.size(); idx++) {
                TextDrawer textDrawer{renderer, getFont(), point, m_items.at(idx)->getString()};
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
    if (m_folded) {
    } else {

    }

    BoxBasic::onDrawBackground();
}