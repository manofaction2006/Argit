#pragma once
#include "RenderableObject.h"

namespace Argit {
	enum class TextureFormat
	{
		RGB,
		RGBA,
		RedInteger
	};

	struct Texture2DDescription {
		unsigned char* data;
		uint32_t width;
		uint32_t height;
		std::string textureName;
		TextureFormat format;
	};

	class Texture2D: public RenderableObject
	{
	public:
		static Reference<Texture2D> Create(const Texture2DDescription& description);

		virtual void Bind(uint16_t textureUnit) = 0;
		virtual uint32_t Height() = 0;
		virtual uint32_t Width() = 0;

		virtual ~Texture2D() = default;
	protected:
		Texture2D() = default;
	};
}
