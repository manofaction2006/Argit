#pragma once
#include "Events/Event.h"

namespace Argit {
	class Layer
	{
	public:
		virtual void OnAttach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event& e) {}

		virtual ~Layer() = default;
	protected:
		Layer() = default;
	};
}
