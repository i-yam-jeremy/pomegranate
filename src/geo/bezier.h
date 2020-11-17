#pragma once

#include <fbxsdk.h>
#include "../lsystem/Lsystem.h"

namespace geo {
	void instanceBezierCurves(FbxMesh* mesh, std::shared_ptr<lsystem::Output> lsystemOut);
	void instanceBezierCurve(FbxMesh* mesh, const lsystem::OutputSegment& segment);
};