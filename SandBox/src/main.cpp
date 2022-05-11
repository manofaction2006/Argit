#include "Argit.h"
#include <iostream>
#include <thread>

using namespace Argit;

enum class PlayerState
{
	Attack,
	Idel
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

		Utility::ImageData imgdata = Utility::ReadImageData("./asserts/Attack.png");

		Texture2DDescription desc;
		desc.data = imgdata.data;
		desc.height = imgdata.height;
		desc.width = imgdata.width;
		desc.format = imgdata.numberOfChannels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
		texture = Texture2D::Create(desc);

		Utility::ImageData walkTextureData = Utility::ReadImageData("./asserts/walk2.png");

		Texture2DDescription walkDesc;
		walkDesc.data = walkTextureData.data;
		walkDesc.height = walkTextureData.height;
		walkDesc.width = walkTextureData.width;
		walkDesc.format = walkTextureData.numberOfChannels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
		walkTexture = Texture2D::Create(walkDesc);

		float spriteWidth = 72;
		float spriteHeight = 60;

		attackAtlases = {};
		attackAtlases[0] = MakeReference<TextureAtlas>(texture, spriteWidth, spriteHeight, 0, 0);
		attackAtlases[1] = MakeReference<TextureAtlas>(texture, spriteWidth, spriteHeight, 1, 0);
		attackAtlases[2] = MakeReference<TextureAtlas>(texture, spriteWidth, spriteHeight, 2, 0);
		attackAtlases[3] = MakeReference<TextureAtlas>(texture, spriteWidth, spriteHeight, 3, 0);
		attackAtlases[4] = MakeReference<TextureAtlas>(texture, spriteWidth, spriteHeight, 4, 0);
		attackAtlases[5] = MakeReference<TextureAtlas>(texture, spriteWidth, spriteHeight, 5, 0);

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
	}
	virtual void OnUpdate(float deltaTime) override{
		RenderCommands::Clear(ClearType::ColorAndDepth);
		if (state == PlayerState::Attack) {
			if (attackIndex == 5) {
				attackIndex = 0;
				state = PlayerState::Idel;
			}
			if (animationIndexer % 4 == 0) {
				attackIndex++;
			}
		}

		Renderer2D::Begin(cam);
		Renderer2D::DrawQuad({ translateX, translateY }, { 80.0f, 80.0f }, 0.0f, attackAtlases[attackIndex], {1.0f, 1.0f, 1.0,});
		//Renderer2D::DrawQuad({ -144.0f, 0.0f }, { 80.0f, 80.0f }, 0.0f, atlases[1], {1.0f, 1.0f, 1.0,});
		//Renderer2D::DrawQuad({ -72.0f, 0.0f }, { 80.0f, 80.0f }, 0.0f, atlases[2], {1.0f, 1.0f, 1.0,});
		//Renderer2D::DrawQuad({  0.0f, 0.0f }, { 80.0f, 80.0f }, 0.0f, atlases[3], {1.0f, 1.0f, 1.0,});
		//Renderer2D::DrawQuad({  72.0f, 0.0f }, { 80.0f, 80.0f }, 0.0f, atlases[4], {1.0f, 1.0f, 1.0,});
		//Renderer2D::DrawQuad({  144.0f, 0.0f }, { 80.0f, 80.0f }, 0.0f, atlases[5], {1.0f, 1.0f, 1.0,});
		Renderer2D::End();
		
		animationIndexer += 0.002 * deltaTime;

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
		dispatcher.Dispatch<KeyPressedEvent>(ARGIT_BIND_EVENT_FN(SandBoxApp::OnKeyPress));
	}
	bool OnKeyPress(KeyPressedEvent& e) {
		if (e.GetKeyCode() == Key::E) {
			state = PlayerState::Attack;
		}

		if (e.GetKeyCode() == Key::A) {
			translateX -= 10;
		}
		if (e.GetKeyCode() == Key::D) {
			translateX += 10;
		}
		if (e.GetKeyCode() == Key::W) {
			translateY += 10;
		}
		if (e.GetKeyCode() == Key::S) {
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
	Reference<Texture2D> texture;
	Reference<Texture2D> walkTexture;
	std::array<Reference<TextureAtlas>, 6> attackAtlases;
	std::array<Reference<TextureAtlas>, 6> walkAtlases;

	int attackIndex = 0;

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