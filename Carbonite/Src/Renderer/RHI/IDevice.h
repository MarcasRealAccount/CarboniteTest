#pragma once

namespace Renderer::RHI
{
	class ISurface;

	class IDevice
	{
	public:
		IDevice(ISurface* surface);
		IDevice(const IDevice&) = delete;
		IDevice(IDevice&&)      = delete;
		virtual ~IDevice()      = default;

		virtual void destroy() = 0;

		virtual void beginRendering() = 0;
		virtual void endRendering()   = 0;

		auto getSurface() const { return m_Surface; }

	protected:
		ISurface* m_Surface;
	};
} // namespace Renderer::RHI