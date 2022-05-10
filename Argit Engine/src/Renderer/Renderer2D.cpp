#include "pch.h"
#include "Renderer2D.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "RenderCommands.h"
#include "Core/Utility.h"
#include "Shader.h"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

namespace Argit {
	struct SquareVertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	struct RendererData {
		static const uint32_t MaxQuads = 250;
		static const uint32_t IndexCount = 6;
		static const uint32_t VertexCount = 4;
		static const uint32_t MaxIndices = MaxQuads * IndexCount;
		static const uint32_t MaxVertices = MaxQuads * VertexCount;

		Reference<VertexBuffer> quadBuffer;
		Reference<VertexArray> quadVertexArray;
		Reference<IndexBuffer> quadIB;
		Reference<Shader> quadShader;

		glm::vec4 quadPositions[4];

		std::vector<SquareVertex> vertices;
	} rendererData;

	Reference<Camera> Renderer2D::camera = nullptr;

	void Renderer2D::Init()
	{
		uint32_t* indices = new uint32_t[RendererData::MaxIndices];
		int offset = 0;
		for (int i = 0; i < rendererData.MaxIndices; i += rendererData.IndexCount) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += rendererData.VertexCount;
		}

		rendererData.quadIB = IndexBuffer::Create(rendererData.MaxIndices);
		rendererData.quadIB->AddData(0, indices, rendererData.MaxIndices);

		rendererData.quadBuffer = VertexBuffer::Create(rendererData.MaxVertices * sizeof(float));

		LayoutDescription layout = {
			{LayoutDataType::Float, false, 3},
			{LayoutDataType::Float, false, 3},
		};
		rendererData.quadVertexArray = VertexArray::Create();
		rendererData.quadVertexArray->AddBuffer(rendererData.quadBuffer, layout);

		rendererData.vertices = {};

		std::string vertSrc = Utility::ReadShaderSource("./asserts/VertexRenderer2D.glsl");
		std::string fragSrc = Utility::ReadShaderSource("./asserts/FragmentRenderer2D.glsl");
		rendererData.quadShader = Shader::Create();
		rendererData.quadShader->AddShader(ShaderTypes::VertexShader, vertSrc);
		rendererData.quadShader->AddShader(ShaderTypes::FragmentShader, fragSrc);
		rendererData.quadShader->Finalize();

		rendererData.quadPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		rendererData.quadPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
		rendererData.quadPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f};
		rendererData.quadPositions[3] = {-0.5f,  0.5f, 0.0f, 1.0f};

		delete[] indices;
	}

	void Renderer2D::Begin(const Reference<Camera>& cam)
	{
		camera = cam;
		rendererData.vertices.clear();
	}

	void Renderer2D::End()
	{
		flush(camera);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec3& color)
	{
		Draw(position, { 1.0f,1.0f }, 0, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
	{
		Draw(position, size, 0, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& color)
	{
		Draw(position, { 1.0f,1.0f }, angle, color);
	}

	void Renderer2D::flush(const Reference<Camera>& camera)
	{
		rendererData.quadBuffer->AddData(0, rendererData.vertices.data(), rendererData.vertices.size() * sizeof(SquareVertex));

		std::vector<UniformDescription> desc = {
			{(void*)glm::value_ptr(camera->getProjection()), "projection", UniformTypes::Mat4}
		};
		RenderCommands::DrawIndexedPrimitive(DrawPrimitiveType::Triangle, rendererData.quadShader, rendererData.quadVertexArray, rendererData.quadBuffer, rendererData.quadIB, desc);
		rendererData.vertices.clear();
	}

	void Renderer2D::Draw(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& color)
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, glm::vec3(position, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::scale(matrix, glm::vec3(size, 1.0f));

		SquareVertex vertices[4];

		vertices[0].position = matrix * rendererData.quadPositions[0];
		vertices[1].position = matrix * rendererData.quadPositions[1];
		vertices[2].position = matrix * rendererData.quadPositions[2];
		vertices[3].position = matrix * rendererData.quadPositions[3];

		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;

		if (rendererData.vertices.size() >= rendererData.MaxVertices) {
			flush(camera);
		}

		rendererData.vertices.push_back(vertices[0]);
		rendererData.vertices.push_back(vertices[1]);
		rendererData.vertices.push_back(vertices[2]);
		rendererData.vertices.push_back(vertices[3]);
	}

}