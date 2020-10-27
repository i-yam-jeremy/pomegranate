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
		auto newMesh = (FbxMesh*) model->GetMesh()->Clone();

		newMesh->SetPivot(segment.getFbxTransform());
		newMesh->ApplyPivot();

		node->SetNodeAttribute(newMesh);
		auto res = scene->AddGeometry(newMesh);
		if (!res) {
			std::cout << "ERROR: Geometry could not be copied to new scene" << std::endl;
		}

		auto result = scene->GetRootNode()->AddChild(node);
		if (!result) {
			std::cout << "ERROR: couldn't add node";
		}
		i++;
	}

	io::exportFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-output.obj", scene);

	return 0;
}
