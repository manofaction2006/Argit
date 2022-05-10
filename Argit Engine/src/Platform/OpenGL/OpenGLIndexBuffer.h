#pragma once
#include "Renderer/IndexBuffer.h"

namespace Argit {
	class OpenGLIndexBuffer: public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t count);

		virtual void Bind() override;
		virtual void AddData(int offset, void* data, uint32_t count) override;
		virtual RendererId getRendererId() override;
		virtual uint32_t getCount() override;

		~OpenGLIndexBuffer() ;
	private:
		RendererId m_RendererId;
		uint32_t count;
	};
}
