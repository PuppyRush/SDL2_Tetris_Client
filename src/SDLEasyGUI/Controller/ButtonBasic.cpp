//
// Created by chaed on 18. 12. 27.
//

#include "ButtonBasic.h"

ButtonBasic::ButtonBasic(const ControllBuilder& bld, const TControllKind kind)
    :Controll(bld,kind)
{


}

void ButtonBasic::onDraw()
{
    _drawCarot();
    Controll::onDraw();
}


void ButtonBasic::_drawCarot()
{
    auto renderer = getWindow()->getSDLRenderer().get();

    if(isSelected() && isCarot())
    {
        if( GroupControllManager::getInstance()->isSelected(getGroup(), getId()))
        {
            SDL_Rect rect{getPoint().x-5, getPoint().y-5, getWidth()+10, getHeight()+10};

            const auto& linecolor = TColor::getColor(TColorCode::red);
            SDL_SetRenderDrawColor(renderer, linecolor.r, linecolor.g, linecolor.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
