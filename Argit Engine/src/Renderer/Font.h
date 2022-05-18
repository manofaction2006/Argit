#pragma once
#include <unordered_map>

#include "Core/Base.h"
#include "Renderer/Textures.h"
#include "Renderer/TextureAtlas.h"

namespace Argit {
	class FontAtlas {
	public:
		FontAtlas(Reference<Texture2D> texture, float charX, float charY, float charWidth, float charHeight);
		float getCharWidth();
		float getCharHeight();
		const Reference<Texture2D>& getTexture();
		std::array<glm::vec2, 4> getCharacterCoords();
	private:
		std::array<glm::vec2, 4> textureCoords;
		float characterWidth;
		float characterHeight;
		Reference<Texture2D> texture;
	};

	class Font final
	{
	public:
		Font(const char* filename, float fontSize = 18);
		const Reference<FontAtlas>& getCharacter(char character);
		const Reference<Texture2D>& getTexture() { return texture; }
		~Font();
	private:
		Reference<Texture2D> texture;
		std::unordered_map<char, Reference<FontAtlas>> characters;
	};
}
