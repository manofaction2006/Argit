#include "pch.h"
#include "WindowsWindow.h"
#include "glfw/glfw3.h"

namespace Argit {
	WindowsWindow::WindowsWindow(WindowData data) : data({}), window(nullptr)
	{
		this->data = {};
		this->data.width = data.width;
		this->data.height = data.height;
		this->data.title = data.title;
		this->data.vsync = data.vsync;
	}

	uint32_t WindowsWindow::Width()
	{
		return data.width;
	}

	uint32_t WindowsWindow::Height()
	{
		return data.height;
	}

	bool WindowsWindow::Vsync()
	{
		return data.vsync;
	}

	void WindowsWindow::Init()
	{
		if (!glfwInit()) {
			std::cout << "Unable to Initialize Window Framework." << std::endl;
		}
		
		window = glfwCreateWindow(data.width, data.height, data.title, nullptr, nullptr);
		context = Context::Create(window);
		context->Init();


		if (data.vsync) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		glfwSetWindowUserPointer(window, &data);
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
	}


	void* WindowsWindow::getNativeWindow()
	{
		return window;
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

}