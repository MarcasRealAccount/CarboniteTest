#pragma once

#include "Renderer/RHI/ForwardDecl.h"
#include "Window/Window.h"

class Carbonite final
{
public:
	static Carbonite& Get();
	static void       Destroy();

private:
	static void GLFWJoystickCallback(int jid, int event);

public:
	void init();
	void run();
	void deinit();

	void initJoysticks();
	void updateJoysticks();

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