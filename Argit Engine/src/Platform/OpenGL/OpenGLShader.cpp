#include "pch.h"
#include "OpenGLShader.h"
#include "glew/glew.h"
#include "glm/glm/glm.hpp"

namespace Argit {
	uint32_t getOpenglShaderType(ShaderTypes type) {
		switch (type)
		{
		case Argit::ShaderTypes::VertexShader:
			return GL_VERTEX_SHADER;
			break;
		case Argit::ShaderTypes::FragmentShader:
			return GL_FRAGMENT_SHADER;
			break;
		default:
			break;
		}
	}


	OpenGLShader::OpenGLShader(): m_RendererId(0), deleteVector({})
	{
		m_RendererId = glCreateProgram();
	}

	void OpenGLShader::AddShader(ShaderTypes type, std::string src)
	{
		GLuint shader = glCreateShader(getOpenglShaderType(type));

		// Get strings for glShaderSource.
		const char* shadeerCode = src.c_str();
		glShaderSource(shader, 1, &shadeerCode, nullptr);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			for (char c : errorLog) {
				std::cout << c;
			}
			std::cout << std::endl;

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
			return;
		}
		glAttachShader(m_RendererId, shader);
		deleteVector.push_back(m_RendererId);
	}

	void OpenGLShader::AddUniform(UniformDescription uniform)
	{
		glUseProgram(m_RendererId);
		uint32_t uniformLocation = glGetUniformLocation(m_RendererId, uniform.uniformName);

		if (uniformLocation == -1) {
			std::cout << "uniform " << uniform.uniformName << " not found." << std::endl;
		}

		switch (uniform.type)
		{
		case UniformTypes::Int:
			glUniform1i(uniformLocation, *(const int*)uniform.data);
			break;
		case UniformTypes::Int2:
			glm::ivec2 vec = *(glm::ivec2*)uniform.data;
			glUniform2i(uniformLocation, vec[0], vec[1]);
			break;
		case UniformTypes::Int3:
			glUniform3iv(uniformLocation, 1, (const int*)uniform.data);
			break;
		case UniformTypes::Int4:
			glUniform4iv(uniformLocation, 1, (const int*)uniform.data);
			break;
		case UniformTypes::Float:
			glUniform1fv(uniformLocation, 1, (const float*)uniform.data);
			break;
		case UniformTypes::Float2:
			glUniform2fv(uniformLocation, 1, (const float*)uniform.data);
			break;
		case UniformTypes::Float3:
			glUniform3fv(uniformLocation, 1, (const float*)uniform.data);
			break;
		case UniformTypes::Float4:
			glUniform4fv(uniformLocation, 1, (const float*)uniform.data);
			break;
		case UniformTypes::Mat4:
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (const float*)uniform.data);
			break;
		default:
			break;
		}
	}

	void OpenGLShader::Finalize()
	{
		glLinkProgram(m_RendererId);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);
			for (char c : infoLog) {
				std::cout << c;
			}
			std::cout << std::endl;

			// We don't need the program anymore.
			glDeleteProgram(m_RendererId);
			return;
		}

		for (auto i : deleteVector) {
			glAttachShader(m_RendererId, i);
			glDeleteShader(i);
		}
	}

	RendererId OpenGLShader::getRendererId()
	{
		return m_RendererId;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

}