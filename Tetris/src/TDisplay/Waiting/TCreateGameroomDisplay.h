//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_CLIENT_CREATEWINDOW_H
#define TETRIS_CLIENT_CREATEWINDOW_H

#include <string>

#include "TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TCreateGameroomDisplay : public TDisplayInterface
{
public:

    explicit TCreateGameroomDisplay();

    virtual ~TCreateGameroomDisplay() = default;

    virtual const seg::t_id getDisplayId() const noexcept override final
    {
        return seg::toUType(resource::CREATEROOM_DISPLAY);
    }


    inline const std::string& getRoomName() const noexcept
    { return m_roomname; }

protected:
    std::string m_roomname;

    virtual void registerEvent() override;

    virtual void onInitialize() override;

    virtual void onDraw() override;

    virtual void onClose() override;

    void onClickOk(const void*);

    void onClickCancel(const void*);

private:

};

SDL_TETRIS_END

#endif //TETRIS_CLIENT_CREATEWINDOW_H
