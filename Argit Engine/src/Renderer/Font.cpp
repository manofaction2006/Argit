#include "pch.h"
#include "Font.h"
#include "stb image/stb_image_write.h"
#include "FreeTypeLib/include/ft2build.h"
#include <sstream>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#define NUM_GLYPHS 128
#define GLYPHS_START 33

struct glyph_info {
	char ch;
	int x, y;
	float row, column;
	float x0, y0, x1, y1;	// coords of glyph in the texture atlas
	float x_off, y_off;   // left & top bearing when rendering
	float advance, height;        // x advance when rendering
} info[NUM_GLYPHS];

namespace Argit {
	void Flip(unsigned char* pixels, int pixelbuffersize)
	{
		// basically rewrites from bottom up...
		std::vector<unsigned char> flipped_pixels(pixels, pixels + pixelbuffersize);
		auto count = flipped_pixels.size();
		std::reverse(flipped_pixels.begin(), flipped_pixels.end());

		unsigned char* buff = (reinterpret_cast<unsigned char*>(&flipped_pixels[0]));
		const void* pnewdata = (const void*)buff;
		memcpy(pixels, pnewdata, count);
	}

	Font::Font(const char* filename, float fontSize): characters({})
	{
		FT_Library ft;
		FT_Face    face;

		FT_Init_FreeType(&ft);
		FT_New_Face(ft, filename, 0, &face);
		float fs = int(fontSize) << 6;
		FT_Set_Char_Size(face, 0, fs, 96, 96);

		int max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(NUM_GLYPHS));
		int tex_width = 1;
		while (tex_width < max_dim) tex_width <<= 1;
		int tex_height = tex_width;

		char* pixels = (char*)calloc(tex_width * tex_height, 1);
		int pen_x = 0, pen_y = 0;

		for (int i = GLYPHS_START; i < NUM_GLYPHS; ++i) {
			FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
			FT_Bitmap* bmp = &face->glyph->bitmap;

			if (pen_x + bmp->width >= tex_width) {
				pen_x = 0;
				pen_y += ((face->size->metrics.height >> 6) + 10);
			}

			for (int row = 0; row < bmp->rows; ++row) {
				for (int col = 0; col < bmp->width; ++col) {
					int x = pen_x + col ;
					int y = pen_y + row ;
					info[i].x = x;
					info[i].y = y;
					pixels[y * tex_width + x] = bmp->buffer[(row * bmp->pitch + col)];
				}
			}
			info[i].ch = i;
			info[i].x0 = pen_x;
			info[i].y0 = pen_y;
			info[i].x1 = pen_x + bmp->width;
			info[i].y1 = pen_y + bmp->rows;
			info[i].height = bmp->rows;

			info[i].x_off = face->glyph->bitmap_left;
			info[i].y_off = face->glyph->bitmap_top;
			info[i].advance = face->glyph->advance.x >> 6;
			


			pen_x += bmp->width + 1;
		}

		FT_Done_FreeType(ft);

		unsigned char* png_data = (unsigned char*)calloc(tex_width * tex_height * 4, 1);
		for (int i = 0; i < (tex_width * tex_height); ++i) {
			png_data[i * 4 + 0] |= pixels[i];
			png_data[i * 4 + 1] |= pixels[i];
			png_data[i * 4 + 2] |= pixels[i];
			png_data[i * 4 + 3] = png_data[i * 4 + 0] | png_data[i * 4 + 1] | png_data[i * 4 + 2];
		}

		Texture2DDescription desc;
		desc.data = png_data;
		desc.width = tex_width;
		desc.height = tex_height;
		desc.format = TextureFormat::RGBA;
		desc.textureName = filename;
		texture = Texture2D::Create(desc);


		for (int i = GLYPHS_START; i < NUM_GLYPHS; i++) {
			float width = info[i].x1 - info[i].x0;
			float height = info[i].y1 - info[i].y0;

			Reference<FontAtlas> atlas = MakeReference<FontAtlas>(texture, info[i].x0, info[i].y0, width, height);
			characters.insert(std::pair(info[i].ch, atlas));
		}
		free(png_data);
		free(pixels);
	}



	const Reference<FontAtlas>& Font::getCharacter(char character)
	{
		return characters.at(character);
	}

	Font::~Font()
	{
	}

	FontAtlas::FontAtlas(Reference<Texture2D> texture, float charX, float charY, float charWidth, float charHeight): textureCoords({}), characterWidth(charWidth), characterHeight(charHeight), texture(texture)
	{
		float boundx0 = charX / texture->Width();
		float boundy0 = charY / texture->Height();

		float boundx1 = (charX + charWidth) / texture->Width();
		float boundy1 = (charY + charHeight)/ texture->Height();

		textureCoords = {
			glm::vec2{boundx0, boundy1},
			glm::vec2{boundx1, boundy1},
			glm::vec2{boundx1, boundy0},
			glm::vec2{boundx0, boundy0},
		};
	}

	float FontAtlas::getCharWidth()
	{
		return characterWidth;
	}

	float FontAtlas::getCharHeight()
	{
		return characterHeight;
	}

	const Reference<Texture2D>& FontAtlas::getTexture()
	{
		return texture;
	}

	std::array<glm::vec2, 4> FontAtlas::getCharacterCoords()
	{
		return textureCoords;
	}


}