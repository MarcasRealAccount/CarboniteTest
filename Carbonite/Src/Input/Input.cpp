#include "Input.h"

namespace Input
{
	bool operator==(Binding lhs, Binding rhs)
	{
		return lhs.m_Location == rhs.m_Location && (lhs.m_ID == 0 ? true : lhs.m_ID == rhs.m_ID) && lhs.m_Index == rhs.m_Index;
	}

	InputGroup::InputGroup(Inputs* inputs, const std::string& name)
	    : m_Inputs(inputs), m_Name(name) {}

	void InputGroup::enable()
	{
		m_Enabled = true;
	}

	void InputGroup::disable()
	{
		m_Enabled = false;
	}

	void InputGroup::toggle()
	{
		m_Enabled = !m_Enabled;
	}

	void InputGroup::update()
	{
		for (auto& binding : m_AxisBindings)
			binding.m_PState = binding.m_State;
		for (auto& binding : m_Axis2DBindings)
			binding.m_PState = binding.m_State;
		for (auto& binding : m_Axis3DBindings)
			binding.m_PState = binding.m_State;
	}

	void InputGroup::postUpdate()
	{
		if (m_Enabled)
		{
			for (auto& binding : m_ButtonBindings)
				binding.m_State = m_Inputs->getButtonState(binding.m_Button);

			for (auto& binding : m_ButtonAxisBindings)
			{
				binding.m_State = 0.0f;
				binding.m_State += m_Inputs->getButtonState(binding.m_PosButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State -= m_Inputs->getButtonState(binding.m_NegButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
			}
			for (auto& binding : m_ButtonAxis2DBindings)
			{
				binding.m_State = { 0.0f, 0.0f };
				binding.m_State.x += m_Inputs->getButtonState(binding.m_PosXButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.x -= m_Inputs->getButtonState(binding.m_NegXButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.y += m_Inputs->getButtonState(binding.m_PosYButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.y -= m_Inputs->getButtonState(binding.m_NegYButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
			}
			for (auto& binding : m_ButtonAxis3DBindings)
			{
				binding.m_State = { 0.0f, 0.0f, 0.0f };
				binding.m_State.x += m_Inputs->getButtonState(binding.m_PosXButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.x -= m_Inputs->getButtonState(binding.m_NegXButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.y += m_Inputs->getButtonState(binding.m_PosYButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.y -= m_Inputs->getButtonState(binding.m_NegYButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.z += m_Inputs->getButtonState(binding.m_PosZButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
				binding.m_State.z -= m_Inputs->getButtonState(binding.m_NegZButton) & ButtonStates::DownMask ? 1.0f : 0.0f;
			}
		}
		else
		{
			for (auto& binding : m_ButtonBindings)
				binding.m_State = 0;
			for (auto& binding : m_ButtonAxisBindings)
				binding.m_State = 0.0f;
			for (auto& binding : m_ButtonAxis2DBindings)
				binding.m_State = { 0.0f, 0.0f };
			for (auto& binding : m_ButtonAxis3DBindings)
				binding.m_State = { 0.0f, 0.0f, 0.0f };
		}
	}

	void InputGroup::registerButtonBinding(const std::string& name, const ButtonBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::Button, m_ButtonBindings.size() } });
		m_ButtonBindings.push_back(binding);
	}

	void InputGroup::registerAxisBinding(const std::string& name, const AxisBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::Axis, m_AxisBindings.size() } });
		m_AxisBindings.push_back(binding);
	}

	void InputGroup::registerAxis2DBinding(const std::string& name, const Axis2DBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::Axis2D, m_Axis2DBindings.size() } });
		m_Axis2DBindings.push_back(binding);
	}

	void InputGroup::registerAxis3DBinding(const std::string& name, const Axis3DBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::Axis3D, m_Axis3DBindings.size() } });
		m_Axis3DBindings.push_back(binding);
	}

	void InputGroup::registerButtonAxisBinding(const std::string& name, const ButtonAxisBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::ButtonAxis, m_ButtonAxisBindings.size() } });
		m_ButtonAxisBindings.push_back(binding);
	}

	void InputGroup::registerButtonAxis2DBinding(const std::string& name, const ButtonAxis2DBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::ButtonAxis2D, m_ButtonAxis2DBindings.size() } });
		m_ButtonAxis2DBindings.push_back(binding);
	}

	void InputGroup::registerButtonAxis3DBinding(const std::string& name, const ButtonAxis3DBinding& binding)
	{
		if (m_BindingsMap.contains(name))
			return;

		m_BindingsMap.insert({ name, { EBindingType::ButtonAxis3D, m_ButtonAxis3DBindings.size() } });
		m_ButtonAxis3DBindings.push_back(binding);
	}

	ButtonBinding* InputGroup::getButtonBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::Button ? (info.m_Index < m_ButtonBindings.size() ? &m_ButtonBindings[info.m_Index] : nullptr) : nullptr;
	}

	AxisBinding* InputGroup::getAxisBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::Axis ? (info.m_Index < m_AxisBindings.size() ? &m_AxisBindings[info.m_Index] : nullptr) : nullptr;
	}

	Axis2DBinding* InputGroup::getAxis2DBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::Axis2D ? (info.m_Index < m_Axis2DBindings.size() ? &m_Axis2DBindings[info.m_Index] : nullptr) : nullptr;
	}

	Axis3DBinding* InputGroup::getAxis3DBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::Axis3D ? (info.m_Index < m_Axis3DBindings.size() ? &m_Axis3DBindings[info.m_Index] : nullptr) : nullptr;
	}

	ButtonAxisBinding* InputGroup::getButtonAxisBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::ButtonAxis ? (info.m_Index < m_ButtonAxisBindings.size() ? &m_ButtonAxisBindings[info.m_Index] : nullptr) : nullptr;
	}

	ButtonAxis2DBinding* InputGroup::getButtonAxis2DBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::ButtonAxis2D ? (info.m_Index < m_ButtonAxis2DBindings.size() ? &m_ButtonAxis2DBindings[info.m_Index] : nullptr) : nullptr;
	}

	ButtonAxis3DBinding* InputGroup::getButtonAxis3DBinding(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return nullptr;
		auto info = itr->second;
		return info.m_Type == EBindingType::ButtonAxis3D ? (info.m_Index < m_ButtonAxis3DBindings.size() ? &m_ButtonAxis3DBindings[info.m_Index] : nullptr) : nullptr;
	}

	bool InputGroup::getButton(const std::string& name)
	{
		auto binding = getButtonBinding(name);
		return binding ? binding->m_State & ButtonStates::DownMask : false;
	}

	std::uint8_t InputGroup::getButtonState(const std::string& name)
	{
		auto binding = getButtonBinding(name);
		return binding ? binding->m_State : 0;
	}

	float InputGroup::getAxis(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return 0.0f;
		auto info = itr->second;
		switch (info.m_Type)
		{
		case EBindingType::Axis:
		{
			auto binding = info.m_Index < m_AxisBindings.size() ? &m_AxisBindings[info.m_Index] : nullptr;
			if (!binding)
				return 0.0f;

			switch (binding->m_Mode)
			{
			case EAxisMode::Direct: return binding->m_State;
			case EAxisMode::Relative: return binding->m_State - binding->m_PState;
			default: return 0.0f;
			}
		}
		case EBindingType::ButtonAxis:
		{
			auto binding = info.m_Index < m_ButtonAxisBindings.size() ? &m_ButtonAxisBindings[info.m_Index] : nullptr;
			if (!binding)
				return 0.0f;

			return binding->m_State;
		}
		default:
			return 0.0f;
		}
	}

	glm::fvec2 InputGroup::getAxis2D(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return { 0.0f, 0.0f };
		auto info = itr->second;
		switch (info.m_Type)
		{
		case EBindingType::Axis2D:
		{
			auto binding = info.m_Index < m_Axis2DBindings.size() ? &m_Axis2DBindings[info.m_Index] : nullptr;
			if (!binding)
				return { 0.0f, 0.0f };

			switch (binding->m_Mode)
			{
			case EAxisMode::Direct: return binding->m_State;
			case EAxisMode::Relative: return binding->m_State - binding->m_PState;
			default: return { 0.0f, 0.0f };
			}
		}
		case EBindingType::ButtonAxis2D:
		{
			auto binding = info.m_Index < m_ButtonAxis2DBindings.size() ? &m_ButtonAxis2DBindings[info.m_Index] : nullptr;
			if (!binding)
				return { 0.0f, 0.0f };

			return binding->m_State;
		}
		default:
			return { 0.0f, 0.0f };
		}
	}

	glm::fvec3 InputGroup::getAxis3D(const std::string& name)
	{
		auto itr = m_BindingsMap.find(name);
		if (itr == m_BindingsMap.end())
			return { 0.0f, 0.0f, 0.0f };
		auto info = itr->second;
		switch (info.m_Type)
		{
		case EBindingType::Axis3D:
		{
			auto binding = info.m_Index < m_Axis3DBindings.size() ? &m_Axis3DBindings[info.m_Index] : nullptr;
			if (!binding)
				return { 0.0f, 0.0f, 0.0f };

			switch (binding->m_Mode)
			{
			case EAxisMode::Direct: return binding->m_State;
			case EAxisMode::Relative: return binding->m_State - binding->m_PState;
			default: return { 0.0f, 0.0f, 0.0f };
			}
		}
		case EBindingType::ButtonAxis3D:
		{
			auto binding = info.m_Index < m_ButtonAxis3DBindings.size() ? &m_ButtonAxis3DBindings[info.m_Index] : nullptr;
			if (!binding)
				return { 0.0f, 0.0f, 0.0f };

			return binding->m_State;
		}
		default:
			return { 0.0f, 0.0f, 0.0f };
		}
	}

	void InputGroup::setAxis(Binding binding, float value)
	{
		for (auto& bnd : m_AxisBindings)
		{
			if (bnd.m_Axis == binding)
				bnd.m_State = value;
		}

		for (auto& bnd : m_Axis2DBindings)
		{
			if (bnd.m_XAxis == binding)
				bnd.m_State.x = value;
			if (bnd.m_YAxis == binding)
				bnd.m_State.y = value;
		}

		for (auto& bnd : m_Axis3DBindings)
		{
			if (bnd.m_XAxis == binding)
				bnd.m_State.x = value;
			if (bnd.m_YAxis == binding)
				bnd.m_State.y = value;
			if (bnd.m_ZAxis == binding)
				bnd.m_State.z = value;
		}
	}

	void InputGroup::setButton(Binding binding, std::uint8_t state)
	{
		for (auto& bnd : m_ButtonBindings)
		{
			if (bnd.m_Button == binding)
				bnd.m_State = state;
		}

		if (state & ButtonStates::PressedMask)
		{
			for (auto& bnd : m_ButtonAxisBindings)
			{
				if (bnd.m_PosButton == binding)
					bnd.m_State += 1.0f;
				if (bnd.m_NegButton == binding)
					bnd.m_State -= 1.0f;
			}

			for (auto& bnd : m_ButtonAxis2DBindings)
			{
				if (bnd.m_PosXButton == binding)
					bnd.m_State.x += 1.0f;
				if (bnd.m_NegXButton == binding)
					bnd.m_State.x -= 1.0f;
				if (bnd.m_PosYButton == binding)
					bnd.m_State.y += 1.0f;
				if (bnd.m_NegYButton == binding)
					bnd.m_State.y -= 1.0f;
			}

			for (auto& bnd : m_ButtonAxis3DBindings)
			{
				if (bnd.m_PosXButton == binding)
					bnd.m_State.x += 1.0f;
				if (bnd.m_NegXButton == binding)
					bnd.m_State.x -= 1.0f;
				if (bnd.m_PosYButton == binding)
					bnd.m_State.y += 1.0f;
				if (bnd.m_NegYButton == binding)
					bnd.m_State.y -= 1.0f;
				if (bnd.m_PosZButton == binding)
					bnd.m_State.z += 1.0f;
				if (bnd.m_NegZButton == binding)
					bnd.m_State.z -= 1.0f;
			}
		}
	}

	Inputs& Inputs::Get()
	{
		static Inputs* s_Instance = new Inputs();
		return *s_Instance;
	}

	void Inputs::Destroy()
	{
		delete &Get();
	}

	void Inputs::updateJGs(std::vector<Joystick>&& joysticks)
	{
		m_Joysticks = std::move(joysticks);
	}

	void Inputs::updateGrouped()
	{
		update();
		for (auto& [name, group] : m_Groups)
			group.update();

		m_Keyboard.update();
		m_Mouse.update();
	}

	void Inputs::postUpdateGrouped()
	{
		postUpdate();
		for (auto& [name, group] : m_Groups)
			group.postUpdate();
	}

	void Inputs::keyPressed(std::uint32_t key)
	{
		m_Keyboard.keyPressed(key);
		setButtonGrouped(Binding { EInputLocation::Keyboard, 0, key }, m_Keyboard.getState(key));
	}

	void Inputs::keyRepeat(std::uint32_t key)
	{
		m_Keyboard.keyRepeated(key);
		setButtonGrouped(Binding { EInputLocation::Keyboard, 0, key }, m_Keyboard.getState(key));
	}

	void Inputs::keyReleased(std::uint32_t key)
	{
		m_Keyboard.keyReleased(key);
		setButtonGrouped(Binding { EInputLocation::Keyboard, 0, key }, m_Keyboard.getState(key));
	}

	void Inputs::mouseMove(float x, float y)
	{
		m_Mouse.setAxis(Axes::MouseX, x);
		m_Mouse.setAxis(Axes::MouseY, y);
		setAxisGrouped(Binding { EInputLocation::Mouse, 0, Axes::MouseX }, x);
		setAxisGrouped(Binding { EInputLocation::Mouse, 0, Axes::MouseY }, y);
	}

	void Inputs::mouseScroll(float x, float y)
	{
		m_Mouse.setAxis(Axes::MouseWheelX, x);
		m_Mouse.setAxis(Axes::MouseWheelY, y);
		setAxisGrouped(Binding { EInputLocation::Mouse, 0, Axes::MouseWheelX }, x);
		setAxisGrouped(Binding { EInputLocation::Mouse, 0, Axes::MouseWheelY }, y);
	}

	void Inputs::mouseButtonPressed(std::uint32_t button)
	{
		m_Mouse.buttonPressed(button);
		setButtonGrouped({ EInputLocation::Mouse, 0, button }, m_Mouse.getState(button));
	}

	void Inputs::mouseButtonReleased(std::uint32_t button)
	{
		m_Mouse.buttonReleased(button);
		setButtonGrouped({ EInputLocation::Mouse, 0, button }, m_Mouse.getState(button));
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
		setAxisGrouped(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, axis }, value);
	}

	void Inputs::joystickButtonPressed(std::uint32_t index, std::uint32_t id, std::uint32_t button)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.buttonPressed(button);
		setButtonGrouped(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, button }, joystick.getState(button));
	}

	void Inputs::joystickButtonRepeated(std::uint32_t index, std::uint32_t id, std::uint32_t button)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.buttonRepeated(button);
		setButtonGrouped(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, button }, joystick.getState(button));
	}

	void Inputs::joystickButtonReleased(std::uint32_t index, std::uint32_t id, std::uint32_t button)
	{
		if (index >= m_Joysticks.size())
			return;

		auto& joystick = m_Joysticks[index];
		joystick.buttonReleased(button);
		setButtonGrouped(Binding { joystick.isGamepad() ? EInputLocation::Gamepad : EInputLocation::Joystick, id, button }, joystick.getState(button));
	}

	InputGroup* Inputs::getGroup(const std::string& name)
	{
		auto itr = m_Groups.find(name);
		return itr != m_Groups.end() ? &itr->second : nullptr;
	}

	InputGroup* Inputs::createGroup(const std::string& name)
	{
		auto itr = m_Groups.insert({ name, InputGroup { this, name } });
		return itr.second ? &itr.first->second : nullptr;
	}

	InputGroup* Inputs::getOrCreateGroup(const std::string& name)
	{
		auto group = getGroup(name);
		return group ? group : createGroup(name);
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

	bool Inputs::isGroupEnabled(const std::string& name)
	{
		auto group = getGroup(name);
		return group ? group->isEnabled() : false;
	}

	float Inputs::getAxisState(Binding binding)
	{
		switch (binding.m_Location)
		{
		case EInputLocation::Mouse: return m_Mouse.getAxis(binding.m_Index);
		case EInputLocation::Gamepad: [[fallthrough]];
		case EInputLocation::Joystick: return getJoystick(binding.m_ID)->getAxis(binding.m_Index);
		default: return 0.0f;
		}
	}

	std::uint8_t Inputs::getButtonState(Binding binding)
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

	Joystick* Inputs::getJoystick(std::uint32_t id)
	{
		for (auto& joystick : m_Joysticks)
			if (joystick.getID() == id)
				return &joystick;
		return nullptr;
	}

	const Joystick* Inputs::getJoystick(std::uint32_t id) const
	{
		for (auto& joystick : m_Joysticks)
			if (joystick.getID() == id)
				return &joystick;
		return nullptr;
	}

	Inputs::Inputs()
	    : InputGroup(this, "Default") {}

	void Inputs::setAxisGrouped(Binding binding, float value)
	{
		setAxis(binding, value);
		for (auto& [name, group] : m_Groups)
			if (group.isEnabled())
				group.setAxis(binding, value);
	}

	void Inputs::setButtonGrouped(Binding binding, std::uint8_t state)
	{
		setButton(binding, state);
		for (auto& [name, group] : m_Groups)
			if (group.isEnabled())
				group.setButton(binding, state);
	}
} // namespace Input