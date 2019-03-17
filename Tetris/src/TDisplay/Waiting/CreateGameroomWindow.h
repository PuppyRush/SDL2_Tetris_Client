//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_FIGURE_CLASS_CREATEWINDOW_H
#define TETRIS_FIGURE_CLASS_CREATEWINDOW_H

#include <string>

#include "TDisplay/TDisplayInterface.h"

SDL_TETRIS_BEGIN

class CreateGameroomWindow : public TDisplayInterface
{
public:

    std::string m_roomname;
    virtual ~CreateGameroomWindow() = default;

protected:
    virtual void registerEvent() override;
    virtual void onInitialize() override;
    virtual void onDraw() override;
    virtual void onClose() override;
    virtual void onOK() override;
    virtual void onCancel() override;

private:

    virtual Json::Value toJson() const override {}
    virtual const std::string_view& getUniqueName() const override {}
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_CREATEWINDOW_H
