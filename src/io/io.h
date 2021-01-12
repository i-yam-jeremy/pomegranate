#pragma once

#include <string>
#include <unordered_map>

#include "../geo/geo.h"

/*
	A namespace containing all functions related to file I/O for this project.
*/
namespace io {
	/*
		Exports the given scene to the given file path.
		@param path The output file path.
		@param mesh The mesh to be exported.
	*/
	void exportFbx(std::string path, Mesh& mesh);
	/*
		Returns the full contents of the given text file.
		@param path The path to the text file.
		@return The full contents of the text file.
	*/
	std::string loadTextFile(std::string path);
};