//
// Created by chaed on 19. 2. 14.
//

#ifndef TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
#define TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H

#include "SDL2EasyGUI/include/EditLabel.h"
#include "SDL2EasyGUI/include/Button.h"

#include "TDisplayInterface.h"
#include "THeader.h"

SDL_TETRIS_BEGIN

class TEnterServerDisplay : public TDisplayInterface
{

public:

    explicit TEnterServerDisplay(const sdleasygui::t_id displayId);

    virtual ~TEnterServerDisplay() = default;

    virtual void registerEvent() override;

    virtual void onInitialize() override;

    void onClickedEnterServer(const void* click);

    void onClickedBack(const void* click);

    bool m_valid = false;

private:

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
