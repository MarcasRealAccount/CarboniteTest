#include "ISurface.h"
#include "Utils/Core.h"
#include "Window/Window.h"

#include <stdexcept>

namespace Renderer::RHI
{
	ISurface::ISurface(Window* window)
	    : m_Window(window), m_Device(nullptr)
	{
		if (!window)
			throw std::runtime_error("Renderer::RHI::ISurface expects window to not be nullptr!");
		window->m_Surface = this;
	}
} // namespace Renderer::RHI