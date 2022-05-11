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

	void RenderCommands::EnableBlending()
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			OpenGLRenderCommands::EnableBlending();
		case RenderingApi::Vulkan:
			return;
		default:
			return;
			break;
		}
	}

	void RenderCommands::EnableDepthTesting()
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			OpenGLRenderCommands::EnableDepthTesting();
		case RenderingApi::Vulkan:
			return;
		default:
			return;
			break;
		}
	}

	void RenderCommands::DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			OpenGLRenderCommands::DrawIndexedPrimitive(primitive, vao, buffer, index);
		case RenderingApi::Vulkan:
			return;
		default:
			return;
			break;
		}
	}

	void RenderCommands::DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<Shader>& shader, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index, const std::vector<UniformDescription>& uniformData)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			OpenGLRenderCommands::DrawIndexedPrimitive(primitive, shader, vao, buffer, index, uniformData);
		case RenderingApi::Vulkan:
			return;
		default:
			return;
			break;
		}
	}

}