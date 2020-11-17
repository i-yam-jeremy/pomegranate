#include "bezier.h"

void geo::instanceBezierCurves(FbxMesh* mesh, std::shared_ptr<lsystem::Output> lsystemOut) {
	for (const auto& segment : lsystemOut->getSegments()) {
		geo::instanceBezierCurve(mesh, segment);
	}
}

void geo::instanceBezierCurve(FbxMesh* mesh, const lsystem::OutputSegment& segment) {
	createCircle(mesh, glm::vec3(0), 1, glm::vec3(0, 1, 0), 0.0f, 8);
}

void geo::createCircle(FbxMesh* mesh, glm::vec3 pos, float radius, glm::vec3 dir, float axisRotAngle, int pointCount) {
	int startIndex = mesh->GetControlPointsCount();
	mesh->InitControlPoints(startIndex + pointCount);
	for (int i = 0; i < pointCount; i++) {
		mesh->SetControlPointAt(FbxVector4(cos(i*2.0f*3.1415926535/pointCount), sin(i * 2.0f * 3.1415926535 / pointCount), 0), startIndex+i);
	}
	for (int i = 0; i < pointCount; i++) {
		mesh->BeginPolygon();
		mesh->AddPolygon(startIndex+0);
		mesh->AddPolygon(startIndex+i);
		mesh->AddPolygon(startIndex + ((i + 1) % pointCount));
		mesh->EndPolygon();
	}
}