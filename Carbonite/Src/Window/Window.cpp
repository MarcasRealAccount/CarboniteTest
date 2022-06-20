#include "Window.h"
#include "Input/Input.h"
#include "Renderer/RHI/ISurface.h"
#include "Utils/Log.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static struct GLFWInitializer
{
public:
	static void ErrorCallback(int code, const char* message)
	{
		s_Logger->error("{}: {}", code, message);
	}

private:
	static inline std::shared_ptr<spdlog::logger> s_Logger = Log::CreateLogger("GLFW");

public:
	GLFWInitializer()
	{
		s_Logger->trace("Init");
		glfwSetErrorCallback(&GLFWInitializer::ErrorCallback);
		m_Success = glfwInit();
	}
	~GLFWInitializer()
	{
		s_Logger->trace("Deinit");
		glfwTerminate();
	}

private:
	bool m_Success = false;
} s_GLFWInitializer;

void Window::PosCallback(GLFWwindow* window, int x, int y)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (wnd->m_Data.m_X != x || wnd->m_Data.m_Y != y)
		wnd->e_Pos(x, y);
	wnd->m_Data.m_X = x;
	wnd->m_Data.m_Y = y;
}

void Window::SizeCallback(GLFWwindow* window, int width, int height)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (wnd->m_Data.m_Width != width || wnd->m_Data.m_Height != height)
		wnd->e_Size(static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height));
	wnd->m_Data.m_Width  = width;
	wnd->m_Data.m_Height = height;
}

void Window::IconifyCallback(GLFWwindow* window, int iconified)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (iconified)
	{
		wnd->e_State(EWindowState::Iconified);
		wnd->m_Data.m_State = EWindowState::Iconified;
	}
	else if (wnd->m_Data.m_State == EWindowState::Iconified)
	{
		wnd->e_State(EWindowState::Normal);
		wnd->m_Data.m_State = EWindowState::Normal;
	}
}

void Window::MaximizeCallback(GLFWwindow* window, int maximized)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (maximized)
	{
		wnd->e_State(EWindowState::Maximized);
		wnd->m_Data.m_State = EWindowState::Maximized;
	}
	else if (wnd->m_Data.m_State == EWindowState::Maximized)
	{
		wnd->e_State(EWindowState::Normal);
		wnd->m_Data.m_State = EWindowState::Normal;
	}
}

void Window::FBSizeCallback(GLFWwindow* window, int fbWidth, int fbHeight)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (wnd->m_Data.m_FBWidth != fbWidth || wnd->m_Data.m_FBHeight != fbHeight)
		wnd->e_FBSize(static_cast<std::uint32_t>(fbWidth), static_cast<std::uint32_t>(fbHeight));
	wnd->m_Data.m_FBWidth  = fbWidth;
	wnd->m_Data.m_FBHeight = fbHeight;
}

void Window::KeyCallback([[maybe_unused]] GLFWwindow* window, int keycode, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Input::Inputs::Get().keyPressed(static_cast<std::uint32_t>(keycode));
		break;
	case GLFW_REPEAT:
		Input::Inputs::Get().keyRepeat(static_cast<std::uint32_t>(keycode));
		break;
	case GLFW_RELEASE:
		Input::Inputs::Get().keyReleased(static_cast<std::uint32_t>(keycode));
		break;
	}
}

void Window::CursorPosCallback([[maybe_unused]] GLFWwindow* window, double x, double y)
{
	Input::Inputs::Get().mouseMove(static_cast<float>(x), static_cast<float>(y));
}

void Window::ScrollCallback([[maybe_unused]] GLFWwindow* window, double x, double y)
{
	Input::Inputs::Get().mouseScroll(static_cast<float>(x), static_cast<float>(y));
}

void Window::MouseButtonCallback([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Input::Inputs::Get().mouseButtonPressed(static_cast<std::uint32_t>(button));
		break;
	case GLFW_RELEASE:
		Input::Inputs::Get().mouseButtonReleased(static_cast<std::uint32_t>(button));
		break;
	}
}

