#pragma once
#include "Core/Layer.h"
#include "Core/Window.h"

namespace Argit {
	class ImGuiLayer: public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event & e) override;

		void setWindow(const Reference<Window>& window) { m_window = window; }

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		Reference<Window> m_window;
		bool m_BlockEvents = true;
	};
}
