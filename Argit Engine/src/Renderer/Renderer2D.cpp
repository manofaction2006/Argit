#include "pch.h"
#include "Renderer2D.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "RenderCommands.h"
#include "Core/Utility.h"
#include "Shader.h"
#include <string>
#include "Textures.h"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <array>
#include <sstream>

namespace Argit {
	struct SquareVertex {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 textCoords;
		float textureIndex;
	};

	char* getTextureUniformName(int i) {
		char buffer[100];
		sprintf_s(buffer, "textures[%d]", i);
		return buffer;
	}

	struct Color {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};

	struct RendererData {
		static const uint32_t MaxQuads = 50;
		static const uint32_t IndexCount = 6;
		static const uint32_t VertexCount = 4;
		static const uint32_t MaxIndices = MaxQuads * IndexCount;
		static const uint32_t MaxVertices = MaxQuads * VertexCount;
		static const uint16_t MaxTextures = 16;

		Reference<VertexBuffer> quadBuffer;
		Reference<VertexArray> quadVertexArray;
		Reference<IndexBuffer> quadIB;
		Reference<Shader> quadShader;

		std::array<Reference<Texture2D>, 16> textures;
		Reference<Texture2D> BlankTexture;
		uint32_t textureIndex = 1;

		glm::vec4 quadPositions[4];
		glm::vec2 textureCoords[4];

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

		rendererData.quadBuffer = VertexBuffer::Create(rendererData.MaxQuads * sizeof(SquareVertex));

		LayoutDescription layout = {
			{LayoutDataType::Float, false, 3},
			{LayoutDataType::Float, false, 3},
			{LayoutDataType::Float, false, 2},
			{LayoutDataType::Float, false, 1},
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

		rendererData.quadPositions[0] = {-0.5f, -0.5f, 1.0f, 1.0f};
		rendererData.quadPositions[1] = { 0.5f, -0.5f, 1.0f, 1.0f};
		rendererData.quadPositions[2] = { 0.5f,  0.5f, 1.0f, 1.0f};
		rendererData.quadPositions[3] = {-0.5f,  0.5f, 1.0f, 1.0f};
		
		
		rendererData.textureCoords[0] = { 0.0f, 0.0f };
		rendererData.textureCoords[1] = { 1.0f, 0.0f };
		rendererData.textureCoords[2] = { 1.0f, 1.0f };
		rendererData.textureCoords[3] = { 0.0f, 1.0f };

		int width = 10;
		int height = 10;
		Color* whiteData = new Color[width*height];

		for (int i = 0; i < width * height; i++) {
			whiteData[i].r = 255;
			whiteData[i].g = 255;
			whiteData[i].b = 255;
			whiteData[i].a = 255;
		}

		Texture2DDescription description;
		description.data = reinterpret_cast<unsigned char*>(whiteData);
		description.width = width;
		description.height = height;
		description.format = TextureFormat::RGBA;

		rendererData.BlankTexture = Texture2D::Create(description);
		rendererData.textures[0] = rendererData.BlankTexture;

		delete[] whiteData;
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
		Draw(position, { 1.0f,1.0f }, 0.0f, color, rendererData.BlankTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
	{
		Draw(position, size, 0.0f, color, rendererData.BlankTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& color)
	{
		Draw(position, size, angle, color, rendererData.BlankTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Reference<Texture2D>& texture, const glm::vec3& color)
	{
		Draw(position, size, angle, color, texture);
	}

	void Renderer2D::flush(const Reference<Camera>& camera)
	{
		rendererData.quadBuffer->AddData(0, rendererData.vertices.data(), rendererData.vertices.size() * sizeof(SquareVertex));

		std::vector<UniformDescription> desc = {
			{(void*)glm::value_ptr(camera->getProjection()), "projection", UniformTypes::Mat4}
		};

		std::string str = "";
		for (int i = 0; i < rendererData.textureIndex; i++) {
			int index = i;
			str = getTextureUniformName(i);
			desc.emplace_back((void*)&index, str, UniformTypes::Int);
			rendererData.textures[i]->Bind(i);
		}
		

		RenderCommands::DrawIndexedPrimitive(DrawPrimitiveType::Triangle, rendererData.quadShader, rendererData.quadVertexArray, rendererData.quadBuffer, rendererData.quadIB, desc);
		rendererData.vertices.clear();
	}

	void Renderer2D::Draw(const glm::vec2& position, const glm::vec2& size, float angle, const glm::vec3& color, const Reference<Texture2D>& texture)
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix *= glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
		matrix *= glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

		SquareVertex vertices[4];

		vertices[0].position = matrix * rendererData.quadPositions[0];
		vertices[1].position = matrix * rendererData.quadPositions[1];
		vertices[2].position = matrix * rendererData.quadPositions[2];
		vertices[3].position = matrix * rendererData.quadPositions[3];

		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;

		vertices[0].textCoords = rendererData.textureCoords[0];
		vertices[1].textCoords = rendererData.textureCoords[1];
		vertices[2].textCoords = rendererData.textureCoords[2];
		vertices[3].textCoords = rendererData.textureCoords[3];

		int textureId = 0;
		auto i = std::find(rendererData.textures.begin() + 1, rendererData.textures.end(), texture);

		if (texture == rendererData.BlankTexture) {
			textureId = 0;
		}
		else if (i != rendererData.textures.end()) {
			textureId = i - rendererData.textures.begin();
		}
		else {
			textureId = rendererData.textureIndex;
			rendererData.textures[textureId] = texture;
			rendererData.textureIndex++;
		}

		vertices[0].textureIndex = textureId;
		vertices[1].textureIndex = textureId;
		vertices[2].textureIndex = textureId;
		vertices[3].textureIndex = textureId;



		if (rendererData.vertices.size() >= rendererData.MaxVertices) {
			flush(camera);
		}

		rendererData.vertices.push_back(vertices[0]);
		rendererData.vertices.push_back(vertices[1]);
		rendererData.vertices.push_back(vertices[2]);
		rendererData.vertices.push_back(vertices[3]);
	}

}