#pragma once

#include "geo.h"
#include "meshlib.h"
#include "../lsystem/Lsystem.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

using namespace meshlib;

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
			Edge edge;
			Face other;
		};
		struct Bridge {
			std::vector<Face> quads;
			std::vector<Edge> mainEdges; // the edges connecting the loops, not the edges of an individual loop
		};

		void instanceSegment(const lsystem::OutputSegment& segment, MeshContext& mc);
		bool isLastChild(const lsystem::OutputSegment& child, MeshContext& mc);
		bool edgeIntersectsTriangle(vec3 p1, vec3 p2, vec3 A, vec3 B, vec3 C, vec3& hitPos, float& t);
		void edgeIntersectsQuad(const Edge edge, const Face quad, std::vector<IntersectionPoint>& intersectionPoints);
		void generateQuad(std::vector<Vertex>& dest, const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, const int bridgeOffset, const int quadIndex);
		int getEdgeLoopBridgeOffset(const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, vec3 loop1Normal, vec3 loop2Normal);
		void bridgeEdgeLoop(const std::vector<Vertex>& loop1, const std::vector<Vertex>& loop2, std::string segmentType, vec3 loop1Normal, vec3 loop2Normal, Bridge& bridge);
		void findBridgeIntersections(const Bridge& bridge, const Bridge& otherBridge, std::vector<IntersectionPoint>& intersectionPoints);

		std::vector<IntersectionPoint> findOutermostIntersections(std::vector<IntersectionPoint>& points);
		void dfsUtil(Vertex currentVertex, const std::vector<Edge>& edges, std::vector<Vertex>& currentComponent, std::unordered_map<size_t, bool>& verticesVisited);
		void findConnectedComponents(std::vector<Edge> edges, std::vector<std::vector<Vertex>>& out);
		mat3 createPlaneBasis(vec3 normal);
		void joinFacesIntoNgons(std::vector<IntersectionPoint>& intersections, std::vector<Vertex>& newVertices, std::unordered_map<Face*, std::vector<int>>& intersectionsByOtherFace);
		void mergeByDistance(std::unordered_map<Face*, std::vector<int>>& intersectionsByOtherFace);
		bool fillInHoles(std::unordered_map<Face*, std::vector<int>>& intersectionsByOtherFace);
		void triangulateFaces(std::unordered_map<Face*, std::vector<int>>& intersectionsByOtherFace);
		void createManifoldBranchHull(std::vector<IntersectionPoint> intersections);

		void createBranchTopology(std::shared_ptr<lsystem::OutputSegment> parent, MeshContext& mc);
		void createCylinder(const lsystem::OutputSegment& segment, int pointCount, int rings, MeshContext& mc);
		void createCircle(std::vector<Vertex>& vertices, glm::mat4 mat, glm::vec3 translation, float interpFactor, int pointCount);

		Mesh& mesh;
		std::shared_ptr<lsystem::Output> lsystemOut;
	};
};
