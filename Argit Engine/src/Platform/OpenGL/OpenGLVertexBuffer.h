#pragma once
#include "Renderer/VertexBuffer.h"

namespace Argit {
	class OpenGLVertexBuffer: public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t size);
		virtual void Bind() override;
		virtual void AddData(int offset, void* data, size_t size) override;
		virtual RendererId getRendererId() override;

		~OpenGLVertexBuffer();
	private:
		RendererId m_RendererId;
	};
}