#include "pch.h"
#include "OpenGLContext.h"
#include "glew/glew.h"
#include "Core/Log.h"
#include "glfw/glfw3.h"

namespace Argit {
	OpenGLContext::OpenGLContext(void* window)
	{
		this->window = static_cast<GLFWwindow*>(window);
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK) {
			
		}
	}

	OpenGLContext::~OpenGLContext()
	{
		
	}

}