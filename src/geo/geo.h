#pragma once

#include <fbxsdk.h>
#include "../lsystem/Lsystem.h"

namespace geo {
	/*
		Converts the given Lsystem output into FBX geometry and adds it to the given scene
		@param scene The FBX scene.
		@param lsystemOut The Lsystem output.
		@param name The name of the FBX mesh and node to be created.
	*/
	void convertLsystemToGeo(FbxScene* scene, std::shared_ptr<lsystem::Output> lsystemOut, const char* name);
};