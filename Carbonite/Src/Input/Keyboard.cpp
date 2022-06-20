#include "Keyboard.h"
#include "ButtonStates.h"

namespace Input
{
	void Keyboard::update()
	{
		for (std::size_t i = 0; i < s_MaxKeys; ++i)
		{
			auto& key = m_Keys[i];
			if (key & ButtonStates::ReleasedMask) // is key released
				key = 0;
			else
				key &= ButtonStates::DownMask;
		}
	}

	void Keyboard::keyPressed(std::uint32_t key)
	{
		if (key < s_MaxKeys)
			m_Keys[key] |= ButtonStates::PressedMask | ButtonStates::DownMask;
	}

	void Keyboard::keyRepeated(std::uint32_t key)
	{
		if (key < s_MaxKeys)
			m_Keys[key] |= ButtonStates::RepeatedMask | ButtonStates::DownMask;
	}

	void Keyboard::keyReleased(std::uint32_t key)
	{
		if (key < s_MaxKeys)
			m_Keys[key] |= ButtonStates::ReleasedMask;
	}

	std::uint8_t Keyboard::getState(std::uint32_t key) const
	{
		return key < s_MaxKeys ? m_Keys[key] : 0;
	}

	bool Keyboard::isKeyPressed(std::uint32_t key) const
	{
		return key < s_MaxKeys ? m_Keys[key] & ButtonStates::PressedMask : false;
	}

	bool Keyboard::isKeyRepeated(std::uint32_t key) const
	{
		return key < s_MaxKeys ? m_Keys[key] & ButtonStates::RepeatedMask : false;
	}

	bool Keyboard::isKeyReleased(std::uint32_t key) const
	{
		return key < s_MaxKeys ? m_Keys[key] & ButtonStates::ReleasedMask : false;
	}

	bool Keyboard::isKeyDown(std::uint32_t key) const
	{
		return key < s_MaxKeys ? m_Keys[key] & ButtonStates::DownMask : false;
	}
} // namespace Input