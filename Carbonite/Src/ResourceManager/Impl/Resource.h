#pragma once

#include "ResourceManager/Resource.h"

#include <utility>

namespace ResourceManager
{
	template <class T>
	template <class... Args>
	Resource<T>::Resource(Args&&... args) requires std::is_constructible_v<T, Args...>
	    : m_Value(std::forward<Args>(args)...), m_RefCount(0), m_WRefCount(1)
	{
	}

	template <class T>
	bool Resource<T>::isPersistent() const
	{
		return m_RefCount == static_cast<std::uint16_t>(~0U) && m_WRefCount == static_cast<std::uint16_t>(~0U);
	}

	template <class T>
	void Resource<T>::setPersistent()
	{
		m_RefCount  = ~0U;
		m_WRefCount = ~0U;
	}

	template <class T>
	void Resource<T>::incRef()
	{
		if (!isPersistent())
			++m_RefCount;
	}

	template <class T>
	bool Resource<T>::decRef()
	{
		if (isPersistent())
			return false;

		if (--m_RefCount == 0)
		{
			destroy();
			return decWRef();
		}
		return false;
	}

	template <class T>
	void Resource<T>::incWRef()
	{
		if (!isPersistent())
			++m_WRefCount;
	}

	template <class T>
	bool Resource<T>::decWRef()
	{
		if (!isPersistent())
			return --m_WRefCount == 0;
		return false;
	}

	template <class T>
	void Resource<T>::destroy()
	{
		m_Value.~T();
	}
} // namespace ResourceManager