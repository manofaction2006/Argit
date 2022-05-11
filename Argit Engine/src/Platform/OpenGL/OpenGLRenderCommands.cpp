#include "pch.h"
#include "OpenGLRenderCommands.h"
#include "glew/glew.h"

namespace Argit {
	static enum class OpenglClearTypes
	{
		Color = GL_COLOR_BUFFER_BIT,
		Depth = GL_DEPTH_BUFFER_BIT,
		ColorAndDepth = Color|Depth
	};

	static enum class OpenglDrawPrimitiveType {
		Triangle = GL_TRIANGLES,
		TriangleFan = GL_TRIANGLE_FAN,
		TriangleStrip = GL_TRIANGLE_STRIP
	};

	static uint32_t getOpenglClearType(ClearType type) {
		switch (type)
		{
		case Argit::ClearType::Color:
			return static_cast<uint32_t>(OpenglClearTypes::Color);
			break;
		case Argit::ClearType::Depth:
			return static_cast<uint32_t>(OpenglClearTypes::Depth);
			break;
		case Argit::ClearType::ColorAndDepth:
			return static_cast<uint32_t>(OpenglClearTypes::ColorAndDepth);
			break;
		default:
			break;
		}
	}

	static OpenglDrawPrimitiveType getOpenglPrimitiveType(DrawPrimitiveType type) {
		switch (type)
		{
		case Argit::DrawPrimitiveType::Triangle:
			return OpenglDrawPrimitiveType::Triangle;
			break;
		case Argit::DrawPrimitiveType::TriangleFan:
			return OpenglDrawPrimitiveType::TriangleFan;
			break;
		case Argit::DrawPrimitiveType::TriangleStrip:
			return OpenglDrawPrimitiveType::TriangleStrip;
			break;
		default:
			break;
		}
	}

	void OpenGLRenderCommands::Clear(ClearType type)
	{
		glClear(getOpenglClearType(type));
	}

	void OpenGLRenderCommands::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderCommands::EnableBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderCommands::EnableDepthTesting()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}


	void OpenGLRenderCommands::DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index)
	{
		vao->Bind();
		index->Bind();
		glDrawElements((uint32_t)getOpenglPrimitiveType(primitive), index->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderCommands::DrawIndexedPrimitive(DrawPrimitiveType primitive, const Reference<Shader>& shader, const Reference<VertexArray>& vao, const Reference<VertexBuffer>& buffer, const Reference<IndexBuffer>& index, const std::vector<UniformDescription>& uniformData)
	{
		glUseProgram(shader->getRendererId());

		for (auto& uniform : uniformData) {
			shader->AddUniform(uniform);
		}

		vao->Bind();
		index->Bind();
		glDrawElements((uint32_t)getOpenglPrimitiveType(primitive), index->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}