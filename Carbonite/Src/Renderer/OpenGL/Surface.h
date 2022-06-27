#pragma once

#include "Renderer/RHI/ISurface.h"

namespace Renderer::OpenGL
{
	class Surface final : public RHI::ISurface
	{
	public:
		Surface(RHI::IInstance* instance, Window* window);
	};
} // namespace Renderer::OpenGL