#include "meshcreator.h"

#include <math.h>

using namespace glm;

#include <fstream>
std::ofstream foutIntersections("C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/examples/intersection-pts.txt", std::ios::out);

void geo::MeshCreator::instance() {
	MeshContext mc;
	for (const auto& segmentPtr : lsystemOut->getSegments()) {
		const lsystem::OutputSegment segment = *segmentPtr;
		instanceSegment(segment, mc);
	}
}

void geo::MeshCreator::instanceSegment(const lsystem::OutputSegment& segment, MeshContext& mc) {
	createCylinder(segment, 8, 4, mc);
}

bool geo::MeshCreator::isLastChild(const lsystem::OutputSegment& child, MeshContext& mc) {
	if (child.parent == nullptr) return false;
	for (const auto& segment : child.parent->children) {
		if (segment->id > child.id) return false;
	}
	return true;
}

bool geo::MeshCreator::edgeIntersectsTriangle(vec3 p1, vec3 p2, vec3 A, vec3 B, vec3 C, vec3& hitPos, float& t) {
	auto pos = p1;
	auto dir = p2 - p1;

	float a = A.x - B.x;
	float d = A.y - B.y;
	float g = A.z - B.z;
	float b = A.x - C.x;
	float e = A.y - C.y;
	float h = A.z - C.z;
	float c = dir.x;
	float f = dir.y;
	float i = dir.z;
	float j = A.x - pos.x;
	float k = A.y - pos.y;
	float l = A.z - pos.z;

	float tmp1 = d * h - g * e;
	float tmp2 = d * i - g * f;
	float tmp3 = d * l - g * k;
	float tmp4 = e * i - h * f;
	float tmp5 = k * h - l * e;
	float tmp6 = k * i - l * f;

	float M = a * (tmp4)-b * (tmp2)+c * (tmp1);

	float detT = a * (-tmp5) - b * (tmp3)+j * (tmp1);
	t = detT / M;
	if (t <= 0 || t >= 0.9999) return false;
	float detGamma = a * (tmp6)-j * (tmp2)+c * (tmp3);
	float gamma = detGamma / M;
	if (gamma < 0 || gamma > 1) return false;
	float detBeta = j * (tmp4)-b * (tmp6)+c * (tmp5);
	float beta = detBeta / M;
	if (beta < 0 || beta > 1 - gamma) return false;

	hitPos = pos + t * dir;
	return true;
}

vec3 geo::MeshCreator::getVertexPos(OpenMesh::SmartVertexHandle v) {
	auto point = mesh.point(v);
	return vec3(point[0], point[1], point[2]);
}

void geo::MeshCreator::edgeIntersectsQuad(const OpenMesh::SmartEdgeHandle edge, const OpenMesh::SmartFaceHandle quad, std::vector<IntersectionPoint>& intersectionPoints) {
	assert(quad.vertices().count_if([](OpenMesh::SmartVertexHandle a) { return true;  }) == 4);
	float t;
	vec3 hitPos;
	auto p1 = getVertexPos(edge.v0());
	auto p2 = getVertexPos(edge.v1());
	std::vector<vec3> quadPos;
	for (const auto& v : quad.vertices()) {
		quadPos.push_back(getVertexPos(v));
	}
	if (edgeIntersectsTriangle(p1, p2, quadPos[0], quadPos[1], quadPos[2], hitPos, t)) {
		const auto v = editableBranchFacesByIndex.find(quad.idx());
		if (v == editableBranchFacesByIndex.end()) {
			editableBranchFacesByIndex[quad.idx()] = editableBranchFaces.size();
			editableBranchFaces[editableBranchFaces.size()] = quad;
		}
		const EditableFaceHandle f = (v == editableBranchFacesByIndex.end()) ? editableBranchFaces.size() - 1 : v->second;
		IntersectionPoint p = { hitPos, t, edge, f };
		intersectionPoints.push_back(p);
	}
	if (edgeIntersectsTriangle(p1, p2, quadPos[0], quadPos[2], quadPos[3], hitPos, t)) {
		const auto v = editableBranchFacesByIndex.find(quad.idx());
		if (v == editableBranchFacesByIndex.end()) {
			editableBranchFacesByIndex[quad.idx()] = editableBranchFaces.size();
			editableBranchFaces[editableBranchFaces.size()] = quad;
		}
		const EditableFaceHandle f = (v == editableBranchFacesByIndex.end()) ? editableBranchFaces.size() - 1 : v->second;
		IntersectionPoint p = { hitPos, t, edge, f };
		intersectionPoints.push_back(p);
	}
}

