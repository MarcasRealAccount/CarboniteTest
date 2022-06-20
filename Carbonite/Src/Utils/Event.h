#pragma once

#include <functional> // TODO(MarcasRealAccount): Maybe implement a faster and smaller std::function alternative
#include <set>
#include <type_traits>

namespace Utils
{
	template <bool B, class T1, class T2>
	class Select
	{
		using Type = T1;
	};

	template <class T1, class T2>
	class Select<true, T1, T2>
	{
		using Type = T2;
	};

	template <class T>
	concept NonRValue = !std::is_rvalue_reference_v<T>;

	template <class T>
	using LargeByRef = Select<(sizeof(T) <= 16), T&, T>::Type;

	template <NonRValue... Args>
	class Event
	{
	public:
		using CallbackType = std::function<void(Args...)>;

	public:
		void invoke(LargeByRef<Args>... args)
		{
			for (auto& callback : m_Callbacks)
				callback(args...);
		}

		void operator()(LargeByRef<Args>... args) { invoke(args...); }

		std::size_t attachCallback(const CallbackType& callback)
		{
			auto res = m_Callbacks.insert(callback);
			return res.second ? static_cast<std::size_t>((res.first - m_Callbacks.begin()) / sizeof(CallbackType)) : ~0ULL;
		}
		std::size_t attachCallback(CallbackType&& callback)
		{
			auto res = m_Callbacks.insert(std::move(callback));
			return res.second ? static_cast<std::size_t>((res.first - m_Callbacks.begin()) / sizeof(CallbackType)) : ~0ULL;
		}
		void detachCallback(const CallbackType& callback) { m_Callbacks.erase(callback); }
		void detachCallback(std::size_t id) { m_Callbacks.erase(m_Callbacks.begin() + id); }

		Event& operator+=(const CallbackType& callback) { attachCallback(callback); }
		Event& operator+=(CallbackType&& callback) { attachCallback(std::move(callback)); }
		Event& operator-=(const CallbackType& callback) { detachCallback(callback); }
		Event& operator-=(std::size_t id) { detachCallback(id); }

	private:
		std::set<CallbackType> m_Callbacks;
	};
} // namespace Utils