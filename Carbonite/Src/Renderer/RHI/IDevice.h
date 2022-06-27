#pragma once

#include "ForwardDecl.h"
#include "RHINode.h"

#include <concepts>
#include <memory>

namespace Renderer::RHI
{
	class IDevice : public RHINode
	{
	public:
		IDevice(const std::string& name, IInstance* instance);
		IDevice(std::string&& name, IInstance* instance);

		virtual bool supportsRayTracing() const { return false; }

		template <std::derived_from<IInstance> T>
		T* getInstance() const
		{
			return static_cast<T*>(m_Instance);
		}

	protected:
		IInstance* m_Instance;
	};
} // namespace Renderer::RHI