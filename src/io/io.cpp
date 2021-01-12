#pragma once

#include "io.h"

#include <OpenMesh/Core/IO/MeshIO.hh>

#include <fstream>
#include <streambuf>

void io::exportFbx(std::string path, Mesh& mesh) {
	if (OpenMesh::IO::write_mesh(mesh, path)) {
		std::cout << "Success" << std::endl;
	}
	else {
		std::cout << "Fail" << std::endl;
	}
}

std::string io::loadTextFile(std::string path) {
	std::ifstream in(path);
	std::string str;

	in.seekg(0, std::ios::end);
	str.reserve(in.tellg());
	in.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	return str;
}