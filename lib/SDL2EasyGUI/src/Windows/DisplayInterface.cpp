//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "magic_enum/include/magic_enum.hpp"

#include "include/DisplayController.h"
#include "include/SEG_Resource.h"
#include "include/SEG_Event.h"
#include "include/DisplayInterface.h"

#include "EasyTimer/ElapsedTimer.h"
#include "GameInterface/include/Logger.h"

using namespace std;
using namespace seg;
using namespace game_interface;

DisplayInterface::DisplayInterface()
{
    m_window = new SEG_Window;
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
    getWindow()->initialize();

    setRun(true);

    onCreate();
    onInitialize();
    show();
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
}

void DisplayInterface::modaless()
{
    m_mode = TDisplayMode::Modaless;
    m_thread = std::thread(&DisplayInterface::_run, this);
}

void DisplayInterface::ready(const DisplayInterface* parentDp)
{
    m_parentId = parentDp->getWindowID();
    m_superParentId = parentDp->m_superParentId;
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
        if (ctl != nullptr && ctl->isHit({ static_cast<t_coord>( evt.button.x) ,static_cast<t_coord>(evt.button.y) }))
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
    case SDL_MOUSEBUTTONDOWN:
    {
        auto ctl = getHittingMunues({ evt.button.x, evt.button.y });
        if (ctl != nullptr && ctl->isHit({ static_cast<t_coord>(evt.motion.x), static_cast<t_coord>(evt.motion.y) }))
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

Control* DisplayInterface::getHittingMunues(const SDL_Point& point) const
{
    for (const auto& ctl : _getMenuAry()) {
        if (ctl->isHit(point.x, point.y))
        {
            return ctl;
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
            //_onDrawMenus();
            //break;
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

void DisplayInterface::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    refresh();
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

void DisplayInterface::_release()
{
    auto renderer = getRenderer();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
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
    _getMenuAry().clear();
}

void DisplayInterface::onDrawBackground()
{
    if (!m_backgroundImgPath.empty()) {
        auto renderer = getRenderer();
        t_size w, h; // m_texture width & height

        auto img = IMG_LoadTexture(renderer, m_backgroundImgPath.c_str());
        SDL_QueryTexture(img, NULL, NULL, reinterpret_cast<int*>(&w), reinterpret_cast<int*>(&h) );

        SDL_Rect texr;
        texr.x = 0;
        texr.y = 0;
        texr.w = w;
        texr.h = h;
        SDL_RenderCopy(renderer, img, NULL, &texr);
    } else {
        SDL_Rect rect = SDL_Rect{0, 0, static_cast<int>( getWindowWidth()), static_cast<int>( getWindowHeight()) };
        GraphicInterface::_drawBackground(rect);
    }
}

void DisplayInterface::onDraw()
{
   logger::Logger::getInstance().printLog("DisplayInterface::onDraw()",
                                           logger::Logger::logger_level::Debug);

    _onDrawMenus();
    _release();
}

void DisplayInterface::_onDrawMenus()
{
    for (const auto& menu : _getMenuAry()) {
        menu->onVirtualDraw();
    }
}


void DisplayInterface::addControl(Control* newCtl)
{
    auto maybeCtl = dynamic_cast<Control*>(newCtl);
    if (maybeCtl == nullptr) {
        assert(0);
        return;
    }

    maybeCtl->initialize();

    auto it = std::find_if(begin(_getMenuAry()), end(_getMenuAry()), [newCtl](control_ptr exCtl) {
        return newCtl->getId() == exCtl->getId();
    });

    if (it != _getMenuAry().end()) {
        assert(0);
        return;
    }

    _getMenuAry().emplace_back(maybeCtl);
}

bool DisplayInterface::removeControl(control_ptr ctl)
{

    if (auto dest = findControl(ctl->getId()); dest != _getMenuAry().end()) {
        _getMenuAry().erase(dest);
        return true;
    }

    return false;
}

void DisplayInterface::refresh()
{
    event::EventPusher event{this->getWindowID(), SEG_DRAW,  SEG_DRAW_DISPLAY};
    event.pushEvent();
}

void DisplayInterface::attachDecorator(const control_ptr ctl, control_ptr decorator)
{
    if (removeControl(ctl)) {
        addControl(decorator);
        m_activatedCtl = decorator;
        m_activatedCtl->refresh();
    }

}

void DisplayInterface::detachDecorator(const control_ptr ctl)
{
    if (removeControl(ctl)) {
        addControl(ctl);
        m_activatedCtl = ctl;
        m_activatedCtl->refresh();
    }
}

DisplayInterface::control_ptr
DisplayInterface::getControl(const t_id resourceId)
{
    if (_getMenuAry().empty())
        return nullptr;

    auto it = find_if(begin(_getMenuAry()), end(_getMenuAry()), [resourceId](control_ptr ptr) {
        return ptr->getId() == resourceId;
    });

    return it == _getMenuAry().end() ? nullptr : *it;
}

DisplayInterface::control_ary_it
DisplayInterface::findControl(const t_id resourceId)
{
    return find_if(begin(_getMenuAry()), end(_getMenuAry()), [resourceId](control_ptr ptr) {
        return ptr->getId() == resourceId;
    });
}