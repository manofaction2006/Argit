#pragma once
#include "Base.h"
#include "Log.h"
#include "Window.h"

namespace Argit {
	class Context
	{
	public:
		static Reference<Context> Create(void* window);
		virtual void Init() = 0;
		virtual void Swap() = 0;
		virtual void* getNativeContext() = 0;
		virtual ~Context() = default;
	protected:
		Context() = default;
	};
}
