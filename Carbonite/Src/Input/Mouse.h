#pragma once

namespace Input
{
	static constexpr std::size_t s_MaxMouseButtons = 8;

	class Mouse final
	{
	public:
		Mouse()  = default;
		~Mouse() = default;

		void update();

		void setAxis(std::uint32_t axis, float value);

		void buttonPressed(std::uint32_t button);
		void buttonReleased(std::uint32_t button);

		float getAxis(std::uint32_t axis);

		std::uint8_t getState(std::uint32_t button);

		bool isButtonPressed(std::uint32_t button);
		bool isButtonReleased(std::uint32_t button);
		bool isButtonDown(std::uint32_t button);

	private:
		float        m_Axises[4] { 0.0f };
		std::uint8_t m_Buttons[s_MaxMouseButtons] { 0 };
	};

	namespace Buttons
	{
		static constexpr std::uint32_t Mouse1      = 0;
		static constexpr std::uint32_t Mouse2      = 1;
		static constexpr std::uint32_t Mouse3      = 2;
		static constexpr std::uint32_t Mouse4      = 3;
		static constexpr std::uint32_t Mouse5      = 4;
		static constexpr std::uint32_t Mouse6      = 5;
		static constexpr std::uint32_t Mouse7      = 6;
		static constexpr std::uint32_t Mouse8      = 7;
		static constexpr std::uint32_t MouseLeft   = Mouse1;
		static constexpr std::uint32_t MouseRight  = Mouse2;
		static constexpr std::uint32_t MouseMiddle = Mouse3;
	} // namespace Buttons

	namespace Axises
	{
		static constexpr std::uint32_t MouseX       = 0;
		static constexpr std::uint32_t MouseY       = 1;
		static constexpr std::uint32_t MouseScrollX = 2;
		static constexpr std::uint32_t MouseScrollY = 3;
	} // namespace Axises
} // namespace Input