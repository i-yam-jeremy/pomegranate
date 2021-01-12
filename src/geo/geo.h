#pragma once

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include "../lsystem/Lsystem.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

namespace geo {
	/*
		Converts the given Lsystem output into geometry.
		@param lsystemOut The Lsystem output.
		@param name The name of the FBX mesh and node to be created.
		@return The generated geometry.
	*/
	Mesh convertLsystemToGeo(std::shared_ptr<lsystem::Output> lsystemOut, const char* name);
};