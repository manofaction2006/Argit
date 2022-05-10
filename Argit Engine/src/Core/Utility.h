#pragma once

namespace Argit {
	namespace Utility {
		struct ImageData {
			unsigned char* data;
			uint32_t width;
			uint32_t height;
			uint32_t numberOfChannels;
		};
		std::string ReadShaderSource(const char* filename);
		ImageData ReadImageData(const char* filename);
	}
}