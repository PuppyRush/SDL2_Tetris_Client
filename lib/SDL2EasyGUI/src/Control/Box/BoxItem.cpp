#include "BoxItem.h"

using namespace seg;


BoxItem::BoxItem(const BoxItemBuilder& bld)
    : Control(bld)
{
}

BoxItem::BoxItem(BoxItemBuilder&& bld)
    :Control(bld)
{

}

void BoxItem::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (isHit(make_segpoint(motion->x, motion->y)))
    {
        SEG_Color color{ ColorCode::blue };
        auto rnd = getRenderer();

        SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(rnd, color.r, color.g, color.b, 128);
        SDL_RenderFillRect(rnd, &getConstPosition());
        SDL_RenderDrawRect(rnd, &getConstPosition());
        SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
        refresh();
    }

    Base::onMouseMotionEvent(motion);
}

void BoxItem::onDraw()
{
    if (isVisible() == false)
    {
        return;
    }

    Base::onDraw();
}
