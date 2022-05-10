#include "pch.h"
#include "WindowsWindow.h"
#include "glfw/glfw3.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Argit {
	WindowsWindow::WindowsWindow(WindowData data) : data({}), window(nullptr)
	{
		this->data = {};
		this->data.Width = data.width;
		this->data.Height = data.height;
		this->data.title = data.title;
		this->data.vsync = data.vsync;
	}

	uint32_t WindowsWindow::Width()
	{
		return data.Width;
	}

	uint32_t WindowsWindow::Height()
	{
		return data.Height;
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
		
		window = glfwCreateWindow(data.Width, data.Height, data.title, nullptr, nullptr);
		context = Context::Create(window);
		context->Init();


		if (data.vsync) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		glfwSetWindowUserPointer(window, &data);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.callback(event);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.callback(event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.callback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.callback(event);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.callback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.callback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.callback(event);
			});
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		context->Swap();
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