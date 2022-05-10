#pragma once
#include "Core/Base.h"

namespace Argit {

	class RenderableObject {
	public:
		virtual RendererId getRendererId() = 0;
	protected:
		RenderableObject() = default;
		virtual ~RenderableObject() = default;
	};
}