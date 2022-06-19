#pragma once

#include "Renderer/RHI/IInstance.h"

namespace Renderer::OpenGL
{
	class Instance : public RHI::IInstance
	{
	public:
		Instance()          = default;
		virtual ~Instance() = default;

		virtual void destroy() override {};

		virtual std::unique_ptr<RHI::ISurface> createSurface(Window& window) override;
		virtual std::unique_ptr<RHI::IDevice>  createDevice(RHI::ISurface* surface) override;
	};
} // namespace Renderer::OpenGL