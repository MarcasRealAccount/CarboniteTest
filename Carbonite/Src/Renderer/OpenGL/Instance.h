#pragma once

#include "Renderer/RHI/IInstance.h"

struct GLFWwindow;

namespace Renderer::OpenGL
{
	class Instance final : public RHI::IInstance
	{
	public:
		Instance(const std::string& name, RHI::IRHI* rhi);
		Instance(std::string&& name, RHI::IRHI* rhi);

		virtual std::unique_ptr<RHI::ISurface> newSurface(Window& window) override;
		virtual std::unique_ptr<RHI::IDevice>  newDevice() override;

		auto getHiddenWindow() const { return m_HiddenWindow; }

	private:
		virtual void createImpl() override;
		virtual void destroyImpl() override;
		virtual bool isDestructible() { return true; }
		virtual bool isValid() { return m_HiddenWindow; }

	private:
		GLFWwindow* m_HiddenWindow;
	};
} // namespace Renderer::OpenGL