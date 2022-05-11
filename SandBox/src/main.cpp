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

		float xbound = window->Width() / 2;
		float ybound = window->Height() / 2;
		projection = glm::ortho(-xbound, xbound, -ybound, ybound, -2.0f, 2.0f);
		cam = MakeReference<Camera>(projection);

		Utility::ImageData imgdata = Utility::ReadImageData("./asserts/wall.jpg");

		Texture2DDescription desc;
		desc.data = imgdata.data;
		desc.height = imgdata.height;
		desc.width = imgdata.width;
		desc.format = imgdata.numberOfChannels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
		texture = Texture2D::Create(desc);

		RenderCommands::ClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		RenderCommands::EnableBlending();
		Renderer2D::Init();
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);

		Renderer2D::Begin(cam);
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 50.0f, 50.0f }, 0.0f, texture,{ 1.0f, 0.0f, 1.0, });
		Renderer2D::End();

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
	Reference<Texture2D> texture;

	Reference<Camera> cam;
	glm::mat4 projection;
	bool running = true;
};

Application* Argit::getApplication() {
	return new SandBoxApp{};
}