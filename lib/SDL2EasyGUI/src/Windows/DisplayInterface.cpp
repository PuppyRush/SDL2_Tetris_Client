//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "magic_enum/include/magic_enum.hpp"

#include "include/DisplayController.h"
#include "include/DisplayInterface.h"
#include "include/SEG_Resource.h"
#include "include/SEG_Event.h"
#include "SEG_Helper.h"

#include "EasyTimer/ElapsedTimer.h"
#include "GameInterface/include/Logger.h"

using namespace std;
using namespace seg;
//using namespace component;
using namespace seg::helper;
using namespace game_interface;

DisplayInterface::DisplayInterface()
    :GraphicInterface(new SEG_Window)
{
}

DisplayInterface::~DisplayInterface()
{
    onClose();
}

void DisplayInterface::onInitialize()
{
    registerEvent();

}

void DisplayInterface::initialize()
{
    getSEGWindow()->initialize();

    setRun(true);

    onCreate();
    onInitialize();
    show();

#ifdef SEG_DEBUG
    dbg_motionDrawer.setSize(14);
    dbg_motionDrawer.setRenderer(getRenderer());
    dbg_motionDrawer.setColor(ColorCode::red);
#endif 
}

std::underlying_type_t<resource> DisplayInterface::alert()
{
    DisplayController::getInstance().alert(this);

    m_thread = thread(&DisplayInterface::_run, this);    
    m_thread.join();

    DisplayController::getInstance().alert_close();
    
    return NULL;
}

void DisplayInterface::modal()
{
    m_mode = TDisplayMode::Modal;
    m_thread = std::thread(&DisplayInterface::_run, this);
    m_thread.join();
    
    DisplayMap::getInstance().popModal(getWindowID());
}

void DisplayInterface::modaless()
{
    m_mode = TDisplayMode::Modaless;
    m_thread = std::thread(&DisplayInterface::_run, this);
}


void DisplayInterface::_run()
{
    static int debug{0};

    while (m_run) 
    {

        auto event = m_eventDelivery.popEvent();
        this->onEvent(event);
            
        //printf("DisplayInterface::_run : %d\n", debug++);
    }
}

void DisplayInterface::onEvent(const SDL_Event& event)
{
    EventListener::onEvent(event);
    _mouseEventOnMenus(event);
}

void DisplayInterface::_mouseEventOnMenus(const SDL_Event& evt)
{
    switch (evt.type)
    {
    case SDL_MOUSEMOTION:
    {
        auto ctl = getHittingMunues({ evt.motion.x, evt.motion.y });
        if (ctl != nullptr && ctl->isHit( make_segpoint(evt.button.x ,evt.button.y) ))
        {
            ctl->onEvent(evt);
            ctl->bound(evt);
        }
        if (ctl == nullptr && getActivatedControl() != nullptr)
        {
            getActivatedControl()->bound(evt);
        }
        break;
    }
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
    {
        auto ctl = getHittingMunues({ evt.button.x, evt.button.y });
        if (ctl != nullptr )
        {
            ctl->onEvent(evt);
            ctl->focus(evt);
            setActivatedControl(ctl);
        }
        if (ctl == nullptr && getActivatedControl() != nullptr)
        {
            getActivatedControl()->focus(evt);
            clearActivatedControl();
        }
        break;
    }
    case SDL_MOUSEWHEEL:
    {
        auto ctl = getHittingMunues({ evt.button.x, evt.button.y });
        if (ctl != nullptr)
        {
            ctl->onEvent(evt);
        }
        if (ctl == nullptr && getActivatedControl() != nullptr)
        {
            getActivatedControl()->onEvent(evt);
        }
        break;
    }
    case SEG_CONTROLLER:
    {
        if (evt.user.code == SEG_ATTACH_FOCUS || evt.user.code == SEG_DETACH_FOCUS)
        {
            auto data = static_cast<event::SEG_UserEventData*>(evt.user.data1);
            if (data == nullptr)
            {
                assert(0);
                return;
            }
            auto ctl = getControl(data->controlId);
            if (ctl == nullptr)
            {
                assert(0);
                return;
            }
            ctl->onEvent(evt);
        }
        break;
    }
    case SDL_TEXTINPUT:
    case SDL_KEYDOWN:
    {
        if (getActivatedControl() != nullptr)
        {
            getActivatedControl()->onEvent(evt);
        }
        break;
    }
    default:

        break;
    }
}

