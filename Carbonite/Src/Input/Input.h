#pragma once

#include "ButtonStates.h"
#include "Joystick.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

namespace Input
{
	enum class EInputLocation
	{
		Keyboard,
		Mouse,
		Gamepad,
		Joystick
	};

	enum class EAxisMode
	{
		Direct,
		Relative
	};

	struct Binding
	{
	public:
		friend bool operator==(Binding lhs, Binding rhs);
		friend bool operator!=(Binding lhs, Binding rhs) { return !(lhs == rhs); }

	public:
		EInputLocation m_Location;
		std::uint32_t  m_ID;
		std::uint32_t  m_Index;
		float          m_Sensitivity = 1.0f;
	};

	struct ButtonBinding
	{
	public:
		std::string m_Name;
		Binding     m_Button;

		std::uint8_t m_State;
	};

	struct AxisBinding
	{
	public:
		std::string m_Name;
		Binding     m_Axis;
		EAxisMode   m_Mode;

		float m_State  = 0.0f;
		float m_PState = 0.0f;
	};

	struct Axis2DBinding
	{
	public:
		std::string m_Name;
		Binding     m_XAxis;
		Binding     m_YAxis;
		EAxisMode   m_Mode;

		glm::fvec2 m_State  = { 0.0f, 0.0f };
		glm::fvec2 m_PState = { 0.0f, 0.0f };
	};

	struct Axis3DBinding
	{
	public:
		std::string m_Name;
		Binding     m_XAxis;
		Binding     m_YAxis;
		Binding     m_ZAxis;
		EAxisMode   m_Mode;

		glm::fvec3 m_State  = { 0.0f, 0.0f, 0.0f };
		glm::fvec3 m_PState = { 0.0f, 0.0f, 0.0f };
	};

	struct ButtonAxisBinding
	{
	public:
		std::string m_Name;
		Binding     m_PosButton;
		Binding     m_NegButton;

		float m_State = 0.0f;
	};

	struct ButtonAxis2DBinding
	{
	public:
		std::string m_Name;
		Binding     m_PosXButton;
		Binding     m_NegXButton;
		Binding     m_PosYButton;
		Binding     m_NegYButton;

		glm::fvec2 m_State = { 0.0f, 0.0f };
	};

	struct ButtonAxis3DBinding
	{
	public:
		std::string m_Name;
		Binding     m_PosXButton;
		Binding     m_NegXButton;
		Binding     m_PosYButton;
		Binding     m_NegYButton;
		Binding     m_PosZButton;
		Binding     m_NegZButton;

		glm::fvec3 m_State = { 0.0f, 0.0f, 0.0f };
	};

	enum class EBindingType
	{
		Button,
		Axis,
		Axis2D,
		Axis3D,
		ButtonAxis,
		ButtonAxis2D,
		ButtonAxis3D
	};

	struct BindingInfo
	{
	public:
		EBindingType m_Type;
		std::size_t  m_Index;
	};

	class Inputs;

	class InputGroup
	{
	public:
		InputGroup(Inputs* inputs, const std::string& name);

		void update();
		void postUpdate();

		void enable();
		void disable();
		void toggle();

		void registerButtonBinding(const std::string& name, const ButtonBinding& binding);
		void registerAxisBinding(const std::string& name, const AxisBinding& binding);
		void registerAxis2DBinding(const std::string& name, const Axis2DBinding& binding);
		void registerAxis3DBinding(const std::string& name, const Axis3DBinding& binding);
		void registerButtonAxisBinding(const std::string& name, const ButtonAxisBinding& binding);
		void registerButtonAxis2DBinding(const std::string& name, const ButtonAxis2DBinding& binding);
		void registerButtonAxis3DBinding(const std::string& name, const ButtonAxis3DBinding& binding);

		ButtonBinding*       getButtonBinding(const std::string& name);
		AxisBinding*         getAxisBinding(const std::string& name);
		Axis2DBinding*       getAxis2DBinding(const std::string& name);
		Axis3DBinding*       getAxis3DBinding(const std::string& name);
		ButtonAxisBinding*   getButtonAxisBinding(const std::string& name);
		ButtonAxis2DBinding* getButtonAxis2DBinding(const std::string& name);
		ButtonAxis3DBinding* getButtonAxis3DBinding(const std::string& name);

		bool         getButton(const std::string& name);
		std::uint8_t getButtonState(const std::string& name);
		float        getAxis(const std::string& name);
		glm::fvec2   getAxis2D(const std::string& name);
		glm::fvec3   getAxis3D(const std::string& name);

		auto& getName() const { return m_Name; }
		bool  isEnabled() const { return m_Enabled; }

