#include "pch.h"
#include "IndexBuffer.h"
#include "Core/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Argit {
	Reference<IndexBuffer> IndexBuffer::Create(uint32_t count)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			return MakeReference<OpenGLIndexBuffer>(count);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}

}