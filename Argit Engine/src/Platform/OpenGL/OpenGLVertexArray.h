#pragma once
#include "Renderer/VertexArray.h"

namespace Argit {
	class OpenGLVertexArray: public VertexArray
	{
	public:
		OpenGLVertexArray();

		virtual void AddBuffer(const Reference<VertexBuffer>& buffer, LayoutDescription layout) override;
		virtual RendererId getRendererId() override;
		virtual void Bind() override;

		~OpenGLVertexArray();
	private:
		RendererId m_RendererId;
	};
}
