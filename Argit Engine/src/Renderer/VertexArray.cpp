#include "pch.h"
#include "VertexArray.h"
#include "Core/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Argit {
	Reference<VertexArray> VertexArray::Create()
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			return MakeReference<OpenGLVertexArray>();
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}

}