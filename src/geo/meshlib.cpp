#include "meshlib.h"

meshlib::Vertex meshlib::Mesh::addVertex(vec3 p) {
	VertexData data{p};
	size_t handle = getNextHandle();
	vertices[handle] = data;
	return Vertex(*this, handle);
}

meshlib::Face meshlib::Mesh::addFace(std::vector<Vertex>& verts) {
	FaceData data;
	for (auto& v : verts) {
		data.vertices.push_back(getHandle(v));
	}
	size_t handle = getNextHandle();
	faces[handle] = data;
	return Face(*this, handle);
}

std::vector<meshlib::Vertex> meshlib::Mesh::getFaceVertices(Face& f) {
	std::vector<Vertex> verts;
	for (const auto& vertexHandle : faces[getHandle(f)].vertices) {
		verts.push_back(Vertex(*this, vertexHandle));
	}
	return verts;
}

void meshlib::Mesh::updateFaceVertices(Face& f, std::vector<Vertex>& verts) {
	auto& vertices = faces[getHandle(f)].vertices;
	vertices.clear();
	for (auto& v : verts) {
		vertices.push_back(getHandle(v));
	}
}

void meshlib::Mesh::toOBJ(std::ostream& out) {
	std::unordered_map<Handle, size_t> vertexIndices;
	size_t currentVertexIndex = 0;
	for (const auto& entry : vertices) {
		const auto& v = entry.second;
		out << "v " << v.position.x << " " << v.position.y << " " << v.position.z << std::endl;
		vertexIndices[entry.first] = currentVertexIndex;
		currentVertexIndex++;
	}

	for (const auto& face : faces) {
		out << "f ";
		for (const auto& v : face.second.vertices) {
			const auto vertexIndex = vertexIndices[v];
			out << vertexIndex << " ";
		}
		out << std::endl;
	}
}

meshlib::Handle meshlib::Mesh::getNextHandle() {
	return currentHandle++;
}

meshlib::Handle meshlib::Mesh::getHandle(Vertex& v) {
	return v.handle;
}

meshlib::Handle meshlib::Mesh::getHandle(Face& f) {
	return f.handle;
}

std::vector<meshlib::Vertex> meshlib::Face::vertices() {
	return mesh.getFaceVertices(*this);
}

void meshlib::Face::update(std::vector<Vertex>& verts) {
	mesh.updateFaceVertices(*this, verts);
}
