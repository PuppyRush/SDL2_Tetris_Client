//
// Created by chaed on 19. 4. 21.
//

#ifndef UICLASSEXAMPLE_BOXBASIC_H
#define UICLASSEXAMPLE_BOXBASIC_H

#include <vector>

#include "../Border.h"

namespace sdleasygui {

struct BoxItem
{
    BoxItem() = default;

    BoxItem(const BoxItem& item)
    {
        if (this == &item) {
            return;
        }
        this->color = item.color;
        this->idx = item.idx;
        this->font = item.font;
    }

    virtual ~BoxItem() = default;

    const std::string& getString()
    {
        if (!caching) {
            setOriginString(origin);
            caching = true;
        }
        return origin;
    }

    size_t getIdx() const
    {
        return idx;
    }

    void setIdx(size_t idx)
    {
        caching = false;
        BoxItem::idx = idx;
    }

    const TColor& getColor() const
    {
        return color;
    }

    void setColor(const TColor& color)
    {
        caching = false;
        BoxItem::color = color;
    }

    const TFont& getFont() const
    {
        return font;
    }

    void setFont(const TFont& font)
    {
        caching = false;
        BoxItem::font = font;
    }

    virtual void setOriginString(std::string& _origin) = 0;

protected:
    bool caching = false;

private:
    mutable std::string origin{100};
    std::size_t idx;
    TColor color = {ColorCode::black};
    TFont font;

};

class BoxBasic : public Border
{
public:
    using item_type = BoxItem;
    using item_ptr = std::shared_ptr<item_type>;

    void appendItem(const item_ptr item)
    {
        m_items.push_back(item);
    }

    item_ptr at(const size_t index)
    {
        assert(m_items.size() > index);
        return m_items.at(index);
    }

protected:

    BoxBasic(ControllerBuilder& bld);

    virtual ~BoxBasic();


    virtual void onDraw() override;

    virtual void initialize() override
    {
        Border::initialize();
    }

    std::vector<item_ptr> m_items;

};

}

#endif //UICLASSEXAMPLE_BOXBASIC_H
