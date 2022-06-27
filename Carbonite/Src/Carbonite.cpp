#include "Carbonite.h"
#include "Input/Input.h"
#include "Renderer/RHISelector.h"
#include "Utils/Log.h"

Carbonite& Carbonite::Get()
{
	static Carbonite* s_Instance = new Carbonite();
	return *s_Instance;
}

void Carbonite::Destroy()
{
	delete &Get();
}

void Carbonite::GLFWJoystickCallback(int jid, int event)
{
	auto& inputs = Input::Inputs::Get();

	if (event == GLFW_CONNECTED)
	{
		bool          gamepad = glfwJoystickIsGamepad(jid);
		std::uint32_t axes    = 0;
		std::uint32_t buttons = 0;
		if (gamepad)
		{
			axes    = 6;
			buttons = 15;
		}
		else
		{
			int axisCount;
			int buttonCount;

			[[maybe_unused]] auto a = glfwGetJoystickAxes(jid, &axisCount);
			[[maybe_unused]] auto b = glfwGetJoystickButtons(jid, &buttonCount);

			axes    = static_cast<std::uint32_t>(axisCount);
			buttons = static_cast<std::uint32_t>(buttonCount);
		}
		inputs.joystickConnect(jid, jid + 1, axes, buttons, gamepad);

		Log::Debug("{} connected: {}, \"{}\"", gamepad ? "Gamepad" : "Joystick", jid + 1, glfwGetJoystickName(jid));
	}
	else if (event == GLFW_DISCONNECTED)
	{
		bool gamepad = inputs.getJoysticks()[jid].isGamepad();
		inputs.joystickDisconnect(jid);

		Log::Debug("{} disconnected: {}", gamepad ? "Gamepad" : "Joystick", jid + 1);
	}
}

void Carbonite::init()
{
	Log::Trace("Init");

	initJoysticks();

	m_Instance = Renderer::SelectRHI();
	m_Surface  = m_Instance->createSurface(m_Window);

	if (!m_Window.create())
		throw std::runtime_error("Failed to create window!");

	m_Device = m_Instance->createDevice(m_Surface.get());

	Input::CreateGroup("onFoot");
	Input::RegisterButtonBinding("toggleFullscreen", Input::Buttons::KeyF11());
	Input::RegisterButtonBinding("close", Input::Buttons::KeyEscape());
	Input::RegisterButtonBinding("toggleMenu", Input::Buttons::KeyI());
	Input::RegisterButtonAxis3DBinding("onFoot",
	                                   "movement",
	                                   Input::Buttons::KeyW(),
	                                   Input::Buttons::KeyS(),
	                                   Input::Buttons::KeyD(),
	                                   Input::Buttons::KeyA(),
	                                   Input::Buttons::KeyE(),
	                                   Input::Buttons::KeyQ());
	Input::RegisterAxis2DBinding("onFoot",
	                             "turn",
	                             Input::Axes::GamepadRightX(),
	                             Input::Axes::GamepadRightY(),
	                             Input::EAxisMode::Relative);
}

void Carbonite::run()
{
	Log::Trace("Run");

	Input::Inputs::Get().update();
	glfwPollEvents();
	updateJoysticks();
	Input::Inputs::Get().postUpdate();

	while (!m_Window.shouldClose())
	{
		if (Input::ButtonPressed("toggleMenu"))
		{
			Log::Trace("ToggledMenu");
			Input::ToggleGroup("onFoot");
		}

		if (Input::ButtonPressed("toggleFullscreen"))
		{
			Log::Trace("ToggledFullscreen");
			if (m_Window.isFullscreen())
				m_Window.restore();
			else
				m_Window.fullscreen();
		}

		m_Device->beginRendering();

		m_Device->endRendering();

		Input::Inputs::Get().update();
		glfwPollEvents();
		updateJoysticks();
		Input::Inputs::Get().postUpdate();

		if (Input::Button("close"))
			m_Window.requestClose();
	}
}

