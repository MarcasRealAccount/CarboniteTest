#include "Carbonite.h"
#include "Utils/Core.h"
#include "Utils/Exception.h"
#include "Utils/Log.h"

#include <stdexcept>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	if constexpr (Core::s_IsConfigDist)
	{
		try
		{
			Carbonite::Get().run();
			Carbonite::Destroy();
		}
		catch (const Utils::Exception& e)
		{
			Log::Critical("Critical exception caught {}", e);
			return 1;
		}
	}
	else
	{
		Carbonite::Get().run();
		Carbonite::Destroy();
	}
}

#if BUILD_IS_SYSTEM_WINDOWS

#undef APIENTRY
#include <Windows.h>

int WinMain([[maybe_unused]] _In_ HINSTANCE hInstance, [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance, [[maybe_unused]] _In_ LPSTR lpszCmdLine, [[maybe_unused]] _In_ int nCmdShow)
{
	return main(__argc, __argv);
}

#endif