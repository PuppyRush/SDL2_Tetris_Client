//
// Created by chaed on 18. 12. 18.
//

#ifndef TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
#define TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H

#include "../TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TOptionDisplay : public TDisplayInterface
{
public:
    enum class UIResource : t_type
    {
        Suspend,
        End
    };

    virtual bool clickedBack(const TDisplay disply) override {}

    static std::shared_ptr<TDisplayInterface> getInstance();

private:

    virtual void _event() override;
    virtual void _draw() override;

};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
