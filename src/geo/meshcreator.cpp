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

void geo::MeshCreator::edgeIntersectsQuad(const Edge edge, const Face quad, std::vector<IntersectionPoint>& intersectionPoints) {
	assert(quad.vertices().size() == 4);
	float t;
	vec3 hitPos;
	auto p1 = edge.v0().pos();
	auto p2 = edge.v1().pos();
	std::vector<vec3> quadPos;
	for (const auto& v : quad.vertices()) {
		quadPos.push_back(v.pos());
	}
	if (edgeIntersectsTriangle(p1, p2, quadPos[0], quadPos[1], quadPos[2], hitPos, t)) {
		IntersectionPoint p = { hitPos, t, edge, quad };
		intersectionPoints.push_back(p);
	}
	if (edgeIntersectsTriangle(p1, p2, quadPos[0], quadPos[2], quadPos[3], hitPos, t)) {
		IntersectionPoint p = { hitPos, t, edge, quad };
		intersectionPoints.push_back(p);
	}
}

void geo::MeshCreator::generateQuad(std::vector<Vertex>& dest, const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, const int bridgeOffset, const int quadIndex) {
	assert(loop1.size() == loop2.size());

	dest.push_back(loop1[quadIndex]);
	dest.push_back(loop1[(quadIndex + 1) % loop1.size()]);
	dest.push_back(loop2[(quadIndex + bridgeOffset + 1) % loop1.size()]);
	dest.push_back(loop2[(quadIndex + bridgeOffset) % loop1.size()]);
}

int geo::MeshCreator::getEdgeLoopBridgeOffset(const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, vec3 loop1Normal, vec3 loop2Normal) {
	assert(loop1.size() == loop2.size());

	std::vector<vec3> loop1Points;
	std::vector<vec3> loop2Points;

	for (const auto& v : loop1) {
		loop1Points.push_back(v.pos());
	}

	for (const auto& v : loop2) {
		loop2Points.push_back(v.pos());
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

void geo::MeshCreator::bridgeEdgeLoop(const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, vec3 loop1Normal, vec3 loop2Normal, Bridge& bridge) {
	assert(loop1.size() == loop2.size());
	int offset = getEdgeLoopBridgeOffset(loop1, loop2, loop1Normal, loop2Normal);
	std::vector<Vertex> quad;
	for (int j = 0; j < loop1.size(); j++) {
		quad.clear();
		generateQuad(quad, loop1, loop2, offset, j);
		const auto face = mesh.addFace(quad);
		const auto edges = face.edges();
		bridge.mainEdges.push_back(edges[1]); // Just need one edge because the next edge will be captured by the next quad
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

std::vector<geo::MeshCreator::IntersectionPoint> geo::MeshCreator::findOutermostIntersections(std::vector<IntersectionPoint>& points) {
	std::unordered_map<size_t, IntersectionPoint*> outermostIntersections;
	
	for (auto& p : points) {
		auto& entry = outermostIntersections.find(p.edge.hash());
		if (entry == outermostIntersections.end() || entry->second->t < p.t) {
			outermostIntersections[p.edge.hash()] = &p;
		}
	}

	std::vector<IntersectionPoint> filteredPoints;
	for (const auto& entry : outermostIntersections) {
		filteredPoints.push_back(*(entry.second));
	}

	return filteredPoints;
}


void geo::MeshCreator::createManifoldBranchHull(std::vector<IntersectionPoint> intersections) {
	std::vector<Vertex> newVertices;
	for (auto& p : intersections) {
		const auto newVertex = p.edge.split(p.t);
		newVertices.push_back(newVertex);
	}

	for (int i = 0; i < intersections.size(); i++) {
		auto& p = intersections[i];
		const auto newVertex = newVertices[i];
		const auto verts = p.other.vertices();
		for (int j = 0; j < verts.size(); j++) {
			std::vector<Vertex> v;
			v.push_back(newVertex);
			v.push_back(verts[j]);
			v.push_back(verts[(j + 1) % verts.size()]);
			mesh.addFace(v);
		}
	}

	for (auto& p : intersections) {
		mesh.deleteFace(p.other);
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

	std::vector<IntersectionPoint> intersectionPoints;
	for (int i = 0; i < bridges.size(); i++) {
		for (int j = i + 1; j < bridges.size(); j++) {
			findBridgeIntersections(bridges[i], bridges[j], intersectionPoints);
		}
	}

	intersectionPoints = findOutermostIntersections(intersectionPoints);

	for (const auto& p : intersectionPoints) {
		foutIntersections << p.pos.x << "," << p.pos.y << "," << p.pos.z << "," << p.t << std::endl;
	}

	createManifoldBranchHull(intersectionPoints);
}

void geo::MeshCreator::createCylinder(const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc) {
	std::vector<Vertex> vertices;
	if (segment.parent != nullptr && segment.parent->children.size() == 1) {
		vertices = std::vector<Vertex>(mc.getSegment(segment.parent->id).endVertices);
	}
	else {
		createCircle(vertices, segment.mat, segment.translation, 0, pointCount);
	}
	auto startVertices = std::vector<Vertex>(vertices);
	for (int j = 0; j <= rings; j++) {
		float interpFactor = segment.length*(float(j + 1) / (rings + 1));
		createCircle(vertices, segment.mat, segment.translation, interpFactor, pointCount);
		for (int i = 0; i < pointCount; i++) {
			std::vector<Vertex> faceVertices;
			faceVertices.push_back(vertices[i]);
			faceVertices.push_back(vertices[((i + 1) % pointCount)]);
			faceVertices.push_back(vertices[pointCount + ((i + 1) % pointCount)]);
			faceVertices.push_back(vertices[pointCount + i]);
			mesh.addFace(faceVertices);
		}
		vertices.erase(vertices.begin(), vertices.begin() + pointCount);
	}
	mc.setSegment(segment.id, Segment(startVertices, vertices));
	if (isLastChild(segment, mc)) {
		createBranchTopology(segment.parent, mc);
	}
}

void geo::MeshCreator::createCircle(std::vector<Vertex>& vertices, mat4 mat, vec3 translation, float interpFactor, int pointCount) {
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = vec3(interpFactor, 0.2*sin(i * 2.0f * M_PI / pointCount), 0.2*cos(i * 2.0f * M_PI / pointCount));
		vec3 p = vec4(circleOffset, 1) * mat;
		p += translation;
		vertices.push_back(mesh.addVertex(p));
	}
}
