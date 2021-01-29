#include "bezier.h"

#include <math.h>

using namespace glm;

void geo::instanceBezierCurves(Mesh& mesh, std::shared_ptr<lsystem::Output> lsystemOut) {
	MeshContext mc;
	for (const auto segmentPtr : lsystemOut->getSegments()) {
		const lsystem::OutputSegment segment = *segmentPtr;
		geo::instanceBezierCurve(mesh, segment, mc);
	}
}

void geo::instanceBezierCurve(Mesh& mesh, const lsystem::OutputSegment& segment, MeshContext& mc) {
	createCylinder(mesh, segment, 8, 4, mc);
}

bool isLastChild(const lsystem::OutputSegment& child, geo::MeshContext& mc) {
	if (child.parent == nullptr) return false;
	for (const auto segment : child.parent->children) {
		if (segment->id > child.id) return false;
	}
	return true;
}

bool edgeIntersectsTriangle(vec3 p1, vec3 p2, vec3 A, vec3 B, vec3 C, vec3& hitPos) {
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
	float t = detT / M;
	if (t < 0 || t > 1) return false;
	float detGamma = a * (tmp6)-j * (tmp2)+c * (tmp3);
	float gamma = detGamma / M;
	if (gamma < 0 || gamma > 1) return false;
	float detBeta = j * (tmp4)-b * (tmp6)+c * (tmp5);
	float beta = detBeta / M;
	if (beta < 0 || beta > 1 - gamma) return false;

	hitPos = pos + t * dir;
	return true;
}

vec3 getVertexPos(Mesh& mesh, Mesh::VertexHandle v) {
	auto point = mesh.point(v);
	return vec3(point[0], point[1], point[2]);
}

bool edgeIntersectsQuad(Mesh& mesh, const Mesh::VertexHandle v1, const Mesh::VertexHandle v2, const std::vector<Mesh::VertexHandle>& quad) {
	assert(quad.size() == 4);
	vec3 hitPos;
	auto p1 = getVertexPos(mesh, v1);
	auto p2 = getVertexPos(mesh, v2);
	vec3 quadPos[4];
	for (int i = 0; i < 4; i++) {
		quadPos[i] = getVertexPos(mesh, quad[i]);
	}
	if (edgeIntersectsTriangle(p1, p2, quadPos[0], quadPos[1], quadPos[2], hitPos)) {
		return true;
	}
	if (edgeIntersectsTriangle(p1, p2, quadPos[0], quadPos[2], quadPos[3], hitPos)) {
		return true;
	}
	return false;
}

bool quadsIntersect(Mesh& mesh, const std::vector<Mesh::VertexHandle>& quad1, const std::vector<Mesh::VertexHandle>& quad2) {
	assert(quad1.size() == 4);
	assert(quad2.size() == 4);
	for (int i = 0; i < 4; i++) {
		if (edgeIntersectsQuad(mesh, quad1[i], quad1[(i + 1) % 4], quad2)) {
			return true;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (edgeIntersectsQuad(mesh, quad2[i], quad2[(i + 1) % 4], quad1)) {
			return true;
		}
	}
	return false;
}

void generateQuad(std::vector<Mesh::VertexHandle>& dest, const std::vector<Mesh::VertexHandle>& loop1, const std::vector<Mesh::VertexHandle>& loop2, const int bridgeOffset, const int quadIndex) {
	assert(loop1.size() == loop2.size());
	dest.push_back(loop1[quadIndex]);
	dest.push_back(loop1[(quadIndex + 1) % loop1.size()]);
	dest.push_back(loop2[(quadIndex + bridgeOffset + 1) % loop1.size()]);
	dest.push_back(loop2[(quadIndex + bridgeOffset) % loop1.size()]);
}

bool isValidEdgeLoopBridge(Mesh& mesh, const std::vector<Mesh::VertexHandle>& loop1, const std::vector<Mesh::VertexHandle>& loop2, const int offset) {
	assert(loop1.size() == loop2.size());
	std::vector<Mesh::VertexHandle> quad1;
	std::vector<Mesh::VertexHandle> quad2;
	for (int i = 0; i < loop1.size(); i++) {
		quad1.clear();
		generateQuad(quad1, loop1, loop2, offset, i);
		for (int j = i + 1; j < loop1.size(); j++) {
			quad2.clear();
			generateQuad(quad2, loop1, loop2, offset, j);
			if (quadsIntersect(mesh, quad1, quad2)) {
				return false;
			}
		}
	}
	return true;
}

void bridgeEdgeLoop(Mesh& mesh, const std::vector<Mesh::VertexHandle>& loop1, const std::vector<Mesh::VertexHandle>& loop2) {
	assert(loop1.size() == loop2.size());
	for (int i = 0; i < loop1.size(); i++) {
		if (isValidEdgeLoopBridge(mesh, loop1, loop2, i)) {
			std::vector<Mesh::VertexHandle> quad;
			for (int j = 0; j < loop1.size(); j++) {
				quad.clear();
				generateQuad(quad, loop1, loop2, i, j);
				mesh.add_face(quad);
				std::cout << "Added quad face" << std::endl;
			}
			break;
		}
	}
}

void generateBranchTopology(Mesh& mesh, std::shared_ptr<lsystem::OutputSegment> parent, geo::MeshContext& mc) {
	for (const auto child : parent->children) {
		bridgeEdgeLoop(mesh,
			           mc.getSegment(parent->id).endVertices,
					   mc.getSegment(child->id).startVertices);
	}
}

void geo::createCylinder(Mesh& mesh, const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc) {
	std::vector<Mesh::VertexHandle> vertices;
	if (segment.parent != nullptr && segment.parent->children.size() == 1) {
		vertices = std::vector<Mesh::VertexHandle>(mc.getSegment(segment.parent->id).endVertices);
	}
	else {
		createCircle(mesh, vertices, segment.mat, segment.translation, 0, pointCount);
	}
	auto startVertices = std::vector<Mesh::VertexHandle>(vertices);
	for (int j = 0; j <= rings; j++) {
		float interpFactor = segment.length*(float(j + 1) / (rings + 1));
		createCircle(mesh, vertices, segment.mat, segment.translation, interpFactor, pointCount);
		for (int i = 0; i < pointCount; i++) {
			std::vector<Mesh::VertexHandle> faceVertices;
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
		generateBranchTopology(mesh, segment.parent, mc);
	}
}

void geo::createCircle(Mesh& mesh, std::vector<Mesh::VertexHandle>& vertices, mat4 mat, vec3 translation, float interpFactor, int pointCount) {
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = vec3(interpFactor, 0.2*sin(i * 2.0f * M_PI / pointCount), 0.2*cos(i * 2.0f * M_PI / pointCount));
		vec3 p = vec4(circleOffset, 1) * mat;
		p += translation;
		vertices.push_back(mesh.add_vertex(Mesh::Point(p.x, p.y, p.z)));
	}
}