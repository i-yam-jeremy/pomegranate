#pragma once

#include "io.h"

#include <fstream>
#include <streambuf>

std::unordered_map<std::string, FbxNode*> io::loadFbx(std::string path) {
	FbxManager* sdkManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	ios->SetBoolProp(IMP_FBX_MATERIAL, true);
	ios->SetBoolProp(IMP_FBX_TEXTURE, true);

	FbxScene* scene = FbxScene::Create(sdkManager, "");
	FbxImporter* importer = FbxImporter::Create(sdkManager, "");
	importer->Initialize(path.c_str(), -1, ios);
	importer->Import(scene);
	importer->Destroy();

	std::unordered_map<std::string, FbxNode*> geoByName;

	FbxNode* root = scene->GetRootNode();
	for (int i = 0; i < root->GetChildCount(); i++) {
		FbxNode* child = root->GetChild(i);
		geoByName[std::string(child->GetName())] = child;
	}

	return geoByName;
}

void io::exportFbx(std::string path, FbxScene* scene) {
	FbxManager* sdkManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	ios->SetBoolProp(EXP_FBX_MATERIAL, true);
	ios->SetBoolProp(EXP_FBX_TEXTURE, true);

	FbxExporter* exporter = FbxExporter::Create(sdkManager, "");
	exporter->Initialize(path.c_str(), -1, ios);
	exporter->Export(scene);
	exporter->Destroy();
}

std::string io::loadTextFile(std::string path) {
	std::ifstream in(path);
	std::string str;

	in.seekg(0, std::ios::end);
	str.reserve(in.tellg());
	in.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	return str;
}