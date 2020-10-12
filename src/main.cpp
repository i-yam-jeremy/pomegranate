#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"

int main(int argc, char** argv) {
	auto modelPieces = io::loadFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.fbx");
	auto source = io::loadTextFile("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt");
	auto out = lsystem::compile(source);

	for (auto segment : out->getSegments()) {
		auto model = modelPieces[segment.type];
		std::cout << "Found model: " << model->GetName() << ", " << model->GetMesh()->GetName() << std::endl;
	}

	std::cout << out->toString() << std::endl;
	return 0;
}
