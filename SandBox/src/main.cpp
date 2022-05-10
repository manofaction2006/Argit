#include "Argit.h"
#include <iostream>

using namespace Argit;

class SandBoxApp : public Application {
public:
	virtual void OnInit() override{
		WindowData data = {};
		data.width = 800;
		data.height = 410;
		data.title = "SandBox";
		data.vsync = true;
		window = Window::Create(data);
		window->setEventCallback(ARGIT_BIND_EVENT_FN(SandBoxApp::OnEvent));
		window->Init();

		RenderCommands::ClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);
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
	bool running = true;
};

Application* Argit::getApplication() {
	return new SandBoxApp{};
}