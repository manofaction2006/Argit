#include "pch.h"
#include "Utility.h"
#include <sstream>
#include <fstream>
#include "stb image/stb_image.h"

namespace Argit {
	namespace Utility {
		std::string ReadShaderSource(const char* filename)
		{
			std::fstream stream;
			stream.open(filename, std::ios::in);
			std::string buffer;
			
			std::string line = "";

			while (std::getline(stream, line)) {
				buffer.append(line);
				buffer.append("\n");
			}

			stream.close();
			return buffer;
		}
		ImageData ReadImageData(const char* filename)
		{
			stbi_set_flip_vertically_on_load(true);

			int width, height, nrChannels;
			unsigned char* data = stbi_load(filename, & width, & height, & nrChannels, 0);

			if (!data) {
				std::cout << "data not loaded" << std::endl;
			}

			ImageData imgData = {};
			imgData.width = width;
			imgData.height = height;
			imgData.numberOfChannels = nrChannels;
			imgData.data = data;
			imgData.FileName = filename;
			return imgData;
		}
	}
}