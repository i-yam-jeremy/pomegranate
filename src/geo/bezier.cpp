#include "bezier.h"

void geo::instanceBezierCurves(FbxMesh* mesh, std::shared_ptr<lsystem::Output> lsystemOut) {
	for (const auto& segment : lsystemOut->getSegments()) {
		geo::instanceBezierCurve(mesh, segment);
	}
}

void geo::instanceBezierCurve(FbxMesh* mesh, const lsystem::OutputSegment& segment) {
	std::cout << "Instancing Curve: TODO" << std::endl;
}