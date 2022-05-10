#pragma once
#include "Renderer/RenderCommands.h"

namespace Argit {
	class OpenGLRenderCommands : public RenderCommands
	{
	public:
		static void Clear(ClearType type);
		static void ClearColor(const glm::vec4& color);
	private:
		OpenGLRenderCommands() = default;
		~OpenGLRenderCommands() = default;
	};
}
