#include "IDevice.h"
#include "ISurface.h"

namespace Renderer::RHI
{
	IDevice::IDevice(ISurface* surface)
	    : m_Surface(surface)
	{
		if (!surface)
			throw std::runtime_error("Renderer::RHI::IDevice expects surface to not be nullptr!");
		m_Surface->m_Device = this;
	}
} // namespace Renderer::RHI