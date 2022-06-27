#include "IRHI.h"

namespace Renderer::RHI
{
	IRHI::IRHI(const std::string& name)
	    : RHINode(name) {}

	IRHI::IRHI(std::string&& name)
	    : RHINode(std::move(name)) {}
} // namespace Renderer::RHI