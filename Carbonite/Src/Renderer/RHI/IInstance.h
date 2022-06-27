#pragma once

#include "ForwardDecl.h"
#include "RHINode.h"

#include <concepts>
#include <memory>

class Window;

namespace Renderer::RHI
{
	class IInstance : public RHINode
	{
	public:
		IInstance(const std::string& name, IRHI* rhi);
		IInstance(std::string&& name, IRHI* rhi);

		virtual std::unique_ptr<ISurface> newSurface(Window& window) = 0;
		virtual std::unique_ptr<IDevice>  newDevice()                = 0;

		template <std::derived_from<IRHI> T>
		T* getRHI() const
		{
			return static_cast<T*>(m_RHI);
		}

	private:
		IRHI* m_RHI;
	};
} // namespace Renderer::RHI