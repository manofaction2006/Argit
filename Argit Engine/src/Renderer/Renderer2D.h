#pragma once
#include "glm/glm/glm.hpp"
#include "Camera.h"
#include "TextureAtlas.h"
#include "Core/Base.h"

namespace Argit {
	class Renderer2D
	{
	public:
		static void Init();

		static void Begin(const Reference<Camera>& camera);
		static void End();

		static void RegisterTexture(const Reference<Texture2D>& texture);

		static void DrawQuad(const glm::vec2& position, const glm::vec3& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Reference<Texture2D>& texture,const glm::vec3& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Reference<TextureAtlas>& atlas,const glm::vec3& color);
	private:
		static void flush(const Reference<Camera>& cam);
		static void Draw(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& color, const Reference<Texture2D>& texture);

		static Reference<Camera> camera;
	};
}
