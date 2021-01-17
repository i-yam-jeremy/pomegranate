#include "bezier.h"

#include <math.h>

using namespace glm;

void geo::instanceBezierCurves(Mesh& mesh, std::shared_ptr<lsystem::Output> lsystemOut) {
	for (const auto segmentPtr : lsystemOut->getSegments()) {
		const lsystem::OutputSegment segment = *segmentPtr;
		geo::instanceBezierCurve(mesh, segment);
	}
}

void geo::instanceBezierCurve(Mesh& mesh, const lsystem::OutputSegment& segment) {
	createCylinder(mesh, segment, 8, 1);
}

void geo::createCylinder(Mesh& mesh, const lsystem::OutputSegment& segment, int pointCount, int rings) {
	std::vector<Mesh::VertexHandle> vertices;
	createCircle(mesh, vertices, segment.mat, segment.translation, 0, pointCount);
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
}

void geo::createCircle(Mesh& mesh, std::vector<Mesh::VertexHandle>& vertices, mat4 mat, vec3 translation, float interpFactor, int pointCount) {
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = vec3(interpFactor, 0.2*sin(i * 2.0f * M_PI / pointCount), 0.2*cos(i * 2.0f * M_PI / pointCount));
		vec3 p = vec4(circleOffset, 1) * mat;
		p += translation;
		vertices.push_back(mesh.add_vertex(Mesh::Point(p.x, p.y, p.z)));
	}
}