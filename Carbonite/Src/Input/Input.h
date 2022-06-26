#pragma once

#include "ButtonStates.h"
#include "Inputs.h"

namespace Input
{
	inline InputGroup* GetGroup(const std::string& name) { return Inputs::Get().getGroup(name); }
	inline InputGroup* CreateGroup(const std::string& name) { return Inputs::Get().createGroup(name); }
	inline InputGroup* GetOrCreateGroup(const std::string& name) { return Inputs::Get().getOrCreateGroup(name); }

	inline void EnableGroup(const std::string& name) { Inputs::Get().enableGroup(name); }
	inline void DisableGroup(const std::string& name) { Inputs::Get().disableGroup(name); }
	inline void ToggleGroup(const std::string& name) { Inputs::Get().toggleGroup(name); }
	inline bool IsGroupEnabled(const std::string& name) { return Inputs::Get().isGroupEnabled(name); }

	inline bool         Button(const std::string& name);
	inline bool         Button(Binding button);
	inline bool         Button(const std::string& group, const std::string& name);
	inline std::uint8_t ButtonState(const std::string& name);
	inline std::uint8_t ButtonState(Binding button);
	inline std::uint8_t ButtonState(const std::string& group, const std::string& name);
	inline bool         ButtonPressed(const std::string& name);
	inline bool         ButtonPressed(Binding button);
	inline bool         ButtonPressed(const std::string& group, const std::string& name);
	inline bool         ButtonRepeated(const std::string& name);
	inline bool         ButtonRepeated(Binding button);
	inline bool         ButtonRepeated(const std::string& group, const std::string& name);
	inline bool         ButtonReleased(const std::string& name);
	inline bool         ButtonReleased(Binding button);
	inline bool         ButtonReleased(const std::string& group, const std::string& name);

	inline float      Axis(const std::string& name);
	inline float      Axis(Binding button);
	inline float      Axis(const std::string& group, const std::string& name);
	inline glm::fvec2 Axis2D(const std::string& name);
	inline glm::fvec2 Axis2D(const std::string& group, const std::string& name);
	inline glm::fvec3 Axis3D(const std::string& name);
	inline glm::fvec3 Axis3D(const std::string& group, const std::string& name);

	template <Bindable T>
	inline void RegisterBinding(const std::string& name, T&& binding);
	template <Bindable T>
	inline void RegisterBinding(std::string&& name, T&& binding);
	template <Bindable T>
	inline void RegisterBinding(const std::string& group, const std::string& name, T&& binding);
	template <Bindable T>
	inline void RegisterBinding(const std::string& group, std::string&& name, T&& binding);
	inline void RegisterButtonBinding(const std::string& name, std::uint32_t button, EInputLocation location = EInputLocation::Keyboard, std::uint32_t id = 0);
	inline void RegisterButtonBinding(std::string&& name, std::uint32_t button, EInputLocation location = EInputLocation::Keyboard, std::uint32_t id = 0);
	inline void RegisterButtonBinding(const std::string& group, const std::string& name, std::uint32_t button, EInputLocation location = EInputLocation::Keyboard, std::uint32_t id = 0);
	inline void RegisterButtonBinding(const std::string& group, std::string&& name, std::uint32_t button, EInputLocation location = EInputLocation::Keyboard, std::uint32_t id = 0);
	inline void RegisterButtonBinding(const std::string& name, Binding button);
	inline void RegisterButtonBinding(std::string&& name, Binding button);
	inline void RegisterButtonBinding(const std::string& group, const std::string& name, Binding button);
	inline void RegisterButtonBinding(const std::string& group, std::string&& name, Binding button);
	inline void RegisterAxisBinding(const std::string& name, std::uint32_t axis, float sensitivity = 1.0f, EAxisMode mode = EAxisMode::Direct, EInputLocation location = EInputLocation::Mouse, std::uint32_t id = 0);
	inline void RegisterAxisBinding(std::string&& name, std::uint32_t axis, float sensitivity = 1.0f, EAxisMode mode = EAxisMode::Direct, EInputLocation location = EInputLocation::Mouse, std::uint32_t id = 0);
	inline void RegisterAxisBinding(const std::string& group, const std::string& name, std::uint32_t axis, float sensitivity = 1.0f, EAxisMode mode = EAxisMode::Direct, EInputLocation location = EInputLocation::Mouse, std::uint32_t id = 0);
	inline void RegisterAxisBinding(const std::string& group, std::string&& name, std::uint32_t axis, float sensitivity = 1.0f, EAxisMode mode = EAxisMode::Direct, EInputLocation location = EInputLocation::Mouse, std::uint32_t id = 0);
	inline void RegisterAxis2DBinding(const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis2DBinding(std::string&& name, Binding xAxis, Binding yAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis2DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis2DBinding(const std::string& group, std::string&& name, Binding xAxis, Binding yAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis3DBinding(const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis3DBinding(std::string&& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis3DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterAxis3DBinding(const std::string& group, std::string&& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode = EAxisMode::Direct);
	inline void RegisterButtonAxisBinding(const std::string& name, Binding posButton, Binding negButton);
	inline void RegisterButtonAxisBinding(std::string&& name, Binding posButton, Binding negButton);
	inline void RegisterButtonAxisBinding(const std::string& group, const std::string& name, Binding posButton, Binding negButton);
	inline void RegisterButtonAxisBinding(const std::string& group, std::string&& name, Binding posButton, Binding negButton);
	inline void RegisterButtonAxis2DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton);
	inline void RegisterButtonAxis2DBinding(std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton);
	inline void RegisterButtonAxis2DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton);
	inline void RegisterButtonAxis2DBinding(const std::string& group, std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton);
	inline void RegisterButtonAxis3DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton);
	inline void RegisterButtonAxis3DBinding(std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton);
	inline void RegisterButtonAxis3DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton);
	inline void RegisterButtonAxis3DBinding(const std::string& group, std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton);
} // namespace Input

namespace Input
{
	inline bool         Button(const std::string& name) { return Inputs::Get().getButton(name); }
	inline bool         Button(Binding button) { return Inputs::Get().getButtonState(button) & ButtonStates::DownMask; }
	inline bool         Button(const std::string& group, const std::string& name) { return GetGroup(group)->getButton(name); }
	inline std::uint8_t ButtonState(const std::string& name) { return Inputs::Get().InputGroup::getButtonState(name); }
	inline std::uint8_t ButtonState(Binding button) { return Inputs::Get().getButtonState(button); }
	inline std::uint8_t ButtonState(const std::string& group, const std::string& name) { return GetGroup(group)->InputGroup::getButtonState(name); }
	inline bool         ButtonPressed(const std::string& name) { return ButtonState(name) & ButtonStates::PressedMask; }
	inline bool         ButtonPressed(Binding button) { return ButtonState(button) & ButtonStates::PressedMask; }
	inline bool         ButtonPressed(const std::string& group, const std::string& name) { return ButtonState(group, name) & ButtonStates::PressedMask; }
	inline bool         ButtonRepeated(const std::string& name) { return ButtonState(name) & ButtonStates::RepeatedMask; }
	inline bool         ButtonRepeated(Binding button) { return ButtonState(button) & ButtonStates::RepeatedMask; }
	inline bool         ButtonRepeated(const std::string& group, const std::string& name) { return ButtonState(group, name) & ButtonStates::RepeatedMask; }
	inline bool         ButtonReleased(const std::string& name) { return ButtonState(name) & ButtonStates::ReleasedMask; }
	inline bool         ButtonReleased(Binding button) { return ButtonState(button) & ButtonStates::ReleasedMask; }
	inline bool         ButtonReleased(const std::string& group, const std::string& name) { return ButtonState(group, name) & ButtonStates::ReleasedMask; }

