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

    void registerEvent();
    void onInitialize() ;
    void onClickedEnterServer();
    void onClickedBack();

private:

    virtual Json::Value toJson() const override {}
    virtual const std::string_view& getUniqueName() const override {}
    //EditLabel m_idLabel;
    //Button m_enterBtn;
    //Button m_backBtn;
};



SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TENTERSERVERDISPLAY_H
