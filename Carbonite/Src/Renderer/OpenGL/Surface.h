#pragma once

#include "Renderer/RHI/ISurface.h"

namespace Renderer::OpenGL
{
	class Surface : public RHI::ISurface
	{
	public:
		Surface(Window* window);
		virtual ~Surface() = default;

		virtual void destroy() override {}

		void makeContextCurrent();
		void swapBuffers();

		virtual void setWindowHints() override;
	};
} // namespace Renderer::OpenGL