	inline float      Axis(const std::string& name) { return Inputs::Get().getAxis(name); }
	inline float      Axis(Binding axis) { return Inputs::Get().getAxisState(axis); }
	inline float      Axis(const std::string& group, const std::string& name) { return GetGroup(group)->getAxis(name); }
	inline glm::fvec2 Axis2D(const std::string& name) { return Inputs::Get().getAxis2D(name); }
	inline glm::fvec2 Axis2D(const std::string& group, const std::string& name) { return GetGroup(group)->getAxis2D(name); }
	inline glm::fvec3 Axis3D(const std::string& name) { return Inputs::Get().getAxis3D(name); }
	inline glm::fvec3 Axis3D(const std::string& group, const std::string& name) { return GetGroup(group)->getAxis3D(name); }

	template <Bindable T>
	inline void RegisterBinding(const std::string& name, T&& binding)
	{
		Inputs::Get().registerBinding(name, std::forward<T>(binding));
	}

	template <Bindable T>
	inline void RegisterBinding(std::string&& name, T&& binding)
	{
		Inputs::Get().registerBinding(std::move(name), std::forward<T>(binding));
	}

	template <Bindable T>
	inline void RegisterBinding(const std::string& group, const std::string& name, T&& binding)
	{
		GetGroup(group)->registerBinding(name, std::forward<T>(binding));
	}

	template <Bindable T>
	inline void RegisterBinding(const std::string& group, std::string&& name, T&& binding)
	{
		GetGroup(group)->registerBinding(std::move(name), std::forward<T>(binding));
	}

	inline void RegisterButtonBinding(const std::string& name, std::uint32_t button, EInputLocation location, std::uint32_t id)
	{
		RegisterBinding(name, ButtonBinding { name, Binding { location, id, button } });
	}

