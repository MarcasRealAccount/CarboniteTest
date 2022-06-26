#pragma once

#include <cstdint>

#include <string>

#include <glm/glm.hpp>

namespace Input
{
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
		static constexpr EBindingType Type = EBindingType::Button;

	public:
		std::string m_Name;
		Binding     m_Button;

		std::uint8_t m_State;
	};

	struct AxisBinding
	{
	public:
		static constexpr EBindingType Type = EBindingType::Axis;

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
		static constexpr EBindingType Type = EBindingType::Axis2D;

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
		static constexpr EBindingType Type = EBindingType::Axis3D;

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
		static constexpr EBindingType Type = EBindingType::ButtonAxis;

	public:
		std::string m_Name;
		Binding     m_PosButton;
		Binding     m_NegButton;

		float m_State = 0.0f;
	};

	struct ButtonAxis2DBinding
	{
	public:
		static constexpr EBindingType Type = EBindingType::ButtonAxis2D;

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
		static constexpr EBindingType Type = EBindingType::ButtonAxis3D;

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

	struct BindingInfo
	{
	public:
		EBindingType m_Type;
		std::size_t  m_Index;
	};

	namespace Detail
	{
		template <EBindingType T>
		struct BindingType
		{
			using Type = void;
		};
		template <>
		struct BindingType<EBindingType::Button>
		{
			using Type = ButtonBinding;
		};
		template <>
		struct BindingType<EBindingType::Axis>
		{
			using Type = AxisBinding;
		};
		template <>
		struct BindingType<EBindingType::Axis2D>
		{
			using Type = Axis2DBinding;
		};
		template <>
		struct BindingType<EBindingType::Axis3D>
		{
			using Type = Axis3DBinding;
		};
		template <>
		struct BindingType<EBindingType::ButtonAxis>
		{
			using Type = ButtonAxisBinding;
		};
		template <>
		struct BindingType<EBindingType::ButtonAxis2D>
		{
			using Type = ButtonAxis2DBinding;
		};
		template <>
		struct BindingType<EBindingType::ButtonAxis3D>
		{
			using Type = ButtonAxis3DBinding;
		};
	} // namespace Detail

	template <EBindingType T>
	using BindingType = Detail::BindingType<T>::Type;

	template <class T>
	concept Bindable = std::is_same_v<std::remove_cv_t<decltype(T::Type)>, EBindingType>;
} // namespace Input