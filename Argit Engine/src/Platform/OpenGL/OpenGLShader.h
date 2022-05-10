#pragma once
#include "Renderer/Shader.h"
#include <unordered_map>

namespace Argit {
	class OpenGLShader: public Shader
	{
	public:
		OpenGLShader();

		virtual void AddShader(ShaderTypes type, std::string src) override;
		virtual void AddUniform(UniformDescription uniform) override;
		virtual void Finalize() override;
		virtual RendererId getRendererId() override;

		~OpenGLShader();
	private:
		std::vector<unsigned int> deleteVector;
		RendererId m_RendererId;
	};
}
