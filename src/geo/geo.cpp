#include "geo.h"

#include "meshcreator.h"

void geo::MeshContext::setSegment(int id, Segment segment) {
	segments[id] = segment;
}

bool geo::MeshContext::hasSegment(int id) {
	return segments.find(id) != segments.end();
}

geo::Segment& geo::MeshContext::getSegment(int id) {
	return segments[id];
}

Mesh geo::convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut) {
	Mesh mesh;
	MeshCreator creator(mesh, lsystemOut);
	creator.instance();
	return mesh;
}