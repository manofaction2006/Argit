#pragma once
#include "Renderer/Textures.h"

namespace Argit {
	class OpenGLTexture2D: public Texture2D
	{
	public:
		OpenGLTexture2D(const Texture2DDescription& description);

		virtual void Bind(uint16_t textureUnit) override;
		virtual uint32_t Height() override;
		virtual uint32_t Width() override;
		virtual RendererId getRendererId() override;

		~OpenGLTexture2D();
	private:
		RendererId m_RendererId;
		Texture2DDescription m_Description;
	};
}
