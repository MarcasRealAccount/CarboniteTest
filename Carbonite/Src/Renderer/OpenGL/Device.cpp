#include "Device.h"
#include "Surface.h"

#include <glad/glad.h>

namespace
{
	static bool s_GLLoaded = false;
}

namespace Renderer::OpenGL
{
	static void LoadGL()
	{
		if (s_GLLoaded)
			return;

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(&glfwGetProcAddress)))
			throw std::runtime_error("GLAD failed to load OpenGL!");
	}

	Device::Device(RHI::ISurface* surface)
	    : RHI::IDevice(surface)
	{
		makeContextCurrent();
		LoadGL();
	}

	void Device::makeContextCurrent()
	{
		static_cast<Surface*>(m_Surface)->makeContextCurrent();
	}

	void Device::beginRendering()
	{
		makeContextCurrent();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Device::endRendering()
	{
		static_cast<Surface*>(m_Surface)->swapBuffers();
	}
} // namespace Renderer::OpenGL