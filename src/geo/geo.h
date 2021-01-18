#pragma once

#include <unordered_map>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include "../lsystem/Lsystem.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

namespace geo {
	class Segment {
	public:
		Segment() {};
		Segment(std::vector<Mesh::VertexHandle> endVertices) :
			endVertices(endVertices) {};
		std::vector<Mesh::VertexHandle> endVertices;
	};

	class MeshContext {
	public:
		MeshContext() {};
		void setSegment(int id, Segment seg);
		const std::vector<Mesh::VertexHandle>& getEndVertices(int id);
	private:
		std::unordered_map<int, Segment> segments;
	};

	/*
		Converts the given Lsystem output into geometry.
		@param lsystemOut The Lsystem output.
		@return The generated geometry.
	*/
	Mesh convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut);
};