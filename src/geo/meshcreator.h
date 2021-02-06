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
			float t;
			OpenMesh::SmartEdgeHandle edge;
			OpenMesh::SmartFaceHandle other;
		};
		struct Bridge {
			std::vector<OpenMesh::SmartFaceHandle> quads;
			std::vector<OpenMesh::SmartEdgeHandle> mainEdges; // the edges connecting the loops, not the edges of an individual loop
		};
		void instanceSegment(const lsystem::OutputSegment& segment, MeshContext& mc);
		bool isLastChild(const lsystem::OutputSegment& child, MeshContext& mc);
		bool edgeIntersectsTriangle(vec3 p1, vec3 p2, vec3 A, vec3 B, vec3 C, vec3& hitPos, float& t);
		vec3 getVertexPos(OpenMesh::SmartVertexHandle v);
		void edgeIntersectsQuad(const OpenMesh::SmartEdgeHandle edge, const OpenMesh::SmartFaceHandle quad, std::vector<IntersectionPoint>& intersectionPoints);
		void generateQuad(std::vector<OpenMesh::SmartVertexHandle>& dest, const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, const int bridgeOffset, const int quadIndex);
		int getEdgeLoopBridgeOffset(const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, vec3 loop1Normal, vec3 loop2Normal);
		void bridgeEdgeLoop(const std::vector<OpenMesh::SmartVertexHandle>& loop1, const std::vector<OpenMesh::SmartVertexHandle>& loop2, vec3 loop1Normal, vec3 loop2Normal, Bridge& bridge);
		void findBridgeIntersections(const Bridge& bridge, const Bridge& otherBridge, std::vector<IntersectionPoint>& intersectionPoints);
		void generateBranchTopology(std::shared_ptr<lsystem::OutputSegment> parent, MeshContext& mc);
		void createCylinder(const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc);
		void createCircle(std::vector<OpenMesh::SmartVertexHandle>& vertices, glm::mat4 mat, glm::vec3 translation, float interpFactor, int pointCount);

		Mesh& mesh;
		std::shared_ptr<lsystem::Output> lsystemOut;
	};
};