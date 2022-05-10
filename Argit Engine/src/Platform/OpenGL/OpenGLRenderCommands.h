#pragma once
#include "Renderer/RenderCommands.h"

namespace Argit {
	class OpenGLRenderCommands : public RenderCommands
	{
	public:
		static void Clear(ClearType type);
		static void ClearColor(const glm::vec4& color);
		static void DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index);
		static void DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<Shader>& shader, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index, const std::vector<UniformDescription>& uniformData);
	private:
		OpenGLRenderCommands() = default;
		~OpenGLRenderCommands() = default;
	};
}
