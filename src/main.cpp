#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"

int main(int argc, char** argv) {
	auto modelPieces = io::loadFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.fbx");
	auto source = io::loadTextFile("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt");
	auto out = lsystem::compile(source);

	FbxManager* sdkManager = modelPieces.begin()->second->GetScene()->GetFbxManager();
	FbxScene* scene = FbxScene::Create(sdkManager, "");

	long i = 0;
	for (auto segment : out->getSegments()) {
		auto model = modelPieces[segment.type];
		FbxNode* node = FbxNode::Create(sdkManager, ("object" + std::to_string(i)).c_str());
		node->SetNodeAttribute(model->GetMesh());
		auto res = scene->AddGeometry(model->GetMesh());
		if (!res) {
			std::cout << "ERROR: Geometry could not be copied to new scene" << std::endl;
		}

		node->SetRotationPivotAsCenterRecursive();
		node->SetRotationPivotAsCenterRecursive();
		node->LclTranslation.Set(segment.getTranslation());
		node->LclRotation.Set(segment.getRotation());
		node->LclScaling.Set(segment.getScaling());

		auto r = node->LclRotation.Get();
		std::cout << "LclRotation: " << r[0] << ", " << r[1] << ", " << r[2] << std::endl;

		auto result = scene->GetRootNode()->AddChild(node);
		if (!result) {
			std::cout << "ERROR: couldn't add node";
		}
		i++;
	}

	io::exportFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-output.obj", scene);

	return 0;
}
