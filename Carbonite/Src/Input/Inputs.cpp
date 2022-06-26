#include "Inputs.h"

namespace Input
{
	Inputs& Inputs::Get()
	{
		static Inputs* s_Instance = new Inputs();
		return *s_Instance;
	}

	void Inputs::Destroy()
	{
		delete &Get();
	}

	void Inputs::updateJoysticks(std::vector<Devices::Joystick>&& joysticks)
	{
		m_Joysticks = std::move(joysticks);
	}

	void Inputs::update()
	{
		updateGroup();
		for (auto& [name, group] : m_Groups)
			group.updateGroup();

		m_Keyboard.update();
		m_Mouse.update();
	}

	void Inputs::postUpdate()
	{
		postUpdateGroup();
		for (auto& [name, group] : m_Groups)
			group.postUpdateGroup();
	}

	void Inputs::keyPressed(std::uint32_t key)
	{
		m_Keyboard.keyPressed(key);
		setButton(Binding { EInputLocation::Keyboard, 0, key }, m_Keyboard.getState(key));
	}

	void Inputs::keyRepeated(std::uint32_t key)
	{
		m_Keyboard.keyRepeated(key);
		setButton(Binding { EInputLocation::Keyboard, 0, key }, m_Keyboard.getState(key));
	}

	void Inputs::keyReleased(std::uint32_t key)
	{
		m_Keyboard.keyReleased(key);
		setButton(Binding { EInputLocation::Keyboard, 0, key }, m_Keyboard.getState(key));
	}

	void Inputs::mouseMove(float x, float y)
	{
		m_Mouse.setAxis(Axes::MouseX, x);
		m_Mouse.setAxis(Axes::MouseY, y);
		setAxis(Binding { EInputLocation::Mouse, 0, Axes::MouseX }, x);
		setAxis(Binding { EInputLocation::Mouse, 0, Axes::MouseY }, y);
	}

	void Inputs::mouseScroll(float x, float y)
	{
		m_Mouse.setAxis(Axes::MouseWheelX, x);
		m_Mouse.setAxis(Axes::MouseWheelY, y);
		setAxis(Binding { EInputLocation::Mouse, 0, Axes::MouseWheelX }, x);
		setAxis(Binding { EInputLocation::Mouse, 0, Axes::MouseWheelY }, y);
	}

	void Inputs::mouseButtonPressed(std::uint32_t button)
	{
		m_Mouse.buttonPressed(button);
		setButton(Binding { EInputLocation::Mouse, 0, button }, m_Mouse.getState(button));
	}

	void Inputs::mouseButtonRepeated(std::uint32_t button)
	{
		m_Mouse.buttonRepeated(button);
		setButton(Binding { EInputLocation::Mouse, 0, button }, m_Mouse.getState(button));
	}

	void Inputs::mouseButtonReleased(std::uint32_t button)
	{
		m_Mouse.buttonReleased(button);
		setButton(Binding { EInputLocation::Mouse, 0, button }, m_Mouse.getState(button));
	}

