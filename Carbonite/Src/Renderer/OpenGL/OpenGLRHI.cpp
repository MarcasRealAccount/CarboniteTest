#include "OpenGLRHI.h"
#include "Instance.h"

#include <GLFW/glfw3.h>

namespace Renderer::OpenGL
{
	OpenGLRHI::OpenGLRHI()
	    : IRHI("OpenGL") {}

	bool OpenGLRHI::isCompatible()
	{
		glfwDefaultWindowHints();
		setWindowHints(*reinterpret_cast<Window*>(0));
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		GLFWwindow* window = glfwCreateWindow(100, 100, "GLCompatTester", nullptr, nullptr);
		if (!window)
			return false;

		glfwDestroyWindow(window);
		return true;
	}

	void OpenGLRHI::setWindowHints([[maybe_unused]] Window& window)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	}

	std::unique_ptr<RHI::IInstance> OpenGLRHI::newInstance(std::string&& name)
	{
		return std::make_unique<Instance>(std::move(name), this);
	}
} // namespace Renderer::OpenGL