#pragma once

class Window;

namespace Renderer::RHI
{
	class IDevice;

	class ISurface
	{
	public:
		friend IDevice;

	public:
		ISurface(Window* window);
		ISurface(const ISurface&) = delete;
		ISurface(ISurface&&)      = delete;
		virtual ~ISurface()       = default;

		virtual void destroy() = 0;

		virtual void setWindowHints() = 0;

		auto getWindow() const { return m_Window; }
		auto getDevice() const { return m_Device; }

	protected:
		Window* m_Window;

		IDevice* m_Device;
	};
} // namespace Renderer::RHI