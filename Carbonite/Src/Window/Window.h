#pragma once

#include <cstdint>

#include <string>

namespace Renderer::RHI
{
	class ISurface;
}

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

enum class EWindowState
{
	Normal,
	Iconified,
	Maximized,
	Fullscreen
};

struct WindowData
{
public:
	std::uint32_t m_Width = 1280, m_Height = 720;
	std::uint32_t m_FBWidth = 0, m_FBHeight = 0;
	std::int32_t  m_X = 1 << 31, m_Y = 1 << 31;
	EWindowState  m_State = EWindowState::Normal;
};

class Window
{
public:
	friend Renderer::RHI::ISurface;

private:
	static void PosCallback(GLFWwindow* window, int x, int y);
	static void SizeCallback(GLFWwindow* window, int width, int height);
	static void IconifyCallback(GLFWwindow* window, int iconified);
	static void MaximizeCallback(GLFWwindow* window, int maximized);
	static void FBSizeCallback(GLFWwindow* window, int fbWidth, int fbHeight);

	static void KeyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
	static void CursorPosCallback(GLFWwindow* window, double x, double y);
	static void ScrollCallback(GLFWwindow* window, double x, double y);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
	Window(std::uint32_t width = 1280, std::uint32_t height = 720, const std::string& title = "Carbonite");
	Window(std::uint32_t width, std::uint32_t height, std::string&& title);
	~Window();

	void setPos(std::int32_t x, std::int32_t y);
	void setSize(std::uint32_t width, std::uint32_t height);
	void setTitle(const std::string& title);
	void setTitle(std::string&& title);

	void restore();
	void iconify();
	void maximize();
	void fullscreen();

	bool create();
	void destroy();

	void requestClose();
	bool shouldClose() const;

	GLFWmonitor*       getBestMonitor() const;
	const GLFWvidmode* getBestVideoMode(GLFWmonitor* monitor) const;

	auto& getData() const { return m_Data; }
	bool  isIconified() const { return m_Data.m_State == EWindowState::Iconified; }
	bool  isMaximized() const { return m_Data.m_State == EWindowState::Maximized; }
	bool  isFullscreen() const { return m_Data.m_State == EWindowState::Fullscreen; }
	auto& getTitle() const { return m_Title; }
	auto  getNative() const { return m_Native; }
	auto  getSurface() const { return m_Surface; }

private:
	WindowData m_Data;
	WindowData m_PData {};

	std::string m_Title;

	GLFWwindow* m_Native;

	Renderer::RHI::ISurface* m_Surface;
};