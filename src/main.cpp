#include <iostream>
#include <memory>
#include <string>
#include <chrono>

#include <flags.h>

#include "io/io.h"
#include "lsystem/Lsystem.h"
#include "geo/geo.h"
#include "value/Random.h"

/*
	Overload for parsing std::string with flags.h argument parser
*/
std::istream& operator>>(std::istream& stream, std::string& s) {
	return stream >> s;
}

int main(int argc, char** argv) {
	argc = 3;
	argv[1] = "C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt";
	argv[2] = "--seed=11";

	const flags::args args(argc, argv);
	if (args.positional().size() != 1) {
		std::cerr << "Usage: pomegranate [--basename=<base-path-to-output-files>] [--seed=<number>] input_file" << std::endl;
		exit(1);
	}
	const auto& inputFile = args.positional()[0];

	auto now = std::chrono::system_clock::now().time_since_epoch().count();
	const auto seed = args.get<long>("seed", (long)now);
	const auto& outputFile = args.get<std::string>("basename", inputFile.data());

	auto source = io::loadTextFile(inputFile.data());

	Random::generator.seed(seed);
	
	auto out = lsystem::compile(source);
	auto mesh = geo::convertLsystemToGeo(out);

	io::exportCSVRig(outputFile + "-rig.csv", out);
	io::exportMesh(outputFile + ".obj", mesh);

	return 0;
}
