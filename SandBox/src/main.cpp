#include "Argit.h"
#include <iostream>

using namespace Argit;

class SandBoxApp : public Application {
public:
	virtual void OnInit() override{
		WindowData data = {};
		data.width = 800;
		data.height = (data.width * 9) / 16;
		data.title = "SandBox";
		data.vsync = true;
		window = Window::Create(data);
		window->setEventCallback(ARGIT_BIND_EVENT_FN(SandBoxApp::OnEvent));
		window->Init();

		float bufferData[] = {
			-50.0f, -50.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
			 50.0f, -50.5f, 0.0f,	1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
			 50.0f,  50.5f, 0.0f,	1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
			-50.0f,  50.5f, 0.0f,	1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		};
		vb = VertexBuffer::Create(sizeof(bufferData));
		vb->AddData(0, bufferData, sizeof(bufferData));

		uint32_t indices[] = { 0,1,2,2,3,0 };
		ib = IndexBuffer::Create(6);
		ib->AddData(0, indices, 6);

		LayoutDescription layout = {
			{LayoutDataType::Float, false, 3},
			{LayoutDataType::Float, false, 3},
			{LayoutDataType::Float, false, 2},
		};
		vao = VertexArray::Create();
		vao->AddBuffer(vb, layout);

		std::string vertSrc = Utility::ReadShaderSource("./asserts/Vertex.glsl");
		std::string fragSrc = Utility::ReadShaderSource("./asserts/Fragment.glsl");
		shader = Shader::Create();
		shader->AddShader(ShaderTypes::VertexShader, vertSrc);
		shader->AddShader(ShaderTypes::FragmentShader, fragSrc);
		shader->Finalize();

		float xbound = window->Width()/2;
		float ybound = window->Height()/2;
		prjection = glm::ortho(-xbound, xbound, -ybound, ybound, -2.0f, 2.0f);

		Utility::ImageData imgdata = Utility::ReadImageData("./asserts/wall.jpg");

		Texture2DDescription textureDescription;
		textureDescription.data = imgdata.data;
		textureDescription.height = imgdata.height;
		textureDescription.width = imgdata.width;
		if (imgdata.numberOfChannels == 3) {
			textureDescription.format = TextureFormat::RGB;
		}
		else {
			textureDescription.format = TextureFormat::RGBA;
		}

		texture = Texture2D::Create(textureDescription);

		RenderCommands::ClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);

		int index = 1;
		std::vector<UniformDescription> uniformData = {
			{(void*)glm::value_ptr(prjection), "projection", UniformTypes::Mat4},
			{(void*)&index, "text", UniformTypes::Int},
		};

		texture->Bind(index);
		RenderCommands::DrawIndexedPrimitive(DrawPrimitiveType::Triangle, shader, vao, vb, ib, uniformData);

		window->Update();
	}
	virtual void OnDestroy() override{
		std::cout << "destroy\n";
	}
	virtual bool isApplicationRunning() override {
		return running;
	}
	virtual const Reference<Window>& getWindow() override {
		return window;
	}
	void OnEvent(Event& e) {
		EventDispatcher dipatcher = EventDispatcher(e);
		dipatcher.Dispatch<WindowCloseEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnWindowClose));
	}
	bool OnWindowClose(WindowCloseEvent& e) {
		running = false;
		return true;
	}
private:
	Reference<Window> window;
	Reference<VertexBuffer> vb;
	Reference<IndexBuffer> ib;
	Reference<VertexArray> vao;
	Reference<Shader> shader;
	Reference<Texture2D> texture;
	glm::mat4 prjection;
	bool running = true;
};

Application* Argit::getApplication() {
	return new SandBoxApp{};
}