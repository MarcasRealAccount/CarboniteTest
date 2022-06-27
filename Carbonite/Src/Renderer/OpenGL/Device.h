#pragma once

#include "Renderer/RHI/IDevice.h"

namespace Renderer::OpenGL
{
	class Device final : public RHI::IDevice
	{
	public:
		Device(RHI::IInstance* instance);

	private:
		virtual void createImpl() override;
		virtual void destroyImpl() override;
	};
} // namespace Renderer::OpenGL