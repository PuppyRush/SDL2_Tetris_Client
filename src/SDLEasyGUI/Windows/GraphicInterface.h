//
// Created by chaed on 19. 1. 22.
//

#ifndef GUI_GRAPHICINTERFACE_H
#define GUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Tetris/Common/TDefine.h"
#include "Window.h"
#include "EventListener.h"
#include "EventDelivery.h"


class GraphicInterface : public EventListener, public EventDelivery
{

public:
    using window_ptr = std::shared_ptr<Window>;

    virtual void onDraw() = 0;

    void setWindow(window_ptr window){m_window = window;}

    window_ptr getWindow() const noexcept {
        return m_window;
    }

protected:

    GraphicInterface() = default;
    virtual ~GraphicInterface() = default;

    virtual void refresh() = 0;

private:

    virtual bool validId(const game_interface::t_id id) = 0;
    virtual void onTimer() = 0;

    window_ptr m_window = nullptr;

};


#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
