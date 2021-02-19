#include "meshlib.h"

meshlib::Vertex meshlib::Mesh::addVertex(vec3 p) {
	VertexData data{p};
	size_t handle = getNextHandle();
	vertices[handle] = data;
	return Vertex(this, handle);
}

meshlib::Face meshlib::Mesh::addFace(std::vector<Vertex>& verts, std::string type) {
	FaceData data;
	data.type = type;
	size_t handle = getNextHandle();
	faces[handle] = data;
	auto f = Face(this, handle);
	updateFaceVertices(f, verts);
	return f;
}

void meshlib::Mesh::deleteFace(Face& f) {
	faces.erase(getHandle(f));
}

size_t meshlib::Mesh::getVertexCount() const {
	return vertices.size();
}

vec3 meshlib::Mesh::getVertexPosition(const Vertex& v) {
	return vertices[getHandle(v)].position;
}

void meshlib::Mesh::updateVertexPosition(Vertex& v, vec3 pos) {
	vertices[getHandle(v)].position = pos;
}

vec2 meshlib::Mesh::getVertexUV(const Vertex& v) {
	return vertices[getHandle(v)].uv;
}

void meshlib::Mesh::updateVertexUV(Vertex& v, vec2 uv) {
	vertices[getHandle(v)].uv = uv;
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

std::string meshlib::Mesh::getFaceType(const Face& f) {
	return faces[getHandle(f)].type;
}

void meshlib::Mesh::mergeVertices(Vertex& a, Vertex& b) {
	if (a == b) return;
	a.pos((a.pos() + b.pos()) / 2.0f);

	auto& facesContainingA = vertices[getHandle(a)].faces;
	auto& facesContainingB = vertices[getHandle(b)].faces;
	for (auto& face : facesContainingB) {
		auto& faceVertices = faces[face].vertices;
		for (int i = 0; i < faceVertices.size(); i++) {
			if (faceVertices[i] == getHandle(b)) {
				faceVertices[i] = getHandle(a);
			}
		}
		
		auto& found = std::find(facesContainingA.begin(), facesContainingA.end(), face);
		if (found == facesContainingA.end()) {
			facesContainingA.push_back(face);
		}
	}

	vertices.erase(getHandle(b));
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
		out << "vt " << v.uv.x << " " << v.uv.y << std::endl;
		vertexIndices[entry.first] = currentVertexIndex;
		currentVertexIndex++;
	}

	for (const auto& type : segmentTypes) {
		out << "g " << type << std::endl;
		out << "usemtl " << type << std::endl;
		for (const auto& face : faces) {
			if (face.second.vertices.size() < 3) continue;
			if (face.second.type != type) continue;
			out << "f ";
			for (const auto& v : face.second.vertices) {
				const auto vertexIndex = vertexIndices[v];
				const auto uvIndex = vertexIndex;
				out << vertexIndex << "/" << uvIndex << " ";
			}
			out << std::endl;
		}
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

size_t meshlib::Vertex::hash() const {
	return handle;
}

vec3 meshlib::Vertex::pos() const {
	return mesh->getVertexPosition(*this);
}

void meshlib::Vertex::pos(vec3 p) {
	mesh->updateVertexPosition(*this, p);
}

vec2 meshlib::Vertex::uv() const {
	return mesh->getVertexUV(*this);
}

void meshlib::Vertex::uv(vec2 tx) {
	mesh->updateVertexUV(*this, tx);
}

bool meshlib::Edge::operator==(const Edge& other) const {
	return m_mesh == other.m_mesh && 
		m_v0 == other.m_v0 &&
		m_v1 == other.m_v1;
}

size_t meshlib::Edge::hash() const {
	const auto meshVertexCount = m_mesh->getVertexCount();
	return m_v0.hash() * meshVertexCount + m_v1.hash();
}

meshlib::Vertex meshlib::Edge::v0() const {
	return m_v0;
}

meshlib::Vertex meshlib::Edge::v1() const {
	return m_v1;
}

std::vector<meshlib::Face> meshlib::Edge::neighboringFaces() const {
	const auto allFaces = m_mesh->getNeighboringFaces(m_v0);
	std::vector<Face> faces;
	for (const auto& face : allFaces) {
		const auto vertices = face.vertices();
		const auto& found = std::find(vertices.begin(), vertices.end(), m_v1);
		if (found != vertices.end()) {
			faces.push_back(face);
		}
	}

	return faces;
}

meshlib::Vertex meshlib::Edge::split(float t) {
	std::vector<Face> faces = neighboringFaces();

	auto newVertex = m_mesh->addVertex(m_v0.pos() + t * (m_v1.pos() - m_v0.pos()));
	newVertex.uv(m_v0.uv() + t * (m_v1.uv() - m_v0.uv()));

	int edgesFound = 0;
	for (auto& face : faces) {
		auto vertices = face.vertices();
		
		for (int i = 0; i < vertices.size(); i++) {
			auto a = vertices[i];
			auto b = vertices[(i+1)%vertices.size()];
			if (a == m_v1 && b == m_v0) {
				vertices[(i + 1) % vertices.size()] = newVertex;
				face.update(vertices);
				edgesFound++;
				break;
			}

			if (a == m_v0 && b == m_v1) {
				vertices[i] = newVertex;
				face.update(vertices);
				edgesFound++;
				break;
			}
		}
	}

	m_v1 = newVertex;

	return newVertex;
}

size_t meshlib::Face::hash() const {
	return handle;
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

std::string meshlib::Face::type() const {
	return mesh->getFaceType(*this);
}

void meshlib::Face::update(std::vector<Vertex>& verts) {
	mesh->updateFaceVertices(*this, verts);
}