		void setAxis(Binding binding, float value);
		void setButton(Binding binding, std::uint8_t state);

	protected:
		Inputs*     m_Inputs;
		std::string m_Name;
		bool        m_Enabled = true;

		std::unordered_map<std::string, BindingInfo> m_BindingsMap;

		std::vector<ButtonBinding>       m_ButtonBindings;
		std::vector<AxisBinding>         m_AxisBindings;
		std::vector<Axis2DBinding>       m_Axis2DBindings;
		std::vector<Axis3DBinding>       m_Axis3DBindings;
		std::vector<ButtonAxisBinding>   m_ButtonAxisBindings;
		std::vector<ButtonAxis2DBinding> m_ButtonAxis2DBindings;
		std::vector<ButtonAxis3DBinding> m_ButtonAxis3DBindings;
	};

	class Inputs final : public InputGroup
	{
	public:
		static Inputs& Get();
		static void    Destroy();

	public:
		void updateJGs(std::vector<Joystick>&& joysticks);

		void updateGrouped();
		void postUpdateGrouped();

		void keyPressed(std::uint32_t key);
		void keyRepeat(std::uint32_t key);
		void keyReleased(std::uint32_t key);

		void mouseMove(float x, float y);
		void mouseScroll(float x, float y);

		void mouseButtonPressed(std::uint32_t button);
		void mouseButtonReleased(std::uint32_t button);

		void joystickConnect(std::uint32_t index, std::uint32_t id, std::uint32_t axes, std::uint32_t buttons, bool gamepad);
		void joystickDisconnect(std::uint32_t index);
		void joystickAxis(std::uint32_t index, std::uint32_t id, std::uint32_t axis, float value);
		void joystickButtonPressed(std::uint32_t index, std::uint32_t id, std::uint32_t button);
		void joystickButtonRepeated(std::uint32_t index, std::uint32_t id, std::uint32_t button);
		void joystickButtonReleased(std::uint32_t index, std::uint32_t id, std::uint32_t button);

		InputGroup* getGroup(const std::string& name);
		InputGroup* createGroup(const std::string& name);
		InputGroup* getOrCreateGroup(const std::string& name);

		void enableGroup(const std::string& name);
		void disableGroup(const std::string& name);
		void toggleGroup(const std::string& name);
		bool isGroupEnabled(const std::string& name);

		float        getAxisState(Binding binding);
		std::uint8_t getButtonState(Binding binding);

		auto&           getKeyboard() const { return m_Keyboard; }
		auto&           getMouse() const { return m_Keyboard; }
		auto&           getJoysticks() const { return m_Joysticks; }
		Joystick*       getJoystick(std::uint32_t id);
		const Joystick* getJoystick(std::uint32_t id) const;

	private:
		Inputs();
		~Inputs() = default;

		void setAxisGrouped(Binding binding, float value);
		void setButtonGrouped(Binding binding, std::uint8_t state);

	private:
		Keyboard m_Keyboard;
		Mouse    m_Mouse;

		std::vector<Joystick> m_Joysticks;

		std::unordered_map<std::string, InputGroup> m_Groups;
	};

	inline InputGroup* GetGroup(const std::string& name) { return Inputs::Get().getGroup(name); }
	inline InputGroup* CreateGroup(const std::string& name) { return Inputs::Get().createGroup(name); }
	inline InputGroup* GetOrCreateGroup(const std::string& name) { return Inputs::Get().getOrCreateGroup(name); }

	inline void EnableGroup(const std::string& name) { Inputs::Get().enableGroup(name); }
	inline void DisableGroup(const std::string& name) { Inputs::Get().disableGroup(name); }
	inline void ToggleGroup(const std::string& name) { Inputs::Get().toggleGroup(name); }
	inline bool IsGroupEnabled(const std::string& name) { return Inputs::Get().isGroupEnabled(name); }

	inline void RegisterButtonBinding(const std::string& name, std::uint32_t button, EInputLocation location = EInputLocation::Keyboard, std::uint32_t id = 0)
	{
		Inputs::Get().registerButtonBinding(name, ButtonBinding { name, Binding { location, id, button } });
	}

	inline void RegisterAxisBinding(const std::string& name, std::uint32_t axis, float sensitivity = 1.0f, EAxisMode mode = EAxisMode::Direct, EInputLocation location = EInputLocation::Mouse, std::uint32_t id = 0)
	{
		Inputs::Get().registerAxisBinding(name, AxisBinding { name, Binding { location, id, axis, sensitivity }, mode });
	}

