#include "pch.h"
#include "Shader.h"
#include "Core/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Argit {
    Reference<Shader> Shader::Create()
    {
		switch (RendererDetails::getCurrentRendeingApi())
		{
		case RenderingApi::OpenGL:
			return MakeReference<OpenGLShader>();
		case RenderingApi::Vulkan:
			return nullptr;
		default:
			return nullptr;
			break;
		}
    }

}