Control* DisplayInterface::getHittingMunues(const SDL_Point& point)
{
    auto it = _getControlAry().beginComponent();
    const auto& end = _getControlAry().endComponent();
    for (; it != end; it++)
    {
        if ((*it)->isHit(make_segpoint(point.x, point.y)))
        {
            return (*it);
        }
    }

    return nullptr;
}

void DisplayInterface::onUserEvent(const SDL_UserEvent* event)
{
    using namespace event;

    switch (event->type) {
    case SEG_DRAW:
        switch (event->code) {
        case SEG_DRAW_CONTROLLER:
        {
            //_onDrawMenus();
            auto userdata = static_cast<SEG_UserEventData*>(event->data1);
            if (auto ctl = getControl(userdata->controlId);
                ctl != nullptr)
            {
                //ctl->onDraw();
            }
        }
        case SEG_DRAW_DISPLAY:
            //dont call _refresh() in this case.
            onDrawBackground();
            onDraw();
            break;
        default:
            break;
        }
        break;
    case SEG_CONTROLLER:
        switch (event->code)
        {
        case SEG_ATTACH_FOCUS:
            onAttachFocus(event);
            break;
        case SEG_DETACH_FOCUS:
            onDetachFocus(event);
            break;
        case SEG_CLICKED_CONTROLLER: {
            auto userdata = static_cast<SEG_UserEventData*>(event->data1);
            if (userdata == nullptr)
                break;

            event::SEG_Click* click = static_cast<event::SEG_Click*>(event->data2);
            _setResult(click->resourceId);

            if (m_callback_one_param.count(userdata->controlId) > 0) {
                m_callback_one_param.at(userdata->controlId)(click);
            }
            break;
        }
        case SEG_ENTER_CONTROLLER: {
            auto userdata = static_cast<SEG_UserEventData*>(event->data1);

            if (m_callback_one_param.count(userdata->controlId) > 0) {
                SDL_KeyboardEvent* keyevent = static_cast<SDL_KeyboardEvent*>(event->data2);
                m_callback_one_param.at(userdata->controlId)(keyevent);
            }
            break;
        }
        case SEG_DECORATOR_ATTACH: {

            auto userdata = static_cast<SEG_UserEventData*>(event->data1);
            control_ptr decorator = static_cast<control_ptr>(event->data2);

            if (auto ctl = getControl(userdata->controlId); ctl != nullptr) {
                attachDecorator(ctl, decorator);
            }
            else {
                assert(0);
            }

            break;
        }
        case SEG_DECORATOR_DETACH: {
            auto userdata = static_cast<SEG_UserEventData*>(event->data1);
            auto origin = static_cast<Control*>(event->data2);
            if (auto deco = getControl(userdata->controlId); deco != nullptr && origin->getId() == deco->getId()) {
                detachDecorator(origin);
            }
            else {
                assert(0);
            }

            break;
        }
        }//switch
        break;
    default:
        switch (event->code)
        {
        case SEG_WINDOW_CLOSE:
            onClose();
            break;
        default:;
        }
    }
}

void DisplayInterface::onTimerEvent(const SDL_UserEvent* user)
{
    using namespace event;
    if (SEG_UserEventData* userdata = static_cast<SEG_UserEventData*>(user->data1);
        userdata != nullptr)
    {
        if (auto ctl = getControl(userdata->controlId);
            ctl != nullptr)
        {
            ctl->onTimerEvent(user);
        }
    }
    
}

void DisplayInterface::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    switch (key->keysym.sym) {
        case SDLK_RETURN:
            if (m_activatedCtl != nullptr && m_activatedCtl->isActivated())
            {
                m_activatedCtl->onHit(m_activatedCtl->getMidPoint(), true);
            }
            break;
        case SDLK_ESCAPE:
            if (m_activatedCtl != nullptr && m_activatedCtl->isActivated())
            {
                m_activatedCtl->setActivating(false);
            }
            break;
    }
}

#include <boost/format.hpp>
void DisplayInterface::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
   
#ifdef SEG_DEBUG
    dbg_motionDrawer.setPoint(make_segpoint(motion->x, motion->y));
    char c[10];
    ::sprintf(c, "%d,%d", motion->x, motion->y);
    dbg_motionDrawer.setText(std::string{ c });
    refresh();
#endif

}

void DisplayInterface::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
}

void DisplayInterface::onWindowEvent(const SDL_WindowEvent& window)
{
    switch (window.event) {
        case SDL_WINDOWEVENT_MAXIMIZED:
        case SDL_WINDOWEVENT_MOVED:
        case SDL_WINDOWEVENT_SHOWN:
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESTORED:
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            refresh();
            break;
        case SDL_WINDOWEVENT_CLOSE:
            onDestroy();
            break;
    }
}

