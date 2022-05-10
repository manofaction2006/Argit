#pragma once
#include "glm/glm/glm.hpp"
#include "Core/Base.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace Argit {
	enum class ClearType: uint32_t
	{
		Color,
		Depth,
		ColorAndDepth
	};

	enum class DrawPrimitiveType
	{
		Triangle,
		TriangleFan,
		TriangleStrip
	};
	class RenderCommands
	{
	public:
		static void Clear(ClearType type);
		static void ClearColor(const glm::vec4& color);
		static void DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index);
		static void DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<Shader>& shader, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index, const std::vector<UniformDescription>& uniformData);
	private:
		RenderCommands() = default;
		~RenderCommands() = default;
	};
}
