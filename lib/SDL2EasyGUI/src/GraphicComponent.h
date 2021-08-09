#ifndef GUI_GRAPHICCOMPONENT_H
#define GUI_GRAPHICCOMPONENT_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include <vector>
#include <memory>
#include <mutex>
#include "SDL2EasyGUI/include/SEG_Type.h"

namespace seg
{

template <class Base, class Dest = Base>
class GraphicComponent
{
public:

	using component_type = Base;
	using component_dest_type = Dest;
	using component_ptr = component_type*;
	using component_dest_ptr = component_dest_type*;
	using unique_type = t_id;
	using component_ary = std::vector<component_ptr>;
	using iterator = typename component_ary::iterator;

	GraphicComponent() = default;

	GraphicComponent(const component_ptr comp)
		:m_componentAry(comp->m_componentAry)
	{}

	virtual ~GraphicComponent() = default;

	virtual void addComponent(const component_ptr& component)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_componentAry.emplace_back(component);
	}

	virtual iterator removeComponent(unique_type resId)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		auto it = std::remove_if(begin(m_componentAry), end(m_componentAry), [resId](auto comp) {
			if (comp->getId() == resId)
				return true;
			});

		if (it != end(m_componentAry))
		{
			return m_componentAry.erase(it);
		}
		else
		{
			return it;
		}
	}

	virtual iterator removeComponent(iterator& it)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_componentAry.erase(it);
	}

	virtual iterator removeComponentFromIndex(t_size idx)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		auto it = m_componentAry.begin() + idx;
		return m_componentAry.erase(it);
	}

	virtual void popComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		getComponentAry().pop_back();
	}


	template <class T = component_dest_type>
	T* getComponent(unique_type resourceId) const noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (const auto& it : m_componentAry)
		{
			if (it->getId() == resourceId)
			{
				return dynamic_cast<T*>(it);
			}
			else
			{
				if (component_ptr _com = it->getComponent<T>(resourceId);
					_com != nullptr)
				{
					return dynamic_cast<T*>(_com);
				}
			}
		}
		return nullptr;
	}

	template <class T = component_dest_type, class U>
	auto getComponent(U resourceId) const noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return getComponent<T>(toUType(resourceId));
	}

	template <class T = component_dest_type>
	auto atComponent(t_size idx)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if constexpr (std::is_same<component_type, T>::value)
		{
			return static_cast<component_ptr>(getComponentAry().at(idx));
		}
		else
		{
			return dynamic_cast<T*>(getComponentAry().at(idx));
		}
		
	}

	template <class T = component_dest_type>
	auto getComponent(iterator& it)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if constexpr (std::is_same<component_type, T>::value)
		{
			return static_cast<component_ptr>(m_componentAry.get(it));
		}
		else
		{
			return dynamic_cast<T*>(m_componentAry.get(it));
		}
	}

	iterator beginComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return  m_componentAry.begin();
	}

	iterator endComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return  getComponentAry().end();
	}

	template <class T = component_dest_type>
	T* backComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if constexpr (std::is_same<component_type, T>::value)
		{
			return static_cast<component_ptr>(m_componentAry.back());
		}
		else
		{
			return dynamic_cast<T*>(m_componentAry.back());
		}
	}

	template <class T = component_dest_type>
	T* frontComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if constexpr (std::is_same<component_type, T>::value)
		{
			return static_cast<component_ptr>(m_componentAry.front());
		}
		else
		{
			return dynamic_cast<T*>(m_componentAry.front());
		}
	}

	virtual  size_t countComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return getComponentAry().size();
	}

	virtual bool emptyComponent() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return getComponentAry().empty();
	}

protected:
	inline component_ary& getComponentAry() noexcept
	{
		return m_componentAry;
	}

protected:
	 mutable std::mutex m_mutex;
	 
private:
	component_ary m_componentAry;
};

}

#endif