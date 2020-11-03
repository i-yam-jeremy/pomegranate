#pragma once

#include <string>
#include <unordered_map>
#include <fbxsdk.h>

namespace io {
	/*
		Returns a map from geometry name to FbxNode* which represents each geometry type in the input file.
		Each name corresponds to an Lsystem rule type (e.g. "Branch", "Leaf", etc.).
		@param path The path to the input FBX file.
		@return A map containing input geometry.
	*/
	std::unordered_map<std::string, FbxNode*> loadFbx(std::string path);
	/*
		Exports the given scene to the given file path.
		@param path The output file path.
		@param scene The scene to be exported.
	*/
	void exportFbx(std::string path, FbxScene* scene);
	/*
		Returns the full contents of the given text file.
		@param path The path to the text file.
		@return The full contents of the text file.
	*/
	std::string loadTextFile(std::string path);
};