void geo::MeshCreator::generateQuad(std::vector<OpenMesh::SmartVertexHandle>& dest, const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, const int bridgeOffset, const int quadIndex) {
	assert(loop1.size() == loop2.size());
	// Copies vertices to avoid non-manifold vertex/edge errors (complex vertex / complex edge)
	dest.push_back(loop1[quadIndex]);
	dest.push_back(loop1[(quadIndex + 1) % loop1.size()]);
	dest.push_back(loop2[(quadIndex + bridgeOffset + 1) % loop1.size()]);
	dest.push_back(loop2[(quadIndex + bridgeOffset) % loop1.size()]);

	for (int i = 0; i < dest.size(); i++) {
		auto p = mesh.point(dest[i]);
		dest[i] = mesh.add_vertex(p);
	}
}

int geo::MeshCreator::getEdgeLoopBridgeOffset(const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, vec3 loop1Normal, vec3 loop2Normal) {
	assert(loop1.size() == loop2.size());

	std::vector<vec3> loop1Points;
	std::vector<vec3> loop2Points;

	for (const auto& v : loop1) {
		auto p = mesh.point(v);
		loop1Points.push_back(vec3(p[0], p[1], p[2]));
	}

	for (const auto& v : loop2) {
		auto p = mesh.point(v);
		loop2Points.push_back(vec3(p[0], p[1], p[2]));
	}


	float minLength = 1000000000000.0f;
	int bestOffset = -1;
	for (int i = 0; i < loop1.size(); i++) {
		float curLength = 0.0f;
		for (int j = 0; j < loop1.size(); j++) {
			curLength += length(loop1Points[j] - loop2Points[(j + i) % loop1.size()]);
			if (curLength >= minLength) {
				break;
			}
		}
		if (curLength < minLength) {
			minLength = curLength;
			bestOffset = i;
		}
	}

	return bestOffset;
}

void geo::MeshCreator::bridgeEdgeLoop(const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, vec3 loop1Normal, vec3 loop2Normal, Bridge& bridge) {
	assert(loop1.size() == loop2.size());
	int offset = getEdgeLoopBridgeOffset(loop1, loop2, loop1Normal, loop2Normal);
	std::vector<OpenMesh::SmartVertexHandle> quad;
	for (int j = 0; j < loop1.size(); j++) {
		quad.clear();
		generateQuad(quad, loop1, loop2, offset, j);
		const auto face = mesh.add_face(quad);
		const auto edges = face.edges().to_vector();
		bridge.mainEdges.push_back(edges[0]);
		bridge.mainEdges.push_back(edges[2]);
		bridge.quads.push_back(face);
	}
}

void geo::MeshCreator::findBridgeIntersections(const Bridge& bridge, const Bridge& otherBridge, std::vector<IntersectionPoint>& intersectionPoints) {
	for (const auto& edge : bridge.mainEdges) {
		for (const auto& quad : otherBridge.quads) {
			edgeIntersectsQuad(edge, quad, intersectionPoints);
		}
	}
	for (const auto& edge : otherBridge.mainEdges) {
		for (const auto& quad : bridge.quads) {
			edgeIntersectsQuad(edge, quad, intersectionPoints);
		}
	}
}