Window::Window(std::uint32_t width, std::uint32_t height, const std::string& title)
    : m_Data({ width, height }), m_Title(title), m_Native(nullptr), m_Surface(nullptr)
{
}

Window::Window(std::uint32_t width, std::uint32_t height, std::string&& title)
    : m_Data({ width, height }), m_Title(std::move(title)), m_Native(nullptr), m_Surface(nullptr)
{
}

Window::~Window()
{
	destroy();
}

void Window::setPos(std::int32_t x, std::int32_t y)
{
	if (m_Native)
	{
		glfwSetWindowPos(m_Native, x, y);
	}
	else
	{
		m_Data.m_X = x;
		m_Data.m_Y = y;
	}
}

void Window::setSize(std::uint32_t width, std::uint32_t height)
{
	if (m_Native)
	{
		glfwSetWindowSize(m_Native, static_cast<int>(width), static_cast<int>(height));
	}
	else
	{
		m_Data.m_Width  = width;
		m_Data.m_Height = height;
	}
}

void Window::setTitle(const std::string& title)
{
	setTitle(std::string { title }); // Call move variant
}

void Window::setTitle(std::string&& title)
{
	m_Title = std::move(title);
	if (m_Native)
		glfwSetWindowTitle(m_Native, m_Title.c_str());
}

void Window::restore()
{
	if (m_Data.m_State == EWindowState::Normal)
		return;

	if (m_Native)
	{
		if (m_Data.m_State == EWindowState::Fullscreen)
		{
			glfwSetWindowMonitor(m_Native, nullptr, m_PData.m_X, m_PData.m_Y, m_PData.m_Width, m_PData.m_Height, 0);

			switch (m_PData.m_State)
			{
			case EWindowState::Iconified:
				glfwIconifyWindow(m_Native);
				break;
			case EWindowState::Maximized:
				glfwMaximizeWindow(m_Native);
				break;
			default:
				e_State(m_PData.m_State);
				m_Data.m_State = m_PData.m_State;
				break;
			}
		}
		else
		{
			glfwRestoreWindow(m_Native);
		}
	}
	else
	{
		m_Data.m_State = EWindowState::Normal;
	}
}

void Window::iconify()
{
	if (m_Data.m_State == EWindowState::Iconified)
		return;

	if (m_Native)
		glfwIconifyWindow(m_Native);
	else
		m_Data.m_State = EWindowState::Iconified;
}

void Window::maximize()
{
	if (m_Data.m_State == EWindowState::Maximized)
		return;

	if (m_Native)
		glfwMaximizeWindow(m_Native);
	else
		m_Data.m_State = EWindowState::Maximized;
}

