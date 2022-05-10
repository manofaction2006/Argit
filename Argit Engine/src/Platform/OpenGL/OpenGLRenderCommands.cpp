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

	void OpenGLRenderCommands::Clear(ClearType type)
	{
		glClear(getOpenglClearType(type));
	}

	void OpenGLRenderCommands::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

}