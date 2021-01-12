#pragma once

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include "../lsystem/Lsystem.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

namespace geo {
	/*
		Converts the given Lsystem output into geometry.
		@param lsystemOut The Lsystem output.
		@return The generated geometry.
	*/
	Mesh convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut);
};