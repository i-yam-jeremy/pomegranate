#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"
#include "geo/geo.h"

int main(int argc, char** argv) {
	auto modelPieces = io::loadFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.fbx");
	auto source = io::loadTextFile("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt");
	auto out = lsystem::compile(source);

	FbxManager* sdkManager = modelPieces.begin()->second->GetScene()->GetFbxManager();
	FbxScene* scene = FbxScene::Create(sdkManager, "");
	geo::convertLsystemToGeo(scene, out, "Tree");

	io::exportFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-output.fbx", scene);

	return 0;
}
