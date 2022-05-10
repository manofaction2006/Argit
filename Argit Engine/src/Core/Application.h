#pragma once
#include <functional>
#include "Window.h"

namespace Argit {
	class Application
	{
	public:
		virtual void OnInit() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnDestroy() = 0;
		virtual bool isApplicationRunning() = 0;
		virtual const Reference<Window>& getWindow() = 0;
		virtual ~Application() = default;
	protected:
		Application() = default;
	};

	extern Application* getApplication();
}


