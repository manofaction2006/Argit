#pragma once

namespace Argit {
	enum class RenderingApi
	{
		OpenGL,
		Vulkan,
	};

	class RendererDetails
	{
	public:
		// TODO: Add Method to set Current Api
		// TODO: Add A Method to get All available Apis
		static RenderingApi getCurrentRendeingApi();
	private:
		static RenderingApi currentApi;
		RendererDetails() = default;
		~RendererDetails() = default;

	};

}