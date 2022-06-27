#pragma once

#include "Renderer/RHI/IRHI.h"

namespace Renderer::OpenGL
{
	class OpenGLRHI final : public RHI::IRHI
	{
	public:
		OpenGLRHI();

		virtual bool isCompatible() override;
		virtual void setWindowHints(Window& window) override;

		virtual std::unique_ptr<RHI::IInstance> newInstance(std::string&& name) override;
	};
} // namespace Renderer::OpenGL