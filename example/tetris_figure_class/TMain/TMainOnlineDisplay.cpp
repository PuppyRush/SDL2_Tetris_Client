//
// Created by chaed on 18. 12. 18.
//

#include "TMainOnlineDisplay.h"

SDL_TETRIS


std::shared_ptr<TMainDisplay> TMainOnlineDisplay::getInstance()
{
    //boost::serialization::singleton<TMainLocalDisplay>::get_mutable_instance();
    static std::shared_ptr<TMainDisplay> inst = std::shared_ptr<TMainOnlineDisplay>(new TMainOnlineDisplay{});
    return inst;
}
