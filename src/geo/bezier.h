#pragma once

#include "geo.h"
#include "../lsystem/Lsystem.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace geo {
	void instanceBezierCurves(Mesh& mesh, std::shared_ptr<lsystem::Output> lsystemOut);
	void instanceBezierCurve(Mesh& mesh, const lsystem::OutputSegment& segment, MeshContext& mc);
	void createCylinder(Mesh& mesh, const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc);
	void createCircle(Mesh& mesh, std::vector<Mesh::VertexHandle>& vertices, glm::mat4 mat, glm::vec3 translation, float interpFactor, int pointCount);
};