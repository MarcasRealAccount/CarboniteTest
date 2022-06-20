#include "Mouse.h"
#include "ButtonStates.h"

namespace Input
{
	void Mouse::update()
	{
		m_Axes[Axes::MouseWheelX] = 0.0f;
		m_Axes[Axes::MouseWheelY] = 0.0f;

		for (std::size_t i = 0; i < s_MaxMouseButtons; ++i)
		{
			auto& button = m_Buttons[i];
			if (button & ButtonStates::ReleasedMask) // is button released
				button = 0;
			else
				button &= ButtonStates::DownMask;
		}
	}

	void Mouse::setAxis(std::uint32_t axis, float value)
	{
		if (axis < 4)
			m_Axes[axis] = value;
	}

	void Mouse::buttonPressed(std::uint32_t button)
	{
		if (button < s_MaxMouseButtons)
			m_Buttons[button] |= ButtonStates::PressedMask | ButtonStates::DownMask;
	}

	void Mouse::buttonReleased(std::uint32_t button)
	{
		if (button < s_MaxMouseButtons)
			m_Buttons[button] |= ButtonStates::ReleasedMask;
	}

	float Mouse::getAxis(std::uint32_t axis) const
	{
		return axis < 4 ? m_Axes[axis] : 0.0f;
	}

	std::uint8_t Mouse::getState(std::uint32_t button) const
	{
		return button < s_MaxMouseButtons ? m_Buttons[button] : 0;
	}

	bool Mouse::isButtonPressed(std::uint32_t button) const
	{
		return button < s_MaxMouseButtons ? m_Buttons[button] & ButtonStates::PressedMask : false;
	}

	bool Mouse::isButtonReleased(std::uint32_t button) const
	{
		return button < s_MaxMouseButtons ? m_Buttons[button] & ButtonStates::ReleasedMask : false;
	}

	bool Mouse::isButtonDown(std::uint32_t button) const
	{
		return button < s_MaxMouseButtons ? m_Buttons[button] & ButtonStates::DownMask : false;
	}
} // namespace Input