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
	SandBoxApp() {

	}

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

		Utility::ImageData attackTextureData = Utility::ReadImageData("./asserts/Attack.png");

		Texture2DDescription attackDesc;
		attackDesc.data = attackTextureData.data;
		attackDesc.height = attackTextureData.height;
		attackDesc.width = attackTextureData.width;
		attackDesc.format = attackTextureData.numberOfChannels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
		attackDesc.textureName = attackTextureData.FileName;
		attackTexture = Texture2D::Create(attackDesc);

		Utility::ImageData walkTextureData = Utility::ReadImageData("./asserts/walk2.png");

		Texture2DDescription walkTextureDesc;
		walkTextureDesc.data = walkTextureData.data;
		walkTextureDesc.height = walkTextureData.height;
		walkTextureDesc.width = walkTextureData.width;
		walkTextureDesc.format = walkTextureData.numberOfChannels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
		walkTextureDesc.textureName = walkTextureData.FileName;
		walkTexture = Texture2D::Create(walkTextureDesc);

		float spriteWidth = 72;
		float spriteHeight = 60;

		attackAtlases = {};
		attackAtlases[0] = MakeReference<TextureAtlas>(attackTexture, spriteWidth, spriteHeight, 0, 0);
		attackAtlases[1] = MakeReference<TextureAtlas>(attackTexture, spriteWidth, spriteHeight, 1, 0);
		attackAtlases[2] = MakeReference<TextureAtlas>(attackTexture, spriteWidth, spriteHeight, 2, 0);
		attackAtlases[3] = MakeReference<TextureAtlas>(attackTexture, spriteWidth, spriteHeight, 3, 0);
		attackAtlases[4] = MakeReference<TextureAtlas>(attackTexture, spriteWidth, spriteHeight, 4, 0);
		attackAtlases[5] = MakeReference<TextureAtlas>(attackTexture, spriteWidth, spriteHeight, 5, 0);

		walkAtlases = {};
		walkAtlases[0] = MakeReference<TextureAtlas>(walkTexture, spriteWidth, spriteHeight, 0, 0);
		walkAtlases[1] = MakeReference<TextureAtlas>(walkTexture, spriteWidth, spriteHeight, 1, 0);
		walkAtlases[2] = MakeReference<TextureAtlas>(walkTexture, spriteWidth, spriteHeight, 2, 0);
		walkAtlases[3] = MakeReference<TextureAtlas>(walkTexture, spriteWidth, spriteHeight, 3, 0);
		walkAtlases[4] = MakeReference<TextureAtlas>(walkTexture, spriteWidth, spriteHeight, 4, 0);
		walkAtlases[5] = MakeReference<TextureAtlas>(walkTexture, spriteWidth, spriteHeight, 5, 0);


		RenderCommands::ClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		RenderCommands::EnableBlending();
		Renderer2D::Init();


		Renderer2D::RegisterTexture(walkTexture);
		Renderer2D::RegisterTexture(attackTexture);
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);

		Renderer2D::Begin(cam);
		if (state == PlayerState::Idel) {
			Renderer2D::DrawQuad({ 0.0,0.0 }, { 80.0f,80.0f }, 0, walkAtlases[5], { 1.0f,1.0f,1.0f });
		}
		else if (state == PlayerState::Attack) {
			Renderer2D::DrawQuad({ 0.0,0.0 }, { 80.0f,80.0f }, 0, attackAtlases[4], { 1.0f,1.0f,1.0f });
		}
		else if (state == PlayerState::Walking) {
			Renderer2D::DrawQuad({ 0.0,0.0 }, { 80.0f,80.0f }, 0, walkAtlases[0], { 1.0f,1.0f,1.0f });
		}
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
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnKeyDown));
		dispatcher.Dispatch<KeyReleasedEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnKeyRelease));
	}
	bool OnKeyRelease(KeyReleasedEvent& e) {
		if (e.GetKeyCode() == Key::E) {
			state = PlayerState::Idel;
		}

		if (e.GetKeyCode() == Key::A) {
			state = PlayerState::Idel;
			//translateX -= 10;
		}
		if (e.GetKeyCode() == Key::D) {
			state = PlayerState::Idel;
			//translateX += 10;
		}
		if (e.GetKeyCode() == Key::W) {
			state = PlayerState::Idel;
			//translateY += 10;
		}
		if (e.GetKeyCode() == Key::S) {
			state = PlayerState::Idel;
			//translateY -= 10;
		}
		return true;
	}
	bool OnKeyDown(KeyPressedEvent& e) {
		if (e.GetKeyCode() == Key::E) {
			state = PlayerState::Attack;
		}

		else if (e.GetKeyCode() == Key::A) {
			state = PlayerState::Walking;
			translateX -= 10;
		}
		else if (e.GetKeyCode() == Key::D) {
			state = PlayerState::Walking;
			translateX += 10;
		}
		else if (e.GetKeyCode() == Key::W) {
			state = PlayerState::Walking;
			translateY += 10;
		}
		else if (e.GetKeyCode() == Key::S) {
			state = PlayerState::Walking;
			translateY -= 10;
		}
		return true;
	}
	bool OnWindowClose(WindowCloseEvent& e) {
		running = false;

		return true;
	}
private:
	Reference<Window> window;
	Reference<Texture2D> attackTexture;
	Reference<Texture2D> walkTexture;
	std::array<Reference<TextureAtlas>, 6> attackAtlases;
	std::array<Reference<TextureAtlas>, 6> walkAtlases;

	int attackIndex = 0;
	int walkIndex = 0;

	PlayerState state = PlayerState::Idel;

	float translateX = 0;
	float translateY = 0;

	int animationIndexer = 0;

	Reference<Camera> cam;
	glm::mat4 projection;
	bool running = true;
};

Application* Argit::getApplication() {
	return new SandBoxApp{};
}