#include <iostream>
#include <memory>
#include <string>

#include "io/io.h"
#include "lsystem/Lsystem.h"
#include "geo/geo.h"
#include "value/Random.h"

int main(int argc, char** argv) {
	argc = 3;
	argv[1] = "C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt";
	argv[2] = "11";

	if (argc != 3 && argc != 4) {
		std::cerr << "Usage: pomegranate input_file seed [output_file_basename]" << std::endl;
		exit(1);
	}
	std::string inputFile = argv[1];
	auto source = io::loadTextFile(inputFile);

	unsigned long seed = std::stol(argv[2]);
	Random::generator.seed(seed);

	std::string outputFile;
	if (argc == 4) {
		outputFile = argv[3];
	}
	else {
		outputFile = inputFile;
	}
	
	auto out = lsystem::compile(source);

	auto mesh = geo::convertLsystemToGeo(out);

	io::exportCSVRig(outputFile + "-rig.csv", out);
	io::exportMesh(outputFile + ".obj", mesh);

	return 0;
}
