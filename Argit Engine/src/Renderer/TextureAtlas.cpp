#include "pch.h"
#include "TextureAtlas.h"

namespace Argit {


	TextureAtlas::TextureAtlas(const Reference<Texture2D>& texture, float spriteWidth, float spriteHeight, float x, float y, float spanX, float spanY): texture(texture), spriteWidth(spriteWidth), sptiteHeight(spriteHeight), textureCoords({})
	{
			float textureWidth = texture->Width();
			float textureHeight = texture->Height();
			float xbound = spriteWidth / textureWidth;
			float ybound = spriteHeight / textureHeight;
			std::array<glm::vec2, 4> textCoords = {};
			textureCoords[0] = { x * xbound, y * ybound };
			textureCoords[1] = { (x + spanX) * xbound, y * ybound };
			textureCoords[2] = { (x + spanX) * xbound, (y + spanY) * ybound };
			textureCoords[3] = { x * xbound, (y + spanY) * ybound };
	}

	std::array<glm::vec2, 4> TextureAtlas::getTextureCoordinates()
	{
		

		return textureCoords;
	}

}