#pragma once
#include "glm/glm/glm.hpp"

namespace Argit {
	class Camera
	{
	public:
		Camera(const glm::mat4& matrix);

		virtual const glm::mat4& getProjection();

		virtual ~Camera();
	private:
		glm::mat4 projection;
	};
}
