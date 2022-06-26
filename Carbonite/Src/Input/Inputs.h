#pragma once

#include "Devices/Joystick.h"
#include "Devices/Keyboard.h"
#include "Devices/Mouse.h"
#include "InputGroup.h"

#include <string>
#include <unordered_map>

namespace Input
{
	class Inputs final : public InputGroup
	{
	public:
		static Inputs& Get();
		static void    Destroy();

	public:
		void updateJoysticks(std::vector<Devices::Joystick>&& joysticks);

		void update();
		void postUpdate();

		void keyPressed(std::uint32_t key);
		void keyRepeated(std::uint32_t key);
		void keyReleased(std::uint32_t key);

		void mouseMove(float x, float y);
		void mouseScroll(float x, float y);

		void mouseButtonPressed(std::uint32_t button);
		void mouseButtonRepeated(std::uint32_t button);
		void mouseButtonReleased(std::uint32_t button);

		void joystickConnect(std::uint32_t index, std::uint32_t id, std::uint32_t axes, std::uint32_t buttons, bool gamepad);
		void joystickDisconnect(std::uint32_t index);
		void joystickAxis(std::uint32_t index, std::uint32_t id, std::uint32_t axis, float value);
		void joystickButtonPressed(std::uint32_t index, std::uint32_t id, std::uint32_t button);
		void joystickButtonRepeated(std::uint32_t index, std::uint32_t id, std::uint32_t button);
		void joystickButtonReleased(std::uint32_t index, std::uint32_t id, std::uint32_t button);

		InputGroup*       getGroup(const std::string& name);
		const InputGroup* getGroup(const std::string& name) const;
		InputGroup*       createGroup(const std::string& name);
		InputGroup*       createGroup(std::string&& name);
		InputGroup*       getOrCreateGroup(const std::string& name);
		InputGroup*       getOrCreateGroup(std::string&& name);

		void enableGroup(const std::string& name);
		void disableGroup(const std::string& name);
		void toggleGroup(const std::string& name);
		bool isGroupEnabled(const std::string& name) const;

		float        getAxisState(Binding binding) const;
		std::uint8_t getButtonState(Binding binding) const;

		auto&                    getKeyboard() const { return m_Keyboard; }
		auto&                    getMouse() const { return m_Mouse; }
		auto&                    getJoysticks() const { return m_Joysticks; }
		Devices::Joystick*       getJoystick(std::uint32_t id);
		const Devices::Joystick* getJoystick(std::uint32_t id) const;

	private:
		Inputs();
		~Inputs() = default;

		void setAxis(Binding binding, float value);
		void setButton(Binding binding, std::uint8_t state);

	private:
		Devices::Keyboard m_Keyboard;
		Devices::Mouse    m_Mouse;

		std::vector<Devices::Joystick> m_Joysticks;

		std::unordered_map<std::string, InputGroup> m_Groups;
	};
} // namespace Input