void Carbonite::deinit()
{
	Log::Trace("Deinit");

	m_Device->destroy();
	m_Window.destroy();
	m_Surface->destroy();
	m_Instance->destroy();
}

void Carbonite::initJoysticks()
{
	Log::Trace("Init Joysticks");

	std::vector<Input::Devices::Joystick> joysticks;
	joysticks.reserve(16);

	for (std::uint32_t i = 0; i < 16; ++i)
	{
		auto& joystick = joysticks.emplace_back();
		if (glfwJoystickPresent(i))
		{
			joystick.setID(i + 1);

			if (glfwJoystickIsGamepad(i))
			{
				joystick.setGamepad();
				joystick.resizeAxises(6);
				joystick.resizeButtons(15);
			}
			else
			{
				int  axisCount;
				auto axes = glfwGetJoystickAxes(i, &axisCount);
				int  buttonCount;
				auto buttons = glfwGetJoystickButtons(i, &buttonCount);

				joystick.resizeAxises(static_cast<std::uint32_t>(axisCount));
				joystick.resizeButtons(static_cast<std::uint32_t>(buttonCount));

				for (std::uint32_t j = 0; j < static_cast<std::uint32_t>(axisCount); ++j)
					joystick.setAxis(j, axes[j]);
				for (std::uint32_t j = 0; j < static_cast<std::uint32_t>(buttonCount); ++j)
				{
					if (buttons[j])
						joystick.buttonPressed(j);
					else
						joystick.buttonReleased(j);
				}
			}

			Log::Debug("{} connected: {}, \"{}\"", joystick.isGamepad() ? "Gamepad" : "Joystick", joystick.getID(), glfwGetJoystickName(i));
		}
	}

	Input::Inputs::Get().updateJoysticks(std::move(joysticks));

	glfwSetJoystickCallback(&Carbonite::GLFWJoystickCallback);
}

void Carbonite::updateJoysticks()
{
	auto& inputs = Input::Inputs::Get();
	for (std::uint32_t i = 0; i < 16; ++i)
	{
		auto joystick = inputs.getJoysticks()[i];

		if (!joystick.isConnected())
			continue;

		if (joystick.isGamepad())
		{
			GLFWgamepadstate state;
			if (!glfwGetGamepadState(i, &state))
				continue;

			for (std::uint32_t axis = 0; axis <= GLFW_GAMEPAD_AXIS_LAST; ++axis)
				inputs.joystickAxis(i, i + 1, axis, state.axes[axis]);

			for (std::uint32_t button = 0; button <= GLFW_GAMEPAD_BUTTON_LAST; ++button)
			{
				if (state.buttons[button])
				{
					if (!joystick.isButtonDown(button))
						inputs.joystickButtonPressed(i, i + 1, button);
				}
				else if (joystick.isButtonDown(button))
				{
					inputs.joystickButtonReleased(i, i + 1, button);
				}
			}
		}
		else
		{
			int  axisCount;
			auto axes = glfwGetJoystickAxes(i, &axisCount);
			int  buttonCount;
			auto buttons = glfwGetJoystickButtons(i, &buttonCount);

			for (std::uint32_t axis = 0; axis < static_cast<std::uint32_t>(axisCount); ++axis)
				inputs.joystickAxis(i, i + 1, axis, axes[axis]);
			for (std::uint32_t button = 0; button < static_cast<std::uint32_t>(buttonCount); ++button)
			{
				if (buttons[button])
				{
					if (!joystick.isButtonDown(button))
						inputs.joystickButtonPressed(i, i + 1, button);
				}
				else if (joystick.isButtonDown(button))
				{
					inputs.joystickButtonReleased(i, i + 1, button);
				}
			}
		}
	}
}

Carbonite::Carbonite()
{
	init();
}

Carbonite::~Carbonite()
{
	deinit();
}