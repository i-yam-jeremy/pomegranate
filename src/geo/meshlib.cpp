#include "meshlib.h"

#include <algorithm>
#include <cstdarg>

meshlib::Vertex meshlib::Mesh::addVertex(vec3 p) {
	VertexData data{p};
	size_t handle = getNextHandle();
	vertices[handle] = data;
	return Vertex(this, handle);
}

meshlib::Face meshlib::Mesh::addFace(std::vector<Vertex>& verts) {
	FaceData data;
	size_t handle = getNextHandle();
	faces[handle] = data;
	auto f = Face(this, handle);
	updateFaceVertices(f, verts);
	return f;
}

vec3 meshlib::Mesh::getVertexPosition(const Vertex& v) {
	return vertices[getHandle(v)].position;
}

void meshlib::Mesh::updateVertexPosition(Vertex& v, vec3 pos) {
	vertices[getHandle(v)].position = pos;
}

std::vector<meshlib::Vertex> meshlib::Mesh::getFaceVertices(const Face& f) {
	std::vector<Vertex> verts;
	for (const auto& vertexHandle : faces[getHandle(f)].vertices) {
		verts.push_back(Vertex(this, vertexHandle));
	}
	return verts;
}

void meshlib::Mesh::updateFaceVertices(Face& f, std::vector<Vertex>& verts) {
	auto& faceData = faces[getHandle(f)];

	// Clear old data
	for (const auto& vertexHandle : faceData.vertices) {
		auto& faces = vertices[vertexHandle].faces;
		const auto& found = std::find(faces.begin(), faces.end(), getHandle(f));
		if (found != faces.end()) {
			faces.erase(found);
		}
	}
	faceData.vertices.clear();

	// Add new data
	for (auto& v : verts) {
		const auto vertexHandle = getHandle(v);
		vertices[vertexHandle].faces.push_back(getHandle(f));
		faceData.vertices.push_back(vertexHandle);
	}
}

std::vector<meshlib::Face> meshlib::Mesh::getNeighboringFaces(const Vertex& v) {
	std::vector<Face> faces;

	for (const auto faceHandle : vertices[getHandle(v)].faces) {
		faces.push_back(Face(this, faceHandle));
	}
	return faces;
}

void meshlib::Mesh::toOBJ(std::ostream& out) {
	std::unordered_map<Handle, size_t> vertexIndices;
	size_t currentVertexIndex = 1;
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

meshlib::Handle meshlib::Mesh::getHandle(const Vertex& v) {
	return v.handle;
}

meshlib::Handle meshlib::Mesh::getHandle(const Face& f) {
	return f.handle;
}

bool meshlib::Vertex::operator==(const Vertex& v) const {
	return handle == v.handle && mesh == v.mesh;
}

vec3 meshlib::Vertex::pos() const {
	return mesh->getVertexPosition(*this);
}

void meshlib::Vertex::pos(vec3 p) {
	mesh->updateVertexPosition(*this, p);
}

meshlib::Vertex meshlib::Edge::v0() const {
	return m_v0;
}

meshlib::Vertex meshlib::Edge::v1() const {
	return m_v1;
}

meshlib::Vertex meshlib::Edge::split(float t) {
	t = 1.0f-t;
	const auto allFaces = m_mesh->getNeighboringFaces(m_v0);
	std::vector<Face> faces;
	for (const auto& face : allFaces) {
		const auto vertices = face.vertices();
		const auto& found = std::find(vertices.begin(), vertices.end(), m_v1);
		if (found != vertices.end()) {
			faces.push_back(face);
		}
	}

	for (auto& face : faces) {
		auto vertices = face.vertices();
		for (int i = 0; i < vertices.size(); i++) {
			auto a = vertices[i];
			auto b = vertices[(i+1)%vertices.size()];
			if (a == m_v1 && b == m_v0) { // If edge going the opposite direction, then invert t
				t = 1.0f - t;
				std::swap(a, b);
			}

			if (a == m_v0 && b == m_v1) {
				const auto newVertex = m_mesh->addVertex(a.pos() + t*(b.pos() - a.pos()));
				vertices.insert(vertices.begin() + i + 1, newVertex);
				m_v1 = newVertex;
				return newVertex;
			}
		}
		face.update(vertices);
	}

	assert(false); // Should never reach here, should always find edge
}

std::vector<meshlib::Vertex> meshlib::Face::vertices() const {
	return mesh->getFaceVertices(*this);
}

std::vector<meshlib::Edge> meshlib::Face::edges() const {
	const auto verts = vertices();
	std::vector<Edge> edges;
	for (int i = 0; i < verts.size(); i++) {
		edges.push_back(Edge(mesh, verts[i], verts[(i+1)%verts.size()]));
	}
	return edges;
}

void meshlib::Face::update(std::vector<Vertex>& verts) {
	mesh->updateFaceVertices(*this, verts);
}
