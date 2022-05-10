#pragma once
#include "Renderer/RenderableObject.h"

namespace Argit {
	enum class ShaderTypes
	{
		VertexShader,
		FragmentShader
	};

	enum class UniformTypes
	{
		Int,
		Int2,
		Int3,
		Int4,

		Float,
		Float2,
		Float3,
		Float4,

		Mat4,
	};

	struct UniformDescription {
		void* data;
		const char* uniformName;
		UniformTypes type;
	};

	class Shader: public RenderableObject
	{
	public:
		static Reference<Shader> Create();
		
		virtual void AddShader(ShaderTypes type, std::string src) = 0;
		virtual void AddUniform(UniformDescription uniform) = 0;
		virtual void Finalize() = 0;

		virtual ~Shader() = default;
	protected:
		Shader() = default;
	};
}
