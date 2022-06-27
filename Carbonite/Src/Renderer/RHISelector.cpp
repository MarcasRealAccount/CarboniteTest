#include "RHISelector.h"
#include "Renderer/OpenGL/OpenGLRHI.h"
#include "Renderer/RHI/IRHI.h"
#include "Utils/Log.h"

namespace
{
	static Renderer::RHI::IRHI* s_SelectedRHI = nullptr;
} // namespace

namespace Renderer
{
	static auto& getRHIs()
	{
		static auto s_RHIs = new std::vector<std::unique_ptr<Renderer::RHI::IRHI>>();
		return *s_RHIs;
	}

	static void SelectRHI()
	{
		// TODO(MarcasRealAccount): Select RHI based on priority and how well it works, instead of a first come first served basis
		for (auto& rhi : getRHIs())
		{
			if (rhi->isCompatible())
			{
				s_SelectedRHI = rhi.get();
				break;
			}
		}
		Log::GetOrCreateLogger("RHI")->trace("Selected '{}'", s_SelectedRHI->getName());
	}

	void RegisterRHI(std::unique_ptr<RHI::IRHI>&& rhi)
	{
		Log::GetOrCreateLogger("RHI")->trace("Registered '{}'", rhi->getName());
		getRHIs().emplace_back(std::move(rhi));
	}

	RHI::IRHI* GetRHI()
	{
		if (!s_SelectedRHI)
			SelectRHI();
		return s_SelectedRHI;
	}
} // namespace Renderer