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

void ComboBox::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if ((button->button == SDL_BUTTON_LEFT) && !m_items.empty()) {
        m_folded = false;
    }

}

void ComboBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    SEG_Point accuPoint = getPoint();

    if (!m_items.empty()) {
        const auto& item = *m_items.begin();

        TextDrawer textDrawer{renderer, getFont(), item->getString()};
        auto textSurface = textDrawer.getTextSurface();

        if (textSurface != nullptr) {
            auto texture = textDrawer.getTexture();
            const double text_width = static_cast<double>(textSurface->w);
            const double text_height = static_cast<double>(textSurface->h);

            const auto point = getPoint();
            SDL_Rect renderQuad =
                    {static_cast<int>(accuPoint.x + 5), static_cast<int>(accuPoint.y), static_cast<int>(text_width),
                     static_cast<int>(text_height)};
            SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

            accuPoint.y += text_height + 3;
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