//
// Created by chaed on 19. 2. 14.
//

#ifndef TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
#define TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H

#include "SDL2EasyGUI/src/Controller/EditLabel.h"
#include "SDL2EasyGUI/src/Controller/Button.h"

#include "TDisplay/TDisplayInterface.h"
#include "../../Common/THeader.h"

SDL_TETRIS_BEGIN

class TEnterServerDisplay : public TDisplayInterface
{

public:

    TEnterServerDisplay() = default;
    virtual ~TEnterServerDisplay() = default;

    virtual void registerEvent() override;
    virtual void onInitialize() override;
    void onClickedEnterServer(const void* click);
    void onClickedBack(const void* click);

private:

};



SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
