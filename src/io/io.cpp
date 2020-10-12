#pragma once

#include "reader.h"

std::unordered_map<std::string, FbxNode*> IO::loadInputFbx(std::string path) {
	FbxManager* sdkManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	ios->SetBoolProp(IMP_FBX_MATERIAL, true);
	ios->SetBoolProp(IMP_FBX_TEXTURE, true);
	ios->SetBoolProp(IMP_FBX_ANIMATION, false);

	FbxScene* scene = FbxScene::Create(sdkManager, "");
	FbxImporter* importer = FbxImporter::Create(sdkManager, "");
	importer->Initialize(path, -1, ios);
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