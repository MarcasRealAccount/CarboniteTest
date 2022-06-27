#include "Instance.h"
#include "Device.h"
#include "Renderer/RHI/IRHI.h"
#include "Surface.h"
#include "Utils/Exception.h"
#include "Window/Window.h"

namespace Renderer::OpenGL
{
	Instance::Instance(const std::string& name, RHI::IRHI* rhi)
	    : RHI::IInstance(name, rhi), m_HiddenWindow(nullptr) {}

	Instance::Instance(std::string&& name, RHI::IRHI* rhi)
	    : RHI::IInstance(std::move(name), rhi), m_HiddenWindow(nullptr) {}

	std::unique_ptr<RHI::ISurface> Instance::newSurface(Window& window)
	{
		return std::make_unique<Surface>(this, &window);
	}

	std::unique_ptr<RHI::IDevice> Instance::newDevice()
	{
		return std::make_unique<Device>(this);
	}

	void Instance::createImpl()
	{
		glfwDefaultWindowHints();
		getRHI<RHI::IRHI>()->setWindowHints(*reinterpret_cast<Window*>(0));
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		m_HiddenWindow = glfwCreateWindow(100, 100, "HiddenGLContext", nullptr, nullptr);
		if (!m_HiddenWindow)
			throw Utils::Exception("Failed to create hidden OpenGL context");

		glfwMakeContextCurrent(m_HiddenWindow);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(&glfwGetProcAddress)))
			throw Utils::Exception("Failed to load OpenGL functions");
	}

	void Instance::destroyImpl()
	{
		if (m_HiddenWindow)
			glfwDestroyWindow(m_HiddenWindow);
	}
} // namespace Renderer::OpenGL