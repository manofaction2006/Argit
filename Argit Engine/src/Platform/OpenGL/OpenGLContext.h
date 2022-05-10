#pragma once
#include "Core/Context.h"

struct GLFWwindow;
namespace Argit {
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(void* window);
		virtual void Init() override;
		virtual void Swap() override;
		~OpenGLContext();
	private:
		GLFWwindow* window;
	};
}
