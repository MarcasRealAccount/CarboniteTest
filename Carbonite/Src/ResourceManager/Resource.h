#pragma once

#include <type_traits>

namespace ResourceManager
{
	template <class T>
	struct Resource final
	{
	public:
		template <class... Args>
		Resource(Args&&... args) requires std::is_constructible_v<T, Args...>;

		inline bool isPersistent() const;
		inline void setPersistent();

		inline void incRef();
		inline bool decRef();
		inline void incWRef();
		inline bool decWRef();
		inline void destroy();

		T*       getValue() { return &m_Value; }
		const T* getValue() const { return &m_Value; }

		auto getRefCount() const { return m_RefCount; }
		auto getWRefCount() const { return m_WRefCount; }

		bool valid() const { return getRefCount() > 0; }

		         operator T&() { return m_Value; }
		         operator const T&() const { return m_Value; }
		T*       operator->() { return &m_Value; }
		const T* operator->() const { return &m_Value; }
		T&       operator*() { return m_Value; }
		const T& operator*() const { return m_Value; }

	private:
		T             m_Value;
		std::uint16_t m_RefCount;
		std::uint16_t m_WRefCount;
	};
} // namespace ResourceManager