#include "../RHISelector.h"
#include "OpenGLRHI.h"

static struct OpenGLRegisterer
{
	OpenGLRegisterer()
	{
		Renderer::RegisterRHI(std::make_unique<Renderer::OpenGL::OpenGLRHI>());
	}
} s_OpenGLRegisterer;