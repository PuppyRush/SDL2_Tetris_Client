
#ifndef GUI_DISPLAYINTERFACE_H
#define GUI_DISPLAYINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif


#include <future>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>
#include <thread>
#include <unordered_map>
#include <mutex>
#include <tuple>
#include <condition_variable>
#include <utility>
#include <cassert>
#include <type_traits>

#include <boost/graph/adjacency_list.hpp>

#include "SEG_Constant.h"
#include "SEG_Window.h"
#include "SEG_TypeTraits.h"
#include "SEG_Resource.h"
#include "SEG_Define.h"
#include "SEG_Tree.h"
#include "EventQueue.h"
#include "ControlBuilderBase.h"

#include "SDL2EasyGUI/src/Control/Control.h"
#include "SDL2EasyGUI/src/Decorator/Decorator.h"

namespace seg {

class DisplayInterface : public GraphicInterface, public GraphicComponent<DisplayInterface>
{
public:

	using control_ptr = Control*;
	using control_ary = GraphicComponent<Control>;
	using control_interator = control_ary::iterator;
	using unique_type = GraphicInterface::unique_type;
	using display_ptr = std::shared_ptr<DisplayInterface>;

	using tree_type = tree::SEG_Tree<control_ptr>;
	using node_type = tree_type::node_type;
	using nodeset_type = tree_type::nodeset_type;

	virtual ~DisplayInterface();

	void addControl(control_ptr newCtl);

	bool removeControl(control_ptr ctl);

	virtual std::underlying_type_t<resource> alert();

	void modal();

	void modaless();

	void show()
	{
		getSEGWindow()->show();
	}

	void hidden()
	{
		getSEGWindow()->hidden();
	}

	virtual void onEvent(const SDL_Event& event);

	virtual void initialize() override;

	virtual void refresh() override;

	virtual const t_id getDisplayId() const noexcept = 0;

	virtual void postCreate(display_ptr) = 0;

	virtual void postDestroy(const unique_type unique) = 0;

	inline void setBackgroundImgPath(const std::string& path)
	{
		m_backgroundImgPath = path;
	}

	inline void setRun(const bool run)
	{
		m_run = run;
	}

	inline t_display getDisplay() const noexcept
	{
		return m_display;
	}

	inline bool isRun() const noexcept
	{
		return m_run;
	}

	inline bool getWindowResizable() const noexcept
	{
		return getSEGWindow()->getResizable();
	}

	inline void setWindowResizable(bool b) noexcept
	{
		return getSEGWindow()->setResizable(b);
	}

	inline bool getWindowBorder() const noexcept
	{
		return getSEGWindow()->getBorder();
	}

	inline void setWindowBorder(bool b) noexcept
	{
		return getSEGWindow()->setBorder(b);
	}

	inline unique_type getWindowID() const noexcept
	{
		return getSEGWindow()->getWindowID();
	}

	inline void setSuperWindowID(unique_type uniqueId) noexcept
	{
		m_superParentId = uniqueId;
	}

	inline unique_type getSuperWindowID() const noexcept
	{
		return m_superParentId;
	}

	inline t_id getResult() const noexcept
	{
		return m_resultResrouce;

	}

	Control* getHittingMunues(const SDL_Point& point);

	inline bool compareUnique(const unique_type uniqueId)
	{
		return getWindowID() == uniqueId;
	}

	template<class T>
	inline bool compareDisplay(const T displayId)
	{
		auto b = static_cast<bool>(std::is_same<std::remove_const_t<T>, std::remove_const_t<decltype(getDisplayId())>>::value);
		return getDisplayId() == toUType(displayId);
	}

	template<class T = Control>
	T* getControl(unique_type resourceId)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (_getControlAry().emptyComponent())
			return nullptr;

		const auto it = find_if(_getControlAry().beginComponent(), _getControlAry().endComponent(), [resourceId](control_ptr ptr) {
			return ptr->getId() == resourceId;
			});

		if (it == _getControlAry().endComponent())
		{
			auto end = _getControlAry().endComponent();
			for (auto _it = _getControlAry().beginComponent(); _it != end; _it++)
			{

				if (Control* _ctl = (*_it)->getComponent<T>(resourceId);
					_ctl != nullptr)
				{
					return dynamic_cast<T*>(_ctl);
				}
			}
			
		}
		else
			return dynamic_cast<T*>(*it);
	}

	template<class T = Control, class U>
	T* getControl(U resourceId)
	{
		return getControl<T>(toUType(resourceId));
	}

	control_ptr getActivatedControl() const noexcept
	{
		return m_activatedCtl;
	}

	void setActivatedControl(const control_ptr ctl) const noexcept
	{
		m_activatedCtl = ctl;
	}

	void clearActivatedControl() const noexcept
	{
		m_activatedCtl = nullptr;
	}

	control_interator findControl(const t_id resourceId);

	virtual void resize() override
	{};

protected:

	DisplayInterface();

