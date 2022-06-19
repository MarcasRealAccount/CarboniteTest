#pragma once

#include "Renderer/RHI/IDevice.h"

namespace Renderer::OpenGL
{
	class Device : public RHI::IDevice
	{
	public:
		Device(RHI::ISurface* surface);
		virtual ~Device() = default;

		virtual void destroy() override {}

		void makeContextCurrent();

		virtual void beginRendering() override;
		virtual void endRendering() override;
	};
} // namespace Renderer::OpenGL