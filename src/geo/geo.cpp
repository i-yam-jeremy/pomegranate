#include "geo.h"

#include "bezier.h"

Mesh geo::convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut, const char* name) {
	Mesh mesh;
	geo::instanceBezierCurves(mesh, lsystemOut);
	return mesh;
}