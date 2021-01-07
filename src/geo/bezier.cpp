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
	createCylinder(mesh, segment, 8, 1);
}

void geo::createCylinder(FbxMesh* mesh, const lsystem::OutputSegment& segment, int pointCount, int rings) {
	int startIndex = mesh->GetControlPointsCount();
	createCircle(mesh, segment.mat, segment.translation, 0, pointCount);
	for (int j = 0; j <= rings; j++) {
		float interpFactor = segment.length*(float(j + 1) / (rings + 1));
		createCircle(mesh, segment.mat, segment.translation, interpFactor, pointCount);
		for (int i = 0; i < pointCount; i++) {
			mesh->BeginPolygon();
			mesh->AddPolygon(startIndex + i);
			mesh->AddPolygon(startIndex + ((i + 1) % pointCount));
			mesh->AddPolygon(startIndex + pointCount + ((i + 1) % pointCount));
			mesh->AddPolygon(startIndex + pointCount + i);
			mesh->EndPolygon();
		}
		startIndex += pointCount;
	}
}

void geo::createCircle(FbxMesh* mesh, mat4 mat, vec3 translation, float interpFactor, int pointCount) {
	int startIndex = mesh->GetControlPointsCount();
	for (int i = 0; i < pointCount; i++) {
		vec3 circleOffset = vec3(0.5*interpFactor, 0.2*sin(i * 2.0f * M_PI / pointCount), 0.2*cos(i * 2.0f * M_PI / pointCount));
		vec3 p = vec4(circleOffset, 1) * mat;
		p += translation;
		mesh->SetControlPointAt(FbxVector4(p.x, p.y, p.z), startIndex+i);
	}
}