#include "geo.h"

#include "bezier.h"

void geo::MeshContext::setSegment(int id, Segment segment) {
	segments[id] = segment;
}

const std::vector<Mesh::VertexHandle>& geo::MeshContext::getEndVertices(int id) {
	return segments[id].endVertices;
}

Mesh geo::convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut) {
	Mesh mesh;
	geo::instanceBezierCurves(mesh, lsystemOut);
	return mesh;
}