void geo::MeshCreator::splitHalfEdge(OpenMesh::SmartHalfedgeHandle target, OpenMesh::SmartVertexHandle newVertex) {
	const auto face = editableBranchFacesByIndex[target.face().idx()];
	editableBranchFacesByIndex.erase(target.face().idx());
	
	std::vector<OpenMesh::SmartVertexHandle> newFaceVertices;
	for (const auto he : target.face().halfedges()) {
		newFaceVertices.push_back(he.from());
		if (he.idx() == target.idx()) {
			newFaceVertices.push_back(newVertex);
		}
	}

	std::cout << "Hello" << std::endl;

	//mesh.delete_face(target.face());
	const auto newFace = mesh.add_face(newFaceVertices);
	editableBranchFaces[face] = newFace;
	editableBranchFacesByIndex[newFace.idx()] = face;
	std::cout << target.face().idx() << " -> " << newFace.idx() << std::endl;
}

void geo::MeshCreator::createManifoldBranchHull(const std::vector<IntersectionPoint> intersections) {
	for (const auto& p : intersections) {
		const auto v = mesh.add_vertex(Mesh::Point(p.pos.x, p.pos.y, p.pos.z));
		splitHalfEdge(p.edge.h0(), v);
		splitHalfEdge(p.edge.h1(), v);
		// TODO update other face references (because faces have been deleted and replaced)
	}
}

void geo::MeshCreator::createBranchTopology(std::shared_ptr<lsystem::OutputSegment> parent, MeshContext& mc) {
	std::vector<Bridge> bridges;
	for (const auto& child : parent->children) {
		Bridge bridge;
		bridgeEdgeLoop(
			           mc.getSegment(parent->id).endVertices,
					   mc.getSegment(child->id).startVertices,
					   vec3(parent->mat[0][0], parent->mat[0][1], parent->mat[0][2]),
					   vec3(child->mat[0][0], child->mat[0][1], child->mat[0][2]),
			bridge);
		bridges.push_back(bridge);
	}

	editableBranchFaces.clear();
	editableBranchFacesByIndex.clear();

	std::vector<IntersectionPoint> intersectionPoints;
	for (int i = 0; i < bridges.size(); i++) {
		for (int j = i + 1; j < bridges.size(); j++) {
			findBridgeIntersections(bridges[i], bridges[j], intersectionPoints);
		}
	}
	
	createManifoldBranchHull(intersectionPoints);
}

void geo::MeshCreator::createCylinder(const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc) {
	std::vector<OpenMesh::SmartVertexHandle> vertices;
	if (segment.parent != nullptr && segment.parent->children.size() == 1) {
		vertices = std::vector<OpenMesh::SmartVertexHandle>(mc.getSegment(segment.parent->id).endVertices);
	}
	else {
		createCircle(vertices, segment.mat, segment.translation, 0, pointCount);
	}
	auto startVertices = std::vector<OpenMesh::SmartVertexHandle>(vertices);
	for (int j = 0; j <= rings; j++) {
		float interpFactor = segment.length*(float(j + 1) / (rings + 1));
		createCircle(vertices, segment.mat, segment.translation, interpFactor, pointCount);
		for (int i = 0; i < pointCount; i++) {
			std::vector<OpenMesh::SmartVertexHandle> faceVertices;
			faceVertices.push_back(vertices[i]);
			faceVertices.push_back(vertices[((i + 1) % pointCount)]);
			faceVertices.push_back(vertices[pointCount + ((i + 1) % pointCount)]);
			faceVertices.push_back(vertices[pointCount + i]);
			mesh.add_face(faceVertices);
		}
		vertices.erase(vertices.begin(), vertices.begin() + pointCount);
	}
	mc.setSegment(segment.id, Segment(startVertices, vertices));
	if (isLastChild(segment, mc)) {
		createBranchTopology(segment.parent, mc);
	}
}

void geo::MeshCreator::createCircle(std::vector<OpenMesh::SmartVertexHandle>& vertices, mat4 mat, vec3 translation, float interpFactor, int pointCount) {
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = vec3(interpFactor, 0.2*sin(i * 2.0f * M_PI / pointCount), 0.2*cos(i * 2.0f * M_PI / pointCount));
		vec3 p = vec4(circleOffset, 1) * mat;
		p += translation;
		vertices.push_back(mesh.add_vertex(Mesh::Point(p.x, p.y, p.z)));
	}
}