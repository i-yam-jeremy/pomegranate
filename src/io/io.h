#pragma once

#include <string>
#include <unordered_map>
#include <fbxsdk.h>

namespace io {
	std::unordered_map<std::string, FbxNode*> loadFbx(std::string path);
	std::string loadTextFile(std::string path);
};