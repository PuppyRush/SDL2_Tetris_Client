//
// Created by chaed on 19. 2. 14.
//

#ifndef TETRIS_CLIENT_TENTERSERVERDISPLAY_H
#define TETRIS_CLIENT_TENTERSERVERDISPLAY_H

#include "SDL2EasyGUI/include/EditLabel.h"
#include "SDL2EasyGUI/include/Button.h"

#include "TDisplayInterface.h"
#include "THeader.h"

SDL_TETRIS_BEGIN

class TEnterServerDisplay : public TDisplayInterface
{

public:

    explicit TEnterServerDisplay();

    virtual ~TEnterServerDisplay() = default;

    virtual const seg::t_id getDisplayId() const noexcept override final
    {
        return seg::toUType(resource::ENTERSERVER_DISPLAY);
    }

    virtual void registerEvent() override;

    virtual void onInitialize() override;

    void onClickedEnterServer(const void* click);

    void onClickedBack(const void* click);

    bool m_valid = false;

private:

};

SDL_TETRIS_END

#endif //TETRIS_CLIENT_TENTERSERVERDISPLAY_H
