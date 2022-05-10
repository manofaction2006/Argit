#pragma once
#include "Core/Window.h"
#include "Core/Context.h"

struct GLFWwindow;

namespace Argit {
	class WindowsWindow: public Window
	{
	public:
		WindowsWindow(WindowData data);

		virtual uint32_t Width() override;
		virtual uint32_t Height() override;

		virtual bool Vsync() override;
		virtual void Init() override;
		virtual void Update() override;

		virtual void setEventCallback(const EventCallbackFn& callback) override { data.callback = callback; };
		virtual void* getNativeWindow() override;
		~WindowsWindow();
	private:
		struct WindowsWindowData {
			uint32_t Width;
			uint32_t Height;
			const char* title;
			bool vsync;
			EventCallbackFn callback;
		}data;
		GLFWwindow* window;
		Reference<Context> context;
	};
}
