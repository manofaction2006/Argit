#include "pch.h"
#include "RenderCommands.h"
#include "Core/Renderer.h"
#include "Platform/OpenGL/OpenGLRenderCommands.h"

namespace Argit {
	void RenderCommands::Clear(ClearType type)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			OpenGLRenderCommands::Clear(type);
		case RenderingApi::Vulkan:
			return ;
		default:
			return ;
			break;
		}
	}

	void RenderCommands::ClearColor(const glm::vec4& color)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			OpenGLRenderCommands::ClearColor(color);
		case RenderingApi::Vulkan:
			return;
		default:
			return;
			break;
		}
	}

}