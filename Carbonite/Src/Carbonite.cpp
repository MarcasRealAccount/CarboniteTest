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

void Carbonite::init()
{
	Log::Trace("Init");

	m_Instance = Renderer::SelectRHI();
	m_Surface  = m_Instance->createSurface(m_Window);

	if (!m_Window.create())
		throw std::runtime_error("Failed to create window!");

	m_Device = m_Instance->createDevice(m_Surface.get());

	Input::RegisterButtonBinding("close", Input::Buttons::KeyEscape);
	Input::RegisterButtonBinding("toggleMenu", Input::Buttons::KeyI);
	Input::RegisterButtonAxis3DBinding("onFoot",
	                                   "movement",
	                                   Input::Binding { Input::EInputLocation::Keyboard, 0, Input::Buttons::KeyW },
	                                   Input::Binding { Input::EInputLocation::Keyboard, 0, Input::Buttons::KeyS },
	                                   Input::Binding { Input::EInputLocation::Keyboard, 0, Input::Buttons::KeyD },
	                                   Input::Binding { Input::EInputLocation::Keyboard, 0, Input::Buttons::KeyA },
	                                   Input::Binding { Input::EInputLocation::Keyboard, 0, Input::Buttons::KeyE },
	                                   Input::Binding { Input::EInputLocation::Keyboard, 0, Input::Buttons::KeyQ });
}

void Carbonite::run()
{
	Log::Trace("Run");

	Input::Inputs::Get().updateGrouped();
	glfwPollEvents();
	Input::Inputs::Get().postUpdateGrouped();

	while (!m_Window.shouldClose())
	{
		if (Input::ButtonPressed("toggleMenu"))
		{
			Log::Trace("ToggledMenu");
			Input::ToggleGroup("onFoot");
		}

		Log::Debug("Movement {}", Input::Axis3D("onFoot", "movement"));

		m_Device->beginRendering();

		m_Device->endRendering();

		Input::Inputs::Get().updateGrouped();
		glfwPollEvents();
		Input::Inputs::Get().postUpdateGrouped();

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

Carbonite::Carbonite()
{
	init();
}

Carbonite::~Carbonite()
{
	deinit();
}