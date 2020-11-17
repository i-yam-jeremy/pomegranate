#pragma once

#include <fbxsdk.h>
#include "../lsystem/Lsystem.h"
#include <glm/vec3.hpp>

namespace geo {
	void instanceBezierCurves(FbxMesh* mesh, std::shared_ptr<lsystem::Output> lsystemOut);
	void instanceBezierCurve(FbxMesh* mesh, const lsystem::OutputSegment& segment);
	void createCylinder(FbxMesh* mesh, glm::vec3 pos, float radius1, float radius2, float length, glm::vec3 dir, float axisRotAngle, int pointCount);
	void createCircle(FbxMesh* mesh, glm::vec3 pos, float radius, glm::vec3 dir, float axisRotAngle, int pointCount);
};