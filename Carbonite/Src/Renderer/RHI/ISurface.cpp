#include "ISurface.h"
#include "IInstance.h"
#include "Window/Window.h"

namespace Renderer::RHI
{
	ISurface::ISurface(IInstance* instance, Window* window)
	    : RHINode("Window"), m_Instance(instance), m_Window(window)
	{
		m_Window->m_Surface = this;
		m_Instance->attachChild(this);
	}
} // namespace Renderer::RHI