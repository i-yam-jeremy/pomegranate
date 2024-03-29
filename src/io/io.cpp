#include "io.h"

#include <fstream>
#include <streambuf>

void io::exportCSVRig(std::string path, std::shared_ptr<lsystem::Output> out) {
	std::ofstream fout(path);
	for (const auto& segment : out->getMainOut()->getSegments()) {
		int parentId;
		if (segment->parent == nullptr) {
			// Add a handle at the start of this segment if there is no parent
			parentId = -1;
			int id = out->getMainOut()->getSegments().size() + segment->id;
			auto t = segment->translation;
			fout << id << ",";
			fout << parentId << ",";
			fout << t.x << "," << t.y << "," << t.z;
			fout << std::endl;
			parentId = id;
		}
		else {
			parentId = segment->parent->id;
		}
		auto t = segment->translation + vec3(vec4(1, 0, 0, 1) * segment->mat);
		fout << segment->id << ",";
		fout << parentId << ",";
		fout << t.x << "," << t.y << "," << t.z;
		fout << std::endl;
	}
	fout.close();
}

void io::exportMesh(std::string path, meshlib::Mesh& mesh) {
	std::ofstream fout(path);
	mesh.toOBJ(fout);
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
