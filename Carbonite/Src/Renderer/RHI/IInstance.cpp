#include "IInstance.h"
#include "IRHI.h"

namespace Renderer::RHI
{
	IInstance::IInstance(const std::string& name, IRHI* rhi)
	    : RHINode(name), m_RHI(rhi)
	{
		m_RHI->attachChild(this);
	}

	IInstance::IInstance(std::string&& name, IRHI* rhi)
	    : RHINode(std::move(name)), m_RHI(rhi)
	{
		m_RHI->attachChild(this);
	}
} // namespace Renderer::RHI