#pragma once

class Window;

namespace Renderer::RHI
{
	class ISurface;
	class IDevice;

	class IInstance
	{
	public:
		IInstance()                 = default;
		IInstance(const IInstance&) = delete;
		IInstance(IInstance&&)      = delete;
		virtual ~IInstance()        = default;

		virtual void destroy() = 0;

		virtual std::unique_ptr<ISurface> createSurface(Window& window)   = 0;
		virtual std::unique_ptr<IDevice>  createDevice(ISurface* surface) = 0;
	};
} // namespace Renderer::RHI