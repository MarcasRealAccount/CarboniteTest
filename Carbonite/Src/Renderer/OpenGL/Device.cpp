#include "Device.h"
#include "Instance.h"
#include "Window/Window.h"

namespace Renderer::OpenGL
{
	Device::Device(RHI::IInstance* instance)
	    : RHI::IDevice("OpenGL Device", instance) {}

	void Device::createImpl()
	{
		setName(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	}

	void Device::destroyImpl()
	{
		setName("OpenGL Device");
	}
} // namespace Renderer::OpenGL