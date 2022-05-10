#include "pch.h"
#include "Window.h"
#include "Platform.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Argit {

    Reference<Window> Window::Create(WindowData data)
    {
		switch (currentPlatform)
		{
		case Platform::Windows:
			return MakeReference<WindowsWindow>(data);
			break;
		case Platform::Mac:
			break;
		case Platform::Linux:
			break;
		case Platform::Android:
			break;
		case Platform::Ios:
			break;
		default:
			break;
		}
    }

}