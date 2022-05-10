#include "pch.h"
#include "Context.h"
#include "Renderer.h"
#include "Assert.h"
#include "Log.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Argit {
	Reference<Context> Context::Create(void* window)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			return MakeReference<OpenGLContext>(window);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}

}