	inline SEG_Window::window_type getSDLWindow() const noexcept
	{
		return getSEGWindow()->getWindow();
	}

	inline SEG_Window::renderer_type getRenderer() const noexcept
	{
		return getSEGWindow()->getRenderer();
	}

	void _noParamEvent(const t_id id, const std::function<void(void)> callback_fn)
	{
		m_callback_no_param.insert(make_pair(id, callback_fn));
	}

	void _oneParamEvent(const t_id id, const std::function<void(const void*)> callback_fn)
	{
		m_callback_one_param.insert(make_pair(id, callback_fn));
	}

	void _twoParamEvent(const t_id id, const std::function<void(const void*, const void*)> callback_fn)
	{
		m_callback_two_param.insert(make_pair(id, callback_fn));
	}

	void onButtonClick(const void*);

	virtual void onDraw() override;

	virtual void onDrawBackground() override;

	virtual void registerEvent() = 0;

	virtual void onInitialize();

	virtual void onCreate();

	virtual void onClose();

	virtual void onOk();

	virtual void onNo();

	virtual void onCancel();

	virtual void onDestroy();

	//events
	virtual void onCommonEvent(const SDL_CommonEvent* common) override
	{};

	virtual void onWindowEvent(const SDL_WindowEvent& window) override;

	virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override;

	virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit) override
	{};

	virtual void onTextInputEvent(const SDL_TextInputEvent* text) override
	{};

	virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

	virtual void onMouseButtonDownEvent(const SDL_MouseButtonEvent* button) override;

	virtual void onMouseButtonUpEvent(const SDL_MouseButtonEvent* button) override
	{}

	virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override
	{};

	virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis) override
	{};

	virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball) override
	{};

	virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat) override
	{};

	virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton) override
	{};

	virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice) override
	{};

	virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis) override
	{};

	virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton) override
	{};

	virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice) override
	{};

	virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice) override
	{};

	virtual void onQuitEvent(const SDL_QuitEvent* quit) override
	{};

	virtual void onUserEvent(const SDL_UserEvent* user) override;

	virtual void onSysWMEvent(const SDL_SysWMEvent* syswm) override
	{};

	virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger) override
	{};

	virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture) override
	{};

	virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture) override
	{};

	virtual void onDropEvent(const SDL_DropEvent* drop) override
	{};

	virtual void onTimerEvent(const SDL_UserEvent* user) override;

	virtual void onAttachFocus(const SDL_UserEvent* user) override
	{};

	virtual void onDetachFocus(const SDL_UserEvent* user) override
	{};

	virtual void onBound(const SDL_MouseMotionEvent* user) override
	{}

	virtual void onUnbound(const SDL_MouseMotionEvent* user) override
	{}

	virtual bool bound(const SDL_Event& event) override
	{
		return false;
	}

	virtual bool focus(const SDL_Event& event) override
	{
		return false;
	}

	virtual void onChangeProperty(const SEG_Property* property) override
	{ }


	t_display m_display;

	std::unordered_map<t_id, std::function<void(void)>> m_callback_no_param;
	std::unordered_map<t_id, std::function<void(const void*)>> m_callback_one_param;
	std::unordered_map<t_id, std::function<void(const void*, const void*)>> m_callback_two_param;

private:

	inline control_ary& _getControlAry() const
	{
		return m_controlAry ;
	}

	void attachDecorator(const control_ptr, control_ptr);

	void detachDecorator(const control_ptr);

	void _run();

	void _onDrawMenus();

	void _mouseEventOnMenus(const SDL_Event& evt);

	inline void _setResult(const t_id res)
	{
		m_resultResrouce = res;
	}

	mutable control_ary m_controlAry;
	mutable control_ptr m_activatedCtl = nullptr;

	std::string m_backgroundImgPath;
	std::thread m_thread;
	std::thread m_clickthread;
	std::atomic_bool m_run = true;
	TDisplayMode m_mode = TDisplayMode::None;
	t_id m_resultResrouce = NONE;

	t_id m_parentId = NULL_WINDOW_ID;
	t_id m_superParentId = NULL_WINDOW_ID;

#ifdef SEG_DEBUG
	drawer::TextDrawer dbg_motionDrawer;
#endif

};

#define SEG_EVENT_NO_PARAM(id, fx, obj) DisplayInterface::_noParamEvent(id,std::bind(fx,obj))
#define SEG_EVENT_1PARAM(id, fx, obj) DisplayInterface::_oneParamEvent(id,std::bind(fx,obj,std::placeholders::_1))
#define SEG_EVENT_2PARAM(id, fx, obj) DisplayInterface::_twoParamEvent(id,std::bind(fx,obj,std::placeholders::_1, std::placeholders::_2))

#define SEG_LBUTTONCLICK(id, fx, obj) SEG_EVENT_1PARAM(id,fx,obj)
#define SEG_KEYDOWN(id, fx, obj) SEG_EVENT_1PARAM(id,fx,obj)

}

#endif