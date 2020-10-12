#pragma once

#include <string>
#include <unordered_map>
#include <fbxsdk.h>

class IO {
public:
	static std::unordered_map<std::string, FbxNode*> loadInputFbx(std::string path);
};