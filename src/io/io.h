#pragma once

#include <string>
#include <unordered_map>

#include "../geo/geo.h"
#include "../lsystem/Lsystem.h"

/*
	A namespace containing all functions related to file I/O for this project.
*/
namespace io {
	/*
		Exports the given Lsystem output as points for a rig to be used 
		within Houdini.
		@param path The output file path.
		@param out The Lsystem output to use for the rig.
	*/
	void exportCSVRig(std::string path, std::shared_ptr<lsystem::Output> out);
	/*
		Exports the given mesh to the given file path.
		@param path The output file path.
		@param mesh The mesh to be exported.
	*/
	void exportMesh(std::string path, Mesh& mesh);
	/*
		Returns the full contents of the given text file.
		@param path The path to the text file.
		@return The full contents of the text file.
	*/
	std::string loadTextFile(std::string path);
};