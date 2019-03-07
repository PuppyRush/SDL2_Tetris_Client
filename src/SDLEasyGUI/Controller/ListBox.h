//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_LIST_H
#define TETRIS_FIGURE_CLASS_LIST_H

#include <vector>

#include "Border.h"

namespace sdleasygui {

enum class ListBoxTypes : t_type {
    multiclicked,
    editable,
    clickable,
};

enum class ListBoxScrollType : t_type {
    vertical,
    horizen,
    both
};

struct ListItem
{
    ListItem() = default;

    ListItem(const ListItem& item)
    {
        if(this == &item)
            return;
        this->color = item.color;
        this->idx = item.idx;
        this->font = item.font;
    }

    virtual const std::string& getString() const noexcept =  0;

    std::size_t idx;
    TColor color;
    TFont font;
};

class ListBoxBuilder;

class ListBox : public Border {
public:

    using item_type = ListItem;
    using item_ptr = std::shared_ptr<item_type>;

    explicit ListBox(ListBoxBuilder& bld);

    void appendItem(const item_ptr item)
    {
        m_items.push_back(item);
    }

    virtual void onDraw() override
    {
        SDL_Rect rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};
        rect.x += getBorderThick();
        rect.y += getBorderThick();
        rect.h = (rect.h - getBorderThick()*2)+1;
        rect.w = (rect.w - getBorderThick()*2)+1;

        drawBackground(rect, getBackgroundColor());
        /////////

        auto renderer = getWindow()->getSDLRenderer().get();

        TPoint accuPoint = getPoint();

        for(const item_ptr item : m_items)
        {
            textDrawer textDrawer{renderer, getFont(), item->getString()};
            auto textSurface = textDrawer.getTextSurface();

            if(textSurface != nullptr)
            {
                auto texture = textDrawer.getTexture();
                const double text_width = static_cast<double>(textSurface->w);
                const double text_height = static_cast<double>(textSurface->h);

                const auto point = getPoint();
                SDL_Rect renderQuad = { static_cast<int>(accuPoint.x +5)
                    , static_cast<int>(accuPoint.y)
                    , static_cast<int>(text_width)
                    , static_cast<int>(text_height) };
                SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

                accuPoint.y += text_height+3;
            }
        }

        Border::onDraw();
    }

    virtual void initialize() override
    {
        Border::initialize();
    }

private:
    std::vector<item_ptr> m_items;

};

class ListBoxBuilder : public BorderBuilder {
public:

    ListBoxBuilder(const GraphicInterface::window_ptr window, const TPoint &point, const std::string &str)
        : BorderBuilder(window, point, str) {
    }

    ListBoxBuilder(const GraphicInterface::window_ptr window, TPoint &&point, std::string &&str)
        : BorderBuilder(window, point, str) {
    }

    virtual std::shared_ptr<Controll> build() final {
        return std::make_shared<ListBox>(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_LIST_H
