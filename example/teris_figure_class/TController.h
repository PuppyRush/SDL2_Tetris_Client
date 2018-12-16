//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TCONTROLLER_H
#define TERIS_FIGURE_CLASS_TCONTROLLER_H

#include "Common/TDefine.h"

#include <memory>



#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "Common/TProperty.h"
#include "Common/TType.h"

class TControllerInterface
{
public:
    virtual ~TControllerInterface();

    void show();
    void hide();

protected:
    TControllerInterface();

    inline std::shared_ptr<SDL_Window> getWindow() const {
        return m_window;
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const
    {
        return m_renderer;
    }

    inline std::shared_ptr<SDL_Event> getSDLEvent() const
    {
        return m_event;
    }

private:
    void _setBackgroundDisplay();
    virtual void _setDisplay() = 0;

    const tetris::t_size m_windowWidth;
    const tetris::t_size m_windowHeight;

    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
    std::shared_ptr<SDL_Event> m_event;
    std::string m_backgroundImgPath;
};


#endif //TERIS_FIGURE_CLASS_TCONTROLLER_H
