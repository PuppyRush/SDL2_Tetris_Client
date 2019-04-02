//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_FIGURE_CLASS_CREATEWINDOW_H
#define TETRIS_FIGURE_CLASS_CREATEWINDOW_H

#include <string>

#include "TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class TCreateGameroomWindow : public TDisplayInterface
{
public:

    std::string m_roomname;
    virtual ~TCreateGameroomWindow() = default;

protected:
    virtual void registerEvent() override;
    virtual void onInitialize() override;
    virtual void onDraw() override;
    virtual void onClose() override;
    void onClickOk(const void *);
    void onClickCancel(const void *);

private:

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_CREATEWINDOW_H
