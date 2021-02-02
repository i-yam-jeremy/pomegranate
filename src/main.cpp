#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"
#include "geo/geo.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: pomegranate input_file" << std::endl;
		exit(1);
	}
	std::string inputFile = argv[1];
	auto source = io::loadTextFile(inputFile);
	
	auto out = lsystem::compile(source);

	auto mesh = geo::convertLsystemToGeo(out);

	io::exportCSVRig(inputFile + "-rig.csv", out);
	io::exportMesh(inputFile + ".obj", mesh);

	return 0;
}
