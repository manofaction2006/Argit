#pragma once
#include "glm/glm/glm.hpp"

namespace Argit {
	enum class ClearType: uint32_t
	{
		Color,
		Depth,
		ColorAndDepth
	};
	class RenderCommands
	{
	public:
		static void Clear(ClearType type);
		static void ClearColor(const glm::vec4& color);
	private:
		RenderCommands() = default;
		~RenderCommands() = default;
	};
}
