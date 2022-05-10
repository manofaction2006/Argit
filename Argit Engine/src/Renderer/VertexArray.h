#pragma once
#include "Core/Base.h"
#include "RenderableObject.h"
#include "VertexBuffer.h"

namespace Argit {
	enum class LayoutDataType
	{
		Int,
		Float
	};

	struct LayoutElement {
		LayoutDataType type;
		bool normalize;
		int count;
	};

	struct LayoutDescription {
		std::vector<LayoutElement> elements;
		LayoutDescription(std::initializer_list<LayoutElement> layouts): elements(layouts){}
	};

	class VertexArray: public RenderableObject
	{
	public:
		static Reference<VertexArray> Create();

		virtual void AddBuffer(const Reference<VertexBuffer>& buffer, LayoutDescription layout) = 0;
		virtual void Bind() = 0;

		virtual ~VertexArray() = default;
	protected:
		VertexArray() = default;
	};
}
