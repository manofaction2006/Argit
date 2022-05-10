#include "pch.h"
#include "VertexBuffer.h"
#include "Core/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Argit {
	Reference<VertexBuffer> VertexBuffer::Create(size_t size)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			return MakeReference<OpenGLVertexBuffer>(size);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}

}