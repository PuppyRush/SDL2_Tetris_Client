//
// Created by chaed on 18. 12. 18.
//

#include "TOptionDisplay.h"

SDL_TETRIS



void TOptionDisplay::_draw()
{

}
void TOptionDisplay::_event()
{

}

std::shared_ptr<TDisplayInterface> TOptionDisplay::getInstance()
{
//boost::serialization::singleton<TMainLocalDisplay>::get_mutable_instance();
    static std::shared_ptr<TDisplayInterface> inst = std::shared_ptr<TDisplayInterface>(new TOptionDisplay{});
    return inst;
}