	inline void RegisterButtonBinding(std::string&& name, std::uint32_t button, EInputLocation location, std::uint32_t id)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), ButtonBinding { std::move(name), Binding { location, id, button } });
	}

	inline void RegisterButtonBinding(const std::string& group, const std::string& name, std::uint32_t button, EInputLocation location, std::uint32_t id)
	{
		RegisterBinding(group, name, ButtonBinding { name, Binding { location, id, button } });
	}

	inline void RegisterButtonBinding(const std::string& group, std::string&& name, std::uint32_t button, EInputLocation location, std::uint32_t id)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), ButtonBinding { std::move(name), Binding { location, id, button } });
	}

	inline void RegisterButtonBinding(const std::string& name, Binding button)
	{
		RegisterBinding(name, ButtonBinding { name, button });
	}

	inline void RegisterButtonBinding(std::string&& name, Binding button)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), ButtonBinding { std::move(name), button });
	}

	inline void RegisterButtonBinding(const std::string& group, const std::string& name, Binding button)
	{
		RegisterBinding(group, name, ButtonBinding { name, button });
	}

	inline void RegisterButtonBinding(const std::string& group, std::string&& name, Binding button)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), ButtonBinding { std::move(name), button });
	}

	inline void RegisterAxisBinding(const std::string& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id)
	{
		RegisterBinding(name, AxisBinding { name, Binding { location, id, axis, sensitivity }, mode });
	}

	inline void RegisterAxisBinding(std::string&& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), AxisBinding { std::move(name), Binding { location, id, axis, sensitivity }, mode });
	}

	inline void RegisterAxisBinding(const std::string& group, const std::string& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id)
	{
		RegisterBinding(group, name, AxisBinding { name, Binding { location, id, axis, sensitivity }, mode });
	}

	inline void RegisterAxisBinding(const std::string& group, std::string&& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), AxisBinding { std::move(name), Binding { location, id, axis, sensitivity }, mode });
	}

	inline void RegisterAxis2DBinding(const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode)
	{
		RegisterBinding(name, Axis2DBinding { name, xAxis, yAxis, mode });
	}

	inline void RegisterAxis2DBinding(std::string&& name, Binding xAxis, Binding yAxis, EAxisMode mode)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), Axis2DBinding { std::move(name), xAxis, yAxis, mode });
	}

	inline void RegisterAxis2DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode)
	{
		RegisterBinding(group, name, Axis2DBinding { name, xAxis, yAxis, mode });
	}

	inline void RegisterAxis2DBinding(const std::string& group, std::string&& name, Binding xAxis, Binding yAxis, EAxisMode mode)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), Axis2DBinding { std::move(name), xAxis, yAxis, mode });
	}

	inline void RegisterAxis3DBinding(const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode)
	{
		RegisterBinding(name, Axis3DBinding { name, xAxis, yAxis, zAxis, mode });
	}

	inline void RegisterAxis3DBinding(std::string&& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), Axis3DBinding { std::move(name), xAxis, yAxis, zAxis, mode });
	}

	inline void RegisterAxis3DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode)
	{
		RegisterBinding(group, name, Axis3DBinding { name, xAxis, yAxis, zAxis, mode });
	}

	inline void RegisterAxis3DBinding(const std::string& group, std::string&& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), Axis3DBinding { std::move(name), xAxis, yAxis, zAxis, mode });
	}

	inline void RegisterButtonAxisBinding(const std::string& name, Binding posButton, Binding negButton)
	{
		RegisterBinding(name, ButtonAxisBinding { name, posButton, negButton });
	}

	inline void RegisterButtonAxisBinding(std::string&& name, Binding posButton, Binding negButton)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), ButtonAxisBinding { std::move(name), posButton, negButton });
	}

	inline void RegisterButtonAxisBinding(const std::string& group, const std::string& name, Binding posButton, Binding negButton)
	{
		RegisterBinding(group, name, ButtonAxisBinding { name, posButton, negButton });
	}

	inline void RegisterButtonAxisBinding(const std::string& group, std::string&& name, Binding posButton, Binding negButton)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), ButtonAxisBinding { std::move(name), posButton, negButton });
	}

	inline void RegisterButtonAxis2DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton)
	{
		RegisterBinding(name, ButtonAxis2DBinding { name, posXButton, negXButton, posYButton, negYButton });
	}

	inline void RegisterButtonAxis2DBinding(std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), ButtonAxis2DBinding { std::move(name), posXButton, negXButton, posYButton, negYButton });
	}

	inline void RegisterButtonAxis2DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton)
	{
		RegisterBinding(group, name, ButtonAxis2DBinding { name, posXButton, negXButton, posYButton, negYButton });
	}

	inline void RegisterButtonAxis2DBinding(const std::string& group, std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), ButtonAxis2DBinding { std::move(name), posXButton, negXButton, posYButton, negYButton });
	}

	inline void RegisterButtonAxis3DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton)
	{
		RegisterBinding(name, ButtonAxis3DBinding { name, posXButton, negXButton, posYButton, negYButton, posZButton, negZButton });
	}

	inline void RegisterButtonAxis3DBinding(std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton)
	{
		std::string copy = name;
		RegisterBinding(std::move(copy), ButtonAxis3DBinding { std::move(name), posXButton, negXButton, posYButton, negYButton, posZButton, negZButton });
	}

	inline void RegisterButtonAxis3DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton)
	{
		RegisterBinding(group, name, ButtonAxis3DBinding { name, posXButton, negXButton, posYButton, negYButton, posZButton, negZButton });
	}

	inline void RegisterButtonAxis3DBinding(const std::string& group, std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton)
	{
		std::string copy = name;
		RegisterBinding(group, std::move(copy), ButtonAxis3DBinding { std::move(name), posXButton, negXButton, posYButton, negYButton, posZButton, negZButton });
	}
} // namespace Input