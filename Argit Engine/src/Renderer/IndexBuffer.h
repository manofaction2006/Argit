#pragma once
#include "RenderableObject.h"

namespace Argit {
	class IndexBuffer : public RenderableObject
	{
	public:
		static Reference<IndexBuffer> Create(uint32_t count);

		virtual void Bind() = 0;
		virtual void AddData(int offset, void* data, uint32_t count) = 0;
		virtual uint32_t getCount() = 0;

		virtual ~IndexBuffer() = default;
	protected:
		IndexBuffer() = default;
	};
}


