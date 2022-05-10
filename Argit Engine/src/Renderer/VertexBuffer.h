#pragma once
#include "RenderableObject.h"

namespace Argit {
	class VertexBuffer: public RenderableObject
	{
	public:
		static Reference<VertexBuffer> Create(size_t size);

		virtual void Bind() = 0;
		virtual void AddData(int offset, void* data, size_t size) = 0;

		virtual ~VertexBuffer() = default;
	protected:
		VertexBuffer() = default;
	};
}
