#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"
#include "geo/geo.h"

int main(int argc, char** argv) {
	auto source = io::loadTextFile("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-input.txt");
	
	auto out = lsystem::compile(source);

	auto mesh = geo::convertLsystemToGeo(out);

	io::exportFbx("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/test-output.obj", mesh);

	return 0;
}
