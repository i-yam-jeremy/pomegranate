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

	for (auto segment : out->getSegments()) {
		auto model = modelPieces[segment.type];
		FbxNode* node = FbxNode::Create(sdkManager, "test");
		node->SetNodeAttribute(model->GetMesh());
		node->LclTranslation.Set(segment.getTranslation());
		//node->LclRotation.Set(segment.getRotation());
		auto result = scene->GetRootNode()->AddChild(node);
		if (!result) {
			std::cout << "ERROR: couldn't add node";
		}
		std::cout << segment.toString() << std::endl;
	}

	io::exportFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-output.obj", scene);

	return 0;
}