	inline void RegisterAxis2DBinding(const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode = EAxisMode::Direct)
	{
		Inputs::Get().registerAxis2DBinding(name, Axis2DBinding { name, xAxis, yAxis, mode });
	}

	inline void RegisterAxis3DBinding(const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode = EAxisMode::Direct)
	{
		Inputs::Get().registerAxis3DBinding(name, { name, xAxis, yAxis, zAxis, mode });
	}

	inline void RegisterButtonAxisBinding(const std::string& name, Binding posButton, Binding negButton)
	{
		Inputs::Get().registerButtonAxisBinding(name, { name, posButton, negButton });
	}

	inline void RegisterButtonAxis2DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton)
	{
		Inputs::Get().registerButtonAxis2DBinding(name, { name, posXButton, negXButton, posYButton, negYButton });
	}

	inline void RegisterButtonAxis3DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton)
	{
		Inputs::Get().registerButtonAxis3DBinding(name, { name, posXButton, negXButton, posYButton, negYButton, posZButton, negZButton });
	}

	inline bool         Button(const std::string& name) { return Inputs::Get().getButton(name); }
	inline std::uint8_t ButtonState(const std::string& name) { return Inputs::Get().InputGroup::getButtonState(name); }
	inline bool         ButtonPressed(const std::string& name) { return ButtonState(name) & ButtonStates::PressedMask; }
	inline bool         ButtonRepeated(const std::string& name) { return ButtonState(name) & ButtonStates::RepeatedMask; }
	inline bool         ButtonReleased(const std::string& name) { return ButtonState(name) & ButtonStates::ReleasedMask; }
	inline float        Axis(const std::string& name) { return Inputs::Get().getAxis(name); }
	inline glm::fvec2   Axis2D(const std::string& name) { return Inputs::Get().getAxis2D(name); }
	inline glm::fvec3   Axis3D(const std::string& name) { return Inputs::Get().getAxis3D(name); }

	inline void RegisterButtonBinding(const std::string& group, const std::string& name, std::uint32_t button, EInputLocation location = EInputLocation::Keyboard, std::uint32_t id = 0)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerButtonBinding(name, ButtonBinding { name, Binding { location, id, button } });
	}

	inline void RegisterAxisBinding(const std::string& group, const std::string& name, std::uint32_t axis, float sensitivity = 1.0f, EAxisMode mode = EAxisMode::Direct, EInputLocation location = EInputLocation::Mouse, std::uint32_t id = 0)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerAxisBinding(name, AxisBinding { name, Binding { location, id, axis, sensitivity }, mode });
	}

	inline void RegisterAxis2DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode = EAxisMode::Direct)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerAxis2DBinding(name, Axis2DBinding { name, xAxis, yAxis, mode });
	}

	inline void RegisterAxis3DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode = EAxisMode::Direct)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerAxis3DBinding(name, { name, xAxis, yAxis, zAxis, mode });
	}

	inline void RegisterButtonAxisBinding(const std::string& group, const std::string& name, Binding posButton, Binding negButton)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerButtonAxisBinding(name, { name, posButton, negButton });
	}

	inline void RegisterButtonAxis2DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerButtonAxis2DBinding(name, { name, posXButton, negXButton, posYButton, negYButton });
	}

	inline void RegisterButtonAxis3DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return;
		g->registerButtonAxis3DBinding(name, { name, posXButton, negXButton, posYButton, negYButton, posZButton, negZButton });
	}

	inline bool Button(const std::string& group, const std::string& name)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return false;
		return g->getButton(name);
	}

	inline std::uint8_t ButtonState(const std::string& group, const std::string& name)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return 0;
		return g->getButtonState(name);
	}
	inline bool ButtonPressed(const std::string& group, const std::string& name) { return ButtonState(group, name) & ButtonStates::PressedMask; }
	inline bool ButtonRepeated(const std::string& group, const std::string& name) { return ButtonState(group, name) & ButtonStates::RepeatedMask; }
	inline bool ButtonReleased(const std::string& group, const std::string& name) { return ButtonState(group, name) & ButtonStates::ReleasedMask; }

	inline float Axis(const std::string& group, const std::string& name)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return 0.0f;
		return g->getAxis(name);
	}

	inline glm::fvec2 Axis2D(const std::string& group, const std::string& name)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return { 0.0f, 0.0f };
		return g->getAxis2D(name);
	}

	inline glm::fvec3 Axis3D(const std::string& group, const std::string& name)
	{
		auto g = GetOrCreateGroup(group);
		if (!g)
			return { 0.0f, 0.0f, 0.0f };
		return g->getAxis3D(name);
	}
} // namespace Input