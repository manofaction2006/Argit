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

		cam = MakeReference<Camera>(projection);

		RenderCommands::ClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Renderer2D::Init();
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);

		/*int index = 1;
		std::vector<UniformDescription> uniformData = {
			{(void*)glm::value_ptr(cam->getProjection()), "projection", UniformTypes::Mat4},
			{(void*)&index, "text", UniformTypes::Int},
		};

		texture->Bind(index);
		RenderCommands::DrawIndexedPrimitive(DrawPrimitiveType::Triangle, shader, vao, vb, ib, uniformData);*/

		Renderer2D::Begin(cam);
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, {100.0f,100.0f}, { 1.0f, 0.0f, 0.0f });
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

	Reference<Camera> cam;
	glm::mat4 projection;
	bool running = true;
};

Application* Argit::getApplication() {
	return new SandBoxApp{};
}