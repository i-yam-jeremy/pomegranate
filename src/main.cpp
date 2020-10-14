#include <iostream>
#include <memory>
#include <glm/vec3.hpp>

#include "io/io.h"
#include "lsystem/Lsystem.h"

int main(int argc, char** argv) {
	auto modelPieces = io::loadFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.fbx");
	auto source = io::loadTextFile("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt");
	auto out = lsystem::compile(source);

	FbxManager* sdkManager = modelPieces.begin()->second->GetScene()->GetFbxManager();
	FbxScene* scene = FbxScene::Create(sdkManager, "");

	for (auto segment : out->getSegments()) {
		auto model = modelPieces[segment.type];
		std::cout << "Found model: " << model->GetName() << ", " << model->GetMesh()->GetName() << std::endl;
		FbxNode* node = FbxNode::Create(sdkManager, "test");
		// TODO add mesh to new node and then add it so it gets included in the output FBX
		scene->GetRootNode()->AddChild((FbxNode*)model->Clone());
	}

	std::cout << scene->GetRootNode()->GetChildCount() << std::endl;

	io::exportFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-output.fbx", scene);

	std::cout << out->toString() << std::endl;
	return 0;
}
