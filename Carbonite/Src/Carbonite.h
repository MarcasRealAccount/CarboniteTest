#pragma once

#include "Renderer/RHI/IDevice.h"
#include "Renderer/RHI/IInstance.h"
#include "Renderer/RHI/ISurface.h"
#include "Window/Window.h"

class Carbonite final
{
public:
	static Carbonite& Get();
	static void       Destroy();

public:
	void init();
	void run();
	void deinit();

	auto getInstance() const { return m_Instance.get(); }
	auto getSurface() const { return m_Surface.get(); }
	auto getDevice() const { return m_Device.get(); }

private:
	Carbonite();
	~Carbonite();

private:
	Window m_Window;

	std::unique_ptr<Renderer::RHI::IInstance> m_Instance;
	std::unique_ptr<Renderer::RHI::ISurface>  m_Surface;
	std::unique_ptr<Renderer::RHI::IDevice>   m_Device;
};