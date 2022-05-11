#include "pch.h"
#include "OpenGLTextures.h"
#include "glew/glew.h"

namespace Argit {
	static uint32_t getOpenglFormat(TextureFormat format) {
		switch (format)
		{
		case Argit::TextureFormat::RGB:
			return GL_RGB;
			break;
		case Argit::TextureFormat::RGBA:
			return GL_RGBA;
			break;
		case Argit::TextureFormat::RedInteger:
			return GL_RED_INTEGER;
			break;
		default:
			break;
		}
	}

	static uint32_t getTextureUnit(uint16_t unit) {
		switch (unit)
		{
		case 0: return GL_TEXTURE0;
		case 1: return GL_TEXTURE1;
		case 2: return GL_TEXTURE2;
		case 3: return GL_TEXTURE3;
		case 4: return GL_TEXTURE4;
		case 5: return GL_TEXTURE5;
		case 6: return GL_TEXTURE6;
		case 7: return GL_TEXTURE7;
		case 8: return GL_TEXTURE8;
		case 9: return GL_TEXTURE9;
		case 10: return GL_TEXTURE10;
		case 11: return GL_TEXTURE11;
		case 12: return GL_TEXTURE12;
		case 13: return GL_TEXTURE13;
		case 14: return GL_TEXTURE14;
		case 15: return GL_TEXTURE15;
		case 16: return GL_TEXTURE16;
		case 17: return GL_TEXTURE17;
		case 18: return GL_TEXTURE18;
		case 19: return GL_TEXTURE19;
		case 20: return GL_TEXTURE20;
		case 21: return GL_TEXTURE21;
		case 22: return GL_TEXTURE22;
		case 23: return GL_TEXTURE23;
		case 24: return GL_TEXTURE24;
		case 25: return GL_TEXTURE25;
		case 26: return GL_TEXTURE26;
		case 27: return GL_TEXTURE27;
		case 28: return GL_TEXTURE28;
		case 29: return GL_TEXTURE29;
		case 30: return GL_TEXTURE30;
		case 31: return GL_TEXTURE31;
		default:
			break;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const Texture2DDescription& description): m_RendererId(0), m_Description(description)
	{
		uint32_t width = description.width;
		uint32_t height = description.height;
		uint32_t format = getOpenglFormat(description.format);

		glGenTextures(1, &m_RendererId);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, description.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLTexture2D::Bind(uint16_t textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}

	uint32_t OpenGLTexture2D::Height()
	{
		return m_Description.height;
	}

	uint32_t OpenGLTexture2D::Width()
	{
		return m_Description.width;
	}

	RendererId OpenGLTexture2D::getRendererId()
	{
		return m_RendererId;
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererId);
	}

}