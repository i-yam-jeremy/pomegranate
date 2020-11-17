#include "bezier.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace glm;

void geo::instanceBezierCurves(FbxMesh* mesh, std::shared_ptr<lsystem::Output> lsystemOut) {
	for (const auto& segment : lsystemOut->getSegments()) {
		geo::instanceBezierCurve(mesh, segment);
	}
}

void geo::instanceBezierCurve(FbxMesh* mesh, const lsystem::OutputSegment& segment) {
	createCylinder(mesh, glm::vec3(0), 1, 1, 1, glm::vec3(0, 0, 1), 0.0f, 8);
}

void geo::createCylinder(FbxMesh* mesh, vec3 pos, float radius1, float radius2, float length, vec3 dir, float axisRotAngle, int pointCount) {
	int startIndex = mesh->GetControlPointsCount();
	createCircle(mesh, pos, radius1, dir, axisRotAngle, pointCount);
	createCircle(mesh, pos + length*dir, radius2, dir, axisRotAngle, pointCount);
	for (int i = 0; i < pointCount; i++) {
		mesh->BeginPolygon();
		mesh->AddPolygon(startIndex + i);
		mesh->AddPolygon(startIndex + ((i + 1) % pointCount));
		mesh->AddPolygon(startIndex + pointCount + ((i + 1) % pointCount));
		mesh->AddPolygon(startIndex + pointCount + i);
		mesh->EndPolygon();
	}
}

void geo::createCircle(FbxMesh* mesh, vec3 pos, float radius, vec3 dir, float axisRotAngle, int pointCount) {
	int startIndex = mesh->GetControlPointsCount();
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = radius*vec3(cos(i * 2.0f * M_PI / pointCount), sin(i * 2.0f * M_PI / pointCount), 0);
		vec3 p = pos + circleOffset;
		mesh->SetControlPointAt(FbxVector4(p.x, p.y, p.z), startIndex+i);
	}
}