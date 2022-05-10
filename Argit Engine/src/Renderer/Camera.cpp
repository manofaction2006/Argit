#include "pch.h"
#include "Camera.h"

namespace Argit {
	Camera::Camera(const glm::mat4& matrix): projection(matrix)
	{
	}

	const glm::mat4& Camera::getProjection()
	{
		return projection;
	}

	Camera::~Camera()
	{
	}

}