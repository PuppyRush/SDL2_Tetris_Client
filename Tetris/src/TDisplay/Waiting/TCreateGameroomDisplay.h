//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_FIGURE_CLASS_CREATEWINDOW_H
#define TETRIS_FIGURE_CLASS_CREATEWINDOW_H

#include <string>

#include "TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TCreateGameroomDisplay : public TDisplayInterface
{
public:

    explicit TCreateGameroomDisplay(const sdleasygui::t_id displayId);

    virtual ~TCreateGameroomDisplay() = default;

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

#endif //TETRIS_FIGURE_CLASS_CREATEWINDOW_H
