#include "Surface.h"
#include "Window/Window.h"

namespace Renderer::OpenGL
{
	Surface::Surface(Window* window)
	    : RHI::ISurface(window)
	{
	}

	void Surface::makeContextCurrent()
	{
		glfwMakeContextCurrent(m_Window->getNative());
	}

	void Surface::swapBuffers()
	{
		glfwSwapBuffers(m_Window->getNative());
	}

	void Surface::setWindowHints()
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // Macos is bad :sad:
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	}
} // namespace Renderer::OpenGL