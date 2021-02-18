#include "meshcreator.h"

#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <earcut.hpp>

using namespace glm;

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

void geo::MeshCreator::bridgeEdgeLoop(const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, std::string segmentType, vec3 loop1Normal, vec3 loop2Normal, Bridge& bridge) {
	assert(loop1.size() == loop2.size());
	int offset = getEdgeLoopBridgeOffset(loop1, loop2, loop1Normal, loop2Normal);
	std::vector<Vertex> quad;
	for (int j = 0; j < loop1.size(); j++) {
		quad.clear();
		generateQuad(quad, loop1, loop2, offset, j);
		const auto face = mesh.addFace(quad, segmentType);
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

void geo::MeshCreator::dfsUtil(Vertex currentVertex, const std::vector<Edge>& edges, std::vector<Vertex>& currentComponent, std::unordered_map<size_t, bool>& verticesVisited) {
	verticesVisited[currentVertex.hash()] = true;
	currentComponent.push_back(currentVertex);
	for (const auto& edge : edges) {
		if (edge.v0() == currentVertex && !verticesVisited[edge.v1().hash()]) {
			dfsUtil(edge.v1(), edges, currentComponent, verticesVisited);
		}
		else if (edge.v1() == currentVertex && !verticesVisited[edge.v0().hash()]) {
			dfsUtil(edge.v0(), edges, currentComponent, verticesVisited);
		}
	}
}

void geo::MeshCreator::findConnectedComponents(std::vector<Edge> edges, std::vector<std::vector<Vertex>>& out) {
	std::unordered_map<size_t, bool> verticesVisited;
	std::unordered_map<size_t, std::shared_ptr<Vertex>> verticesByHash;
	for (const auto& edge : edges) {
		verticesVisited[edge.v0().hash()] = false;
		verticesByHash[edge.v0().hash()] = std::make_shared<Vertex>(edge.v0());
		verticesVisited[edge.v1().hash()] =  false;
		verticesByHash[edge.v1().hash()] = std::make_shared<Vertex>(edge.v1());
	}
	
	for (const auto& entry : verticesVisited) {
		if (!entry.second) {
			std::vector<Vertex> currentComponent;
			dfsUtil(*(verticesByHash[entry.first]), edges, currentComponent, verticesVisited);
			out.push_back(currentComponent);
		}
	}
}

mat3 geo::MeshCreator::createPlaneBasis(vec3 normal) {
	auto u1 = normal;
	auto offset = (abs(u1.x) < 0.001 && abs(u1.y) < 0.001) ? vec3(1, 0, 0) : vec3(0, 0, 1);
	auto v2 = u1 + offset;
	auto u2 = v2 - (dot(u1, v2) / dot(u1, u1)) * u1;
	
	auto e1 = normalize(u1);
	auto e2 = normalize(u2);
	auto e3 = cross(e1, e2);

	mat3 m;

	m[0][0] = e1.x;
	m[0][1] = e1.y;
	m[0][2] = e1.z;

	m[1][0] = e2.x;
	m[1][1] = e2.y;
	m[1][2] = e2.z;

	m[2][0] = e3.x;
	m[2][1] = e3.y;
	m[2][2] = e3.z;

	return m;
}

void geo::MeshCreator::createManifoldBranchHull(std::vector<IntersectionPoint> intersections) {
	std::vector<Vertex> newVertices;
	for (auto& p : intersections) {
		const auto newVertex = p.edge.split(p.t);
		newVertices.push_back(newVertex);
	}

	/*
	1. Group intersection points by other face (possibly a multi-map or map of vectors)
	2. Find all newly created vertices that intersect with the face
	3. Add those vertices to the face in between the two vertices for the left edge, and the two vertices for the right edge, and there should only be four vertices per other face
	*/
	std::unordered_map<Face*, std::vector<int>> intersectionsByOtherFace;
	for (int i = 0; i < intersections.size(); i++) {
		auto& p = intersections[i];
		intersectionsByOtherFace[&p.other].push_back(i);
	}

	for (auto& entry : intersectionsByOtherFace) {
		auto face = *(entry.first);
		auto vertices = face.vertices();
		auto& refPoint = vertices[0];
		auto& newVertexIndices = entry.second;
		std::sort(newVertexIndices.begin(), newVertexIndices.end(),
			[&](int a, int b) {
				float distA = distance(newVertices[a].pos(), refPoint.pos());
				float distB = distance(newVertices[b].pos(), refPoint.pos());
				return distA < distB;
			});
		for (auto index : newVertexIndices) {
			auto newVertex = newVertices[index];
			vertices.insert(vertices.begin() + 1, newVertex);
		}
		face.update(vertices);
	}

	/*
	Remove small edges:
	For each face,
		for each vertex on the face,
			if the current vertex is nearer than the minimum distance threshold to the next vertex then,
				merge the two vertices
	*/
	const float mergeDistThreshold = 0.01;
	for (auto& entry : intersectionsByOtherFace) {
		auto face = *(entry.first);
		auto vertices = face.vertices();
		for (int i = 0; i < vertices.size(); i++) {
			auto a = vertices[i];
			auto b = vertices[(i + 1) % vertices.size()];
			auto dist = distance(a.pos(), b.pos());
			if (dist < mergeDistThreshold) {
				vertices.erase(vertices.begin() + ((i + 1) % vertices.size()));
				mesh.mergeVertices(a, b);
			}
		}
	}

	std::vector<Face*> toRemove;
	for (auto& entry : intersectionsByOtherFace) {
		auto face = *(entry.first);
		auto vertices = face.vertices();
		if (vertices.size() < 3) {
			mesh.deleteFace(face);
			toRemove.push_back(entry.first);
		}
	}
	for (auto& face : toRemove) {
		intersectionsByOtherFace.erase(face);
	}

	/*
	Fill in holes:
	1. Find edges with only one adjoining face
	2. Group connected edges (edges sharing a vertex, or connected by a mutually shared edge)
	3. Create a face from each group of edges
	*/
	std::vector<Edge> openEdges;
	for (auto& entry : intersectionsByOtherFace) {
		auto face = *(entry.first);
		for (auto edge : face.edges()) {
			if (edge.neighboringFaces().size() == 1) {
				openEdges.push_back(edge);
			}
		}
	}

	std::vector<std::vector<Vertex>> connectedComponents;
	findConnectedComponents(openEdges, connectedComponents);

	for (auto& group : connectedComponents) {
		mesh.addFace(group, "UNKNOWN");
	}

	/*
	Replace n-gon faces:
	1. Triangulate the face
	2. Add triangles to the mesh
	3. Delete the original face
	*/
	for (auto& entry : intersectionsByOtherFace) {
		auto face = *(entry.first);
		const auto vertices = face.vertices();
		if (vertices.size() <= 4) continue; // Don't triangulate quads or tris
		using Coord = float;
		using N = uint16_t;
		using Point = std::pair<Coord, Coord>;
		std::vector<Point> polygon;

		auto estimatedNormal = normalize(cross(vertices[0].pos() - vertices[1].pos(), vertices[2].pos() - vertices[1].pos()));
		auto planeBasis = createPlaneBasis(estimatedNormal);
		auto inversePlaneBasis = inverse(planeBasis);
		for (const auto& v : vertices) {
			auto p = v.pos();
			p -= estimatedNormal * dot(p, estimatedNormal);
			p = inversePlaneBasis * p;
			//assert(abs(p.x) < 0.01);
			Point point = std::make_pair(p.y, p.z);
			polygon.push_back(point);
		}

		std::vector<std::vector<Point>> polygonWrapper;
		polygonWrapper.push_back(polygon);
		std::vector<N> indices = mapbox::earcut<N>(polygonWrapper);
		for (int i = 0; i < indices.size(); i += 3) {
			std::vector<Vertex> verts;
			verts.push_back(vertices[indices[i+0]]);
			verts.push_back(vertices[indices[i+1]]);
			verts.push_back(vertices[indices[i+2]]);
			mesh.addFace(verts, face.type());
		}
	}

	for (auto& entry : intersectionsByOtherFace) {
		auto face = *(entry.first);
		if (face.vertices().size() <= 4) continue; // Quads and tris aren't triangulated, so don't delete
		mesh.deleteFace(face);
	}
}

void geo::MeshCreator::createBranchTopology(std::shared_ptr<lsystem::OutputSegment> parent, MeshContext& mc) {
	std::vector<Bridge> bridges;
	for (const auto& child : parent->children) {
		Bridge bridge;
		bridgeEdgeLoop(
			           mc.getSegment(parent->id).endVertices,
					   mc.getSegment(child->id).startVertices,
					   child->type,
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
			mesh.addFace(faceVertices, segment.type);
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
		auto v = mesh.addVertex(p);
		v.uv(vec2(float(i)/pointCount, interpFactor));
		vertices.push_back(v);
	}
}
