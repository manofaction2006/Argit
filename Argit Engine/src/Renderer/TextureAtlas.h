#pragma once
#include "Textures.h"
#include "glm/glm/glm.hpp"
#include <array>

namespace Argit {
	class FontAtlas;
	class TextureAtlas final
	{
	public:
		TextureAtlas(const Reference<Texture2D>& texture, float spriteWidth, float spriteHeight, float x, float y, float spanX = 1, float spanY = 1);
		TextureAtlas() = default;
		const Reference<Texture2D>& getTexture() { return texture; };
		float getSpriteWidth() { return spriteWidth; }
		float getSpriteHeight() { return sptiteHeight; }
		friend class FontAtlas;
		std::array<glm::vec2, 4> getTextureCoordinates();
	private:
		Reference<Texture2D> texture;
		float spriteWidth;
		float sptiteHeight;
		std::array<glm::vec2, 4> textureCoords;
	};
}