	void Inputs::joystickConnect(std::uint32_t index, std::uint32_t id, std::uint32_t axes, std::uint32_t buttons, bool gamepad)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.setID(id);
		if (gamepad)
			joystick.setGamepad();
		joystick.resizeAxises(axes);
		joystick.resizeButtons(buttons);
	}

	void Inputs::joystickDisconnect(std::uint32_t index)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.setID(0);
	}

	void Inputs::joystickAxis(std::uint32_t index, std::uint32_t id, std::uint32_t axis, float value)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.setAxis(axis, value);
		setAxis(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, axis }, value);
	}

	void Inputs::joystickButtonPressed(std::uint32_t index, std::uint32_t id, std::uint32_t button)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.buttonPressed(button);
		setButton(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, button }, joystick.getState(button));
	}

	void Inputs::joystickButtonRepeated(std::uint32_t index, std::uint32_t id, std::uint32_t button)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.buttonRepeated(button);
		setButton(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, button }, joystick.getState(button));
	}

	void Inputs::joystickButtonReleased(std::uint32_t index, std::uint32_t id, std::uint32_t button)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.buttonReleased(button);
		setButton(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, button }, joystick.getState(button));
	}

	InputGroup* Inputs::getGroup(const std::string& name)
	{
		if (name == "Default")
			return this;

		auto itr = m_Groups.find(name);
		return itr != m_Groups.end() ? &itr->second : nullptr;
	}

	const InputGroup* Inputs::getGroup(const std::string& name) const
	{
		if (name == "Default")
			return this;

		auto itr = m_Groups.find(name);
		return itr != m_Groups.end() ? &itr->second : nullptr;
	}

	InputGroup* Inputs::createGroup(const std::string& name)
	{
		if (name == "Default")
			return nullptr;

		auto itr = m_Groups.insert({ name, InputGroup { this, name } });
		return itr.second ? &itr.first->second : nullptr;
	}

	InputGroup* Inputs::createGroup(std::string&& name)
	{
		if (name == "Default")
		{
			name.~basic_string();
			return nullptr;
		}

		std::string copy = name;
		auto        itr  = m_Groups.insert({ std::move(copy), InputGroup { this, std::move(name) } });
		return itr.second ? &itr.first->second : nullptr;
	}

	InputGroup* Inputs::getOrCreateGroup(const std::string& name)
	{
		auto group = getGroup(name);
		return group ? group : createGroup(name);
	}

	InputGroup* Inputs::getOrCreateGroup(std::string&& name)
	{
		auto group = getGroup(name);
		if (group)
		{
			name.~basic_string();
			return group;
		}
		return createGroup(std::move(name));
	}

	void Inputs::enableGroup(const std::string& name)
	{
		auto group = getGroup(name);
		if (group)
			group->enable();
	}

	void Inputs::disableGroup(const std::string& name)
	{
		auto group = getGroup(name);
		if (group)
			group->disable();
	}

	void Inputs::toggleGroup(const std::string& name)
	{
		auto group = getGroup(name);
		if (group)
			group->toggle();
	}

	bool Inputs::isGroupEnabled(const std::string& name) const
	{
		auto group = getGroup(name);
		return group ? group->isEnabled() : false;
	}

	float Inputs::getAxisState(Binding binding) const
	{
		switch (binding.m_Location)
		{
		case EInputLocation::Mouse: return m_Mouse.getAxis(binding.m_Index);
		case EInputLocation::Gamepad: [[fallthrough]];
		case EInputLocation::Joystick: return getJoystick(binding.m_ID)->getAxis(binding.m_Index);
		default: return 0.0f;
		}
	}

	std::uint8_t Inputs::getButtonState(Binding binding) const
	{
		switch (binding.m_Location)
		{
		case EInputLocation::Keyboard: return m_Keyboard.getState(binding.m_Index);
		case EInputLocation::Mouse: return m_Mouse.getState(binding.m_Index);
		case EInputLocation::Gamepad: [[fallthrough]];
		case EInputLocation::Joystick: return getJoystick(binding.m_ID)->getState(binding.m_Index);
		default: return 0;
		}
	}

	Devices::Joystick* Inputs::getJoystick(std::uint32_t id)
	{
		for (auto& joystick : m_Joysticks)
			if (joystick.getID() == id)
				return &joystick;
		return nullptr;
	}

	const Devices::Joystick* Inputs::getJoystick(std::uint32_t id) const
	{
		for (auto& joystick : m_Joysticks)
			if (joystick.getID() == id)
				return &joystick;
		return nullptr;
	}

	Inputs::Inputs()
	    : InputGroup(this, "Default") {}

	void Inputs::setAxis(Binding binding, float value)
	{
		setAxisGroup(binding, value);
		for (auto& [name, group] : m_Groups)
			if (group.isEnabled())
				group.setAxisGroup(binding, value);
	}

	void Inputs::setButton(Binding binding, std::uint8_t state)
	{
		setButtonGroup(binding, state);
		for (auto& [name, group] : m_Groups)
			if (group.isEnabled())
				group.setButtonGroup(binding, state);
	}
} // namespace Input