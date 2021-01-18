#pragma once

#include "io.h"

#include <OpenMesh/Core/IO/MeshIO.hh>

#include <fstream>
#include <streambuf>

void io::exportCSVRig(std::string path, std::shared_ptr<lsystem::Output> out) {
	std::ofstream fout(path);
	for (const auto segment : out->getSegments()) {
		int parentId = (segment->parent == nullptr) ? -1 : segment->parent->id;
		auto t = segment->translation;
		fout << segment->id << ",";
		fout << parentId << ",";
		fout << t.x << "," << t.y << "," << t.z;
		fout << std::endl;
	}
	fout.close();
}

void io::exportMesh(std::string path, Mesh& mesh) {
	if (!OpenMesh::IO::write_mesh(mesh, path)) {
		std::cerr << "Error writing mesh to " << path << std::endl;
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