#pragma once
#include "Base.h"
#include "Events/Event.h"
#include "Context.h"

namespace Argit {
	struct WindowData {
		const char* title = "Argit Window";
		uint32_t width = 800;
		uint32_t height = 410;
		bool vsync = true;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static Reference<Window> Create(WindowData data);

		virtual uint32_t Width() = 0;
		virtual uint32_t Height() = 0;
		
		virtual bool Vsync() = 0;
		virtual void Init() = 0;
		virtual void Update() = 0;


		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void* getNativeWindow() = 0;
	protected:
		Window() = default;
		virtual ~Window() = default;
	};
}
