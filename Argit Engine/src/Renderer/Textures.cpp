#include "pch.h"
#include "Textures.h"
#include "Core/Renderer.h"
#include "Platform/OpenGL/OpenGLTextures.h"

namespace Argit {
	Reference<Texture2D> Texture2D::Create(const Texture2DDescription& description)
	{
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			return MakeReference<OpenGLTexture2D>(description);
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
	}

}