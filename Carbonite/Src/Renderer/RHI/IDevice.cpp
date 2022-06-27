#include "IDevice.h"
#include "IInstance.h"
#include "Window/Window.h"

namespace Renderer::RHI
{
	IDevice::IDevice(const std::string& name, IInstance* instance)
	    : RHINode(name), m_Instance(instance)
	{
		m_Instance->attachChild(this);
	}

	IDevice::IDevice(std::string&& name, IInstance* instance)
	    : RHINode(std::move(name)), m_Instance(instance)
	{
		m_Instance->attachChild(this);
	}
} // namespace Renderer::RHI