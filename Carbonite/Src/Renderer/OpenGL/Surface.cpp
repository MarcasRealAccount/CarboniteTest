#include "Surface.h"
#include "Instance.h"
#include "Window/Window.h"

namespace Renderer::OpenGL
{
	Surface::Surface(RHI::IInstance* instance, Window* window)
	    : RHI::ISurface(instance, window)
	{
		window->setShare(getInstance<Instance>()->getHiddenWindow());
	}
} // namespace Renderer::OpenGL