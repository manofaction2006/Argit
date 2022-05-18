#include "Argit.h"
#include <iostream>
#include <thread>

using namespace Argit;

enum class PlayerState
{
	Attack,
	Idel,
	Walking
};

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

		RenderCommands::ClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		RenderCommands::EnableBlending();
		Renderer2D::Init();

		imgui = MakeReference<ImGuiLayer>();
		imgui->setWindow(window);

		stack.PushLayerBack(imgui);

		font = MakeReference<Font>("./asserts/OpenSan.ttf", 20);
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);

		Renderer2D::Begin(cam);
		Renderer2D::DrawString("HEllO.))00", { 0.0,0.0 }, font, glm::vec3(1.0f, 0.0f, 1.0f), 10);
		Renderer2D::End();

		imgui->Begin();
		ImGui::Begin("DebugInfo");
		ImGui::End();
		imgui->End();

		stack.UpdateAllLayers(deltaTime);
		window->Update();
	}
	virtual void OnDestroy() override{
	}
	virtual bool isApplicationRunning() override {
		return running;
	}
	virtual const Reference<Window>& getWindow() override {
		return window;
	}
	void OnEvent(Event& e) {
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnKeyDown));
		dispatcher.Dispatch<KeyReleasedEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnKeyRelease));

		stack.PassEventToAllLayers(e);
	}
	bool OnKeyRelease(KeyReleasedEvent& e) {

		return true;
	}
	bool OnKeyDown(KeyPressedEvent& e) {

		return true;
	}
	bool OnWindowClose(WindowCloseEvent& e) {
		running = false;

		return true;
	}
private:
	Reference<Window> window;

	Reference<ImGuiLayer> imgui;
	LayerStack stack;

	Reference<Font> font;

	Reference<Camera> cam;
	glm::mat4 projection;
	bool running = true;
};

Application* Argit::getApplication() {
	return new SandBoxApp{};
}