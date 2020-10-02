
#ifndef GUI_DISPLAYINTERFACE_H
#define GUI_DISPLAYINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/include/EventListener.h"
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

#include "SEG_Window.h"
#include "EventListener.h"
#include "EventQueue.h"

#include "SEG_TypeTraits.h"
#include "SEG_Resource.h"
#include "SEG_Define.h"

#include "ControlBuilder.h"
#include "SDL2EasyGUI/src/Controller/Control.h"
#include "../src/Decorator/Decorator.h"

namespace seg {

	class DisplayInterface : public GraphicInterface, public EventListener
	{
	public:

		using control_ptr = typename Control::control_ptr;
		using control_ary = std::vector<control_ptr>;
		using control_ary_it = typename control_ary::iterator;
		using unique_type = typename GraphicInterface::unique_type;
		using display_ptr = std::shared_ptr<DisplayInterface>;

		virtual ~DisplayInterface();

		void addControl(control_ptr newCtl);

		bool removeControl(control_ptr ctl);

		virtual std::underlying_type_t<resource> alert();

		void modal();

		void modaless();

		void drawBackGroundImage();

		void show()
		{
			getWindow()->show();
		}

		void hidden()
		{
			getWindow()->hidden();
		}

		//부모 클래스의 포인터(this)를 넘긴다.
		void ready(const DisplayInterface*);

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

		inline void setStopDraw(const bool set)
		{
			m_stopDraw = set;
		}

		inline t_display getDisplay() const noexcept
		{
			return m_display;
		}

		inline bool isRun() const noexcept
		{
			return m_run;
		}

		inline bool getSetDraw() const noexcept
		{
			return m_stopDraw;
		}

		inline unique_type getWindowID() const noexcept
		{
			return getWindow()->getWindowID();
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

		Control* getHittingMunues(const SDL_Point& point) const;

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

		template<class T, class U>
		auto getControl(const U resourceId)
		{
			auto ctl = *find_if(begin(m_menus), end(m_menus), [resourceId](control_ptr ptr) {
				return ptr->getId() == toUType(resourceId);
				});

			return dynamic_cast<T*>(ctl);
		}

		control_ptr getControl(const t_id resourceId);

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

		control_ary_it findControl(const t_id resourceId);

		virtual void resize() override
		{};

	protected:

		DisplayInterface();

		inline SEG_Window::window_type getSDLWindow() const noexcept
		{
			return getWindow()->getSDLWindow();
		}

		inline SEG_Window::renderer_type getRenderer() const noexcept
		{
			return getWindow()->getSDLRenderer();
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

		virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
		{}

		virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

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


		t_display m_display;

		std::unordered_map<t_id, std::function<void(void)>> m_callback_no_param;
		std::unordered_map<t_id, std::function<void(const void*)>> m_callback_one_param;
		std::unordered_map<t_id, std::function<void(const void*, const void*)>> m_callback_two_param;

	private:

		inline control_ary& _getMenuAry() const 
		{
			return m_menus;
		}

		void attachDecorator(const control_ptr, control_ptr);

		void detachDecorator(const control_ptr);

		void _release();

		void _run();

		void _onDrawMenus();

		void _mouseEventOnMenus(const SDL_Event& evt);

		inline void _setResult(const t_id res)
		{
			m_resultResrouce = res;
		}

		mutable control_ary m_menus;
		mutable Control* m_activatedCtl = nullptr;

		std::string m_backgroundImgPath;
		bool m_stopDraw = false;
		std::thread m_thread;
		std::thread m_clickthread;
		std::atomic_bool m_run = true;
		TDisplayMode m_mode = TDisplayMode::None;
		t_id m_resultResrouce = NONE;

		t_id m_parentId = IVALID_DISPLAY_ID;
		t_id m_superParentId = IVALID_DISPLAY_ID;

	};

#define SEG_EVENT_NO_PARAM(id, fx, obj) DisplayInterface::_noParamEvent(id,std::bind(fx,obj))
#define SEG_EVENT_1PARAM(id, fx, obj) DisplayInterface::_oneParamEvent(id,std::bind(fx,obj,std::placeholders::_1))
#define SEG_EVENT_2PARAM(id, fx, obj) DisplayInterface::_twoParamEvent(id,std::bind(fx,obj,std::placeholders::_1, std::placeholders::_2))

#define SEG_LBUTTONCLICK(id, fx, obj) SEG_EVENT_1PARAM(id,fx,obj)
#define SEG_KEYDOWN(id, fx, obj) SEG_EVENT_1PARAM(id,fx,obj)

}

#endif