void DisplayInterface::onCreate()
{
    refresh();
}

void DisplayInterface::onClose()
{
    if (m_resultResrouce == resource::NONE) {
        m_resultResrouce = resource::BTN_CLOSE;
    }

    setRun(false);
    hidden();

    onDestroy();
}

void DisplayInterface::onButtonClick(const void* event)
{
    m_resultResrouce = static_cast<const event::SEG_Click*>(event)->resourceId;
}

void DisplayInterface::onOk()
{
    m_resultResrouce = BTN_OK;
    onClose();
}

void DisplayInterface::onNo()
{
    m_resultResrouce = BTN_NO;
    onClose();
}

void DisplayInterface::onCancel()
{
    m_resultResrouce = BTN_CANCEL;
    onClose();
}

void DisplayInterface::onDestroy()
{
   //_getControlAry().clear();
}

void DisplayInterface::onDrawBackground()
{
    if (!m_backgroundImgPath.empty()) {
        t_size w, h; // m_texture width & height

        auto img = IMG_LoadTexture(getRenderer(), m_backgroundImgPath.c_str());
        SDL_QueryTexture(img, NULL, NULL, reinterpret_cast<int*>(&w), reinterpret_cast<int*>(&h) );

        SDL_Rect texr;
        texr.x = 0;
        texr.y = 0;
        texr.w = w;
        texr.h = h;
        SDL_RenderCopy(getRenderer(), img, NULL, &texr);
    } else {
        SDL_Rect rect = make_sdlrect(0, 0, getWindowWidth(), getWindowHeight());
        GraphicInterface::_drawBackground(rect);
    }
}

void DisplayInterface::onDraw()
{
   logger::Logger::getInstance().printLog("DisplayInterface::onDraw()",
                                           logger::Logger::logger_level::Debug);
    _onDrawMenus();

#ifdef SEG_DEBUG
    dbg_motionDrawer.drawText();
#endif

    GraphicInterface::onDraw();
}

void DisplayInterface::_onDrawMenus()
{
    const auto end = _getControlAry().endComponent();
    for (auto it = _getControlAry().beginComponent(); it != end; it++)
    {
        (*it)->onVirtualDraw();
    }
}


void DisplayInterface::addControl(Control* newCtl)
{
    auto maybeCtl = dynamic_cast<Control*>(newCtl);
    if (maybeCtl == nullptr) {
        assert(0);
        return;
    }

    if (maybeCtl->wasInitailized() == false)
        maybeCtl->initialize();

    auto it = std::find_if(_getControlAry().beginComponent(), _getControlAry().endComponent(), [newCtl](control_ptr exCtl) {
        return newCtl->getId() == exCtl->getId();
        });

    if (it != _getControlAry().endComponent()) {
        assert(0);
        return;
    }

    //디스플레이의 제일 표면에 추가한다
    _getControlAry().addComponent(newCtl);
}

bool DisplayInterface::removeControl(control_ptr ctl)
{

    if (auto dest = findControl(ctl->getId()); dest != _getControlAry().endComponent()) {
        _getControlAry().removeComponent(dest);
        return true;
    }

    return false;
}

void DisplayInterface::refresh()
{
    event::EventPusher event {this->getWindowID(), SEG_DRAW, SEG_DRAW_DISPLAY};
    event.pushEvent();
}

void DisplayInterface::attachDecorator(const control_ptr ctl, control_ptr decorator)
{
    if (removeControl(ctl)) {
        decorator->initialize();
        dynamic_cast<DecoratorInterface*>(decorator)->attach();
        addControl(decorator);
        m_activatedCtl = decorator;
        m_activatedCtl->refresh();
    }

}

void DisplayInterface::detachDecorator(const control_ptr ctl)
{
    if (auto deco = getControl(ctl->getId());
        deco != nullptr)
    {
        if (auto decoInterface = dynamic_cast<DecoratorInterface*>(deco);
            decoInterface != nullptr)
        {
            decoInterface->detach();
        }

        removeControl(deco);
        addControl(ctl);
        m_activatedCtl = ctl;
        m_activatedCtl->refresh();
    }
}



DisplayInterface::control_interator
DisplayInterface::findControl(const t_id resourceId)
{
    return find_if( _getControlAry().beginComponent(), _getControlAry().endComponent(), [resourceId](control_ptr ptr) {
        return ptr->getId() == resourceId;
    });
}