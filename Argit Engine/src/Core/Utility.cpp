#include "pch.h"
#include "Utility.h"
#include <sstream>
#include <fstream>


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
	}
}