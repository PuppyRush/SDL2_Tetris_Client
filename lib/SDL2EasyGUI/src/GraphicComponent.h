#ifndef GUI_GRAPHICCOMPONENT_H
#define GUI_GRAPHICCOMPONENT_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include <vector>
#include <memory>

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

	~GraphicComponent() = default;

	void addComponent(const component_ptr& component)
	{
		m_componentAry.emplace_back(component);
	}

	void removeComponent(unique_type resId)
	{
		for (const auto& it : m_componentAry)
		{
			if ((*it)->getId() == resId)
			{
				m_componentAry.erase(it);
				return;
			}
		}
	}

	void removeComponent(iterator& it)
	{
		m_componentAry.erase(it);
	}

	template <class T = component_dest_type>
	T* getComponent(unique_type resourceId) const noexcept
	{
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
		return getComponent<T>(toUType(resourceId));
	}

	template <class T = component_dest_type>
	auto atComponent(t_size idx)
	{
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
		return  m_componentAry.begin();
	}

	iterator endComponent() noexcept
	{
		return  getComponentAry().end();
	}

	template <class T = component_dest_type>
	T* backComponent() noexcept
	{
		if constexpr (std::is_same<component_type, T>::value)
		{
			return static_cast<component_ptr>(m_componentAry.back());
		}
		else
		{
			return dynamic_cast<T*>(m_componentAry.back());
		}
	}

	void popComponent() noexcept
	{
		getComponentAry().pop_back();
	}

	size_t sizeComponent() noexcept
	{
		return getComponentAry().size();
	}

	bool emptyComponent() noexcept
	{
		return getComponentAry().empty();
	}

private:

	inline component_ary& getComponentAry() noexcept
	{
		return m_componentAry;
	}

	component_ary m_componentAry;

};

}

#endif