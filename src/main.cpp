#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"
#include "geo/geo.h"

int main(int argc, char** argv) {
	auto source = io::loadTextFile("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt");
	
	auto out = lsystem::compile(source);

	auto mesh = geo::convertLsystemToGeo(out, "Tree");

	io::exportFbx("C:/Users/Jeremy\\ Berchtold/Documents/GitHub/pomegranate/examples/test-output.fbx", mesh);

	return 0;
}
