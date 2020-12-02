#pragma once

#include <fbxsdk.h>
#include "../lsystem/Lsystem.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace geo {
	void instanceBezierCurves(FbxMesh* mesh, std::shared_ptr<lsystem::Output> lsystemOut);
	void instanceBezierCurve(FbxMesh* mesh, const lsystem::OutputSegment& segment);
	void createCylinder(FbxMesh* mesh, const lsystem::OutputSegment& segment, int pointCount, int rings);
	void createCircle(FbxMesh* mesh, glm::mat4 mat, float interpFactor, int pointCount);
};