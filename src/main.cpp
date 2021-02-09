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
	/*argc = 4;
	argv[1] = "C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt";
	argv[2] = "--seed=0";
	argv[3] = "--override-generations=2.5";*/

	const flags::args args(argc, argv);
	if (args.positional().size() != 1) {
		std::cerr << "Usage: pomegranate [--basename=<base-path-to-output-files>] [--seed=<number>] [--override-generations=<number>] input_file" << std::endl;
		exit(1);
	}
	const auto& inputFile = args.positional()[0];

	auto now = std::chrono::system_clock::now().time_since_epoch().count();
	const auto seed = args.get<long>("seed", (long)now);
	const auto& outputFile = args.get<std::string>("basename", inputFile.data());
	const auto generations = args.get<float>("override-generations");

	auto source = io::loadTextFile(inputFile.data());

	Random::seed(seed);

	if (generations.has_value()) {
		std::cout << "Generations: " << generations.value() << std::endl;
	}
	auto out = generations.has_value() ? lsystem::compile(source, generations.value(), true) : lsystem::compile(source);
	auto mesh = geo::convertLsystemToGeo(out);

	io::exportCSVRig(outputFile + "-rig.csv", out);
	io::exportMesh(outputFile + ".obj", mesh);

	return 0;
}
