#include "RootDir.h"

#include <source_location>

namespace Utils
{
	std::filesystem::path RootDir()
	{
		return std::filesystem::path { std::source_location::current().file_name() }.parent_path();
	}
} // namespace Utils