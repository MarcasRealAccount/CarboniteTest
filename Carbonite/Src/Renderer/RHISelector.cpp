#include "RHISelector.h"
#include "Renderer/OpenGL/Instance.h"

namespace Renderer
{
	std::unique_ptr<RHI::IInstance> SelectRHI()
	{
		// TODO(MarcasRealAccount): Add selection for more RHIs in the future, maybe through a user promt or argument passed to the executable!
		return std::make_unique<OpenGL::Instance>();
	}
} // namespace Renderer