void Window::fullscreen()
{
	if (m_Data.m_State == EWindowState::Fullscreen)
		return;

	if (m_Native)
	{
		GLFWmonitor*       monitor = getBestMonitor();
		const GLFWvidmode* vidmode = getBestVideoMode(monitor);

		m_PData = m_Data;
		glfwSetWindowMonitor(m_Native, monitor, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
	}

	e_State(EWindowState::Fullscreen);
	m_Data.m_State = EWindowState::Fullscreen;
}

bool Window::create()
{
	if (m_Native)
		return true;

	glfwDefaultWindowHints();
	if (!m_Surface)
		throw std::runtime_error("Window::create() expected surface to be created first!");
	m_Surface->setWindowHints();

	GLFWmonitor* monitor = getBestMonitor();

	int mx = 0, my = 0, mw = 0, mh = 0;
	glfwGetMonitorWorkarea(monitor, &mx, &my, &mw, &mh);

	m_Data.m_X = m_Data.m_X == 1 << 31 ? mx + (mw - m_Data.m_Width) / 2 : m_Data.m_X;
	m_Data.m_Y = m_Data.m_Y == 1 << 31 ? my + (mh - m_Data.m_Height) / 2 : m_Data.m_Y;

	if (m_Data.m_State == EWindowState::Fullscreen)
	{
		const GLFWvidmode* vidmode = getBestVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

		m_PData = m_Data;

		m_Native = glfwCreateWindow(vidmode->width, vidmode->height, m_Title.c_str(), monitor, nullptr);
	}
	else
	{
		m_Native = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Title.c_str(), nullptr, nullptr);
	}

	if (!m_Native)
		return false;

	glfwSetWindowPos(m_Native, m_Data.m_X, m_Data.m_Y);

	switch (m_Data.m_State)
	{
	case EWindowState::Iconified:
		glfwIconifyWindow(m_Native);
		break;
	case EWindowState::Maximized:
		glfwMaximizeWindow(m_Native);
		break;
	}

	int fw, fh;
	glfwGetFramebufferSize(m_Native, &fw, &fh);
	m_Data.m_FBWidth  = fw;
	m_Data.m_FBHeight = fh;

	glfwSetWindowUserPointer(m_Native, this);

	glfwSetWindowPosCallback(m_Native, &Window::PosCallback);
	glfwSetWindowSizeCallback(m_Native, &Window::SizeCallback);
	glfwSetWindowIconifyCallback(m_Native, &Window::IconifyCallback);
	glfwSetWindowMaximizeCallback(m_Native, &Window::MaximizeCallback);
	glfwSetFramebufferSizeCallback(m_Native, &Window::FBSizeCallback);

	glfwSetKeyCallback(m_Native, &Window::KeyCallback);
	glfwSetCursorPosCallback(m_Native, &Window::CursorPosCallback);
	glfwSetScrollCallback(m_Native, &Window::ScrollCallback);
	glfwSetMouseButtonCallback(m_Native, &Window::MouseButtonCallback);

	return true;
}

void Window::destroy()
{
	if (!m_Native)
		return;

	glfwDestroyWindow(m_Native);
	m_Native = nullptr;
}

void Window::requestClose()
{
	glfwSetWindowShouldClose(m_Native, true);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_Native);
}

GLFWmonitor* Window::getBestMonitor() const
{
	if (!m_Native)
		return glfwGetPrimaryMonitor();

	GLFWmonitor* bestMonitor = glfwGetWindowMonitor(m_Native);
	if (bestMonitor)
		return bestMonitor;
	std::uint64_t bestArea = 0;

	int           monitorCount = 0;
	GLFWmonitor** monitors     = glfwGetMonitors(&monitorCount);

	int           mx = 0, my = 0, mw = 0, mh = 0;
	std::int32_t  wx = m_Data.m_X, wy = m_Data.m_Y;
	std::uint32_t ww = m_Data.m_Width, wh = m_Data.m_Height;
	for (int i = 0; i < monitorCount; ++i)
	{
		GLFWmonitor* monitor = monitors[i];
		glfwGetMonitorWorkarea(monitor, &mx, &my, &mw, &mh);

		std::uint64_t ax = std::max<std::uint64_t>(wx, mx);
		std::uint64_t ay = std::max<std::uint64_t>(wy, my);
		std::uint64_t bx = std::min<std::uint64_t>(static_cast<std::uint64_t>(wx) + ww, static_cast<std::uint64_t>(mx) + mw);
		std::uint64_t by = std::min<std::uint64_t>(static_cast<std::uint64_t>(wy) + wh, static_cast<std::uint64_t>(my) + mh);
		if (bx < ax || by < ay)
			continue;
		std::uint64_t area = (bx - ax) * (by - ay);
		if (area > bestArea)
		{
			bestMonitor = monitor;
			bestArea    = area;
		}
	}

	return bestMonitor ? bestMonitor : glfwGetPrimaryMonitor();
}

const GLFWvidmode* Window::getBestVideoMode(GLFWmonitor* monitor) const
{
	return glfwGetVideoMode(monitor);
}