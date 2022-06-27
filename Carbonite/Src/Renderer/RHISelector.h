#pragma once

#include "Renderer/RHI/ForwardDecl.h"

namespace Renderer
{
	void RegisterRHI(std::unique_ptr<RHI::IRHI>&& rhi);

	RHI::IRHI* GetRHI();
} // namespace Renderer