#include "pch.h"
#include "Renderer.h"

namespace Argit {
	RenderingApi RendererDetails::currentApi = RenderingApi::OpenGL;
	RenderingApi RendererDetails::getCurrentRendeingApi()
	{
		return currentApi;
	}
}
