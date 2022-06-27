#pragma once

#include "ForwardDecl.h"
#include "IInstance.h"
#include "RHINode.h"

#include <memory>

class Window;

namespace Renderer::RHI
{
	class IRHI : public RHINode
	{
	public:
		IRHI(const std::string& name);
		IRHI(std::string&& name);

		virtual bool isCompatible()                 = 0;
		virtual void setWindowHints(Window& window) = 0;

		std::unique_ptr<IInstance>         newInstance(const std::string& name) { return newInstance(std::string { name }); }
		virtual std::unique_ptr<IInstance> newInstance(std::string&& name) = 0;
	};
} // namespace Renderer::RHI