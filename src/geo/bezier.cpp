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
	createCylinder(mesh, segment, 8, 0, mc);
}

void geo::createCylinder(Mesh& mesh, const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc) {
	std::vector<Mesh::VertexHandle> vertices;
	if (segment.parent != nullptr && segment.parent->children.size() == 1) {
		vertices = std::vector<Mesh::VertexHandle>(mc.getEndVertices(segment.parent->id));
	}
	else {
		createCircle(mesh, vertices, segment.mat, segment.translation, 0, pointCount);
	}
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
	mc.setSegment(segment.id, Segment(vertices));
}

void geo::createCircle(Mesh& mesh, std::vector<Mesh::VertexHandle>& vertices, mat4 mat, vec3 translation, float interpFactor, int pointCount) {
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = vec3(interpFactor, 0.2*sin(i * 2.0f * M_PI / pointCount), 0.2*cos(i * 2.0f * M_PI / pointCount));
		vec3 p = vec4(circleOffset, 1) * mat;
		p += translation;
		vertices.push_back(mesh.add_vertex(Mesh::Point(p.x, p.y, p.z)));
	}
}