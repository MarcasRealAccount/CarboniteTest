#pragma once

#include "ForwardDecl.h"
#include "RHINode.h"

#include <concepts>
#include <memory>

class Window;

namespace Renderer::RHI
{
	class ISurface : public RHINode
	{
	public:
		ISurface(IInstance* instance, Window* window);

		template <std::derived_from<IInstance> T>
		T* getInstance() const
		{
			return static_cast<T*>(m_Instance);
		}
		auto getWindow() const { return m_Window; }

	private:
		IInstance* m_Instance;
		Window*    m_Window;
	};
} // namespace Renderer::RHI