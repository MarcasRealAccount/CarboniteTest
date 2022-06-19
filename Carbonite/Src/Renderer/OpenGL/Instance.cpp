#include "Instance.h"
#include "Device.h"
#include "Surface.h"

namespace Renderer::OpenGL
{
	std::unique_ptr<RHI::ISurface> Instance::createSurface(Window& window)
	{
		return std::make_unique<Surface>(&window);
	}

	std::unique_ptr<RHI::IDevice> Instance::createDevice(RHI::ISurface* surface)
	{
		return std::make_unique<Device>(surface);
	}
} // namespace Renderer::OpenGL