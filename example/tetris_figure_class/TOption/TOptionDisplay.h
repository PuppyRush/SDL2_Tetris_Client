//
// Created by chaed on 18. 12. 18.
//

#ifndef TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
#define TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H

#include "../TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TOptionDisplay final: public TDisplayInterface
{
public:
    enum class UIResource : t_type
    {
        Suspend,
        End
    };

    virtual bool clickedBack(const TDisplay disply) override { return false; }

    static std::shared_ptr<TDisplayInterface> getInstance();

private:

    virtual void _preInitialize() final;
    virtual void _event(const SDL_Event* event) final;
    virtual void _timer() final;
    virtual void _draw() final;

};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
