#pragma once

#include "Renderer/RHI/IInstance.h"

namespace Renderer
{
	std::unique_ptr<RHI::IInstance> SelectRHI();
}