#pragma once

#include "geo.h"
#include "../lsystem/Lsystem.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace geo {
	class MeshCreator {
	public:
		MeshCreator(Mesh& mesh, std::shared_ptr<lsystem::Output> lsystemOut) :
			mesh(mesh),
			lsystemOut(lsystemOut) {};
		void instance();
	private:
		struct IntersectionPoint {
			vec3 pos;
			OpenMesh::SmartEdgeHandle edge;
			OpenMesh::SmartFaceHandle other;
		};
		void instanceSegment(const lsystem::OutputSegment& segment, MeshContext& mc);
		bool isLastChild(const lsystem::OutputSegment& child, MeshContext& mc);
		bool edgeIntersectsTriangle(vec3 p1, vec3 p2, vec3 A, vec3 B, vec3 C, vec3& hitPos);
		vec3 getVertexPos(OpenMesh::SmartVertexHandle v);
		bool edgeIntersectsQuad(const OpenMesh::SmartVertexHandle v1, const OpenMesh::SmartVertexHandle v2, const std::vector<OpenMesh::SmartVertexHandle>& quad);
		void generateQuad(std::vector<OpenMesh::SmartVertexHandle>& dest, const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, const int bridgeOffset, const int quadIndex);
		vec3 createOrthonormalVector(vec3 u1);
		mat3 createPlaneBasis(vec3 planeNormal);
		vec2 projectPoint(Mesh::Point meshPoint, vec3 planeNormal, mat3 planeBasis);
		std::vector<vec2> projectVertices(const std::vector<OpenMesh::SmartVertexHandle>& points, vec3 planeNormal, mat3 planeBasis);
		int getEdgeLoopBridgeOffset(const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, vec3 loop1Normal, vec3 loop2Normal);
		std::vector<OpenMesh::SmartFaceHandle> bridgeEdgeLoop(const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, vec3 loop1Normal, vec3 loop2Normal);
		void quadsIntersect(const OpenMesh::SmartFaceHandle quad1, const OpenMesh::SmartFaceHandle quad2, std::vector<IntersectionPoint>& intersectionPoints);
		void findBridgeIntersections(const std::vector<OpenMesh::SmartFaceHandle>& bridge, const std::vector<OpenMesh::SmartFaceHandle>& otherBridge, std::vector<IntersectionPoint>& intersectionPoints);
		void findBridgeIntersections(int index, const std::vector<std::vector<OpenMesh::SmartFaceHandle>>& bridges, std::vector<IntersectionPoint>& intersectionPoints);
		void generateBranchTopology(std::shared_ptr<lsystem::OutputSegment> parent, MeshContext& mc);
		void createCylinder(const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc);
		void createCircle(std::vector<OpenMesh::SmartVertexHandle>& vertices, glm::mat4 mat, glm::vec3 translation, float interpFactor, int pointCount);

		Mesh& mesh;
		std::shared_ptr<lsystem::Output> lsystemOut;
	};
};