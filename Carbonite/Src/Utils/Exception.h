#pragma once

#include "RootDir.h"

#include <spdlog/fmt/fmt.h>

#include <filesystem>
#include <source_location>
#include <string>
#include <utility>

namespace Utils
{
	struct SourceLocation
	{
	public:
		SourceLocation(const std::source_location& location)
		    : m_File(std::filesystem::relative(location.file_name(), RootDir())), m_Function(location.function_name()), m_Line(location.line()), m_Column(location.column()) {}

		auto& file() const { return m_File; }
		auto& function() const { return m_Function; }
		auto  line() const { return m_Line; }
		auto  column() const { return m_Column; }

	private:
		std::filesystem::path m_File;
		std::string           m_Function;
		std::size_t           m_Line;
		std::size_t           m_Column;
	};

	struct Exception
	{
	public:
		Exception(const std::string& message, const std::source_location& location = std::source_location::current())
		    : m_Message(message), m_Location(location) {}
		Exception(std::string&& message, const std::source_location& location = std::source_location::current())
		    : m_Message(std::move(message)), m_Location(location) {}
		template <class... Args>
		Exception(fmt::format_string<Args...> format, Args&&... args, const std::source_location& location = std::source_location::current())
		    : m_Message(fmt::format(format, std::forward<Args>(args)...)), m_Location(location)
		{
		}

		auto& what() const { return m_Message; }
		auto& location() const { return m_Location; }

	private:
		std::string    m_Message;
		SourceLocation m_Location;
	};
} // namespace Utils

template <>
struct fmt::formatter<Utils::SourceLocation>
{
public:
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	template <class FormatContext>
	auto format(const Utils::SourceLocation& location, FormatContext& ctx) -> decltype(ctx.out())
	{
		return fmt::format_to(ctx.out(), "{}({}:{}): {}()", location.file().string(), location.line(), location.column(), location.function());
	}
};

template <>
struct fmt::formatter<Utils::Exception>
{
public:
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	template <class FormatContext>
	auto format(const Utils::Exception& exception, FormatContext& ctx) -> decltype(ctx.out())
	{
		return fmt::format_to(ctx.out(), "{}: \"{}\"", exception.location(), exception.what());
	}
};